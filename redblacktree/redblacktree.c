#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int value;
	char color;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
	struct Node *uncle;
}TNodeRB;

typedef struct{
	TNodeRB *root;
}TtreeRB;

void insertNode(TNodeRB *n, TNodeRB *root){
	TNodeRB *nAux;
	if(root == NULL){
		root->color = 'B';
		root->value = n->value;
		root->left = n->left;
		root->right = n->right;
		root->parent = n->parent;
		root->uncle = n->uncle;
		root = n;
	}else{
		nAux = root;
		while(n != NULL){
			if(nAux->value < n->value){
				insertNode(n->left, nAux);
				n->parent = nAux;
				n->color = 'R';
			}else{
				if(nAux->value > n->value || nAux->value == n->value){
					insertNode(n->right, nAux);
					n->parent = nAux;
					n->color = 'R';
				}
			}
		}
	}
}

void rotate_ll(TNodeRB *n){
	TNodeRB *nAux = n;
	if(n->color == 'R' && n->right->color == 'R'){
		nAux = n->parent;
		n->left = n;
		n->uncle = n->right;
		n = nAux;
		n->color = 'B';
	}
}

void rotate_rr(TNodeRB *n){
	TNodeRB *nAux = n;
	if(n->color == 'R' && n->left->color == 'R'){
		nAux = n->parent;
		n = n->parent;
		n->right = n;
		n->uncle = n->left;
		n = nAux;
		n->color = 'B';
	}
}

void rotate_lr(TNodeRB *n){
	if(n->color == 'R' && n->parent->color == 'R' && n->right->color == 'R'){
		rotate_ll(n);
		rotate_rr(n->parent);
	}
}

void rotate_rl(TNodeRB *n){
	if(n->color == 'R' && n->parent->color == 'R' && n->left->color == 'R'){
		rotate_rr(n);
		rotate_ll(n->parent);
	}
}

void fixUp(TNodeRB *root){
	TNodeRB *nAux = root;
	while(nAux != NULL){
		if(nAux->color == 'B'){
			nAux = nAux->left;
			if(nAux->color == 'R' && nAux->uncle->color == 'R'){
				if(nAux->parent->color == 'R'){
					rotate_lr(nAux);
				}else{
					rotate_ll(nAux);
				}
				nAux = nAux->left;
			}
			if(nAux->color == 'R' && nAux->uncle->color == 'R'){
				if(nAux->parent->color == 'R'){
					rotate_rl(nAux);
				}else{
					rotate_rr(nAux);
				}
				nAux = nAux->right;
			}
		}else{
			nAux->color = 'B';
			fixUp(root);
		}
	}
}

void removeNode(TNodeRB *root, int value){
	TNodeRB *nAux = root;
	while(nAux != NULL){
		if(nAux->value < value){
			nAux = nAux->left;
		}
		if(nAux->value > value){
			nAux = nAux->right;
		}
		if(nAux->value == value){
			nAux->parent = nAux;
			nAux->parent->left = nAux->left;
			nAux->parent->right = nAux->right;
			nAux->parent->uncle = nAux->uncle;
			nAux = NULL;
		}
	}
}

void pathInOrder(TNodeRB *n){
	if(n != NULL){
		pathInOrder(n->left);
		printf("value: %d\n Color: %d\n", n->value, n->color);
		pathInOrder(n->right);
	}
}

int main(){
	FILE *file;
	TtreeRB *tree;
	TNodeRB input[8];
	int i = 0;

	file = fopen("input.txt", "rt");
	while(fgets(input[i], 8, file) != NULL){
		insertNode(TNodeRB input[i], tree->root);
		i++;
	}

	fixUp(tree->root);

	pathInOrder(tree->root);

	return 0;
}