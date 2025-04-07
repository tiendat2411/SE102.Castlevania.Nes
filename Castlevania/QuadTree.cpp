#include "QuadTree.h"
#include "Camera.h"
#include "Zombie.h"


#include <fstream>
#include <string.h>




CQuadTree::CQuadTree(D3DXVECTOR2 pos, D3DXVECTOR2 range, LPCWSTR filePath)
{
	root = new CQuadTreeNode(pos, range);
	this->filePath = filePath;
}


CQuadTree::~CQuadTree()
{
	delete root;
}


vector<LPGAMEOBJECT> CQuadTree::LoadGameObjects() {
	vector<LPGAMEOBJECT> objects;
	ifstream file(filePath, ios::in);

	std::string line;
	std::getline(file, line);
	/*int id, type;
	float x, y, w, h;*/
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::vector<std::string> tokens;
		std::string token;

		while (std::getline(ss, token, '|')) {
			tokens.push_back(token);
		}
		int id = std::stoi(tokens[0]);
		int type = std::stoi(tokens[1]);
		float x = std::stof(tokens[2]);
		float y = std::stof(tokens[3]);
		float width = std::stof(tokens[4]);
		float height = std::stof(tokens[5]);
		float boundaryLeft = std::stof(tokens[6]);
		float boundaryRight = std::stof(tokens[7]);

		LPGAMEOBJECT obj = CreateGameObjectByType(type, x, y);
		SetObjectDynamicState(obj, type);
		objects.push_back(obj);
	}
	file.close();
	return objects;
}

void CQuadTree::SetObjectDynamicState(LPGAMEOBJECT obj, int type)
{
	// Mark the types of dynamic objects.
	switch (type)
	{
	case static_cast<int>(Type::ZOMBIE):
	case static_cast<int>(Type::SIMON):
	case static_cast<int>(Type::GHOST):
		obj->SetDynamic(true);
		break;
	default:
		obj->SetDynamic(false);
		break;
	}
}


//hinh nhu con thieu cai huong nen em de tam nhaa
LPGAMEOBJECT  CQuadTree::CreateGameObjectByType(int type, int x, int y) {
	switch (type)
	{
	case static_cast<int>(Type::ZOMBIE):
		return new CZombie(x, y, DIRECTION_POSITIVE);
		break;
	}
}


void CQuadTree::insertObjectIntoTree()
{
	vector<LPGAMEOBJECT> objects = LoadGameObjects();
	for (LPGAMEOBJECT obj : objects) {
		insert(obj);
	}
}

int CQuadTree::direction(const D3DXVECTOR2& point, CQuadTreeNode* node)
{
	// get the quadrant that would contain the D3DXVECTOR2
	// in reference to a given start node
	unsigned X = 0, Y = 0;
	X |= ((point.x >= node->pos.x) << 1);
	Y |= ((point.y >= node->pos.y) << 0);
	return (X | Y);
}



CQuadTreeNode* CQuadTree::childNode(const D3DXVECTOR2& v, CQuadTreeNode* node, UINT id)
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
		node->child[dir] = new CQuadTreeNode(newPos(dir, node), r, 8 * id + dir);
		if (node->child[dir]->range.x > (FLOAT)CGame::GetInstance()->GetBackBufferWidth() / 2)
			node->child[dir]->leaf = false;
		return node->child[dir];
	}
}


D3DXVECTOR2  CQuadTree::newPos(int direction, CQuadTreeNode* node)
{
	D3DXVECTOR2 v(node->pos.x, node->pos.y);
	switch (direction) {
	case LOWER_LEFT_QUAD:
		v.x -= node->range.x / 4.0;
		v.y -= node->range.y / 4.0;
		break;
	case UPPER_LEFT_QUAD:
		v.x -= node->range.x / 4.0;
		v.y += node->range.y / 4.0;
		break;
	case LOWER_RIGHT_QUAD:
		v.x += node->range.x / 4.0;
		v.y -= node->range.y / 4.0;
		break;
	case UPPER_RIGHT_QUAD:
		v.x += node->range.x / 4.0;
		v.y += node->range.y / 4.0;
		break;
	}
	return v;
}


/*by design, gameObject are stored only in leaf nodes
/newly created nodes are leaf nodes by default*/

void CQuadTree::insert(LPGAMEOBJECT data)
{
	float left, top, right, bottom;
	data->GetBoundingBox(left, top, right, bottom);
	RECT bounds = { (LONG)left, (LONG)top, (LONG)right, (LONG)bottom };

	insert(data, bounds, root);
}

void CQuadTree::insert(LPGAMEOBJECT data, RECT bounds, CQuadTreeNode* node)
{
	// Check if the bounding box is within this node.
	if (!RectInNode(bounds, node)) {
		return;
	}

	// push gameObject in deepest node (leaf)
	if (node->leaf) {
		if (data->IsDynamic()) {
			node->dynamicBucket.push_back({ bounds, data });
		}
		else {
			node->staticBucket.push_back({ bounds, data });
		}

		data->SetCurrentNode(node);
	}
	// current node is a stem node used for navigation
	else
	{
		// Check which child node completely contains the bounding box.
		bool inserted = false;
		for (int i = 0; i < 4; i++) {
			if (node->child[i] && RectInNode(bounds, node->child[i])) {
				insert(data, bounds, node->child[i]);
				inserted = true;
				break;
			}
		}

		// If it doesn't completely fit within any child node, store it in the current node.
		if (!inserted) {
			if (data->IsDynamic()) {
				node->dynamicBucket.push_back({ bounds, data });
			}
			else {
				node->staticBucket.push_back({ bounds, data });
			}

			data->SetCurrentNode(node);
		}
	}
}

bool CQuadTree::RectInNode(const RECT& rect, CQuadTreeNode* node)
{
	float halfRangeX = node->range.x / 2.0f;
	float halfRangeY = node->range.y / 2.0f;

	RECT nodeBounds = {
		(LONG)(node->pos.x - halfRangeX),
		(LONG)(node->pos.y - halfRangeY),
		(LONG)(node->pos.x + halfRangeX),
		(LONG)(node->pos.y + halfRangeY)
	};

	return (rect.left >= nodeBounds.left && rect.right <= nodeBounds.right &&
		rect.top >= nodeBounds.top && rect.bottom <= nodeBounds.bottom);
}

bool CQuadTree::RectIntersectNode(const RECT& rect, CQuadTreeNode* node)
{
	float halfRangeX = node->range.x / 2.0f;
	float halfRangeY = node->range.y / 2.0f;

	RECT nodeBounds = {
		(LONG)(node->pos.x - halfRangeX),
		(LONG)(node->pos.y - halfRangeY),
		(LONG)(node->pos.x + halfRangeX),
		(LONG)(node->pos.y + halfRangeY)
	};

	return !(rect.left > nodeBounds.right || rect.right < nodeBounds.left ||
		rect.top > nodeBounds.bottom || rect.bottom < nodeBounds.top);
}

bool CQuadTree::remove(LPGAMEOBJECT data)
{
	CQuadTreeNode* node = data->GetCurrentNode();
	if (!node) {
		return false;
	}

	// Select the appropriate bucket (static or dynamic).
	vector<pair<RECT, LPGAMEOBJECT>>& bucket =
		data->IsDynamic() ? node->dynamicBucket : node->staticBucket;

	for (auto it = bucket.begin(); it != bucket.end(); ++it) {
		if (it->second == data) {
			bucket.erase(it);
			data->SetCurrentNode(nullptr);
			return true;
		}
	}

	return false;
}

void CQuadTree::UpdateDynamicObject(LPGAMEOBJECT object)
{
	if (!object->IsDynamic()) {
		return;
	}

	CQuadTreeNode* currentNode = object->GetCurrentNode();
	if (!currentNode) {
		insert(object);
		return;
	}

	float left, top, right, bottom;
	object->GetBoundingBox(left, top, right, bottom);
	RECT newBounds = { (LONG)left, (LONG)top, (LONG)right, (LONG)bottom };

	// Check if the object is still within the current node.
	if (RectInNode(newBounds, currentNode)) {
		// Still within the current node, update the bounding box.
		for (auto& pair : currentNode->dynamicBucket) {
			if (pair.second == object) {
				pair.first = newBounds;
				break;
			}
		}
		return;
	}

	remove(object);

	insert(object);
}


/*	once a gameObject is removed from a leaf node's bucket
	check if there are any other gameobjects in that node (which is an empty node)
	if not, remove it and do the same with its parent node.
*/

//void  CQuadTree::reduce(stack <CQuadTreeNode*>& nodes)
//{
//	nodes.pop();
//	while (!nodes.empty()) {
//		CQuadTreeNode* top = nodes.top();
//		for (int i = 0; i < 4; ++i) {
//			if (top->child[i] && !top->child[i]->leaf) {
//				return;
//			}
//		}
//		int emtyChild = 0;
//		for (int i = 0; i < 4; ++i) {
//			if (top->child[i] && top->child[i]->bucket.size() == 0) {
//				delete top->child[i];
//				top->child[i] = NULL;
//
//			}
//			if (!top->child[i])
//				emtyChild++;
//		}
//
//		if (emtyChild == 4)
//			top->leaf = true;
//		nodes.pop();
//	}
//	return;
//}

vector<LPGAMEOBJECT> CQuadTree::renderObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY)
{
	vector<LPGAMEOBJECT> results;
	queue<CQuadTreeNode*> nodes;
	nodes.push(root);

	// Create RECT from minXY and maxXY.
	RECT queryRegion = {
		(LONG)minXY.x, (LONG)minXY.y,
		(LONG)maxXY.x, (LONG)maxXY.y
	};

	while (!nodes.empty()) {
		CQuadTreeNode* top = nodes.front();

		// Check if the node intersects with the query region.
		if (!RectIntersectNode(queryRegion, top)) {
			nodes.pop();
			continue;
		}

		if (top->leaf) {
			processNodeObjects(top->staticBucket, queryRegion, results);
			processNodeObjects(top->dynamicBucket, queryRegion, results);
		}
		else {
			for (int i = 0; i < 4; ++i) {
				if (top->child[i]) {
					nodes.push(top->child[i]);
				}
			}
		}
		nodes.pop();
	}

	// Remove duplicates.
	sort(results.begin(), results.end());
	results.erase(unique(results.begin(), results.end()), results.end());

	return results;
}

void CQuadTree::processNodeObjects(const vector<pair<RECT, LPGAMEOBJECT>>& bucket, const RECT& queryRegion, vector<LPGAMEOBJECT>& results)
{
	for (const auto& pair : bucket) {
		// Check if the object's bounding box intersects with the query region.
		if (RectIntersectsRect(pair.first, queryRegion)) {
			LPGAMEOBJECT obj = pair.second;
			if (!obj->IsUpdated()) {
				obj->SetUpdateState(true);
				results.push_back(obj);
			}
		}
	}
}

bool CQuadTree::RectIntersectsRect(const RECT& rect1, const RECT& rect2)
{
	return !(rect1.left > rect2.right || rect1.right < rect2.left ||
		rect1.top > rect2.bottom || rect1.bottom < rect2.top);
}


/*void CQuadTree::addAllObjectToResults(CQuadTreeNode* node, vector<pair <D3DXVECTOR2, LPGAMEOBJECT> >& results)
{
	if (node->leaf) {
		for (pair <D3DXVECTOR2, LPGAMEOBJECT> p : node->bucket) {
			LPGAMEOBJECT obj = p.second;
			if (!obj->IsUpdated()) {
				obj->Render();
				obj->SetUpdateState(true);
				results.push_back(p);
			}
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			if (node->child[i]) {
				addAllObjectToResults(node->child[i], results);
			}
		}
	}
}*/


bool CQuadTree::pointInRegion(const D3DXVECTOR2& point, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY)
{
	if ((point.x >= minXY.x) && (point.x < maxXY.x) && (point.y >= minXY.y) && (point.y < maxXY.y)) {
		return true;
	}
	else {
		return false;
	}
}


enclosure_status CQuadTree::getEnclosureStatus(const D3DXVECTOR2& pos, const D3DXVECTOR2& range, const D3DXVECTOR2& minXY, const D3DXVECTOR2& maxXY)
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


void CQuadTree::render()
{
	//Because all objects are stored in leaf nodes, only leaf nodes are drawn.
	float cx, cy;
	CCamera* cam = CCamera::GetInstance();
	CGame* g = CGame::GetInstance();
	cam->GetCameraPos(cx, cy);

	D3DXVECTOR2 minXY(cx, cy);
	D3DXVECTOR2 maxXY(cx + g->GetBackBufferWidth(), cy + g->GetBackBufferHeight());

	vector<LPGAMEOBJECT> dataList = renderObjectsInRegion(minXY, maxXY);


	for (auto obj : dataList) {
		obj->Render();
	}
}

void CQuadTree::UpdateDynamicObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY, DWORD dt)
{
	// Expand the update area to include objects around the viewport.
	float margin = 100.0f;
	D3DXVECTOR2 expandedMin(minXY.x - margin, minXY.y - margin);
	D3DXVECTOR2 expandedMax(maxXY.x + margin, maxXY.y + margin);

	vector<LPGAMEOBJECT> dynamicObjects;
	queue<CQuadTreeNode*> nodes;
	nodes.push(root);

	// Create RECT from the expanded area.
	RECT expandedRegion = {
		(LONG)expandedMin.x, (LONG)expandedMin.y,
		(LONG)expandedMax.x, (LONG)expandedMax.y
	};

	while (!nodes.empty()) {
		CQuadTreeNode* top = nodes.front();

		// Check if the node intersects with the update area.
		if (!RectIntersectNode(expandedRegion, top)) {
			nodes.pop();
			continue;
		}

		if (top->leaf) {
			for (const auto& pair : top->dynamicBucket) {
				LPGAMEOBJECT obj = pair.second;
				if (!obj->IsUpdated() && RectIntersectsRect(pair.first, expandedRegion)) {
					obj->SetUpdateState(true);
					dynamicObjects.push_back(obj);
				}
			}
		}
		else {
			for (int i = 0; i < 4; ++i) {
				if (top->child[i]) {
					nodes.push(top->child[i]);
				}
			}
		}
		nodes.pop();
	}

	// Remove duplicates.
	sort(dynamicObjects.begin(), dynamicObjects.end());
	dynamicObjects.erase(unique(dynamicObjects.begin(), dynamicObjects.end()), dynamicObjects.end());

	for (auto obj : dynamicObjects) {
		obj->Update(dt);

		UpdateDynamicObject(obj);
	}
}
