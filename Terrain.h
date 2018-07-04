#pragma once
#include "Bitmap.h"
#include "stdafx.h"

class Terrain {
private :int width, height;
	float *vertices;
	
	Bitmap *mapa;

public :GLuint id,trees;
		 
public :Terrain();
		~Terrain();
        void zaladuj();
 		float getHeight(int x, int z);
		void prepareRender(GLuint texgrass,GLuint texwater);
		void calculateNormals(int x, int y, int z);
		float linearInterpolation(float x, float z);
		void drawText(const char *text, int length, int x, int y);
		void calculateCrossProduct(float x, float y, float z, float x1, float y1, float z1, int count);
 		struct normals
		{
			float nx,ny,nz;
			normals & operator+(const normals& v) {
				nx += v.nx;
				ny += v.ny;
				nz += v.nz;

				return *this;
			}
		};
private:
	normals * vector;
	normals *temp;


};
