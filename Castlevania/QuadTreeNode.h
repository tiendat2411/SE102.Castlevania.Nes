#pragma once

#include "Game.h"
#include "GameObject.h"

#include <cstdlib>
#include <vector>
using namespace std;


class CQuadTreeNode {

public:
	D3DXVECTOR2 pos, range;

	// used by stem nodes
	bool leaf;
	UINT id;
	CQuadTreeNode* child[4];

	// used by leaf nodes
	vector<pair<RECT, LPGAMEOBJECT>> staticBucket;
	vector<pair<RECT, LPGAMEOBJECT>> dynamicBucket;


	CQuadTreeNode(D3DXVECTOR2 pos, D3DXVECTOR2 range, UINT id = 0) {
		child[0] = NULL;
		child[1] = NULL;
		child[2] = NULL;
		child[3] = NULL;
		this->pos = pos;
		this->range = range;
		this->id = id;
		leaf = true;
	}
	~CQuadTreeNode() { for (int i = 0; i < 4; ++i) if (child[i]) { delete child[i]; } }

	vector<pair<RECT, LPGAMEOBJECT>> GetAllObjects() {
		vector<pair<RECT, LPGAMEOBJECT>> allObjects;
		allObjects.insert(allObjects.end(), staticBucket.begin(), staticBucket.end());
		allObjects.insert(allObjects.end(), dynamicBucket.begin(), dynamicBucket.end());
		return allObjects;
	}

};

typedef CQuadTreeNode* LPQUADTREENODE;
