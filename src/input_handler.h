/**
 * Copyright Carl Kelso, Oct 4, 2024.  All Rights Reserved.
 */

#ifndef SRC_INPUT_HANDLER_H_
#define SRC_INPUT_HANDLER_H_

#include "core_types.h"

typedef enum {
    SOURCE_KEYBOARD,
    SOURCE_MOUSE,
    SOURCE_JOY,
    SOURCE_CONTROLLER,
} source_id_t;


typedef enum {
    ACT_FREE,
    ACT_RELEASE,
    ACT_HELD,
    ACT_PRESS,

    ACT_transition_to = 1,
} act_t;


typedef uint32_t ubutton_t;


static ubutton_t universal_button( source_id_t id, act_t act, uint32_t key ) {
    return ( id & 0xF ) << 28
         | ( act & 0x3 ) << 26
         | ( key & 0x3FFFFFF );
}

static act_t get_universal_button_action( ubutton_t button ) {
    return (act_t) ( ( button >> 26 ) & 0x3 );
}

typedef retcode_t (keypress_handler_f)( act_t action, void * context );
typedef retcode_t (axis_handler_f)( act_t action, int32_t pos, void * context );
typedef retcode_t (axis2d_handler_f)( act_t action, int32_t posx, int32_t posy, void * context );
typedef keypress_handler_f *keypress_handler_fp;
typedef axis_handler_f *axis_handler_fp;
typedef axis2d_handler_f *axis2d_handler_fp;

class input_handler {
public:
    /**
     * Use to register an action against a particular button
     * @param button
     * @param handler
     * @param context
     * @return
     * @{
     */
    virtual retcode_t register_keypress( ubutton_t button, keypress_handler_fp handler, void * context ) = 0;
    virtual retcode_t register_axis( ubutton_t button, axis_handler_fp handler, void * context ) = 0;
    virtual retcode_t register_axis2d( ubutton_t button, axis2d_handler_fp handler, void * context ) = 0;
    /// @}

    /**
     * Use to execute the registered action associated with this button
     * @param button
     * @return
     */
    virtual retcode_t keypress( ubutton_t button ) const = 0;
    virtual retcode_t axis( ubutton_t button, int32_t pos ) const = 0;
    virtual retcode_t axis2d( ubutton_t button, int32_t posx, int32_t posy ) const = 0;

    /**
     * Use to delete a registered action associated with a button
     * @param button
     * @return
     */
    virtual retcode_t unregister_keypress( ubutton_t button ) = 0;
    virtual retcode_t unregister_axis( ubutton_t button ) = 0;
    virtual retcode_t unregister_axis2d( ubutton_t button ) = 0;
    /// @}

public:
    static input_handler * create_handler();
    static void cleanup_handler( input_handler ** handler );

protected:
    input_handler() = default;
    virtual ~input_handler() = default;
};




#endif /* SRC_INPUT_HANDLER_H_ */
