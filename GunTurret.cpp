#include "stdafx.h"
#include<iostream>
#include "GunTurret.h"

using namespace std;
void GunTurret::set(float xt, float yt, float zt, GLuint wieza1)
{
	x = xt;
	y = yt;
	z = zt;
	wieza = wieza1;
	x1 = x - 5;
	x2 = x + 5.0f;
	z1 = z - 5.0f;
	z2 = z + 5.0f;
}

GunTurret::GunTurret():x(0),y(0),z(0)
{
}
void GunTrret::Render(float move_op, float posy, float posz, float rot_start, float rot, GLuint wieza1,float rot_destroy)
{
	wieza = wieza1;
	glPushMatrix();

	glTranslatef(move_op, posy + 6.0f, posz);
	glRotatef(rot_start, 0.0f, 1.0f, 0.0f);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	if(rot_destroy<20.0f)
	glRotatef(rot_destroy, 1.0f, 0.0f, 1.0f);
	else if (rot_destroy<40.0f)
		glRotatef(-rot_destroy, 0.0f, 1.0f, 1.0f);
	else if (rot_destroy<60.0f)
		glRotatef(rot_destroy, 0.0f, 0.0f, 1.0f);
	else if (rot_destroy<80.0f)
		glRotatef(-rot_destroy, 1.0f, 0.0f, 1.0f);
	else 
		glRotatef(rot_destroy, 1.0f, 1.0f, 1.0f);
	glScalef(4.0f, 4.0f, 4.0f);
	glCallList(wieza);
	glPopMatrix();



}
