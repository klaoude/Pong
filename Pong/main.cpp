#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Barre.h"
#include "Balle.h"

using namespace std;

//SDL var
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* texte = NULL;
SDL_Surface* texte2 = NULL;
SDL_Surface* scoretxt = NULL;
SDL_Surface* nametxt = NULL;
SDL_Surface* qname = NULL;
SDL_Surface* soloText = NULL;
SDL_Surface* multiText = NULL;
SDL_Rect position;
SDL_Rect scorePos;
SDL_Rect namePos;

//TFF Var
TTF_Font* police;
TTF_Font* police2;
TTF_Font* police3;
SDL_Color couleurBlanc = { 255, 255, 255 };
SDL_Color couleurRouge = { 255, 0, 0 };

//class
Barre* player;
Barre* other;
Balle* balle;

//Clasic var
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BORDER = 10;
const int BARRE_H = 40;
const int BARRE_W = 10;

bool quit = false; //Controle de la boucle principale

bool colision, colisionOther, CenableL = false, CenableR = false; //bool colision
bool Rmenu = false; //bool de l'afichage des resultats
bool jeu = false; //bool de la boucle du jeu
bool Cmenu = true; //bool de l'afichage du menu
bool start; //bool du score
bool boolname; // bool de la boucle pour choisir le nom
bool writeScore; //bool qui dit si on ecrit le nom du joueur ou pas

int score;
Uint32 oldballeid;
Uint32 newballeid;

string scorestr;
const char* scorechar;

string pseudo;

string pathFichierScore = ("score.txt");


//Fonction
void doVars();
void modMenu();
void jeux();
void pause();
void changeColor(int yolo, int yola, int yala);
bool check_collision(SDL_Rect A, SDL_Rect B);
void resultMenu();
void menu();
void endGame();
string getName();

int main(int argc, char *argv[])
{
	/*ofstream fichierscore(pathFichierScore.c_str());
	if (!fichierscore)
		printf("erreur fichier score.txt");*/	

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	if (TTF_Init() == -1)
		printf("erreur tff");

	doVars();

	gWindow = SDL_CreateWindow("Pong", 20, 20, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	gScreenSurface = SDL_GetWindowSurface(gWindow);

	while (!quit)
	{
		if (pseudo == "")
		{
			pseudo = getName();
			cout << pseudo << endl;
		}
		changeColor(0, 0, 0);

		if (Rmenu && !quit)
			resultMenu();

		if (Cmenu && !quit)
			menu();

		if (jeu)
		{
			player = new Barre(10, SCREEN_HEIGHT / 2 - BARRE_H / 2 - SCREEN_BORDER -100, gScreenSurface, 10);
			other = new Barre(SCREEN_WIDTH - SCREEN_BORDER - 10, SCREEN_HEIGHT / 2 - SCREEN_BORDER + BARRE_H, gScreenSurface, 9);
			balle = new Balle(15, SCREEN_HEIGHT / 2 - SCREEN_BORDER + BARRE_H, gScreenSurface);
		}

		while (jeu && !quit)
			jeux();
	}

	pause();

	TTF_CloseFont(police);
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void doVars()
{
	police = TTF_OpenFont("SnackerComic.ttf", 50);
	if (!police)
	{
		cout << "fucking ttf bug :( - " << TTF_GetError() << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	police2 = TTF_OpenFont("SnackerComic.ttf", 30);
	if (!police2)
	{
		cout << "fucking ttf bug :( - " << TTF_GetError() << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	police3 = TTF_OpenFont("ttf/BMgermar.ttf", 50);
	if (!police3)
	{
		cout << "fucking ttf bug :( - " << TTF_GetError() << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void modMenu()
{
	changeColor(0, 0, 0);

	soloText = TTF_RenderText_Solid(police, "SinglePlayer", couleurBlanc);
	multiText = TTF_RenderText_Solid(police, "MultiPlayer", couleurBlanc);
}

void resultMenu()
{
	changeColor(0, 0, 0);
	
	texte = TTF_RenderText_Solid(police, "Your score is : ", couleurBlanc);	
	texte2 = TTF_RenderText_Solid(police2, "Rejouer : Press Enter !", couleurRouge);

	position.x = SCREEN_WIDTH / 2 - texte->w / 2; position.y = 10;
	SDL_BlitSurface(texte, NULL, gScreenSurface, &position);

	position.x = SCREEN_WIDTH / 2 - texte2->w / 2; position.y = SCREEN_HEIGHT / 2 - 50;
	SDL_BlitSurface(scoretxt, NULL, gScreenSurface, &position);

	position.x = SCREEN_WIDTH / 2 - texte2->w / 2; position.y = SCREEN_HEIGHT / 2 - 100;
	SDL_BlitSurface(texte2, NULL, gScreenSurface, &position);

	SDL_UpdateWindowSurface(gWindow);

	while (Rmenu)
	{
		SDL_Event e;

		while (!SDL_PollEvent(&e))
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RETURN:
				Rmenu = false;
				jeu = true;				
				break;
			}
		}
		SDL_Delay(33);
	}
	SDL_FreeSurface(texte);
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(scoretxt);
}

void menu()
{	
	changeColor(0, 0, 0);

	texte = TTF_RenderText_Solid(police, "Pong !!!", couleurBlanc);
	texte2 = TTF_RenderText_Solid(police2, "Jouer : Press Enter !", couleurRouge);

	position.x = SCREEN_WIDTH / 2 - texte->w / 2; position.y = 10;
	SDL_BlitSurface(texte, NULL, gScreenSurface, &position);
	
	position.x = SCREEN_WIDTH / 2 - texte2->w / 2; position.y = SCREEN_HEIGHT / 2 - 50;
	SDL_BlitSurface(texte2, NULL, gScreenSurface, &position);

	SDL_UpdateWindowSurface(gWindow);
	
	while (Cmenu)
	{
		SDL_Event e;

		while (!SDL_PollEvent(&e))
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RETURN:
				Cmenu = false;
				jeu = true;
				break;
			}
		}
		SDL_Delay(33);
	}
	SDL_FreeSurface(texte);
	SDL_FreeSurface(texte2);
}

void jeux()
{
	player->move();

	//Anti Bord Player
	if (player->getRect().y >= SCREEN_HEIGHT - SCREEN_BORDER - player->getRect().h)
		player->setRecty(SCREEN_HEIGHT - SCREEN_BORDER - player->getRect().h);
	if (player->getRect().y <= SCREEN_BORDER)
		player->setRecty(SCREEN_BORDER);

	colision = check_collision(player->getRect(), balle->getRect());
	colisionOther = check_collision(other->getRect(), balle->getRect());

	if (colision){ CenableR = true; CenableL = false;}
	if (colisionOther){ CenableL = true; CenableR = false;}
	if (CenableR)balle->moveR();
	if (CenableL)balle->moveL();

	other->ia(balle->getRect().y);

	changeColor(0, 0, 0);
	player->render(gScreenSurface);
	other->render(gScreenSurface);
	balle->render(gScreenSurface);		

	if (balle->getRect().x <= 5 || balle->getRect().x >= 630)
	{
		endGame();
		return;
	}

	if (start)
		score++;
	
	scorestr = static_cast<ostringstream*>(&(ostringstream() << score))->str();
	scorechar = scorestr.c_str();

	scoretxt = TTF_RenderText_Solid(police3, scorechar, couleurBlanc);

	scorePos.x = SCREEN_WIDTH / 2 - scoretxt->w / 2;
	scorePos.y = SCREEN_HEIGHT / 2 - 50;
	SDL_BlitSurface(scoretxt, NULL, gScreenSurface, &scorePos);

	SDL_UpdateWindowSurface(gWindow);

	SDL_Delay(33);
}

bool check_collision(SDL_Rect A, SDL_Rect B)
{
	
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || rightA <= leftB || leftA >= rightB)
		return false;
	else
		start = true;
	return true;
}

void endGame()
{
	delete player;
	delete other;
	delete balle;

	cout << "endgame" << endl;

	//Free surface
	//SDL_FreeSurface(scoretxt);

	//write score in file
	string const file("../Pong/score.txt");
	ifstream checkfile(file.c_str());
	//if file exist
	if (checkfile)
	{
		//check if player is already in score
		string line;
		while (getline(checkfile, line, ' '))
		{
			if (line == pseudo)
			{
				cout << "[DEBUG] line == pseudo" << endl;
				writeScore = false;
				break;
			}
			else
			{
				writeScore = true;
				cout << "/" << line << "/ | " << "/" << pseudo << "/" << endl;
			}				
		}

		ofstream flux(file.c_str(), ios::app);

		if (flux && writeScore)
		{
			flux << pseudo << " : " << score << endl;;
		}
	}
	else
	{
		ofstream flux(file.c_str());
		flux << "High Score" << endl << "--------------" << endl;
		checkfile.close();
	}
	

	//set Vars
	jeu = false;
	Cmenu = false;
	Rmenu = true;
	colision = false;
	colisionOther = false;
	CenableL = false;
	CenableR = false;
	start = false;
	score = NULL;
}

void changeColor(int yolo, int yola, int yala)
{
	SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, yolo, yola, yala));
	SDL_UpdateWindowSurface(gWindow);
}

void pause()
{
	int continuer = 1;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
		}
	}
}

string getName()
{
	changeColor(0, 0, 0);

	boolname = true;

	string name;

	while( boolname )
	{
		const char* namechar = name.c_str();
		SDL_Event e;

		nametxt = TTF_RenderText_Solid(police3, namechar, couleurBlanc);
		namePos.x = SCREEN_HEIGHT / 2;
		namePos.y = SCREEN_WIDTH / 2;
		SDL_BlitSurface(nametxt, NULL, gScreenSurface, &namePos);

		qname = TTF_RenderText_Solid(police3, "Pseudo = ", couleurBlanc);
		namePos.y = 0 + 50;
		SDL_BlitSurface(qname, NULL, gScreenSurface, &namePos);

		SDL_UpdateWindowSurface(gWindow);

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						case SDLK_a:
							name += "a";
							break;
						case SDLK_b:
							name += "b";
							break;
						case SDLK_c:
							name += "c";
							break;
						case SDLK_d:
							name += "d";
							break;
						case SDLK_e:
							name += "e";
							break;
						case SDLK_f:
							name += "f";
							break;
						case SDLK_g:
							name += "g";
							break;
						case SDLK_h:
							name += "h";
							break;
						case SDLK_i:
							name += "i";
							break;
						case SDLK_j:
							name += "j";
							break;
						case SDLK_k:
							name += "k";
							break;
						case SDLK_l:
							name += "l";
							break;
						case SDLK_m:
							name += "m";
							break;
						case SDLK_n:
							name += "n";
							break;
						case SDLK_o:
							name += "o";
							break;
						case SDLK_p:
							name += "p";
							break;
						case SDLK_q:
							name += "q";
							break;
						case SDLK_r:
							name += "r";
							break;
						case SDLK_s:
							name += "s";
							break;
						case SDLK_t:
							name += "t";
							break;
						case SDLK_u:
							name += "u";
							break;
						case SDLK_v:
							name += "v";
							break;
						case SDLK_w:
							name += "w";
							break;
						case SDLK_x:
							name += "x";
							break;
						case SDLK_y:
							name += "y";
							break;
						case SDLK_z:
							name += "z";
							break;
						case SDLK_ESCAPE:
							changeColor(0, 0, 0);
							if (name.size() > 0)
								name.erase(name.size() - 1);
							break;
						case SDLK_RETURN:
							if (name.size() >= 3)
								boolname = false;
							break;
						}	
					break;
			}
		}		
		SDL_Delay(33);
	}
	SDL_FreeSurface(nametxt);
	SDL_FreeSurface(qname);
	return name;
}