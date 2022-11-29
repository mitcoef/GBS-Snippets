#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// declare count as global variable
int count = 0;

// if bool inside is false, lock is corrently free
typedef struct mutex {
        atomic_int _lock_int;
} mutex_t;

int mutex_lock(mutex_t* lock)
{
        int expected = 0;

        while(atomic_compare_exchange_strong(&lock->_lock_int, &expected, 1) != 1){
                expected = 0;
        };

        return 0;
}

int mutex_unlock(mutex_t* lock)
{
        int expected = 1;
        return atomic_compare_exchange_strong(&lock->_lock_int, &expected, 0);
}

mutex_t* mutex_alloc()
{
        struct mutex* lock = malloc(sizeof(mutex_t));
        lock->_lock_int = ATOMIC_VAR_INIT(0);
        return lock;
}

void mutex_free(mutex_t* lock)
{
        if(lock) free(lock);
}

void* run_nosync(void* data)
{
        (void)data;
        for(int i = 0; i < 10000; i++) {
                count++;
        }

        return NULL;
}

void* run_sync(void* data)
{
        mutex_t* m = (mutex_t*) data;
        for(int i = 0; i < 10000; i++) {
                mutex_lock(m);
                count++;
                mutex_unlock(m);
        }

        return NULL;
}


int main()
{
        pthread_t t1, t2;

        printf("Trial run without syncing!\n");

        pthread_create(&t1, NULL, &run_nosync, NULL);
        pthread_create(&t2, NULL, &run_nosync, NULL);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        printf("Count should be 20000, is: %d\n", count);

        count = 0;

        /*************************************************/

        printf("Trial run with syncing!\n");

        mutex_t* m = mutex_alloc();

        pthread_create(&t1, NULL, &run_sync, m);
        pthread_create(&t2, NULL, &run_sync, m);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        printf("Count should be 20000, is: %d\n", count);
}

