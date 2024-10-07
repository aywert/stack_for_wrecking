#include"stack_functions.h"


switch_if_ok stack_assert(my_stack* stk)
{

    if (stk->stk_hash != get_hash((char*)&stk->name, 1, sizeof(my_stack)-28))
    {
        stk->status += WARP_VAL_STK;
    }

    if (stk->data == NULL)
        stk->status += DATA_NULL;

    if (stk->capacity == NAN || stk->capacity < 0)
        stk->status += CAPACITY_NAN;

    if (stk->size == NAN || stk->size < 0)
        stk->status += SIZE_NAN;

    if (!compare_double(stk->left_block, 0xDED))
    {
        stk->status += SK_KANARIKA_L;
    }
    if (!compare_double(stk->right_block, 0xDED))
    {
        stk->status += SK_KANARIKA_R;
    }

    if (!compare_double(stk->data[-1], 0xDED))
    {
        stk->status += DATA_KANARIKA_L;
    }

    if (!compare_double(stk->data[stk->capacity], 0xDED))
    {
        stk->status += DATA_KANARIKA_R;
    }

    if (stk->data_hash != get_hash((char*)&stk->data[0], stk->size, sizeof(stack_elem_t)))
    {
        stk->status += WARP_VAL_DATA;
    }
    
    
    if (stk->status != ALL_OK)
    {
        return FAILURE;
    }
    else
        return SUCCESS;
}

void my_stack_dump(my_stack* stk ON_DEBUG(, const char* function, const char* file, int line))
{
    static int n_calls = 0;
    int index = 1;

    #ifdef DEBUG
    printf(RED("ERROR in line %d, in file %s, in function %s\n"), line, file, function);
    printf("%s was made in file %s in function %s on line %d\n", stk->name, stk->file, stk->function, stk->line);
    #endif
    
    printf("----------Found issues so far in %s ----------\n", stk->name);

    int status = stk->status;

    if (status >> 11)
    {
        printf(YELLOW("%d)WARP_OF_STACK \n"), index++);
        status -= WARP_VAL_STK;
    }

    if (status >> 10)
    {
        printf(YELLOW("%d)WARP_OF_DATA \n"), index++);
        status -= WARP_VAL_DATA;
    }

    if (status >> 9)
    {
        printf(YELLOW("%d)SK_KANARIKA_L \n"), index++);
        status -= SK_KANARIKA_L;
    }

    if (status >> 8)
    {
        printf(YELLOW("%d) SK_KANARIKA_R\n"), index++);
        status -= SK_KANARIKA_R;
    }

    if (status >> 7)
    {
        printf(YELLOW("%d)  DATA_KANARIKA_L\n"), index++);
        status -= DATA_KANARIKA_L;
    }

    if (status >> 6)
    {
        printf(YELLOW("%d)  DATA_KANARIKA_R\n"), index++);
        status -= DATA_KANARIKA_R;
    }

    if (status >> 5)
    {
        printf(YELLOW("%d) UNDERFLOW\n"), index++);
        status -= MY_UNDERFLOW ;
    }

    if (status >> 4)
    {
        printf(YELLOW("%d) Get memory couldn't find a spot\n"), index++);
        status -= GET_MEMORY_FAIL;
    }

    if (status >> 3)
    {
        printf(YELLOW("%d) Size of stack is NAN or less then 0\n"), index++);
        status -= SIZE_NAN; 
    }

    if (status >> 2)
    {
        printf(YELLOW("%d) Capacity of stack is invalid\n"), index++);
        status -= CAPACITY_NAN;
    }

    if (status >> 1)
    {
        printf(YELLOW("%d) Data turned out to be NULL\n"), index++);
        status -= DATA_NULL;
    }
    
    if (stk->status == ALL_OK)
        printf(GREEN("* Nothing found\n"));
    
    printf("-------------------------\n");
    printf(MAGENTA("It's your %d call\n"), ++n_calls);
    printf("-------------------------\n");
    printf("Adress in which \"stk\"  is saved is" CYAN(" 0x %p\n"), stk);
    printf("Adress in which \"data\" is saved is" CYAN(" 0x %p\n"), stk->data);
    printf(BLUE("capasity = %2d\nsize     = %2d\n"), stk->capacity, stk->size);
    
    if (stk->data != NULL)
    {
        if (stk->size == 0)
            printf(CYAN("Nothing to print. Stack is empty.\n"));
        else
        {
            for (int i = 0; i < stk->size; i++)
            {
                printf("[x_%d] == %lg\n", i, stk->data[i]);
            }
        }
    }
}

int compare_double(double a, double b)
{
    if (fabs(a - b) <= epsilon)
        return 1;
    else 
        return 0;
}

uint64_t get_hash(char* pointer, int size, int size_of_elem)
{
    uint64_t h = 5381;

    for (int i = sizeof(stack_elem_t); i < size*size_of_elem; i++)
    {
        h = (31 * (h)) ^ (uint64_t)pointer[i];
    }
    return h;
}