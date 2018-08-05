#include <stdio.h>
#include <stdlib.h>

typedef struct list {int data; struct list *next;} LIST;

LIST *start, *end;

void add(LIST **head, LIST **tail, int data);

int delete(LIST **head, LIST **tail);

int main(void){
	start=end=NULL;
	add(&start, &end, 2);
	add(&start, &end, 3);
	printf("First element: %d\n", delete(&start, &end));
	printf("Second element: %d\n", delete(&start, &end));
	printf("Third element: %d\n", delete(&start, &end));
}

void add(LIST **head, LIST **tail, int data){
	if(*tail==NULL){
		*head=*tail=(LIST *) malloc(sizeof(LIST));
		(*head)->data=data;
		(*head)->next=NULL;
	}
	else{
		(*tail)->next= (LIST *) malloc(sizeof(LIST));
		*tail=(*tail)->next;
		(*tail)->data=data;
		(*tail)->next=NULL;
	}
}

int delete (LIST **head, LIST **tail){
	LIST *temp;
	
	if (*head == NULL)
		return -1;
	
	int retVal = (*head)->data;
	
	if(*head==*tail){
		free(*head);
		*head=*tail=NULL;
	}
	else{
		temp=(*head)->next;
		free(*head);
		*head=temp;
	}
	
	return retVal;
}
