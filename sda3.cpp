#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Order {
    int number;
    char product[50];
    int quantity;
    float price;
    float total;
};
struct Order *orders = NULL;
int capacity = 0;
int order_count = 0;
int next_order_number = 1;
// Функция для расчета общей стоимости
void calculate_total(struct Order *order) {
    order->total = order->quantity * order->price;
}
// Функция для создания начального массива
void init_array(int size) {
    orders = (struct Order*)malloc(size * sizeof(struct Order));
    if (orders == NULL) {
        printf("Ошибка памяти!\n");
        exit(1);
    }
    capacity = size;
    order_count = 0;
    printf("Создан массив на %d элементов\n", capacity);
}
// Функция расширения массива
void expand_array() {
    printf("\n Расширение массива\n");
    printf("Было: %d элементов\n", capacity);
    int new_cap = capacity + 1;
    struct Order *new_orders = (struct Order*)malloc(new_cap * sizeof(struct Order));
    if (new_orders == NULL) {
        printf("Ошибка расширения памяти!\n");
        return;
    }
    for (int i = 0; i < order_count; i++) {
        new_orders[i] = orders[i];
    }
    free(orders);
    orders = new_orders;
    capacity = new_cap;
    printf("Стало: %d элементов\n", capacity);
}
// Функция уменьшения массива
void shrink_array() {
    if (capacity <= 1) {
        printf("Массив и так минимального размера\n");
        return;
    }
    printf("\nУменьшение массива\n");
    printf("Было: %d элементов\n", capacity);
    int new_cap = capacity - 1;
    struct Order *new_orders = (struct Order*)malloc(new_cap * sizeof(struct Order));
    if (new_orders == NULL) {
        printf("Ошибка памяти при уменьшении!\n");
        return;
    }
    for (int i = 0; i < order_count; i++) {
        new_orders[i] = orders[i];
    }
    free(orders);
    orders = new_orders;
    capacity = new_cap;
    printf("Стало: %d элементов\n", capacity);
}
// Добавление заказа
void add_order() {
    if (order_count >= capacity) {
        printf("\nМассив заполнен! Расширяем на 1 элемент.\n");
        expand_array();
    }
    printf("\nДобавление заказа %d\n", order_count + 1);
    orders[order_count].number = next_order_number++;
    printf("Товар: ");
    scanf("%s", orders[order_count].product);
    printf("Количество: ");
    scanf("%d", &orders[order_count].quantity);
    printf("Цена: ");
    scanf("%f", &orders[order_count].price);
    orders[order_count].total = orders[order_count].quantity * orders[order_count].price;
    order_count++;
    printf("Заказ добавлен! Всего заказов: %d (память: %d элементов)\n", order_count, capacity);
}
// Вывод всех заказов
void print_orders() {
    if (order_count == 0) {
        printf("Нет заказов.\n");
        return;
    }
    printf("\nВСЕ ЗАКАЗЫ:\n");
    printf("Использовано памяти: %d/%d элементов\n", order_count, capacity);
    float total_sum = 0;
    for (int i = 0; i < order_count; i++) {
        printf("Заказ #%d\n", orders[i].number);
        printf("  Товар: %s\n", orders[i].product);
        printf("  Количество: %d шт.\n", orders[i].quantity);
        printf("  Цена: %.2f лей.\n", orders[i].price);
        printf("  Сумма: %.2f лей.\n", orders[i].total);
        total_sum += orders[i].total;
    }
    printf("ИТОГО: %.2f лей\n", total_sum);
}
// Функция сортировки
void sort_orders() {
    if (order_count <= 1) {
        printf("Недостаточно заказов для сортировки!\n");
        return;
    }
    printf("\nСортировка заказов\n");
    printf("Выберите поле для сортировки:\n");
    printf("1 - По номеру заказа\n");
    printf("2 - По названию товара\n");
    printf("3 - По количеству\n");
    printf("4 - По цене\n");
    printf("5 - По общей сумме\n");
    printf("Выбор: ");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 5) {
        printf("Неверный выбор!\n");
        return;
    }
    for (int i = 0; i < order_count - 1; i++) {
        for (int j = 0; j < order_count - i - 1; j++) {
            int need_swap = 0;
            switch(choice) {
                case 1:
                    if (orders[j].number > orders[j + 1].number) need_swap = 1;
                    break;
                case 2:
                    if (strcmp(orders[j].product, orders[j + 1].product) > 0) need_swap = 1;
                    break;
                case 3:
                    if (orders[j].quantity > orders[j + 1].quantity) need_swap = 1;
                    break;
                case 4:
                    if (orders[j].price > orders[j + 1].price) need_swap = 1;
                    break;
                case 5:
                    if (orders[j].total > orders[j + 1].total) need_swap = 1;
                    break;
            }
            if (need_swap) {
                struct Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
    printf("Заказы отсортированы!\n");
    print_orders();
}
//Функция вставки нового элемента на указанную позицию
void insert_order() {
    if (order_count == 0) {
        printf("Нет заказов! Используйте добавление заказа.\n");
        return;
    }
    int position;
    printf("Введите позицию для вставки (1-%d): ", order_count);
    scanf("%d", &position);
    if (position < 1 || position > order_count) {
        printf("Неверная позиция!\n");
        return;
    }
    if (order_count >= capacity) {
        printf("\nМассив заполнен! Расширяем на 1 элемент.\n");
        expand_array();
    }
    for (int i = order_count; i > position - 1; i--) {
        orders[i] = orders[i - 1];
    }
    printf("\nВставка нового заказа на позицию %d\n", position);
    orders[position - 1].number = next_order_number++;
    printf("Товар: ");
    scanf("%s", orders[position - 1].product);
    printf("Количество: ");
    scanf("%d", &orders[position - 1].quantity);
    printf("Цена: ");
    scanf("%f", &orders[position - 1].price);
    orders[position - 1].total = orders[position - 1].quantity * orders[position - 1].price;
    order_count++;
    printf("Заказ вставлен на позицию %d!\n", position);
}
// Функция удаления элемента по индексу
void delete_by_index() {
    if (order_count == 0) {
        printf("Нет заказов для удаления!\n");
        return;
    }
    int index;
    printf("Введите индекс для удаления (1-%d): ", order_count);
    scanf("%d", &index);
    if (index < 1 || index > order_count) {
        printf("Неверный индекс!\n");
        return;
    }
    printf("\nУдаление заказа с позиции %d\n", index);
    printf("Удален заказ: %s\n", orders[index - 1].product);
    for (int i = index - 1; i < order_count - 1; i++) {
        orders[i] = orders[i + 1];
    }
    order_count--;
    printf("Осталось заказов: %d\n", order_count);
    if (order_count > 0 && order_count < capacity) {
        shrink_array();
    } else if (order_count == 0) {
        printf("Заказов нет. Создаем новый массив.\n");
        free(orders);
        init_array(1);
        next_order_number = 1;
    }
}
// Удаление последнего заказа
void remove_last_order() {
    if (order_count == 0) {
        printf("Нет заказов для удаления!\n");
        return;
    }
    printf("\nУдаление последнего заказа\n");
    printf("Удален заказ: %s\n", orders[order_count-1].product);
    order_count--;
    next_order_number--;
    printf("Осталось заказов: %d\n", order_count);
    if (order_count > 0) {
        shrink_array(); 
    } else {
        printf("Заказов нет. Создаем новый массив.\n");
        free(orders);
        init_array(1);
    }
}
// Редактирование заказа
void edit_order() {
    if (order_count == 0) {
        printf("Нет заказов!\n");
        return;
    }
    int num;
    printf("Введите номер заказа (1-%d): ", order_count);
    scanf("%d", &num);
    if (num < 1 || num > order_count) {
        printf("Неверный номер!\n");
        return;
    }
    int idx = num - 1;
    printf("\nЧто редактируем?\n");
    printf("1 - Товар\n");
    printf("2 - Количество\n");
    printf("3 - Цену\n");
    printf("Выбор: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Новый товар: ");
        scanf("%s", orders[idx].product);
    }
    else if (choice == 2) {
        printf("Новое количество: ");
        scanf("%d", &orders[idx].quantity);
        orders[idx].total = orders[idx].quantity * orders[idx].price;
    }
    else if (choice == 3) {
        printf("Новая цена: ");
        scanf("%f", &orders[idx].price);
        orders[idx].total = orders[idx].quantity * orders[idx].price;
    }
    else {
        printf("Неверный выбор!\n");
        return;
    }
    printf("Заказ изменен!\n");
}
// Поиск заказа
void search_order() {
    if (order_count == 0) {
        printf("Нет заказов!\n");
        return;
    }
    printf("\nПоиск по:\n");
    printf("1 - Номеру заказа\n");
    printf("2 - Названию товара\n");
    printf("Выбор: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        int num;
        printf("Введите номер: ");
        scanf("%d", &num);
        for (int i = 0; i < order_count; i++) {
            if (orders[i].number == num) {
                printf("\nНАЙДЕНО:\n");
                printf("Заказ #%d\n", orders[i].number);
                printf("Товар: %s\n", orders[i].product);
                printf("Количество: %d\n", orders[i].quantity);
                printf("Цена: %.2f\n", orders[i].price);
                printf("Сумма: %.2f\n", orders[i].total);
                return;
            }
        }
        printf("Заказ не найден!\n");
    }
    else if (choice == 2) {
        char product[50];
        printf("Введите товар: ");
        scanf("%s", product);
        printf("\nРЕЗУЛЬТАТЫ ПОИСКА:\n");
        int found = 0;
        for (int i = 0; i < order_count; i++) {
            if (strcmp(orders[i].product, product) == 0) {
                printf("Заказ #%d: %d шт, %.2f лей, сумма: %.2f лей\n",
                       orders[i].number,
                       orders[i].quantity,
                       orders[i].price,
                       orders[i].total);
                found = 1;
            }
        }
        if (!found) printf("Ничего не найдено\n");
    }
    else {
        printf("Неверный выбор!\n");
    }
}
// Полная очистка
void clear_all() {
    printf("\nПолная очистка\n");
    if (orders != NULL) {
        free(orders);
        orders = NULL;
        capacity = 0;
        order_count = 0;
        next_order_number = 1;
        printf("Все заказы удалены, память освобождена\n");
        printf("Создаем новый пустой массив\n");
        init_array(1);
    }
}
int main() {
    int size;
    printf("Программа управления заказами\n");
    printf("Введите начальный размер массива: ");
    scanf("%d", &size);
    if (size < 1) size = 1;
    init_array(size);
    int choice;
    do {
        printf("\nМЕНЮ:\n");
        printf("1. Добавить заказ\n");
        printf("2. Показать все заказы\n");
        printf("3. Редактировать заказ\n");
        printf("4. Найти заказ\n");
        printf("5. Удалить последний заказ\n");
        printf("6. Очистить все\n");
        printf("7. Отсортировать заказы\n");
        printf("8. Вставить заказ на позицию\n");
        printf("9. Удалить заказ по индексу\n");
        printf("0. Выход\n");
        printf("Выберите: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: add_order(); break;
            case 2: print_orders(); break;
            case 3: edit_order(); break;
            case 4: search_order(); break;
            case 5: remove_last_order(); break;
            case 6: clear_all(); break;
            case 7: sort_orders(); break;
            case 8: insert_order(); break;
            case 9: delete_by_index(); break;
            case 0:
                if (orders != NULL) {
                    free(orders);
                    printf("Память освобождена. До свидания!\n");
                }
                break;
            default: printf("Неверный выбор!\n");
        }
    } while (choice != 0);
    return 0;
}