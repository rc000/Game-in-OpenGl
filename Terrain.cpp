#include "stdafx.h"
#include "Terrain.h"
#include "Bitmap.h"
#include<math.h>


Terrain::Terrain()
{
	temp = new normals[8];

}
Terrain::~Terrain()
{
	delete temp;
	delete vector;
	delete vertices;
	
}
void Terrain::drawText(const char *text, int length, int x, int y)
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
 
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
void Terrain::zaladuj()
{
	mapa->loadBMP("Resources\\textures\\terrain1.bmp");
	height = mapa->height;
	width = mapa->width;
	 
	vertices = new float[height*width*2];
	vector = new normals[height*width*2];
	unsigned char *tempData = new  unsigned char[height*width];
	int temp = 0;
	for (int i = 0; i < height; i ++)
	{
		for (int j = 0; j < width; j ++)
		{
			tempData[i*height + j] = ( unsigned char)mapa->data[temp];

			temp +=3; 
		}
	}
	float startX = width / 2.0 - width;
	float startZ = -height / 2.0;
	int k;
	int j;
 	for (int i = 0; i < height; i++)
	{
		for ( j = 0; j < width; j++)
		{
			vertices[i*height + j] = (float)(tempData[i*height + j])*0.03f;
 			 
   		}
		k = i*height + 512 - 1;
	}
	for (int i = height; i < 2*height; i++)
	{
		for (int j = 0; j < width; j++)
		{	 
			vertices[i*height + j] = vertices[k];
 			k--;
 		}

	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
 			if ((j != 0) && (j != height - 1) && (i != height - 1) && (i != 0))
				calculateNormals(startX + i + 1, i *height + j, startZ + j);
		}
	}
	delete mapa;
  }
void Terrain::calculateCrossProduct(float x, float y, float z, float x1, float y1, float z1, int count)
{
	temp[count].nx = y*z1 - z*y1;
	temp[count].ny = z*x1 - x*z1;
	temp[count].nz = x*y1 - y*x1;
	 
}
void Terrain::calculateNormals(int x, int y, int z)
{
	normals V[8];

	V[0].nx = x - 1;
	V[0].ny = vertices[ y - height-1];
	V[0].nz = z-1;

	V[0].nx-=x;
	V[0].ny-=vertices[y];
	V[0].nz-=z;
	 
 	V[1].nx = x-1;
 	V[1].ny =vertices[ y -height];
	V[1].nz = z ;
 
	V[1].nx -= x;
	V[1].ny -= vertices[y];
	V[1].nz -= z;
	
	V[2].nx = x-1;
	V[2].ny = vertices[y -height+ 1];
	V[2].nz = z + 1;

	V[2].nx -= x;
	V[2].ny -= vertices[y];
	V[2].nz -= z;

	V[3].nx = x ;
	V[3].ny = vertices[y + 1 ];
	V[3].nz = z+1;

	V[3].nx -= x;
	V[3].ny -= vertices[y];
	V[3].nz -= z;

	V[4].nx = x+1 ;
	V[4].ny = vertices[y +height+1];
	V[4].nz = z+1;

	V[4].nx -= x;
	V[4].ny -= vertices[y];
	V[4].nz -= z;

	V[5].nx = x+1;
	V[5].ny = vertices[y +height];
	V[5].nz = z ;

	V[5].nx -= x;
	V[5].ny -= vertices[y];
	V[5].nz -= z;

	V[6].nx = x + 1;
	V[6].ny = vertices[y + height-1];
	V[6].nz = z-1;

	V[6].nx -= x;
	V[6].ny -= vertices[y];
	V[6].nz -= z;

	V[7].nx = x ;
	V[7].ny = vertices[y - 1];
	V[7].nz = z - 1;

	V[7].nx -= x;
	V[7].ny -= vertices[y];
	V[7].nz -= z;

	calculateCrossProduct(V[0].nx, V[0].ny, V[0].nz, V[1].nx, V[1].ny, V[1].nz, 0);
	calculateCrossProduct(V[1].nx, V[1].ny, V[1].nz, V[2].nx, V[2].ny, V[2].nz, 1);
	calculateCrossProduct(V[2].nx, V[2].ny, V[2].nz, V[3].nx, V[3].ny, V[3].nz, 2);
	calculateCrossProduct(V[3].nx, V[3].ny, V[3].nz, V[4].nx, V[4].ny, V[4].nz, 3);
	calculateCrossProduct(V[4].nx, V[4].ny, V[4].nz, V[5].nx, V[5].ny, V[5].nz, 4);
	calculateCrossProduct(V[5].nx, V[5].ny, V[5].nz, V[0].nx, V[0].ny, V[0].nz, 5);
	calculateCrossProduct(V[6].nx, V[6].ny, V[6].nz, V[7].nx, V[7].ny, V[7].nz, 6);
	calculateCrossProduct(V[7].nx, V[7].ny, V[7].nz, V[0].nx, V[0].ny, V[0].nz, 7);

	vector[y] = temp[1] + temp[2] + temp[3] + temp[4] + temp[0] + temp[5] +temp[6] + temp[7];
	
	

	vector[y].nx/=8.0f ;
	vector[y].ny/=8.0f ;
	vector[y].nz/=8.0f ;


}
float Terrain::linearInterpolation(float x, float z)
{
	int x_low = (int)x;
	int z_low = (int)z;
	int x_high;
	int z_high;
	if (x < 0)
	{
		x_low -= 1;
		x_high = x_low + 1;
	}
	else
		x_high = x_low + 1;

	if (z < 0)
	{
		z_low -= 1;
		z_high = z_low + 1;
	}
	else
	z_high = z_low + 1;

 	float dif_x = (float) x-x_low/(x_high-x_low);
	 

	float dif_z = (float) z-z_low / (z_high - z_low);
	 
	
	float h1, h2, h3,h4,h0,H1,H2,H3;
	 
		h0 = getHeight(x_low, z_high);
		h1 = getHeight(x_high, z_high);
		h2 = getHeight(x_low, z_low);
		h3= getHeight(x_high, z_low);
		dif_x = abs(dif_x);
		dif_z = abs(dif_z);
		H1 = h0*(1 - dif_x) + h1*( dif_x);
		H2 = h2*(1 - dif_x) + h3* dif_x;
		H3 = H1*dif_z + H2*(1 - dif_z);
 	 
 
	return H3;

}
float Terrain::getHeight(int x,int z)
{
	float h;
	int startX = width / 2.0 - width;
	int startZ = -height / 2.0;
	int i = x - startX;
	int j = z - startZ;
	h = vertices[(i-1)*height + j];
 	return h;
}
 
void Terrain::prepareRender(GLuint texgrass,GLuint texwater)
{

	float startX =width / 2.0 - width;
	float startZ = -height / 2.0 ;
 
	float m1_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m1_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);

	glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
 	int j;
	id = glGenLists(1);

	glNewList(id, GL_COMPILE);

	glBegin(GL_TRIANGLE_STRIP);

	glBindTexture(GL_TEXTURE_2D, texgrass);

		for (int i = 0; i <height; i++)
		{
	
 
			for (j = 0; j < width; j++)
			{

				if ((i > 0) && (j == 0))
				{
   						glTexCoord2f(1.0f, 0.0f);
 
					glVertex3f(startX + i, vertices[(i - 1) * height], startZ);
 				}

				if (i == 0)
				{

 					glTexCoord2f(0.0f, 1.0f);
 					glVertex3f(startX + i, vertices[i*height + j], startZ + j);


				}
				else if (i > 0)
				{
				 
						 
				  glTexCoord2f((float)i/10, (float)j/10);
					
					if ((j != 0) && (j != height - 1) && (i != height - 1) && (i != 0))
					{
						glNormal3f(vector[(i - 1)*height + j].nx, vector[(i - 1)*height + j].ny, vector[(i - 1)*height + j].nz);
					}

					glVertex3f(startX + i, vertices[(i - 1)*height + j], startZ + j);

					if ((j != 0) && (j != height - 1) && (i != height - 1) && (i != 0))
						glNormal3f(vector[i *height + j].nx, vector[i *height + j].ny, vector[i *height + j].nz);
					glTexCoord2f((float)(i+1) / 10, (float)j / 10);

					glVertex3f(startX + i + 1, vertices[i*height + j], startZ + j);
				}

			}
		 
		 glNormal3f(vector[i *height + j-1].nx, vector[i *height + j-1].ny, vector[i *height + j-1].nz);

		 glVertex3f(startX + i + 1, vertices[i*height + j-1], startZ + j-1);

	}
			 

			

		glEnd();
		glEndList();

	 



 
 

}