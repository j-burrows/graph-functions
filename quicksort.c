/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Filename:	quick.c	
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
#include "quicksort.h"

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Subroutine:	quick_sort
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
void quick_sort(edgePointer edge_list[], size_t list_len){
	q_sort(edge_list, 0, list_len-1);
}

/*-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 |	Function:	q_sort
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
*/
int q_sort(edgePointer edge_list[], int first, int last){
	int key;
	int left_bar, right_bar, pivot;
	edgePointer temp;
	
	/*	If the left and right pivotes dont cross (the size is greater than one), perform 
		the quick sort on.	*/
	if( first < last){
		pivot = (first+last)/2;					//The pivot is chosen.
		SWAP(edge_list[first], edge_list[pivot], temp);	//Pivot value is moved to front
		key = edge_list[first]->weight;			//The key is set to value of pivot.
		left_bar = first+1;						//Left bar is set to the value beside pivot
		right_bar = last;
		
		/*	While the left and right bars dont cross, the values greater than the pivot are
			placed on the right side, and smaller than are placed on left side.	*/
		while(left_bar <= right_bar){
			/*The left bar is shifted to end or the first value larger than pivot value.*/
			while((left_bar <= last) && (edge_list[left_bar]->weight <= key)){
				left_bar++;
			}
			/*The right bar is shifted to end or first value smaller than the pivot value.*/
			while( (right_bar >= first) && (edge_list[right_bar]->weight > key)){
				right_bar--;
			}
			/*If the two values at the bars are out of order, they are swapped.*/
			if(left_bar<right_bar){
				SWAP(edge_list[left_bar], edge_list[right_bar], temp);
			}
		}
		/*The pivot value is returned to the list in its ordered spot.*/
		SWAP(edge_list[first], edge_list[right_bar], temp);
		
		/*	The left and right sides of the pivot are sorted in the same manner*/
		q_sort(edge_list, first, right_bar-1);
		q_sort(edge_list, right_bar+1, last);
	}

	return 0;
}
