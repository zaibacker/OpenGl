#include "wrapperopengl.h"
#include "world.h"
#include "camera.h"
#include "reseau.h"
#include "inforeseau.h"
#include "serveur.h"
#include "client.h"
#include <iostream>

int  SCREEN_WIDTH = 640;
int  SCREEN_HEIGHT = 480;

World *world;
Camera *camera;
Reseau *reseau;

void display(void){
	world->display();
}

void redim(int l,int h){
	world->redim(l,h);
}

void idle(void){
	world->idle();
}

void init(void){
	world->init();
}

void clavier(unsigned char touche,int x,int y){
  	camera->clavier(touche,x,y);
}

void souris(int bouton, int etat,int x,int y){
  	camera->souris(bouton, etat, x, y);	
}

void sourismouv(int x,int y){
	camera->sourismouv(x,y);
}


int main(int argc, char** argv){



	// connection client/serveur

	if (argc < 2)
	{
		fprintf(stderr, "Mauvais nombre d'arguments\n");
		fprintf(stderr,"=> Utilisation : %s CLIENT/SERVEUR [machineServeur] numeroClient\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(strcmp(argv[1], "CLIENT") && strcmp(argv[1], "SERVEUR")) {
		fprintf(stderr, "premier argument = CLIENT ou SERVEUR\n");
		exit(EXIT_FAILURE);
	}

	if(!strcmp(argv[1], "CLIENT") && argc<4) {
		fprintf(stderr, "deuxieme argument = machineServeur\n");
		fprintf(stderr, "troisieme argument = numeroClient\n");
		exit(EXIT_FAILURE);
	}

	if(!strcmp(argv[1], "SERVEUR")) {
		reseau = new Serveur();
		reseau->setServeur(true);
	}
        int num;
	if(!strcmp(argv[1], "CLIENT")) {
		reseau = new Client(argv[2]);
		reseau->setServeur(false);
		
		sscanf(argv[3], "%d", &num);
	}
	

	//init les var principal
	camera = new Camera();
        world = new World(camera, reseau);
	world->charge("terrain8bits.tga","sol.tga","ciel.tga");
	camera->loadWorld(world);
	
	if(!strcmp(argv[1], "CLIENT")) {
		world->setwhoiam(num);
	}
	if(!strcmp(argv[1], "SERVEUR")) {
		world->setNbavatar(1);
		world->setwhoiam(0);
	}
	reseau->connexion(world);

	int numero[255];
	int numero2[255];

	for(int i=0; i<3; i++){
		float x = (((float)rand()/(float)RAND_MAX)-0.5)*world->taille();
		float y = (((float)rand()/(float)RAND_MAX)-0.5)*world->taille();
		numero[i]=world->creerfaune(0,"proie1",x,y);
	}
	for(int i=0; i<3; i++){
		float x = (((float)rand()/(float)RAND_MAX)-0.5)*world->taille();
		float y = (((float)rand()/(float)RAND_MAX)-0.5)*world->taille();
		numero2[i]=world->creerfaune(1,"proie1",x,y);
	}
	//application graphique
	WrapperOpenGL opengl(	argc, argv,
			GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH,
			0,0,
			100,100,
			"projet d'openGL",
			init,
			display,
			idle,
			clavier,
			souris,
			sourismouv,
			redim );
	return 0;
}
