#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//--------------------
typedef struct {
    int elements[MAX_SIZE];
    int front;
    int rear;
} Deque;

//-------------------------------------------------
Deque* createDeque() {
    Deque* newDeque = (Deque*)malloc(sizeof(Deque));
    newDeque->front = -1;
    newDeque->rear = -1;
    return newDeque;
}

//--------------------------------------
void push_back(Deque* deque, int value) {
    if (deque->rear == MAX_SIZE - 1) {
        printf("Deque is full\n");
        return;
    }
    if (deque->front == -1) {
        deque->front = 0;
    }
    deque->rear++;
    deque->elements[deque->rear] = value;
}

//-------------------------------------
void push_front(Deque* deque, int value) {
    if (deque->front == 0) {
        printf("Cannot insert at front\n");
        return;
    }
    if (deque->front == -1) {
        deque->front = 0;
        deque->rear = 0;
    }
    else {
        deque->front--;
    }
    deque->elements[deque->front] = value;
}

//-удаления  из конца дека---
void pop_back(Deque* deque) {
    if (deque->front == -1) {
        printf("Deque is empty\n");
        return;
    }
    if (deque->rear == deque->front) {
        deque->front = -1;
        deque->rear = -1;
    }
    else {
        deque->rear--;
    }
}

//----удаления из начала дека--
void pop_front(Deque* deque) {
    if (deque->front == -1) {
        printf("Deque is empty\n");
        return;
    }
    if (deque->front == deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    }
    else {
        deque->front++;
    }
}

// ---слияния двух деков----------------------------
Deque* mergeDeques(Deque* deque1, Deque* deque2) {
    Deque* result = createDeque();
    int i = deque1->front;
    int j = deque2->front;

    while (i <= deque1->rear && j <= deque2->rear) {
        if (deque1->elements[i] <= deque2->elements[j]) {
            push_back(result, deque1->elements[i]);
            i++;
        }
        else {
            push_back(result, deque2->elements[j]);
            j++;
        }
    }

    while (i <= deque1->rear) {
        push_back(result, deque1->elements[i]);
        i++;
    }

    while (j <= deque2->rear) {
        push_back(result, deque2->elements[j]);
        j++;
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "rus");
    Deque* deque1 = createDeque();
    Deque* deque2 = createDeque();

    push_back(deque1, 1);
    push_back(deque1, 3);
    push_back(deque1, 5);

    push_back(deque2, 2);
    push_back(deque2, 4);
    push_back(deque2, 6);

    Deque* mergedDeque = mergeDeques(deque1, deque2);

    printf("Слияние деков:\n");
    while (mergedDeque->front != -1) {
        printf("%d ", mergedDeque->elements[mergedDeque->front]);
        pop_front(mergedDeque);
    }
    printf("\n");

    return 0;
}
