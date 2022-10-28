//world.h : Franck

#ifndef WORLD_H
#define WORLD_H

#include "camera.h"
#include "terrain.h"
#include "faune.h"
#include "light.h"
#include "proie.h"
#include "predateur.h"
#include "avatar.h"
#include "reseau.h"
#define MAX 256
#define SPEED	200		//vitesse des spheres

class Camera;
class Reseau;
class World{
private:
protected:
public:
Camera *_cameraW;
World(Camera *cam, Reseau *reseau);
void display(void);
void charge(char *carte, char* sol, char *cote);
float hauteur(float x, float y);
float taille();
void init(void);
int creerfaune(int type, char *name, float x, float y);
void deplacer( int type, int numero, float x, float z);
void detruirefaune(int type, int numero);
void redim(int l,int h);
void idle(void);
void manger();
void setwhoiam(int num){_whoiam = num;}
int getwhoiam(){return _whoiam;}
int setNbavatar(int nb){_nbavatar = nb;}
Light *light;
Terrain *_terrain;
Reseau *_reseau;
Faune *_faune[3][MAX];
int _nbproie,  _nbpredateur, _nbavatar, _whoiam;
};

#endif
