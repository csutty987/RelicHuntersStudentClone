#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise() = 0;
	virtual void Update() = 0;

	virtual void GetPosition(int& x, int & y) = 0;

private:

};

#endif
