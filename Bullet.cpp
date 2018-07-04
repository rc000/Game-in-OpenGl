#include "stdafx.h"
#include<iostream>
#include"Bullet.h"

using namespace std;
Bullet::Bullet(float posx, float posy, float posz, float dirx, float diry, float dirz,GLuint bullet1):
	speed(20.0),px(posx + dirx * 15),py(posy - 4.5f),pz(posz + dirz * 15),dx(dirx),dy(diry),dz(dirz),bullet(bullet1)
{
	
}
Bullet::~Bullet()
{

}
float Bullet::getx()
{
	return px;
}
float Bullet::gety()
{
	return py;
}
float Bullet::getz()
{
	return pz;
}
void Bullet::fire(float rot,float tor)
{
	px += dx*speed;
	py +=dy*4.0f;
 	pz += dz*speed;
	float m_amb[] = { 0.0f, 0.0f, 0.0f };
	float m_dif[] = { 0.0f, 0.0f, 0.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	glPushMatrix();

	glTranslatef(px, py-2.0f, pz);
	
  	glutSolidSphere(0.5f,24,24);

	glPopMatrix();
	speed += 3.5;
}
 void Bullet:: set(float posx, float posy, float posz, float dirx, float diry, float dirz)
{
	px = posx;
	py = posy;
	pz = posz;
	dx = dirx;
	dy = diry;
	dz = dirz;
	speed = 0.1;
}