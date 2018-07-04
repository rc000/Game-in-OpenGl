// Deklaracje funkcji u¿ywanych jako obs³uga zdarzeñ GLUTa.
#include "Terrain.h"
 #include "Tank.h"
#include "Skydome.h"
#include"Bullet.h"
#include <vector>
#include"Tree.h"
#include "ParticleSystem.h"

void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnMouseMove(int, int);
void mouseClicks(int button, int state, int x, int y);
void OnKeyUp(unsigned char, int, int);
void OnSpecialKeyPress(int, int, int);
void OnSpecialKeyDown(int, int, int);
void init();
void mouseWheel(int, int, int, int);
GLUquadric *kolo;
GLuint tex_fire;
GLuint tex_tree;
ParticleSystem *system1;

void OnSpecialKeyUp(int, int, int);
void OnTimer(int);
GLuint LoadObj(char * file);
GLuint LoadTexture(char * file, int magFilter, int minFilter);
GLuint LoadTextureTga(char * file, int magFilter, int minFilter);
void DrawString(float x, float y, const char * string);


// Uniwersalna struktura reprezentuj¹ca trójwymiarowy wektor.
// Mo¿e s³u¿yæ do przechowywania po³o¿enia punktu, wspó³rzêdnych wektora itp.
// Wskazane jest rozszerzenie tej struktury o metody i operatory pozwalaj¹ce
// na wykonywanie operacji na wektorach - to na pewno siê przyda w przysz³oœci.

struct vec3 {
	float x, y, z;
};


// Struktura pozwalaj¹ca na przechowanie aktualnego stanu kamery.
struct SCameraState {
	vec3 pos; // pozycja kamery
	vec3 dir_view; // kierunek patrzenia (wektor jednostkowy)
	vec3 dir_move;
	float speed; // mno¿nik zmian pozycji - "szybkoœæ" ruchów kamery
	float v1, v2;
};
enum GameState {
	WIN,
	LOSE,
	START,
	END
 };
GameState gameState;

// Zmienna przechowuj¹ca aktualny stan kamery.
SCameraState player;
vec3 LightPos; // pozycja zrodla swiatla
Terrain teren;
 GLuint kadlub;
GLuint gasiennica;
GLuint wieza;
GLuint tank_bullet;
GLuint building1,building2,building3,building4,cross,droga;
GLuint tex_building1, tex_building2, tex_building3, tex_building4, tex_cross, tex_droga;
 GLuint pien;
GLuint airplane_a10;
GLuint tex_aircraft;
GLuint czolg;

GLuint liscie;
GLuint texfire, texsmoke;
GLuint skyd,skyd1;
CSkydome skydome;
GLuint texbark;
GLuint textank;
GLuint texgrass;
GLuint texwater;
GLuint texcity;
GLuint texkadlub;
GLuint texwieza;
GLuint trees;
GLuint leaves;
Tank tank1;
Tank tank_player;
GLuint start;
GLuint tex_start;
GLuint tex_win;
GLuint tex_lose;
GLuint texsky;
GLuint texhft;
GLuint texhlf;
GLuint texhrt;
vector <Bullet>pociski;
vector <ParticleSystem*>emitery;

vector <Tree>drzewa;
vector <Tank>czolgi;
vector <GLuint>szanse;
GLuint tank_szanse;
vector<float>move_op;
int tab[20];
 

