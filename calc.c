#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "tree.h"
#include "constants.h"

int get_token();
tree_t *expr();
tree_t *factor();
tree_t *term();
tree_t *spr();
void match(int);

/* globals for communication between parser and scanner */
int current_token;
int current_attribute;

int main()
{
	tree_t *value;
	while(1){
		current_token = get_token();
		if (current_token==EOS){
			break;
		}
		value = expr();
		fprintf(stderr,"\nPRINTING TREE:\n\n");
		print_tree(value);
		fprintf(stderr,"Value = %d\n",eval_tree(value));
	}
}


/* parser */
/* E -> TE', E' -> +TE'|empty */
tree_t *expr(){
	int opval;
	tree_t *value=term();
	while(current_token==ADDOP){
		opval = current_attribute;
		match(ADDOP);
		value = make_tree(ADDOP, value, term());
		value->attribute.opval = opval;
	}
	return value;
}

/* T -> FT', T' -> *FT'|empty */
tree_t *term(){
	int opval;
	tree_t *value = factor();
	while(current_token==MULOP){
		opval = current_attribute;
		match(MULOP);
		value = make_tree(MULOP, value,  factor());
		value->attribute.opval = opval;
	}
	return value;
}

/* F-> -F | (E) | NUM */
tree_t *factor(){
	tree_t *value;
	int opval;
	if (current_token=='('){
		match('(');
		value = expr();
		match(')');	
		return value;
	}
	else if (current_token==NUM){
		tree_t *value = make_tree(NUM, NULL, NULL);
                value->attribute.ival = current_attribute;
                match(NUM);
		return value;	
	}
	else if (current_token ==ADDOP){
                opval = current_attribute;
                match (ADDOP);
                tree_t *left = make_tree(NUM, NULL, NULL);
                left->attribute.ival = 0;
                tree_t *value = make_tree(ADDOP, left, factor());
                value->attribute.opval = opval;
		return value;
	}
}

/* tokenlizer/scanner: tokenize a string according to its token types */
/* example: "(278+312)*4659" ==> [(][NUM][+][NUM][)][*][NUM] */
int get_token()
{
	int c, value;
	while((c=getchar()) != EOF){
		switch(c){
			case '+': case '-':
				current_attribute = c; 
				fprintf(stderr,"[OP:%c]",c);
				return ADDOP;
			case '/':  case '*': case '^':
				current_attribute = c;
				fprintf(stderr, "[OP:%c]", c);
				return MULOP;
			case '(': case ')':
				fprintf(stderr, "[%c]", c);
				return c;
			case ' ': case '\t':
			continue;
			default:
				if (isdigit(c)){
					value = 0;
					do {
						value = 10*value+(c-'0');
					}
					while(isdigit(c=getchar() ));					
					ungetc(c,stdin);
					fprintf(stderr,"[NUM:%d]",current_attribute= value);
					return NUM;
				}
				else if (c=='\n'){
					fprintf(stderr,"[EOS]");
					return EOS;
				}
				else{
					fprintf(stderr,"ERROR: unknown token {%c}\n", c);
					exit(1);
				}
		}
	}
}

void match(int expected_token){
	if (current_token==expected_token){
		current_token = get_token();
	}
	else{
	fprintf(stderr, "Error in match: current = %d,expected = %d\n", current_token, expected_token);
	}

}
