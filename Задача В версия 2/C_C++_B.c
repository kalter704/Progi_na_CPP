#include "stdio.h"
#include "stdlib.h"

#define NUMBER 			1
#define VECTOR 			2
#define OPERATOR 		3

#define true		1
#define false		0

#define INITIAL_STACK_SIZE 16
#define INITIAL_STRING_SIZE 256

struct UnitOfExpression {
	int* arr;
	int dimension;
	int type;
};

struct StackOperations {
	char* stack;
	int top,
			size;
};

struct StackOperands {
	struct UnitOfExpression* stack;
	int top, 
			size;
};

int fillingArrUnits(char* string, struct UnitOfExpression* arr_units) {
	struct StackOperations stack_oper;
	stack_oper.stack = (struct UnitOfExpression*)calloc(INITIAL_STACK_SIZE, sizeof(struct UnitOfExpression));
	if(stack_oper.stack == NULL) {
		return false;
	}
	stack_oper.size	= INITIAL_STACK_SIZE;
	stack_oper.top = 0;
	
	int index_str = 0;
	while(string[index_str]) {
		
		++index_str;
	}
	
	return true;
}

// Надо ддописать
int calculateExpression(struct UnitOfExpression* arr_units, ) {
	
	return true
}

int main() {
	char string[INITIAL_STRING_SIZE];
	if(scanf("%s", string) != 1) {
	  printf("[error]"); 
	  return 0;
	}
	
	struct UnitOfExpression* arr_units = (struct UnitOfExpression*)calloc(INITIAL_STACK_SIZE, sizeof(struct UnitOfExpression));
	if(arr_units == NULL) {
		printf("[error]"); 
		return 1;
	}
	if(fillingArrUnits(string, arr_units) == false) {
		printf("[error]"); 
		return 1;
	}
	
	/*
	Надо додумать!!!!!!!!!!!!!
		
	struct UnitOfExpression* result;
	if(calculateExpression(arr_units, ) == false) {
		printf("[error]"); 
		return 1;
	}
	*/
	
	free(arr_units);
	return 0;
}
