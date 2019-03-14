#include "Product.h"

Product* createProduct(char *name, char *category, int quantity, char* expiration)
{
	/*
	We create a product
	We allocate everything dynamically
	*/
	Product* p = (Product*)malloc(sizeof(Product));
	p->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(p->name, name);
	p->category = (char*)malloc(sizeof(char) * (strlen(category) + 1));
	strcpy(p->category, category);
	p->expiration = (char*)malloc(sizeof(char) * (strlen(expiration) + 1));
	strcpy(p->expiration, expiration);

	p->quantity = quantity;
	return p;
}
Product* copyProduct(Product *p)
{
	Product* newp = createProduct(p->name, p->category, p->quantity, p->expiration);
	return newp;
}
void destroyProduct(Product* p)
{
	/*
	We destroy a product,if it exists
	*/
	if (p == NULL)
		return;
	free(p->category);
	free(p->name);
	free(p->expiration);
	free(p);
}
void destroyAux(Product *p)
{
	/*
	We destroy the aux
	*/
	if (p == NULL)
		return;
	free(p->name);
	free(p);
}
void getProduct(Product *p, char s[])
{
	/*
	We get as an output parameter the string containing the product
	*/
	sprintf(s, "Product %s is in category %s. We have %d units of that product with expiration date %s.", p->name, p->category, p->quantity, p->expiration);	
}