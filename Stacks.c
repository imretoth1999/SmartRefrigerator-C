#include "Stacks.h"

Operation * create_operation(Product* p, char * type)
{
	/*
	We create an operation we can use
	*/
	Operation* op = (Operation*)malloc(sizeof(Operation));
	op->p = copyProduct(p);
	op->type = (char*)malloc(sizeof(char)*strlen(type) + 1);
	strcpy(op->type, type);
	return op;
}

void destroy_operation(Operation * op)
{
	/*
	We destroy an operation
	*/
	destroyProduct(op->p);
	free(op);
}

Operation * operation_copy(Operation * op)
{
	/*
	We return a copy of the operation
	*/
	Operation* new_op = create_operation(op->p, op->type);
	return new_op;
}
OperationStack* create_operation_stack()
{
	/*
	We create a new operation stack
	*/
	OperationStack* stack = (OperationStack*)malloc(sizeof(OperationStack));
	stack->n = 0;

	return stack;
}

void destroy_operation_stack(OperationStack* stack)
{
	/*
	We destroy the operation stack
	*/
	for (int i = 0; i < stack->n; i++) {
		destroy_operation(stack->op[i]);
	}

	free(stack);
}

void delete_op(OperationStack* o, int pos)
{
	/*
	We delete the operation
	*/
	if (o == NULL)
		return;
	if (pos < 0 || pos >= o->n)
		return;
	for (int i = pos; i < o->n - 1; i++)
		o->op[i] = o->op[i+1];
	o->n--;
}

void push(OperationStack* stack, Operation* op)
{	
	/*
	We push the op in the stack
	*/
	if (stack->n == 100)
		return;
	stack->op[stack->n] = operation_copy(op);
	stack->n++;
}

Operation* pop(OperationStack* stack)
{
	/*
	We pop the last operation
	*/
	if (stack->n == 0)
		return NULL;
	Operation* op = stack->op[stack->n - 1];
	stack->n--;

	return op;
}