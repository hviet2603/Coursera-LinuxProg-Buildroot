#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    struct thread_data* thr_data = (struct thread_data *) thread_param;
    usleep(thr_data->wait_to_obtain_ms*1000);
    pthread_mutex_lock(thr_data->mutex);
    usleep(thr_data->wait_to_release_ms*1000);
    pthread_mutex_unlock(thr_data->mutex);
    thr_data->thread_complete_success = true;

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    //struct thread_data thr_data = { .mutex=mutex, .wait_to_obtain_ms=wait_to_obtain_ms, .wait_to_release_ms=wait_to_release_ms, .thread_complete_success=false };
    struct thread_data *thr_data = malloc(sizeof(struct thread_data));
    thr_data->mutex = mutex;
    thr_data->wait_to_obtain_ms = wait_to_obtain_ms;
    thr_data->wait_to_release_ms = wait_to_release_ms;
    thr_data->thread_complete_success = false;
    int ret = pthread_create(thread, NULL, threadfunc, (void*) thr_data);

    return ret == 0 ? true : false;
}

