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

///////////////////////////////////////////
struct UnitOfExpression* getVector(char* string, int* index_str) {
	
}

///////////////////////////////////////////
struct UnitOfExpression* getNumber(char* string, int* index_str) {
	
}

// при экстенном выходе надо отчищать память!!!
int fillingArrUnits(char* string, struct UnitOfExpression* arr_units, int* size_arr_units, int* last_arr_units) {
	struct StackOperations stack_oper;
	stack_oper.stack = (char*)calloc(INITIAL_STACK_SIZE, sizeof(char));
	if(stack_oper.stack == NULL) {
		return false;
	}
	stack_oper.size	= INITIAL_STACK_SIZE;
	stack_oper.top = 0;
	
	int index_str = 0;
	char character = string[index_str];
	while(character != '\0') {
		if(stack_oper.size == stack_oper.top) {
			stack_oper.size *= 2;
			realloc((void*)stack_oper.stack, stack_oper.size * sizeof(char));
			if(stack_oper.stack == NULL) {
				return false;
			}
		}
		if(character == '{') {
			struct UnitOfExpression* tempUnit;
			tempUnit = getVector(string, &index_str); /////////// Заглушка
			if(tempUnit == NULL) {
				return false;
			}
			stack_oper.stack[stack_oper.top++] = tempUnit;
		} else if((character >= '0') && (character <= '9')) {
			////
			struct UnitOfExpression* tempUnit;
			tempUnit = getNumber(string, &index_str); /////////// Заглушка
			if(tempUnit == NULL) {
				return false;
			}
			stack_oper.stack[stack_oper.top++] = tempUnit;
		} else if(character > ')') {
			
		} else {
			
		}
		++index_str;
		string[index_str];
		for( ; string[index_str] == ' '; ++index_str) {}
	}
	
	return true;
}

// Надо ддописать
int calculateExpression(struct UnitOfExpression* arr_units, struct UnitOfExpression* result) {
	
	return true;
}

int main() {
	char string[INITIAL_STRING_SIZE];
	if(scanf("%s", string) != 1) {
	  printf("[error]"); 
	  return 0;
	}
	
	struct UnitOfExpression* arr_units = (struct UnitOfExpression*)calloc(INITIAL_STACK_SIZE, sizeof(struct UnitOfExpression));
	int size_arr_units = INITIAL_STACK_SIZE,
			last_arr_units = 0;
	
	if(arr_units == NULL) {
		printf("[error]"); 
		return 1;
	}
	if(fillingArrUnits(string, arr_units, &size_arr_units, &last_arr_units) == false) {
		printf("[error]"); 
		return 1;
	}
	
	struct UnitOfExpression* result;
	if(calculateExpression(arr_units, result) == false) {
		printf("[error]"); 
		return 1;
	}
	
	free(arr_units);
	return 0;
}
