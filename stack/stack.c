#include "stack.h"

stack_t*
init_stack(int capacity)
__attribute__((malloc))
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if (!stack) {
        fprintf(stderr, "Memory Allocation Error \n");
        exit(1);
    }

    stack->capacity = capacity;
    stack->top = -1;
    stack->elements = (element_t *)malloc(sizeof(element_t) * capacity);
    if (!stack->elements) {
        fprintf(stderr, "Memory Allocation Error \n");
        free(stack);
        exit(1);
    }

    return stack;
}

bool
is_empty(const stack_t* const stack)
{
    assert(stack != NULL);
    return stack->top == -1;
}

bool
is_full(const stack_t* const stack)
{
    assert(stack != NULL);
    return stack->top == stack->capacity - 1;
}

void
push(stack_t* const restrict stack, void *data, size_t capacity)
__attribute__((noreturn))
{
    assert(stack != NULL);

    if (is_full(stack)) {
        fprintf(stderr, "Stack Overflow \n");
        return;
    }

    stack->top++;
    stack->elements[stack->top].data = malloc(capacity);
    if (!stack->elements[stack->top].data) {
        fprintf(stderr, "Memory Allocation Error \n");
        exit(1);
    }

    memcpy(stack->elements[stack->top].data, data, capacity);
    stack->elements[stack->top].capacity = capacity;
}

void*
pop_or_null(stack_t* const restrict stack, size_t capacity)
{
    assert(stack != NULL);

    if (is_empty(stack)) {
        fprintf(stderr, "Stack Underflow\n");
        return NULL;
    }

    void *data = stack->elements[stack->top].data;
    capacity = stack->elements[stack->top].capacity;
    stack->top--;

    return data;
}

void* 
peek_or_null(const stack_t* const restrict stack, size_t capacity)
{
    assert(stack != NULL);

    if (is_empty(stack)) {
        fprintf(stderr, "Stack Empty \n");
        return NULL;
    }

    capacity = stack->elements[stack->top].capacity;
    return stack->elements[stack->top].data;
}

void
free_stack(stack_t* const restrict stack)
{
    assert(stack != NULL);

    for (int i = 0; i <= stack->top; i++) {
        free(stack->elements[i].data);
    }
    free(stack->elements);
    free(stack);
}

int main() {
    int capacity = 5;
    stack_t* stack = init_stack(capacity);

    int a = 10;
    double b = 20.5;
    char c[] = "Hello";

    push(stack, &a, sizeof(a));
    push(stack, &b, sizeof(b));
    push(stack, &c, sizeof(c));

    size_t elm_capacity;
    char* top_element = (char *)peek(stack, &elm_capacity);
    if (top_element) {
        printf("Top element: %s\n", top_element);
    }

    char* popped_element = (char *)pop(stack, &elm_capacity);
    if (popped_element) {
        printf("Pop element: %s\n", popped_element);
        free(popped_element);
    }

    double* top_double = (double *)peek(stack, &elm_capacity);
    if (top_double) {
        printf("Top element: %f\n", *top_double);
    }

    double* popped_double = (double *)pop(stack, &elm_capacity);
    if (popped_double) {
        printf("Pop element: %f\n", *popped_double);
        free(popped_double);
    }

    int* top_int = (int *)peek(stack, &elm_capacity);
    if (top_int) {
        printf("Top element: %d\n", *top_int);
    }

    int* popped_int = (int *)pop(stack, &elm_capacity);
    if (popped_int) {
        printf("Pop element: %d\n", *popped_int);
        free(popped_int);
    }

    free_stack(stack);
    return 0;
}