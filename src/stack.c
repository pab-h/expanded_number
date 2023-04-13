#include "../headers/stack.h"

Stack *create_stack() {
    Stack *stack = malloc(sizeof(Stack));

    stack->top = 0;

    return stack;
}

int is_empty_stack(Stack *stack) {
    return stack->top == 0;
}

void push_stack(Stack *stack, unsigned int module, int order) {
    Stack_Node *new = malloc(sizeof(Stack_Node));

    new->module = module;
    new->order = order;
    new->next = stack->top;
    stack->top = new;

}

Stack_Node *pop_stack(Stack *stack) {
    if (isEmpty(stack)) {
        return;
    }

    Stack_Node *poped_node = stack->top;
    Stack_Node *tmp = stack->top;

    stack->top = stack->top->next;

    return poped_node;
}

Stack_Node *peek_stack(Stack *stack) {
    if (isEmpty(stack)) {
        return;
    }

    return stack->top;
}
