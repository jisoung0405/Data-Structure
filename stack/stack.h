#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct element {
    void* data;
    size_t capacity;
} element_t;

typedef struct stack {
    element_t *elements;
    int top;
    size_t capacity;
} stack_t;

/** initialize stack */
stack_t* init_stack(int) __attribute__((malloc));

/** return whether stack is empty */
bool is_empty(const stack_t* const restrict);

/** return whether stack is full */
bool is_full(const stack_t* const restrict);

/** push element to stack */
void push(stack_t* const restrict, void* data, size_t) __attribute__((noreturn)) ;

/** return element from stack's top element and top decrement. if stack is emtpy, it returns null */
void* pop_or_null(stack_t* const restrict, size_t);

/** return element from stack's top element. if stack is emtpy, it returns null */
void* peek_or_null(const stack_t* const restrict, size_t);

/** free stack memory */
void free_stack(stack_t* const restrict);