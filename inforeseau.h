//inforeseau.h : Jean-Sébastien

#ifndef INFORESEAU_H
#define INFORESEAU_H

#include <string.h>

#define CLIENT 0
#define SERVEUR 1

class InfoReseau{
private:
	int _typereseau; 	// 0:Client;
				// 1:serveur;
	unsigned short _port;	// numero de port
	char *_hostname;	// nom du service
protected:
public:
	inline int gettypereseau(){return _typereseau;}
	inline unsigned short getport(){return _port;}
	inline char * gethostname(){return _hostname;}
	void charge();
};

#endif
