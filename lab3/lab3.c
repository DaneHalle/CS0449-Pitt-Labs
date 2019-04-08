// Dane Halle (dmh148)
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int value;
	struct Node* next;
} Node;

Node* create_node(int value)
{
	Node* out=malloc(sizeof(Node));
	out->value=value;
	out->next=NULL;
	return out;
}

void list_print(Node* head)
{
	if(head->next!=NULL){
		printf("%d -> ", head->value);
		list_print(head->next);
	}
	if(head->next==NULL){
		printf("%d\n", head->value);
	}
}

Node* list_append(Node* head, int value)
{
	if(head->next!=NULL){
		list_append(head->next, value);
	}
	if(head->next==NULL){
		head->next=create_node(value);
	}
	return head->next;
}

Node* list_prepend(Node* head, int value)
{
	Node* new_head=create_node(value);
	new_head->next=head;
	return new_head;
}

void list_free(Node* head)
{
	if(head->next!=NULL){
		list_free(head->next);
		head->next=NULL;
	}
	if(head->next==NULL){
		free(head);
	}
}

Node* list_remove(Node* head, int value)
{
	if(value==head->value){
		Node* out=head->next;
		head->next=NULL;
		list_free(head);
		return out;
	}
	if(head->next==NULL){
		return head;
	}
	if(value==head->next->value){
		Node* free=head->next;
		if(head->next->next==NULL){
			head->next=NULL;
		}else{
			head->next=free->next;
		}
		free->next=NULL;
		list_free(free);
		return head;
	}else{
		list_remove(head->next, value);
	}
	return head;
}

int main()
{
	// The comments at the ends of the lines show what list_print should output.
	Node* head = create_node(1);
	list_print(head);                  // 1
	Node* end = list_append(head, 2);
	list_print(head);                  // 1 -> 2
	end->next = create_node(3);
	list_print(head);                  // 1 -> 2 -> 3
	head = list_prepend(head, 0);
	list_print(head);                  // 0 -> 1 -> 2 -> 3
	head = list_prepend(head, -1);
	list_print(head);
	list_append(head, 4);
	list_print(head);                  // 0 -> 1 -> 2 -> 3 -> 4
	list_append(head, 5);
	list_print(head);                  // 0 -> 1 -> 2 -> 3 -> 4 -> 5

	head = list_remove(head, 5);
	list_print(head);                  // 0 -> 1 -> 2 -> 3 -> 4
	head = list_remove(head, 5);
	list_print(head);
	head = list_remove(head, 3);
	list_print(head);                  // 0 -> 1 -> 2 -> 4
	head = list_remove(head, 0);
	list_print(head);                  // 1 -> 2 -> 4
	head = list_remove(head, -1); 
	list_print(head);
	head = list_remove(head, 4);
	list_print(head);
	head = list_remove(head, 1);
	list_print(head);

	list_free(head);

	return 0;
}
