#include"stack_functions.h"
#include"ASSERT.h"


const int capacity_of_stack = 10;

int main(void)
{
    my_stack stk = {};
    
    MY_STACK_CTOR(&stk, capacity_of_stack);
  
    MY_STACK_DTOR(&stk);
}
