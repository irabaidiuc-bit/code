#ifndef DATA_H
#define DATA_H

struct Order {
    int number;
    char product[50];
    int quantity;
    float price;
    float total;
};

extern struct Order *orders;
extern int capacity;
extern int order_count;
extern int next_order_number;

void init_array(int size);
void expand_array();
void shrink_array();
void add_order();
void print_orders();
void sort_orders();
void insert_order();
void delete_by_index();
void remove_last_order();
void edit_order();
void search_order();
void clear_all();
void save_to_file();
void load_from_file();
void save_on_exit();

#endif