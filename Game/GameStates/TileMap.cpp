#include "TileMap.h"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>



#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/SpritesheetDef.h"
#include "../GameObjects/Player/Player.h"

inline void splitString(std::string pstring, std::vector<std::string>& plist, char pdelim = ' ')
{
	std::istringstream is(pstring);
	std::string part;
	while (std::getline(is, part, pdelim))
	{
		plist.push_back(part);
	}
}

TileMap::TileMap()
{
	
}

TileMap::~TileMap()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void TileMap::Initialise()
{
	
}

void TileMap::Update()
{
	
}

void TileMap::GetPosition(int& x, int& y)
{
	
}

bool TileMap::CollidesWith(Collider2D * pCollider2D)
{
	return pCollider2D->CollidesWith(this);
}

bool TileMap::CollidesWith(BoxCollider2D * pBoxCollider2D)
{
	Player* tplayer = dynamic_cast<Player*>(pBoxCollider2D);
	bool iscolliding = false;
	if (tplayer)
	{
		int x, y;
		tplayer->GetPosition(x, y);
		int tilenum = TileIndexAtPosition(x, y);
		iscolliding = tilenum > 1;
		if (iscolliding)
		{
	 	bool test = true;
		}
		
	}
	return iscolliding;
}

bool TileMap::CollidesWith(CircleCollider2D * pCircleCollider2D)
{
	return false;
}

bool TileMap::CollidesWith(TileMap * pCollider2D)
{
	return false;
}

void TileMap::OnCollision(Collider2D * pCollider2D)
{
	
}

bool TileMap::LoadFromFile(std::string pfile)
{
	// Read the file and store the value into our map
	std::ifstream file;
	
	file.open(pfile);
	if(file.is_open())
	{
		std::string ttileset;
		std::getline(file, ttileset);

		std::string tscratch;
		
		std::getline(file, tscratch);
		std::vector<std::string> tst;
		splitString(tscratch, tst);
		
		mapWidth = stoi(tst[0]); // Map width
		mapHeight = stoi(tst[1]); // Map height
		
		GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
		SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef(ttileset.c_str());
		
		pMap = new int[mapWidth*mapHeight];
		int input;

		for(int i = 0; i < mapWidth * mapHeight; i++)
		{
			file >>input;
			pMap[i] = input;
			tiles.push_back(input);
		}
		
		file.close();

		
		LoadFromSpritesheetDef(pSpritesheetDef, pMap, mapWidth, mapHeight);

		delete[]pMap;
		
	}
	else
	{
		char message[1024];strerror_s(message, 1024, errno);
		std::cerr <<"Error: "<<message;
	}

	return true;
}

int TileMap::TileIndexAtPosition(int TileX, int TileY)
{
	int col = TileX / cellwidth;
	int row = TileY / cellheight;

	int index = row * mapWidth + col;
	int indexnum = tiles[index];
	
	return indexnum;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = m_pTileset;

	// draw the vertex array
	target.draw(m_Vertices, states);
}

bool TileMap::LoadFromSpritesheetDef(SpritesheetDef* pSpritesheetDef, const int* tiles, unsigned width, unsigned height)
{
	if (!pSpritesheetDef)
		return false;
	
	AssetManager* pAssetManager = C_SysContext::Get<AssetManager>();
	m_pTileset = &(pAssetManager->GetTexture(pSpritesheetDef->m_Filename.c_str()));
	std::vector<sf::IntRect> frames;
	for (std::vector<SpritesheetSpriteDef>::iterator iter = pSpritesheetDef->m_pSpriteDefs.begin();
		iter != pSpritesheetDef->m_pSpriteDefs.end(); iter++)
	{
		sf::IntRect rect((*iter).m_PosX, (*iter).m_PosY, (*iter).m_Width, (*iter).m_Height); frames.push_back(rect);

		cellwidth = rect.width;
		cellheight = rect.height;
	}
	int numTiles = 0;
	for (int i = 0; i < width* height; i++)
	{
		int tileNumber = tiles[i];
		if (tileNumber < 0 || tileNumber >= frames.size())
			continue;

		numTiles++;
		
	}
	//resize the vertex array to fit the level size
	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices.resize(numTiles * 4);
	int quadNum = 0;
	
	for(unsigned int i = 0; i < width; ++i)
		for(unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * width];
			if(tileNumber < 0 || tileNumber >= frames.size())
				continue;

			// find its position in the tileset texture
			int tu1 = frames[tileNumber].left;
			int tv1 = frames[tileNumber].top;
			int tu2 = tu1 + frames[tileNumber].width;
			int tv2 = tv1 + frames[tileNumber].height;

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_Vertices[(quadNum) * 4];

			// define its 4 corners
			quad[0].position =sf::Vector2f(i * frames[tileNumber].width, j * 
	frames[tileNumber].height);
			quad[1].position =sf::Vector2f((i + 1) * frames[tileNumber].width, j *
	frames[tileNumber].height);
			quad[2].position =sf::Vector2f((i + 1) * frames[tileNumber].width, (j + 1) *
	frames[tileNumber].height);
			quad[3].position =sf::Vector2f(i * frames[tileNumber].width, (j + 1) *
	frames[tileNumber].height);
			// define its 4 texture coordinates
			quad[0].texCoords =sf::Vector2f(tu1, tv1);
			quad[1].texCoords =sf::Vector2f(tu2, tv1);
			quad[2].texCoords =sf::Vector2f(tu2, tv2);
			quad[3].texCoords =sf::Vector2f(tu1, tv2);
			quadNum++;
		}
	C_SysContext::Get<RenderManager>()->AddRenderObject(this);

	return true;
}
