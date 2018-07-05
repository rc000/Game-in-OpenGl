#include "stdafx.h"
#include<iostream>
#include "Core.h"

using namespace std;
void Core::set(float xt, float yt, float zt, GLuint kadlub)
{
	x = xt;
	y = yt;
	z = zt;
	this->kadlub = kadlub;
	x1 = x - 5;
	x2 = x + 5.0f;
	z1 = z - 5.0f;
	z2 = z + 5.0f;
}
 
Core::Core():x(0),y(0),z(0)
{
}
void Core::Render(float move_op, float posy, float posz, float rot_start,float rot, GLuint kadlub)
{
	this->kadlub = kadlub;
	glPushMatrix();
	glTranslatef(move_op, posy + 6.0f, posz);
	glRotatef(rot_start, 0.0f, 1.0f, 0.0f);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	glScalef(4.0f, 4.0f, 4.0f);
	glCallList(kadlub);
	glPopMatrix();

}
