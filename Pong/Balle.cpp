#include "Balle.h"
#include <iostream>
#include <SDL.h>

Uint32 Balle::currentId = 0;

int incrementXBalle = 10;
int incrementYBalle = 10;

Balle::Balle()
{
	this->id = currentId;
	Balle::currentId++;
	this->balle = NULL;
	balle = SDL_LoadBMP("images/balle.bmp");
}

Balle::Balle(int x, int y, SDL_Surface* surface) : Balle()
{
	this->rect.x = x;
	this->rect.y = y;
}

Balle::~Balle()
{
	SDL_FreeSurface(balle);
}

void Balle::render(SDL_Surface* surface)
{
	SDL_BlitSurface(this->balle, NULL, surface, &this->rect);
}

void Balle::moveR()
{
	this->rect.x += incrementXBalle;
	if (this->getRect().x > 640 || this->getRect().x < 0)
		incrementXBalle = -incrementXBalle;

	this->rect.y -= incrementYBalle;
	if (this->getRect().y >= 460 || this->getRect().y <= 20)
		incrementYBalle = -incrementYBalle;
}

void Balle::moveL()
{
	this->rect.x -= incrementXBalle;
	if (this->getRect().x > 640 || this->getRect().x < 0)
		incrementXBalle = -incrementXBalle;

	this->rect.y -= incrementYBalle;
	if (this->getRect().y >= 460 || this->getRect().y <= 5)
		incrementYBalle = -incrementYBalle;
}

void Balle::moveDiago()
{
	this->rect.x += incrementXBalle;
	if (this->getRect().x > 620 || this->getRect().x == 0)
		incrementXBalle = -incrementXBalle;

	this->rect.y += incrementYBalle;
	if (this->getRect().y > 460 || this->getRect().y == 5)
		incrementYBalle = -incrementYBalle;
}

Uint32 Balle::getId(){ return this->currentId; }
SDL_Rect Balle::getRect(){ return this->rect; }