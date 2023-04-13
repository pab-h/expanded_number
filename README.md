# Expanded Number
Um Expanded Number é a representação computacional de um número real expandido em suas somas multiplicadas por dez elevado a suas respectivas ordens. 

## Representação visual  
(p<sub>0</sub>)[m<sub>0</sub> o<sub>0</sub>] -> ... -> (p<sub>i</sub>)[m<sub>i</sub> o<sub>i</sub>] -> ... -> (p<sub>n</sub>)[m<sub>n</sub> o<sub>n</sub>] -> **λ**	

Onde p<sub>i</sub> é a i-ésima **parte**, m<sub>i</sub> é o i-ésimo **módulo** e o<sub>i</sub> é a i-ésima **ordem** de um Expanded Number.

Uma **parte** é formada pelo seu *módulo* e a sua *ordem*. 

### Exemplos
1. Se 123 é um número real. Então, pode ser escrito como:
123 = 1x10<sup>2</sup>  + 2x10<sup>1</sup>  + 3x10<sup>0</sup>
Dessa forma, na representação *Expanded Number* será: 
(p<sub>0</sub>)[3 0] -> (p<sub>1</sub>)[2 1] -> (p<sub>2</sub>)[1 2] -> **λ** 

1.  Se 10023 é um número real. Então, pode ser escrito como:
10023 = 1x10<sup>4</sup>  + 2x10<sup>1</sup>  + 3x10<sup>0</sup>
Dessa forma, na representação *Expanded Number* será: 
(p<sub>0</sub>)[3 0] -> (p<sub>1</sub>)[2 1] -> (p<sub>2</sub>)[1 4] -> **λ** 

1.  Se 100,23 é um número real. Então, pode ser escrito como:
100,23 = 1x10<sup>4</sup>  + 2x10<sup>-1</sup>  + 3x10<sup>-2</sup>
Dessa forma, na representação *Expanded Number* será: 
(p<sub>0</sub>)[3 -2] -> (p<sub>1</sub>)[2 -1] -> (p<sub>2</sub>)[1 4] -> **λ** 

## Operações

### Normalização 
Normaliza um *Expanded Number*.

Exemplos de *Expanded Number* não normalizado:
* (p<sub>0</sub>)[18 0] -> (p<sub>1</sub>)[3 1] -> **λ** 
* (p<sub>0</sub>)[123 0] -> (p<sub>1</sub>)[47 1] -> **λ** 

Exemplos acima normalizado: 
* (p<sub>0</sub>)[8 0] -> (p<sub>1</sub>)[4 1] -> **λ** 
* (p<sub>0</sub>)[3 0] -> (p<sub>1</sub>)[9 1] -> (p<sub>2</sub>)[5 2] -> **λ** 

Em código, o equivalente será:

```c
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
```

### Soma
Seja **a** = (p<sub>0</sub>)[2 0] -> (p<sub>1</sub>)[7 2] -> **λ**  

Seja **b** = (p<sub>0</sub>)[4 0] -> (p<sub>1</sub>)[3 1] -> **λ** 

Então, a soma **a** + **b** será:

**a** + **b** = (p<sub>0</sub>)[6 0] -> (p<sub>1</sub>)[3 1] -> (p<sub>2</sub>)[7 2] -> **λ** 

Em código, o equivalente será:

```c
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
```

### Multiplicação 
Seja **a** = (p<sub>0</sub>)[2 0] -> **λ** 

Seja **b** = (p<sub>0</sub>)[3 0] -> (p<sub>1</sub>)[3 1] -> **λ** 

Então, a multiplicação **a** * **b** será:

**a** * **b** = (p<sub>0</sub>)[6 0] -> (p<sub>1</sub>)[6 1] -> **λ**

```c
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
```
## Aplicação: Fatorial 

```c
#include "../headers/expanded_number.h"

Expanded_Number *factorial_expanded_number(Expanded_Number *number) {
    Expanded_Number *result = create_expanded_number();
    append_expanded_number_part(result, 1, 0);

    if (is_empty_expanded_number(number)) {

        return result;
    }

    Expanded_Number *previous_result;

    Expanded_Number *increment = create_expanded_number();
    append_expanded_number_part(increment, 1, 0);

    Expanded_Number *current = create_expanded_number();
    append_expanded_number_part(current, 1, 0);
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

    Expanded_Number *number = create_expanded_number();
    append_expanded_number_part(number, 1, 2);

    Expanded_Number *factorial = factorial_expanded_number(number);

    describe_expanded_number(factorial);
    print_expanded_number(factorial);

    return 1;
}

```
Nesse exemplo, é calculado o fatorial de 100.

## Como executar o exemplo do fatorial

Compilando o arquivo

```bash
gcc -I ./headers ./src/*.c ./example/factorial.c  -o ./build/factorial 
```

Executando

```bash 
./build/factorial
```