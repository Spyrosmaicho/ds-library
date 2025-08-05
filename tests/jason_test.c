#include "../acutest/acutest.h"
#include "jason.h"


void test_valid_json(void)
{
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test1.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test2.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test3.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test4.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test6.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test7.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test14.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test15.json")==0);
}

void test_invalid_json(void)
{
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test5.json")==1);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test8.json")==1);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test9.json")==1);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test10.json")==1);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test11.json")==1);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test12.json")==1);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test13.json")==1);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test16.json")==1);
}

void test_empty_json(void)
{
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test17.json")==0);
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test18.json")==0);
}

void test_large_json(void)
{
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/test19.json")==1);
}

void test_file_not_found(void)
{
    TEST_CHECK(extraction_mode("../tests/jason_test_cases/non_existent.json")==1);
}


TEST_LIST = {
    {"test_valid_json", test_valid_json},
    {"test_invalid_json", test_invalid_json},
    {"test_empty_json", test_empty_json},
    {"test_large_json", test_large_json},
    {"test_file_not_found", test_file_not_found},
    {NULL, NULL} // end of the list
};