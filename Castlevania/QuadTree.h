#pragma once
#ifndef QUADTREE_H
#define QUADTREE_H

//#include"GameObjectDem.h"
#include "ViewPort.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Enemy.h"

#include "Ground.h"
#include "Candle.h"
#include "ViewPort.h"
#include "LargeCandle.h"
#include "Stair.h"
#include "SceneCheck.h"
#include "Door.h"
#include "CheckPoint.h"

#define MAX_OBJECT_IN_REGION 1
#define MAX_LEVEL 2

class GameObjectDem;

class QuadTree
{
protected:
	ViewPort* viewPort;
	std::vector<GameObjectDem*>* listObject;

	//////////////////////////////////
	int id;
	RECT* region;
	QuadTree** node;

public:
	static std::map<int, GameObjectDem*> mapObject;

	QuadTree( ViewPort* viewPort);
	~QuadTree(void);

	void Load(std::string file);
	void LoadQuad(std::string trace, int pos, float left, float top, float right, float bottom, std::vector<GameObjectDem*>* list);
	void LoadObject(int id, int type, float x, float y, int width, int height);

	void Update(float gameTime);
	void Render();

	std::vector<GameObjectDem*>* GetListObject() { return listObject; }


	//////////////////////////////////////////////////////////////////////////////////////////
	void Remove(GameObjectDem* object);
	bool IsContain(GameObjectDem* object);
	bool IsContain(RECT* region);
	void GetObjectList(std::vector<GameObjectDem*>* returnList, RECT* region);
	void GetObjectList(std::vector<GameObjectDem*>* staticList, std::vector<GameObjectDem*>* moveList, RECT* region);
	void GetObjectList(std::vector<GameObjectDem*>* staticList, std::vector<GameObjectDem*>* moveList, RECT* region, GameObjectDem* camera);
};

#endif
