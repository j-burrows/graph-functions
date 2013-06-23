 /*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	kruskal.h
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	An algorithm that can find the smallest weight of a complete graphg using
 |				Kruskal's algorithm.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		April 8th 2013
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/

#ifndef KRUSKAL_H
#define KRUSKAL_H 1

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "quicksort.h"

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	kruskal_method
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	Returns a tree (array of edges) with the minimum weight of a given complete
 |				graph by using Kruskal's algorithm.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	@param:		current		The complete graph whos minimum cost spanning tree will be made
 |	@return:	min_tree	The minimum spanning tree produced
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Assumptions:	The given graph is completed (no unconnected sections).
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
extern graph* kruskal_method(graph* current);

#endif
