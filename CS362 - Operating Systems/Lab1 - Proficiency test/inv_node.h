#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct inv_node {
	char *name;
	double price;
	int quantity;
	struct inv_node *next;
} INV_NODE;

void display(INV_NODE *node);

INV_NODE *add(INV_NODE *list, INV_NODE *node);

INV_NODE *find(INV_NODE *list, char *name);
