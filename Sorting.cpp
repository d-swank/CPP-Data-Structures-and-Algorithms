#include <iostream>
using namespace std;

void enteredNum(int arr[], int len) {

	int i = 0;
	cout << "\nArray before sorting: \n";
	for (i = 0; i < len; i++)
		cout << arr[i] << " ";	
}

void display(int A[], int len) {

	for (int i = 0; i < len; i++)
		cout << A[i] << " ";
}

void swap(int *a, int *b) {

	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSort(int A[], int len) {

	int i, j, smallestNum;

	for (i = 0; i < len - 1; i++) {
		smallestNum = i;

		for (j = i + 1; j < len; j++) {

			if (A[smallestNum] > A[j])
				smallestNum = j;
		}

		swap(A[i], A[smallestNum]);
	}
}

void bubbleSort(int A[], int len) {

	int i, j;

	for (i = 0; i < (len - 1); i++) {

		for (j = 0; j < (len - i - 1); j++) {

			if (A[j] > A[j + 1])
				swap(A[j], A[j + 1]);
		}
	}
}

void insertionSort(int A[], int len) {

	int i, j, k;

	for (i = 1; i < len; i++) {
		k = A[i];
		j = i - 1;

		while (j >= 0 && A[j] > k) {
			A[j + 1] = A[j];
			j -= 1;
		}

		A[j + 1] = k;
	}
}

int partiton(int A[], int p, int r) {

	int pivot = A[p];
	int i, q;
	q = i = (p + 1);

	while (i <= r) {
		
		if (A[i] <= pivot) {
			q++;
			swap(&A[q - 1], &A[i]);
		}
		
		i++;
	}
	
	swap(&A[q - 1], &A[p]);
	return q - 1;
}

void quickSort(int A[], int p, int r) {

	if (p >= r)
		return;

	int q = partiton(A, p, r);
	quickSort(A, p, q - 1);
	quickSort(A, q + 1, r);
}

void merge(int A[], int p, int q, int r) {

	int sub1 = q - p + 1;
	int sub2 = r - q;

	int *leftArray = new int[sub1];
	int *rightArray = new int[sub2];

	for (int i = 0; i < sub1; i++)
		leftArray[i] = A[p + i];

	for (int j = 0; j < sub2; j++)
		rightArray[j] = A[(q + 1) + j];

	int i = 0;
	int j = 0;
	int k = p;

	while (i < sub1 && j < sub2) {

		if (leftArray[i] <= rightArray[j]) {
			A[k++] = leftArray[i++];
		}

		else {
			A[k++] = rightArray[j++];
		}
	}

	while (i < sub1) {
		A[k++] = leftArray[i++];
	}

	while (j < sub2) {
		A[k++] = rightArray[j++];
	}
}

void mergeSort(int A[], int p, int r) {
	
	if (p >= r)
		return;

	int q = (p + r) / 2;
	mergeSort(A, p, q);
	mergeSort(A, q + 1, r);
	merge(A, p, q, r);
}

class MaxHeap {

	int* arr;
	int capacity;
	int size;
	class Underflow{};
	class Overflow{};

public:

	MaxHeap(int cap) {
		size = 0; capacity = cap;
		arr = new int[capacity];
	}

	int parent(int i) {
		return (i - 1) / 2;
	}

	int left(int i) {
		return (2 * i + 1);
	}

	int right(int i) {
		return (2 * i + 2);
	}

	int getSize() {
		return size;
	}

	bool isLeaf(int i) {
		return (i < size / 2) ? false : true;
	}

	int getMax() {
		return arr[0];
	}

	void siftUp(int i) {

		while (i > 0 && arr[parent(i)] > arr[i]){

			swap(&arr[i], &arr[parent(i)]);
			i = parent(i);
		}
	}

	void siftDown(int i) {

		while (!isLeaf(i)) {

			int l = left(i);
			int r = right(i);
			int larger = l;

			if (r < size)
				larger = (arr[l] > arr[r]) ? l : r;

			if (arr[i] >= arr[larger])
				break;

			swap(&arr[i], &arr[larger]);
			i = larger;
		}
	}

	void insert(int k) {
		
		if (size >= capacity)
			throw Overflow();

		int i = size;
		arr[i] = k;
		siftUp(i);
		size++;
	}

	int removeAt(int i) {
		
		if (i < 0 || size <= i) 
			throw Underflow();
		
		if (size == 1) 
			return arr[--size];
		
		int result = arr[i];
		arr[i] = arr[--size];
		
		if (arr[i] > result) 
			siftDown(i);
		
		else 
			siftUp(i);
		
		return result;
	}

	int extractMax() {
		if (size <= 0) 
			throw Underflow();
		
		if (size == 1) 
			return arr[--size];
		
		int result = arr[0];
		arr[0] = arr[--size];
		siftDown(0);

		return result;
	}

	void heapify(int* array, int len) {

		arr = array;
		capacity = size = len;

		int half = size / 2 - 1;

		for (int i = half; i >= 0; i--)
			siftDown(i);
	}
};

void heapSort(int A[], int len) {

	MaxHeap heap(len);
	heap.heapify(A, len);
	int i = len - 1;
	int count = 1;

	while (heap.getSize() > 0)
		A[i--] = heap.extractMax();
}

int main() {

	int input[100] = {};
	int num = 0, i = 0;
	int len = sizeof(input) / sizeof(input[0]);

	while (num >= 1 || num <= 6) {

		cout << "\n\n" << string(70, '*');
		cout << "\nChoose one of the following sorting algorithms:\n\n1) Selection Sort\t"
			"4) Quick Sort\n2) Bubble Sort\t\t5) Merge Sort\n3) Insertion Sort\t6) Heap Sort\n";
		cout << "\n" << string(70, '*') << "\n";
		cin >> num;

		if (num == 1) {
			cout << "\nYou chose Selection Sort!\n"
				"\nEnter how many integers you want to sort:\n";
			cin >> len;
			cout << "\nPlease enter " << len << " integers for the array:\n";
			for (i = 0; i < len; i++) {
				cin >> input[i];
			}

			enteredNum(input, len);
			selectionSort(input, len);
			cout << "\n\nArray after selection sort:\n";
			display(input, len);
		}

		else if (num == 2) {
			cout << "\nYou chose Bubble Sort!\n"
				"\nEnter how many integers you want to sort:\n";
			cin >> len;
			cout << "\nPlease enter " << len << " integers for the array:\n";

			for (int i = 0; i < len; i++) {
				cin >> input[i];
			}

			enteredNum(input, len);
			bubbleSort(input, len);
			cout << "\n\nArray after bubble sort:\n";
			display(input, len);
		}

		else if (num == 3) {
			cout << "\nYou chose Insertion Sort!\n"
				"\nEnter how many integers you want to sort:\n";
			cin >> len;
			cout << "\nPlease enter " << len << " integers for the array:\n";

			for (int i = 0; i < len; i++) {
				cin >> input[i];
			}

			enteredNum(input, len);
			insertionSort(input, len);
			cout << "\n\nArray after insertion sort:\n";
			display(input, len);
		}

		else if (num == 4) {
			cout << "\nYou chose Quick Sort!\n"
				"\nEnter how many integers you want to sort:\n";
			cin >> len;
			cout << "\nPlease enter " << len << " integers for the array:\n";

			for (int i = 0; i < len; i++) {
				cin >> input[i];
			}

			enteredNum(input, len);
			quickSort(input, 0, len - 1);
			cout << "\n\nArray after quick sort:\n";
			display(input, len);
		}

		else if (num == 5) {
			cout << "\nYou chose Merge Sort!\n"
				"\nEnter how many integers you want to sort:\n";
			cin >> len;
			cout << "\nPlease enter " << len << " integers for the array:\n";

			for (int i = 0; i < len; i++) {
				cin >> input[i];
			}

			enteredNum(input, len);
			mergeSort(input, 0, len - 1);
			cout << "\n\nArray after merge sort:\n";
			display(input, len);
		}

		else if (num == 6) {
			cout << "\nYou chose Heap Sort!\n"
				"\nEnter how many integers you want to sort:\n";
			cin >> len;
			cout << "\nPlease enter " << len << " integers for the array:\n";

			for (int i = 0; i < len; i++) {
				cin >> input[i];
			}

			enteredNum(input, len);
			heapSort(input, len);
			cout << "\n\nArray after heap sort:\n";
			display(input, len);
		}

		else {
			cout << "\nERROR! Incorrect number. Please input a number between 1 and 6.\n";
		}
	}
	return 0;
}
