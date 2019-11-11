#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//#define DebugXOR

//array quicksort
void arr_swap(int *a, int *b) {
	int tmp = *b;
	*b = *a;
	*a = tmp;
}

int arr_partition(int a[], int low, int high) {//auxiliary function of arr_quicksort
	int i = low;
	for (int j = low + 1; j <= high; ++j)
		if (a[j] < a[low]) {
			++i;
			arr_swap(a + i, a + j);
		}
	arr_swap(a + low, a + i);
	return i;
}

void arr_quicksort(int a[], int low, int high) {
	int pivot;
	if (low >= high) return;
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
	printf("sll:\n");
	for (header = header -> next; header; header = header -> next)
		printf("%i ", header -> value);
	printf("\n");
}

void swap(node *i, node *j) {//swap values in two nodes
#ifdef DebugXOR
	i -> value ^= j -> value;
	j -> value ^= i -> value;
	i -> value ^= j -> value;
#else
	int tmp = i -> value;
	i -> value = j -> value;
	j -> value = tmp;
#endif
}

void partition(node *front, node *rear, node **nr_ptr, node **nf_ptr) {
	node *i = front, *j = front -> next;
	for(; j; j = j -> next)//put smaller one to the front
		if (j -> value < front -> value) {
			*nr_ptr = i;
			i = i -> next;
#ifdef DebugXOR
printf("%i, %i\n", i -> value, j -> value);
#endif
			swap(i, j);
#ifdef DebugXOR
printf("%i, %i\n", i -> value, j -> value);
sleep(1);
#endif
		}
#ifdef DebugXOR
printf("%i, %i\n", front -> value, i -> value);
#endif
	swap(front, i);//swap pivot to the end of smaller data
#ifdef DebugXOR
printf("%i, %i\n", front -> value, i -> value);
sleep(1);
#endif
	if(i != rear) *nf_ptr = i -> next;
}

void r_quicksort(node *front, node *rear) {
	if (front == rear) return ;//only one node left

	node *next_rear = 0, *next_front = 0;
	node **nr_ptr = &next_rear, **nf_ptr = &next_front;
	partition(front, rear, nr_ptr, nf_ptr);

	if (next_rear) r_quicksort(front, next_rear);
	if (next_front) r_quicksort(next_front, rear);
}

void quicksort(node *header) {//deal with header node
	if (!header || !header -> next) return ;
	node *front = header -> next, *rear = header -> next;
	for(; rear -> next; rear = rear -> next) ;
	r_quicksort(front, rear);
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
	for(int i = 0; cpy; cpy = cpy -> next, ++i)//copy to array
		arr[i] = cpy -> value;

	long long int t0 = clock();
	quicksort(s);//sll quicksort by swapping
	long long int t1 = clock();
	//print_sll(s);//for checking the result after sll quicksort

	long long int t2 = clock();
	arr_quicksort(arr, 0, n - 1);//array quicksort
	long long int t3 = clock();
	//print_arr(arr, n);//for checking the result after array quicksort

#ifndef DebugXOR
	printf("swapping_sll quicksort : %lf(ms)\n", (double)(t1 - t0) / (CLOCKS_PER_SEC / 1000));//time of sll quicksort
	printf("array quicksort in the same manner : %lf(ms)\n", (double)(t3 - t2) / (CLOCKS_PER_SEC / 1000));//time of array quicksort
	printf("sll/arr(times) : %lf\n", (double)(t1-t0) / (t3-t2));
#else
	print_sll(s);
#endif

	return 0;
}
