#include <pthread.h>

int work(int id);

int count = 0;                         
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; 

struct thread_arg {
    int vezes; 
};

void *thread_func(void *arg)
{
    struct thread_arg *a = (struct thread_arg *)arg;

    for (int k = 0; k < a->vezes; ++k) {
        int my_id;

        pthread_mutex_lock(&mut);
        my_id = count;
        count++;
        pthread_mutex_unlock(&mut);

        work(my_id);
    }

    return NULL;
}
