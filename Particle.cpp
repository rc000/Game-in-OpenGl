#include"stdafx.h"
#include"Particle.h"
#include<iostream>
using namespace std;
void Particle::update(int frame,int ry)
{
	float randomx=0;
	state->size -= 0.4f;
	 randomx = (rand() % 10) + 1;
 	float randomy = (rand() % ry) + 1;
	float randomz = (rand() % 2 + 1);
 	state->speed += 0.1f;
	if (state->live % 2 == 0)
	{
 		state->position.x+= randomx / 5.0f;
		state->position.y += randomy ;
		state->position.z -= randomz / 3.0f;
	}
	if (state->live  % 2 != 0)
	{
 		 
		state->position.x -= randomx / 5.0f;
		state->position.y -= randomy / 3.0f;
		state->position.z += randomz / 3.0f;
	
	}
	 
	state->live++;
 
}
void Particle::set(float x, float y, float z)
{
	state->position.x = x;
	state->position.y = y;
	state->position.z = z;
}


Particle::Particle()
{
	state = new ParticleState(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 15.0f, false, false);
	
}
~Particle::Particle()
{
	delete state;
}

int Particle::getLive()
{
	return state->live;
}
void Particle::draw( )
{
	glPushMatrix();
 
	glPointSize(state->size);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glEnable(GL_POINT_SPRITE);

	glBegin(GL_POINTS);
	glVertex3f(state->position.x, state->position.y, state->position.z);
 	glEnd();
	glDisable(GL_POINT_SPRITE);

  	glPopMatrix();

}