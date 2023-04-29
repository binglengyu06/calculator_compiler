/* 一般在【.h】类的头文件里面只放入函数声明，宏定义，函数原型. */
/* 而具体的实现在【.cpp】文件里面。*/

#ifndef TREE_H
#define TREE_H
/* ask the c processor that if you not seen it before, then go ahead and take it; otherwise, if you seen this constent before, do not do anything. */ 

typedef struct tree_s{  /*自定义数据结构*/
	int type;  /*token type: ADDOP, MULOP, NUM */
	union{
		int ival;
		int opval;
	}attribute;
	struct tree_s *left;
	struct tree_s *right;
} tree_t;

tree_t *make_tree(int type, tree_t *left, tree_t *right); /*函数原型*/
void print_tree(tree_t *t); /*函数原型*/
int eval_tree(tree_t *t);
#endif
