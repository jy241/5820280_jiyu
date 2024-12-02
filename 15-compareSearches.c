#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000  // �迭 ũ�� ����

int compareCount = 0;  // �� Ƚ���� ������ ���� ����

// ������ ���ڷ� �迭�� �ʱ�ȭ�ϴ� �Լ�
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0���� 999 ������ ���� ���� ����
    }
}

// ���� Ž�� �Լ�
int linearSearch(int* array, int target) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        count++;
        if (array[i] == target) {
            return count;  // ã���� �� Ƚ�� ��ȯ
        }
    }
    return count;  // ã�� ���ϸ� �� Ƚ�� ��ȯ
}

// ��� ���� Ž�� �� Ƚ���� ����ϴ� �Լ�
double getAverageLinearSearchCompareCount(int* array) {
    double totalCount = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // ���� Ÿ�� ����
        totalCount += linearSearch(array, target);  // ���� Ž�� ����
    }
    return totalCount / 100;  // ��� �� Ƚ�� ��ȯ
}

// �� ���� �Լ�
void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivot = array[high];  // �ǹ� ����
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            compareCount++;  // �� Ƚ�� ����
            if (array[j] < pivot) {
                i++;
                // ����
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        // �ǹ��� ����
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;
        // ���� ����
        quickSort(array, low, i);
        quickSort(array, i + 2, high);
    }
}

// �� ������ ȣ���ϰ� �� Ƚ���� �ʱ�ȭ�ϴ� �Լ�
void getQuickSortCompareCount(int* array) {
    compareCount = 0;  // �� Ƚ�� �ʱ�ȭ
    quickSort(array, 0, SIZE - 1);  // �� ���� ����
}

// ���� Ž�� �Լ�
int binarySearch(int* array, int low, int high, int target) {
    int count = 0;
    while (low <= high) {
        count++;
        int mid = low + (high - low) / 2;  // �߰� �ε��� ���
        if (array[mid] == target) {
            return count;  // ã���� �� Ƚ�� ��ȯ
        }
        if (array[mid] < target) {
            low = mid + 1;  // ������ Ž��
        }
        else {
            high = mid - 1;  // ���� Ž��
        }
    }
    return count;  // ã�� ���ϸ� �� Ƚ�� ��ȯ
}

// ��� ���� Ž�� �� Ƚ���� ����ϴ� �Լ�
double getAverageBinarySearchCompareCount(int* array) {
    double totalCount = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE];  // ���� Ÿ�� ����
        totalCount += binarySearch(array, 0, SIZE - 1, target);  // ���� Ž�� ����
    }
    return totalCount / 100;  // ��� �� Ƚ�� ��ȯ
}

// �迭�� ó�� 20���� ������ 20�� ��Ҹ� ����ϴ� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);  // ó�� 20�� ��� ���
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);  // ������ 20�� ��� ���
    printf("\n");
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    srand(time(NULL));  // ���� �õ� �ʱ�ȭ

    // 3ȸ �ݺ��Ͽ� ���� ����
    for (int run = 0; run < 3; run++) {
        int array[SIZE];  // �迭 ����
        generateRandomArray(array);  // �迭 �ʱ�ȭ

        // ��հ��� ��ȯ�ޱ� ���� ��ġ
        printf("Run %d:\n", run + 1);
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // �迭�� �����ϰ� �� Ƚ�� ���
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // ���ĵ� �迭�� ���� ���� Ž�� ��� �� Ƚ�� ���
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        printArray(array);  // �迭 ���
    }

    return 0;  // ���α׷� ����
}
