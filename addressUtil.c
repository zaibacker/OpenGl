#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   /* inet_aton */
#include <net/if.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "addressUtil.h"

/*---------------------------------------------------------------------------*/
        /* struct in_addr ===> xxx.xxx.xxx.xxx                        */
        /*------------------------------------------------------------*/
void getDotAddr(struct in_addr inaddr, char *dotAddr, size_t len)
{
 union {
   struct in_addr inaddr;
   struct {
            unsigned char v1,v2,v3,v4;
   } octets;
 } data;

 char str[3+1+3+1+3+1+3+1];     /* nnn.nnn.nnn.nnn'\0' */
 
 data.inaddr=inaddr;
 sprintf(str,"%d.%d.%d.%d",data.octets.v1, data.octets.v2,
                           data.octets.v3, data.octets.v4);
 strncpy(dotAddr,str,len);
 dotAddr[len-1]='\0';
}

/*---------------------------------------------------------------------------*/
        /* Recuperation d'un NOM OFFICIEL a partir d'adresse internet */
        /* En entree : une adresse internet (inaddr)                  */
        /*             un tableau de caracteres et sa longueur (len)  */
        /* En Sortie : un nom de machine officiel (distantHostName)   */
        /* ATTENTION : utilisation d'une variable statique            */
        /*            ==> Appel a proteger avec un mutex              */
        /*                si plusieurs threads...                     */
        /*------------------------------------------------------------*/
void getDistantHostName(struct in_addr inaddr, char *distantHostName,size_t len)
{
 struct hostent *hostent=gethostbyaddr((char*)&inaddr,sizeof(inaddr),AF_INET);

 if (hostent==NULL) {
     /* fprintf (stderr, "getDistantHost:: error on gethostbyaddr\n"); */
        getDotAddr(inaddr,distantHostName,len);
 }
 else { strncpy(distantHostName,hostent->h_name,len);
        distantHostName[len-1]='\0';
 }
}

/*---------------------------------------------------------------------------*/
        /* Recuperation du NOM OFFICIEL de la machine locale         */
        /* En entree : un tableau de caracteres et sa longueur (len) */
        /* En Sortie : le nom officiel de la machine locale          */
        /* ATTENTION : utilisation d'une variable statique           */
        /*            ==> Appel a proteger avec un mutex             */
        /*                si plusieurs threads...                    */
        /*-----------------------------------------------------------*/
void getLocalHostName(char *localHostName, size_t len)
{
 strcpy(localHostName,"");

 if (gethostname(localHostName,len)==-1)
 {
  /* fprintf(stderr, "Impossible de localiser la machine locale\n"); */
   strncpy(localHostName,"localhost",len);
   localHostName[len-1]='\0';
 }
 else
 {
  struct hostent *hostent = gethostbyname(localHostName);
  if (hostent!=NULL)
  { 
   strncpy(localHostName,hostent->h_name,len);
   localHostName[len-1]='\0';
  }
  else
  {
   /* fprintf(stderr, "Impossible de localiser la machine locale\n"); */
   strncpy(localHostName,"localhost",len);
   localHostName[len-1]='\0';
  }
 }

}

/*---------------------------------------------------------------------------*/
            /* gethostid buggee sous Linux?                    */
            /*                    (octets dans le desordre)    */
            /* ==> getHostId                                   */
            /* ATTENTION : utilisation d'une variable statique */
            /*            ==> Appel a proteger avec un mutex   */
            /*                si plusieurs threads...          */
            /* ATTENTION : permet d'obtenir une adresse au     */
            /*             format reseaux                      */
            /*------------------------------------------------ */

#define SIZE 256

struct in_addr getHostId(void)
{
 struct in_addr adr;
 
 char localHostName[SIZE];

 adr.s_addr=0;

 getLocalHostName(localHostName,SIZE);

 if (inet_aton (localHostName, &adr) == 0) { /* si inet_aton non disponible,
                                                voir inet_addr */
 
   /* erreur sur inet_aton => essai de gethostbyname */
 
   struct hostent *hostent = gethostbyname(localHostName);
   if (hostent == NULL) {
       /* fprintf (stderr, "getAddr::address %s not found\n", address); */
        adr.s_addr=0;
   }
   else {
    /* adr = *((struct in_addr *) (hostent -> h_addr)); */
       adr = *((struct in_addr *) (hostent -> h_addr_list[0]));
   }
  }

  return adr;
}

/*--------------------------------------------------------------------*/
void getAllBbroadcastAdresses(int sock, BroadcastAdresses *ba)
{
  struct sockaddr_in adrBroadcast;
  struct sockaddr    dst;
 
  struct  ifconf  ifc;
  char buf[BUFSIZ];
 
  struct ifreq *ifr;
  int ok,n;
 
 
  /*----------*/
   ba->nbAdr=0;
  /*----------*/
 
  ifc.ifc_len = sizeof(buf);
  ifc.ifc_buf = buf;
 
  ok = ioctl(sock, SIOCGIFCONF, &ifc);
  if (ok<0) { perror("getAllBbroadcastAdresses::ioctl avec SIOCGIFCONF=>");
              exit(EXIT_FAILURE);
  }

  ifr = ifc.ifc_req;
 
  for (n = ifc.ifc_len / sizeof (struct ifreq); --n >= 0; ifr++) {
          /*
           * We must be careful that we don't use an interface
           * dev oted to an address family other than those intended;
           * if we were interested in NS interfaces, the
           * AF_INET would be AF_NS.
           */
          if (ifr->ifr_addr.sa_family != AF_INET)
               continue;
          if (ioctl(sock, SIOCGIFFLAGS, ifr) < 0) {
               perror("getAllBbroadcastAdresses::ioctl avec SIOCGIFFLAGS");
               continue;
          }
          /*
           * Skip boring cases.
           */
           if ((ifr->ifr_flags & IFF_UP) == 0 ||
             (ifr->ifr_flags & IFF_LOOPBACK) ||
             (ifr->ifr_flags & (IFF_BROADCAST | IFF_POINTOPOINT)) == 0)
               continue;
 
 
          if (ifr->ifr_flags & IFF_POINTOPOINT) {
             if (ioctl(sock, SIOCGIFDSTADDR, ifr) < 0) {
                 perror("getAllBbroadcastAdresses::ioctl avec SIOCGIFDSTADDR");
                 continue;
             }
          /*   printf("Cas IFF_POINTTOPOINT:\n"); */
             memcpy(&dst, &ifr->ifr_dstaddr, sizeof(ifr->ifr_dstaddr));
          }
          else
          if (ifr->ifr_flags & IFF_BROADCAST) {
             if (ioctl(sock, SIOCGIFBRDADDR, ifr) < 0) {
                perror("getAllBbroadcastAdresses::ioctl avec SIOCGIFBRDADDR");
                continue;
             }
          /*  printf("Cas IFF_BROADCAST:\n");   */
             memcpy(&dst, &ifr->ifr_broadaddr, sizeof(ifr->ifr_broadaddr));
          }
 
          /*-----------------------------------------------------*/
           adrBroadcast = *(struct sockaddr_in*)(&dst);
           ba->adrTab[ba->nbAdr++] = adrBroadcast.sin_addr.s_addr;
           if (ba->nbAdr==MAX_BROADCAST_ADDR) break;
          /*-----------------------------------------------------*/
  }
}
