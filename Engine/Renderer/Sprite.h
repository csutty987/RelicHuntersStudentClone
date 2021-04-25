#ifndef _SPRITE_H
#define _SPRITE_H

#include <SFML/Graphics.hpp>

class TextureManager;

class Sprite : public sf::Sprite
{
public: 
	Sprite();
	~Sprite();

	void Initialise(const char* filename, const int x, const int y, const int sizeX, const int sizeY, bool isUIObject);

private:

	bool m_bInitialised;
	bool m_isUIObject;
};

#endif
