#include <termina.h>
#include <termina/shared/task.h>
#include <termina/shared/test.h>

#include <string.h>

/**
 * \brief Size of the longest EXCEPTION record: the tag, the task, the variant
 *        and the fields of EProcessorFault.
 */
#define TERMINA__TEST__EXCEPTION_RECORD_SIZE \
    (1U + sizeof(termina__id_t) + 1U + (2U * sizeof(uint32_t)) + (2U * sizeof(size_t)))

static void termina__test__except__put(uint8_t * const record,
                                       size_t * const offset,
                                       const void * const field,
                                       const size_t size) {

    (void)memcpy(&record[*offset], field, size);
    *offset = *offset + size;

}

void termina__test__except_hook(const termina__event_t * const termina__ev,
                                void * const termina__this,
                                const Exception except) {

    uint8_t record[TERMINA__TEST__EXCEPTION_RECORD_SIZE];
    size_t offset = 0U;

    const termina__id_t task_id = termina__os__task__current_id();
    const uint8_t variant = (uint8_t)except._variant;

    (void)termina__ev;
    (void)termina__this;

    record[0] = (uint8_t)termina__test__tag__exception;
    offset = 1U;

    termina__test__except__put(record, &offset, &task_id, sizeof(task_id));
    termina__test__except__put(record, &offset, &variant, sizeof(variant));

    // The fields one by one, so the record has no padding
    switch (except._variant) {

        case Exception__EMsgQueueSendError:
            termina__test__except__put(record, &offset, &except.EMsgQueueSendError._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EMsgQueueSendError._1, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EMsgQueueSendError._2, sizeof(int32_t));
            break;

        case Exception__EMsgQueueRecvError:
            termina__test__except__put(record, &offset, &except.EMsgQueueRecvError._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EMsgQueueRecvError._1, sizeof(int32_t));
            break;

        case Exception__EArrayIndexOutOfBounds:
            termina__test__except__put(record, &offset, &except.EArrayIndexOutOfBounds._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArrayIndexOutOfBounds._1, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArrayIndexOutOfBounds._2, sizeof(size_t));
            break;

        case Exception__EArraySliceOutOfBounds:
            termina__test__except__put(record, &offset, &except.EArraySliceOutOfBounds._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArraySliceOutOfBounds._1, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArraySliceOutOfBounds._2, sizeof(size_t));
            break;

        case Exception__EArraySliceNegativeRange:
            termina__test__except__put(record, &offset, &except.EArraySliceNegativeRange._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArraySliceNegativeRange._1, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArraySliceNegativeRange._2, sizeof(size_t));
            break;

        case Exception__EArraySliceInvalidRange:
            termina__test__except__put(record, &offset, &except.EArraySliceInvalidRange._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArraySliceInvalidRange._1, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArraySliceInvalidRange._2, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EArraySliceInvalidRange._3, sizeof(size_t));
            break;

        case Exception__EShiftAmountOutOfBounds:
            termina__test__except__put(record, &offset, &except.EShiftAmountOutOfBounds._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EShiftAmountOutOfBounds._1, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EShiftAmountOutOfBounds._2, sizeof(size_t));
            break;

        case Exception__EArithmeticOverflow:
            termina__test__except__put(record, &offset, &except.EArithmeticOverflow._0, sizeof(size_t));
            break;

        case Exception__EDivisionByZero:
            termina__test__except__put(record, &offset, &except.EDivisionByZero._0, sizeof(size_t));
            break;

        case Exception__ERuntimeFailure:
            termina__test__except__put(record, &offset, &except.ERuntimeFailure._0, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.ERuntimeFailure._1, sizeof(uint32_t));
            termina__test__except__put(record, &offset, &except.ERuntimeFailure._2, sizeof(int32_t));
            break;

        case Exception__EProcessorFault:
            termina__test__except__put(record, &offset, &except.EProcessorFault._0, sizeof(uint32_t));
            termina__test__except__put(record, &offset, &except.EProcessorFault._1, sizeof(uint32_t));
            termina__test__except__put(record, &offset, &except.EProcessorFault._2, sizeof(size_t));
            termina__test__except__put(record, &offset, &except.EProcessorFault._3, sizeof(size_t));
            break;

        case Exception__EKernelFailure:
            termina__test__except__put(record, &offset, &except.EKernelFailure._0, sizeof(uint32_t));
            termina__test__except__put(record, &offset, &except.EKernelFailure._1, sizeof(size_t));
            break;

        case Exception__EStackOverflow:
            termina__test__except__put(record, &offset, &except.EStackOverflow._0, sizeof(size_t));
            break;

        default:
            // A variant without fields that the decoder knows
            break;

    }

    // After the quiesce nothing else runs, so the record takes no lock
    termina__shared__test__write(record, offset);

}
