#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct s_node {
	struct s_node *prev;
	struct s_node *next;
	int value;
};

typedef struct s_node node;

void connect(node *a, node *b) {
	if (a)
		a->next = b;
	if (b)
		b->prev = a;
}

void print_node(node *out) {
	if (!out) {
		puts("NULL");
		return;
	}
	while (out) {
		printf("%d ", out->value);
		if (out->next)
			out = out->next;
		else
			break;
	}
	putchar(10);
}

node *quickSort(node *elements) {
	if (elements == NULL || elements->next == NULL)
		return elements;
	// create header nodes for left and right part
	node *left = calloc(1, sizeof(node)), *right = calloc(1, sizeof(node));
	// iterator
	node *iteratorL = left, *iteratorR = right;
	// take the first element for pivot
	node *pivot = elements;
	// split
	for (elements = elements->next; elements; elements = elements->next) {
		if (elements->value <= pivot->value) {
			connect(iteratorL, elements);
			iteratorL = iteratorL->next;
		}
		else {
			connect(iteratorR, elements);
			iteratorR = iteratorR->next;
		}
	}
	iteratorL->next = iteratorR->next = NULL;
	left->next = quickSort(left->next);
	right->next = quickSort(right->next);
	for (iteratorL = left; iteratorL->next; iteratorL = iteratorL->next);
	connect(iteratorL, pivot);
	connect(pivot, right->next);
	return left->next;
}

int main(int argc, char const *argv[]) {
	node *header = calloc(1, sizeof(node)), *tmp = header;
	int length;
	scanf("%d", &length);
	for (int i = 0; i < length; i++) {
		connect(tmp, calloc(1, sizeof(node)));
		tmp = tmp->next;
		scanf("%d", &tmp->value);
	}
    long long int before = clock();
	header->next = quickSort(header->next);
    long long int after = clock();
    printf("time: %lf (ms)\n", (double)(after - before) / (CLOCKS_PER_SEC / 1000));
    before = clock();
	header->next = quickSort(header->next);
    after = clock();
    printf("time: %lf (ms)\n", (double)(after - before) / (CLOCKS_PER_SEC / 1000));
	return 0;
}
