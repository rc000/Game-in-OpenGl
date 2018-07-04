#include "stdafx.h"
#include<iostream>
#include "Tank.h"

using namespace std;
void Tank::set(float xt, float yt, float zt, GLuint kadlub1)
{
	x = xt;
	y = yt;
	y1 = y - 5.0f;
	y2 = y + 5.0f;
	z = zt;
	//kadlub = kadlub1;
	x1 = x - 7.0f;
	x2 = x + 7.0f;
	z1 = z - 7.0f;
	z2 = z + 7.0f;
}
void Tank::set_z(float z1)
{
	z = z1;
}
void Tank::set_x(float x1)
{
	x = x1;
}void Tank::set_y(float y1)
{
	y = y1;
}
float Tank::get_z()
{
	return z;
}
float Tank::get_x()
{
	return x;
}
float Tank::get_y()
{
	return y;
}
Tank::Tank():x(0),y(0),z(0),health(4),czas_od_zniszczenia(0),zniszczony(false)
{

}
void Tank::render_kadlub(float move_op, float posy, float posz, float rot_start, float rot, float rotx, float rotz, GLuint kadlub1)
{
	kadlub.Render(move_op, posy, posz, rot_start, rot, kadlub1);

}
bool Tank::czy_zniszczony()
{
	return zniszczony;
}
void Tank::set_zniszczony(bool zniszcz)
{
	zniszczony = zniszcz;
	health = 0;
}
int Tank::getTime()
{
	return czas_od_zniszczenia;
}
void Tank::increase_czas()
{
	czas_od_zniszczenia++;
}
void Tank::render_wieza(float move_op, float posy,  float posz,float rot_start, float rot, float rotx, float rotz, float destroy,GLuint wieza1)
{
	if(health>0)
	wieza.Render(move_op, posy, posz, rot_start, rot, wieza1,0.0f);
	else
	{
		wieza.Render(move_op + 5.0f, posy, posz + 5.0f, rot_start, rot, wieza1, destroy);
	}
}
int Tank::get_health()
{
	return health;
}
void Tank::Render(float move_op,float posy,float posz,float rot_start,float rot,float rotx,float rotz,    bool h)
{
	x = move_op;
	y = posy;
	z=posz;
	y1 = y - 15.0f;
	y2 = y + 15.0f;
	x1 = x - 15.0f;
	x2 = x + 15.0f;
	z1 = z - 15.0f;
	z2 = z + 15.0f;


	if (h == true)
	{
		if (health >= 0)
		{
			glPushMatrix();

			glTranslatef(move_op - 5.0f, posy + 20.0f, z);
			glScalef(health*1.0f, 0.2f, 0.2f);
			glutSolidCube(5.0f);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(move_op - 5.0f, posy + 20.0f, z);
			glScalef(4 * 1.0f, 0.2f, 0.2f);
			glutWireCube(5.0f);
			glPopMatrix();
		}
	}

 
 

}
bool Tank::Kolizja(float posx,float posy, float posz,bool bullet)
{
	if ((posx > x1) && (posx<x2) && (posz>z1) && (posz < z2)&&(posy>=y)&&(posy<y2))
	{
		if(bullet)
		health--;
		 
		return true;
	}
	else return false;
}