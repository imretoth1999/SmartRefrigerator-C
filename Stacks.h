#pragma once
#include "Repo.h"

typedef struct {
	Product *p;
	char *type;
}Operation;

typedef struct {
	Operation* op[100];
	int n;
}OperationStack;

Operation * create_operation(Product* p, char * type);

void destroy_operation(Operation * op);

Operation * operation_copy(Operation * op);

OperationStack* create_operation_stack();

void destroy_operation_stack(OperationStack* stack);

void delete_op(OperationStack* o, int pos);

void push(OperationStack* stack, Operation* op);

Operation* pop(OperationStack* stack);
