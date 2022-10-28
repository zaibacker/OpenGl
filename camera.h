//camera.h : Goulwen

#ifndef CAMERA_H
#define CAMERA_H
#define ESC 27
#define PI 3.14159
#include "world.h"

class World;

class Mouse{
public :
	int x;
	int y;
	bool left_button;
	bool right_button;
};

void terminateApplication(void);
//CVector3 debug : 3DMath.h
class CVector3
{
public:
	
	// Constructeur par defaut
	CVector3() {}


	CVector3& operator += (const CVector3 &other);
    	CVector3& operator -= (const CVector3 &other);
	friend CVector3 operator * (const float &scalar, const CVector3 &other);	
	

	// Constructeur qui permet d'initialiser les chans
	CVector3(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	// Here we overload the + operator so we can add vectors together 
	CVector3 operator+(CVector3 &vVector)
	{
		// Return the added vectors result.
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	// Here we overload the - operator so we can subtract vectors 
	CVector3 operator-(CVector3 &vVector)
	{
		// Return the subtracted vectors result
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	
	// Here we overload the * operator so we can multiply by scalars
	CVector3 operator*(float num)
	{
		// Return the scaled vector
		return CVector3(x * num, y * num, z * num);
	}

	// Here we overload the / operator so we can divide by a scalar
	CVector3 operator/(float &num)
	{
		// Return the scale vector
		return CVector3(x / num, y / num, z / num);
	}

	float x, y, z;			
	
	
};


class Camera{
private:
	// Reference vers le world
	World * _world;
	float _hauteur;
	float _pas;
	float _Xmax;
	float _Zmax;
	
	// Attributs	
	Mouse mouse;

	// Vecteur position de la camera
	CVector3 m_vPosition;					

	// Vecteur de visée
	CVector3 m_vView;						

	// Vecteur d'oriention de la camera
	CVector3 m_vUpVector;		
	
	// Vecteur de straff
	CVector3 m_vStrafe;
	
	// Position de la souris en X
	int mouseX;

	// Position de la souris en Y
	int mouseY;
protected:
public:
	Camera(void);
	float getPosX(){return m_vPosition.x;}
	float getPosZ(){return m_vPosition.z;}
	void clavier(unsigned char touche,int x,int y);
	void souris(int bouton, int etat,int x,int y);
	void sourismouv(int x,int y);
	void Look(void);
 	void StrafeCamera(float speed);
	void MoveCamera(float speed);
	void Update(void);
	void RotateView(float angle, float x, float y, float z);
	void SetViewByMouse(void);
	void Mouse_Move(int wndWidth, int wndHeight);
	void Rotate_View(float speed);
	void loadWorld(World * world);

};



#endif
