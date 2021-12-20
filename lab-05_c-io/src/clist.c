#include <stdlib.h>

#include "clist.h"


// Реализация foreach для intrusive_list
void apply(intrusive_list *list, operation op, void* data) {
    if(!list->head){
        return;
    }
    intrusive_node* current_node = list->head->prev;
    do {
        current_node = current_node->next;
        op(current_node, data);
    } while (current_node->next != list->head);
}

// Устанавливает связи ноды current с нодами prev и next
// Если current == NULL, то устанавливает связь prev и current
void setConnections(intrusive_node *prev, intrusive_node *current,
                    intrusive_node *next){
    if(current){
        current->prev = prev;
        current->next = next;
        prev->next = current;
        next->prev = current;
        
    } else {
        prev->next = next;
        next->prev = prev;
    }
}

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
        setConnections(list->head, list->head, list->head);
        return;
    }
    setConnections(list->head->prev, new_node, list->head);
    return;
}

// Удаляет ноду deleted_node из списка list
void remove_node(intrusive_list *list, intrusive_node *deleted_node){
    if(deleted_node->next == deleted_node){
            list->head = NULL;
            return;
        }
    setConnections(deleted_node->prev, NULL, deleted_node->next);
    if(deleted_node == list->head){
        list->head = deleted_node->next;
    }
    return;
}

// Счётчик для поиска длины списка 
void find_length(intrusive_node* node, void* length) {
    node = node;
    (*(int*)length)++;
}

// Поиск длины списка
int get_length(intrusive_list *list){
    int counter = 0;
    apply(list, find_length, &counter);
    return counter;
}