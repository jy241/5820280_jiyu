#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

// �Լ� ����: ���� �迭 ���� �Լ�
void generateRandomArray(int* array);
// �Լ� ����: �� ���� �Լ�
void QuickSort(int* array, int low, int high);
// �Լ� ����: �迭�� ������ ������ �Լ� (�����Ŀ� ���)
int Partition(int* array, int low, int high);
// �Լ� ����: �迭 ��� �Լ�
void printArray(int* array);
// �Լ� ����: ���� Ž���� ���� ��� �� Ƚ�� ���ϴ� �Լ�
float getAverageBinarySearchCompareCount(int* array);
// �Լ� ����: ���� Ž���� ���� ��� �� Ƚ�� ���ϴ� �Լ�
float getAverageInterpolationSearchCompareCount(int* array);
// �Լ� ����: ���� Ž��
int BinarySearch(int* array, int target);
// �Լ� ����: ���� Ž��
int InterpolationSearch(int* array, int target);

int main(int argc, char* argv[]) {
    // 3�� �ݺ��Ͽ� ���
    for (int i = 0; i < 3; i++) {
        // �� �ݺ����� �ٸ� �õ尪�� ����Ͽ� ���� ����
        srand(time(NULL) + i);
        int array[SIZE];

        // �迭 ���� �� ������ ����
        generateRandomArray(array);
        QuickSort(array, 0, SIZE - 1);

        // �迭 ���
        printArray(array);

        // ���� Ž���� ���� Ž�� ��� �� Ƚ�� ���
        printf("Average Compare Count of Binary Search: %.2f\n",
            getAverageBinarySearchCompareCount(array));
        printf("Average Compare Count of Interpolation Search: %.2f\n",
            getAverageInterpolationSearchCompareCount(array));
        printf("\n");
    }
    return 0;
}

// �迭�� 0���� SIZE-1 ������ ������ �����ϴ� �Լ�
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % SIZE;  // SIZE ���� ������ ���� ����
    }
}

// �� ���� �Լ� (�迭�� ����)
void QuickSort(int* array, int low, int high) {
    if (low < high) {
        // �迭�� ��Ƽ������ ������, ���ҵ� �迭�� ���� ��������� �� ���� ����
        int pivotIndex = Partition(array, low, high);
        QuickSort(array, low, pivotIndex - 1);
        QuickSort(array, pivotIndex + 1, high);
    }
}

// �迭�� ������ ��Ƽ�� �Լ� (�������� �߿��� �κ�)
int Partition(int* array, int low, int high) {
    int pivot = array[high];  // ������ ��Ҹ� �ǹ����� ����
    int i = low - 1;  // �ǹ����� ���� ���� ���� ��ġ

    // low���� high-1������ ���� ���������� Ȯ���ϸ� �ǹ����� ���� ���� �������� ������
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            // �� ����
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // �ǹ��� ���ĵ� ��ġ�� ���� ���� ����
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;  // �ǹ��� ���� ��ġ ��ȯ
}

// �迭�� ó�� 20���� �� 20���� ���� ����ϴ� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]);  // ó�� 20�� �� ���
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]);  // �� 20�� �� ���
    }
    printf("\n\n");
}

// ���� Ž���� 1000�� �����ϰ� ��� �� Ƚ���� ���ϴ� �Լ�
float getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;  // �� Ƚ���� ��
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];  // �迭���� ������ ���� target���� ����
        totalComparisons += BinarySearch(array, target);  // ���� Ž�� ����
    }
    return totalComparisons / 1000.0;  // ��� �� Ƚ�� ��ȯ
}

// ���� Ž�� �Լ�
int BinarySearch(int* array, int target) {
    int left = 0, right = SIZE - 1, comparisons = 0;  // �ʱ�ȭ
    while (left <= right) {
        comparisons++;  // �� Ƚ�� ����
        int mid = (left + right) / 2;
        if (array[mid] == target) {
            return comparisons;  // �� ã���� �� Ƚ�� ��ȯ
        }
        else if (array[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return comparisons;  // ã�� ���ϸ� �� Ƚ�� ��ȯ
}

// ���� Ž���� 1000�� �����ϰ� ��� �� Ƚ���� ���ϴ� �Լ�
float getAverageInterpolationSearchCompareCount(int* array) {
    int totalComparisons = 0;  // �� Ƚ���� ��
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];  // �迭���� ������ ���� target���� ����
        totalComparisons += InterpolationSearch(array, target);  // ���� Ž�� ����
    }
    return totalComparisons / 1000.0;  // ��� �� Ƚ�� ��ȯ
}

// ���� Ž�� �Լ�
int InterpolationSearch(int* array, int target) {
    int low = 0, high = SIZE - 1, comparisons = 0;  // �ʱ�ȭ
    while (low <= high && target >= array[low] && target <= array[high]) {
        comparisons++;  // �� Ƚ�� ����
        if (low == high) {
            if (array[low] == target) return comparisons;  // �� ã���� �� Ƚ�� ��ȯ
            break;
        }
        // �������� ����Ͽ� ���ο� �˻� ��ġ ���
        int pos = low + ((double)(high - low) / (array[high] - array[low]) * (target - array[low]));
        if (array[pos] == target) {
            return comparisons;  // �� ã���� �� Ƚ�� ��ȯ
        }
        else if (array[pos] < target) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return comparisons;  // ã�� ���ϸ� �� Ƚ�� ��ȯ
}
