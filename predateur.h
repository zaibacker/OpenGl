//proie.h : José

#ifndef PREDATEUR_H
#define PREDATEUR_H

#include "faune.h"

#define RAD_P	0.3		//grosseur proie
#define RAYON  1.0 		//rayon a partir duquel une proie est mangé

class Predateur : public Faune{
private:
int _nbmanger;
protected:
public:
virtual void display(int who);
Predateur(char *name, float x, float z, float y);
void deplacer(float x, float z, float y);
float getx();
float getz();
int manger();
};

#endif
