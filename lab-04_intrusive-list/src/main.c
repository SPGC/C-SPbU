#include "clist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXINPUTLENGTH 239

typedef struct point point;

struct point { 
    int x, y;
    intrusive_node node;
};

// Добавляет в список list точку с координатами x, y
void add_point(intrusive_list *list, int x, int y) {
    point *new_point = malloc(sizeof(point));
    new_point->x = x;
    new_point->y = y;
    add_node(list, &(new_point->node));
}

// Выводит в терминал всё содержимое списка list
void show_all_points(intrusive_list *list) {
    int length_of_list = get_length(list);
    if (length_of_list == 0){
        printf("\n");
        return;
    }
    point *current_point;
    intrusive_node *current_node = list->head;
    for(int i = 0; i < length_of_list - 1; i++){
        current_point = container_of(current_node, point, node);
        printf("(%d %d) ", current_point->x, current_point->y);
        current_node = current_node->next;
    }
    current_point = container_of(current_node, point, node);
    printf("(%d %d)\n", current_point->x, current_point->y);
}

// Удаляет из списка list все тчоки с координатами (x,y)
void remove_point(intrusive_list *list, int x, int y) {
    intrusive_node *current_node = list->head;
    point *current_point;
    int length_of_list = get_length(list);
    for(int i = 0; i < length_of_list; i++){
        current_point = container_of(current_node, point, node);
        if(current_point->x == x && current_point->y == y){
            remove_node(list, current_node);
            current_node = current_node->next;
            free(current_point);
        } else {
            current_node = current_node->next;
        }
    } 
}

// Удаляет всё содержимое списка list
void remove_all_points(intrusive_list *list) {
    int length_of_list = get_length(list);
    point *current_point;
    intrusive_node *current_node = list->head;
    for(int i = 0; i < length_of_list; i++){
        current_point = container_of(current_node, point, node);
        remove_node(list, current_node);
        current_node = current_node->next;
        free(current_point);
    } 
}

int main() {
    intrusive_list *list = malloc(sizeof(intrusive_list));
    init_list(list);
    char input[MAXINPUTLENGTH];
    int exit_flag = 0;
    while(1){
        scanf("%239s", input);
        switch (input[0]){
        case 'a':
            if(!strcmp(input, "add")){
                int x;
                int y;
                scanf("%d%d", &x, &y);
                add_point(list, x, y);
            } else {
                printf("Unknown command\n");
            }
            break;
        case 'r':
            if(!strcmp(input, "rm")){
                int x;
                int y;
                scanf("%d%d", &x, &y);
                remove_point(list, x, y);
            } else if(!strcmp(input, "rma")){
                remove_all_points(list);
            } else {
                printf("Unknown command\n");
            }
            break;
        case 'p':
            if(!strcmp(input, "print")){
                show_all_points(list);
            } else {
                printf("Unknown command\n");
            }
            break;
        case 'l':
            if(!strcmp(input, "len")){
                printf("%d\n", get_length(list));
            } else {
                printf("Unknown command\n");
            }
            break;
        case 'e':
            if(!strcmp(input, "exit")){
                exit_flag = 1;
            } else {
                printf("Unknown command\n");
            }
            break;
        default:
            printf("Unknown command\n");
            break;
        }
        if(exit_flag){
            break;
        }
    }
    remove_all_points(list);
    free(list);
}