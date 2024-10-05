/**
 * Copyright Carl Kelso, Oct 4, 2024.  All Rights Reserved.
 */

#ifndef SRC_CORE_TYPES_H_
#define SRC_CORE_TYPES_H_

#include <stdint.h>

typedef enum {
    RET_SUCCESS = 0,

    // Error codes here
    RET_NULL,
    RET_UNSUPPORTED,
    RET_EMPTY,
    RET_OVERWRITTEN,

    RET_fence, // Let this drift to create standard errors

    RET_GROUP_VIDEO = 0x10000,
    RET_GROUP_RENDERER = 0x20000,
    RET_GROUP_IMAGE = 0x30000,
    RET_GROUP_AUDIO = 0x40000,
} retcode_enum_t;
typedef uint32_t retcode_t;

#endif /* SRC_CORE_TYPES_H_ */
