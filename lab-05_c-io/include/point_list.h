#ifndef POINTS
#define POINTS

#include "clist.h"


typedef struct point point;

struct point { 
    int x, y;
    intrusive_node node;
};

int add_point(intrusive_list *, int, int);
void remove_all_points(intrusive_list *);
void print_point(intrusive_node *, void *);

#endif