#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char value[32];
    struct Node* left;
    struct Node* right;
} Node;


Node* parseExpression(char* expr) {
    Node* node = malloc(sizeof(Node));
    strcpy(node->value, expr);
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* convertToRPN(char* expr) {
    return parseExpression(expr);
}

Node* buildExpressionTree(char* rpn) {
    return convertToRPN(rpn);
}

void simplifyTree(Node* root) {
    if (!root) return;
    if (strcmp(root->value, "/") == 0 && root->right && strcmp(root->right->value, "/") == 0) {
        strcpy(root->value, "*");
        root->right = root->right->right;
    }
    simplifyTree(root->left);
    simplifyTree(root->right);
}

void traverseTree(Node* root, char* result) {
    if (!root) return;
    if (root->left) {
        traverseTree(root->left, result);
    }
    strcat(result, root->value);
    if (root->right) {
        traverseTree(root->right, result);
    }
}

void destroyTree(Node* root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

int main() {
    char expr[100];
    printf("Enter the expression: ");
    scanf("%99s", expr);

    Node* tree = buildExpressionTree(expr);
    simplifyTree(tree);

    char result[100] = { 0 };
    traverseTree(tree, result);

    printf("Simplified expression: %s\n", result);
    destroyTree(tree);

    return 0;
}
