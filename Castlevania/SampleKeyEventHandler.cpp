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
	case DIK_A:
		simon->SetState(sType::SIMON_STATE_HURTING, (simon->GetDirectionX()));
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
			simon->SetState(sType::SIMON_STATE_WALKING_ONSTAIRS,DIRECTION_POSITIVE, DIRECTION_NEGATIVE);
		else if (game->IsKeyDown(DIK_DOWN))
				simon->SetState(sType::SIMON_STATE_WALKING_ONSTAIRS, DIRECTION_POSITIVE);
		else
			simon->SetState(sType::SIMON_STATE_WALKING, DIRECTION_POSITIVE);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_UP))
			simon->SetState(sType::SIMON_STATE_WALKING_ONSTAIRS, DIRECTION_NEGATIVE, DIRECTION_NEGATIVE);
		else if (game->IsKeyDown(DIK_DOWN))
			simon->SetState(sType::SIMON_STATE_WALKING_ONSTAIRS, DIRECTION_NEGATIVE);
		else
			simon->SetState(sType::SIMON_STATE_WALKING, DIRECTION_NEGATIVE);
	}
	else 
	{
		simon->SetState(sType::SIMON_STATE_IDLE, DIRECTION_DEFAULT);

	}

	// Sitting state has higher priority 
	if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(sType::SIMON_STATE_DUCKING, DIRECTION_DEFAULT);
	}
}