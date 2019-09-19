#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../kfifo.h"

DEFINE_KFIFO(g_fifobuf, int, 16);

void* write_thread(void* arg) {
    int x = 0;
    for (int i = 0; i < 20; i++) {
        if (kfifo_is_full(&g_fifobuf)) {
            kfifo_out(&g_fifobuf, &x, 1);
            printf("discard %d\n", x);
        }
        if (kfifo_in(&g_fifobuf, &i, 1) == 1) {
            printf("write %d\n", i);
        } else {
            printf("write fail\n");
        }
    }
    printf("write over\n");
    return NULL;
}

void* read_thread(void* arg) {
    printf("read...\n");
    int x = 0;
    for (int i = 0; i < 8; i++) {
        if (kfifo_out(&g_fifobuf, &x, 1) == 1)
            printf("read %d\n", x);
    }
    return NULL;
}

int main() {
    printf("hello kfifo\n");
    int n = kfifo_avail(&g_fifobuf);
    printf("avail: %d\n", n);

    pthread_t r, w;
    pthread_create(&w, NULL, write_thread, NULL);
    printf("..............\n");
    pthread_create(&r, NULL, read_thread, NULL);
    pthread_join(r, NULL);
    pthread_create(&r, NULL, read_thread, NULL);
    pthread_join(r, NULL);
    pthread_join(w, NULL);

    printf("over\n");
    return 0;
}
