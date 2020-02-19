#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <time.h>
#endif

#include "round_robin.h"

float RB_SCHED_TM_SLICE = 0;  /* in ms */
float RB_MASTER_TIMER = 0;
uint8_t RB_CUR_BUFFER_SIZE = 0;

/* private functions */
static int __buffer_default_data_init(CIRC_BUFFER *, float);

#ifndef _WIN32
    static int sleep_in_ms(long);
#endif

/* public functions */
RB_FUNC_STATUS rb_initial_init(uint8_t count, float time_slice) {

    /* create a handle for circular buffer 
    handling buffer for all process */
    MASTER_PROCESS_C_BUFFER = &cbuff;

    /* create a handle for circular buffer handling buffer for all process */
    MASTER_PROCESS_C_BUFFER = &cbuff; 
    
    /* init. per process per round time slot */
    RB_SCHED_TM_SLICE = time_slice;

    /* init process count */
    RB_CUR_BUFFER_SIZE = count;

    /* check if count is valid */
    if (count <= 0)
        return RB_INVD_ARGS;

    /* initialise circular buffer & fill it with default values */
    if (cb_init(MASTER_PROCESS_C_BUFFER, sizeof(CIRC_BUFFER), 
    RB_CUR_BUFFER_SIZE) == CB_SUCCESS) {

        /* init. data to each of the process
        struct object in the c buffer */
        if (!__buffer_default_data_init(MASTER_PROCESS_C_BUFFER, 
        DEFAULT_EXEC_TIME)) {
            
            /* if the data initialisation of process buffer
            is success, then, return RB_SUCCESS */
            return RB_SUCCESS;

        }

        /* if the data initialisation of process buffer
        is fails, then, return fail */
        return RB_MISC_FAIL;

    }


    /* handle error */
    else

        /* if the initialisation of the process
        buffer fails, then, return RB_FAIL */
        return RB_FAIL;

}

RB_FUNC_STATUS rb_start_scheduling(func_ptr rb_callback) {
    RB_FUNC_STATUS ret_code;

    /* inits. */
    PROCESS_t rb_cur_proc;
    float cur_slice;
    static uint8_t expired_cntr = 0;
    uint32_t no_of_loops = 0;
    static uint8_t itr = 0;

    /* do processing */
    while (1) {

        /* pop the first process from queue */
        if (cb_pop(MASTER_PROCESS_C_BUFFER, &rb_cur_proc) == CB_SUCCESS) {
            
            /* catch completion of each round */
            if (itr == (RB_CUR_BUFFER_SIZE)) {
                itr = 0;
                printf("\n__________________________________________________________________________");
                expired_cntr = 0;
                no_of_loops++;
            }

            /* check if the process expired 
            (exceeded max limit allowed) */
            if (!rb_cur_proc.expired_flag) {

                /* do processing for that process */
                /* start */
/* if Windows system */
#ifdef _WIN32
                Sleep(RB_DEFAULT_SLEEP_TIME_WIN);
/* UNIX based systems */
#else
                sleep_in_ms(RB_DEFAULT_SLEEP_TIME_MAC);
#endif
                /* stop */
                /* deduct the time slcie from allotted time */
                rb_cur_proc.total_time_allotted = //
                rb_cur_proc.total_time_allotted - RB_SCHED_TM_SLICE;

                /* check if total time allotted expired, if yes, 
                set the expired_flagm, update master timer */
                if (rb_cur_proc.total_time_allotted <= 0) {
                    rb_cur_proc.expired_flag = 1;
                    
                    cur_slice = RB_SCHED_TM_SLICE + 
                    rb_cur_proc.total_time_allotted;
                    
                    RB_MASTER_TIMER += cur_slice;
                    rb_cur_proc.total_time_allotted = 0;
                }

                /* if not, (. of above if)
                update new remaining time */
                else {
                    cur_slice = RB_SCHED_TM_SLICE;
                    RB_MASTER_TIMER += RB_SCHED_TM_SLICE;
                }

                /* call the call back function */
                ret_code = (*rb_callback)((void *)&rb_cur_proc, //
                (void *)&cur_slice, (void *)&no_of_loops);
            }
            else
                /* if the process was already expired 
                increment the counter*/
                expired_cntr++;

            /* push the buffer back to the queue */
            if (cb_push(MASTER_PROCESS_C_BUFFER, &rb_cur_proc) != CB_SUCCESS)
                return RB_FAIL;
        }

        else 
            /* if error in popping the process from
            the circular buffer, then, return RB_FAIL*/
            return RB_FAIL;
        

        /* if all process in the queue expired then break the loop */
        if (expired_cntr == RB_CUR_BUFFER_SIZE) {
            break;
        }

        /* keeping track of the count of 
        processes in each rounds*/
        itr++;

    }

    printf("\nSTAT -> TOTAL TIME: %f", RB_MASTER_TIMER);

    /* return, success */
    return RB_SUCCESS;
}

/* /////////////////////////// H E L P E R S  //////////////////////////// */

static int __buffer_default_data_init(CIRC_BUFFER *cbuff, float exec_time) {

    PROCESS_t rb_temp_proc;
    int t_id = 1;
    int t_count;
    int i = 0;
    float t__fval;

    /* for each of the process to
    be added to the circular buffer */
    while (i < RB_CUR_BUFFER_SIZE) {

        /* prompt exec time from user*/
        printf("Allotted time for %d: ", t_id);
        scanf("%f", &t__fval);
        
        /* init the process struct with data */
        rb_temp_proc.id = t_id;
        rb_temp_proc.total_time_allotted = t__fval;
        rb_temp_proc.expired_flag = 0;

        /* push the process struct to the buffer */
        if (cb_push(cbuff, &rb_temp_proc) != CB_SUCCESS)
            return 1;

        t_id++;
        if (t_id == (t_count + 1))
            break;

        i++;
    }

    return 0;
}

#ifndef _WIN32
    static int sleep_in_ms(long ms) {

        struct timespec ts;
        int res;

        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000;

        do {
            res = nanosleep(&ts, &ts);
        } while (res);

        return res;
    }
#endif