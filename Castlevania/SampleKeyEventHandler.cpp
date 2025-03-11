#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "Simon.h"

extern CSimon* simon;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		simon->SetState(SIMON_STATE_JUMP);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		simon->SetState(SIMON_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		simon->SetState(SIMON_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	CGame* game = CGame::GetInstance();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			simon->SetState(SIMON_STATE_RUNNING_RIGHT);
		else
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			simon->SetState(SIMON_STATE_RUNNING_LEFT);
		else
			simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
	
	// Sitting state has higher priority 
	if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_SIT);
	}

}