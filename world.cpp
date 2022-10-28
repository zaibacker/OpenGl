//world.cpp : Franck

#include "wrapperopengl.h"
#include "world.h"
#include "terrain.h"
#include <string.h>
#include <iostream>


World::World(Camera *cam, Reseau *reseau){
	_terrain = new Terrain();
	_cameraW = cam;
	_reseau=reseau;
	_nbproie = 0;
	_nbpredateur=0;
	_nbavatar = 0;
	light = new Light();
}

void
World::display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_cameraW->Update();
	_cameraW->Look();
	glEnable(GL_LIGHT0);
	/*for(int i=0;i<MAX;i++){	
	 if(_faune[AVATAR][i]!=NULL){
	     printf(">world::display() : faune %d ,%d\n",i, _faune[AVATAR][i]);
	 }
	}*/
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light->pos2) ;
	_terrain->display();
	for(int i=0;i<_nbproie;i++)
		_faune[PROIE][i]->display(0);
	for(int i=0;i<_nbpredateur;i++)
		_faune[PREDATEUR][i]->display(0);
	for(int i=0;i<MAX;i++)
		if( i != _whoiam && _faune[AVATAR][i] != NULL){_faune[AVATAR][i]->display(i);}
	glFlush();
	glutSwapBuffers();
	glDisable(GL_LIGHT0);
}

void 
World::charge(char *carte, char *sol, char *cote){
	_terrain->charge(carte, sol, cote);
}

int 
World::creerfaune(int type, char *name, float x, float z){
	int numero;
	switch(type){
		case PROIE : 
			_faune[PROIE][_nbproie]=new Proie(name, x, z,hauteur(x,z));
			numero = _nbproie;
			_nbproie++;
			break;
		case PREDATEUR : 
			_faune[PREDATEUR][_nbpredateur]=new Predateur(name, x, z,hauteur(x,z));
			numero = _nbpredateur;
			_nbpredateur++;
			break;
		case AVATAR : 
			int num;
			sscanf(name,"%d",&num);
			_faune[AVATAR][num]=new Avatar(name, x, z,hauteur(x,z));
			numero = _nbavatar;
			_nbavatar++;
			break;
	}
	return numero;
}


void 
World::deplacer(int type,int numero, float x, float z){
	switch(type){
		case PROIE :
			_faune[type][numero]->deplacer( x, z,hauteur(x,z));
			break;
		case PREDATEUR : 
			_faune[type][numero]->deplacer( x, z,hauteur(x,z));
			break;
		case AVATAR : 
			char nom[2];
			sprintf(nom,"%d\0",numero);
			printf(">deplacer() avatar num : %d  , nom : %s, nbAvatar :%d\n",numero,nom,_nbavatar);
			if(_faune[type][numero] == NULL) {printf(">deplacer() if\n");creerfaune(type, nom,  x,  z);}
			else {printf(">deplacer() not if numero: %d %d\n",numero,_faune[type][numero]);_faune[type][numero]->deplacer( x, z,hauteur(x,z));}
			break;
	}
	//_faune[type][numero]->deplacer( x, z,hauteur(x,z));
}

void 
World::detruirefaune(int type, int numero){
	_faune[type][numero]->detruire();
}


void 
World::redim(int l,int h){
  	if (h==0) h=l; 
	glViewport(0,0,(GLsizei)l,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(GLfloat)l/(GLfloat)h,0.01f, 20000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void 
World::init(){
  	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT,GL_FILL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPolygonMode(GL_FRONT, GL_FILL);

	//glEnable(GL_COLOR_MATERIAL);
   	glEnable(GL_CULL_FACE);
 	glEnable(GL_DEPTH_TEST);
	
	
	

	_terrain->init();

    
}

float 
World::hauteur(float x, float y){
	return _terrain->hauteur(x,y);
}

float 
World::taille(){
	return _terrain->taille();
}

void
World::idle(void){	
	//free(mes1);
	_reseau->run();
	glutPostRedisplay();
}

void
World::manger(){
	for(int i=0; i < _nbpredateur; i++){
		for(int j=0; j < _nbproie; j++){
			if( _faune[PROIE][j]->manger()==0){
				float x=_faune[PROIE][j]->getx()-_faune[PREDATEUR][i]->getx();
				if((x>-0.8)&&(x<0.8)){
					float z=_faune[PROIE][j]->getz()-_faune[PREDATEUR][i]->getz();
					if((z>-0.8)&&(z<0.9)){
						_faune[PROIE][j]->detruire();
						
					}
				}
			} 
		} 
	}

}

