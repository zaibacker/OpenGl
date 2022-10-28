//proie.cpp : José

#include "proie.h"
#include "wrapperopengl.h"
#include "string.h"
#include <iostream>

void
Proie::display(int who){
	if (etat==1){
		glEnable(GL_LIGHTING) ;
		glMaterialfv(GL_FRONT,GL_DIFFUSE,color->bleu);
		glTranslatef(posX,posY+rad,posZ);
		glutSolidSphere(rad, slice, stack);
		glTranslatef(-posX,-posY-rad,-posZ);
		glDisable(GL_LIGHTING) ;
	}
}

Proie::Proie(char *name, float x, float z, float y){
	color = new Color();
	_name= name;
	posX=x;
	posY=y;
	posZ=z;
	rad=RAD_E;
	slice=10;
	stack=10;
	etat=1;
}

void
Proie::deplacer(float x, float z, float y){
	if (etat==1){
		posX=x;
		posY=y;
		posZ=z;
	}
}

void
Proie::detruire(){
	etat=0;
}

float
Proie::getx(){
	return posX;
}

float
Proie::getz(){
	return posZ;
}

int
Proie::manger(){
	if (etat ==1)return 0;
	else return 1;
} 
