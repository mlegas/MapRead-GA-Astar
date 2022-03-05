#include <iostream>
#include <iomanip>
#include <queue>
#include "Maze.h"
#include "Node.h"
#include <string>
#include <cmath>
#include <ctime>
#include <vector>

// Determine priority (in the priority queue)
bool operator<(const Node & a, const Node & b)
{
	return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
std::vector<int> pathFind(Maze &_maze)
{
	std::vector<int> path;
	const int dir = 8; // number of possible directions to go at any position
				   // if dir==4
				   //static int dx[dir]={1, 0, -1, 0};
				   //static int dy[dir]={0, 1, 0, -1};
				   // if dir==8
	int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	int c;

	std::vector<std::vector<int>> closed_nodes_map(_maze.getY(), std::vector<int>(_maze.getX(), 0));
	std::vector<std::vector<int>> open_nodes_map(_maze.getY(), std::vector<int>(_maze.getX(), 0));
	std::vector<std::vector<int>> dir_map(_maze.getY(), std::vector<int>(_maze.getX(), 0));

	std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes

	int pqi = 0; // pq index

	Node* n0;
	Node* m0;
	int i, j, x, y, xdx, ydy;

	// create the start node and push into list of open nodes
	n0 = new Node(_maze.getStartX(), _maze.getStartY(), 0, 0);
	n0->updatePriority(_maze.getEndX(), _maze.getEndY());
	pq[pqi].push(*n0);
	open_nodes_map.at(_maze.getStartY()).at(_maze.getStartX()) = n0->getPriority(); // mark it on the open nodes map

											  // A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new Node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map.at(y).at(x) = 0;
		// mark it on the closed nodes map
		closed_nodes_map.at(y).at(x) = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == _maze.getEndX() && y == _maze.getEndY())
		{
			while (!(x == _maze.getStartX() && y == _maze.getStartY()))
			{
				j = dir_map.at(y).at(x);
				c = (j + dir / 2) % dir;
				path.push_back(c);
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>_maze.getX() - 1 || ydy<0 || ydy>_maze.getY() - 1 || _maze.getMap().at(ydy).at(xdx) == 1
				|| closed_nodes_map.at(ydy).at(xdx) == 1))
			{
				// generate a child node
				m0 = new Node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(_maze.getEndX(), _maze.getEndY());

				// if it is not in the open list then add into that
				if (open_nodes_map.at(ydy).at(xdx) == 0)
				{
					open_nodes_map.at(ydy).at(xdx) = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map.at(ydy).at(xdx) = (i + dir / 2) % dir;
				}
				else if (open_nodes_map.at(ydy).at(xdx)>m0->getPriority())
				{
					// update the priority info
					open_nodes_map.at(ydy).at(xdx) = m0->getPriority();
					// update the parent direction info
					dir_map.at(ydy).at(xdx) = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return path; // no route found
}