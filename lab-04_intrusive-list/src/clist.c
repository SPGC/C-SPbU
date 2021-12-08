#include "clist.h"
#include <stdlib.h>

// Начальная инициализация списка
void init_list(intrusive_list *new_list){
    new_list->head = NULL;
    return;
}

// Добавляет в список list новую ноду new_node, 
// если список пуст, эта нода становится головой списка
void add_node(intrusive_list *list, intrusive_node *new_node){
    if (!list->head){
        list->head = new_node;
        list->head->next = list->head;
        list->head->prev = list->head;
        return;
    }
    new_node->prev = list->head->prev;
    new_node->next = list->head;
    list->head->prev->next = new_node;
    list->head->prev = new_node;
    list->head = new_node;
    return;
}

// Удаляет ноду deleted_node из списка list
void remove_node(intrusive_list *list, intrusive_node *deleted_node){
    if(deleted_node == list->head){
        if(deleted_node->next == deleted_node){
            list->head = NULL;
            return;
        }
        list->head->prev->next = list->head->next;
        list->head->next->prev = list->head->prev;
        list->head = list->head->next;
        return;
    }
    deleted_node->prev->next = deleted_node->next;
    deleted_node->next->prev = deleted_node->prev;
    return;
}

// Возвращает текущую длинну списка list
int get_length(intrusive_list *list){
    intrusive_node *head = list->head;
    intrusive_node *current_node = head;
    if(!current_node){
        return 0;
    }
    int counter = 1;
    while(current_node->next != head){
        counter++;
        current_node = current_node->next;
    }
    return counter;
}