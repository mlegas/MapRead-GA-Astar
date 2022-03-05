#include "Node.h"
#include <iomanip>
#include <queue>
#include <cmath>

Node::Node(int xp, int yp, int d, int p)
{
	xPos = xp; yPos = yp; level = d; priority = p;
	m_dir = 8;
}

int Node::getxPos() const 
{ 
	return xPos; 
}
int Node::getyPos() const 
{ 
	return yPos; 
}
int Node::getLevel() const 
{ 
	return level; 
}
int Node::getPriority() const 
{ 
	return priority; 
}

// give better priority to going strait instead of diagonally
void Node::nextLevel(const int & i) // i: direction
{
	level += (m_dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

void Node::updatePriority(const int & xDest, const int & yDest)
{
	priority = level + estimate(xDest, yDest) * 10; //A*
}

// Estimation function for the remaining distance to the goal.
const int & Node::estimate(const int & xDest, const int & yDest) const
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	//d = static_cast<int>(sqrt(xd*xd + yd*yd));

	// Manhattan distance
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	d = std::max(abs(xd), abs(yd));

	return(d);
}
