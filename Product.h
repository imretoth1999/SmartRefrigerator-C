#pragma once
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
typedef struct {
	char *name;
	char *category;
	int quantity;
	char *expiration;
}Product;

Product* createProduct(char *name, char *category, int quantity, char* expiration);
Product* copyProduct(Product *p);
void destroyProduct(Product* p);
void destroyAux(Product *p);
void getProduct(Product *p, char s[]);
void test_delete();
void test_get();
void test_add();
void test_create();
