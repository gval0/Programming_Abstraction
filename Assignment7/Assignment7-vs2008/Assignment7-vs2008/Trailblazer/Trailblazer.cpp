/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "set.h"
#include "random.h"
#include "foreach.h"
using namespace std;


/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {

	TrailblazerPQueue<Loc> queue;
	Map<Loc, double> costsMap;
	Map<Loc, Loc> pathMap;
	
	double h = heuristic(start, end, world);
	queue.enqueue(start, h);
	costsMap.put(start, h);
	pathMap.put(start, makeLoc(-1, -1));
	colorCell(world, start, YELLOW);

	Loc cur;
	while(!queue.isEmpty()){
		cur = queue.dequeueMin();
		colorCell(world, cur, GREEN);
		if(cur == end) break;
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				if(world.inBounds(cur.row + i, cur.col + j)){
					Loc temp = makeLoc(cur.row + i, cur.col + j);
					if(cur == temp) continue;
					double dist = costsMap.get(cur) + costFn(cur, temp, world);
					if(costsMap.containsKey(temp)) {
						if (costsMap.get(temp) >= dist){
							queue.decreaseKey(temp, dist + heuristic(temp, end, world));
							costsMap.put(temp, dist);
							pathMap.put(temp, cur);
						}
					} else {
						colorCell(world, temp, YELLOW);
						queue.enqueue(temp, dist + heuristic(temp, end, world));
						costsMap.put(temp, dist);
						pathMap.put(temp, cur);
					}

				}
			}
		} 

	}
	Vector<Loc> result;
	result.insert(0, end);
	Loc l;
	while(true){
		if(cur == start) break;
		l = pathMap.get(cur);
		result.insert(0, l);
		cur = l;
	}
	result.insert(0, start);
	return result;
	}


Set<Edge> createMaze(int numRows, int numCols) {
	TrailblazerPQueue<Edge> queue;
	Map<Loc, int> clusters;
	int index = 0;
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			Loc cur = makeLoc(i,j);
			clusters.put(cur, index);
			index ++;
			int row = i + 1;
			int col = j;
			if((row >= 0 && row < numRows) && (col >= 0 && col < numCols)){
				Loc next = makeLoc(row, col);
				Edge newEdge = makeEdge(cur, next);
				queue.enqueue(newEdge, randomInteger(0,numRows));	
			}
			row = i;
			col = j + 1;
			if((row >= 0 && row < numRows) && (col >= 0 && col < numCols)){
				Loc next = makeLoc(row, col);
				Edge newEdge = makeEdge(cur, next);
				queue.enqueue(newEdge, randomInteger(0,numRows));	
			}
		}
	}

	Set<Edge> result;
	while(queue.size() >= 2){
		Edge cur = queue.dequeueMin();
		if(clusters[cur.start] != clusters[cur.end]){
			int keeperCluster = clusters[cur.start];
			int notNeeded = clusters[cur.end];
			foreach(Loc curLoc in clusters){
				if(clusters[curLoc] == notNeeded) clusters[curLoc] = keeperCluster;
			}
			result.add(cur);
		}
	}
    return result;
}
