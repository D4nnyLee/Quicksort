#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//#define Debug

//array quicksort
int arr_n1 = 0, arr_n2 = 0, arr_n3 = 0;
int arr_partition(int a[], int low, int high) {//auxiliary function of arr_quicksort
	int pivot = a[low];
	for(;;) {
		while (low < high && a[high] >= pivot)
			high--;
		if (low == high) break;
		a[low++] = a[high];
#ifdef Debug
++arr_n3;
#endif
		while (low < high && a[low] <= pivot)
			low++;
		if (low == high) break;
		a[high--] = a[low];
#ifdef Debug
++arr_n3;
#endif
	}
	a[high] = pivot;
#ifdef Debug
++arr_n3;
#endif
	return low;
}

void arr_quicksort(int a[], int low, int high) {
	if (low >= high) return;
#ifdef Debug
++arr_n1;
arr_n2 += high - low + 1;
#endif
	int pivot;
	pivot = arr_partition(a, low, high);
	arr_quicksort(a, low, pivot - 1);
	arr_quicksort(a, pivot + 1, high);
}

void print_arr(int a[], int n) {
	printf("arr:\n");
	for (int i = 0; i < n; ++i)
		printf("%i ", a[i]);
	printf("\n");
}
//

//sll quicksort
int sll_n1 = 0, sll_n2 = 0, sll_n3 = 0;
typedef struct s{
	int value;
	struct s *next;
} node;

node *create_sll(int n) {//scan n numbers
	node *ret = malloc(sizeof(node));
	scanf("%i", &(ret -> value));

	node *tmp = ret;
	for (int i = 1; i < n; ++i) {
		tmp -> next = malloc(sizeof(node));
		tmp = tmp -> next;
		scanf("%i", &(tmp -> value));
	}

	tmp -> next = 0;
	return ret;
}

void print_sll(node *header) {
	for (header = header -> next; header; header = header -> next)
		printf("%i ", header -> value);
	printf("\n");
}

node *r_quicksort(node *sll) {
	if (!sll) return 0;//none
	else if (!sll -> next) return sll;//only one
#ifdef Debug
++sll_n1;
for (node *tmp = sll; tmp; tmp = tmp -> next) ++sll_n2;
#endif
	node *left = 0, *right = 0;
	node *tmp = sll, *tmp_left, *tmp_right;
	for (tmp = tmp -> next; tmp; tmp = tmp -> next) {//separate to two linked list
		if (tmp -> value <= sll -> value)
			if (left) {
				tmp_left -> next = tmp;
				tmp_left = tmp_left -> next;
			} else left = tmp_left = tmp;//first of left
		else
			if (right) {
				tmp_right -> next = tmp;
				tmp_right = tmp_right -> next;
			} else right = tmp_right = tmp;//first of right
#ifdef Debug
++sll_n3;
#endif
	}
	if (left) tmp_left -> next = 0;//end
	if (right) tmp_right -> next = 0;

	node *ret = r_quicksort(left);//return first node
	for (tmp = ret; tmp && tmp -> next; tmp = tmp -> next) ;
	if (tmp) tmp -> next = sll;//join left end and pivot
	else ret = sll;//left is empty
#ifdef Debug
++sll_n3;
#endif

	sll -> next = r_quicksort(right);//join pivot and right front
#ifdef Debug
++sll_n3;
#endif

	return ret;
}

void quicksort(node *header) {//deal with header node
	header -> next = r_quicksort(header -> next);
}
//

int main() {
	int n;
	scanf("%i", &n);//number of data

	node *s = malloc(sizeof(node));
	s -> next = create_sll(n);//read n numbers

	int *arr;
	arr = malloc(n * sizeof(int));
	node *cpy = s -> next;
	for(int i = 0; cpy; cpy = cpy -> next, ++i)//copy data to array
		arr[i] = cpy -> value;
	
	long long int t0 = clock();
	quicksort(s);//sll quicksort by swapping
	long long int t1 = clock();
	//print_sll(s);//for checking the result after sll quicksort

	long long int t2 = clock();
	arr_quicksort(arr, 0, n - 1);//array quicksort
	long long int t3 = clock();
	//print_arr(arr, n);//for checking the result after array quicksort

#ifndef Debug
	printf("rejoining_sll quicksort : %lf(ms)\n", (double)(t1 - t0) / (CLOCKS_PER_SEC / 1000));//time of sll quicksort
	printf("array quicksort in the same manner : %lf(ms)\n", (double)(t3 - t2) / (CLOCKS_PER_SEC / 1000));//time of array quicksort
	printf("sll/arr(times) : %lf\n", (double)(t1-t0) / (t3-t2));
#else
	printf("number of quicksort call: %i(sll), %i(array)\n", sll_n1, arr_n1);
	printf("sum of length of each call: %i(sll), %i(array)\n", sll_n2, arr_n2);
	printf("times of rejoin / times of arr-assignment: %i, %i\n", sll_n3, arr_n3);
#endif

	return 0;
}
