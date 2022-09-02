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
#include <math.h>

#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pqNode{
	void* val;
	int pri;
	struct pqNode* left;
	struct pqNode* right;
};

struct pq{
	struct pqNode* root;
	float nodeCount;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* temp = malloc(sizeof(struct pq));
	temp->root = NULL;
	temp->nodeCount = 0;
	
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
void pq_free_node(struct pqNode* node){
	if(node->left != NULL){
		pq_free_node(node->left);
		free(node->left);
	}
	if(node->right != NULL){
		pq_free_node(node->right);
		free(node->right);
	}
	printf("\n=== result: %d", node->pri);
}

void pq_free(struct pq* pq) {
	pq_free_node(pq->root);
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
	if(pq->root == NULL){
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
 
int pq_insert_node(struct pqNode* node, struct pqNode* insert, float height){
	int nodeFound = 0;
		//printf("\n== ndepth: %f", height);
	
	if(node->left && height > 1){
		//printf("\n   goleft");
		nodeFound = pq_insert_node(node->left, insert, height-1);
	}
	if(node->right && height > 1 && nodeFound == 0){
		//printf("\n   gorigh");
		nodeFound = pq_insert_node(node->right, insert, height-1);
	}
	
	if(height == 1 && nodeFound == 0){
		if(node->left == NULL){
			//printf("\n   leftin");
			node->left = insert;
			nodeFound++;
		}else if(node->right == NULL){
			//printf("\n   righin");
			node->right = insert;
			nodeFound++;
		}
	}
	
	if(node->left){
		if(node->left->pri < node->pri){
			//printf("\n== swap left: c:%d < p:%d", node->left->pri, node->pri);
			int temp = node->pri;
			node->pri = node->left->pri;
			node->left->pri = temp;
			//printf("\n== result: c:%d ? p:%d", node->left->pri, node->pri);
			
			void* tempV = node->val;
			node->val = node->left->val;
			node->left->val = tempV;
		}
	}
	if(node->right){
		if(node->right->pri < node->pri){
			//printf("\n== swap right: %d < %d", node->right->pri, node->pri);
			int temp = node->pri;
			node->pri = node->right->pri;
			node->right->pri = temp;
			//printf("\n== result: %d ? %d", node->right->pri, node->pri);
			
			void* tempV = node->val;
			node->val = node->right->val;
			node->right->val = tempV;
		}
	}
	
	if(!nodeFound){
		//printf("\n== return");
	}
	
	return nodeFound;
}

void pq_insert(struct pq* pq, void* value, int priority){
	struct pqNode* insert = malloc(sizeof(struct pqNode));
	struct pqNode* insertVal = malloc(sizeof(void*));
	insertVal = value;
	insert->val = insertVal;
	insert->pri = priority;
		//printf("\n");
		//printf("\n== insert: %d", priority);
		//printf("\n== nd_cnt: %f", pq->nodeCount);
		//printf("\n== fullde: %f", ceil(log(pq->nodeCount+1)/log(2)));
		//printf("\n== opr_at: %f", floor(log(pq->nodeCount+1)/log(2)));
	if(pq->root == NULL){
		pq->root = insert;
	}else{
		pq_insert_node(pq->root, insert, floor(log(pq->nodeCount+1)/log(2)));
	}
	pq->nodeCount++;
	//pq_free_node(pq->root);
	return;
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
  return pq->root->val;
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
	//printf("\n== nd_cnt: %d", pq->root->pri);
  return pq->root->pri;
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

struct pqNode* pq_remove_first_node(struct pqNode* node, float height){
	struct pqNode* lastNode = NULL;
		//printf("\n== ndepth: %f", height);
	
	if(node->right != NULL && height > 1){
		//printf("\n   gorigh");
		lastNode = pq_remove_first_node(node->right, height-1);
	}
	if(node->left != NULL && height > 1 && lastNode == NULL){
		//printf("\n   goleft");
		lastNode = pq_remove_first_node(node->left, height-1);
	}
	
	if(node->right != NULL){
			//printf("\n   righfi");
		lastNode = node->right;
		node->right = NULL;
	}else if(node->left != NULL){
			//printf("\n   leftfi");
		lastNode = node->left;
		node->left = NULL;
	}
	
	if(lastNode != NULL){
		//printf("\n== return");
	}
	
	return lastNode;
}

void swap_nodes(struct pqNode* Cnode, struct pqNode* Pnode){
	int tempPri;
	void* tempVal;
	
	tempPri = Cnode->pri;
	Cnode->pri = Pnode->pri;
	Pnode->pri = tempPri;
			
	tempVal = Cnode->val;
	Cnode->val = Pnode->val;
	Pnode->val = tempVal;
}

void pq_sort_head(struct pqNode* node){
	if(node->left != NULL){
		if(node->left->pri < node->pri){
			swap_nodes(node->left, node);
			pq_sort_head(node->left);
		}
	}
	if(node->right != NULL){
		if(node->right->pri < node->pri){
			swap_nodes(node->right, node);
			pq_sort_head(node->right);
		}
	}
}

void* pq_remove_first(struct pq* pq){
	printf("\n== remove call done");
	void* returnVal;
	if(pq->root == NULL){
		returnVal = NULL;
	}else{
		returnVal = pq->root->val;
		//printf("\n== nd_cnt: %d", pq->root->pri);
		struct pqNode* lastNode;
		//printf("\n== nd_cnt: %f", pq->nodeCount);
		//printf("\n== opr_at: %f\n", ceil(log(pq->nodeCount+1)/log(2)));
		lastNode = pq_remove_first_node(pq->root, ceil(log(pq->nodeCount)/log(2)));
		pq->root->val = lastNode->val;
		pq->root->pri = lastNode->pri;
		pq->nodeCount--;
		pq_sort_head(pq->root);
	}
	return returnVal;
}

//2p+1 = left
//2p+2 = right

//floor((C-1)/2) = parent


/*
struct pqNode* pq_remove_first_node(struct pqNode* node, int height){ //undone
	int nodeFound = 0;
	struct pqNode* lastNode;
	
	if(node->right){
		nodeFound = pq_insert_node(node->right, height-1);
	}
	if(node->left && nodeFound == 0){
		nodeFound = pq_insert_node(node->left, height-1);
	}
	
	if(height == 1){
		if(node->right){
			lastNode = node->right;
			nodeFound++;
		}else if(node->left){
			lastNode = node->left;
			nodeFound++;
		}
	}
	
	if(node->left){
		if(node->left->pri > node->pri){
			int temp = node->pri;
			node->pri = node->left->pri;
			node->left->pri = temp;
			
			void* tempV = node->val;
			node->val = node->left->val;
			node->left->val = tempV;
		}
	}
	if(node->right){
		if(node->right->pri > node->pri){
			int temp = node->pri;
			node->pri = node->right->pri;
			node->right->pri = temp;
			
			void* tempV = node->val;
			node->val = node->right->val;
			node->right->val = tempV;
		}
	}
	
	return nodeFound;
}
*/




