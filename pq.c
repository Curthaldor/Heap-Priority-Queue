/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */

struct pq{
	struct dynarray* dap;
	struct dynarray* dav;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* temp = malloc(sizeof(struct pq));
	temp->dap = dynarray_create();
	temp->dav = dynarray_create();
	return temp;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */

void pq_free(struct pq* pq) {
	dynarray_free(pq->dap);
	dynarray_free(pq->dav);
	free(pq);
}



/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq){
	int temp = 0;
	if(dynarray_size(pq->dav) == 0){
		temp = 1;
	}
	return temp;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */

void arr_report(dap){
	for(int i = 0; i < dynarray_size(dap); i++){
		printf("\n== %d, %p", i, dynarray_get(dap, i));
	}
	printf("\n== endport\n");
}

void pq_insert(struct pq* pq, void* value, int priority){
	int i = 0;
	for(; i < dynarray_size(pq->dap); i++){
		if(dynarray_get(pq->dap, i) > priority){
			break;
		}
	}
	dynarray_insert(pq->dav, i, value);
	dynarray_insert(pq->dap, i, priority);
	//arr_report(pq->da);
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	return dynarray_get(pq->dav, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	return dynarray_get(pq->dap, 0);
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

void* pq_remove_first(struct pq* pq){
	void* temp = dynarray_get(pq->dav, 0);
	dynarray_remove(pq->dav, 0);
	dynarray_remove(pq->dap, 0);
	return temp;
}

//2p+1 = left child
//2p+2 = right child

//floor((C-1)/2) = parent

//       0
//   1       2
// 3   4   5   6
//7 8 9 0 1 2 3 4



