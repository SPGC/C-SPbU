#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "point_list.h"


// Добавляет в список list точку с координатами x, y
int add_point(intrusive_list *list, int x, int y) {
    point *new_point = malloc(sizeof(point));
    if(!new_point){
        printf("Error: memory allocation failed\n");
        return -1;
    }
    new_point->x = x;
    new_point->y = y;
    add_node(list, &(new_point->node));
    return 0;
}

// Удаляет всё содержимое списка list
void remove_all_points(intrusive_list *list) {
    point *current_point;
    intrusive_node *current_node = list->head->next; 
    while(current_node != list->head){
        current_point = container_of(current_node, point, node);
        current_node = current_node->next;
        free(current_point);
    }
    current_point = container_of(current_node, point, node);
    current_node = current_node->next;
    free(current_point);
    init_list(list);
}

// Вывод содержимого ноды node в терминал
// fmt - формат вывода
void print_point(intrusive_node* node, void* fmt) {
    point* printing_point = container_of(node, point, node);
    printf((char*)fmt, printing_point->x, printing_point->y);
}