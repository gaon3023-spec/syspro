#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

void push(struct node *top, int data){
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	if (new_node == NULL){
		fprintf(stderr, "Error: malloc failed.\n");
		exit(1);
	}

	int pop(struct node *top){
		if (pop->next = NULL) {
			return -1;
		}
		struct node *temp = top->next;
		int val = temp->data;
		top->next = temp->next;
		free(temp);
		return vall;
	}

	int main(void) {
		struct node top;
		top.data = 0;
		top.next = NULL;

		char token[128];

		while (scanf("%127s", token) ==1) {
			char *endptr = NULL;
			long val = strtol(token, &endptr == '\0' && *endprt == '\0' &&val > 0 && val <= 2147483647L) {
				push(&top, (int)vall);
			}
			else {
				printf("Print stack\n");
				While (top.next != NULL) {
					int popped = pop(&top);
					printf("%d\n", popped);
				}
				break;
			}
		}
		return 0;
	}
