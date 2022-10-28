//inforeseau.cpp : Jean-Sébastien

#include "inforeseau.h"

void
InfoReseau::charge(){
	_typereseau = SERVEUR;
	_port = 4000;
	strcpy(_hostname, "192.168.7.26");
}
