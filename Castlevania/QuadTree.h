#pragma once

/**
	QuadTree.h

	QTNode: the recursive building block of a quad tree

	Quadtree: a dynamic 2d space partitioning structure

**/
#include "QuadTreeNode.h"
#include "GameObject.h"

#include <cstdlib>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <stdlib.h>
class CQuadTreeNode;
using namespace std;

//region direction						/*----------------------*/
#define LOWER_LEFT_QUAD 0				/*	   0	|	  2  	*/
#define UPPER_LEFT_QUAD 1				/*----------|-----------*/
#define LOWER_RIGHT_QUAD 2				/*	   1	|	  3		*/
#define UPPER_RIGHT_QUAD 3				/*----------------------*/

enum enclosure_status
{
	NODE_NOT_IN_REGION,
	NODE_PARTIALLY_IN_REGION,
	NODE_CONTAINED_BY_REGION
};

class CQuadTree
{
public:

	CQuadTree(D3DXVECTOR2 pos, D3DXVECTOR2 range, LPCWSTR filePath);
	~CQuadTree();
	void	insertObjectIntoTree();
	void	insert(LPGAMEOBJECT data);
	bool	remove(LPGAMEOBJECT data);
	void 	render();
	void	UpdateDynamicObject(LPGAMEOBJECT object);
	vector <LPGAMEOBJECT> renderObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY);
	void	UpdateDynamicObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY, DWORD dt);
	//void	ResetUpdateState();

private:

	vector<LPGAMEOBJECT> LoadGameObjects();
	LPGAMEOBJECT CreateGameObjectByType(int type, int x, int y);
	void SetObjectDynamicState(LPGAMEOBJECT obj, int type);
	CQuadTreeNode* childNode(const D3DXVECTOR2& v, CQuadTreeNode* node, UINT id);
	D3DXVECTOR2 newPos(int direction, CQuadTreeNode* node);
	void	insert(LPGAMEOBJECT data, RECT bounds, CQuadTreeNode* node);
	int 	direction(const D3DXVECTOR2& point, CQuadTreeNode* node);
	//void	reduce(stack <CQuadTreeNode*>& node);
	//void	addAllObjectToResults(CQuadTreeNode* node, vector<pair <D3DXVECTOR2, LPGAMEOBJECT> >& results);
	bool	pointInRegion(const D3DXVECTOR2& point, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY);
	enclosure_status getEnclosureStatus(const D3DXVECTOR2& pos, const D3DXVECTOR2& range, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY);
	bool RectInNode(const RECT& rect, CQuadTreeNode* node);
	bool RectIntersectNode(const RECT& rect, CQuadTreeNode* node);
	void processNodeObjects(const vector<pair<RECT, LPGAMEOBJECT>>& bucket, const RECT& queryRegion, vector<LPGAMEOBJECT>& results);
	bool RectIntersectsRect(const RECT& rect1, const RECT& rect2);
	CQuadTreeNode* root;
	LPCWSTR filePath;
};

