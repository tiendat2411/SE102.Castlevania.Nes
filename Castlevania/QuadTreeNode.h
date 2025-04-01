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
	vector <pair <D3DXVECTOR2, LPGAMEOBJECT> > bucket;


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



};