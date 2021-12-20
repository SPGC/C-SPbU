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

void remove_point(intrusive_node *deleting_node, void *data){
    data = data;
    point *current_point = container_of(deleting_node, point, node);
    free(current_point);
}

// Удаляет всё содержимое списка list
void remove_all_points(intrusive_list *list) {
    apply(list, remove_point, NULL);
    init_list(list);
}

// Вывод содержимого ноды node в терминал
// fmt - формат вывода
void print_point(intrusive_node* node, void* fmt) {
    point* printing_point = container_of(node, point, node);
    printf((char*)fmt, printing_point->x, printing_point->y);
}