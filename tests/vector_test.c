#include "vector.h"
#include "../acutest/acutest.h"
#include <stdlib.h>
#include <string.h>


int cmp_int(const void *a,const void *b)
{
    return *(int*)a - *(int*)b;
}

int cmp_long(const void *a,const void *b)
{
    return *(long*)a - *(long*)b;
}

int cmp_double(const void *a,const void *b)
{
    return *(double*)a - *(double*)b;
}

void test_vector_init(void)
{
    vector *v = init(sizeof(int),10);
    TEST_CHECK(v != NULL);
    int *data = get_data(v);
    TEST_CHECK(data!=NULL);
    int capacity = get_capacity(v);
    TEST_CHECK(capacity == 10);
    int index = get_index(v);
    TEST_CHECK(index == -1);
    destroy(v);
}

void test_vector_insert(void)
{

    //Test case for int type
    vector *v = init(sizeof(int),11);
    TEST_CHECK(v!=NULL);
    
    for(int i = 0;i<10;i++) insert(&i,v);

    int element = elements(v);

    TEST_CHECK(element==10);

    int index = get_index(v);
    TEST_CHECK(index == 9);

    
    
    int x = 5;

    int *val = get_value(&x,v,cmp_int);
    TEST_CHECK(*val == 5);

    destroy(v);

    //Test case for long type
    vector *v2 = init(sizeof(long),11);
    TEST_CHECK(v2!=NULL);

    for(long i = 0;i<10;i++) insert(&i,v2);

    int element2 = elements(v2);

    TEST_CHECK(element2==10);

    int index2 = get_index(v2);
    TEST_CHECK(index2 == 9);
    bool check2 = full(v2);
    TEST_CHECK(!check2);

    long x2 = 5;
    long *val2 = get_value(&x2,v2,cmp_long);
    TEST_CHECK(*val2 == 5);

    destroy(v2);

    //Test case for double type
    vector *v3 = init(sizeof(double),11);
    TEST_CHECK(v3!=NULL);

    for(double i = 0;i<10;i++) insert(&i,v3);

    int element3 = elements(v3);

    TEST_CHECK(element3==10);

    int index3 = get_index(v3);
    TEST_CHECK(index3 == 9);
    bool check3 = full(v3);
    TEST_CHECK(!check3);

    double x3 = 5;
    double *val3 = get_value(&x3,v3,cmp_double);
    TEST_CHECK(*val3 == 5);

    destroy(v3);

}

void test_vector_empty_and_full(void)
{
    vector *v = init(sizeof(int), 3);
    TEST_CHECK(v != NULL);

    TEST_CHECK(empty(v) == true);
    TEST_CHECK(full(v) == false);

    int x = 10;
    insert(&x, v);
    TEST_CHECK(empty(v) == false);
    TEST_CHECK(full(v) == false);

    insert(&x, v);
    insert(&x, v);
    TEST_CHECK(full(v) == true);

    destroy(v);
}

void test_vector_peek(void)
{
    vector *v = init(sizeof(int), 5);
    TEST_CHECK(v != NULL);

    int x = 42;
    insert(&x, v);

    x = 99;
    insert(&x, v);

    int *last = peek(v);
    TEST_CHECK(*last == 99);

    destroy(v);
}

void test_vector_realloc(void)
{
    vector *v = init(sizeof(int), 2);
    TEST_CHECK(v != NULL);
    TEST_CHECK(get_capacity(v) == 2);

    int x1 = 1, x2 = 2, x3 = 3;
    insert(&x1, v);
    insert(&x2, v);

    // Προκαλεί realloc
    insert(&x3, v);
    TEST_CHECK(get_capacity(v) == 4);
    TEST_CHECK(elements(v) == 3);

    int *val = get_value(&x3, v, cmp_int);
    TEST_CHECK(*val == 3);

    destroy(v);
}

void test_vector_get_value_not_found(void)
{
    vector *v = init(sizeof(int), 3);
    TEST_CHECK(v != NULL);

    int a = 5, b = 10;
    insert(&a, v);

    int *res = get_value(&b, v, cmp_int);
    TEST_CHECK(res == NULL);

    destroy(v);
}


TEST_LIST = {
    {"vector_init", test_vector_init},
    {"vector_insert", test_vector_insert},
    {"vector_empty_and_full", test_vector_empty_and_full},
    {"vector_peek", test_vector_peek},
    {"vector_realloc", test_vector_realloc},
    {"vector_get_value_not_found", test_vector_get_value_not_found},
    {NULL, NULL}
};
