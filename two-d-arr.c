#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  two_d_allloc allocates memory for a 2d array
char *two_d_alloc(size_t N, size_t M, size_t sz)
{
    char *buf = (char *)malloc(N * M * sz);
    return buf;
}
// two_d_dealloc frees memory for a 2d array
void two_d_dealloc(char *array)
{
    free(array);
}
// two_d_store_int stores an integer in a 2d array
int two_d_store_int(int arg, char *array, size_t i, size_t j, size_t M, size_t N)
{
    if (array == NULL)
    {
        return -1;
    }
    if (i >= N || j >= M)
    {
        return -1;
    }
    int *ptr = (int *)array;
    ptr[i * M + j] = arg;
    return 0;
}
// two_d_fetch_int fetches an integer from a 2d array
int two_d_fetch_int(char *array, size_t i, size_t j, size_t M, size_t N)
{
    if (array == NULL)
    {
        printf("Error: array is NULL");
        return -1;
    }
    if (i >= N || j >= M)
    {
        printf("Error: index out of bounds");
        return -1;
    }
    int *ptr = (int *)array;
    return ptr[i * M + j];
}
// two_d_store stores a value of any type in a 2d array
int two_d_store(void *arg, char *array, size_t i, size_t j, size_t M, size_t N, size_t sz)
{
    if (array == NULL)
    {
        return -1;
    }
    if (i >= N || j >= M)
    {
        return -1;
    }
    char *ptr = (char *)array;
    memcpy(ptr + (i * M + j) * sz, arg, sz);
    return 0;
}
// two_d_fetch fetches a value of any type from a 2d array
void *two_d_fetch(char *array, size_t i, size_t j, size_t M, size_t N, size_t sz)
{
    if (array == NULL)
    {
        printf("Error: array is NULL");
        return NULL;
    }
    if (i >= N || j >= M)
    {
        printf("Error: index out of bounds");
        return NULL;
    }
    char *ptr = (char *)array;
    return ptr + (i * M + j) * sz;
}
// definition for a node
typedef struct Node
{
    int payload;
    struct Node *next;
} node;
// print_array prints out the contents of a 2d array in a hexdump format
void print_array(char *array, size_t M, size_t N, size_t sz)
{
    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < M; j++)
        {
            printf("%p\t", array + i * M * sz);
            for (int k = 0; k < sz; k++)
            {
                printf("%02x ", *(unsigned char *)(array + (i * M + j) * sz + k));
            }
            printf("\n");
        }
    }
}

int main()
{
    // test 2d array of ints

    char *array = two_d_alloc(3, 3, sizeof(int));
    two_d_store_int(1, array, 0, 0, 3, 3);
    two_d_store_int(2, array, 0, 1, 3, 3);
    two_d_store_int(3, array, 0, 2, 3, 3);
    two_d_store_int(4, array, 1, 0, 3, 3);
    printf("%d\n", two_d_fetch_int(array, 0, 0, 3, 3));
    printf("%d\n", two_d_fetch_int(array, 0, 1, 3, 3));
    printf("%d\n", two_d_fetch_int(array, 0, 2, 3, 3));
    printf("%d\n", two_d_fetch_int(array, 1, 0, 3, 3));

    // test for boundary conditions

    printf("%d\n", two_d_fetch_int(array, 3, 0, 3, 3));
    printf("%d\n", two_d_fetch_int(array, 0, 3, 3, 3));
    two_d_dealloc(array);

    // test 2d array of floats

    array = two_d_alloc(3, 3, sizeof(float));
    float f = 1.14;
    two_d_store(&f, array, 0, 0, 3, 3, sizeof(float));
    f = 2.28;
    two_d_store(&f, array, 0, 1, 3, 3, sizeof(float));
    f = 3.39;
    two_d_store(&f, array, 0, 2, 3, 3, sizeof(float));
    f = 4.56;
    two_d_store(&f, array, 1, 0, 3, 3, sizeof(float));
    printf("%f\n", *(float *)two_d_fetch(array, 0, 0, 3, 3, sizeof(float)));
    printf("%f\n", *(float *)two_d_fetch(array, 0, 1, 3, 3, sizeof(float)));
    printf("%f\n", *(float *)two_d_fetch(array, 0, 2, 3, 3, sizeof(float)));
    printf("%f\n", *(float *)two_d_fetch(array, 1, 0, 3, 3, sizeof(float)));
    two_d_dealloc(array);

    // test 2d array of type node

    array = two_d_alloc(3, 3, sizeof(node));
    node *n1 = (node *)malloc(sizeof(node));
    n1->payload = 1;
    n1->next = NULL;
    two_d_store(n1, array, 0, 0, 3, 3, sizeof(node));
    node *n = (node *)malloc(sizeof(node));
    n->payload = 2;
    n->next = n1;
    two_d_store(n, array, 0, 1, 3, 3, sizeof(node));
    print_array(array, 3, 3, sizeof(node));
    two_d_dealloc(array);
}