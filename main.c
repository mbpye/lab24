#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void simplify_fraction(char* expr) {
    char* pos1, * pos2, * a, * b, * c;

    if ((pos1 = strchr(expr, '/')) && (pos2 = strchr(pos1 + 1, '/'))) {
        *pos1 = '\0';
        a = expr;
        b = pos1 + 1;
        c = pos2 + 1;
        printf("%s/(%s*%s)\n", a, b, c);
    }
    else if (pos1 && (pos2 = strchr(expr, '/'))) {
        *pos2 = '\0';
        a = expr;
        b = pos2 + 1;
        c = pos1 + 1;
        printf("(%s/%s)*%s\n", a, b, c);
    }
    else {
        printf("Expression format is incorrect.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    char expr[100];
    printf("¬ведите сложную дробь: ");
    scanf("%s", expr);
    simplify_fraction(expr);
    return 0;
}
