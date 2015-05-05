#include "stdio.h"
#include "stdlib.h"

#define ZERO 0
#define ADDITION_OR_SUBTRACTION 1
#define MULTIPLICATION 2
#define NUMBER 1
#define VECTOR 2

const int SIZE_STRING = 100;
const int INITIAL_SIZE_OF_THE_STACK = 8;
const int SIZE_NUM = 10;

struct Operand {
	int* operand;
	int size; 
};

struct StackOperands {
	struct Operand* arr;
	int size, top;
};

struct StackOperations {
	char* oper;
	int size, top;
};

//iaai iii?iaiaaou realloc
//oaaee?aiea noaea iia?aiaia
int growStackOperands(struct StackOperands** operands) {             
	int new_size = (**operands).size * 2;
	struct Operand* arr = (struct Operand*)calloc(new_size, sizeof(struct Operand));
	if(arr == NULL) {
		return 1;
	}
	int i;
	for(i = 0; i < (**operands).top; ++i) {
		arr[i] = (**operands).arr[i];
	}
	free((**operands).arr);
	(**operands).arr = arr;
	(**operands).size = new_size;
	return 0;
}

//iaai iii?iaiaaou realloc
//oaaee?aiea noaea iia?aoee
int growStackOperations(struct StackOperations* operations) {
	int new_size = (*operations).size * 2;
	char* oper = (char*)calloc(new_size, sizeof(char));
	if(oper == NULL) {
		return 1;
	}
	int i;
	for(i = 0; i < (*operations).top; ++i) {
		oper[i] = (*operations).oper[i];
	}
	free((*operations).oper);
	(*operations).oper = oper;
	(*operations).size = new_size;
	return 0;
}

//iaai iii?iaiaaou realloc!!!!!!!!!!!!!!!!!!!!!!!!!!
//oaaee?aiea aeiaie?aneiai ianneaa neiaieia
int growCharArray(char** array, int* size) { /////caiaia int& size ia int* size
	int new_size = *size * 2;
	char* temp_arr = (char*)calloc(new_size, sizeof(char));
	if(temp_arr == NULL) {
		return 1;
	}
	int i;
	for(i = 0; i < *size; ++i) {
		(*array)[i] = temp_arr[i];
	}
	free(*array);
	(*array) = temp_arr;
	*size = new_size;
	return 0;
}

int addNumberInStack(struct StackOperands* operands, char* num) { //caiaia char& num ia char* num// caiaia StackOperands& ia StackOperands*
  if((*operands).top == (*operands).size) {
    if(growStackOperands(&operands) == 1) {
      return 0;
    }
  }
  (*operands).arr[(*operands).top].operand = (int*)malloc(sizeof(int));
  (*operands).arr[(*operands).top].size = 1;
  if((*operands).arr[(*operands).top].operand == NULL) {
 	  return 0;
  }
  (*(*operands).arr[(*operands).top].operand) = atoi(num);
  (*operands).top++;
  return 1;
}

int getNumberFromStringAndAddInStack(struct StackOperands* operands, char* str, int* index) {  ////////////iineaaiaa eciaiaiea((((
  int size_num = SIZE_NUM;
  char* num = (char*)calloc(size_num, sizeof(char));
  if(num == NULL) {
		return 1;
  }
  int i = 0;
  while((str[*index] >= '0') && (str[*index] <= '9')) {
		if(i == size_num) {
		  if(growCharArray(&num, &size_num) == 1) {
		    return 1;
		  }
    }
    num[i] = str[*index];
    i++;
    (*index)++;
  }
  (*index)--;
  if( i == size_num) {
    if(growCharArray(&num, &size_num) == 0) {
		  return 1;
		}
  }
  num[i++] = '\0';
  if(addNumberInStack(&(*operands), num) == 0) {
    return 1;
  }
  return 0;
}

int addVectorInStack(struct StackOperands* operands, struct Operand temp_operand) {  ///////////?oi-oi iiiaiye;;;;;;;;;;;
  if((*operands).top == (*operands).size) {
    if(growStackOperands(&operands) == 1) { //////////////////////////////&(*operands) ???????????????
      return 1;
    }
  }
  (*operands).arr[(*operands).top++] = temp_operand;
  return 0;
}

int getVectorFromStringAndAddInStack(struct StackOperands* operands, char* str, int* index) {
  int size_vector = SIZE_NUM;
  char* vector = (char*)calloc(size_vector, sizeof(char));  
  if(vector == NULL) {
    return 1;
  }
  int i = *index + 1,
      amount_num = 0;
  while(str[i] != '}') {
    if(str[i++] == ',') amount_num++;
  }
  amount_num++;
  struct Operand* temp_operand = (struct Operand*)malloc(sizeof(struct Operand));
  (*temp_operand).operand = (int*)calloc(amount_num, sizeof(int));
	(*temp_operand).size = amount_num;
  if((*temp_operand).operand == NULL) {
    return 1;
  }
  int j;  
  for(j = 0; j < amount_num; ++j) {
    i = 0;
    do {
      (*index)++;
      if((str[*index] >= '0') && (str[*index] <= '9')) {
        if( i == size_vector) {
		      if(growCharArray(&vector, &size_vector) == 1) {
		        return 1;
		      }
        }
        vector[i++] = str[*index]; 
      }
    } while((str[*index] != '}') && (str[*index] != ','));               ////условие не правильное
    if( i == size_vector) {
      if(growCharArray(&vector, &size_vector) == 1) {
		    return 1;
      }
    }
    vector[i++] = '\0';
    (*temp_operand).operand[j] = atoi(vector);
  }
  if(addVectorInStack(&(*operands), *temp_operand) == 1) {
    return 1;
  }
  (*index)--;
  return 0;
}

struct Operand multiplicationNumberAndVector(struct Operand num, struct Operand vector) { /////////////////iaoea 222
  struct Operand result = {(int*)calloc(vector.size, sizeof(int)),
                           vector.size};
	int i;
  for(i = 0; i < vector.size; ++i) {
    result.operand[i] = vector.operand[i] * num.operand[0];
  }
  return result;
}

int AddOperationAddORSubInStack(struct StackOperands* operands, struct StackOperations* operations, char operation) { /////iaoea 111
  while((*operations).oper[(*operations).top] != '*') {
    struct Operand first_operand = (*operands).arr[(*operands).top - 1]; 
    //free((void*)(operands.arr[operands.top].operand));    aaa-oi ie?a
    struct Operand second_operand = (*operands).arr[(*operands).top - 2];
    //free((void*)(operands.arr[operands.top].operand));    aaa-oi ie?a
    /////////////////iaoea 222
    struct Operand result = {NULL, 0};
    if(first_operand.size > 1) {
      result = multiplicationNumberAndVector(second_operand, first_operand);
      if(result.operand == NULL) {
        return 1;
      }
    } else {
      result = multiplicationNumberAndVector(first_operand, second_operand);
      if(result.operand == NULL) {
        return 1;
      }
    }
    free((void*)((*operands).arr[--(*operands).top].operand));
    free((void*)((*operands).arr[--(*operands).top].operand));
    if(addVectorInStack(&(*operands), result) == 1) {///////////?oi-oi iiiaiye ;;;;;;;;;;;????????
    	return 1;
    }
    if((*operations).size == (*operations).top) {
      if(growStackOperations(&(*operations))) {
        return 1;
      }
    }
    (*operations).oper[(*operations).top++] = operation;
  }
  return 0;
}

int AddOperationMulInStack(struct StackOperations* operations) { /////////caiaia StackOperations&
  if((*operations).size == (*operations).top) {
      if(growStackOperations(&(*operations))) {
        return 1;
      }
    }
  (*operations).oper[(*operations).top++] = '*';
  return 0;
}

int AddOpenBracket(struct StackOperations* operations) { /////////caiaia StackOperations&
  if((*operations).size == (*operations).top) {
      if(growStackOperations(&(*operations))) {
        return 1;
      }
    }
  (*operations).oper[(*operations).top++] = '(';
  return 0;
}


struct Operand AdditionVectors(struct Operand first, struct Operand second) {
	int higher_size = 0, 
	    lower_size = 0; 
	if(first.size > second.size) {
		higher_size = first.size;
		lower_size = second.size;
	} else {
		higher_size = second.size;
		lower_size = first.size;
	}
	struct Operand result = {(int*)calloc(higher_size, sizeof(int)),
                           higher_size};
	if(result.operand == NULL) {
		return result;
	}
	int i;
	for(i = 0; i < lower_size; ++i) {
		result.operand[i] = first.operand[i] + second.operand[i];
	}
	if(first.size > second.size) {
		for(i = lower_size; i < higher_size; ++i) {
			result.operand[i] = first.operand[i];
		}
	} else {
		for(i = lower_size; i < higher_size; ++i) {
			result.operand[i] = second.operand[i];
		}
	}
	return result;
}

struct Operand SubtractionVectors(struct Operand first, struct Operand second) {
	int higher_size = 0, 
	    lower_size = 0; 
	if(first.size > second.size) {
		higher_size = first.size;
		lower_size = second.size;
	} else {
		higher_size = second.size;
		lower_size = first.size;
	}
	struct Operand result = {(int*)calloc(higher_size, sizeof(int)),
                           higher_size};
	if(result.operand == NULL) {
		return result;
	}
	int i;
	for(i = 0; i < lower_size; ++i) {
		result.operand[i] = first.operand[i] - second.operand[i];
	}
	if(first.size > second.size) {
		for(i = lower_size; i < higher_size; ++i) {
			result.operand[i] = first.operand[i];
		}
	} else {
		for(i = lower_size; i < higher_size; ++i) {
			result.operand[i] = -second.operand[i];
		}
	}
	return result;
}

int AddCloseBracket(struct StackOperands* operands, struct StackOperations* operations) { // caiaia StackOperands&
	while((*operations).oper[--(*operations).top] != '(') {
		///////////////////////////////////////////////////////////////////////////////////////////
		struct Operand first = (*operands).arr[(*operands).top - 1];
		struct Operand second = (*operands).arr[(*operands).top - 2];
		struct Operand result = {NULL, 0};
		switch((*operations).oper[(*operations).top]) {
			case '+':
				result = AdditionVectors(first, second);
				break;
			case '-':
				result = SubtractionVectors(first, second);   
				break;
		}
		if(result.operand == NULL) {
			return 1;
		}
		free((void*)(*operands).arr[--(*operands).top].operand);
		free((void*)(*operands).arr[--(*operands).top].operand);
		if(addVectorInStack(&(*operands), result) == 1) {
  		return 1;
		}
	}
	(*operations).top--;
	return 0;
}

struct Operand SummVectors(struct StackOperands operands, struct StackOperations operations) {
  struct Operand result = {NULL, 0};
  struct Operand t_result = {NULL, 0};
  if(operands.top > 1) {
    switch(operations.oper[operations.top - 1]) {
      case '+':
			  result = AdditionVectors(operands.arr[operands.top - 1], operands.arr[operands.top - 2]);
			  operands.top -= 2;
			  break; 
		  case '-':
			  result = SubtractionVectors(operands.arr[operands.top - 1], operands.arr[operands.top - 2]);  
        operands.top -= 2; 
			  break;
	  } 
	  if(result.operand == NULL) {
			return result;
		}
  }
  int i;
  for(i = operations.top - 2; i >= 0; --i) {
    switch(operations.oper[i]) {
			case '+':
				t_result = AdditionVectors(operands.arr[--operands.top], result);
				free(result.operand);
				result = t_result;
				break;
			case '-':
				t_result = SubtractionVectors(operands.arr[--operands.top], result);   
				free(result.operand);
				result = t_result;
				break;
		}
		if(result.operand == NULL) {
			return result;
		}
  }
  return result;
  /////////////////   надо все просуммировать !!!!!!!!
}

struct Operand Calculation(char* str) {              ////////////iaai inaiaiaeou iaiyou!!!!!!!!!!!!!!!!!
	struct Operand result = {NULL, 0};
	struct StackOperands operands = {(struct Operand*)calloc((INITIAL_SIZE_OF_THE_STACK), sizeof(struct Operand)),  //*arr
	                                 INITIAL_SIZE_OF_THE_STACK,                                       //size
														       0};                                                              //top
	if(operands.arr == NULL) {
		return result;
	}
  struct StackOperations operations = {(char*)calloc((INITIAL_SIZE_OF_THE_STACK), sizeof(char)),    //*oper
                                       INITIAL_SIZE_OF_THE_STACK,                                   //size
 														           0};                                                          //top
  if(operations.oper == NULL) {
 	  return result;
  }
  operations.oper[operations.top] = '\0';
  int index = 0;
  int flag_operation = ZERO,
      flag_operand = ZERO;
	while(str[index] != '\0') {
		if((str[index] >= '0') && (str[index] <= '9')) {
		  if(flag_operand == NUMBER){
		    return result;
		  }
		  if((flag_operand == VECTOR) && (flag_operation == ADDITION_OR_SUBTRACTION)){
		    return result;
		  }
			if(getNumberFromStringAndAddInStack(&operands, str, &index) == 1) {
			  return result;
			}
			flag_operand = NUMBER;
		}
		if(str[index] == '{') {
		  if((flag_operand == NUMBER) && (flag_operation == ADDITION_OR_SUBTRACTION)){
		    return result;
		  }
		  if((flag_operand == VECTOR) && (flag_operation == MULTIPLICATION)){
		    return result;
		  }
			if(getVectorFromStringAndAddInStack(&operands, str, &index) == 1){
			  return result;
			}
			flag_operand = VECTOR;
		}
		switch(str[index]) {
			case '+':
			case '-':
				if(AddOperationAddORSubInStack(&operands, &operations, str[index]) == 1) {
				  return result;
				}
				flag_operation = ADDITION_OR_SUBTRACTION;
				break;
			case '*':
				if(AddOperationMulInStack(&operations) == 1) {
				  return result;
				}
				flag_operation = MULTIPLICATION;
				break;
			case '(': //// Aicii?ii iauaaeieaiea n case '*'
				if(AddOpenBracket(&operations) == 1) {
				  return result;
				}
				flag_operation = ZERO; 
				flag_operand = ZERO;
				break;
			case ')':
				if(AddCloseBracket(&operands, &operations) == 1) {
					return result;
				}
				flag_operand = VECTOR;
				break;
		}
		index++;
	}
	//////  тут нужны вычисления!!!!! 
	////// и отчистка памяти!!!!!!!
	result = SummVectors(operands, operations);
	return result;
}

int main() {
  
	//printf("OK\n");
  //return 0; ////////////////////////////// auoia
  
	char str[SIZE_STRING];
	if(scanf("%s", str) != 1) {
	  printf("[error]"); 
	  return 0;
	}
	//printf("%s", str);
	
	struct Operand result = Calculation(str);
	if(result.operand == NULL) {
		printf("[error]"); 
	  return 0;
	}
	printf("{");
/*	int i = 0;
	while(result.arr[i] != '\0') {
		printf("%c,", result.arr[i]);
		i++;
	} */
	int i;
	for(i = 0; i < result.size; ++i) {
		printf("%c,", result.operand[i]);
	}
	printf("}");
	free(result.operand);
	//int q = 0;
	//scanf("%d", &q);
	return 0;
}
