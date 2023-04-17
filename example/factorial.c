#include "../headers/expanded_number.h"

Expanded_Number *factorial_expanded_number(Expanded_Number *number) {
    Expanded_Number *result = create_from_int(1);
    if (is_empty_expanded_number(number)) {
        return result;
    }

    Expanded_Number *previous_result;
    Expanded_Number *increment = create_from_int(1);
    Expanded_Number *current = create_from_int(1);
    Expanded_Number *previous_current;
    while (!is_equal_expanded_number(number, current)) {
        previous_result = result;
        previous_current = current;
        current = sum_expanded_number(previous_current, increment);
        result = multiply_expanded_number(previous_result, current);
        destroy_expanded_number(previous_result);
        destroy_expanded_number(previous_current);
    }

    return result;
}

int main() {
    Expanded_Number *number = create_from_int(100);

    Expanded_Number *factorial = factorial_expanded_number(number);
    describe_expanded_number(factorial);
    print_expanded_number(factorial);

    return 0; // 0 indica que executou sem erros
}
