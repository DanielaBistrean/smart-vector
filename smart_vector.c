#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector
{
	int *data; // data[];
	size_t cap;
	size_t used;
};

typedef struct vector vector_t;

int
vector_create(vector_t *p_vec, size_t intial_size)
{
	int *p_new_data;

	if (intial_size == 0)
	{
		p_new_data = NULL;
	}
	else
	{
		int *p_new_data = (int *) malloc(intial_size * sizeof(int));
		if (p_new_data == NULL)
			return -1;
	}

	p_vec->data = p_new_data; 
	p_vec->cap = intial_size;
	p_vec->used = 0;

	return 0;
}

int
vector_push_back(vector_t *p_vec, int elem)
{
	if ((p_vec->cap == p_vec->used) || (p_vec->cap == 0))
	{
		size_t new_size = 2 * (p_vec->cap + 1);
		int *p_new_data = (int *) realloc(p_vec->data, new_size);
		if (p_new_data == NULL)
			return -1;
		p_vec->data = p_new_data;
		p_vec->cap = new_size;
	}
	
	p_vec->data[p_vec->used] = elem;
	p_vec->used++;

	return 0;
}

int
vector_print(const vector_t *p_vec)
{
	int i;

	// 	return 0;
	// if (p_vec->used == 0)
	if (p_vec->data == NULL)
		return -1;

	printf("[ ");
	for (i = 0; i < p_vec->used; i++)
	{
		printf("%d ", p_vec->data[i]);
	}
	printf("]\n");

	return 0;
}

int
vector_insert(vector_t *p_vec, int elem, size_t pos)
{
	size_t new_size = p_vec->cap;
	int *p_data = p_vec->data;

	if (pos > p_vec->used)
		return -1;

	if ((p_vec->used == p_vec->cap) || (p_data == NULL))
	{
		new_size = 2 * (p_vec->cap + 1);
		int *p_data = (int *) realloc(p_vec->data, new_size * sizeof(int));
		if (p_data == NULL)
			return -1;
	}

	memmove(p_data + pos + 1, p_data + pos, (p_vec->used - pos) * sizeof(int));
	
	p_vec->data = p_data;
	p_vec->data[pos] = elem;
	p_vec->used++;
	p_vec->cap = new_size;
}

int
main(int argc, char const *argv[])
{
	vector_t v;

	// vector_print(&v);

	vector_create(&v, 0);

	vector_print(&v);

	printf("data=%p\n", v.data);
	printf("cap=%lu\n", v.cap);
	printf("used=%lu\n", v.used);

	vector_push_back(&v, 3);
	vector_push_back(&v, 4);
	vector_push_back(&v, 5);
	vector_push_back(&v, 6);

	printf("data=%p\n", v.data);
	printf("cap=%lu\n", v.cap);
	printf("used=%lu\n", v.used);

	vector_print(&v);

	vector_insert(&v, 2, 1);
	vector_insert(&v, 20, 5);
	vector_insert(&v, 10, 1);
	vector_insert(&v, 90, 10);

	printf("data=%p\n", v.data);
	printf("cap=%lu\n", v.cap);
	printf("used=%lu\n", v.used);
	
	vector_print(&v);

	return 0;
}
