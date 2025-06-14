#include "GamePlayStateOne.h"



GamePlayStateOne::GamePlayStateOne()
{
}


GamePlayStateOne::~GamePlayStateOne()
{
}

bool GamePlayStateOne::Initialize(CGraphics* graphics)
{
	this->gDevice = graphics->GetDevice();

	viewPort = new ViewPort(0, GAME_HEIGHT);
	CTextures* textures = CTextures::GetInstance();
	tileMap = new CMap(Type::TILESET_LEVEL1, textures->Get(Type::TILESET_LEVEL1));
	tileMap->LoadMapFromFile(L"textures/readfile_map_1.txt");

	cameraObject = new GameObjectDem();
	cameraObject->Initialize(SIMON_SPRITE, viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y, 5, 900);

	leftCamera = new Ground(2, 450);
	leftCamera->Initialize(TEXTURE_PATH_LARGE_CANDLE ,viewPort->GetCameraPosition().x - 2, viewPort->GetCameraPosition().y, TAG_GROUND, 960);

	rightCamera = new Ground(2, 450);
	rightCamera->Initialize(TEXTURE_PATH_LARGE_CANDLE, viewPort->GetCameraPosition().x + GAME_WIDTH, viewPort->GetCameraPosition().y, TAG_GROUND, 970);

	quadTree = new QuadTree(viewPort);
	quadTree->Load("Resource\\sprites\\QuadTree\\lv1.txt");

	list = new std::vector<GameObjectDem*>();
	simon = new SimonDemo(8, 0, 0);
	if (!simon->Initialize( SIMON_SPRITE, 610, 91, TAG_SIMON, 10000))
		return false;
	simon->SetIsLeft(true);

	simon->SetPosition(100, 150);
	simon->Reload();

	changeState = false;




	//Item::TakeSimonPointer(simon);

	//listItem = new std::vector<Item*>();

	ui = new UI();
	ui->Initialize(gDevice, simon, 16);
	time = 0;

	return true;
}


void GamePlayStateOne::Update(float gameTime)
{
	time += gameTime;
	ui->Update(16, 1000 - (int)time, 3, 1);

	if (simon->GetPosition().x >= GAME_WIDTH / 2 && simon->GetPosition().x <= 1536 - GAME_WIDTH / 2 - 32)
	{
		D3DXVECTOR2 currentCamera = viewPort->GetCameraPosition();
		currentCamera.x += simon->GetVelocity().x * gameTime;
		viewPort->SetCameraPosition(currentCamera.x, currentCamera.y);
	}

	cameraObject->SetPosition(viewPort->GetCameraPosition());
	cameraObject->SetRegion(0, GAME_WIDTH, 0, -GAME_HEIGHT);

	//khong cho simon di ra khoi camera
	leftCamera->SetPosition(viewPort->GetCameraPosition().x - 2, viewPort->GetCameraPosition().y);
	leftCamera->SetBox(leftCamera->GetPosition().x, leftCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

	rightCamera->SetPosition(viewPort->GetCameraPosition().x + GAME_WIDTH, viewPort->GetCameraPosition().y);
	rightCamera->SetBox(rightCamera->GetPosition().x, rightCamera->GetPosition().y, 2, GAME_HEIGHT, 0, 0);

	list->clear();
	quadTree->GetObjectList(list, cameraObject->GetRegion());
	for (auto i = list->begin(); i != list->end(); i++)
	{
		if (!(*i)->IsEnable())
		{
			/*if ((*i)->isDropItem == false)
			{
				Item* item = new Item();
				item->Initialize(gDevice, (*i)->GetPosition().x, (*i)->GetPosition().y);
				//item->Initialize(gDevice, (*i)->GetPosition().x, (*i)->GetPosition().y, ITEM_UPGRADE_1, 10);
				listItem->push_back(item);
				(*i)->isDropItem = true;
			}*/
			quadTree->Remove((*i));
		}
		else
			(*i)->Update(gameTime);
	}

	/*for (auto i = listItem->begin(); i != listItem->end(); i++)
	{
		(*i)->Update(gameTime);
		(*i)->CheckCollider(gameTime, list);
	}*/

	/*
	for (int i = 0; i < simon->GetNoSubWeapon(); i++)
	{
		simon->subWeapon[i]->CheckCollider(gameTime, list);
		if (simon->subWeapon[i]->GetPosition().x < viewPort->GetCameraPosition().x ||
			simon->subWeapon[i]->GetPosition().x > viewPort->GetCameraPosition().x + GAME_WIDTH)
			simon->subWeapon[i]->SetEnable(false);

		if (simon->subWeapon[i]->CheckColliderWith(gameTime, simon) && simon->subWeapon[i]->GetTag() == TAG_CROSS)
		{
			if (((Cross*)simon->subWeapon[i])->IsTurnBack())
				simon->subWeapon[i]->SetEnable(false);
		}
	}
	*/
	simon->KeyBoardHandle(gameTime);
	simon->Update(gameTime);
	simon->CheckCollider(gameTime, list);
	simon->CheckColliderWith(gameTime, leftCamera);
	simon->CheckColliderWith(gameTime, rightCamera);

	if (IsKeyPress(DIK_M))
		SetChangingState(true);

	if (simon->GetPosition().x > 1300 && simon->GetPosition().x < 1400)
	{
		simon->SetVelocity(D3DXVECTOR2(0, 0));
		simon->SetPosition(simon->GetPosition().x + 50 * gameTime,
			simon->GetPosition().y);
		simon->SetAction(MOVE);
		simon->SetCanControlKeyboard(false);
		if (simon->GetPosition().x >= 1408 - 55)
		{
		}
	}
	else if (simon->GetPosition().x > 1400)
	{
		SetChangingState(true);
	}
}

void GamePlayStateOne::Render()
{
	ui->Render();
	tileMap->DrawMap(viewPort);
	for (auto i = list->begin(); i != list->end(); i++)
	{
		(*i)->isAdded = false;
		(*i)->Render(viewPort);
	}
	/*for (auto i = listItem->begin(); i != listItem->end(); i++)
	{
		(*i)->Render(viewPort);
	}*/
	simon->Render(viewPort);

	castleSprite->Render(viewPort);
}

bool GamePlayStateOne::GetChangingState()
{
	return GameState::GetChangingState();
}

void GamePlayStateOne::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void GamePlayStateOne::DestroyAll()
{
	//delete(simon);
	delete(tileMap);
	delete(ground);
	delete(cameraObject);
	delete(listObject);
	delete(viewPort);
}