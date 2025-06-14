#include "QuadTree.h"

QuadTree::QuadTree( ViewPort* viewPort)
{
	this->node = NULL;
	this->viewPort = viewPort;
	this->region = new RECT();
}

QuadTree::~QuadTree(void)
{
	for (std::vector<GameObjectDem*>::iterator i = listObject->begin(); i != listObject->end(); i++)
	{
		delete[](*i);
	}

	delete[] listObject;
}

std::map<int, GameObjectDem*> QuadTree::mapObject;

void QuadTree::Load(std::string file)
{
	std::ifstream input;
	input.open(file, std::ifstream::in);

	std::string checkEnd;
	std::string trace;

	int id;
	int type;
	float x;
	float y;
	int width;
	int height;

	float left;
	float top;
	float right;
	float bottom;
	int n;
	int objectID;

	int count = 0;

	while (input >> checkEnd)
	{
		if (checkEnd == "END")
		{
			count++;
			continue;
		}

		if (count == 0)
		{
			id = atoi(checkEnd.c_str());
			input >> type >> x >> y >> width >> height;
			LoadObject(id, type, x, y, width, height);
		}
		else if (count == 1)
		{
			id = atoi(checkEnd.c_str());
			input >> left >> top >> right >> bottom >> n;

			std::vector<GameObjectDem*>* list = new std::vector<GameObjectDem*>();
			for (int i = 0; i < n; i++)
			{
				input >> objectID;
				list->push_back(mapObject[objectID]);
			}

			trace.clear();

			while (true)
			{
				id--;
				if (id < 0)
					break;
				else
				{
					trace = std::to_string(id % 4) + trace;
					id = id / 4;
				}
			}

			trace = trace + "e";

			LoadQuad(trace, 0, left, top, right, bottom, list);
		}
	}
}

void QuadTree::LoadQuad(std::string trace, int pos, float left, float top, float right, float bottom, std::vector<GameObjectDem*>* list)
{
	if (trace[pos] == 'e')
	{
		SetRect(this->region, left, top, right, bottom);
		this->listObject = list;
	}
	else
	{
		if (!this->node)
		{
			node = new QuadTree * [4];
			node[0] = new QuadTree(viewPort);
			node[1] = new QuadTree(viewPort);
			node[2] = new QuadTree(viewPort);
			node[3] = new QuadTree(viewPort);
		}

		if (trace[pos] == '0')
			node[0]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
		else if (trace[pos] == '1')
			node[1]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
		else if (trace[pos] == '2')
			node[2]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
		else if (trace[pos] == '3')
			node[3]->LoadQuad(trace, pos + 1, left, top, right, bottom, list);
	}
}

void QuadTree::LoadObject(int id, int type, float x, float y, int width, int height)
{
	if (type == 10)
	{
		GameObjectDem* object;
		object = new LargeCandle();
		object->Initialize(TEXTURE_PATH_LARGE_CANDLE, x, y, type, 666);
		object->SetID(id);
		object->SetSize(width, height);
		object->SetRegion(0, width, 0, -height);
		mapObject[id] = object;
	}
	else if (type == TAG_GROUND)
	{
		GameObjectDem* object;
		object = new Ground(width, height);
		object->Initialize(TEXTURE_PATH_GROUND, x, y, TAG_GROUND, 730);
		object->SetID(id);
		object->SetSize(width, height);
		object->SetRegion(0, width, 0, -height);
		object->SetBox(x, y, width, height, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == TAG_GROUND_LEVEL_TWO)
	{
		GameObjectDem* object;
		object = new Ground(width, height);
		object->Initialize(TEXTURE_PATH_GROUND_TWO, x, y, TAG_GROUND, 732);
		object->SetID(id);
		object->SetSize(width, height);
		object->SetRegion(0, width, 0, -height);
		object->SetBox(x, y, width, height, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == TAG_STAIR)
	{
		GameObjectDem* object;
		object = new Stair();
		object->Initialize(TEXTURE_PATH_STAIR, x, y, type, 734);
		object->SetID(id);
		object->SetBox(x, y, 32, 32, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == TAG_STAIR_)
	{
		GameObjectDem* object;
		object = new Stair();
		object->Initialize(TEXTURE_PATH_STAIR_THREE, x, y, type, 736);
		object->SetID(id);
		object->SetBox(x, y, 32, 32, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == TAG_STAIR_TOP_)
	{
		GameObjectDem* object;
		object = new Stair();
		object->Initialize(TEXTURE_PATH_STAIR_TOP_TWO, x, y, TAG_STAIR_TOP, 738);
		object->SetID(id);
		object->SetBox(x, y, 32, 32, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == TAG_CANDLE)
	{
		GameObjectDem* object;
		object = new Candle();
		object->Initialize(TEXTURE_PATH_SMALL_CANDLE, x, y, type, 740);
		object->SetID(id);
		object->SetBox(x, y, 32, 32, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == 22 || type == -22) // O tren cau thang di xuong
	{
		GameObjectDem* object;
		object = new GameObjectDem();
		object->Initialize(TEXTURE_PATH_STAIR_TOP_THREE, x, y, type, 742);
		object->SetID(id);
		object->SetBox(x, y, 32, 32, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == 25 || type == -25) // O duong dat di len cau thang
	{
		GameObjectDem* object;
		object = new GameObjectDem();
		object->Initialize(TEXTURE_PATH_STAIR_BOTTOM, x, y, type, 744);
		object->SetID(id);
		object->SetBox(x, y, 32, 32, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == TAG_CHECK_STAIR)
	{
		GameObjectDem* object;
		object = new SceneCheck();
		object->Initialize(TEXTURE_PATH_CHECK_STAIR, x, y, type, 746);
		object->SetID(id);
		object->SetBox(x - 15, y, 96, 32 - 30, 0.0f, 0.0f);
		mapObject[id] = object;
	}
	else if (type == TAG_DOOR)
	{
		GameObjectDem* object;
		object = new Door();
		object->Initialize(TEXTURE_PATH_SMALL_DOOR, x, y, type, 750);
		object->SetID(id);
		mapObject[id] = object;
	}
	else if (type == TAG_CHECK_POINT)
	{
		GameObjectDem* object;
		object = new CheckPoint();
		object->Initialize(TEXTURE_PATH_CHECK_POINT, x, y, type, 755);
		object->SetID(id);
		object->SetBox(x, y, 32, 64, 0.0f, 0.0f);
		mapObject[id] = object;
	}
}

void QuadTree::Remove(GameObjectDem* object)
{
	if (this->node)
	{
		if (this->node[0]->IsContain(object))
			this->node[0]->Remove(object);

		if (this->node[1]->IsContain(object))
			this->node[1]->Remove(object);

		if (this->node[2]->IsContain(object))
			this->node[2]->Remove(object);

		if (this->node[3]->IsContain(object))
			this->node[3]->Remove(object);
	}
	else if (this->IsContain(object))
	{
		for (std::vector<GameObjectDem*>::iterator i = this->listObject->begin(); i != this->listObject->end(); i++)
		{
			if ((*i) == object)
			{
				this->listObject->erase(i);
				break;
			}
		}
	}
}

void QuadTree::Update(float gameTime)
{
	for (std::vector<GameObjectDem*>::iterator i = listObject->begin(); i != listObject->end(); i++)
	{
		(*i)->Update(gameTime);
	}

}

void QuadTree::Render()
{
	for (std::vector<GameObjectDem*>::iterator i = listObject->begin(); i != listObject->end(); i++)
	{
		if ((*i)->IsEnable())
			(*i)->Render(this->viewPort);
	}
}


bool QuadTree::IsContain(GameObjectDem* object)
{
	return object->IsInRegion(this->region);
}

bool QuadTree::IsContain(RECT* region)
{
	if (this->region->right < region->left || this->region->left > region->right ||
		this->region->bottom > region->top || this->region->top < region->bottom)
		return false;
	return true;
}

void QuadTree::GetObjectList(std::vector<GameObjectDem*>* staticList, std::vector<GameObjectDem*>* moveList, RECT* region)
{
	if (this->node)
	{
		if (this->node[0]->IsContain(region))
			this->node[0]->GetObjectList(staticList, moveList, region);

		if (this->node[1]->IsContain(region))
			this->node[1]->GetObjectList(staticList, moveList, region);

		if (this->node[2]->IsContain(region))
			this->node[2]->GetObjectList(staticList, moveList, region);

		if (this->node[3]->IsContain(region))
			this->node[3]->GetObjectList(staticList, moveList, region);
	}
	else if (this->IsContain(region))
	{
		for (std::vector<GameObjectDem*>::iterator i = this->listObject->begin(); i != this->listObject->end(); i++)
		{
			if ((*i)->IsMoveable() == true)
			{
				if (((Enemy*)(*i))->isIn == false && (*i)->IsEnable() == false)
				{
					(*i)->SetEnable(true);
					moveList->push_back(*i);
					((Enemy*)(*i))->isIn = true;
				}
			}
			else
				staticList->push_back(*i);
		}
	}
}

void QuadTree::GetObjectList(std::vector<GameObjectDem*>* staticList, std::vector<GameObjectDem*>* moveList, RECT* region, GameObjectDem* camera)
{
	if (this->node)
	{
		if (this->node[0]->IsContain(region))
			this->node[0]->GetObjectList(staticList, moveList, region);

		if (this->node[1]->IsContain(region))
			this->node[1]->GetObjectList(staticList, moveList, region);

		if (this->node[2]->IsContain(region))
			this->node[2]->GetObjectList(staticList, moveList, region);

		if (this->node[3]->IsContain(region))
			this->node[3]->GetObjectList(staticList, moveList, region);
	}
	else if (this->IsContain(region))
	{
		for (std::vector<GameObjectDem*>::iterator i = this->listObject->begin(); i != this->listObject->end(); i++)
		{
			if ((*i)->IsMoveable() == true)
			{
				if (((Enemy*)(*i))->isIn == false && (*i)->IsEnable() == false)
				{
					if ((*i)->IsInRegion(camera->GetRegion()))
					{
						(*i)->SetEnable(true);
						moveList->push_back(*i);
						((Enemy*)(*i))->isIn = true;
					}
				}
			}
			else
				staticList->push_back(*i);
		}
	}
}


void QuadTree::GetObjectList(std::vector<GameObjectDem*>* returnList, RECT* region)
{
	if (this->node)
	{
		if (this->node[0]->IsContain(region))
			this->node[0]->GetObjectList(returnList, region);

		if (this->node[1]->IsContain(region))
			this->node[1]->GetObjectList(returnList, region);

		if (this->node[2]->IsContain(region))
			this->node[2]->GetObjectList(returnList, region);

		if (this->node[3]->IsContain(region))
			this->node[3]->GetObjectList(returnList, region);
	}
	else if (this->IsContain(region))
	{
		for (std::vector<GameObjectDem*>::iterator i = this->listObject->begin(); i != this->listObject->end(); i++)
			/*if ((*i)->isAdded == false) {*/
			returnList->push_back(*i);
		/*(*i)->isAdded = true;
	}*/
	}
}