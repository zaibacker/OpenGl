#include "wrapperopengl.h"
#include <iostream>


WrapperOpenGL::WrapperOpenGL(	int argc, char **argv,
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
	    		void (*reshape)(int, int)){
	
	if (width != (int)0) SCREEN_WIDTH= width;
	if (height != (int)0) SCREEN_HEIGHT= height;
	glutInit(&argc, argv);
	glutInitDisplayMode(mode);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(x, y);
	glutCreateWindow(title);
	
	init();
	
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();
}
/*
void
WrapperOpenGL::init(){
	
}
*/
