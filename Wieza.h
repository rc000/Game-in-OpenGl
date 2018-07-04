#pragma once
 #include "stdafx.h"

class Wieza {
	float x, x1, x2, y, z, z1, z2;
	int trafienia;
	GLuint wieza;
public:
	void set(float xt, float yt, float zt, GLuint wieza);
	Wieza();
	void Render(float move_op, float posy, float posz, float rot_start, float rot, GLuint wieza,float rot_wreck);
	bool Kolizja(float posx, float z);
};