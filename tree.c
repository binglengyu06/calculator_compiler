#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include "tree.h"
#include "constants.h"

void aux_print_tree(tree_t *, int);
//void print_tree(tree_t *);
//int eval_tree(tree_t *);
//tree_t *make_tree(int type, tree_t *left, tree_t *right);


int eval_tree(tree_t *t){
	//int result;
	if (t==NULL) return 0;
	switch(t->type){
	case ADDOP:
		if (t->attribute.opval=='+'){
			return eval_tree(t->left) + eval_tree(t->right);
		}
		else if (t->attribute.opval=='-'){
                        return eval_tree(t->left) - eval_tree(t->right);
                }
        case MULOP:
		if (t->attribute.opval=='*'){
	                return eval_tree(t->left) * eval_tree(t->right); 
        	}
		else if (t->attribute.opval=='/'){
	                return eval_tree(t->left) / eval_tree(t->right); 
		}
		else if (t->attribute.opval=='^'){ 
			return pow( eval_tree(t->left), eval_tree(t->right));
		}
	case NUM:
		return t->attribute.ival;
	default:
		fprintf(stderr, "ERROR!!!");
		exit(1);
	}
}

tree_t *make_tree(int type, tree_t *l, tree_t *r){
	tree_t *p = (tree_t *)malloc( sizeof(tree_t));
	assert(p !=NULL);
	p->type = type;
	p->left = l;
	p->right = r;
	return p;
}

void print_tree(tree_t *t){
	aux_print_tree(t,0);
 }

void aux_print_tree(tree_t *t, int spaces){
	if (t==NULL) return;
	for (int i=0;i<spaces;i++)
		fprintf(stderr," ");
	switch(t->type){
	case ADDOP:
		fprintf(stderr, "[ADDOP:%c]\n",t->attribute.opval);
		aux_print_tree(t->left,spaces+4);
		aux_print_tree(t->right,spaces+4);
		break;
	case MULOP:
		fprintf(stderr, "[MULOP:%c]\n",t->attribute.opval);
                aux_print_tree(t->left,spaces+4);
                aux_print_tree(t->right,spaces+4);
		break;
	case NUM:
		fprintf(stderr, "[NUM:%d]\n",t->attribute);
		break;
	default:
		fprintf(stderr, "Error:print_tree, unknow type\n", t->type);
		exit(1);
	}
}
