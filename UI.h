#pragma once
#include "Controller.h"
#include <crtdbg.h>

typedef struct {

	Controller* c;
} UI;

UI* initUI(Controller *c);
void finish(UI* ui);
int getCommand(const char* m);
void printMenu();
void start(UI *ui);
void listAll(UI *ui);
void listDate(DynamicRefrigerator *d);
void listR(DynamicRefrigerator *d);

