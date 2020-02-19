/** @file circular_bfr.h
 *  @brief Function prototypes & structures for circular buffer.
 *
 *  This contains the prototypes for the  circular buffer
 *  and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Tony Josi   https://tjosi.000webhostapp.com/
 *  @bug No known bugs.
 */

/**
 * @enum CB_STAT return enum
 * @brief CB func. return type enum
 *
 * Enumeration for different possible return values for the circular
 * buffer library functions
 */
#include <stdint.h> 

typedef enum {
    CB_SUCCESS = 0,      /*!< Function success */
    CB_OVER_FLOW,        /*!< Buffer encontered memory overflow */
    CB_UNDER_FLOW,       /*!< Buffer encontered memory underflow */
} CB_STAT;

/**
 * @struct _CIRC_BUFFER
 * @brief cb basic structure
 *
 * Basic structure containing the feilds for handling different params of 
 * circular buffer
 */
typedef struct _CIRC_BUFFER {
    void *buffer;       /*!< Start address of the memory */
    void *buffer_end;   /*!< End address of the memory */
    size_t size;        /*!< Size of each buffer element in bytes */
    size_t count;       /*!< Count of items currently in buffer */
    size_t capacity;    /*!< Total capacity of the buffer */
    void *head;         /*!< Current head of buffer */
    void *tail;         /*!< Current tail of the buffer */
} CIRC_BUFFER;

/**
 * @brief Initialises the circular buffer with filling up the structure
 * and allocates memory
 *
 */
CB_STAT cb_init(CIRC_BUFFER *cb, size_t size, size_t capacity);

/**
 * @brief Get the current number of elements in the buffer
 *
 */
CB_STAT cb_get_count(CIRC_BUFFER *cb, uint32_t *count);

/**
 * @brief Push an item to the buffer
 *
 */
CB_STAT cb_push(CIRC_BUFFER *cb, const void *item);

/**
 * @brief Pop an item from the buffer
 *
 */
CB_STAT cb_pop(CIRC_BUFFER *cb, void *item);

/**
 * @brief Free the circular buffer and deallocates the memory
 *
 */
CB_STAT cb_free(CIRC_BUFFER *cb);