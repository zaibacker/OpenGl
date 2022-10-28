//terrain.h : Franck

#ifndef TERRAIN_H
#define TERRAIN_H

#define MAP_RES_MAX 512

#include "wrapperopengl.h"

class Terrain{
private:
char *imgFile;
char *_sol;
char *_cote;
TGAFILE image, _texsol, _texcote;
GLuint texture, texture2;
float mapSize;
int mapRes;
float terrain[MAP_RES_MAX][MAP_RES_MAX][3];
float vertScale;
int LoadTGAFile(char *filename, TGAFILE *tgaFile);
void initializeTerrain();
float height(int i, int j, int index);
void affcotesable1();
void affcotesable2();
void affcotesable3();
void affcotesable4();
void affcoteciel1();
void affcoteciel2();
void affcoteciel3();
void affcoteciel4();
void affciel();
protected:
public:
Terrain(void);
void display(void);
void init(void);
void charge(char *carte, char *sol, char *cote);
float hauteur(float x, float y);
float taille();
float precision();
};

#endif
