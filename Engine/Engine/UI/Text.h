#ifndef _TEXT_H
#define _TEXT_H

#include "SFML\Graphics.hpp"

class Text
{
public:

	Text();
	~Text();

	void Initialise(const char* filename, std::string text, int size, int posX, int posY, sf::Color color, bool isUIObject);
	const sf::Text& GetText() { return m_Text; }

private:

	sf::Text m_Text;
	bool m_Initialised;

};

#endif
