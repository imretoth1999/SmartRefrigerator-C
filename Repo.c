#include "Repo.h"

DynamicRefrigerator* initRepo(int capacity)
{
	/*
	We initialise the repo
	*/
	DynamicRefrigerator* dr = (DynamicRefrigerator*)malloc(sizeof(DynamicRefrigerator));
	if (dr == NULL)
		return NULL;
	dr->capacity = capacity;
	dr->lenght = 0;
	dr->p = (Product**)malloc(sizeof(Product*) * capacity);
	if (dr->p == NULL)
		return NULL;
	return dr;
}
void destroy(DynamicRefrigerator* dr)
{
	/*
	We destroy the dynamic refrigerator
	*/
	if (dr == NULL)
		return;
	for (int i = 0; i < dr->lenght; i++)
		destroyProduct(dr->p[i]);
	free(dr->p);
	dr->p = NULL;
	free(dr);
	dr = NULL;
}
int resize(DynamicRefrigerator* dr)
{
	/*
	We resize the dynamic refrigerator if we need to do it
	*/
	if (dr == NULL)
		return;
	dr->capacity *= 2;
	Product** pr = (Product**)malloc(sizeof(Product*) * dr->capacity);
	if (pr == NULL)
		return -1;
	for (int i = 0; i < dr->lenght; i++)
		pr[i] = dr->p[i];
	free(dr->p);
	dr->p = pr;
	
	return 0;
}
void add(DynamicRefrigerator* dr, Product *pr)
{
	/*
	We add the product to the refrigerator
	*/
	if (dr == NULL)
		return;
	if (dr->p == NULL)
		return;

	if (dr->lenght == dr->capacity)
		resize(dr);
	dr->p[dr->lenght++] = pr;
}
int datecondition(char s1d[], char s2d[], int x)
{
	/*
	We get the years month and days from the strings
	*/
	char s1[255], s2[255];
	strcpy(s1, s1d);
	strcpy(s2, s2d);
	char day1[255], month1[255], year1[255], day2[255], month2[255], year2[255];
	int i = 0, j = 0;
	while (s1[i] != '/')
	{
		day1[j] = s1[i];
		i++;
		j++;
	}
	day1[j] = '\0';
	i++;
	j = 0;
	int d1 = atoi(day1);
	while (s1[i] != '/')
	{
		month1[j] = s1[i];
		i++;
		j++;
	}
	month1[j] = '\0';
	i++;
	j = 0;
	int m1 = atoi(month1);
	while (s1[i])
	{
		year1[j] = s1[i];
		i++;
		j++;
	}
	year1[j] = '\0';
	i++;
	j = 0;
	i = 0;
	int y1 = atoi(year1);
	while (s2[i] != '/')
	{
		day2[j] = s2[i];
		i++;
		j++;
	}
	i++;
	day2[j] = '\0';
	j = 0;
	int d2 = atoi(day2);
	while (s2[i] != '/')
	{
		month2[j] = s2[i];
		i++;
		j++;
	}
	i++;
	month2[j] = '\0';
	j = 0;
	int m2 = atoi(month2);
	while (s2[i])
	{
		year2[j] = s2[i];
		i++;
		j++;
	}
	year2[j] = '\0';
	int y2 = atoi(year2);
	if (x == -1)
	{
		return datecondition1(y1,y2,m1,m2,d1,d2);
	}
	else
		return expiresin(y1, m1, d1, x);
}
int expiresin(int y1, int m1, int d1, int x)
{
	/*
	We return if the product expires in the following x days
	*/
	int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int cy, cm, cd;
	cy = tm.tm_year + 1900;
	cm = tm.tm_mon + 1;
	cd = tm.tm_mday;
	for (int i = 0; i < x; i++)
	{
		cd++;
		if (cd > daysPerMonth[cm - 1])
		{
			cd = 1;
			cm++;
			if (cm == 13)
			{
				cm = 1;
				cy++;
			}
		}
	}
	return datecondition1(cy, y1, cm, m1, cd, d1);
}
int datecondition1(int y1, int y2, int m1, int m2, int d1, int d2)
{
	/*
	We compare the dates
	*/
	if (y1 > y2)
		return 1;
	else if (y1 == y2 && m1 > m2)
		return 1;
	else if (y1 == y2 && m1 == m2 && d1 > d2)
		return 1;
	return 0;
}
void orderDate(DynamicRefrigerator *d)
{
	/*
	We order the elements from the refrigerator according to their date
	*/
	Product *aux;
	for (int i = 0;i<getLenght(d)- 1;i++)
		for (int j = i + 1; j < getLenght(d); j++)
		{
			if (datecondition(d->p[i]->expiration, d->p[j]->expiration,-1) != 0)
			{
				aux = d->p[i];
				d->p[i] = d->p[j];
				d->p[j] = aux;
			}
		}
}
void orderA(DynamicRefrigerator* d)
{
	/*
	We order the products in the refrigerator according to the quantity
	*/
	for(int i = 0;i<getLenght(d)- 1;i++)
		for(int j = i+1;j<getLenght(d);j++)
			if (d->p[i]->quantity > d->p[j]->quantity)
			{
				char aux[256],aux1[256],aux2[256];
				strcpy(aux,d->p[i]->name);
				strcpy(aux1, d->p[i]->category);
				strcpy(aux2, d->p[i]->expiration);
				d->p[i]->name = (char *)realloc(d->p[i]->name, 255);
				d->p[i]->category = (char *)realloc(d->p[i]->category, 255);
				d->p[i]->expiration = (char *)realloc(d->p[i]->expiration, 255);

				strcpy(d->p[i]->name,d->p[j]->name);
				strcpy(d->p[i]->category, d->p[j]->category);
				strcpy(d->p[i]->expiration, d->p[j]->expiration);

				d->p[j]->name = (char *)realloc(d->p[j]->name, 255);
				d->p[j]->category = (char *)realloc(d->p[j]->category, 255);
				d->p[j]->expiration = (char *)realloc(d->p[j]->expiration, 255);

				strcpy(d->p[j]->name,aux);
				strcpy(d->p[j]->category, aux1);
				strcpy(d->p[j]->expiration, aux2);
				int q = d->p[i]->quantity;
				d->p[i]->quantity = d->p[j]->quantity;
				d->p[j]->quantity = q;
			}
}
void listexpiration(DynamicRefrigerator *d, int x)
{
	/*
	We list the products in order of expiration
	*/
	for (int i = 0; i < d->lenght; i++)
	{
		if (datecondition(d->p[i]->expiration, d->p[i]->expiration, x))
			printf("The product %s will expire in %d days (the expiration date is %s)\n", d->p[i]->name, x, d->p[i]->expiration);
	}
}

void sortQ(DynamicRefrigerator *d)
{
	Product *pr;
	for (int i = 0; i < d->lenght - 1; i++)
	for (int j = i+1;j<d->lenght;j++)
		if (d->p[i]->quantity < d->p[j]->quantity)
		{
			pr = d->p[i];
			d->p[i] = d->p[j];
			d->p[j] = pr;
		}
	
}
int getLenght(DynamicRefrigerator* dr)
{
	/*
	We return the length of the dynamic refrigerator
	*/
	if (dr == NULL)
		return -1;
	return dr->lenght;
}

Product* get(DynamicRefrigerator* dr, int i)
{
	/*
	We get the product at the i position
	*/
	return dr->p[i];
}
void delete_repo(DynamicRefrigerator *dr, int pos)
{
	/*
	We delete the a product at a given position
	*/
	if (dr == NULL)
		return;
	if (dr->p == NULL)
		return;
	if (pos < 0 || pos >= dr->lenght)
		return;
	for (int i = pos; i < dr->lenght - 1; i++)
		dr->p[i] = dr->p[i + 1];
	dr->lenght--;
}

void test ()
{
	/*
	We test the repo and the product
	*/
	test_create();
	test_add();
	test_get();
	test_delete();
}