#include "unity.h"
#include "Fib.h"

#define DIMENSION_OF(a) (sizeof(a),sizeof(a[0]))

void test_eleent0_should_return1(void)
{
  //TEST_IGNORE_MESSAGE("Imlement me");

  TEST_ASSERT_EQUAL(1,Fibonacci_GetElement(0));
}

void test_eleent1_should_return1(void)
{
  //TEST_IGNORE_MESSAGE("Imlement me");

  TEST_ASSERT_EQUAL(1,Fibonacci_GetElement(1));
}

void test_eleent2_should_return2(void)
{
  //TEST_IGNORE_MESSAGE("Imlement me");

  TEST_ASSERT_EQUAL(2,Fibonacci_GetElement(2));
}

void test_eleent5_should_return8(void)
{
  //TEST_IGNORE_MESSAGE("Imlement me");

  TEST_ASSERT_EQUAL(8,Fibonacci_GetElement(5));
}

void test_part_of_sequence (void)
{ 
  int expected[] = {1,1,2,3,5,8,13,21,34,55,89,144};
  int n;

  for(n = 0; n < DIMENSION_OF(expected) ;n++)
  {
    TEST_ASSERT_EQUAL(expected[n],Fibonacci_GetElement(n));
  }

}

void test_negative_negative_values_return_0(void)
{
  TEST_ASSERT_EQUAL(0,Fibonacci_GetElement(-1));  
  TEST_ASSERT_EQUAL(0,Fibonacci_GetElement(-555));  
  TEST_ASSERT_EQUAL(0,Fibonacci_GetElement(-3));  
  TEST_ASSERT_EQUAL(0,Fibonacci_GetElement(INT_MIN));  
}

void test_overrun_values_return_0(void)
{
  TEST_ASSERT_EQUAL(0,Fibonacci_GetElement(INT_MAX+1));    
}
