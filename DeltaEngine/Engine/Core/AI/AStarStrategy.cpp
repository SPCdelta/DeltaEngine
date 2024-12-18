#include "AStarStrategy.hpp"

std::vector<Math::Vector2> AStarStrategy::CalculatePath(Math::Vector2& start, Math::Vector2& end, int range, int step)
{
	std::unordered_map<Math::Vector2, Node*, Vector2Hash> nodeMap;
	InitializeNodesAround(start, range, step, nodeMap);

	std::unordered_map<Node*, double> g_costs;
	std::unordered_map<Node*, Node*> predecessors;
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> pq;

    auto heuristic = [&](const Math::Vector2& a, const Math::Vector2& b) 
    {
        return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY()); // Manhattan distance
    };
      
    Node* startNode = CreateNode(start);
	g_costs[startNode] = 0.0;
	pq.push({0.0, startNode});

    while (!pq.empty()) 
    {
        auto [current_f_cost, current_node] = pq.top();
        pq.pop();

        if (current_node->tag != "visited") 
            current_node->tag = "visited";

        if (current_node->position == end) 
            break;

        // N, E, S, W and diagonals
        const std::vector<Math::Vector2> directions = 
        {
			{1, 0}, {-1, 0},  {0, 1},  {0, -1},	
			{1, 1}, {-1, -1}, {1, -1}, {-1, 1}	 
		};
            
        for (auto& dir : directions) 
        {
			Math::Vector2 neighborPos = current_node->position + dir; 

            if (!IsWalkable(neighborPos))
				continue;

            Node* neighbor;
			if (nodeMap.find(neighborPos) == nodeMap.end())
			{
				neighbor = CreateNode(neighborPos);
				nodeMap[neighborPos] = neighbor;
			}
			else
			{
				neighbor = nodeMap[neighborPos];
			}

            if (neighbor->tag == "visited")
				continue;
			else
				neighbor->tag = "visited";
            
            double tentative_g_cost = g_costs[current_node] + 1.0;

            if (tentative_g_cost < g_costs[neighbor]) 
            {
                g_costs[neighbor] = tentative_g_cost;
                double h_cost = heuristic(neighbor->position, end);
                double f_cost = tentative_g_cost + h_cost;

                predecessors[neighbor] = current_node;
                pq.push({f_cost, neighbor});
            }
        }
    }

    std::vector<Math::Vector2> path;
	Node* endNode = CreateNode(end);
    for (Node* at = endNode; at; at = predecessors[at]) 
    {
        path.push_back(at->position);
		at->tag = "path";
    }

    for (auto& entry : nodeMap)
		delete entry.second;
	nodeMap.clear();
	delete startNode;
	delete endNode;

    std::reverse(path.begin(), path.end());
    return path;
}

Node* AStarStrategy::CreateNode(const Math::Vector2& position, Node* parent)
{
    Node* newNode = new Node(position, parent);   
    newNode->tag = "normal";
    return newNode;
}

void AStarStrategy::InitializeNodesAround(Math::Vector2 center, int range, int step, std::unordered_map<Math::Vector2, Node*, Vector2Hash>& nodeMap) 
{
    for (int x = -range; x <= range; x += step) 
    {
        for (int y = -range; y <= range; y += step) 
        {
            Math::Vector2 position = center + Math::Vector2(x, y);
            if (IsWalkable(position) && nodeMap.find(position) == nodeMap.end()) 
            {
                Node* newNode = CreateNode(position);
                nodeMap[position] = newNode;
            }
        }
    }
}

bool AStarStrategy::IsWalkable(const Math::Vector2& position) // TODO when we have walls
{
	bool isWalkable = true;	

	//_rigidbody.onTriggerEnter.Register(
	//	[&](Collider& collider)
	//	{
	//		// Check if the collider is something that blocks movement, like a wall or obstacle
	//		if (collider.transform.gameObject->GetTag() == "Wall")	
	//		{
	//			isWalkable = false;	
	//		}
	//	});

	//_rigidbody.onTriggerExit.Register(
	//	[&](Collider& collider)
	//	{
	//		if (collider.transform.gameObject->GetTag() == "Wall")	 
	//		{
	//			isWalkable = true; 
	//		}
	//	});

	// If collision with a wall, return false (not walkable)
	return isWalkable;
}
