#pragma once

/**
	QuadTree.h

	QTNode: the recursive building block of a quad tree

	Quadtree: a dynamic 2d space partitioning structure

**/
#include "QuadTreeNode.h"

#include <cstdlib>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

#define LOWER_LEFT_QUAD 0
#define UPPER_LEFT_QUAD 1
#define LOWER_RIGHT_QUAD 2
#define UPPER_RIGHT_QUAD 3

enum enclosure_status
{
	NODE_NOT_IN_REGION,
	NODE_PARTIALLY_IN_REGION,
	NODE_CONTAINED_BY_REGION
};

template <typename T>
class CQuadTree
{
public:

	CQuadTree <T>(D3DXVECTOR2 pos, D3DXVECTOR2 range);
	~CQuadTree();

	void 	insert(D3DXVECTOR2 v, T data);
	bool 	remove(D3DXVECTOR2 v,T  data);
	void 	draw();
	vector <pair <D3DXVECTOR2, T> > getObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY);

private:

	CQuadTreeNode<T>* childNode(const D3DXVECTOR2& v, CQuadTreeNode<T>* node, UINT id);
	D3DXVECTOR2 newPos(int direction, CQuadTreeNode<T>*  node);
	int 	direction(const D3DXVECTOR2& point, CQuadTreeNode<T>* node);
	void 	insert(D3DXVECTOR2 v, T data, CQuadTreeNode<T>* node, UINT id);
	void	reduce(stack <CQuadTreeNode<T>*>& node);
	void 	draw(CQuadTreeNode<T>* node);
	void	addAllPointsToResults(CQuadTreeNode<T>* node, vector <pair <D3DXVECTOR2, T> >& results);
	bool	pointInRegion(const D3DXVECTOR2& point, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY);
	enclosure_status getEnclosureStatus(const D3DXVECTOR2& pos, const D3DXVECTOR2& range, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY);

	CQuadTreeNode<T>* root;
};
