#pragma once
#include"stdafx.h"

class Particle {
	struct vec3 {
		float x, y, z;
	};
 
	struct ParticleState {
		vec3 position;
		float speed;
		float x_tempuj,x_tempd;
		int live;
		float size;
		bool change_texfire;
		bool change_texsmoke;
		ParticleState(float x,float y,float z,float speed,float x_tempuj, float x_tempd,int live, float size,bool change_texfire,bool change_texsmoke):
			position{x,y,z},speed(speed),x_tempuj(x_tempuj),x_tempd(x_tempd),live(live),size(size),change_texfire(change_texfire),change_texsmoke(change_texsmoke)
		{};

	};

GLuint vbo;

public :ParticleState *state;
public :Particle();
		~Particle();
	void update(int frame,int ry);
	void set(float x, float y, float z);
	void draw();
	int getLive();


};
