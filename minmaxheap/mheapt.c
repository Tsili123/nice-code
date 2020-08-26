#include "mheapt.h"

// new tree
HeapTree* new_heap_tree(){
    HeapTree* mtree = malloc(sizeof(HeapTree));
    mtree->root = NULL;
    mtree->next_free=NULL;
    mtree->h=0;
    return mtree;
}


// add new node  or update one
HeapNode* new_node(HeapTree* tree, char* disease, int counter){
	//printf("%s\n",disease);
    if(tree->root==NULL){
        //if tree is emtpy
        HeapNode* node = malloc(sizeof(HeapNode));
        node->disease = disease;
        node->counter = counter;
        node->child_a   = NULL;
        node->child_b  = NULL;
        node->parent = NULL;
        tree->root = node;
        tree->next_free = node;
        return node;
    }else{
        // search to find same node
        HeapNode* temp = search_tree(tree->root,disease);
        if(temp == NULL){
        //	printf("mpike\n");
            // insert
            HeapNode* node = malloc(sizeof(HeapNode));
            
            node->counter = counter;
            node->disease = disease;
            node->child_a  = NULL;
            node->child_b  = NULL;
            
            // find next available parent in order to maintain balance
            HeapNode *parent = tree->next_free;
            node->parent = parent;
            
            if(parent->child_a==NULL){
                parent->child_a=node;
            }else{
                parent->child_b=node;//full binary tree-subtree
                tree->next_free = findfreeparent(tree);
            }
            //printf("mpike %d\n",tree->next_free->counter);
            
            tree->last_node=node;
            
            // swap nodes  to maintain  max heap
            swap_up(node);
            
            return node;
        }else{
            // update node
            temp->counter = counter;
            temp->disease = disease;
            
            swap_up(temp);
            
            return temp;
        }
    }
}


HeapNode* search_tree(HeapNode * root, char* disease) 
{ 
	if (root == NULL)
	    return NULL;
	else if (strcmp(root->disease , disease)==0)
	    return root;
	else {
	    HeapNode *left = search_tree(root->child_a, disease);
	    return left? left: search_tree(root->child_b, disease);
	}
}
/*
void printTree(HeapTree* tree){
    printPreorder(tree->root);
}

void printPreorder(HeapNode* node){
    if(node!=NULL){
        printf("Number: %s, Total cost: %d\n", node->disease,node->counter);
        printPreorder(node->child_b);
        printPreorder(node->child_a);
    }

}*/

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(HeapNode* node) 
{ 
    if (node == NULL) 
        return; 
  
    //print data
    printf("%s %d\n",node->disease,node->counter); 
  
	//recur left
    printPreorder(node->child_a);  
  
    //recur right
    printPreorder(node->child_b); 
}  

// compare and swap nodes
void swap_up(HeapNode* node){
    HeapNode* parent = node->parent;
    if(parent == NULL || node->counter<parent->counter){
        // if root reached or every node is in right place
        return;
    }else{
    	
        // swap disease and counter
        //structure properties
        char* disease;
        int counter;
        //printf("%d \n",node->counter);
		counter=node->counter;
		node->counter = parent->counter;
		parent->counter = counter;
		
        disease = node->disease;
        node->disease = parent->disease;
        parent->disease = disease;
        
        disease=NULL;
        // check parent of parent with recursion
        swap_up(parent);
    }
}

// find next available  parent node(level ordred)
HeapNode* findfreeparent(HeapTree* tree){

    HeapNode* tmp = find_parent(tree->root,tree->h);
    if(tmp!=NULL)
	{
        return tmp;
    }
	else
	{
	//if we have full tree
    	tree->h++;
        tmp = find_parent(tree->root,tree->h);
        return tmp;
    }
}

// find the  leftmost node with null children at given height
HeapNode* find_parent(HeapNode* node, int h){

    // child free
    if(node->child_a==NULL || node->child_b==NULL){
        return node;
    }
    
    // finished recursion
    if(h==0){
        return NULL;
    }

    // Move  down
    HeapNode* tmp;
    
    tmp = find_parent(node->child_a,h-1);
    if(tmp!=NULL){//if free parent node found return it
        return tmp;
    }
    tmp = find_parent(node->child_b,h-1);
    return tmp;

}


HeapNode* extract(HeapTree* tree){
	if(tree->root!=NULL){
		//printf("mpike\n");
		//extract root
		
		HeapNode* var=malloc(sizeof(HeapNode));
		var->disease=tree->root->disease;
		var->counter=tree->root->counter;
		
		tree->root->counter=tree->last_node->counter;
		tree->root->disease=tree->last_node->disease;
		
		//printf("tree last node parent counter %d %d\n",tree->last_node->parent->counter,tree->last_node->parent->child_b->counter);
		if(tree->last_node->parent->child_a==tree->last_node){
			printf("mpike1\n");
			tree->last_node->parent->child_a==NULL;
		}else if(tree->last_node->parent->child_b==tree->last_node){
			printf("mpike2\n");
			tree->last_node->parent->child_b==NULL;
		}
		free(tree->last_node);
		////////////
		//tree->last_node=parent
		
		if(tree->root->counter<tree->root->child_a->counter)
			swap_up(tree->root->child_a);
		else if(tree->root->counter<tree->root->child_b->counter)
			swap_up(tree->root->child_b);
			
		return var;
		
	}else
		return NULL;
}


int main(void){
	HeapTree *tr;
	tr=new_heap_tree();
	new_node(tr,"kalo",10);
		
	new_node(tr,"ka",30);
	new_node(tr,"lo",20);
		new_node(tr,"l",100);
		new_node(tr,"po",15);
		
HeapNode *ptr;
	printPreorder(tr->root);
	
//printf("ee %d\n",tr->last_node->counter);
//printf("ee %d\n",tr->height);
ptr = extract(tr);
	printf("%s %d \n\n\n",ptr->disease,ptr->counter);

	printPreorder(tr->root);
return 0;
}



