#include "global_variables.h"

void initArray(Array *a, size_t initialSize) {
	a->point = (tPoint *)calloc(initialSize , sizeof(tPoint));
	a->used = 0;
	a->size = initialSize;
}
void insertArray(Array *a, tPoint element) {
	if (a->used == a->size) {
		a->size *= 2;
		a->point = (tPoint *)realloc(a->point, a->size * sizeof(tPoint));
	}
	a->point[a->used++] = element;
}
