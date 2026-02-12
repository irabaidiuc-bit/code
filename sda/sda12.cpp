#include <stdio.h>

#define SIZE 10

struct Order {
    int orderNumber;
    char product[30];
    int quantity;
    float price;
    float total;
};

// добавление одного заказа
void addOrder(struct Order orders[], int *count) {
    if (*count >= SIZE) {
        printf("Массив заказов заполнен!\n");
        return;
    }

    printf("\nДобавление заказа\n");

    printf("Номер заказа: ");
    scanf("%d", &orders[*count].orderNumber);

    printf("Товар: ");
    scanf("%s", orders[*count].product);

    printf("Количество: ");
    scanf("%d", &orders[*count].quantity);

    printf("Цена за единицу: ");
    scanf("%f", &orders[*count].price);

    orders[*count].total =
        orders[*count].quantity * orders[*count].price;

    (*count)++;
    printf("Заказ добавлен!\n");
}

// вывод заказов
void printOrders(struct Order orders[], int count) {
    if (count == 0) {
        printf("Заказов нет\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nИндекс %d\n", i);
        printf("Номер заказа: %d\n", orders[i].orderNumber);
        printf("Товар: %s\n", orders[i].product);
        printf("Количество: %d\n", orders[i].quantity);
        printf("Цена: %.2f\n", orders[i].price);
        printf("Общая стоимость: %.2f\n", orders[i].total);
    }
}

// редактирование по индексу
void editOrder(struct Order orders[], int count) {
    int index, choice;

    printf("Введите индекс заказа: ");
    scanf("%d", &index);

    if (index < 0 || index >= count) {
        printf("Неверный индекс\n");
        return;
    }

    printf("Что изменить?\n");
    printf("1 - Номер заказа\n");
    printf("2 - Товар\n");
    printf("3 - Количество\n");
    printf("4 - Цена\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Новый номер: ");
            scanf("%d", &orders[index].orderNumber);
            break;
        case 2:
            printf("Новый товар: ");
            scanf("%s", orders[index].product);
            break;
        case 3:
            printf("Новое количество: ");
            scanf("%d", &orders[index].quantity);
            break;
        case 4:
            printf("Новая цена: ");
            scanf("%f", &orders[index].price);
            break;
        default:
            printf("Неверный выбор\n");
            return;
    }

    orders[index].total =
        orders[index].quantity * orders[index].price;

    printf("Заказ изменён\n");
}

// поиск по номеру заказа
void searchOrder(struct Order orders[], int count) {
    int number;
    printf("Введите номер заказа: ");
    scanf("%d", &number);

    for (int i = 0; i < count; i++) {
        if (orders[i].orderNumber == number) {
            printf("\nЗаказ найден:\n");
            printf("Товар: %s\n", orders[i].product);
            printf("Количество: %d\n", orders[i].quantity);
            printf("Цена: %.2f\n", orders[i].price);
            printf("Общая стоимость: %.2f\n", orders[i].total);
            return;
        }
    }

    printf("Заказ не найден\n");
}

// общая сумма
void totalSum(struct Order orders[], int count) {
    float sum = 0;

    for (int i = 0; i < count; i++) {
        sum += orders[i].total;
    }

    printf("Общая сумма всех заказов: %.2f\n", sum);
}

int main() {
    struct Order orders[SIZE];
    int count = 0;
    int choice;

    do {
        printf("\n--- Главное меню ---\n");
        printf("1. Добавить заказ\n");
        printf("2. Показать заказы\n");
        printf("3. Редактировать заказ\n");
        printf("4. Найти заказ\n");
        printf("5. Общая сумма\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addOrder(orders, &count);
                break;
            case 2:
                printOrders(orders, count);
                break;
            case 3:
                editOrder(orders, count);
                break;
            case 4:
                searchOrder(orders, count);
                break;
            case 5:
                totalSum(orders, count);
                break;
            case 0:
                printf("Выход из программы\n");
                break;
            default:
                printf("Неверный пункт меню\n");
        }

    } while (choice != 0);

    return 0;
}
