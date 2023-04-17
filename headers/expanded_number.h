#ifndef HEADER_EXPANDED_NUMBER_INCLUDED

#define HEADER_EXPANDED_NUMBER_INCLUDED 1

typedef struct Expanded_Number_Part {
    unsigned int module; 
    int order;

    struct Expanded_Number_Part *next;
} Expanded_Number_Part; 

typedef struct Expanded_Number {
    unsigned int len;

    Expanded_Number_Part *head;
    Expanded_Number_Part *tail;
} Expanded_Number;

Expanded_Number *create_expanded_number();

void destroy_expanded_number(Expanded_Number *number);

int is_empty_expanded_number(Expanded_Number *number);

int is_equal_expanded_number(Expanded_Number *a, Expanded_Number *b);

int is_normalized_expanded_number(Expanded_Number *number);

void append_expanded_number_part(Expanded_Number *number, unsigned int module, int order);

Expanded_Number *normalize_expanded_number(Expanded_Number *number);

Expanded_Number *sum_expanded_number(Expanded_Number *a, Expanded_Number *b);

Expanded_Number *multiply_by_expanded_number_part(Expanded_Number *number, Expanded_Number_Part *part);

Expanded_Number *multiply_expanded_number(Expanded_Number *a, Expanded_Number *b);

Expanded_Number *create_from_int(int n);

void describe_expanded_number(Expanded_Number *number);

void print_expanded_number(Expanded_Number *number);

#endif