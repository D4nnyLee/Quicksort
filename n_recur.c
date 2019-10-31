#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int arr_partition(int a[], int low, int high) {//auxiliary function of quicksort
	int pivot = a[high];
	for(;;) {
		while (low < high && a[low] <= pivot)
			low++;
		if (low == high) break;
		a[high--] = a[low];
		while (low < high && a[high] >= pivot)
			high--;
		if (low == high) break;
		a[low++] = a[high];
	}
	a[low] = pivot;
	return low;
}

void arr_quicksort(int a[], int low, int high) {
	int pivot;
	if (low >= high) return;
	pivot = arr_partition(a, low, high);
	arr_quicksort(a, low, pivot - 1);
	arr_quicksort(a, pivot + 1, high);
}

void quicksort(int a[], int low, int high) {

}

int main() {
	int n;
	scanf("%i", &n);

	int *arr1 = malloc(n * sizeof(int)), *arr2 = malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		scanf("%i", &arr1[i]);
		arr2[i] = arr1[i];
	}
	for (int i = 0; i < n; ++i) printf("%i ", arr1[i]);
		printf("\n");
	long long int t0 = clock();

	quicksort(arr1, 0, n - 1);//array quicksort
	long long int t1 = clock();

	arr_quicksort(arr2, 0, n - 1);//array quicksort
	long long int t2 = clock();

	//for (int i = 0; i < n; ++i) printf("%i ", arr[i]);
	arr_quicksort(arr2, 0, n - 1);//array quicksort
	long long int t3 = clock();

	printf("time:%lf(ms)\n", (double)(t1 - t0) / (CLOCKS_PER_SEC / 1000));
	printf("time:%lf(ms)\n", (double)(t2 - t1) / (CLOCKS_PER_SEC / 1000));
	printf("time(worst case):%lf(ms)\n", (double)(t3 - t2) / (CLOCKS_PER_SEC / 1000));

	printf("times:%lf\n", (double)(t1-t0)/(t2-t1));
	return 0;
}