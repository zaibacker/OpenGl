//terrain.cpp : Franck

#include "terrain.h"
#include "wrapperopengl.h"
#include <iostream>

Terrain::Terrain(){
	mapSize = 100.0;
	vertScale= 3;
	 mapRes=500;
}

float 
Terrain::hauteur(float x, float y){
        int posX1, posX2, posY1, posY2;
	float h=0;
 	for(int i=0 ; i< mapRes;i++)
		if(terrain[i][0][0] < y) posX1 = i;
	posX2 = posX1 +1;
	for(int i=0 ; i< mapRes;i++)
		if(terrain[0][i][1] < x) posY1 = i;
	posY2 = posY1 +1;
        h = (terrain[posX1][posY1][2] + terrain[posX1][posY2][2] + terrain[posX2][posY2][2] + terrain[posX2][posY1][2])/4;
	return h;
}
float 
Terrain::taille(){
	return mapSize;
}

void 
Terrain::affcotesable1(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(-ext,-3*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(-ext,2*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,0,1);
	WrapperOpenGL::glVertex(-ext,-3*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,1,1);
	WrapperOpenGL::glVertex(-ext,2*vertScale,ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void 
Terrain::affcotesable2(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,-3*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(ext,2*vertScale,-ext);
	WrapperOpenGL::glTexCoord(1,0,0);
	WrapperOpenGL::glVertex(-ext,-3*vertScale,-ext);
	WrapperOpenGL::glTexCoord(1,1,0);
	WrapperOpenGL::glVertex(-ext,2*vertScale,-ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void 
Terrain::affcotesable3(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,-3*vertScale,ext);
	WrapperOpenGL::glTexCoord(1,0,0);
	WrapperOpenGL::glVertex(-ext,-3*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,-3*vertScale,ext);
	WrapperOpenGL::glTexCoord(1,1,0);
	WrapperOpenGL::glVertex(-ext,2*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(ext,2*vertScale,ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void 
Terrain::affcotesable4(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,-3*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(ext,2*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,0,1);
	WrapperOpenGL::glVertex(ext,-3*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,1,1);
	WrapperOpenGL::glVertex(ext,2*vertScale,-ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void 
Terrain::affcoteciel1(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture2);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(-ext,2*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(-ext,6*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,0,1);
	WrapperOpenGL::glVertex(-ext,2*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,1,1);
	WrapperOpenGL::glVertex(-ext,6*vertScale,ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void 
Terrain::affcoteciel2(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture2);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,2*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(ext,6*vertScale,-ext);
	WrapperOpenGL::glTexCoord(1,0,0);
	WrapperOpenGL::glVertex(-ext,2*vertScale,-ext);
	WrapperOpenGL::glTexCoord(1,1,0);
	WrapperOpenGL::glVertex(-ext,6*vertScale,-ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void 
Terrain::affcoteciel3(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture2);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,2*vertScale,ext);
	WrapperOpenGL::glTexCoord(1,0,0);
	WrapperOpenGL::glVertex(-ext,2*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,2*vertScale,ext);
	WrapperOpenGL::glTexCoord(1,1,0);
	WrapperOpenGL::glVertex(-ext,6*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(ext,6*vertScale,ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void 
Terrain::affcoteciel4(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture2);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(0,0,0);
	WrapperOpenGL::glVertex(ext,2*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,1,0);
	WrapperOpenGL::glVertex(ext,6*vertScale,ext);
	WrapperOpenGL::glTexCoord(0,0,1);
	WrapperOpenGL::glVertex(ext,2*vertScale,-ext);
	WrapperOpenGL::glTexCoord(0,1,1);
	WrapperOpenGL::glVertex(ext,6*vertScale,-ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void 
Terrain::affciel(){
	glTranslatef(0.0,6*vertScale,0.0);
	glRotatef(180,1.0,0.0,0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture2);
	float ext = (mapSize/2);
	glBegin(GL_TRIANGLE_STRIP);
	WrapperOpenGL::glTexCoord(1.0,0.0,1.0);
	WrapperOpenGL::glVertex(ext,0.0,ext);
	WrapperOpenGL::glTexCoord(1.0,0.0,0.0);
	WrapperOpenGL::glVertex(ext,0.0,-ext);
	WrapperOpenGL::glTexCoord(0.0,0.0,1);
	WrapperOpenGL::glVertex(-ext,0.0,ext);
	WrapperOpenGL::glTexCoord(0.0,0.0,0.0);
	WrapperOpenGL::glVertex(-ext,0.0,-ext);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glRotatef(-180,1.0,0.0,0.0);
	glTranslatef(0.0,-6*vertScale,0.0);
}


void
Terrain::display(){
//affiche le terrain en utilissant les methode du wrapper openGL
	
	//glEnable(GL_LIGHTING);
	//glEnable(GL_DEPTH_TEST);
	

	affcotesable1();
        affcotesable2();
	affcotesable3();
	affcotesable4();

	affcoteciel1();
	affcoteciel2();
	affcoteciel3();
	affcoteciel4();

	affciel();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	
	//WrapperOpenGL::glColor(1.0,0.0,0.0);
	//affiche le sol
	for (int i = 0; i < mapRes-1; i++)
    		{
      		for (int j = 0; j < mapRes-1; j++)
			{
			glBegin(GL_TRIANGLE_STRIP);
			WrapperOpenGL::glTexCoord((terrain[i][j][0]-mapSize/2)/mapSize,
						(terrain[i][j][2]-mapSize/2)/mapSize,
						(terrain[i][j][1]-mapSize/2)/mapSize);
			WrapperOpenGL::glVertex(terrain[i][j][1],
						terrain[i][j][2],
						terrain[i][j][0]);
			WrapperOpenGL::glVertex(terrain[i+1][j][1],
						terrain[i+1][j][2],
						terrain[i+1][j][0]);
			WrapperOpenGL::glVertex(terrain[i][j+1][1],
						terrain[i][j+1][2],
						terrain[i][j+1][0]);
			WrapperOpenGL::glVertex(terrain[i+1][j+1][1],
						terrain[i+1][j+1][2],
						terrain[i+1][j+1][0]);
			glEnd();
		}
			
    	}
	glDisable(GL_TEXTURE_2D);
	float ext = (mapSize/2);


	//glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
}

void
Terrain::charge(char * carte, char *sol, char *cote){
	imgFile=carte;
	_sol=sol;
	_cote=cote;
	if (LoadTGAFile(imgFile, &image) != 1) {
		printf("erreur lors du chargement de l'image TGA\n");
		exit(-1);
	}
	initializeTerrain();
}



/* Fonction lisant un fichier TGA 8, 16, 24 ou 32 bits et remplissant la structure
 * TGAFILE pass� en param�re
 */
int 
Terrain::LoadTGAFile(char *filename, TGAFILE *tgaFile) 
{
	FILE *filePtr;			// pointeur sur le fichier
	unsigned char ucharBad;		// poubelle pour les unsigned char
	short int sintBad;		// poubelle pour les short int
	int colorMode;			// 4 pour RGBA ou 3 pour RGB
	long imageSize;			// taille de l'image TGA
	long imageIdx;			// compteur
	unsigned char colorSwap;	// variable d'�hange
	unsigned short pixels = 0;	// un pixel d'une image 16 bits
	int r, g, b;			// composantes RGB
	
	// ouverture du fichier TGA
	if (!(filePtr = fopen (filename, "rb"))) {
		//fclose(filePtr);
        	return TGA_FILE_NOT_FOUND;
	}
	
	// lecture des 2 premiers champs dont on n'a pas besoin
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	
	// lecture du type de l'image/*
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	if ((ucharBad != 2) && (ucharBad != 3)) {
		fclose(filePtr);
		return TGA_BAD_IMAGE_TYPE;
	}
	// lecture des 5 champs suivants dont on n'a pas besoin
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	
	// lecture des dimensions de l'image
	fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
	fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);
	fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);
	
	// lecture du dernier champ dont on n'a pas besoin
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	
	// on ne lit que les images 24 ou 32 bits
	if (tgaFile->bitCount != 32 && tgaFile->bitCount != 24 && tgaFile->bitCount != 8 && tgaFile->bitCount != 16) {
		fclose(filePtr);
		return TGA_BAD_BITS;
	}
	
	// image 8, 24 ou 32 bits
	if(tgaFile->bitCount == 24 || tgaFile->bitCount == 32 || tgaFile->bitCount == 8)
	{
		// colorMode -> 3 = BGR, 4 = BGRA
		colorMode = tgaFile->bitCount / 8;
		imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;
	
		// allocation de la m�oire pour les donn�s de l'image
		tgaFile->imageData = (unsigned char*) malloc(sizeof(unsigned char) * imageSize);
	
		// lecture des donn�s de l'image
		fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);
		if (tgaFile->imageData == NULL) {
        		fclose(filePtr);
			return TGA_BAD_DATA;
		}
	
		// dans les images TGA les couleurs des pixels sont en mode BGR
		// transformation en mode RGB
		if (tgaFile->bitCount != 8)
		for (imageIdx=0; imageIdx < imageSize; imageIdx += colorMode)
		{
			colorSwap = tgaFile->imageData[imageIdx];
			tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
			tgaFile->imageData[imageIdx + 2] = colorSwap;
		}
	}
	else { // image 16 bits

		colorMode = 3;	// mode RGB
		imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;
		
		// allocation de la m�oire pour les donn�s de l'image
		tgaFile->imageData = (unsigned char*) malloc(sizeof(unsigned char) * imageSize);
		
		// en 16 bits chaque pixel est contenu dans un "unsigned short"
		// boucle sur tous les pixels de l'image
		for (imageIdx = 0; imageIdx < tgaFile->imageWidth*tgaFile->imageHeight; imageIdx++)
		{
			// lecture du pixel courant
			fread(&pixels, sizeof(unsigned short), 1, filePtr);
				
			// pour convertir 16 bits en composantes RGB
			// chaque composante occupe 5 bits
			// ex: pixels = 0x61E8 = 0110000111101000
			// on utilise un masque 0x1F = 11111
			// 0110000111101000 & 11111 = 01000
			// on effectue un d�allage de 3 bits pour avoir un nombre sur 8 bits
			// 01000 << 3 = 01000000 = 0x40 = 64 --> composante bleu
			// on d�ale ensuite de 5 bits pour arriver �la prochaine
			// composante et on r�t�e la m�e op�ation
			// 0110000111101000 >> 5 = 0000001100001111
			// 0000001100001111 & 11111 = 01111
			// 01111 << 3 = 01111000 = 0x78 = 120 --> composante vert
			// ...etc...
			b = (pixels & 0x1f) << 3;
			g = ((pixels >> 5) & 0x1f) << 3;
			r = ((pixels >> 10) & 0x1f) << 3;
				
			// on assigne ensuite les composantes au tableau de donn�s
			tgaFile->imageData[imageIdx * 3 + 0] = r;
			tgaFile->imageData[imageIdx * 3 + 1] = g;
			tgaFile->imageData[imageIdx * 3 + 2] = b;
		}
	}
	
	// fermeture du fichier
	fclose(filePtr);
	
	// Format de l'image RGB, RGBA ou niveau de gris
	switch (tgaFile->bitCount) {
		case 8: tgaFile->texFormat = GL_LUMINANCE; break;
		case 32: tgaFile->texFormat = GL_RGBA; break;
		default: tgaFile->texFormat = GL_RGB;
	}
	
	return 1;
}



void 
Terrain::initializeTerrain(){
  int i,j;
  float pas = mapSize/mapRes;
  // on calcule les coordonn�s de chaque point du maillage
  for (i = 0; i < mapRes; i++)
    {
      for (j = 0; j < mapRes; j++)
	{
	  terrain[i][j][0] = -(mapSize/2)+i*pas;
	  terrain[i][j][1] = -(mapSize/2)+j*pas;
	  terrain[i][j][2] =  (height(i, j, 0)+height(i, j, 1)+height(i, j, 2))/3*vertScale;
	}
    }
}


float 
Terrain::height(int i, int j, int index){
  int valeur;
  int colorMode = image.bitCount / 8;
  if (colorMode == 2) colorMode = 3;
  valeur =image.imageData[((((int)((float)i/mapRes*(image.imageWidth-1)))*image.imageWidth) + ((int)((float)j/mapRes*(image.imageHeight-1)))) * colorMode+index];
  return (float)valeur/255.0;	
}



void
Terrain::init(){
	
	//charge texture
	
	if (LoadTGAFile(_sol, &_texsol) != 1) {
		printf("erreur lors du chargement de l'image TGA\n");
		exit(-1);
	}
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,_texsol.imageWidth,_texsol.imageHeight,0,_texsol.texFormat,GL_UNSIGNED_BYTE,_texsol.imageData);

	if (LoadTGAFile(_cote, &_texcote) != 1) {
		printf("erreur lors du chargement de l'image TGA\n");
		exit(-1);
	}
	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D,texture2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,_texcote.imageWidth,_texcote.imageHeight,0,_texcote.texFormat,GL_UNSIGNED_BYTE,_texcote.imageData);

//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image.imageWidth,image.imageHeight,0,image.texFormat,GL_UNSIGNED_BYTE,image.imageData);

}

