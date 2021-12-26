#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "clist.h"


#define MAXINPUTLENGTH 239

typedef struct point point;

struct point { 
    int x, y;
    intrusive_node node;
};

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

// Выводит в терминал всё содержимое списка list
void show_all_points(intrusive_list *list) {
    point *current_point;
    intrusive_node *current_node = list->head;
    if (current_node){
        do{
            if(current_node != list->head){
                printf(" ");
            }
            current_point = container_of(current_node, point, node);
            printf("(%d %d)", current_point->x, current_point->y);
            current_node = current_node->next;
        } while (current_node != list->head);
    }
    printf("\n");
}

// Удаляет из списка list все тчоки с координатами (x,y)
void remove_point(intrusive_list *list, int x, int y) {
    point *current_point;
    if(!list->head){
        return;
    }
    intrusive_node *current_node = list->head->next;
    while(current_node != list->head){
        current_point = container_of(current_node, point, node);
        current_node = current_node->next;
        if(current_point->x == x && current_point->y == y){
            remove_node(list, current_node->prev);
            free(current_point);
        }
    }
    current_point = container_of(current_node, point, node);
    current_node = current_node->next;
    if(current_point->x == x && current_point->y == y){
            remove_node(list, current_node->prev);
            free(current_point);
    }
}

// Удаляет всё содержимое списка list
void remove_all_points(intrusive_list *list) {
    point *current_point;
    if(!list->head){
        return;
    }
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


int main() {
    intrusive_list list;
    init_list(&list);
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
                if(add_point(&list, x, y)){
                    return -1;
                }
            } else {
                printf("Unknown command\n");
            }
            break;
        case 'r':
            if(!strcmp(input, "rm")){
                int x;
                int y;
                scanf("%d%d", &x, &y);
                remove_point(&list, x, y);
            } else if(!strcmp(input, "rma")){
                remove_all_points(&list);
            } else {
                printf("Unknown command\n");
            }
            break;
        case 'p':
            if(!strcmp(input, "print")){
                show_all_points(&list);
            } else {
                printf("Unknown command\n");
            }
            break;
        case 'l':
            if(!strcmp(input, "len")){
                printf("%d\n", get_length(&list));
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
    remove_all_points(&list);
}