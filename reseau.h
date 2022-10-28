//reseau.h : Jean-Sébastien

#ifndef RESEAU_H
#define RESEAU_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "restartOp.h"
#include "world.h"


#include <stdlib.h>
#include <stdarg.h>
#include <sys/time.h>
#define DEPLACE 0
#define CREE 1
#define DETRUI 2

#define   PORT_BROADCAST    4700

#define   DELTA_BROADCAST   10  // En seconde pour simplifier

#define   PORT_TCP  0000

#define   MAXCONNECT        100
#define   MAXACCEPT         100

#include "creerSocket.h"
#include "restartOp.h"
#include "streamOp.h"
#include "addressUtil.h"
#include "dialogue.h"



#define SIZE 255
#define   PORT_SERVEUR  2777

class World;

class Reseau{
private:
protected:
	/*int testGET(char* str);
	void recupName(char* str,char*strRes);
	void eliminer_zombie(int signum);
	void initSignalAction(int signum, void(*fct)(int));
	int creerSocket(unsigned short *port, int type);*/
	unsigned short _port;
  	struct sockaddr_in _adr ;
  	socklen_t _lgradr ;
	FILE* _sockfile;
	bool serveur;
	World *w1;
public:
	bool getServeur() {return serveur;}
	void setServeur(bool serv) {serveur=serv;}
	ssize_t writeLong(int sockfd,const long *l);
	ssize_t readLong(int sockfd, long *l);
	ssize_t readFully(int sockfd, char *buf, size_t count);
	ssize_t writeFully(int sockfd, const char *buf, size_t count);
	ssize_t readString(int sockfd, char *str, size_t len);
	ssize_t writeString(int sockfd, char *str);
	virtual void connexion(World * world)=0;
	virtual void run(void)=0;
};

void removeSession(int index, struct global *globalData);
void InitServeurTCP(struct global *globalData);
void AcceptConnectionTCP(struct global *globalData);
int storeAccept(int socket, struct global *globalData);
void removeAccept(int index, struct global *globalData);


struct infoSession {
  unsigned short  portTCP;    // format : ordre reseau
  struct in_addr  addr;       // format : ordre reseau
  char   user[SIZE];
  char   machine[SIZE];
};

struct connectInfo {
       int    socket;
       struct infoSession remoteSession;
};

struct acceptInfo {
       int socket;
};

struct global {
  unsigned short  portTCP;    // Le port TCP
  unsigned short  portUDP;    // Le port UDP broadcast
    
  struct infoSession localInfo;
                                                // Tableau pour stocker  
  struct connectInfo tabSessions[MAXCONNECT];   // les sessions pour      
  int                nbSessions;                // lesquelles on a fait   
                                                // un connect             
                                                // => Lecture             

  struct acceptInfo  tabAccepts[MAXACCEPT];     // Tableau pour stocker 
  int                nbAccepts;                 // les sockets issues de  
                                                // accept => Ecriture  

  int socketTCP;              // Pour le server TCP (socket d'ecoute)    
  int socketUDP;              // Pour le server UDP (socket broadcast UDP)
};  
#endif

