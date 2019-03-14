#pragma once
#include "Repo.h"
#include "Stacks.h"

typedef struct {
	DynamicRefrigerator* dr;

	OperationStack *undo_s;

	OperationStack *redo_s;
} Controller;

void destroyCtrl(Controller *c);
Controller* initCtrl(DynamicRefrigerator *d, OperationStack *u, OperationStack *r);
int addProductCtrl(Controller *c, char *name, char *category, int quantity, char *expiration, int ok);
void delete(Controller* dr, int pos, int ok);
Product* updateCtrl(Controller *c, char *name, char *category, int quantity, char *expiration);
int findCtrl(Controller *c, char *name, char *category);
void findName(Controller *c, char *name, DynamicRefrigerator *aux);
void findCategory(Controller *c, char *category, DynamicRefrigerator *a);
void findall(Controller *c, DynamicRefrigerator * aux);
DynamicRefrigerator* getR(Controller *c);
int undolast(Controller *c);
int redolast(Controller *c);

