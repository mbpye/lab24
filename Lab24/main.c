#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


typedef struct Node {
    char operation; //(+, -, \*, /)
    char variable; // ��������� ���������
    int power; // ������� ���������� ���������
    struct Node* left; // ����� �������� ����
    struct Node* right; // ������ �������� ����
} Node;


Node* createNode(char operation, char variable, int power) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->operation = operation;
    newNode->variable = variable;
    newNode->power = power;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* simplify(Node* node) {
    if (node == NULL) {
        return NULL;
    }


    if (node->operation == '/') {
        if (node->left->operation == '/' && node->right->operation == '/') {
            Node* left = simplify(node->left);
            Node* right = simplify(node->right);
            if (left->operation == '/' && right->operation == '/') {
                if (left->variable == right->variable && left->power == right->power) {
                    return createNode('/', left->variable, left->power - right->power);
                }
            }
        }
    }

    if (node->operation == '*') {
        if (node->left->operation == '*' && node->right->operation == '*') {
            Node* left = simplify(node->left);
            Node* right = simplify(node->right);
            if (left->operation == '*' && right->operation == '*') {
                if (left->variable == right->variable) {
                    return createNode('*', left->variable, left->power + right->power);
                }
            }
        }
    }

    return node;
}


void printExpression(Node* node) {
    if (node == NULL) {
        return;
    }

    if (node->operation == '+') {
        printf("(");
        printExpression(node->left);
        printf(" + ");
        printExpression(node->right);
        printf(")");
    }
    else if (node->operation == '/') {
        printf("(");
        printExpression(node->left);
        printf(" / ");
        printExpression(node->right);
        printf(")");
    }
    else if (node->operation == '*') {
        printExpression(node->left);
        printf("*");
        printExpression(node->right);
    }
    else {
        if (node->power == 1) {
            printf("%c", node->variable);
        }
        else {
            printf("%c^%d", node->variable, node->power);
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    char expression[100];
    printf("������� ������������ ������� ��������� � ���������� ����������� (��������, a/(b/c)): ");
    fgets(expression, 100, stdin);
    expression[strcspn(expression, "\n")] = '\0';


    Node* root = NULL;
    int i = 0;
    while (expression[i] != '\0') {
        if (isalpha(expression[i])) {
            char variable = expression[i];
            int power = 1;
            if (expression[i + 1] == '^') {
                i++;
                power = 0;
                while (isdigit(expression[++i])) {
                    power = power * 10 + (expression[i] - '0');
                }
            }
            if (root == NULL) {
                root = createNode('*', variable, power);
            }
            else {
                Node* newNode = createNode('*', variable, power);
                newNode->left = root;
                root = newNode;
            }
        }
        else if (expression[i] == '/') {
            Node* newNode = createNode('/', 0, 0);
            newNode->left = root;
            root = newNode;
        }
        else if (expression[i] == '(') {
            int j = i;
            int depth = 1;
            while (depth > 0) {
                j++;
                if (expression[j] == '(') depth++;
                else if (expression[j] == ')') depth--;
            }
            char subExpression[100];
            strncpy(subExpression, expression + i + 1, j - i - 1);
            subExpression[j - i - 1] = '\0';
            Node* subRoot = main(subExpression);
            if (root == NULL) {
                root = subRoot;
            }
            else {
                Node* newNode = createNode('/', 0, 0);
                newNode->left = root;
                newNode->right = subRoot;
                root = newNode;
            }
            i = j;
        }
        i++;
    }

    Node* simplified = simplify(root);

    printf("�������� ���������: ");
    printExpression(root);
    printf("\n");

    printf("���������� ���������: ");
    printExpression(simplified);
    printf("\n");

    return 0;
}