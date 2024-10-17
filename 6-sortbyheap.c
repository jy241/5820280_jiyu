#include <stdio.h>
#include <stdlib.h>

// �� ������ ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ���� �������ϴ� �Լ�
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // ��Ʈ
    int left = 2 * i + 1; // ���� �ڽ�
    int right = 2 * i + 2; // ������ �ڽ�

    // ���� �ڽ��� ��Ʈ���� ũ�� largest�� ������Ʈ
    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;
    }

    // ������ �ڽ��� ���� largest���� ũ�� ������Ʈ
    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;
    }

    // largest�� ��Ʈ�� �ƴϸ� ��ȯ�ϰ� ��������� ���� ������
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// ���� �����ϴ� �Լ�
void BuildMaxHeap(int inputData[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// �迭 ���� ��� �Լ�
void printArray(int inputData[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
}

// �迭�� ��Ҹ� �����ϰ� �� ���¸� ����ϴ� �Լ�
void insertAndHeapify(int inputData[], int* size, int value) {
    // �迭 ũ�� ����
    inputData[*size] = value; // ���ο� ��� �߰�
    (*size)++;

    // ���� �籸��
    BuildMaxHeap(inputData, *size);

    // ���� �� ���� ���
    printArray(inputData, *size);
}

// ���ο� ��ҵ��� �迭�� �߰��ϸ� �� ���¸� ����ϴ� �Լ�
void insertElementsAndPrintHeap(int inputData[], int newElements[], int newSize, int* size) {
    for (int i = 0; i < newSize; i++) {
        insertAndHeapify(inputData, size, newElements[i]);

    }
}

// �� ���� �� ���� ��� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    BuildMaxHeap(inputData, n);


    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);
        resortHeap(inputData, i, 0);
        printArray(inputData, i); // ���� ���� ���� ���
    }
}

// ���� �Լ�
int main() {
    int inputData[100]; // �迭 ũ�� 100���� ����
    int size = 0;

    // �ʱ� ������ �߰�
    int initialData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int initialSize = sizeof(initialData) / sizeof(initialData[0]);

    // �ʱ� ������ ����
    insertElementsAndPrintHeap(inputData, initialData, initialSize, &size);

    // �� ���� ����
    BuildMaxHeapAndSort(inputData, size);

    // ���ĵ� ��� ���
    printf("\nSorted Array:\n");
    printArray(inputData, size); // ���� ���ĵ� �迭 ���

    return 0;
}
