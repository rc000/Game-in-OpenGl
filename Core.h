#pragma once
#include "stdafx.h"

class Core {
	float x, x1, x2, y, z, z1, z2;
	int trafienia;
	GLuint kadlub;
public:
	void set(float xt, float yt, float zt, GLuint kadlub);
	Core();
	void Render(float move_op, float posy, float posz,float rot_start, float rot, GLuint kadlub);
};
