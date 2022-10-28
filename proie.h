//proie.h : José

#ifndef PROIE_H
#define PROIE_H

#include "faune.h"

#define RAD_E	0.3		//grosseur proie

class Proie : public Faune{
private:
int etat;
protected:
public:
virtual void display(int who);
Proie(char *name, float x, float z, float y);
void deplacer(float x, float z, float y);
void detruire();
float getx();
float getz();
int manger();
};

#endif
