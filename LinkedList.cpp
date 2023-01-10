#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {

	int num;
	Node* next;
};

void append(struct Node** head, int value);
bool isPresent(struct Node* head, int num);
void printList(struct Node* node);

void unionLL(Node* LA, Node* LB) {

	Node* newNode = NULL;

	while (LA != NULL) {
		append(&newNode, LA->num);
		LA = LA->next;
	}

	while (LB != NULL) {
		if (!isPresent(newNode, LB->num))
			append(&newNode, LB->num);
		LB = LB->next;
	}

	printf("\nUnion of A and B is: \n");
	printList(newNode);
	printf("\n\n");
}

void append(struct Node** head, int value) {

	Node* newNode = new Node;
	Node* tail = *head;
	newNode->num = value;
	newNode->next = NULL;

	if (head == NULL) {
		*head = newNode;
		return;
	}

	while (tail->next != NULL)
		tail = tail->next;

	tail->next = newNode;
}

void printList(struct Node* node) {

	while (node != NULL) {
		printf("%d ", node->num);
		node = node->next;
	}
}

bool isPresent(struct Node* head, int value) {

	while (head != NULL) {
		if (head->num == value)
			return 1;
		head = head->next;
	}
	return 0;
}

int main()
{
	struct Node* LA = NULL;
	struct Node* LB = NULL;
	struct Node* mergeLL = NULL;

	append(&LA, 3);
	append(&LA, 5);
	append(&LA, 8);
	append(&LA, 11);
	append(&LB, 2);
	append(&LB, 6);
	append(&LB, 8);
	append(&LB, 9);
	append(&LB, 22);
	append(&LB, 24);

	printf("\nLinked List A is: \n");
	printList(LA);
	printf("\n");
	printf("\nLinked List B is: \n");
	printList(LB);
	printf("\n");
	unionLL(LA, LB);

	return 0;
}

