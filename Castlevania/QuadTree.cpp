#include "QuadTree.h"
#include "Camera.h"
#include "Zombie.h"


#include <fstream>
#include <string.h>




CQuadTree::CQuadTree(D3DXVECTOR2 pos, D3DXVECTOR2 range,LPCWSTR filePath)
{
	root = new CQuadTreeNode(pos, range);
	this->filePath = filePath;
}


CQuadTree::~CQuadTree()
{
	delete root;
}


vector <pair<D3DXVECTOR2, LPGAMEOBJECT>> CQuadTree::LoadGameObjects() {
	vector <pair<D3DXVECTOR2, LPGAMEOBJECT>> fullBucket;
	ifstream file(filePath, ios::in);

	std::string line;
	std::getline(file, line);
	int id, type;
	float x, y, w, h;
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
		fullBucket.push_back({ D3DXVECTOR2(x,y),obj });
	}
	file.close();
	return fullBucket;
}


LPGAMEOBJECT  CQuadTree::CreateGameObjectByType(int type,int x,int y) {
	switch (type)
	{
	case static_cast<int>(Type::ZOMBIE):
		return new CZombie(x,y, DIRECTION_POSITIVE);
		break;
	}
}


void CQuadTree::insertObjectIntoTree()
{
	vector < pair <D3DXVECTOR2, LPGAMEOBJECT>> fullBucket = LoadGameObjects();
	for (pair <D3DXVECTOR2, LPGAMEOBJECT> p : fullBucket) {
		CQuadTreeObject* object = new CQuadTreeObject(p.second, p.first);
		registerDynamicObject(object, insert(p.first, p.second, root));
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

CQuadTreeNode* CQuadTree::insert(D3DXVECTOR2 v, LPGAMEOBJECT data, CQuadTreeNode* node)
{
	// push gameObject in deepest node (leaf)
	if (node->leaf) {
		node->bucket.push_back({ v, data });
		return node;
	}
	// current node is a stem node used for navigation
	else
	{
		return insert(v, data, childNode(v, node, node->id));
	}
}

bool  CQuadTree::remove(D3DXVECTOR2 v, LPGAMEOBJECT data)
{
	stack <CQuadTreeNode*> nodes;
	nodes.push(root);
	CQuadTreeNode* top = nodes.top();
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
void  CQuadTree::reduce(stack <CQuadTreeNode*>& nodes)
{
	nodes.pop();
	while (!nodes.empty()) {
		CQuadTreeNode* top = nodes.top();
		for (int i = 0; i < 4; ++i) {
			if (top->child[i] && !top->child[i]->leaf) {
				return;
			}
		}
		int emtyChild = 0;
		for (int i = 0; i < 4; ++i) {
			if (top->child[i] && top->child[i]->bucket.size() == 0) {
				delete top->child[i];
				top->child[i] = NULL;

			}
			if (!top->child[i])
				emtyChild++;
		}

		if (emtyChild == 4)
			top->leaf = true;
		nodes.pop();
	}
	return;
}

vector <pair <D3DXVECTOR2, LPGAMEOBJECT> > CQuadTree::renderObjectsInRegion(D3DXVECTOR2 minXY, D3DXVECTOR2 maxXY)
{

	vector<pair<D3DXVECTOR2, LPGAMEOBJECT>> results;
	queue <CQuadTreeNode*> nodes;
	nodes.push(root);

	while (!nodes.empty()) {
		CQuadTreeNode* top = nodes.front();
		if (top->leaf) {
			enclosure_status status = getEnclosureStatus(top->pos, top->range, minXY, maxXY);
			switch (status) {
				// this node is completely contained within the search region
			case NODE_CONTAINED_BY_REGION:
				// add all elements to results
				addAllObjectToResults(top, results);
				break;

				// this node is partially contained by the region
			case  NODE_PARTIALLY_IN_REGION:
				// search through this leaf node's bucket
				for (int i = 0; i < top->bucket.size(); ++i) {
					// check if this point is in the region
					if (pointInRegion(top->bucket[i].first, minXY, maxXY)) {
						LPGAMEOBJECT obj = top->bucket[i].second;
						if (obj->IsUpdated()) {
							obj->Render();
							obj->SetUpdateState(false);
							results.push_back(top->bucket[i]);
						}
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

void CQuadTree::addAllObjectToResults(CQuadTreeNode* node, vector<pair <D3DXVECTOR2, LPGAMEOBJECT> >& results)
{
	if (node->leaf) {
		for (pair <D3DXVECTOR2, LPGAMEOBJECT> p : node->bucket) {
			LPGAMEOBJECT obj = p.second;
			if (obj->IsUpdated()) {
				obj->Render();
				obj->SetUpdateState(false);
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
}


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
	if (root) {
		render(root);
	}
}


void CQuadTree::render(CQuadTreeNode* node)
{
	//Because all objects are stored in leaf nodes, only leaf nodes are drawn.
	float cx, cy;
	CCamera* cam = CCamera::GetInstance();
	CGame* g = CGame::GetInstance();
	cam->GetCameraPos(cx, cy);
	renderObjectsInRegion(
		D3DXVECTOR2(cx, cy),
		D3DXVECTOR2(cx + g->GetBackBufferWidth(), cy + g->GetBackBufferHeight())
	);
}

// Register a dynamic object with the Quadtree
void CQuadTree::registerDynamicObject(CQuadTreeObject* object, CQuadTreeNode* node)
{
	dynamicObjects.push_back(object);
	//insert(object->position, object->obj,root);
	object->currentNode =node;
}

// Unregister a dynamic object
void CQuadTree::unregisterDynamicObject(CQuadTreeObject* object)
{
	remove(object->position, object->obj);

	for (auto it = dynamicObjects.begin(); it != dynamicObjects.end(); ++it) {
		if (*it == object) {
			dynamicObjects.erase(it);
			break;
		}
	}

	object->currentNode = nullptr;
}

// Update position of a dynamic object
void CQuadTree::updateDynamicObject(CQuadTreeObject* object, D3DXVECTOR2 newPosition, bool force)
{
	if (object->position.x == newPosition.x && object->position.y == newPosition.y)
		return;

	CQuadTreeNode* newNode = findNodeForPoint(newPosition);

	if (!force && newNode == object->currentNode) {
		object->position = newPosition;
		return;
	}

	remove(object->position, object->obj);
	object->position = newPosition;
	insert(object->position, object->obj,root);
	object->currentNode = newNode;
}

// Update all dynamic objects
void CQuadTree::updateAllDynamicObjects(float dt)
{
	float cx, cy;
	CCamera::GetInstance()->GetCameraPos(cx, cy);

	float updateMargin = 200.0f; 
	D3DXVECTOR2 minXY(cx - updateMargin, cy - updateMargin);
	D3DXVECTOR2 maxXY(cx + CGame::GetInstance()->GetBackBufferWidth() + updateMargin,
		cy + CGame::GetInstance()->GetBackBufferHeight() + updateMargin);

	for (auto object : dynamicObjects) {
		float x, y;
		object->obj->GetPosition(x, y);
		D3DXVECTOR2 newPosition(x, y);

		bool inUpdateRegion =
			newPosition.x >= minXY.x && newPosition.x <= maxXY.x &&
			newPosition.y >= minXY.y && newPosition.y <= maxXY.y;

		object->timeSinceLastUpdate += dt;

		if (inUpdateRegion || object->timeSinceLastUpdate >= object->updateInterval * 3) {
			bool shouldUpdate = object->timeSinceLastUpdate >= object->updateInterval;

			if (object->currentNode) {
				D3DXVECTOR2 halfRange = object->currentNode->range * 0.5f;
				bool stillInNode =
					newPosition.x >= object->currentNode->pos.x - halfRange.x &&
					newPosition.x <= object->currentNode->pos.x + halfRange.x &&
					newPosition.y >= object->currentNode->pos.y - halfRange.y &&
					newPosition.y <= object->currentNode->pos.y + halfRange.y;

				shouldUpdate = shouldUpdate || !stillInNode;
			}

			if (shouldUpdate) {
				updateDynamicObject(object, newPosition, true);
				object->timeSinceLastUpdate = 0.0f;
			}
			else {
				object->position = newPosition;
			}
		}
		else {
			object->position = newPosition;
		}
	}
}

// Find node containing a point
CQuadTreeNode* CQuadTree::findNodeForPoint(D3DXVECTOR2 point)
{
	return findNodeForPoint(point, root);
}

// Recursive function to find node containing a point
CQuadTreeNode* CQuadTree::findNodeForPoint(D3DXVECTOR2 point, CQuadTreeNode* startNode)
{
	D3DXVECTOR2 halfRange = startNode->range * 0.5f;
	if (point.x < startNode->pos.x - halfRange.x ||
		point.x > startNode->pos.x + halfRange.x ||
		point.y < startNode->pos.y - halfRange.y ||
		point.y > startNode->pos.y + halfRange.y) {
		return nullptr; 
	}

	if (startNode->leaf) {
		return startNode;
	}

	int dir = direction(point, startNode);
	if (startNode->child[dir]) {
		CQuadTreeNode* childResult = findNodeForPoint(point, startNode->child[dir]);
		if (childResult) {
			return childResult;
		}
	}
	return startNode;
}
