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

	CQuadTree(D3DXVECTOR2 pos, D3DXVECTOR2 range);
	~CQuadTree();

	void 	insert(D3DXVECTOR2 v, LPGAMEOBJECT data);
	bool 	remove(D3DXVECTOR2 v,LPGAMEOBJECT  data);
	void 	render();
	vector <pair <D3DXVECTOR2, LPGAMEOBJECT> > renderObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY);
	void registerDynamicObject(CQuadTreeObject* object);
	void unregisterDynamicObject(CQuadTreeObject* object);
	void updateDynamicObject(CQuadTreeObject* object, D3DXVECTOR2 newPosition, bool force = false);
	void updateAllDynamicObjects(float dt);
	CQuadTreeNode* findNodeForPoint(D3DXVECTOR2 point);

private:

	CQuadTreeNode* childNode(const D3DXVECTOR2& v, CQuadTreeNode* node, UINT id);
	D3DXVECTOR2 newPos(int direction, CQuadTreeNode*  node);
	int 	direction(const D3DXVECTOR2& point, CQuadTreeNode* node);
	void 	insert(D3DXVECTOR2 v, LPGAMEOBJECT data, CQuadTreeNode* node);
	void	reduce(stack <CQuadTreeNode*>& node);
	void 	render(CQuadTreeNode* node);
	void	addAllObjectToResults(CQuadTreeNode* node, vector<pair <D3DXVECTOR2, LPGAMEOBJECT> >& results);
	bool	pointInRegion(const D3DXVECTOR2& point, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY);
	enclosure_status getEnclosureStatus(const D3DXVECTOR2& pos, const D3DXVECTOR2& range, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY);
	CQuadTreeNode* findNodeForPoint(D3DXVECTOR2 point, CQuadTreeNode* startNode);

	CQuadTreeNode* root;
	vector<CQuadTreeObject*> dynamicObjects;
};
