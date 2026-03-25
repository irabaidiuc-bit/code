#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <locale.h>
int main() {
    setlocale(LC_ALL, "Russian");
    int size;
    printf("Программа управления заказами\n");
    printf("Введите начальный размер массива: ");
    scanf("%d", &size);
    if (size < 1) size = 1;
    init_array(size);
    
    printf("\nЗагрузить данные из файла? (y/n): ");
    char load_choice;
    scanf(" %c", &load_choice);
    if (load_choice == 'y' || load_choice == 'Y') {
        load_from_file();
    }
    
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
        printf("10. Сохранить в файл\n");
        printf("11. Загрузить из файла\n");
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
            case 10: save_to_file(); break;
            case 11: load_from_file(); break;
            case 0:
                save_on_exit();
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