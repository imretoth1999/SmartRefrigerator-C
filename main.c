#include "UI.h"
int main()
{
	test();

	DynamicRefrigerator *repo = initRepo(50);
	OperationStack* undo = create_operation_stack();
	OperationStack* redo = create_operation_stack();
	Controller *ctrl = initCtrl(repo,undo,redo);
	UI *ui = initUI(ctrl);
	
	addProductCtrl(ui->c, "Waffle", "Sweets", 2, "11/02/2019",1);
	addProductCtrl(ui->c, "Banana", "Fruit", 100, "4/04/2018",1);
	addProductCtrl(ui->c, "Pork", "Meat", 1, "1/09/2018",1);
	addProductCtrl(ui->c, "Milk", "Dairy", 50, "11/05/2018",1);
	addProductCtrl(ui->c, "Jelly Beans", "Sweets", 1, "24/02/2021",1);
	addProductCtrl(ui->c, "Sugar", "Sweets", 10, "21/02/2011",1);
	start(ui);
	finish(ui);
	_CrtDumpMemoryLeaks();
	return 0;
}