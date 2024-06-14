#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char op;
    struct Node* left;
    struct Node* right;
} Node;


char* readExpression() {
    char buffer[1024];
    printf("Введите выражение: ");
    fgets(buffer, sizeof(buffer), stdin);
    return buffer;
}


char* reversePolishNotation(char* expr) {
    char* result = (char*)malloc(strlen(expr) * sizeof(char));
    int i = 0, j = 0;
    for (; i < strlen(expr); i++) {
        if (expr[i] == '(') {
            result[j++] = '(';
        }
        else if (expr[i] == ')') {
            result[j++] = ')';
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (j > 0 && result[j - 1] != '(') {
                result[j++] = result[--j];
            }
            result[j++] = expr[i];
        }
        else {
            result[j++] = expr[i];
        }
    }
    result[j] = '\0';
    return result;
}


Node* createTree(char* exprNotation) {
    Node* root = NULL;
    for (int i = 0; i < strlen(exprNotation); i++) {
        if (exprNotation[i] == '(') {
            Node* node = (Node*)malloc(sizeof(Node));
            node->op = exprNotation[++i];
            node->left = createTree(&exprNotation[i]);
            i++;
            node->right = createTree(&exprNotation[i]);
            if (root == NULL) {
                root = node;
            }
            else {
                Node* current = root;
                while (current->right != NULL) {
                    current = current->right;
                }
                current->right = node;
            }
        }
    }
    return root;
}


void simplifyTree(Node* tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->op == '+') {
        if (tree->left->op == '+' || tree->right->op == '+') {
            simplifyTree(tree->left);
            simplifyTree(tree->right);
        }
    }
    else if (tree->op == '-') {
        if (tree->left->op == '-' || tree->right->op == '-') {
            simplifyTree(tree->left);
            simplifyTree(tree->right);
        }
    }
    else if (tree->op == '*') {
        if (tree->left->op == '*' || tree->right->op == '*') {
            simplifyTree(tree->left);
            simplifyTree(tree->right);
        }
    }
    else if (tree->op == '/') {
        if (tree->left->op == '/' || tree->right->op == '/') {
            simplifyTree(tree->left);
            simplifyTree(tree->right);
        }
    }
}


char* buildExpression(Node* tree) {
    char* result = (char*)malloc(1024 * sizeof(char));
    if (tree == NULL) {
        return result;
    }
    if (tree->left != NULL) {
        strcat(result, buildExpression(tree->left));
    }
    strcat(result, " ");
    strcat(result, &tree->op);
    strcat(result, " ");
    if (tree->right != NULL) {
        strcat(result, buildExpression(tree->right));
    }
    return result;
}

int main() {
    char* expr = readExpression();
    char* exprNotation = reversePolishNotation(expr);
    Node* tree = createTree(exprNotation);
    simplifyTree(tree);
    char* res = buildExpression(tree);
    printf("Результат: %s\n", res);
    free(exprNotation);
    free(res);
    return 0;
}