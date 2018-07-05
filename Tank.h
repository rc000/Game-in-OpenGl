#pragma once
#include "stdafx.h"
#include "Core.h"
#include "GunTurret.h"

class Tank {
	float x, x1, x2, y,y1,y2, z, z1, z2;
	Core core;
	GunTurret gunTurret;
	bool zniszczony;
	int czas_od_zniszczenia;
public :int health;
	GLuint  texkadlub;

public:
	void set(float xt, float yt, float zt, GLuint tank1);
	int getTime();
	void increase_czas();
	int get_health();
	void set_z(float z1);
	void set_x(float x1);
	void set_y(float y1);

	float get_z();
	float get_x();
	float get_y();
	void set_zniszczony(bool zniszczony);
	bool czy_zniszczony();

	Tank();
	void renderCore(float move_op, float posy,float posz,float rot_start, float rot, float rotx, float rotz, GLuint kadlub1);
	void renderTurret(float move_op, float posy,float posz, float rot_start, float rot, float rotx, float rotz,float destroy, GLuint wieza1);

	void Render(float move_op, float posy, float posz,  float rot_start,float rot,float rotx,float rotz,bool h);
	bool Kolizja(float posx, float y,float z,bool pocisk);

};
