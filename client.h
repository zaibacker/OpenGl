#ifndef CLIENT_H
#define CLIENT_H

#include "reseau.h"
#define SEND 5
class Client:public Reseau{
private:

	int                sockService, ok;
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
	Client(char * hostname);
	void connexion(World * world);
	void run(void);
	void ReceiveTCP(struct global *globalData);
	void SendTCP(char *phrase, struct global *globalData);
};

#endif
 
