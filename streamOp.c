/*  streamOp.c  -  sockets  -  ENIB  -  LI2  -  01/05/2002 */

#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "restartOp.h"
#include "creerSocket.h"
#include "streamOp.h"

/*******************************************************************/
/*     Quelques operations de lecture/ecriture sur socket          */
/*                     en mode connecte                            */
/*******************************************************************/

int connectToServer(char serverHost[],unsigned short serverPort)
{
 struct hostent*    hp;
 struct in_addr adrHost;
 int    sock;
 
 
 /***************************************/
  /* Preparation de l'adresse du serveur */
  /***************************************/
 
  hp = gethostbyname(serverHost);
 
  if (hp == NULL) { perror("gethostbyname"); return -1; }

  adrHost = *((struct in_addr *) (hp -> h_addr_list[0]));

   /* et Aussi ...
 
     adrHost.s_addr = *((u_int32_t*) (hp -> h_addr_list[0]));

     ou bien encore ...
 
     memcpy(&adrHost, hp -> h_addr, hp -> h_length);
     adrHost.s_addr = ((struct in_addr*)(hp -> h_addr))->s_addr;
 
  */

  sock = connectToServer2(adrHost,serverPort);
 
 return sock;
}

int connectToServer2(struct in_addr adrHost, unsigned short serverPort)
{
 int                sock, ok;

 unsigned short     port;

 struct sockaddr_in adr;
 socklen_t          lgradr;

  port = 0;
  sock = creerSocket(&port, SOCK_STREAM);

  /***************************************/
  /* Preparation de l'adresse du serveur */
  /***************************************/

  lgradr = sizeof(struct sockaddr_in);
  memset(&adr, 0, lgradr);
  adr.sin_family = AF_INET;
  adr.sin_port = htons (serverPort);

  adr.sin_addr = adrHost;

  ok = connect_rs(sock, (struct sockaddr*)&adr, lgradr);
  if (ok == -1) { perror("connect"); return -1; }

 return sock;

}

/*------------------------------------------------------------------*/
/*                           writeFully                             */
/*------------------------------------------------------------------*/
ssize_t writeFully(int sockfd, const void *buf, size_t count)
{
 unsigned char* bufc = (unsigned char*)buf;

 ssize_t returnValue    = 0;

  size_t  nbByteToWrite = count;
  size_t  nbByteSent    = 0;

 while (nbByteToWrite!=nbByteSent)
 {
  returnValue = write_rs(sockfd, bufc+nbByteSent,
                                 nbByteToWrite-nbByteSent);

  if (returnValue==-1 || returnValue==0) return returnValue;

  nbByteSent += returnValue;
 }

 return nbByteSent;
}
/*------------------------------------------------------------------*/
/*                           readFully                              */
/*------------------------------------------------------------------*/
ssize_t readFully(int sockfd, void* buf, size_t count)
{
 ssize_t  returnValue   = 0;

  size_t  nbByteToRead  = count;
  size_t  nbByteArrived = 0;

 unsigned char* bufc = (unsigned char*)buf;

 while (nbByteToRead!=nbByteArrived)
 {
  returnValue = read_rs(sockfd,bufc+nbByteArrived,
                               nbByteToRead-nbByteArrived);

  if (returnValue==-1 || returnValue==0) return returnValue;

  nbByteArrived += returnValue;
 }
 return nbByteArrived;
}

/*------------------------------------------------------------------*/
/*                           writeLong                              */
/*------------------------------------------------------------------*/
ssize_t writeLong(int sockfd,const long *l)
{
 long    lToWrite = htonl(*l);

 return writeFully(sockfd,&lToWrite,sizeof(long));
}
/*------------------------------------------------------------------*/
/*                           readLong                               */
/*------------------------------------------------------------------*/
ssize_t readLong(int sockfd, long *l)
{
 long    lToRead = 0;

 ssize_t returnValue  = readFully(sockfd,&lToRead,sizeof(long));

 if (returnValue!=-1 && returnValue!=0) *l=ntohl(lToRead);

 return returnValue;
}

/*------------------------------------------------------------------*/
/*                           writeShort                             */
/*------------------------------------------------------------------*/
ssize_t writeShort(int sockfd,const short *s)
{
 short   sToWrite = htons(*s);

 return writeFully(sockfd,&sToWrite,sizeof(short));
}
/*------------------------------------------------------------------*/
/*                           readShort                              */
/*------------------------------------------------------------------*/
ssize_t readShort(int sockfd, short *s)
{
 long    sToRead = 0;

 ssize_t returnValue  = readFully(sockfd,&sToRead,sizeof(short));

 if (returnValue!=-1 && returnValue!=0) *s=ntohs(sToRead);

 return returnValue;
}

/*------------------------------------------------------------------*/
/*                          writeString                             */
/*------------------------------------------------------------------*/
ssize_t writeString(int sockfd, char str[])
{
 long  nbBytes = strlen(str)+1;                    /* +1 => '\0' */
 
 int returnValue = writeLong(sockfd,&nbBytes);
 
 if (returnValue==-1 || returnValue==0) return returnValue;
 
 return writeFully(sockfd,str,nbBytes);
}
/*------------------------------------------------------------------*/
/*                          readString                              */
/*------------------------------------------------------------------*/
ssize_t readString(int sockfd, char str[], size_t len)
{
 long  nbBytes;
 int   returnValue = readLong(sockfd,&nbBytes);
 
 if ((returnValue==-1) || (returnValue==0)) return returnValue;
 
 if (len>=(size_t)nbBytes) return readFully(sockfd,str,(size_t)nbBytes);
 else { /* Pb de taille .... */
        /* Il faut vider le tampon de reception .... */
 
        size_t  nbByteToRead  = nbBytes;
        size_t  nbByteArrived = 0;
        char    oneChar;
        while (nbByteToRead!=nbByteArrived)
        {
         returnValue = readFully(sockfd,&oneChar,1);
         if (returnValue==-1 || returnValue==0) return returnValue;
         nbByteArrived += returnValue;
        }
 
        return -1;
 }
}
