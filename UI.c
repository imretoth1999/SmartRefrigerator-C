#include "UI.h"

UI* initUI(Controller *c)
{
	/*
	We initialise the UI
	We return the struct
	*/
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->c = c;
	return ui;
}
void finish(UI* ui)
{
	/*
	We destroy the UI
	We free the memory
	*/
	destroyCtrl(ui->c);

	free(ui);
}
int getCommand(const char* m)
{
	/*
	We make sure that the number read is an integer
	We return the number if it is good
	We ask the user to input a number until is a valid integer
	*/
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(m);
		scanf("%s", s);

		r = sscanf(s, "%d", &res);
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}
void printMenu()
{
	/*
	We print the menu
	*/
	printf("Input -1 to view the products\n");
	printf("Input 0 to exit\n");
	printf("Input 1 to add a product\n");
	printf("Input 2 to update a product\n");
	printf("Input 3 for deleting a product\n");
	printf("Input 4 to find all products containing a string\n");
	printf("Input 5 to view all the elements from a given category orderd according to their date\n");
	printf("Input 6 for displaying all the products from a category that expire in X days\n");
	printf("Input 7 to undo an operation\n");
	printf("Input 8 to redo an operation\n");
	printf("Input 9 to view all products from a category in descendent order acording to the quantity\n");
}
void start(UI *ui)
{
	/*
	We show the user the options
	We make sure that the option is valid
	We choose the operation according to the user input
	*/
	int i = 0;
	while (1)
	{
		printMenu();
		int co = getCommand("Enter a number please\n");
		while (co != -1 && co != 0 && co != 1 && co != 2 && co != 3 && co != 4 && co != 5 && co != 6 && co != 7 && co != 8 && co != 9)
		{
			co = getCommand("Wrong command,enter another one\n");
		}
		if (co == 0)
			break;
		switch (co)
		{
			case -1:
			{
				listAll(ui);
				break;
			}
			case 1:
			{
				char n[255], c[255], e[255];
				int q;
				printf("Enter the name:\n");
				scanf("%s", n);
				printf("Enter the category:\n");
				scanf("%s", c);
				printf("Enter the quantity:\n");
				scanf("%d", &q);
				printf("Enter the expiration date:\n");
				scanf("%s", e);
				if (addProductCtrl(ui->c, n, c, q, e,1) == 1)
					printf("The product was succesfully added\n");
				else
					printf("The product exists but we updated the quantity\n");
				break;
			}
			case 2:
			{
				char n[255], c[255], e[255];
				int q;
				printf("Enter the name:\n");
				scanf("%s", n);
				printf("Enter the category:\n");
				scanf("%s", c);
				printf("Enter the quantity:\n");
				scanf("%d", &q);
				printf("Enter the expiration date:\n");
				scanf("%s", e);
				if (updateCtrl(ui->c, n, c, q, e))
					printf("The product was succesfully updated\n");
				else
					printf("The product does not exist\n");
				break;
			}
			case 3:
			{
				char n[255], c[255];
				printf("Enter the name:\n");
				scanf("%s", n);
				printf("Enter the category:\n");
				scanf("%s", c);
				int i = findCtrl(ui->c, n, c);
				if (i != -1)
				{
					delete(ui->c, i,1);
					printf("The product was deleted!\n");
				}
				else
				{
					printf("The product was not found\n");
				}
				break;
			}
			case 4:
			{
				char n[255];
				printf("Enter the string:\n");
				scanf("%s", n);
				DynamicRefrigerator *r = initRepo(50);
				findName(ui->c, n,r);
				if (r->lenght == 0)
				{
					findall(ui->c, r);
				}
					orderA(r);
					listR(r);
				
				destroyAux(r);
				break;
			}
			case 5:
			{
				char n[255];
				printf("Enter the category please:\n");
				scanf("%s", n);
				DynamicRefrigerator *r = initRepo(50);
				findCategory(ui->c, n, r);
				if (r->lenght == 0)
				{
					printf("Nothing found");
					break;
				}
				orderDate(r);
				listDate(r);
				destroyAux(r);
				break;
			}
			case 6:
			{
				char n[255];
				printf("Enter the category please:\n");
				scanf("%s", n);
				DynamicRefrigerator *r = initRepo(50);
				int x;
				printf("Enter the number of days:\n");
				scanf("%d", &x);
				findCategory(ui->c, n, r);
				if (r->lenght == 0)
				{
					listexpiration(ui->c->dr,x);
				}
				else
					listexpiration(r,x);
				destroyAux(r);
				break;
			}
			case 7:
			{
				if (undolast(ui->c) == 0)
				{
					printf("Impossible undo\n");
				}
				break;
			}
			case 8:
			{
				if (redolast(ui->c) == 0)
				{
					printf("Impossible redo\n");
				}
				break;
			}
			case 9:
			{
				char n[255];
				printf("Enter the category please:\n");
				scanf("%s", n);
				DynamicRefrigerator *r = initRepo(50);
				findCategory(ui->c, n, r);
				if (r->lenght == 0)
					printf("No product found!\n");
				else
				{
					sortQ(r);
					for (int i = 0; i < r->lenght; i++)
					{
						printf("The product %s has the quantity : %d  \n", r->p[i]->name, r->p[i]->quantity);
					}
				}
				break;
			}

		}
		
	}
}

void listAll(UI *ui)
{
	/*
	We list all the products
	*/
	DynamicRefrigerator* d = getR(ui->c);
	int n = getLenght(d);
	for(int i = 0; i < n; i++)
	{
		char s[255];
		getProduct(get(d, i), s);
		printf("%s\n", s);
	}
}
void listDate(DynamicRefrigerator *d)
{
	/*
	We list the elements from the refrigerator poiting out the dates
	*/
	int n = getLenght(d);
	for (int i = 0; i < n; i++)
	{
		printf("The product %s from the given category has the expiration date %s\n", d->p[i]->name, d->p[i]->expiration);
	}

}
void listR(DynamicRefrigerator *d)
{
	/*
	We list the things we need
	*/
	int n = getLenght(d);
	for (int i = 0; i < n; i++)
	{
		printf("%s with the quantity: %d \n", d->p[i]->name,d->p[i]->quantity);
	}
}