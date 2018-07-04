#include"stdafx.h"
#include "ParticleSystem.h"
#include"Particle.h"
#include<iostream>
using namespace std;
void ParticleSystem::add(int frame)
{
	Particle p[5];
	
	for (int i = 0; i < 5; i++)
	{
		p[i].set(position.x, position.y, position.z);
		Particles.push_back(p[i]);
 
	}


}
ParticleSystem::ParticleSystem(float x, float y, float z, GLuint fire, GLuint smoke)
	:position{ x,y,z },texfire(fire),texsmoke(smoke),time(0)
{

}
ParticleSystem::~ParticleSystem()
{
}

int ParticleSystem::getTime()
{
	return time;
}
void  ParticleSystem::update(int frame)
{
	time++;
	for (vector<Particle>::iterator it=Particles.begin();it!=Particles.end();)
	{
		
		if (it->getLive() > 14)
			it = Particles.erase(it);

		else if (it->getLive() > 12)
		{
			it->update(frame, 10);
			it++;

		}

		else
		{
			it->update(frame, 4);
			it++;

		}

	}
}

void  ParticleSystem::draw()
{
	for (vector<Particle>::iterator it = Particles.begin(); it != Particles.end();)
	{

		if (it->getLive() > 12)
		{
			glBindTexture(GL_TEXTURE_2D, texsmoke);
 		}
		else if (it->getLive()  <= 12 )
		{
			glBindTexture(GL_TEXTURE_2D, texfire);
 
		}
		float m1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float m1_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		float m1_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);


		it->draw();

	}

}
