#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[20];
    struct student *next;
};

int main(void) {
    int count = 0, id;
    char name[20];
    struct student *p, *head = NULL;

    printf("Enter student ID and name\n");

    while (scanf("%d %19s", &id, name) == 2) {
        p = (struct student *)malloc(sizeof(struct student));
        if (p == NULL) {
            fprintf(stderr, "Error: malloc failed.\n");
            exit(1);
        }
        p->id = id;
        strcpy(p->name, name);
        p->next = head;
        head = p;
    }

    printf("\n* Student Information (Reverse Order) *\n");
    p = head;
    while (p != NULL) {
        count++;
        printf("ID: %d Name: %s\n", p->id, p->name);
        p = p->next;
    }
    printf("Total %d students.\n", count);

    p = head;
    while (p != NULL) {
        struct student *next = p->next;
        free(p);
        p = next;
    }

    return 0;
}

