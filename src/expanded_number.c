#include "../headers/expanded_number.h"
#include "../headers/stack.h"
#include <stdlib.h>
#include <stdio.h>

Expanded_Number *create_expanded_number() {
    Expanded_Number *number = malloc(sizeof(Expanded_Number));

    number->len = 0;
    number->head = 0;
    number->tail = 0;

    return number;
}

void destroy_expanded_number(Expanded_Number *number){
    Expanded_Number_Part *tmp;

    while (number->head) {
        tmp = number->head;
        number->head = number->head->next;
        free(tmp);

    }

    number->len = 0;
    number->tail = 0;

}

int is_empty_expanded_number(Expanded_Number *number) {
    return number->head == 0;
}

int is_equal_expanded_number(Expanded_Number *a, Expanded_Number *b) {
    if (a->len != b->len) {
        return 0;
    }

    Expanded_Number_Part *current_a = a->head;
    Expanded_Number_Part *current_b = b->head;

    while (current_a) {

        if (current_a->module != current_b->module) {
            
            return 0;
        }

        if (current_a->order != current_b->order) {
            
            return 0;
        }

        current_a = current_a->next;
        current_b = current_b->next;
    }

    return 1;
}

int is_normalized_expanded_number(Expanded_Number *number) {
    Expanded_Number_Part *current = number->head;

    while (current) {
        if (current->module <= 0 || current->module >= 10) {
            
            return 0;
        }

        if (current->next && (current->order == current->next->order)) {

            return 0;
        }
            

        current = current->next;
    }

    return 1;
}

void append_expanded_number_part(Expanded_Number *number, unsigned int module, int order) {
    Expanded_Number_Part *new = malloc(sizeof(Expanded_Number_Part));

    if (module <= 0) {
        
        return;
    }

    new->module = module;
    new->order = order;
    new->next = 0;

    if (is_empty_expanded_number(number)) {
        number->head = new;
        number->tail = new;
        number->len++;

        return;
    }

    if (number->head->order >= new->order) {
        new->next = number->head;
        number->head = new;
        number->len++;
        
        return;
    }

    if (number->tail->order <= new->order) {
        number->tail->next = new;
        number->tail = new;
        number->len++;

        return;
    }

    Expanded_Number_Part *current = number->head;

    while (current) {
        if (current->next->order >= new->order) {
            new->next = current->next;
            current->next = new;
            number->len++;

            return;
        }

        current = current->next;

    }

}

void print_expanded_number(Expanded_Number *number) {
    printf("\n");

    if (is_empty_expanded_number(number)) {
        printf("0");
        
        return;
    }

    Stack *stack = create_stack();

    Expanded_Number_Part *current_part = number->head;

    while (current_part) {
        push_stack(stack, current_part->module, current_part->order);

        current_part = current_part->next;
    }

    Stack_Node *current_poped_stack_node = pop_stack(stack);
    Stack_Node *current_peeked_stack_node = peek_stack(stack);

    while (current_peeked_stack_node) {
        int zeros_between = current_poped_stack_node->order - current_peeked_stack_node->order - 1;

        printf("%u", current_poped_stack_node->module);

        for (int i = 0; i < zeros_between; i++) {
            printf("0");
        }

        current_poped_stack_node = pop_stack(stack);
        current_peeked_stack_node = peek_stack(stack);
    }

    printf("%u", current_poped_stack_node->module);

    int zeros_after_last_poped_stack_node = current_poped_stack_node->order;

    for (int i = 0; i < zeros_after_last_poped_stack_node; i++) {
        printf("0");
    }

    printf("\n");

}

void describe_expanded_number(Expanded_Number *number) {
    Expanded_Number_Part *current = number->head;

    while (current) {
        printf("[%i %d] -> ", current->module, current->order);

        current = current->next;
    }

    printf("0\n");
}

Expanded_Number *normalize_expanded_number(Expanded_Number *number) {
    Expanded_Number *tmp = create_expanded_number(); 
    Expanded_Number_Part *current = number->head;

    unsigned int current_module;
    int current_order;

    while (current) {
        current_module = current->module;
        current_order = current->order;

        while (current_module > 0){
            append_expanded_number_part(
                tmp, 
                current_module % 10, 
                current_order
            );

            current_module /= 10;
            current_order++;

        }

        current = current->next;
    }

    Expanded_Number *result = create_expanded_number(); 

    current = tmp->head;

    while (current) {
        if (
            is_empty_expanded_number(result) || 
            result->tail->order != current->order
        ) {
            append_expanded_number_part(
                result, 
                current->module, 
                current->order
            );
            current = current->next;
            
            continue;
        }

        if (result->tail->order == current->order) {
            result->tail->module += current->module;

        }

        current = current->next;
    }

    destroy_expanded_number(tmp);

    if (!is_normalized_expanded_number(result)) {

        return normalize_expanded_number(result);
    }

    return result;
}

Expanded_Number *sum_expanded_number(Expanded_Number *a, Expanded_Number *b) {
    Expanded_Number *tmp = create_expanded_number();

    Expanded_Number_Part *current_a = a->head;
    Expanded_Number_Part *current_b = b->head;

    while (current_a || current_b) {
        if (current_a) {
            append_expanded_number_part(
                tmp, 
                current_a->module, 
                current_a->order
            );

            current_a = current_a->next;

        }

        if (current_b) {
            append_expanded_number_part(
                tmp, 
                current_b->module, 
                current_b->order
            );

            current_b = current_b->next;

        }

    }

    Expanded_Number *result = normalize_expanded_number(tmp);
    destroy_expanded_number(tmp);

    return result;
}

Expanded_Number *multiply_by_expanded_number_part(Expanded_Number *number, Expanded_Number_Part *part) {
    Expanded_Number *tmp = create_expanded_number();
    Expanded_Number_Part *current = number->head;

    while (current) {
        append_expanded_number_part(
            tmp,
            current->module * part->module,
            current->order + part->order
        );

        current = current->next;
    }

    Expanded_Number *result = normalize_expanded_number(tmp);
    destroy_expanded_number(tmp);

    return result;
}

Expanded_Number *multiply_expanded_number(Expanded_Number *a, Expanded_Number *b) {
    Expanded_Number *result = multiply_by_expanded_number_part(b, a->head);
    Expanded_Number *previous_result;
    Expanded_Number *tmp;

    Expanded_Number_Part *current = a->head->next;

    while (current) {
        previous_result = result;
        tmp = multiply_by_expanded_number_part(b, current);
        result = sum_expanded_number(previous_result, tmp);

        destroy_expanded_number(previous_result);
        destroy_expanded_number(tmp);

        current = current->next;

    }

    return result;
}

// int main() {
//     Expanded_Number *number = create_expanded_number();

//     append_expanded_number_part(number, 1, 4);
//     append_expanded_number_part(number, 2, 1);
//     append_expanded_number_part(number, 3, 0);

//     print_expanded_number(number);

// }
