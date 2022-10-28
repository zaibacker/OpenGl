//objet.h : José

#ifndef FAUNE_H
#define FAUNE_H

#include "color.h"

#define PROIE 0
#define PREDATEUR 1
#define AVATAR 2

class Faune{
private:
protected:
float posX, posY, posZ;
double rad;
int slice, stack;
char *_name;
Color *color;
public:
virtual void display(int who);
virtual void deplacer( float x, float z, float y);
virtual void detruire();
virtual float getx();
virtual float getz();
virtual int manger();
};

#endif
