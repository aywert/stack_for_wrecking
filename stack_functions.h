#ifndef STACK_FUNCTIONS
#define STACK_FUNCTIONS

#include<stdint.h>
#include"ASSERT.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>


typedef double stack_elem_t;
const double poison_number = -13;

struct my_stack
{
    int left_block;
    //////////////
    const char* name;
    stack_elem_t* data;
    int capacity;
    int size;
    int status;
    int add_info;
    /////////////
    const char* file;
    const char* function;
    int line;
    //////////////
    uint64_t stk_hash;
    uint64_t data_hash;
    /////////////
    int right_block;
};

enum switch_if_ok
{
    WARP_VAL_STK    =2048, 
    WARP_VAL_DATA   =1024, 
    SK_KANARIKA_L   = 512,
    SK_KANARIKA_R   = 256,
    DATA_KANARIKA_L = 128,
    DATA_KANARIKA_R =  64,
    MY_UNDERFLOW    =  32,
    GET_MEMORY_FAIL =  16,
    SIZE_NAN        =   8,
    CAPACITY_NAN    =   4,
    DATA_NULL       =   2,
    ALL_OK          =   0,
    SUCCESS         =   1,
    FAILURE         =  -1,
};

switch_if_ok my_stack_ctor(my_stack* stk, int size, const char* name ON_DEBUG(, int line, const char* file, const char* function));
switch_if_ok my_stack_dtor(my_stack* stk ON_DEBUG (, int line, const char* file, const char* function));    
switch_if_ok my_stack_push(my_stack* stk, stack_elem_t value ON_DEBUG(, const char* function, const char* file, int line));
switch_if_ok my_stack_pop(my_stack* stk, stack_elem_t* x ON_DEBUG(, const char* function, const char* file, int line));
switch_if_ok stack_assert(my_stack* stk);
void my_stack_dump(my_stack* stk ON_DEBUG(, const char* function, const char* file, int line));
void user_dump(my_stack* stk);
int compare_double(double a, double b);
uint64_t get_hash(char* pointer, int size, int size_of_elem);
#endif