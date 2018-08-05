#include "inv_node.h"
void display(INV_NODE *node)
{
	while(node->next != NULL){
		printf("ITEM:   Name - %s, Price - $%f, Quantity - %f", node->name, node->price,node->quantity);
	}
}

INV_NODE *add(INV_NODE *list, INV_NODE *node)
{
	list->next = node;
    return node;
}

INV_NODE *find(INV_NODE *list, char *name){
	
	if(strncmp(list->name,name,strlen(name))==0){
		
		return list;
		
		}else{
			
			if(list->next != NULL){
			find(list->next,name);
				
				}else{
				
				return NULL;	
				}
			}	
			
    return 0;
}
int main(void)
{
	int flag;
	char input;
	char nextchar;
	char* readname;
	double readprice;
	int readquantity;
	double custmoney = 0;
	char* customerwant;
	int custquantity = 0;
	INV_NODE *currnode = malloc(sizeof(INV_NODE));
		
	INV_NODE *inventory = malloc(sizeof(INV_NODE));
	inventory->name = "Inventory";
	inventory->price = 0;
	inventory->quantity = 0;
	inventory->next = NULL;
	
	currnode = inventory;
	
	inventory->next = currnode;
	currnode->name = "List";
	
	while ((input = getchar()) != EOF )){
	
	flag = 0;
	nextchar = getchar();
	 
	if(input == I){
		
		while(nextchar = getchar() != ' '){
			strcat(readname,nextchar);
		}
		additem->name = readname;
		
		scanf("%lf", &readprice);
		
		scanf("%lf", &readquantity);
		
		if(find(inventory,readname) == NULL){
			inv_node *additem= malloc(sizeof(struct INV_NODE));
			additem->name = readname;
			additem->price = readprice;
			additem->quantity = readquantity;
			
			currnode = add(currnode, additem);
			currnode->next = NULL;
			
		}else{
			currnode->quantity = currnode->quantity +readquantity;
			//if the node has already been created, just add the quantity to that node
		}
	}
	else if(input = 'C'){
		
		custmoney = 0;
		strcpy(customerwant, "");
		custquantity = 0;
		
		scanf("%lf",&custmoney);
		
		scanf("%lf",&custquantity);
		
		char nextchar = getchar();
		
		while(nextchar = getchar() != ' '){
			strcat(customerwant,nextchar);
		}
		
		
		currnode = find(inventory,customerwant);
		
		if(currnode == NULL){
			flag = 1;
			printf("Error: item not found");
			}
		
		if(custquantity > currnode->quantity){
			flag = 1;
			printf("Error: insufficient item quantity for customer");
			}
		
		double custneedpay = (custquantity * currnode->price);
		
		if(custneedpay > custmoney){
			flag = 1;
			printf("Error: insufficient funds to pay for items");
			}
		
		if(flag == 0){
			currnode->quantity = currnode->quantity-custquantity;
			double remainingcash = (custmoney - custneedpay);
			printf("Success! The customer's change is: $%f",remainingcash);
			
			}
		
	}else{	
		printf("Wrong input format");
			}
}
	display(inventory);
    return 0;
}
