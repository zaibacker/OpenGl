//proie.cpp : José

#include "predateur.h"
#include "wrapperopengl.h"
#include "string.h"
#include <iostream>

void
Predateur::display(int who){
		glEnable(GL_LIGHTING) ;
		glMaterialfv(GL_FRONT,GL_DIFFUSE,color->rouge);
		glTranslatef(posX,posY+rad,posZ);
		glutSolidSphere(rad, slice, stack);
		glTranslatef(-posX,-posY-rad,-posZ);
		glDisable(GL_LIGHTING) ;
}

Predateur::Predateur(char *name, float x, float z, float y){
	color = new Color();
	_name= name;
	posX=x;
	posY=y;
	posZ=z;
	rad=RAD_P;
	slice=10;
	stack=10;
	_nbmanger=0;
}

void
Predateur::deplacer(float x, float z, float y){
		posX=x;
		posY=y;
		posZ=z;
}

float
Predateur::getx(){
	return posX;
}

float
Predateur::getz(){
	return posZ;
}

int
Predateur::manger(){
	_nbmanger++;
	rad=RAD_P+_nbmanger*RAYON;
}

