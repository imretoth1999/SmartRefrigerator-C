#include "Controller.h"

Controller* initCtrl(DynamicRefrigerator *d,OperationStack *u, OperationStack *r)
{
	/*
	We initialise the controller
	*/
	Controller *c = (Controller*)malloc(sizeof(Controller));
	c->dr = d;
	c->undo_s = u;
	c->redo_s = r;
	return c;
}
void destroyCtrl(Controller *c)
{
	/*
	We destroy the controller
	*/
	destroy(c->dr);

	free(c);
}

int addProductCtrl(Controller *c, char *name, char *category, int quantity, char *expiration,int ok)
{
	/*
	We add a product
	if the product exists,we add to the existing quantity the given quantity
	*/
	Product *pr = createProduct(name, category, quantity, expiration);
	DynamicRefrigerator *r = getR(c);
	for (int i = 0; i < getLenght(r); i++)
	{
		if ((strcmp(r->p[i]->name, pr->name) == 0) && (strcmp(r->p[i]->category, pr->category) == 0))
		{
			r->p[i]->quantity += quantity;
			return 0;
		}
	}
	add(c->dr, pr);
	if (ok != -1)
	{
		Operation *op = create_operation(pr, "add");
		push(c->undo_s, op);
		destroy_operation(op);
		//destroy_operation_stack(c->redo_s);
		
	}
	return 1;
}

void delete(Controller* dr, int pos,int ok)
{
	/*
	We delete the a product at a given position
	*/
	if (dr->dr == NULL)
		return;
	if (dr->dr->p == NULL)
		return;
	if (pos < 0 || pos >= dr->dr->lenght)
		return;
	Product *pro = copyProduct(dr->dr->p[pos]);
	for (int i = pos; i < dr->dr->lenght - 1; i++)
		dr->dr->p[i] = dr->dr->p[i + 1];
	dr->dr->lenght--;
	if (ok != -1)
	{
		Operation *op = create_operation(pro, "del");
		push(dr->undo_s, op);
		destroy_operation(op);
	}
}
Product* updateCtrl(Controller *c, char *name, char *category, int quantity, char *expiration)
{
	/*
	We update the quantity and the expiration date
	We return 1 if the update was succesful
	0 otherwise
	*/
	for (int i = 0; i < c->dr->lenght; i++)
	{
		if ((strcmp(c->dr->p[i]->name, name) == 0) && (strcmp(c->dr->p[i]->category, category) == 0))
		{
				Operation* op = create_operation(c->dr->p[i], "update");
				push(c->undo_s, op);
				destroy_operation(op);
			c->dr->p[i]->quantity = quantity;
			c->dr->p[i]->expiration = (char *)realloc(c->dr->p[i]->expiration, 255);
			strcpy(c->dr->p[i]->expiration, expiration);
			return c->dr->p[i];
		}
	}
	return NULL;
}
int findCtrl(Controller *c, char *name, char *category)
{
	/*
	We find the index of a given product
	*/
	DynamicRefrigerator *r = getR(c);
	for (int i = 0; i < getLenght(r); i++)
	{
		if ((strcmp(r->p[i]->name, name) == 0) && (strcmp(r->p[i]->category, category) == 0))
		{
			return i;
		}
	}
	return -1;
}

void findName(Controller *c, char *name, DynamicRefrigerator *aux)
{
	/*
	We find all products containing a given string
	*/
	DynamicRefrigerator* r = getR(c);
	for (int i = 0; i < getLenght(r); i++)
	{
		if ((strstr(r->p[i]->name, name)))
		{
			Product *p = copyProduct(r->p[i]);
			add(aux, p);
		}
	}
}
void findCategory(Controller *c, char *category, DynamicRefrigerator *a)
{
	/*
	We find all the elements from the given category
	*/
	for (int i = 0; i < c->dr->lenght; i++)
	{
		if (strcmp(c->dr->p[i]->category, category) == 0)
		{
			Product *p = copyProduct(c->dr->p[i]);
			add(a, p);
		}
	}
}

void findall(Controller *c, DynamicRefrigerator * aux)
{
	/*
	We give to the repo all the elements
	*/
	for (int i = 0; i < c->dr->lenght; i++)
	{
		Product *p = copyProduct(c->dr->p[i]);
		add(aux, p);
	}
}
DynamicRefrigerator* getR(Controller *c)
{
	/*
	We return the repo
	*/
	return c->dr;
}


int undolast(Controller *c)
{
	/*
	We undo the last operation
	*/
	if (c->undo_s->n == 0 || c->redo_s == NULL || c->undo_s == NULL)
		return 0;

	Operation *o = pop(c->undo_s);
	if (strcmp(o->type, "add") == 0)
	{
		Operation* op = create_operation(o->p, "add");
		push(c->redo_s, op);
		destroy_operation(op);
		Product *p = o->p;
		delete(c, findCtrl(c, o->p->name, o->p->category),-1);
	}
	else if (strcmp(o->type, "del") == 0)
	{
		Operation *op = create_operation(o->p, "del");
		push(c->redo_s, op);
		destroy_operation(op);
		Product *p = o->p;
		add(c->dr, p,-1);
		
	}
	else if (strcmp(o->type, "update") == 0)
	{
		Product *p = o->p;
		Operation *op = create_operation(p, "update");
		push(c->redo_s, op);
		destroy_operation(op);
		delete(c, findCtrl(c, o->p->name, o->p->category),-1);
		add(c->dr, p,-1);

	}
	return 1;
}

int redolast(Controller *c)
{
	/*
	We redo the last operation
	*/
	if (c->redo_s->n == 0 || c->redo_s == NULL)
		return 0;
	Operation *o = pop(c->redo_s);
	if (strcmp(o->type, "add") == 0)
	{
		Product *p = copyProduct(o->p);
		add(c->dr, p,-1);
	}
	else if (strcmp(o->type, "del") == 0)
	{
		Product *p = o->p;
		delete(c, findCtrl(c, o->p->name, o->p->category), -1);
	}
	else if (strcmp(o->type, "update") == 0)
	{
		Product *p = o->p;
		delete(c, findCtrl(c, o->p->name, o->p->category), -1);
		add(c->dr, p, 1);
	}
}