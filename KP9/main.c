#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char text[100];
} Record;

void ShellSort(Record arr[], int n)
{
    int j;
    Record tmp;
    for (int step = n / 2; step > 0; step /= 2)
        for (int i = step; i < n; i++)
        {
            tmp = arr[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp.key < arr[j - step].key)
                    arr[j] = arr[j - step];
                else
                    break;
            }
            arr[j] = tmp;
        }
}

int binarySearch(Record arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m].key == x) {
            return m;
        }
        if (arr[m].key < x) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    return -1;
}

void printArray(Record arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d: %s\n", arr[i].key, arr[i].text);
    printf("\n");
}

int main() {
    Record records[100];
    int n = 0;
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (fscanf(file, "%d,%[^\n]", &records[n].key, records[n].text) != EOF) {
        n++;
    }
    fclose(file);

    printf("Original array:\n");
    printArray(records, n);

    ShellSort(records, n);
    printf("Sorted array:\n");
    printArray(records, n);

    int key;
    printf("Enter key to search: ");
    scanf("%d", &key);
    int result = binarySearch(records, 0, n - 1, key);
    if (result != -1) {
        printf("Found: %d: %s\n", records[result].key, records[result].text);
    }
    else {
        printf("Key not found!\n");
    }

    return 0;
}
