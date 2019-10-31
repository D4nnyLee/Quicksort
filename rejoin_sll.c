#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int arr_partition(int a[], int low, int high) {//auxiliary function of arr_quicksort
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
	}

	if (left) tmp_left -> next = 0;//end
	if (right) tmp_right -> next = 0;

	node *ret = r_quicksort(left);//return first node
	for (tmp = ret; tmp && tmp -> next; tmp = tmp -> next) ;
	if (tmp) tmp -> next = sll;//join left end and pivot
	else ret = sll;//left is empty

	sll -> next = r_quicksort(right);//join pivot and right front

	return ret;
}

void quicksort(node *header) {//deal with header node
	header -> next = r_quicksort(header -> next);
}

int main() {
	int n;
	scanf("%i", &n);//number of data

	node *s = malloc(sizeof(node));
	s -> next = create_sll(n);//input n numbers

	int *arr;//copy data to array
	arr = malloc(n * sizeof(int));
	node *cpy = s -> next;
	for(int i = 0; cpy; cpy = cpy -> next, ++i)
		arr[i] = cpy -> value;

	
	long long int t0 = clock();
	quicksort(s);//sll quicksort by rejoining
	long long int t1 = clock();

	printf("sll:\n");
	print_sll(s);

	long long int t2 = clock();
	arr_quicksort(arr, 0, n - 1);//array quicksort
	long long int t3 = clock();

	//for (int i = 0; i < n; ++i) printf("%i ", arr[i]);

	long long int t4 = clock();
	arr_quicksort(arr, 0, n - 1);//array quicksort(worst case)
	long long int t5 = clock();

	printf("time:%lf(ms)\n", (double)(t1 - t0) / (CLOCKS_PER_SEC / 1000));//time of sll quicksort
	printf("time:%lf(ms)\n", (double)(t3 - t2) / (CLOCKS_PER_SEC / 1000));//time of array quicksort
	printf("time(worst case):%lf(ms)\n", (double)(t5 - t4) / (CLOCKS_PER_SEC / 1000));//worst case of quicksort
	printf("times:%lf\n", (double)(t1-t0)/(t3-t2));

	return 0;
}
