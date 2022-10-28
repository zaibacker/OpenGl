//camera.cpp : Goulwen

#include "wrapperopengl.h"
#include "camera.h"
#include <iostream>
#include <math.h>
#define STRAFF_SPEED 0.2
#define MOVE_SPEED 0.3
#define ALTITUDE 2.5

//CVector3, operations de base
CVector3 Cross(CVector3 &vVector1, CVector3 &vVector2)
{
	CVector3 vNormal;									// The vector to hold the cross product

	// The X value for the vector is:  (V1.y * V2.z) - (V1.z * V2.y)													// Get the X value
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
														
	// The Y value for the vector is:  (V1.z * V2.x) - (V1.x * V2.z)
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
														
	// The Z value for the vector is:  (V1.x * V2.y) - (V1.y * V2.x)
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vNormal;										// Return the cross product (Direction the polygon is facing - Normal)
}

float Magnitude(CVector3 &vNormal)
{
	// This will give us the magnitude or "Norm" as some say, of our normal.
	// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)  Where V is the vector

	return (float)sqrt( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z) );
}

CVector3 Normalize(CVector3 &vNormal)
{
	float magnitude = Magnitude(vNormal);		// Get the magnitude of our normal

	// Now that we have the magnitude, we can divide our normal by that magnitude.
	// That will make our normal a total length of 1.  This makes it easier to work with too.

	vNormal.x /= magnitude;		// Divide the X value of our normal by it's magnitude
	vNormal.y /= magnitude;		// Divide the Y value of our normal by it's magnitude
	vNormal.z /= magnitude;		// Divide the Z value of our normal by it's magnitude

	// Finally, return our normalized normal.

	return vNormal;		// Return the new normal of length 1.
}
//fin CVector3




void
Camera::loadWorld(World * world){
	_world = world;
	_Zmax = _Xmax = (world->taille()-1)/2;
	m_vPosition.y = ALTITUDE+_world->hauteur((int)m_vPosition.x,(int)m_vPosition.z);
}

Camera::Camera(void){
	mouse.x = 0;
	mouse.y = 0;
	mouse.left_button = false;
	mouse.right_button = false;

	CVector3 vZero = CVector3(8.0, 3.0, 13.0);		// Init a vVector to 0 0 0 for our position
	CVector3 vView = CVector3(0.0, 0.0, 0.0);		// Init a starting view vVector (looking up and out the screen) 
	CVector3 vUp   = CVector3(0.0, 1.0, 0.0);		// Init a standard up vVector (Rarely ever changes)

	m_vPosition	= vZero;		// Init the position to zero
	m_vView		= vView;		// Init the view to a std starting view
	m_vUpVector	= vUp;	
}


void 
Camera::clavier(unsigned char touche,int x,int y){//,(int)m_vPosition.x,(int)m_vPosition.z);//
	float yArea;

	switch(touche) {
		case ESC:	// touche escape
			terminateApplication();
		break;

		case 'z': 
			MoveCamera(MOVE_SPEED);
			yArea = _world->hauteur((int)m_vPosition.x,(int)m_vPosition.z);
			m_vPosition.y = ALTITUDE+yArea;
		break;
	
		case 's': 
			MoveCamera(-MOVE_SPEED);
			yArea = _world->hauteur((int)m_vPosition.x,(int)m_vPosition.z);
			m_vPosition.y = ALTITUDE+yArea;
		break;
		
		case 'q': 
			StrafeCamera(-STRAFF_SPEED);
			yArea = _world->hauteur((int)m_vPosition.x,(int)m_vPosition.z);
			m_vPosition.y = ALTITUDE+yArea;

		break;

		case 'd': 
			StrafeCamera(+STRAFF_SPEED);
			yArea = _world->hauteur((int)m_vPosition.x,(int)m_vPosition.z);
			m_vPosition.y = ALTITUDE+yArea;

		break;
		
		case 'e': 
			m_vPosition.y+=0.6;
			m_vView.y+=0.6;
		break;
		
		case 'a': 
			m_vPosition.y-=0.6;
			m_vView.y-=0.6;
		break;
	  
  }
	glutPostRedisplay();
}

void 
Camera::souris(int bouton, int etat,int x,int y){
	// Gere les bouton de la souris
        if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN)
                mouse.left_button = true;

        else if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
                mouse.left_button = false;

        else if (bouton == GLUT_RIGHT_BUTTON && etat == GLUT_DOWN)
                mouse.right_button = true;

        else if (bouton == GLUT_RIGHT_BUTTON && etat == GLUT_UP)
                mouse.right_button = false;
	// Sauvegarde de la position lors de l'appui sur un bouton
	mouse.x = x;
	mouse.y = y;
	// Action lors d'un clic gauche
	if(mouse.left_button)
	{
		printf("left_button\n");
	}
	// Action lors d'un clic droit
	if(mouse.right_button)
	{
		printf("right_button\n");
	}
}

void 
Camera::sourismouv(int x,int y){
//gere le mouvement de la souris
mouseX = x;
mouseY = y;
Mouse_Move(SCREEN_WIDTH, SCREEN_HEIGHT);
//debug : glutPostRedisplay();
//debug : SetViewByMouse(x,y);
}
void 
Camera::Look()
{	
	// Defini la vue de la camera
	glLoadIdentity();
	gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z,	
			  m_vView.x,	 m_vView.y,     m_vView.z,	
			  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
	
}

void 
Camera::StrafeCamera(float speed)
{
	// Add the strafe vector to our position
	if(abs( (int )(m_vPosition.x+m_vStrafe.x * speed)) < _Xmax - 1)
	{
	 m_vPosition.x += m_vStrafe.x * speed;
         m_vView.x += m_vStrafe.x * speed;	
	}
	// Add the strafe vector to our view
	if(abs( (int )(m_vPosition.z+m_vStrafe.z * speed)) < _Xmax - 1)
	{
	 m_vPosition.z += m_vStrafe.z * speed;
         m_vView.z += m_vStrafe.z * speed;
	}
}
void 
Camera::MoveCamera(float speed)
{
	// Get the current view vector (the direction we are looking)
	CVector3 vVector = m_vView - m_vPosition;
	vVector = Normalize(vVector);
	

	if(abs( (int )(m_vPosition.x+vVector.x * speed)) < _Xmax - 1)
	{
	 m_vPosition.x += vVector.x * speed;
	 m_vView.x += vVector.x * speed;
	}
	
	if(abs( (int )(m_vPosition.z+vVector.z * speed)) < _Zmax - 1){
	   m_vPosition.z += vVector.z * speed;
           m_vView.z += vVector.z * speed;
	}
}

void 
Camera::Update(void){
	
	CVector3 res = m_vView - m_vPosition;
	CVector3 vCross = Cross(res, m_vUpVector);

	// Normalize the strafe vector
	m_vStrafe = Normalize(vCross);

}

// debug changer de place a cette fonction
void terminateApplication(void)
{
	exit(1);
}
//Gestion de la souris
// debug : Extraitde source de Dagorn

void 
Camera::Rotate_View(float speed)
{
	CVector3 vVector = m_vView - m_vPosition;	// Get the view vector

	m_vView.z = (float)(m_vPosition.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	m_vView.x = (float)(m_vPosition.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}
//debug : 'defines' à nettoyer
void 
Camera::Mouse_Move(int wndWidth, int wndHeight)
{
	int mid_x = wndWidth  >> 1;	
	int mid_y = wndHeight >> 1;	
	float angle_y  = 0.0f;				
	float angle_z  = 0.0f;	
        
        if (( mouseX== mid_x) && (mouseY == mid_y) ) return;

	glutWarpPointer(mid_x, mid_y);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed

	angle_y = (float)( (mid_x - mouseX) ) / 1000;		
	angle_z = (float)( (mid_y - mouseY) ) / 1000;

	// The higher the value is the faster the camera looks around.
	m_vView.y += angle_z * 15;

	// limit the rotation around the x-axis
	if((m_vView.y - m_vPosition.y) > 15)  m_vView.y = m_vPosition.y + 15;
	if((m_vView.y - m_vPosition.y) <-15)  m_vView.y = m_vPosition.y - 15;
	
	Rotate_View(-angle_y); // Rotate
}
