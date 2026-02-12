#include <stdio.h>
#include <string.h>
struct Order {
    int number;         
    char product[50];    
    int quantity;      
    float price;    
    float total;   
};
#define MAX_ORDERS 10
#define MAX_PRODUCT_LEN 50
struct Order orders[MAX_ORDERS];
int order_count = 0;  
//Функция для расчета общей стоимости
void calculate_total(struct Order *order) {
    order->total = order->quantity * order->price;
}
//Функция ввода одного заказа
void input_order() {
    if (order_count >= MAX_ORDERS) {
        printf("Массив заказов полон!\n");
        return;
    }   
    printf("\nВвод заказа %d \n", order_count + 1);   
    orders[order_count].number = order_count + 1;  
    printf("Введите название товара: ");
    scanf("%s", orders[order_count].product);   
    printf("Введите количество: ");
    scanf("%d", &orders[order_count].quantity);  
    printf("Введите цену за единицу: ");
    scanf("%f", &orders[order_count].price);   
    calculate_total(&orders[order_count]);   
    order_count++;
    printf("Заказ успешно добавлен!\n");
}
//Функция вывода всех заказов
void print_orders() {
    if (order_count == 0) {
        printf("Нет заказов.\n");
        return;
    }
    printf("\n ВСЕ ЗАКАЗЫ \n");
    float grand_total = 0;
    for (int i = 0; i < order_count; i++) {
        printf("Заказ №%d\n", orders[i].number);
        printf("  Товар: %s\n", orders[i].product);
        printf("  Количество: %d\n", orders[i].quantity);
        printf("  Цена: %.2f\n", orders[i].price);
        printf("  Сумма: %.2f\n", orders[i].total);
        grand_total += orders[i].total;
    }
    printf("ОБЩАЯ СУММА: %.2f\n", grand_total);
}
//Функция редактирования заказа по индексу
void edit_order() {
    int index;  
    printf("Введите номер заказа для редактирования (1-%d): ", order_count);
    scanf("%d", &index);
    if (index < 1 || index > order_count) {
        printf("Неверный номер заказа!\n");
        return;
    }
    index--; 
    printf("\nРедактирование заказа №%d\n", index + 1);
    printf("Текущие данные:\n");
    printf("1. Товар: %s\n", orders[index].product);
    printf("2. Количество: %d\n", orders[index].quantity);
    printf("3. Цена за единицу: %.2f\n", orders[index].price);
    int choice;
    printf("\nЧто хотите отредактировать?\n");
    printf("1 - Товар\n");
    printf("2 - Количество\n");
    printf("3 - Цену\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            printf("Введите новое название товара: ");
            scanf("%s", orders[index].product);
            break;
        case 2:
            printf("Введите новое количество: ");
            scanf("%d", &orders[index].quantity);
            break;
        case 3:
            printf("Введите новую цену: ");
            scanf("%f", &orders[index].price);
            break;
        default:
            printf("Неверный выбор!\n");
            return;
    }
    calculate_total(&orders[index]);
    printf("Заказ успешно отредактирован!\n");
}
//Функция поиска заказа
void search_order() {
    int choice;
    printf("\nПоиск заказа\n");
    printf("По какому полю искать?\n");
    printf("1 - По номеру заказа\n");
    printf("2 - По названию товара\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);
    if (choice == 1) {
        int search_number;
        printf("Введите номер заказа: ");
        scanf("%d", &search_number);
        int found = 0;
        for (int i = 0; i < order_count; i++) {
            if (orders[i].number == search_number) {
                printf("\nНАЙДЕН ЗАКАЗ\n");
                printf("ЗАКАЗ №%d\n", orders[i].number);
                printf("  Товар: %s\n", orders[i].product);
                printf("  Количество: %d шт.\n", orders[i].quantity);
                printf("  Цена за единицу: %.2f лей\n", orders[i].price);
                printf("  Общая стоимость: %.2f лей\n", orders[i].total);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Заказ с номером %d не найден.\n", search_number);
        }
    } else if (choice == 2) {
        char search_product[MAX_PRODUCT_LEN];
        printf("Введите название товара: ");
        scanf("%s", search_product);
        int found = 0;
        printf("\nРЕЗУЛЬТАТЫ ПОИСКА \n");
        for (int i = 0; i < order_count; i++) {
            if (strcmp(orders[i].product, search_product) == 0) {
                printf("\nЗАКАЗ №%d\n", orders[i].number);
                printf("  Товар: %s\n", orders[i].product);
                printf("  Количество: %d шт.\n", orders[i].quantity);
                printf("  Цена за единицу: %.2f лей\n", orders[i].price);
                printf("  Общая стоимость: %.2f лей\n", orders[i].total);
                found = 1;
            }
        }
        if (!found) {
            printf("Заказы с товаром '%s' не найдены.\n", search_product);
        }
    } else {
        printf("Неверный выбор!\n");
    }
}
void print_menu() {
    printf("\nМЕНЮ УПРАВЛЕНИЯ ЗАКАЗАМИ\n");
    printf("1. Добавить новый заказ\n");
    printf("2. Показать все заказы\n");
    printf("3. Редактировать заказ\n");
    printf("4. Найти заказ\n");
    printf("5. Выход\n");
    printf("Выберите действие: ");
}
int main() {
    printf("Программа управления заказами\n");
    int choice;
    do {
        print_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                input_order();
                break;
            case 2:
                print_orders();
                break;
            case 3:
                if (order_count > 0) {
                    edit_order();
                } else {
                    printf("Нет заказов для редактирования!\n");
                }
                break;
            case 4:
                if (order_count > 0) {
                    search_order();
                } else {
                    printf("Нет заказов для поиска!\n");
                }
                break;
            case 5:
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (choice != 5);
    return 0;
}