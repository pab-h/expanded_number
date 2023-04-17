#include "../headers/expanded_number.h"

int main() {
    // em vez de chamar create e append, pode criar um número direto de um valor qualquer
    Expanded_Number *number = create_from_int(1024);
    describe_expanded_number(number);
    print_expanded_number(number);

    return 0; // 0 indica que executou sem erros
}
