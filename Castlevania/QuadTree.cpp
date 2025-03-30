#include "QuadTree.h"
#include "Camera.h"

template <typename T>
CQuadTree<T>::CQuadTree(D3DXVECTOR2 pos, D3DXVECTOR2 range)
{
	root = new CQuadTreeNode<T>(pos, range);
}

template <typename T>
CQuadTree<T>::~CQuadTree()
{
	delete root;
}

template <typename T>
void CQuadTree<T>::insert(D3DXVECTOR2 v, T data)
{
	insert(v, data, root, 0);
}

template <typename T>
int CQuadTree<T>::direction(const D3DXVECTOR2& point, CQuadTreeNode<T>* node)
{
	// get the quadrant that would contain the D3DXVECTOR2
	// in reference to a given start node
	unsigned X = 0, Y = 0;
	X |= ((point.x >= node->pos.x) << 1);
	Y |= ((point.y >= node->pos.y) << 0);
	return (X | Y);
}

template <typename T>
CQuadTreeNode<T>* CQuadTree<T>::childNode(const D3DXVECTOR2& v, CQuadTreeNode<T>* node,UINT id)
{
	// get the next node that would contain the D3DXVECTOR2
	// in reference to a given start node
	unsigned dir = direction(v, node);
	if (node->child[dir]) {
		return node->child[dir];
	}
	// node not found, so create it 
	else {
		D3DXVECTOR2 r(node->range.x / 2.0, node->range.y / 2.0);
		node->child[dir] = new CQuadTreeNode<T>(newPos(dir, node), r, 8 * id + dir);
		if (node->child[dir]->range.x > (FLOAT)CGame::GetBackBufferWidth() / 2)
			node->child[dir]->leaf = false;
		return node->child[dir];
	}
}

template <typename T>
D3DXVECTOR2  CQuadTree<T>::newPos(int direction, CQuadTreeNode<T>* node)
{
	D3DXVECTOR2 v(node->pos.x, node->pos.y);
	switch (direction) {
	case LOWER_LEFT_QUAD:
		v.x -= node->range.x / 2.0;
		v.y -= node->range.y / 2.0;
		break;
	case UPPER_LEFT_QUAD:
		v.x -= node->range.x / 2.0;
		v.y += node->range.y / 2.0;
		break;
	case LOWER_RIGHT_QUAD:
		v.x += node->range.x / 2.0;
		v.y -= node->range.y / 2.0;
		break;
	case UPPER_RIGHT_QUAD:
		v.x += node->range.x / 2.0;
		v.y += node->range.y / 2.0;
		break;
	}
	return v;
}


/*by design, gameObject are stored only in leaf nodes
/newly created nodes are leaf nodes by default*/
template <typename T>
void CQuadTree<T>::insert(D3DXVECTOR2 v, T data, CQuadTreeNode<T>* node, UINT id)
{
	// push gameObject in deepest node (leaf)
	if (node->leaf) {
		node->bucket.push_back({ v, data });
	}
	// current node is a stem node used for navigation
	else 
	{
		insert(v, data, childNode(v, node), node->id);
	}
}

template <typename T>
bool  CQuadTree<T>::remove(D3DXVECTOR2 v,T data)
{
	stack <CQuadTreeNode<T>*> nodes;
	nodes.push(root);
	CQuadTreeNode<T>* top = nodes.top();
	unsigned dir;

	// navigate to leaf node containing the gameObject to be deleted
	while (!top->leaf) {
		dir = direction(v, top);
		if (top->child[dir]) {
			nodes.push(top->child[dir]);
			top = nodes.top();
		}
		else {
			return false;
		}
	}
	// linearly search bucket for target  gameObject
	for (int i = 0; i < top->bucket.size(); ++i) {
		//  gameObject found, delete from bucket
		if (top->bucket[i].first == v && top->bucket[i].second == data) {
			top->bucket.erase(top->bucket.begin() + i);
			reduce(nodes);
			return true;
		}
	}
	return false;
}




/*	once a gameObject is removed from a leaf node's bucket
	check if there are any other gameobjects in that node (which is an empty node)
	if not, remove it and do the same with its parent node.
*/
template <typename T>
void  CQuadTree<T>::reduce(stack <CQuadTreeNode<T>*>& nodes)
{
	nodes.pop();
	while (!nodes.empty()) {
		CQuadTreeNode<T>* top = nodes.top();
		for (int i = 0; i < 4; ++i) {
			if (top->child[i] && !top->child[i]->leaf) {
				return;
			}
		}
		int emtyChild = 0;
		for (int i = 0; i < 4; ++i) {
			if (top->child[i] && top->child[i]->bucket.size()==0) {
				delete top->child[i];
				top->child[i] = NULL;
	
			}
			if(!top->child[i])
				emtyChild++;
		}

		if(emtyChild == 4)
			top->leaf = true;
		nodes.pop();
	}
	return;
}


template <typename T>
vector <pair <D3DXVECTOR2, T> > CQuadTree<T>::getObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY)
{
	vector <pair <D3DXVECTOR2, T> > results;
	queue <CQuadTreeNode<T>*> nodes;
	nodes.push(root);

	while (!nodes.empty()) {
		CQuadTreeNode<T>* top = nodes.front();
		if (top->leaf) {
			enclosure_status status = getEnclosureStatus(top->pos, top->range, minXY, maxXY);
			switch (status) {
				// this node is completely contained within the search region
			case NODE_CONTAINED_BY_REGION:
				// add all elements to results
				results.insert(results.end(), top->bucket.begin(), top->bucket.end());
				break;

				// this node is partially contained by the region
			case  NODE_PARTIALLY_IN_REGION:
				// search through this leaf node's bucket
				for (int i = 0; i < top->bucket.size(); ++i) {
					// check if this point is in the region
					if (pointInRegion(top->bucket[i].first, minXY, maxXY)) {
						results.push_back(top->bucket[i]);
					}
				}
				break;

				// this node definitely has no points in the region
			case NODE_NOT_IN_REGION:
				// do nothing
				break;
			}
		}
		else {
			for (int i = 0; i < 4; ++i) {
				if (top->child[i]) {
					// check if this nodes children could have points in the region
					enclosure_status status = getEnclosureStatus(top->child[i]->pos, top->child[i]->range, minXY, maxXY);
					switch (status) {
						// this node is completely contained by region, add all points within
					case NODE_CONTAINED_BY_REGION:
						addAllPointsToResults(top->child[i], results);
						break;

						// this node might contain points in the region
					case NODE_PARTIALLY_IN_REGION:
						nodes.push(top->child[i]);
						break;

						// no points in region, discontinue searching this branch
					case NODE_NOT_IN_REGION:
						break;
					}
				}
			}
		}
		nodes.pop();
	}
	return results;
}

template <typename T>
void CQuadTree<T>::addAllPointsToResults(CQuadTreeNode<T>* node, vector <pair <D3DXVECTOR2, T> >& results)
{
	if (node->leaf) {
		results.insert(results.end(), node->bucket.begin(), node->bucket.end());
	}
	else {
		for (int i = 0; i < 4; ++i) {
			if (node->child[i]) {
				addAllPointsToResults(node->child[i], results);
			}
		}
	}
}

template <typename T>
bool CQuadTree<T>::pointInRegion(const D3DXVECTOR2& point, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY)
{
	if ((point.x >= minXY.x) && (point.x < maxXY.x) && (point.y >= minXY.y) && (point.y < maxXY.y)) {
		return true;
	}
	else {
		return false;
	}
}

template <typename T>
enclosure_status CQuadTree<T>::getEnclosureStatus(const D3DXVECTOR2& pos, const D3DXVECTOR2& range, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY)
{
	int enclosedPts = 0;
	D3DXVECTOR2 halfRange = range * 0.5f;

	enclosedPts += pointInRegion({ pos.x - halfRange.x, pos.y - halfRange.y }, minXY, maxXY);
	enclosedPts += pointInRegion({ pos.x - halfRange.x, pos.y + halfRange.y }, minXY, maxXY);
	enclosedPts += pointInRegion({ pos.x + halfRange.x, pos.y - halfRange.y }, minXY, maxXY);
	enclosedPts += pointInRegion({ pos.x + halfRange.x, pos.y + halfRange.y }, minXY, maxXY);

	if (enclosedPts == 4) {

		//so just return NODE_CONTAINED_BY_REGION; 
		// when size of the region is larger than the size of the node

		return NODE_CONTAINED_BY_REGION;
	}
	else if (enclosedPts > 0) {
		return NODE_PARTIALLY_IN_REGION;
	}
	else {
		D3DXVECTOR2 nodeMin(pos.x - halfRange.x, pos.y - halfRange.y);
		D3DXVECTOR2 nodeMax(pos.x + halfRange.x, pos.y + halfRange.y);

		enclosedPts += pointInRegion(minXY, nodeMin, nodeMax);
		enclosedPts += pointInRegion({ minXY.x, maxXY.y }, nodeMin, nodeMax);
		enclosedPts += pointInRegion(maxXY, nodeMin, nodeMax);
		enclosedPts += pointInRegion({ maxXY.x, minXY.y }, nodeMin, nodeMax);
		if (enclosedPts > 0) {
			return NODE_PARTIALLY_IN_REGION;
		}
	}
	return NODE_NOT_IN_REGION;
}

template <typename T>
void CQuadTree<T>::draw()
{
	if (root) {
		draw(root);
	}
}

template <typename T>
void CQuadTree<T>::draw(CQuadTreeNode<T>* node)
{
	//Because all objects are stored in leaf nodes, only leaf nodes are drawn.
	/*float cx, cy;
	CCamera* cam = CCamera::GetInstance();
	cam->GetCameraPos(cx, cy);
	getObjectsInRegion(new D3DXVECTOR2(cx,root->range.y-cy);
	for (int i = 0; i < 4; ++i) {
		if (node->child[i]) {
			draw(node->child[i]);
		}
	}*/
}

