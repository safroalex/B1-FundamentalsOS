#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    int thread_num = *((int *) arg);
    int local_var = 0;

    while (1) {
        printf("Thread %d: local_var = %d\n", thread_num, local_var);
        local_var++;
        sleep(5);
    }

    return NULL;
}

int main() {
    const int NUM_THREADS = 5; // Количество нитей
    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
