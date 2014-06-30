#pragma once
#include <SDL.h>

class Barre
{
public:
	Barre();
	Barre(int x, int y, SDL_Surface* surface, int speed);
	~Barre();
	void move();
	void render(SDL_Surface* surface);

	SDL_Rect getRect();
	void setRectx(int x);
	void setRecty(int y);
	void ia(int y);
private:
	static Uint32 currentId;
	Uint32 id;
	int speed;
	SDL_Surface* barre;
	SDL_Rect rect;
};