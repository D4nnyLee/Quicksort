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

//for debug
node *header;
int find_pos(node *n) {
	node *tmp = header;
	int i;
	for (i = 0; tmp;) {
		tmp = tmp -> next;
		++i;
		if (n == tmp) break;
	}
	if(tmp) return i;
	else return 0;
}
//

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

void swap(node *i, node *j) {//swap values in two nodes
	int tmp = i -> value;
	i -> value = j -> value;
	j -> value = tmp;
	/*i -> value ^= j -> value;
	j -> value ^= i -> value;
	i -> value ^= j -> value;*/
}

void partition(node *front, node *rear, node **nr_ptr, node **nf_ptr) {
	node *i = front, *j = front -> next;
	for(; j; j = j -> next)//put smaller one to the front
		if (j -> value < front -> value) {
			*nr_ptr = i;
			i = i -> next;
			swap(i, j);
		}
	swap(front, i);//swap pivot to the end of smaller data
	if(i != rear) *nf_ptr = i -> next;
}

void r_quicksort(node *front, node *rear) {
	//printf("pos:%i %i\n", find_pos(front), find_pos(rear));
	//sleep(1);
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

	header = s;

	long long int t0 = clock();
	quicksort(s);//sll quicksort by swapping
	long long int t1 = clock();

	printf("sll:\n");
	print_sll(s);

	long long int t2 = clock();
	arr_quicksort(arr, 0, n - 1);//array quicksort
	long long int t3 = clock();

	//for (int i = 0; i < n; ++i) printf("%i ", arr[i]);

	long long int t4 = clock();
	arr_quicksort(arr, 0, n - 1);//array quicksort
	long long int t5 = clock();

	printf("time:%lf(ms)\n", (double)(t1 - t0) / (CLOCKS_PER_SEC / 1000));//time of sll quicksort
	printf("time:%lf(ms)\n", (double)(t3 - t2) / (CLOCKS_PER_SEC / 1000));//time of array quicksort
	printf("time(worst case):%lf(ms)\n", (double)(t5 - t4) / (CLOCKS_PER_SEC / 1000));//worst case of quicksort
	printf("times:%lf\n", (double)(t1-t0)/(t3-t2));

	return 0;
}
