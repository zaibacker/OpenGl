//proie.h : José

#ifndef AVATAR_H
#define AVATAR_H

#include "faune.h"

#define RAD_A	0.6		//grosseur avatar

class Avatar : public Faune{
private:
protected:
public:
virtual void display(int who);
Avatar(char *name, float x, float z, float y);
void deplacer(float x, float z, float y);
float getx();
float getz();
};

#endif
