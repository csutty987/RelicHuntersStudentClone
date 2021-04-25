#pragma once
#include <SFML\Graphics.hpp>
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/Collider2D.h"
#include "../GameData/GameDataManager.h"


struct SpritesheetDef;

class TileMap :
	public GameObject,
	public GameDataManager,
	public sf::Drawable,
	public sf::Transformable,
	public Collider2D

{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
public:


	TileMap();
	~TileMap();
	
	void Initialise() override;
	void Update() override;
	void GetPosition(int& x, int& y) override;

	//Used
	bool CollidesWith(Collider2D* pCollider2D) override;
	bool CollidesWith(BoxCollider2D* pBoxCollider2D) override;

	//Collision handling
	void OnCollision(Collider2D* pCollider2D) override;
	
	//Unused
	bool CollidesWith(CircleCollider2D* pCircleCollider2D) override;
	bool CollidesWith(TileMap* pCollider2D) override;
	
	virtual CollisionType GetCollisionType() override { return CollisionType::E_Floor; };

	bool LoadFromSpritesheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, unsigned int width, unsigned int height);
	bool LoadFromFile(std::string pfile);

	int TileIndexAtPosition(int TileX, int TileY);

	int cellwidth;
	int cellheight;

	int* pMap;

	std::vector<int> tiles;

private:

	sf::VertexArray m_Vertices;
	sf::Texture* m_pTileset;

	

	int mapWidth;
	int mapHeight;
};

