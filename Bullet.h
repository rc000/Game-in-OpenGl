#pragma once
#include "stdafx.h"

class Bullet {
	 
		float px, py, pz,py_temp;
	 
	
		float dx, dy, dz;
		GLuint bullet;
 	float speed;
 public:
	Bullet(float posx, float posy, float posz,float dirx,float diry,float dirz,GLuint bullet1);
	~Bullet();
 	void fire(float rot,float tor);
	void set(float posx, float posy, float posz, float dirx, float diry, float dirz);
	float getx();
	float gety();
	float getz();

};
