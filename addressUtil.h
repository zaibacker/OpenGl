/*  addressUtil.h -  sockets  -  ENIB  -  LI2  -  01/05/2002 */ 

#ifndef ADDRESSUTIL_H
#define ADDRESSUTIL_H



/*---------------------------------------------------------------------------*/
        /* struct in_addr ===> xxx.xxx.xxx.xxx                        */ 
        /*------------------------------------------------------------*/
extern void getDotAddr(struct in_addr inaddr, char *dotAddr, size_t len);

/*---------------------------------------------------------------------------*/
        /* Recuperation d'un NOM OFFICIEL a partir d'adresse internet */
        /* En entree : une adresse internet (inaddr)                  */
        /*             un tableau de caracteres et sa longueur (len)  */
        /* En Sortie : un nom de machine officiel (distantHostName)   */
        /* ATTENTION : utilisation d'une variable statique            */
        /*            ==> Appel a proteger avec un mutex              */
        /*                si plusieurs threads...                     */
        /*------------------------------------------------------------*/
extern void getDistantHostName(struct in_addr inaddr,
                               char *distantHostName,size_t len);

/*---------------------------------------------------------------------------*/
        /* Recuperation du NOM OFFICIEL de la machine locale         */
        /* En entree : un tableau de caracteres et sa longueur (len) */
        /* En Sortie : le nom officiel de la machine locale          */
        /* ATTENTION : utilisation d'une variable statique           */
        /*            ==> Appel a proteger avec un mutex             */
        /*                si plusieurs threads...                    */
        /*-----------------------------------------------------------*/
extern void getLocalHostName(char *localHostName, size_t len);

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
extern struct in_addr getHostId(void);   /* Attention pas gethostid */

/*--------------------------------------------------------------------*/
#define MAX_BROADCAST_ADDR 1024
struct _broadcastAdresses {
                           long adrTab[MAX_BROADCAST_ADDR];
                           int  nbAdr;
};
 
typedef struct _broadcastAdresses BroadcastAdresses;

extern void getAllBbroadcastAdresses(int sock, BroadcastAdresses *ba);
/*--------------------------------------------------------------------*/

#endif  /* ADDRESSUTIL_H */
