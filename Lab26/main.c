#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Node* mergeLists(Node* list1, Node* list2) {
    if (list1 == NULL && list2 == NULL) {
        return NULL;
    }

    if (list1 == NULL) {
        return list2;
    }

    if (list2 == NULL) {
        return list1;
    }

    if (list1->value < list2->value) {
        list1->next = mergeLists(list1->next, list2);
        return list1;
    }

    if (list2->value < list1->value) {
        list2->next = mergeLists(list1, list2->next);
        return list2;
    }


    Node* result = createNode(list1->value);
    result->next = mergeLists(list1->next, list2);
    return result;
}


void printList(Node* list) {
    while (list != NULL) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main() {

    Node* list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->next = createNode(5);

    Node* list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next = createNode(6);

    Node* mergedList = mergeLists(list1, list2);

    printList(mergedList);

    return 0;
}