#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Структура для представления дерева выражений
typedef struct Node {
    char data[10];
    struct Node* left;
    struct Node* right;
} Node;

// Функция для создания нового узла
Node* createNode(char* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->data, data);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для печати выражения в инфиксной нотации
void printInfix(Node* root) {
    if (root == NULL) return;
    if (root->left != NULL) printf("(");
    printInfix(root->left);
    printf("%s", root->data);
    printInfix(root->right);
    if (root->right != NULL) printf(")");
}

// Функция для преобразования (a/b)/c в a/(b*c) и a/(b/c) в (a/b)*c
Node* simplifyFraction(Node* root) {
    if (root == NULL) return NULL;
    if (strcmp(root->data, "/") == 0) {
        if (root->left && strcmp(root->left->data, "/") == 0) {
            // (a/b)/c -> a/(b*c)
            Node* a = root->left->left;
            Node* b = root->left->right;
            Node* c = root->right;

            // Создаем новое дерево для b*c
            Node* newRight = createNode("*");
            newRight->left = b;
            newRight->right = c;

            // Создаем новое дерево для a/(b*c)
            Node* newRoot = createNode("/");
            newRoot->left = a;
            newRoot->right = newRight;

            return newRoot;
        }
        if (root->right && strcmp(root->right->data, "/") == 0) {
            // a/(b/c) -> (a/b)*c
            Node* a = root->left;
            Node* b = root->right->left;
            Node* c = root->right->right;

            // Создаем новое дерево для (a/b)
            Node* newLeft = createNode("/");
            newLeft->left = a;
            newLeft->right = b;

            // Создаем новое дерево для (a/b)*c
            Node* newRoot = createNode("*");
            newRoot->left = newLeft;
            newRoot->right = c;

            return newRoot;
        }
    }
    root->left = simplifyFraction(root->left);
    root->right = simplifyFraction(root->right);
    return root;
}

int main() {
    //1: (a/b)/c -> a/(b*c)
    setlocale(LC_ALL, "Rus");
    Node* root1 = createNode("/");
    root1->left = createNode("/");
    root1->left->left = createNode("a");
    root1->left->right = createNode("b");
    root1->right = createNode("c");

    printf("Исходное выражение 1: ");
    printInfix(root1);
    printf("\n");

    root1 = simplifyFraction(root1);

    printf("Преобразованное выражение 1: ");
    printInfix(root1);
    printf("\n\n");

    //2: a/(b/c) -> (a/b)*c
    Node* root2 = createNode("/");
    root2->left = createNode("a");
    root2->right = createNode("/");
    root2->right->left = createNode("b");
    root2->right->right = createNode("c");

    printf("Исходное выражение 2: ");
    printInfix(root2);
    printf("\n");

    root2 = simplifyFraction(root2);

    printf("Преобразованное выражение 2: ");
    printInfix(root2);
    printf("\n");

    return 0;
}
