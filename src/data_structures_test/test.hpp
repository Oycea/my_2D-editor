#ifndef TEST_HPP
#define TEST_HPP

#include "../data_structures/dllist.hpp"
#include "../data_structures/stack.hpp"

bool test_is_empty();
bool test_front();
bool test_back();
bool test_remove_first();
bool test_remove_last();
bool test_clear_list1();
bool test_clear_list2();
void test_list_print();
void run_all_tests_list();

bool test_stack_push();
bool test_stack_pop();
bool test_stack_back();
void all_tests_stack();

#endif // TEST_HPP
