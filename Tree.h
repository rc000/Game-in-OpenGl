#pragma once
#include "stdafx.h"

class Tree {
	int x,x1, x2, y,y1,z,z1, z2;
	GLuint pien,liscie;
	float rot;
	bool przewrocone;
public :
	void set(int xt, int yt, int zt, GLuint pien,GLuint liscie);
	Tree();
	  void Render_pien();
	  bool get_przewrocone();
	  void Render_liscie();
	  void set_rot(float rot);
	  bool Kolizja(float posx,float y, float z);

};