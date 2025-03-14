#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "GameDefines.h"
#include "Simon.h"

extern CSimon* simon;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_Z:
		simon->SetState(sType::DEFAULT_STATE, DIRECTION_DEFAULT);
		break;
	case DIK_X:
		simon->SetState(sType::SIMON_STATE_JUMPING,DIRECTION_DEFAULT);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		simon->SetState(sType::SIMON_STATE_IDLE, DIRECTION_DEFAULT);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();


	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_UP))
			simon->SetState(sType::SIMON_STATE_UPSTAIRS,DIRECTION_RIGHT);
		else if (game->IsKeyDown(DIK_DOWN))
				simon->SetState(sType::SIMON_STATE_DOWNSTAIRS, DIRECTION_RIGHT);		
		else
			simon->SetState(sType::SIMON_STATE_WALKING, DIRECTION_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_UP))
			simon->SetState(sType::SIMON_STATE_UPSTAIRS, DIRECTION_LEFT);
		else if (game->IsKeyDown(DIK_DOWN))
			simon->SetState(sType::SIMON_STATE_DOWNSTAIRS, DIRECTION_LEFT);
		else
			simon->SetState(sType::SIMON_STATE_WALKING, DIRECTION_LEFT);
	}
	else
		simon->SetState(sType::SIMON_STATE_IDLE, DIRECTION_DEFAULT);

	// Sitting state has higher priority 
	if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(sType::SIMON_STATE_DUCKING, DIRECTION_DEFAULT);
	}
}