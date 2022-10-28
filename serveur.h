//serveur.h : Jean-Sébastien

#ifndef SERVEUR_H
#define SERVEUR_H

#include "reseau.h"
#define SEND 1



class Serveur:public Reseau{
private:
	int sockService, sockEcoute, ok;
	struct hostent*    hp ;
	struct sockaddr_in adr ;
	socklen_t          lgradr ;
	char   reponse1[SIZE];
	char   reponse2[SIZE];
	char * _hostname;
 	struct global globalData;
	int timerSend;
protected:
public:
	Serveur();
	void connexion(World * world);
	void run(void);
	void ReceiveAllTCP(fd_set *rdFds, struct global *globalData);
	void SendAllTCP(char *phrase, struct global *globalData);
	void AcceptConnectionTCP(struct global *globalData);
};

#endif
