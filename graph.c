 /*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	graph.c
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
#include "graph.h"


/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	create_graph
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
graph* create_graph(void){
	graph* graph_creating;
	if((graph_creating = (graph*) malloc(sizeof(graph)))==NULL){
		return NULL;
	}
	graph_creating->edge_num = 0;
	graph_creating->vector_num = 0;
	return graph_creating;
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	create_edge
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
edgePointer create_edge(vectorPointer start, vectorPointer end, int weight){
	edgePointer edge_creating;
	vectorPointer start_vec, end_vec;
	
	/*	Checks if edge is self edge, returns error value if so.	*/
	if( start->value == end->value){
		return NULL;
	}
	
	/*	Allocates memory and frees/returns error value if unsuccessful.	*/
	if( (edge_creating = (edgePointer) malloc(sizeof(edge))) == NULL ){
		return NULL;
	}
	if( (start_vec = (vectorPointer) malloc(sizeof(vector))) == NULL ){
		free(edge_creating);
		return NULL;
	}
	if( (end_vec = (vectorPointer) malloc(sizeof(vector))) == NULL ){
		free(start_vec);
		free(edge_creating);
		return NULL;
	}
	//The smallest value is assigned to the start vector
	if( start->value < end->value){
		start_vec->value = start->value;
		end_vec->value = end->value;
	}
	else{
		start_vec->value = end->value;
		end_vec->value = start->value;
	}
	
	//The edge is assigned vectors
	edge_creating->start = start_vec;
	edge_creating->end= end_vec;
	
	edge_creating->weight = weight;
	
	return edge_creating;
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	delete_edge
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
void delete_edge(edgePointer edge_deleting){
	free(edge_deleting->start);
	edge_deleting->start = NULL;
	free(edge_deleting->end);
	edge_deleting->end = NULL;
	free(edge_deleting);
	edge_deleting = NULL;
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	delete_graph
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
void delete_graph(graph* to_delete){
	int i;
	
	/*	Frees all allocated vectors.	*/
	for( i=0; i<to_delete->vector_num; i++){
		free(to_delete->vectors[i]);
		to_delete->vectors[i] = NULL;
	}
	
	/*Calls the delete function for the all the edges.*/
	for( i=0; i<to_delete->edge_num; i++){
		delete_edge(to_delete->edges[i]);
	}
	
	/*	Frees the memory allocated for the graph itself.	*/
	free(to_delete);
	to_delete = NULL;
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	create_vector
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
vectorPointer create_vector(int value){
	vectorPointer vec_created;
	//Allocates memory to the new vector, and returns error value if unsuccessful.
	if((vec_created = (vectorPointer) malloc(sizeof(vector)))==NULL){
		return NULL;
	}
	vec_created->value = value;
	
	return vec_created;
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	add_vector
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
int add_vector(graph* current, vectorPointer vec_adding){
	int i;
	vectorPointer to_add;
	
	/*	Graph is searched to see if vector is already in and returns -1 if so.	*/
	for( i=0; i<current->vector_num; i++){
		if( vec_adding->value == current->vectors[i]->value){
			return -1;
		}
	}
	
	//Allocates memory for the copier then clones it.
	if( (to_add = (vectorPointer) malloc(sizeof(vector))) == NULL){
		return 0;
	}
	to_add->value = vec_adding->value;
	
	//Vector is added and the number incrimented.
	current->vectors[current->vector_num++] = to_add;
	return 1;
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	add_edge
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
int add_edge(graph* current, edgePointer edg_adding){
	int i;
	edgePointer to_add;
	
	/*	Adds the vectors if they are not already added.*/
	add_vector(current, edg_adding->start);
	add_vector(current, edg_adding->end);
	
	/*	Checks if the edge is already in the graph. If so, it is not added.*/
	for( i=0; i<current->edge_num; i++){
		if( current->edges[i]->start->value == edg_adding->start->value
		  &&current->edges[i]->end->value == edg_adding->end->value){
			return -1;
		}
	}
	
	/*	Allocates memory for the clone and then gives it the value. */
	if( (to_add=create_edge(edg_adding->start, edg_adding->end, edg_adding->weight))==NULL){
		return 0;
	}
	
	/*	Adds the cloned edge to the graph.	*/
	current->edges[current->edge_num++] = to_add;
	return 1;
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	fprint_graph
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
void fprint_graph(FILE* stream, graph* to_print){
	int total_weight = 0;
	int i;
	
	/*	The vectors are printed off.	*/
	fprintf(stream, "\n\nVectors:\n");
	for(i=0; i<to_print->vector_num; i++){
		fprintf(stream, "\t%d", to_print->vectors[i]->value);
	}
	
	/*	The edges are printed off.	*/
	fprintf(stream, "\n\nEdges:\n");
	for(i=0; i<to_print->edge_num; i++){
		fprintf(stream, "\t(%d,%d)w:%d", to_print->edges[i]->start->value,
				to_print->edges[i]->end->value,to_print->edges[i]->weight);
		total_weight += to_print->edges[i]->weight;
	}
	fprintf(stdout, "\nTotal Weight:\t%d",total_weight);
}
