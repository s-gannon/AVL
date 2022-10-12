#include <math.h>
#include <stdio.h>
#include <assert.h>

typedef struct{
	char id[8];
	char* name;
	node* left;
	node* right;
} node;

typedef struct{
	node* root;
} avl;

void node_create(node* new_node){

}

void avl_left_rotation(node* parent, node* child){
	parent->right = NULL;
	child->left = parent;
}
void avl_right_rotation(node* parent, node* child){
	parent->left = NULL;
	child->right = parent;
}

int main(){

}
