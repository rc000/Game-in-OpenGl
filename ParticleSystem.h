#pragma once
#include"stdafx.h"
#include<vector>
#include"Particle.h"
using std::vector;

class ParticleSystem {

	vector <Particle>Particles;
 	struct pos {
		float x, y, z;
	};
	pos position;
	int time;
	GLuint texfire, texsmoke;
public:
	void add(int frame);
	void draw ();
	int getTime();
	ParticleSystem(float x, float y, float z,GLuint fire,GLuint smoke);
	~ParticleSystem();
 	void update(int frame);

};