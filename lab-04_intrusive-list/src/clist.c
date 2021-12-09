#include <stdlib.h>

#include "clist.h"


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
    list->head = new_node;
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