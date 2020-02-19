/** 
 *  @file circular_bfr.c
 *  @brief Circular buffer global file
 *
 *  This contains the circular buffer impelementation.
 *
 *  @author Tony Josi   https://tjosi.000webhostapp.com/
 *  @bug No known bugs.
 */

#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

/**
*circular buffer header 
*
*/
#include "circular_bfr.h"


/**
 * Initialises an empty buffer with the given size and
 * number of elements
 * 
 * @param [out]  *cb          Handle to the circular buffer
 *
 * @param [in]   size         Size of an element in the circular buffer  
 * 
 * @param [in]   capacity     Number of elements in the circular buffer  
 *
 * @return   Status
 *           - #CB_SUCCESS    Successfully initialised the c buffer
 */
CB_STAT cb_init(CIRC_BUFFER *cb, size_t size, size_t capacity) {
    
    /* init struct. fields */
    cb->buffer = malloc(capacity * size);
    cb->buffer_end = (uint8_t *)cb->buffer + (capacity * size);
    cb->capacity = capacity;
    cb->size = size;
    cb->count = 0;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
    
    /* return success */
    return CB_SUCCESS;
}

/**
 * Returns the exact count of items in the buffer currently
 * 
 * @param [in]  *cb          Handle to the circular buffer
 *
 * @param [out] *count       Count of items currently in the buffer
 * 
 * @return   Status
 *           - #CB_SUCCESS    Successfully initialised the c buffer
 */
CB_STAT cb_get_count(CIRC_BUFFER *cb, uint32_t *count) {
    
    *count = cb->count;

    /* return success */
    return CB_SUCCESS;
}

/**
 * Pushes an item to the buffer
 * 
 * @param [in]  *cb          Handle to the circular buffer
 *
 * @param [in]  *item        Item pushed in the buffer
 * 
 * @return   Status
 *           - #CB_SUCCESS    Successfully initialised the c buffer
 *           - #CB_OVER_FLOW  Buffer encountered overflow
 */
CB_STAT cb_push(CIRC_BUFFER *cb, const void *item) {

    if(cb->count == cb->capacity) {
        /* buffer full*/
        printf("\nERR: Buffer overflow");
        return CB_OVER_FLOW;
    }

    memcpy(cb->head, item, cb->size);
    cb->head = (uint8_t *)cb->head + cb->size;
    if(cb->head == cb->buffer_end) 
        cb->head = cb->buffer;
    cb->count++;

    /* return success */
    return CB_SUCCESS;
}

/**
 * Pops an item from the buffer
 * 
 * @param [in]  *cb          Handle to the circular buffer
 *
 * @param [out]  *item       Item poped from the buffer
 * 
 * @return   Status
 *           - #CB_SUCCESS    Successfully initialised the c buffer
 *           - #CB_UNDER_FLOW Buffer encountered underflow
 */
CB_STAT cb_pop(CIRC_BUFFER *cb, void *item) {

    if(cb->count == 0) {
        /* buffer empty */
        printf("\nERR: Buffer underflow");
        return CB_UNDER_FLOW;
    }

    memcpy(item, cb->tail, cb->size);
    cb->tail = (uint8_t*)cb->tail + cb->size;
    if(cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    cb->count--;

    /* return success */
    return CB_SUCCESS;
}

/**
 * Deallocates an allocated buffer
 * 
 * @param [in]  *cb          Handle to the circular buffer
 * 
 * @return   Status
 *           - #CB_SUCCESS    Successfully initialised the c buffer
 */
CB_STAT cb_free(CIRC_BUFFER *cb) {
    
    free(cb->buffer);

    /* return success */
    return CB_SUCCESS;
}