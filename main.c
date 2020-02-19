#include <stdio.h>
#include <stdint.h>

#include "rrobin/round_robin.h"

RB_FUNC_STATUS main_test_cb__OP_STAT(void *, void *, void *);

int main() {

    uint8_t proc_count;
    float time_slice;

    printf("Enter process count: ");
    scanf("%d", &proc_count);
    printf("Enter time slice per process per round: ");
    scanf("%f", &time_slice);

    if (rb_initial_init(proc_count, time_slice) == RB_SUCCESS)
        if(rb_start_scheduling((func_ptr)main_test_cb__OP_STAT) == RB_SUCCESS)
            printf("\nSuccess");
            
    else
        printf("\nFail");

    printf("\nExec. Completed");

    return 0;
}

RB_FUNC_STATUS main_test_cb__OP_STAT(void *ptr1, void *ptr2, void *ptr3) {

    PROCESS_t *t__ptr;
    t__ptr = (PROCESS_t *) ptr1;
    
    printf("\n ** LOOP: %d       ID: %d      SLICE: %f      REM_TIME: %f", 
    *(uint32_t *)ptr3, t__ptr->id, *(float *)ptr2, t__ptr->total_time_allotted);

    return RB_SUCCESS;
}