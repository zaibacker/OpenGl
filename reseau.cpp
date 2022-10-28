//reseau.cpp : Jean-Sébastien

#include "reseau.h"
#include "wrapperopengl.h"

ssize_t 
Reseau::writeLong(int sockfd,const long *l){
 	long lToWrite = htonl(*l);
 	unsigned char* pt_lToWrite = (unsigned char*)&lToWrite;
 	ssize_t returnValue   = 0;
 	size_t nbByteToWrite = sizeof(long);
 	size_t nbByteSent    = 0;
 	while (nbByteToWrite!=nbByteSent){
  		returnValue = write_rs(sockfd,pt_lToWrite+nbByteSent,nbByteToWrite-nbByteSent);
  	if (returnValue==-1 || returnValue==0) return returnValue;
  	nbByteSent += returnValue;
}

 return nbByteSent;
}

ssize_t 
Reseau::readLong(int sockfd, long *l){
 	long lToRead = 0;
 	unsigned char* pt_lToRead = (unsigned char*)&lToRead;
 	ssize_t returnValue   = 0;
 	size_t  nbByteToRead  = sizeof(long);
 	size_t  nbByteArrived = 0;
 	while (nbByteToRead!=nbByteArrived){
  		returnValue =  read_rs(sockfd, pt_lToRead+nbByteArrived, nbByteToRead-nbByteArrived);
  		if (returnValue==-1 || returnValue==0) return returnValue;
  		nbByteArrived += returnValue;
 	}
	*l=ntohl(lToRead);
 	return nbByteArrived;
}

ssize_t 
Reseau::readFully(int sockfd, char *buf, size_t count){
 	ssize_t returnValue = 0;
	do{
      		returnValue = read(sockfd,buf+returnValue,count-returnValue);
 	}while ((returnValue<(ssize_t)count) && (returnValue==-1) && (errno==EINTR));
	return returnValue;
}

ssize_t 
Reseau::writeFully(int sockfd, const char *buf, size_t count){
 	ssize_t returnValue = 0;
	do{
      		returnValue = write(sockfd,buf+returnValue,count-returnValue);
 	}while ((returnValue<(ssize_t)count) && (returnValue==-1) && (errno==EINTR));
	return returnValue;
}

ssize_t 
Reseau::readString(int sockfd, char *str, size_t len){
 	ssize_t returnValue = 0;
 	long len2;
 	returnValue=readLong(sockfd,&len2);
 	if(len2>(long)len) return -1;
	returnValue=readFully(sockfd,str,len2);
 	return returnValue;
}

ssize_t 
Reseau::writeString(int sockfd, char *str){
 	ssize_t returnValue = 0;
	ssize_t len = strlen(str)+1;
 	returnValue=writeLong(sockfd,(long*)&len);
 	returnValue=writeFully(sockfd,str,len);
 	return returnValue;
}

void removeSession(int index, struct global *globalData)
{
 globalData->nbSessions--;
 if (globalData->nbSessions<0) globalData->nbSessions=0; // Cas impossible !
 globalData->tabSessions[index]=
                            globalData->tabSessions[globalData->nbSessions];
}


/**********************************************************************/
/*           Gestion du tableau des sockets issues d'un accept        */
/**********************************************************************/

int storeAccept(int socket, struct global *globalData);

void removeAccept(int index, struct global *globalData);

/*--------------------------------------------------------------------*/
          /*******************************************************/
          /* Retour de storeAccept : 0 si ok, -1 si ko           */
          /* -1 si plus de place dans le tableau tabAccepts      */
          /*******************************************************/
int storeAccept(int socket, struct global *globalData)
{
 int returnValue = 0;
 int nbElems = globalData->nbAccepts;

   if (nbElems==MAXACCEPT) {
      fprintf(stderr,
            "Plus possible de stocker une nouvelle socket:"
            " nbAccepts=MAXACCEPT\n");
      returnValue = -1;
   }
   else {
          globalData->tabAccepts[nbElems].socket=socket;
          globalData->nbAccepts++;
    }

 return returnValue;
}

          /*******************************************************/
          /* Retour de removeAccept :                            */
          /* ATTENTION : l'ï¿½ï¿½ent enlevï¿½est remplacï¿½par le    */
          /* dernier ï¿½ï¿½ent du tableau                          */
          /*******************************************************/
/*--------------------------------------------------------------------*/
void removeAccept(int index, struct global *globalData)
{
 globalData->nbAccepts--;
 if (globalData->nbAccepts<0) globalData->nbAccepts=0; // Cas impossible !
 globalData->tabAccepts[index]=globalData->tabAccepts[globalData->nbAccepts];
}


/**********************************************************************/
/*                               TCP                                  */
/**********************************************************************/

/*--------------------------------------------------------------------*/

void InitServeurTCP(struct global *globalData)
{
 globalData->portTCP = PORT_SERVEUR;
 globalData->socketTCP = creerSocket(&globalData->portTCP, SOCK_STREAM);
 if(listen(globalData->socketTCP,5) == -1){
   perror("listen");
   exit(EXIT_FAILURE);
 }
 globalData->nbSessions=0;  // Le tableau des sessions est vide
 globalData->nbAccepts=0;   // Le tableau des "accepts" est vide
}


/*--------------------------------------------------------------------*/


