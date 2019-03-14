#include "Controller.h"

void test_create()
{
	DynamicRefrigerator* dr = initRepo(2);
	if (dr == NULL)
		assert(0);
	assert(dr->capacity == 2);
	assert(dr->lenght == 0);
	destroy(dr);

}
void test_add()
{
	DynamicRefrigerator* dr = initRepo(2);
	Product* p1 = createProduct("Waffle", "Sweets", 2, "11/02/2019");
	add(dr, p1);
	assert(dr->lenght == 1);

	Product* p2 = createProduct("Pork", "Meat", 1, "1/09/2018");

	add(dr, p2);
	assert(dr->lenght == 2);

	Product* p3 = createProduct("Milk", "Dairy", 50, "11/05/2018");
	add(dr, p3);
	assert(dr->lenght == 3);
	assert(dr->capacity == 4);
	destroy(dr);

}
void test_get()
{
	DynamicRefrigerator* dr = initRepo(2);
	Product* p1 = createProduct("Waffle", "Sweets", 2, "11/02/2019");
	add(dr, p1);
	Product* p2 = createProduct("Pork", "Meat", 1, "1/09/2018");

	add(dr, p2);

	Product* p3 = createProduct("Milk", "Dairy", 50, "11/05/2018");
	add(dr, p3);

	Product* p = get(dr, 0);
	assert(strcmp(dr->p[0]->name, "Waffle") == 0);
	assert(dr->lenght == 3);
	destroy(dr);
}
void test_delete()
{
	DynamicRefrigerator* dr = initRepo(2);
	Product* p1 = createProduct("Waffle", "Sweets", 2, "11/02/2019");
	add(dr, p1);
	Product* p2 = createProduct("Pork", "Meat", 1, "1/09/2018");

	add(dr, p2);

	Product* p3 = createProduct("Milk", "Dairy", 50, "11/05/2018");
	add(dr, p3);

	delete_repo(dr, 0);
	assert(strcmp(dr->p[0]->name, "Pork") == 0);
	assert(dr->lenght == 2);
	destroy(dr);
}