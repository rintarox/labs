#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// пока запись двумя разными функциями

// можно автоматизировать, чтобы человек писал потоком через запятую, но есть проблема с различением float и integer
// как решение для каждого заполнения добавлять бит метаданных или фиксированной структуры

void int_input(uint8_t arr[], size_t index, int value) {   // запись битов целого
    memcpy(&arr[index], &value, sizeof(int));        
}

void float_input(uint8_t arr[], size_t index, float value) {    // запись битов вещественного
    memcpy(&arr[index], &value, sizeof(float));
}

int gen_randint() {
    return rand() % 20001 - 10000; // понадобится для генерации и быстрого заполнения
}

float gen_ranfloat() {
    return (float)(rand() % 10000) / 1000.0f - 5.0f; // от -5.0 до 5.0
}


int uin_int() {     // ввод в hex формате
    int value;
    printf("Введите целое число в HEX формате (например, 0x1A2B): ");
    scanf("%x", &value);
    return value;
}

float uin_float() {     // ввод вещественного числа
    int choice;
    float value;
    uint32_t hex_value;      

    printf("Выберите формат ввода для вещественного числа:\n");
    printf("1. HEX (например, 0x40490FDB)\n");
    printf("2. Вещественный (например, 3.14159)\n");
    printf("3. Экспоненциальный (например, 3.14159e0)\n");
    printf("Ваш выбор (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Введите значение в HEX формате: ");
            scanf("%x", &hex_value);
            memcpy(&value, &hex_value, sizeof(float));
            break;
        case 2:
            printf("Введите значение в вещественном формате: ");
            scanf("%f", &value);
            break;
        case 3:
            printf("Введите значение в экспоненциальном формате: ");
            scanf("%f", &value);
            break;
        default:
            printf("Неверный выбор, используется вещественный формат по умолчанию.\n");
            printf("Введите значение: ");
            scanf("%f", &value);
            break;
    }
    return value;
}

void out_int(const uint8_t arr[], size_t index) {     // вывод целого числа в hex формате
    int value;
    memcpy(&value, &arr[index], sizeof(int));
    printf("Целое число (HEX): 0x%08X\n", value);
    printf("Целое число Десятичный формат: %d\n", value);
}

void out_float(const uint8_t arr[], size_t index) {
    float value;
    memcpy(&value, &arr[index], sizeof(float));
    printf("Вещественное число:\n");
    printf("  Вещественный формат: %f\n", value);
    printf("  HEX формат: 0x%08X\n", *(uint32_t*)&value);
    printf("  Экспоненциальный формат: %e\n", value);
}

int main() {
    srand(time(NULL));

    uint8_t byteArray[64] = {0};
    uint8_t typeArray[16] = {0}; // 16 блоков по 4 байта

    for (size_t i = 0; i < 16; i++) {
        size_t index = i * 4; // Индекс в массиве байт (0, 4, 8, ..., 60)
        int choice;

        printf("\nБлок %zu (индексы %zu-%zu):\n", i, index, index + 3);
        printf("Выберите способ заполнения:\n");
        printf("1. Случайное значение\n");
        printf("2. Ввод вручную\n");
        printf("Ваш выбор (1-2): ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Случайное заполнение
            int type = rand() % 2 + 1; // Случайный тип: 1 (int) или 2 (float)
            typeArray[i] = type;

            if (type == 1) {
                int value = gen_randint();
                int_input(byteArray, index, value);
            } else {
                float value = gen_ranfloat();
                float_input(byteArray, index, value);
            }
        } else {
            // Ввод вручную
            printf("Выберите тип данных:\n");
            printf("1. Целое число (int)\n");
            printf("2. Вещественное число (float)\n");
            printf("Ваш выбор (1-2): ");
            scanf("%d", &choice);

            typeArray[i] = choice;
            if (choice == 1) {
                int value = uin_int();
                int_input(byteArray, index, value);
            } else {
                float value = uin_float();
                float_input(byteArray, index, value);
            }
        }
    }

/////////////////////////////////////// OUTPUT
    printf("\nСодержимое массива:\n");
    for (size_t i = 0; i < 16; i++) {
        size_t index = i * 4;
        printf("Блок %zu (индексы %zu-%zu): ", i, index, index + 3);
        if (typeArray[i] == 1) {
            out_int(byteArray, index);
        } else {
            out_float(byteArray, index);
        }
    }

    return 0;
}