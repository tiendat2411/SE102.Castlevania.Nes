#include "StateManager.h"


StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}

bool StateManager::Initialize(HWND hwnd)
{
	gDevice = new CGraphics();
	if (!gDevice->Initialize(hwnd))
		return false;
	return true;
}

/*LOAD STATE DUA THEO ID CUA STATE DO*/
void StateManager::LoadState(int stateID)
{
	switch (stateID)
	{
	/*case GAME_MENU_STATE:
		gameState = new GameMenuState();
		if (!gameState->Initialize(gDevice))
			return;
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case GAME_INTRO_SCENE:
		gameState = new IntroScene();
		if (!gameState->Initialize(gDevice))
			return;
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	*/
	case GAME_PLAY_STATE_ONE:
		delete(gameState);
		gameState = new GamePlayStateOne();
		if (!gameState->Initialize(gDevice))
			return;
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	/*case GAME_PLAY_STATE_TWO:
		delete(gameState);
		gameState = new GamePlayStateTwo();
		if (!gameState->Initialize(gDevice))
			return;
		gameState->state = stateID;
		this->stateID = stateID;
		break;*/
	default:
		break;
	}
}

void StateManager::NextStateLevel()
{
	stateID++;
}

void StateManager::Render()
{
	gDevice->Clear();
	gameState->Render();

	gDevice->Present();
}

void StateManager::Update(float gameTime)
{
	if (gameState->GetChangingState())
	{
		if (stateID != GAME_MENU_STATE)
		{
			gameState->DestroyAll();
		}
		NextStateLevel();
		LoadState(stateID);
		gameState->SetChangingState(false);
	}

	gameState->Update(gameTime);
}
