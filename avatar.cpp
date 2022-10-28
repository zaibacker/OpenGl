//proie.cpp : José

#include "avatar.h"
#include "wrapperopengl.h"
#include "string.h"
#include <iostream>
void
Avatar::display(int who){
		glEnable(GL_LIGHTING) ;
		switch(who){
			case 0 : glMaterialfv(GL_FRONT,GL_DIFFUSE,color->vert);
			break;
			case 1 : glMaterialfv(GL_FRONT,GL_DIFFUSE,color->col1);
			break;
			case 2 : glMaterialfv(GL_FRONT,GL_DIFFUSE,color->col2);
			break;
			case 3 : glMaterialfv(GL_FRONT,GL_DIFFUSE,color->col3);
			break;
			default : glMaterialfv(GL_FRONT,GL_DIFFUSE,color->col4);
		}
		glTranslatef(posX,posY+rad,posZ);
		glutSolidSphere(rad, slice, stack);
		glTranslatef(-posX,-posY-rad,-posZ);
		glDisable(GL_LIGHTING) ;
}

Avatar::Avatar(char *name, float x, float z, float y){
	color = new Color();
	_name= name;
	posX=x;
	posY=y;
	posZ=z;
	rad=RAD_A;
	slice=10;
	stack=10;
}

void
Avatar::deplacer(float x, float z, float y){
		posX=x;
		posY=y;
		posZ=z;
}

float
Avatar::getx(){
	return posX;
}

float
Avatar::getz(){
	return posZ;
}


