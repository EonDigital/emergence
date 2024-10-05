/**
 * Copyright Carl Kelso, Oct 4, 2024.  All Rights Reserved.
 */

#include "keypress_handlers.h"

#include <stdio.h>

retcode_t match_bool( act_t action, void * context ) {
    bool * p_value = (bool *) context;
    switch (action) {
    default:
    case ACT_FREE:
    case ACT_RELEASE:
        *p_value = false;
        break;

    case ACT_HELD:
    case ACT_PRESS:
        *p_value = true;
        break;
    }
    return RET_SUCCESS;
}

retcode_t inv_bool( act_t action, void * context ) {
    bool * p_value = (bool *) context;
    switch (action) {
    default:
    case ACT_FREE:
    case ACT_RELEASE:
        *p_value = true;
        break;

    case ACT_HELD:
    case ACT_PRESS:
        *p_value = false;
        break;
    }
    return RET_SUCCESS;
}

retcode_t false_on_release( act_t action, void * context ) {
    bool * p_value = (bool *) context;
    if (action == ACT_RELEASE ) {
        *p_value = false;
    }
    return RET_SUCCESS;
}


retcode_t print_on_press( act_t action, void * context ) {
    (void) context;
    fprintf(stderr, "Button Pressed %d\n", action );
    return RET_SUCCESS;
}
