#include "Barre.h"
#include "Balle.h"
#include <iostream>
#include <SDL.h>

Uint32 Barre::currentId = 0;

Barre::Barre()
{
	this->id = currentId;
	Barre::currentId++;
	this->barre = NULL;
	barre = SDL_LoadBMP("images/barre.bmp");
}

Barre::Barre(int x, int y, SDL_Surface* surface, int speed) : Barre()
{
	this->rect.x = x;
	this->rect.y = y;
	this->speed = speed;
}

Barre::~Barre()
{
	this->rect.x = -100;
	this->rect.y = -100;
	SDL_FreeSurface(barre);
}

void Barre::move()
{
	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP]) {
		this->rect.y -= this->speed;
	}
	if (state[SDL_SCANCODE_DOWN]){
		this->rect.y += this->speed;
	}

	/*SDL_Event e;

	SDL_PollEvent(&e);
	if (e.type)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			std::cout << "" << std::endl;
			this->rect.y -= this->speed;
			break;

		case SDLK_DOWN:
			std::cout << "" << std::endl;
			this->rect.y += this->speed;
			break;
		}
	}*/
}

void Barre::render(SDL_Surface* surface)
{
	SDL_BlitSurface(this->barre, NULL, surface, &this->rect);
}

SDL_Rect Barre::getRect(){ return this->rect; }

void Barre::setRectx(int x){ this->rect.x = x; }
void Barre::setRecty(int y){ this->rect.y = y; }

void Barre::ia(int y)
{
	this->rect.y = y;
}