#include "stdafx.h"
#include<iostream>
#include "Tree.h"
using namespace std;
void Tree::set(int xt, int yt, int zt,GLuint pien1,GLuint liscie1)
{
	x = xt;
	y = yt;
	z = zt;
	pien = pien1;
	liscie = liscie1;
	x1 = x - 5.0f;
	x2 = x + 5.0f;
	z1 = z - 5.0f;
	z2 = z + 5.0f;
	y1 = y + 10.0f;
}
void Tree::set_rot(float rot1)
{
	rot = rot1;
	przewrocone = true;
	if (z > 0)
		rot *= -1.0f;
}
bool Tree::get_przewrocone()
{
	return przewrocone;
}
Tree::Tree():rot(0.0f),x(0),y(0),z(0),przewrocone(false)
{

}
void Tree::Render_pien()
{
	glPushMatrix();
	float m_amb[] = { 0.0f, 1.0f, 0.0f };
	float m_dif[] = { 0.0f, 1.0f, 0.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	glTranslatef(x*1.0f, y, z*1.0f);
	glRotatef(rot, 1.0f, 0.0f, 0.0f);
	glScalef(4.0f, 2.5f, 4.0f);
	glCallList(pien);
 	glPopMatrix();


}
void Tree::Render_liscie()
{
	
	glPushMatrix();
	float m_amb[] = { 0.0f, 1.0f, 0.0f };
	float m_dif[] = { 0.0f, 1.0f, 0.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	glTranslatef(x*1.0f, y , z*1.0f+2.0f);
	glRotatef(rot, 1.0f, 0.0f, 0.0f);

	glScalef(5.0f, 4.0f, 5.0f);
 	glCallList(liscie);
	glPopMatrix();


}
bool Tree::Kolizja(float posx, float posy, float posz)
{
	if ((posx >= x1) && (posx<=x2) && (posz>=z1) && (posz <= z2) && (posy<=30)  )
	{
	
		return false;

	}
	else return true;
}