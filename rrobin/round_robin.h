
#include "./op_def.h"
#include "../cbuffer/circular_bfr.h"

/*!
 * \def         DEFAULT_TIME_SLICE
 * \brief       Defines the default time slice per process per round (for DEBUG)
 */
#define     DEFAULT_TIME_SLICE              10

/*!
 * \def         DEFAULT_EXEC_TIME
 * \brief       Defines the default execution time of all process (for DEBUG)
 */
#define     DEFAULT_EXEC_TIME               111.00

/*!
 * \def         RB_DEFAULT_SLEEP_TIME_WIN
 * \brief       Defines the default sleep time for each process
 *              per each round in Windows
 */
#define     RB_DEFAULT_SLEEP_TIME_WIN       100 

/*!
 * \def         RB_DEFAULT_SLEEP_TIME_MAC
 * \brief       Defines the default sleep time for each process
 *              per each round in Mac or UNIX sys.
 */
#define     RB_DEFAULT_SLEEP_TIME_MAC       100

/*!
 * \enum        RB_FUNC_STATUS
 * \brief       Return type for all RB functions
 * 
 */
typedef enum {
    RB_SUCCESS = 0,
    RB_FAIL,
    RB_INVD_ARGS,
    RB_MISC_FAIL
} RB_FUNC_STATUS;

/*!
 * \struct      PROCESS_t
 * \brief       Basic structure for each of the process in the buffer
 *              defines process properties
 */
typedef struct __PROCESS_TYPE {
    int id;
    float total_time_allotted;
    int expired_flag;
} PROCESS_t;

/*!
 * \typedef     func_ptr
 * \brief       Function pointer for call back function from 
 *              RB functions
*/
typedef RB_FUNC_STATUS (*func_ptr)(void *, void *, void *);


extern float RB_MASTER_TIMER;

CIRC_BUFFER cbuff;
CIRC_BUFFER *MASTER_PROCESS_C_BUFFER;

RB_FUNC_STATUS rb_initial_init(uint8_t, float);
RB_FUNC_STATUS rb_start_scheduling(func_ptr);