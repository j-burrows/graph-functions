 /*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	kruskal.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Purpose:	An algorithm that can find the smallest weight of a complete graphg using
 |				Kruskal's algorithm.
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Author:		Jonathan Burrows
 |	Date:		April 8th 2013
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
#include "kruskal.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	kruskal_method
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
graph* kruskal_method(graph* current){
	graph* minSpanningTree;
	int i;
	edgePointer* nonTreeEdges;
	
	if( (minSpanningTree = create_graph()) == NULL){
		return NULL;
	}
	if((nonTreeEdges = (edgePointer*) malloc(current->edge_num*sizeof(edgePointer)))==NULL){
		delete_graph(minSpanningTree);
		minSpanningTree = NULL;
		return NULL;
	}

	/*	Copies the contents into a set of edges then sorts them from smallest to largest. */
	for( i=0; i<current->edge_num; i++){
		nonTreeEdges[i] = current->edges[i];
	}
	quick_sort(nonTreeEdges,current->edge_num);
	
	/*	Starting from the smallest weighted edges, the set is traversed. It is checked if
		the current edge would cause a cycle (both vectors are already in graph), and if
		not, the edge is added to it.	*/
	for( i = 0; i < current->edge_num; i++){
		if( (add_vector(minSpanningTree, nonTreeEdges[i]->start) == -1) 
		  && (add_vector(minSpanningTree, nonTreeEdges[i]->end) == -1)){
			/*	A cycle could be possibly made if added, it is checked to see if so.	*/
			if(0 == 1){
				/*	Adding this edge would produce a cycle, it cannot be added.	*/
				continue;
			}
		}
		
		printf("| %d |",i);
		add_edge(minSpanningTree,nonTreeEdges[i]);
		
	}
	
	free(nonTreeEdges);
	nonTreeEdges = NULL;
	return minSpanningTree;
}
