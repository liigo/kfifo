#include <stdio.h>
#include "../list.h"

struct node {
    int i;
    struct list_head list;
};

LIST_HEAD(head);

int main() {
    struct node n1,n2,n3;
    n1.i = 101;
    n2.i = 102;
    n3.i = 103;

    list_add_tail(&n1.list, &head);
    list_add_tail(&n2.list, &head);
    list_add_tail(&n3.list, &head);

    struct list_head *p;
    list_for_each(p, &head) {
        struct node *n = list_entry(p, struct node, list);
        printf("%d, ", n->i);
    }

    return 0;
}
