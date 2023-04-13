#ifndef HEADER_STACK_INCLUDED

#define HEADER_STACK_INCLUDED 1

typedef struct Stack_Node{
    unsigned int module; 
    int order;

    struct Stack_Node *next;
} Stack_Node;

typedef struct Stack {
    Stack_Node *top;
} Stack; 

Stack *create_stack();

void push_stack(Stack *stack, unsigned int module, int order);

Stack_Node *pop_stack(Stack *stack);

Stack_Node *peek_stack(Stack *stack);

#endif