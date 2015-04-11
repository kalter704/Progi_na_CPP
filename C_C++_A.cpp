#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int proverNaProst(int c) {
  int i = 2;
  while((c % i) != 0) { ++i; }
  if(i == c) { return 0; }
  else { return -1; }
}

void growMas(int** mas, size_t* k) { //realloc
	size_t lastSize = *k;
	*k *= 2;
	int* masTemp = (int*)calloc(*k, sizeof(int));// проверка нужна
	int i;
	for(i = 0; i < lastSize; ++i) {
		masTemp[i] = (*mas)[i];
 	}
 	free(*mas);
 	(*mas) = masTemp;
}

int* razlogChisla(int chislo) {
  int i = 0;
  size_t kol = 5;// define || const
  int* mas = (int*)calloc(kol, sizeof(int));
  if(mas == NULL) { return mas; }
  mas[i++] = 1;
  if((chislo == 1)) {
    return mas; 
  } else {
    if(proverNaProst(chislo) == 0) {
      mas[i] = chislo;
      return mas; 
    }
  }
  int c = 2;
  while(chislo > 1) {
    if((proverNaProst(c) == 0) && ((chislo % c) == 0)) {
      mas[i++] = c;
      chislo /= c;
      if(i == kol) {
      	growMas(&mas, &kol);
      }
    } else {
      c++;
    }
  }
  mas[i] = 0;
  return mas;
}

int main() {
  int chislo;
  int* mas;				// NULL
  if(scanf("%d", &chislo) != 1) {
    printf("[error]");
    return 0;
  }
  if(chislo <= 0) {
    printf("[error]");
    return 0;
  }
  mas = razlogChisla(chislo);
  if(mas == NULL) { 
    printf("[error]");
    return 0;
  } else {
    int i = 0;
    while(mas[i] != 0) {
      printf("%d ", mas[i]);
      ++i;
    }
  }
  free(mas);
  return 0;
}

