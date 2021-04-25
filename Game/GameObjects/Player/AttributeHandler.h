#ifndef _ATTRIBUTE_HANDLER__H
#define _ATTRIBUTE_HANDLER__H

#include <string>

class AttributeHandler

{
public:
	AttributeHandler();
	~AttributeHandler();

	void Initialise();
	void Update();

	void ScoreHandler(int pScore);

	std::string ScoreString;

	int ScoreValue;

	void UpdateScoreHandler();

	bool isDead = false;

	bool GameRestart = false;

private:
	
};
#endif

