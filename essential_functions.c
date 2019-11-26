#include "global_variables.h"

void initArray(Array *a, size_t initialSize) {
	a->point = (Ponto_t *)calloc(initialSize , sizeof(Ponto_t));
	a->used = 0;
	a->size = initialSize;
}
void insertArray(Array *a, Ponto_t element) {
	if (a->used == a->size) {
		a->size *= 2;
		a->point = (Ponto_t *)realloc(a->point, a->size * sizeof(Ponto_t));
	}
	a->point[a->used++] = element;
}
