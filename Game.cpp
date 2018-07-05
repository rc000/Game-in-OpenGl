#include "stdafx.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

#include<math.h>
#include "Terrain.h"
#include "Bullet.h"
#include "Tree.h"
#include <vector>
#include "tga.h"
#include "ParticleSystem.h"
#include"Skydome.h"
#include <cstdlib>
#include<vector>
bool captureMouse = true;
int mouseX = 0;
int mouseY = 0;
float mouseSensitivity = .15f;

float amb_sky[] = {0.1f, 0.1f, 0.1f ,1.0f };
float dif_sky[] = { 0.1f, 0.1f, 0.1f,1.0f };
float spe_sky[] = { 0.5f, 0.5f, 0.5f,1.0f };

int minutes = 0;
int hours = 0;
int chances = 5;
float move_airplane_z = -200.0f;

int time_from_defeat = 0;
bool tex_skydome = false;
bool airplane = false;

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")
  
ISoundEngine* engine = createIrrKlangDevice();

 int main(int argc, char* argv[])
{
	srand(time(NULL));
	
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Obrona miasta");

	glutPostRedisplay();
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);


	glutSpecialFunc(OnSpecialKeyPress); // klawisze specjalne (strzalki, F1-F12, PgUp/PgDn, Home, End, Delete, Insert)
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_CULL_FACE); // Włączenie cullingu - rysowania tylko jednej strony wielokątów
	glCullFace(GL_BACK); // Określenie, którą stronę wielokątów chcemy ukrywać
	glFrontFace(GL_CW);*/
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_LIGHTING); // Wlaczenie oswietlenia
	glShadeModel(GL_SMOOTH); // Wybor techniki cieniowania
	glEnable(GL_LIGHT0); // Wlaczenie 0-go zrodla swiatla
	glEnable(GL_LIGHT1); // Wlaczenie 1-go zrodla swiatla
	//glEnable(GL_LIGHT2); // Wlaczenie 2-go zrodla swiatla

	teren.zaladuj();

	// Inicjalizacja stanu kamery:
	player.pos.x = -105.0f;
	player.pos.y = teren.linearInterpolation(-105.0f,5.0f)+30.0f;
	player.pos.z = 5.0f;

	player.dir_view.x = -0.0001f;
	player.dir_view.y = 0.17f;
	player.dir_view.z = -0.98f;
	player.dir_move.x = 0.0f;
	player.dir_move.y = 0.0f;
	player.dir_move.z = -1.0f;
	player.speed = 5.5f;
	player.pos.x += player.dir_move.x * player.v1*.5f;
	player.pos.y = teren.linearInterpolation(player.pos.x, player.pos.z) + 25.5f;
	player.pos.z += player.dir_move.z * player.v1*.5f;

	kolo = gluNewQuadric();
	gluQuadricTexture(kolo, GL_TRUE);


	start = LoadObj("Resources\\startowy.txt");
	tex_start = LoadTexture("Resources\\textures\\start1.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	skyd = LoadTexture("Resources\\textures\\output1.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	engine->play2D("Resources\\sounds\\deszcze.wav");

	  glutMainLoop();

	return 0;
}

void init()
{
	
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(mouseClicks);
	glutMouseWheelFunc(mouseWheel);
 	textank = LoadTexture("Resources\\textures\\tank3.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	texgrass = LoadTexture("Resources\\textures\\grass2.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
  	texkadlub = LoadTexture("Resources\\textures\\kadlub_Diffuse2.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
 	tex_win = LoadTexture("Resources\\textures\\win.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tex_lose = LoadTexture("Resources\\textures\\ruin.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tex_aircraft = LoadTexture("Resources\\textures\\tex_aircraft.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tex_building1 = LoadTextureTga("Resources\\city\\tex_building.tga", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tex_building2 = LoadTextureTga("Resources\\city\\tex_building2.tga", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tex_building3 = LoadTextureTga("Resources\\city\\tex_building3.tga", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tex_building4 = LoadTextureTga("Resources\\city\\tex_building4.tga", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	texfire = LoadTextureTga("Resources\\textures\\fire.tga", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
 	texsmoke = LoadTextureTga("Resources\\textures\\smoke1.tga", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tex_tree= LoadTextureTga("Resources\\textures\\tree.tga", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	texwieza = LoadTexture("Resources\\textures\\wieza_Diffuse.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	skyd = LoadTexture("Resources\\textures\\output1.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	skyd1 = LoadTexture("Resources\\textures\\skydom.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);

	texbark = LoadTexture("Resources\\textures\\pien.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	skyd1 = LoadTexture("Resources\\textures\\skydom.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	tank_szanse = LoadObj("Resources\\tank_lives.obj");

	teren.prepareRender(texgrass, texwater);
 	kadlub = LoadObj("Resources\\czolg1.obj");


	wieza = LoadObj("Resources\\Leo_wieza.obj");

	skydome.Initialize(skyd);
 	airplane_a10 = LoadObj("Resources\\airplane.obj");

	pien = LoadObj("Resources\\pien.obj");
	liscie = LoadObj("Resources\\liscie1.obj");

	building1 = LoadObj("Resources\\city\\building1.obj");
	building2 = LoadObj("Resources\\city\\building2.obj");
	building3 = LoadObj("Resources\\city\\building3.obj");
	building4 = LoadObj("Resources\\city\\building4.obj");
	 
	for (int i = 0; i < 20; i++)
	{
		tab[i] = (rand() % 3) + 1;

	}

	for (int i = -250; i < 250; i += 20)
	{
		Tree drzewo;


		drzewo.set(i, teren.linearInterpolation(i, -250.0f), -250.0f, pien, liscie);

		drzewa.push_back(drzewo);
		drzewo.set(i, teren.linearInterpolation(i, -250.0f), 250.0f, pien, liscie);
		drzewa.push_back(drzewo);


	}
	for (int i = -240; i < 260; i += 20)
	{
		Tree drzewo;
		drzewo.set(i, teren.linearInterpolation(i, -240.0f), -240.0f, pien, liscie);


		drzewa.push_back(drzewo);
		drzewo.set(i, teren.linearInterpolation(i, -240.0f), 240.0f, pien, liscie);
		drzewa.push_back(drzewo);


	}
	for (int i = -230; i < 260; i += 15)
	{
		Tree drzewo;

		drzewo.set(i, teren.linearInterpolation(i, -230.0f), -230.0f, pien, liscie);

		drzewa.push_back(drzewo);
		drzewo.set(i, teren.linearInterpolation(i, -240.0f),  230.0f, pien, liscie);
		drzewa.push_back(drzewo);
	}
	Tree drzewo, drzewo1;
	drzewo.set(5.0f, teren.linearInterpolation(5.0f, -5.0f), -5.0f, pien, liscie);
	drzewa.push_back(drzewo);

	drzewo1.set(-15.0f, teren.linearInterpolation(-15.0f, -5.0f), -5.0f, pien, liscie);
	drzewa.push_back(drzewo1);


}
// Tablica przechowująca stan klawiszy w formie flag, indeksowana wg kodów ASCII.
int frame = 1000;
bool ifinit = false;
bool able_to_shoot=true;
bool keystate[256];
float beta;
float y_building = 75.0f;
float tor = 0.0f;
float beta_move;
double theta, sigma;
 float r;
 float rad = 0;
  float amb_x = 0.0f;
 float amb_z = 1.0f;
 float amb_y = 0.0f;
  float hgt;
 bool ifstart = false;
 float mt = 0.0f;
  int flaga = 0;
 float rot = 0.0f;
 float rot_move = 0.0f;
 bool able_to_move = true;
   bool keystate_special[256];

 void OnKeyPress(unsigned char key, int x, int y) {
	 if (!keystate[key]) {
		 OnKeyDown(key, x, y);
	 }
	 keystate[key] = true;
 }

 void OnSpecialKeyPress(int key, int x, int y) {
	 if (!keystate_special[key]) {
		 OnSpecialKeyDown(key, x, y);
	 }
	 keystate_special[key] = true;
 }
 void mouseWheel(int button, int dir, int x, int y)
 {
	 if (dir > 0)
	 {
		 if (tor<0.9f)
			 tor += 0.05f;
	 }
	 else
	 {
		 if (tor>-0.9f)
			 tor -= 0.05f;
	 }

	 return;
 }
 void OnKeyDown(unsigned char key, int x, int y) {
	 if (key == 27) {
		 glutLeaveMainLoop();
	 }
	 if (key == 'm' || key == 'M') {
		 if (captureMouse) {
			 captureMouse = false;
			 glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		 }
		 else {
			 captureMouse = true;
			 glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			 glutSetCursor(GLUT_CURSOR_NONE);
		 }
	 }
 }
 void OnSpecialKeyDown(int key, int x, int y) {
 }


 void OnKeyUp(unsigned char key, int x, int y) {
	 keystate[key] = false;
 }
 void OnMouseMove(int x, int y) {
	 mouseX = x;
	 mouseY = y;
 }
 void mouseClicks(int button, int state, int x, int y) {
	 if (button == GLUT_LEFT_BUTTON ) {
		 if (able_to_shoot == true)
		 {
			 Bullet bullet1(player.pos.x, player.pos.y -10.0f+ tor, player.pos.z, player.dir_view.x, player.dir_view.y  + tor, player.dir_view.z, tank_bullet);
 			 pociski.push_back(bullet1);
			 engine->play2D("Resources\\sounds\\fire.wav");
			 able_to_shoot = false;
		 }
 	 }
 }
 void OnSpecialKeyUp(int key, int x, int y) {
	 keystate_special[key] = false;
 }


// Aktualizacja stanu gry - wywoływana za pośrednictwem zdarzenia-timera.
 

	void OnTimer(int id) {

		// Chcemy, by ta funkcja została wywołana ponownie za 17ms.
		glutTimerFunc(17, OnTimer, 0);

		skydome.Update();
		rad += 0.02f;
#pragma region moving

		//forward
		if (keystate['w']) {
 		
			if (able_to_move == true)
			{
				player.v1 = player.speed;
				player.pos.x += player.dir_move.x * player.v1*.5f;
				player.pos.y = teren.linearInterpolation(player.pos.x, player.pos.z) + 25.5f;
				player.pos.z += player.dir_move.z * player.v1*.5f;
			}
		}

		// backwards:
		if (keystate['s']) {
			player.v1 = -player.speed;
			player.pos.x += player.dir_move.x * player.v1*.5f;
			player.pos.y = teren.linearInterpolation(player.pos.x, player.pos.z) + 25.5f;
			player.pos.z += player.dir_move.z * player.v1*.5f;

		}
		// right:
		if (keystate['d']) {
			player.v2 = player.speed;
			player.pos.x += -player.dir_move.z*player.v2*.1f;
			player.pos.z += player.dir_move.x*player.v2*.1f;

		}

		//left:
		if (keystate['a']) {
			player.v2 = -player.speed;
			player.pos.x += -player.dir_move.z*player.v2*.1f;
			player.pos.z += player.dir_move.x*player.v2*.1f;


		}
		//up, view from above
		if (keystate['t']) {
	
			player.pos.y += player.speed*0.5f;

		}
		if (keystate['o']) {
			mt -= 0.5f;
		}
		// down
		if (keystate['g']) {
			if (player.pos.y>hgt + 0.5f)
			player.pos.y -= player.speed*0.5f;

		}
		//camera move left
		if (keystate['q']) {

			beta_move = atan2(player.dir_move.z, player.dir_move.x);
			player.dir_move.x = cos(-0.03f + beta_move);
			player.dir_move.z = sin(-0.03f + beta_move);
			beta_move = atan2(player.dir_move.z, player.dir_move.x);

			rot_move = -beta_move*57.29577f-90.0f ;
		}
		//aiming
		if (keystate['j']) {
			if(tor<0.5f)
			tor += 0.05f;

		}
		if (keystate['m']) {
			if(tor>-0.5f)
			tor -= 0.05f;

		}
		//camera move right

		if (keystate['e']) {

			beta_move = atan2(player.dir_move.z, player.dir_move.x);

			player.dir_move.x = cos(0.03f + beta_move);
			player.dir_move.z = sin(0.03f + beta_move);
			beta_move = atan2(player.dir_move.z, player.dir_move.x);
			rot_move = -(beta_move*57.29577f+90.0f );
		}
		if (keystate['y'])
		{
			beta = atan2(player.dir_view.z, player.dir_view.x);
			player.dir_view.x = cos(-0.03f + beta);
			player.dir_view.z = sin(-0.03f + beta);
			beta = atan2(player.dir_view.z, player.dir_view.x);

			rot = -beta * 57.29577f - 90.0f;
		}
		if (keystate['u'])
		{
			beta = atan2(player.dir_view.z, player.dir_view.x);

			player.dir_view.x = cos(0.03f + beta);
			player.dir_view.z = sin(0.03f + beta);
			beta = atan2(player.dir_view.z, player.dir_view.x);
			rot = -(beta*57.29577f + 90.0f);



		}

		if (keystate['k'])
		{
			r = 1;
			theta = acos(double(player.dir_view.y / r));
			sigma = atan2(player.dir_view.z, player.dir_view.x);
			player.dir_view.x = r * sin(0.02f + theta)*cos(sigma);
			player.dir_view.y = r * cos(0.02f + theta);

			player.dir_view.z = (r*sin(0.02f + theta)*sin(sigma));


		}

		if (keystate['i'])
		{

			r = 1;
			theta = acos(double(player.dir_view.y / r));
			sigma = atan2(player.dir_view.z, player.dir_view.x);
			player.dir_view.x = r * sin(-0.02f + theta)*cos(sigma);
			player.dir_view.y = r * cos(-0.02f + theta);

			player.dir_view.z = r * sin(-0.02f + theta)*sin(sigma);



		}
#pragma endregion


		if (keystate[13]) {
		
			if ( gameState==END)
			{
				minutes = 0;
				hours = 0;
				chances = 5;
				czolgi.clear();
				move_op.clear();
				emitery.clear();
 	
				amb_sky[0] = 0.1f;
				amb_sky[1] = 0.1f;
				amb_sky[2] = 0.1f;
				dif_sky[0] = 0.1f;;
				dif_sky[1] += 0.1f;
				dif_sky[2] += 0.1f;
				y_building = 75.0f;
				time_from_defeat = 0;
				skydome.Set_texture(skyd);
				gameState = START;

			}
		}


		if (captureMouse) {
			float Y = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
			float X = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			float T = acos(player.dir_view.y);
			float G = atan2(player.dir_view.z, player.dir_view.x);
			T -= X* .03f;
			G += Y * .03f;
			player.dir_view.x = sin(T) * cos(G);
			player.dir_view.z = sin(T) * sin(G);
			beta = atan2(player.dir_view.z, player.dir_view.x);
			rot = -beta*57.29577f - 90.0f;

		}

		//sterowanie kamera
		

		if (keystate_special[GLUT_KEY_LEFT]) {
			player.v2 = -player.speed;
			player.pos.x += -player.dir_move.z*player.v2*.1f;
			player.pos.z += player.dir_move.x*player.v2*.1f;
			player.pos.y = teren.linearInterpolation(player.pos.x, player.pos.z) + 0.5f;
		}
		if (keystate_special[GLUT_KEY_RIGHT]) {

			player.v2 = player.speed;
			player.pos.x += -player.dir_move.z*player.v2*.1f;
			player.pos.z += player.dir_move.x*player.v2*.1f;
			player.pos.y = teren.linearInterpolation(player.pos.x, player.pos.z) + 0.5f;

		}
		if (keystate_special[GLUT_KEY_UP]) {
			player.v1 = player.speed;
			player.pos.x += player.dir_move.x * player.v1*.5f;
			player.pos.y = teren.linearInterpolation(player.pos.x, player.pos.z) + 25.5f;
			player.pos.z += player.dir_move.z * player.v1*.5f;
		}
		if (keystate_special[GLUT_KEY_DOWN]) {
			player.v1 = -player.speed;
			player.pos.x += player.dir_move.x * player.v1*.5f;
			player.pos.y = teren.linearInterpolation(player.pos.x, player.pos.z) + 25.5f;
			player.pos.z += player.dir_move.z * player.v1*.5f;
		}

		player.v1 /= 1.12;
		player.v2 /= 1.12;



	}



void OnRender() {


	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, że światło ma wpływ na teksturę; GL_DECAL i GL_REPLACE rysują teksturę tak jak jest
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluPerspective(60.0f, 1, 1, 10000);  // 10000 = backplane
	 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	


	// Ustawienie kamery na podstawie jej stanu przechowywanego w zmiennej player.

	hgt = teren.getHeight(player.pos.x, player.pos.z);

	glTranslatef(0.0f, 10.0f, -9.0f);
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z, // Pozycja kamery
		player.pos.x + player.dir_view.x, player.pos.y, player.pos.z + player.dir_view.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
		0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
		);
	
	//terrain is small and restricted
	if ((player.pos.x  > 249.0f) || (player.pos.x <-249.0f) || (player.pos.z  >249.0f) || (player.pos.z < -249.0f))
		able_to_move = false;
	else able_to_move = true;

	float l0_pos[] = { -1.0f, 1.0f, 1.0f, 0.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb_sky);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_sky);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spe_sky);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);


	glPopMatrix();
#pragma region actions depending on state of game
	if (gameState==LOSE)
	{
 		glDisable(GL_DEPTH_TEST);
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_lose);
		glTranslatef(player.pos.x, player.pos.y-10.0f, player.pos.z);
		glRotatef(rot, 0.0f, 1.0f, 0.0f);
		glScalef(3.1f, 2.8f, 1.0f);

		glCallList(start);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		gameState = END;
	}
	if (gameState == WIN)
	{
 		glDisable(GL_DEPTH_TEST);
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_win);
		glTranslatef(player.pos.x, player.pos.y-10.0f, player.pos.z);
		glRotatef(rot, 0.0f, 1.0f, 0.0f);
		glScalef(3.1f, 2.8f, 1.0f);

		glCallList(start);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		gameState = END;

	}
	if (gameState==END )
	{
		frame++;
 	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, tex_start);
	glTranslatef(player.pos.x, player.pos.y-10.0f, player.pos.z);
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	glScalef(3.1f, 2.8f, 1.0f);

	glCallList(start);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	}
#pragma endregion


	if (chances == 0 )//out of chances
	{
		if(time_from_defeat == 0)
		engine->play2D("Resources\\sounds\\lost.wav");

	
		time_from_defeat++;
	}
	if (time_from_defeat > 30)
	{
	
		gameState = LOSE;
	}
	if (hours > 23)
	{
		gameState = WIN;
	}

	if ((hours > 22)&&(minutes>10))
	{
		if (airplane == false)
		{

			engine->play2D("Resources\\sounds\\airplane.wav");
		}
			if (minutes > 30)
			{
				for (int i = 0; i < czolgi.size(); i++)
				{
					if (czolgi.at(i).czy_zniszczony() == false)
					{
						ParticleSystem *system = new ParticleSystem(czolgi.at(i).get_x(), czolgi.at(i).get_y(), czolgi.at(i).get_z(), texfire, texsmoke);
						emitery.push_back(system);
 
						czolgi.at(i).set_zniszczony(true);
					}
				}
				engine->play2D("Resources\\sounds\\fire_sound.wav");
			}
		
		airplane = true;

		glEnable(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, tex_aircraft);
		float m_amb_a[] = { 1.0f, 1.0f, 1.0f };
		float m_dif_a[] = { 1.0f, 1.0f, 1.0f };
		float m_spe_a[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb_a);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif_a);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe_a);
		for (int i = 0; i < 200; i += 40)
		{
			glPushMatrix();
			glTranslatef(i-20.0f, 50.0f, move_airplane_z);
			glScalef(0.01f, 0.01f, 0.01f);

			glCallList(airplane_a10);
			glPopMatrix();
		}
		move_airplane_z+=5.0f;
		glDisable(GL_TEXTURE_2D);

	}


	if (gameState=START)
	{



		if (frame %2 == 0)
			minutes++;
		if (minutes > 59)
		{
			minutes = 0;
			hours++;
		}
		frame++;
		skydome.Position.x = player.pos.x;
		skydome.Position.y = player.pos.y;
		skydome.Position.z = player.pos.z;
		//glDisable(GL_FOG);
		skydome.Render();



		if (!ifinit)
		{
			init();
			ifinit = true;
		}

		if ((hours > 4) && (hours < 7))
		{
			amb_sky[0] += 0.001f;
			amb_sky[1] += 0.001f;
			amb_sky[2] += 0.001f;
			dif_sky[0] += 0.0005f;;
			dif_sky[1] += 0.0005f;
			dif_sky[2] += 0.0005f;
		}
		if ((hours > 6) && (hours < 21) && (tex_skydome == false))
		{
			amb_sky[0] = 0.5f;
			amb_sky[1] = 0.5f;
			amb_sky[2] = 0.5f;
			dif_sky[0] = 0.3f;
			dif_sky[1] = 0.3f;
			dif_sky[2] = 0.3f;
			spe_sky[0] = 1.0f;
			spe_sky[1] = 1.0f;
			spe_sky[2] = 1.0f;

			skydome.Set_texture(skyd1);
			tex_skydome = true;
		}
		if ((hours > 21) && (tex_skydome == true))
		{
			amb_sky[0] = 0.1f;
			amb_sky[1] = 0.1f;
			amb_sky[2] = 0.1f;
			dif_sky[0] = 0.1f;
			dif_sky[1] = 0.1f;
			dif_sky[2] = 0.1f;
			spe_sky[0] = 0.5f;
			spe_sky[1] = 0.5f;
			spe_sky[2] = 0.5f;

			skydome.Set_texture(skyd);
			tex_skydome = false;
		}


		skydome.Position.x = player.pos.x;
		skydome.Position.y = player.pos.y;
		skydome.Position.z = player.pos.z;
		//glDisable(GL_FOG);
		skydome.Render();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texgrass);

		glCallList(teren.id);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
		float m_amb_bark[] = { 0.1f, 0.5f, 0.1f };
		float m_dif_bark[] = { 0.1f, 0.5f, 0.1f };
		float m_spe_bark[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb_bark);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif_bark);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe_bark);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, texbark);
		for (int i = 0; i < drzewa.size(); i++)
		{

			drzewa[i].Render_pien();

			//sprawdzic czy mozna  w inicie

		}
		//glCallList(trees);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, textank);

		//shows chances in corner
		for (int i = 0; i < chances; i++)
		{
			glPushMatrix();

			glTranslatef(350.0f, 170.0f, -200.0f+i*50.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glScalef(15.0f, 15.0f, 15.0f);
			glCallList(tank_szanse);
			glPopMatrix();
			glPushMatrix();

			glTranslatef(-350.0f, 170.0f, -200.0f + i*50.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glScalef(15.0f, 15.0f, 15.0f);
			glCallList(tank_szanse);
			glPopMatrix();
		}


		float rotxr, rotzr, rotxs, rotzs;
		rotxr = atan2(player.pos.x + player.dir_move.x*0.5, player.pos.z + player.dir_move.z*0.5);
		tank_player.Render(player.pos.x, teren.linearInterpolation(player.pos.x, player.pos.z) , player.pos.z, -90.0f, rot_move, 0.0f, 0.0f, false);
		tank_player.renderCore(player.pos.x, teren.linearInterpolation(player.pos.x, player.pos.z)  , player.pos.z, -90.0f, rot_move, 0.0f, 0.0f, kadlub);
		tank_player.renderTurret(player.pos.x, teren.linearInterpolation(player.pos.x, player.pos.z)  , player.pos.z, -90.0f, rot, 0.0f, 0.0f, 0.0f, wieza);
		glDisable(GL_TEXTURE_2D);

		bool move_tank = false;
		for (int i = 0; i < czolgi.size(); i++)
		{
			if (czolgi.at(i).get_health() > 0)
			{
				move_tank = czolgi.at(i).Kolizja(tank_player.get_x(), tank_player.get_y(), tank_player.get_z(), false);
				if (move_tank)
					czolgi.at(i).set_z(czolgi.at(i).get_z() + 5.0f);
				move_op.at(i) += 1.5f;
			}
			if (czolgi.at(i).get_x() > 300)
			{
				czolgi.erase(czolgi.begin() + i);
				chances--;
				move_op.erase(move_op.begin() + i);
				 
				szanse.push_back(tank_szanse);
 
			}
			if (czolgi.at(i).get_health() < 1)
			{
				if (czolgi.at(i).czy_zniszczony() == false)
				{
					ParticleSystem *system = new ParticleSystem(czolgi.at(i).get_x(), czolgi.at(i).get_y(), czolgi.at(i).get_z(), texfire, texsmoke);
					emitery.push_back(system);
 					engine->play2D("Resources\\sounds\\fire_sound.wav");

					czolgi.at(i).set_zniszczony(true);
				}
				czolgi.at(i).increase_czas();
				if (czolgi.at(i).getTime() > 100)
				{


					czolgi.erase(czolgi.begin() + i);
					move_op.erase(move_op.begin() + i);
				}
			}
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


		glBindTexture(GL_TEXTURE_2D, tex_tree);
		//glCallList(leaves);


	
		for (int i = 0; i < drzewa.size(); i++)
		{

			drzewa[i].Render_liscie();
		}


		for (int i = 0; i < emitery.size(); i++)
		{
			if (emitery.at(i)->getTime() < 100)
			{
				emitery.at(i)->draw();
				emitery.at(i)->update(frame);
				emitery.at(i)->add(frame);
			}
			else if (emitery.at(i)->getTime() > 100)
			{
				delete emitery.at(i);
				emitery.erase(emitery.begin() + i);
			}
	

		}
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		if ((frame % 110 == 0)||(frame%1010==0))
		{
			Tank t;
			float m = -200.0f;
			move_op.push_back(m);
			t.set_z((rand() % 500) - 250);
			engine->play2D("Resources\\sounds\\tank_moving.wav");

			czolgi.push_back(t);
		}
		float m_amb1[] = { 0.5f, 0.5f, 0.5f };
		float m_dif1[] = { 0.5f, 0.5f, 0.5f };
		float m_spe1[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe1);
		if (frame % 20 == 0)
			able_to_shoot = true;
		for (int i = 0; i < czolgi.size(); i++)
		{
			float m_temp = move_op.at(i);
			float z_temp = czolgi.at(i).get_z();
			glEnable(GL_TEXTURE_2D);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture(GL_TEXTURE_2D, texkadlub);
			czolgi.at(i).Render(m_temp, teren.linearInterpolation(m_temp, z_temp), z_temp, -180.0f, 0.0f, 0.0f, 0.0f, true);
			czolgi.at(i).render_kadlub(m_temp, teren.linearInterpolation(m_temp, z_temp), z_temp, -180.0f, 0.0f, 0.0f, 0.0f, kadlub);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture(GL_TEXTURE_2D, texwieza);
			czolgi.at(i).render_wieza(m_temp, teren.linearInterpolation(m_temp, z_temp), z_temp, -180.0f, 0.0f, 0.0f, 0.0f, 10.0f*i, wieza);
			glDisable(GL_TEXTURE_2D);
		}


		bool pocisk = false;
		for (int i = 0; i < pociski.size(); i++)
		{
			pociski[i].fire(rot, tor * 2);
			
			for (int j = 0; j < czolgi.size(); j++)
			{
				pocisk = czolgi.at(j).Kolizja(pociski.at(i).getx(), pociski.at(i).gety(), pociski.at(i).getz(), true);
				if (pocisk == true)
				{
					pociski.erase(pociski.begin() + i);
					engine->play2D("Resources\\sounds\\explosion.wav");

					break;

				}
			}
			if (pocisk == false)
			{
				if ((pociski[i].getx()>350.0f) || (pociski[i].getx() < -350.0f) || (pociski[i].getz() < -350.0f) || (pociski[i].getz() < -350.0f))
					 pociski.erase(pociski.begin() + i);
			}
		}

		for (int i = 0; i < pociski.size(); i++)
		{
			for (int j = 0; j < drzewa.size(); j++)
			{
				if (drzewa.at(j).get_przewrocone() == false)
				{
					pocisk = drzewa.at(j).Kolizja(pociski.at(i).getx(), pociski.at(i).gety(), pociski.at(i).getz());
					if (!pocisk == true)
					{
						pociski.erase(pociski.begin() + i);
						drzewa.at(j).set_rot(-90.0f);
 						break;
					}
				}
			}
		}
		 

 
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building1);
		glPushMatrix();

		glTranslatef(350.0f, y_building, -280.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(8.0f, 6.0f, 3.0f);
	 
		if ((time_from_defeat > 0)&&(time_from_defeat%5==0))
		{
			y_building -= 5.0f;
			ParticleSystem *system1 = new ParticleSystem(330.0f, y_building+25.0f, -220.0f+time_from_defeat, texfire, texsmoke);
			emitery.push_back(system1);
		}
		glCallList(building1);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building2);
		glPushMatrix();

		glTranslatef(350.0f, y_building, -140.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(6.0f, 6.0f, 6.0f);
		 
		if ((time_from_defeat > 0) && (time_from_defeat % 5 == 0))
		{
			ParticleSystem *system2 = new ParticleSystem(330.0f, y_building+25.0f, -140.0f+time_from_defeat, texfire, texsmoke);
			emitery.push_back(system2);
		}
		glCallList(building2);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building3);
		glPushMatrix();

		glTranslatef(350.0f, y_building, -45.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(6.0f, 6.0f, 6.0f);
		 
		if ((time_from_defeat > 0) && (time_from_defeat % 5 == 0))
		{
			ParticleSystem *system3 = new ParticleSystem(330.0f, y_building+25.0f, -40.0f+time_from_defeat, texfire, texsmoke);
			emitery.push_back(system3);
		}
		glCallList(building3);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building4);
		glPushMatrix();

		glTranslatef(350.0f, y_building, 45.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(6.0f, 6.0f, 6.0f);

		glCallList(building4);
		glPushMatrix();
		if ((time_from_defeat > 0) && (time_from_defeat % 5 == 0))
		{
			ParticleSystem *system4 = new ParticleSystem(330.0f, y_building + 25.0f, 45.0f + time_from_defeat, texfire, texsmoke);
			emitery.push_back(system4);
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building1);
		glPushMatrix();
		if ((time_from_defeat > 0) && (time_from_defeat % 5 == 0))
		{
			ParticleSystem *system4 = new ParticleSystem(330.0f, y_building+25.0f, -70.0f + time_from_defeat, texfire, texsmoke);
			emitery.push_back(system4);
		}
		glTranslatef(350.0f, y_building, -70.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(8.0f, 6.0f, 3.0f);

		glCallList(building1);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building2);
		glPushMatrix();

		glTranslatef(350.0f, y_building, 70.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(6.0f, 6.0f, 6.0f);
		if ((time_from_defeat > 0) && (time_from_defeat % 5 == 0))
		{
			ParticleSystem *system5 = new ParticleSystem(330.0f, y_building+25.0f, 70.0f + time_from_defeat, texfire, texsmoke);
			emitery.push_back(system5);
		}
		glCallList(building2);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building3);
		glPushMatrix();

		glTranslatef(350.0f, y_building, 170.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(6.0f, 6.0f, 6.0f);
		if ((time_from_defeat > 0) && (time_from_defeat % 5 == 0))
		{
			ParticleSystem *system6 = new ParticleSystem(330.0f, y_building+25.0f, 170.0f + time_from_defeat, texfire, texsmoke);
			emitery.push_back(system6);
		}
		glCallList(building3);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, tex_building4);
		glPushMatrix();

		glTranslatef(350.0f, y_building, 265.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(6.0f, 6.0f, 6.0f);
		if ((time_from_defeat > 0) && (time_from_defeat % 5 == 0))
		{
			ParticleSystem *system7 = new ParticleSystem(330.0f, y_building+25.0f, 200.0f + time_from_defeat, texfire, texsmoke);
			emitery.push_back(system7);
		}
		glCallList(building4);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		int k = 0;

		//celownik

	 
		glBegin(GL_LINES);
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(player.pos.x + player.dir_view.x*15.0f - 1.5f, player.pos.y-9.0f + player.dir_view.y*4.0f-3.0f+2*tor, player.pos.z + player.dir_view.z*15.0f - 0.5f);
		glVertex3f(player.pos.x + player.dir_view.x*15.0f + 1.5f, player.pos.y-9.0f + player.dir_view.y*4.0f -3.0f+2*tor, player.pos.z + player.dir_view.z*15.0f + 0.5f);
		glRotatef(rot, 0.0f, 1.0f, 0.0f);
		glPopMatrix();
		glEnd();
		glBegin(GL_LINES);
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(player.pos.x + player.dir_view.x*15.0f, player.pos.y-9.0f + player.dir_view.y*4.0f - 4.5f+2*tor, player.pos.z + player.dir_view.z*15.0f);
		glVertex3f(player.pos.x + player.dir_view.x *15.0f, player.pos.y-9.0f + player.dir_view.y *4.0f -1.5f+2*tor, player.pos.z + player.dir_view.z*15.0f);

		glPopMatrix();
		glEnd();
		
		
		float m_amb[] = { 0.0f, 0.0f, 0.0f };
		float m_dif[] = { 0.0f, 0.0f, 0.0f };
		float m_spe[] = { 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		 

		std::string positionminutesText;
		if (minutes<10)
			positionminutesText = "0"+std::to_string(minutes);
		else
			positionminutesText =  std::to_string(minutes);

		std::string positionhoursText;
		if(hours<10)
		  positionhoursText = "0"+std::to_string(hours);
		else
			  positionhoursText =  std::to_string(hours);

		std::string dwukropek = ":";

		teren.drawText(positionhoursText.data(), positionhoursText.size(), 690, 550);
		teren.drawText(dwukropek.data(), dwukropek.size(), 724, 555);
		teren.drawText(positionminutesText.data(), positionminutesText.size(), 730, 550);
		

#pragma region Sciany

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texhft);
		glBegin(GL_QUADS);


		{
			float m_amb[] = { 1.0f, 1.0f, 1.0f };
			float m_dif[] = { 1.0f, 1.0f, 1.0f };
			float m_spe[] = { 0.0f, 0.0f, 0.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f);

			glVertex3f(player.pos.x - 5.0f, 1.0f, player.pos.z - 1955.0f);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);

			glVertex3f(player.pos.x - 5.0f, -1.0f, player.pos.z - 1955.0f);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);

			glVertex3f(player.pos.x + 5.0f, -1.0f, player.pos.z - 1955.0f);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f);

			glVertex3f(player.pos.x + 5.0f, 1.0f, player.pos.z - 1955.0f);
		}
		glDisable(GL_TEXTURE_2D);
		glEnd();
		
	#pragma endregion
 


	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	
 }

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, 1.0f, 10000.0f);
}
void DrawString(float x, float y, const char * string)
{
	glRasterPos2d(x, y);

	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}

struct SFace {
	int v[3];
	int n[3];
	int t[3];
};
GLuint LoadObj(char * file) {

	FILE * fp = fopen(file, "r");

	if (fp == NULL) {
		printf("ERROR: Cannot read model file \"%s\".\n", file);
		return -1;
	}

	std::vector<vec3> * v = new std::vector<vec3>();
	std::vector<vec3> * n = new std::vector<vec3>();
	std::vector<vec3> * t = new std::vector<vec3>();
	std::vector<SFace> * f = new std::vector<SFace>();

	char buf[128];

	while (fgets(buf, 128, fp) != NULL) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 * vertex = new vec3();
			sscanf(buf, "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			v->push_back(*vertex);
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 * vertex = new vec3();
			sscanf(buf, "vt %f %f", &vertex->x, &vertex->y);
			t->push_back(*vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 * vertex = new vec3();
			sscanf(buf, "vn %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			n->push_back(*vertex);
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace * face = new SFace();
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face->v[0], &face->t[0], &face->n[0],
				&face->v[1], &face->t[1], &face->n[1],
				&face->v[2], &face->t[2], &face->n[2]
				);
			f->push_back(*face);
		}
	}

	fclose(fp);

	GLuint dlId;
	dlId = glGenLists(1);
	glNewList(dlId, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < f->size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			vec3 * cv = &(*v)[((*f)[i].v[j] - 1)];
			vec3 * ct = &(*t)[((*f)[i].t[j] - 1)];
			vec3 * cn = &(*n)[((*f)[i].n[j] - 1)];
			glTexCoord2f(ct->x, ct->y);
			glNormal3f(cn->x, cn->y, cn->z);
			glVertex3f(cv->x, cv->y, cv->z);
		}
	}
	glEnd();
	glEndList();

	delete v;
	delete n;
	delete t;
	delete f;

	return dlId;

}

GLuint LoadTexture(char * file, int magFilter, int minFilter) {

	// Odczytanie bitmapy
	Bitmap *tex = new Bitmap();
	if (!tex->loadBMP(file)) {
		printf("ERROR: Cannot read texture file \"%s\".\n", file);
		return -1;
	}

	// Utworzenie nowego id wolnej tekstury
	GLuint texId;
	glGenTextures(1, &texId);

	// "Bindowanie" tekstury o nowoutworzonym id
	glBindTexture(GL_TEXTURE_2D, texId);

	// Określenie parametrów filtracji dla tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powiększana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Filtracja, gdy tekstura jest pomniejszana

																	  // Wysłanie tekstury do pamięci karty graficznej zależnie od tego, czy chcemy korzystać z mipmap czy nie
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		// Automatyczne zbudowanie mipmap i wysłanie tekstury do pamięci karty graficznej
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height,GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}
	else {
		// Wysłanie tekstury do pamięci karty graficznej 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}

	// Zwolnienie pamięci, usunięcie bitmapy z pamięci - bitmapa jest już w pamięci karty graficznej
	delete tex;

	// Zwrócenie id tekstury
	return texId;
}

GLuint LoadTextureTga(char * file, int magFilter, int minFilter) {

	tgaInfo *tex = tgaLoad(file);
	if (tex->status<0) {
		printf("ERROR: Cannot read texture file \"%s\".\n", file);
		return -1;
	}

	// Utworzenie nowego id wolnej tekstury
	GLuint texId;
	glGenTextures(1, &texId);

	// "Bindowanie" tekstury o nowoutworzonym id
	glBindTexture(GL_TEXTURE_2D, texId);

	// Określenie parametrów filtracji dla tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powiększana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Filtracja, gdy tekstura jest pomniejszana

																  // Wysłanie tekstury do pamięci karty graficznej zależnie od tego, czy chcemy korzystać z mipmap czy nie
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		// Automatyczne zbudowanie mipmap i wysłanie tekstury do pamięci karty graficznej

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height, GL_RGBA, GL_UNSIGNED_BYTE, tex->imageData);
	}
	else {
		// Wysłanie tekstury do pamięci karty graficznej 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->imageData);
	}

	// Zwolnienie pamięci, usunięcie bitmapy z pamięci - bitmapa jest już w pamięci karty graficznej
	delete tex;

	// Zwrócenie id tekstury
	return texId;
}
