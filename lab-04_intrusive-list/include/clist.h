#ifndef CLIST_H_
#define CLIST_H_
#include <stddef.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node intrusive_node;
typedef struct intrusive_list intrusive_list;

struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
};

struct intrusive_list {
    struct intrusive_node *head;
};

void init_list(intrusive_list *);
void add_node(intrusive_list *, intrusive_node *);
void remove_node(intrusive_list *, intrusive_node *);
int get_length(intrusive_list *);

#endif
