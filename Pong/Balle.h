#pragma once
#include <SDL.h>
class Balle
{
public:
	Balle();
	Balle(int x, int y, SDL_Surface* surface);
	~Balle();
	void render(SDL_Surface* surface);
	void moveR();
	void moveL();
	void moveDiago();

	Uint32 getId();
	SDL_Rect getRect();
private:
	static Uint32 currentId;
	Uint32 id;
	SDL_Surface* balle;
	SDL_Rect rect;
};