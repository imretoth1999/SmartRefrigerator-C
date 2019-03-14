#pragma once
#include "Product.h"

typedef struct {
	Product** p;
	int lenght;
	int capacity;
}DynamicRefrigerator;


DynamicRefrigerator* initRepo(int capacity);
void destroy(DynamicRefrigerator* dr);
int resize(DynamicRefrigerator* dr);
void add(DynamicRefrigerator* dr, Product *pr);
int datecondition(char s1d[], char s2d[], int x);
int expiresin(int y1, int m1, int d1, int x);
int datecondition1(int y1, int y2, int m1, int m2, int d1, int d2);
void orderDate(DynamicRefrigerator *d);
void orderA(DynamicRefrigerator* d);
void listexpiration(DynamicRefrigerator *d, int x); 
void sortQ(DynamicRefrigerator *d);
int getLenght(DynamicRefrigerator* dr);
Product* get(DynamicRefrigerator* dr, int i);
void delete_repo(DynamicRefrigerator *dr, int pos);
void test();
