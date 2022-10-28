//wrapperopengl.h

#ifndef WRAPPEROPENGL_H
#define WRAPPEROPENGL_H

extern int  SCREEN_WIDTH;
extern int  SCREEN_HEIGHT;

#define	WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define TITLE "le monde de de nemo"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class WrapperOpenGL{
private:
protected:
public:
WrapperOpenGL(int argc, char **argv,
	    int mode, 
            int width, int height, 
	    int x, int y,
	    char* title,
	    void (*init)(void), 
	    void (*display)(void),
	    void (*idle)(void),
	    void (*key)(unsigned char, int, int),
	    void (*mouse)(int, int, int, int),
	    void (*motion)(int, int),
	    void (*reshape)(int, int));
//glvertex
static void glVertex(GLdouble x,GLdouble y){glVertex2d(x, y );}
static void glVertex(GLfloat x,GLfloat y){glVertex2f(x, y );}
static void glVertex(GLint x, GLint y){glVertex2i(x, y );}
static void glVertex(GLshort x,GLshort y){glVertex2s(x, y );}
static void glVertex(GLfloat x,GLfloat y,GLfloat z ){glVertex3f(x, y, z );}
//static void glVertex(GLdouble x,GLdouble y,GLdouble z){glVertex3d(x, y, z );}  
static void glVertex(GLint x, GLint y,GLint z ){glVertex3i(x, y, z );}
static void glVertex(GLshort x, GLshort y, GLshort z){glVertex3s(x, y, z );}  
static void glVertex(GLfloat x,GLfloat y,GLfloat z, GLfloat w ){glVertex4f(x, y, z, w );}
static void glVertex(GLdouble x,GLdouble y,GLdouble z, GLdouble w){glVertex4d(x, y, z, w );}  
static void glVertex(GLint x, GLint y, GLint z, GLint w ){glVertex4i(x, y, z, w );}
static void glVertex(GLshort x, GLshort y, GLshort z, GLshort w){glVertex4s(x, y, z, w );}  
//glcolor
static void glColor(GLfloat red,GLfloat green,GLfloat blue ){glColor3f(red, green, blue );}
static void glColor(GLdouble red,GLdouble green,GLdouble blue){glColor3d(red, green, blue );}  
static void glColor(GLint red, GLint green,GLint blue ){glColor3i(red, green, blue );}
static void glColor(GLshort red, GLshort green, GLshort blue){glColor3s(red, green, blue );} 
static void glColor(GLbyte red,GLbyte green,GLbyte blue ){glColor3b(red, green, blue );}
static void glColor(GLubyte red,GLubyte green,GLubyte blue){glColor3ub(red, green, blue );}  
static void glColor(GLuint red, GLuint green,GLuint blue ){glColor3ui(red, green, blue );}
static void glColor(GLushort red, GLushort green, GLushort blue){glColor3us(red, green, blue );} 
static void glColor(GLfloat red,GLfloat green,GLfloat blue, GLfloat alpha ){glColor4f(red, green, blue, alpha );}
static void glColor(GLdouble red,GLdouble green,GLdouble blue, GLdouble alpha){glColor4d(red, green, blue, alpha );}  
static void glColor(GLint red, GLint green,GLint blue, GLint alpha ){glColor4i(red, green, blue, alpha );}
static void glColor(GLshort red, GLshort green, GLshort blue, GLshort alpha){glColor4s(red, green, blue, alpha );} 
static void glColor(GLbyte red,GLbyte green,GLbyte blue, GLbyte alpha ){glColor4b(red, green, blue, alpha );}
static void glColor(GLubyte red,GLubyte green,GLubyte blue,GLubyte alpha){glColor4ub(red, green, blue, alpha );}  
static void glColor(GLuint red, GLuint green,GLuint blue, GLuint alpha ){glColor4ui(red, green, blue, alpha );}
static void glColor(GLushort red, GLushort green, GLushort blue, GLushort alpha){glColor4us(red, green, blue, alpha );} 
//glTexCoord
static void glTexCoord( GLdouble s ){ glTexCoord1d( s );}
static void glTexCoord( GLfloat s ){ glTexCoord1f( s );}
static void glTexCoord( GLint s ){ glTexCoord1i( s );}
static void glTexCoord( GLshort s ){ glTexCoord1s( s );}
static void glTexCoord( GLdouble s,GLdouble t ){ glTexCoord2d( s,t );}
static void glTexCoord( GLfloat s,GLfloat t ){ glTexCoord2f( s,t );}
static void glTexCoord( GLint s,GLint t ){ glTexCoord2i( s,t );}
static void glTexCoord( GLshort s,GLshort t ){ glTexCoord2s( s,t );}
//static void glTexCoord( GLdouble s,GLdouble t,GLdouble r ){ glTexCoord3d( s,t,r );}
static void glTexCoord( GLfloat s,GLfloat t,GLfloat r ){ glTexCoord3f( s,t,r );}
/*static void glTexCoord( GLint s,GLint t,GLint r ){ glTexCoord3i( s,t,r );}
static void glTexCoord( GLshort s,GLshort t,GLshort r ){ glTexCoord3s( s,t,r );}*/
static void glTexCoord( GLdouble s,GLdouble t,GLdouble r,GLdouble q ){ glTexCoord4d( s,t,r,q );}
static void glTexCoord( GLfloat s,GLfloat t,GLfloat r,GLfloat q ){ glTexCoord4f( s,t,r,q );}
static void glTexCoord( GLint s,GLint t,GLint r,GLint q ){ glTexCoord4i( s,t,r,q );}
static void glTexCoord( GLshort s,GLshort t,GLshort r,GLshort q ){ glTexCoord4s( s,t,r,q );}




};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Codes erreurs de retour des fonctions */
#define TGA_FILE_NOT_FOUND 13
#define TGA_BAD_IMAGE_TYPE 14
#define TGA_BAD_BITS 16
#define TGA_BAD_DATA 17
#define TGA_FILE_NOT_CREATE 18
#define TGA_BAD_SIZE 19
/* class permettant de stocker une image TGA */
class TGAFILE {
public:
	GLenum texFormat;	// GL_RGB, GL_RGBA ou GL_LUMINANCE
	short int imageWidth;
	short int imageHeight;
	unsigned char bitCount;
	unsigned char *imageData;
} ;


#endif
