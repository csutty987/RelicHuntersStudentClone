#include "AttributeHandler.h"

#include "Player.h"

AttributeHandler::AttributeHandler()
{
	
}

AttributeHandler::~AttributeHandler()
{
	
}

void AttributeHandler::Initialise()
{

}

void AttributeHandler::Update()
{
	UpdateScoreHandler();
}

void AttributeHandler::ScoreHandler(int pScore)
{
	ScoreString = std::to_string((pScore) + ScoreValue);
}

void AttributeHandler::UpdateScoreHandler()
{
	Player* t_player;
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
	t_player = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
	
	ScoreHandler(t_player->PlayerScore);
}
