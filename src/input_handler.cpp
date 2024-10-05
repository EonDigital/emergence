/**
 * Copyright Carl Kelso, Oct 4, 2024.  All Rights Reserved.
 */

#include "input_handler.h"

#include <unordered_map>
#include <utility>

class input_handler_impl : public input_handler {

public:
    retcode_t register_keypress( ubutton_t button, keypress_handler_fp handler, void * context ) override;
    retcode_t register_axis( ubutton_t button, axis_handler_fp handler, void * context ) override;
    retcode_t register_axis2d( ubutton_t button, axis2d_handler_fp handler, void * context ) override;

    retcode_t keypress( ubutton_t button ) const override;
    retcode_t axis( ubutton_t button, int32_t pos ) const override;
    retcode_t axis2d( ubutton_t button, int32_t posx, int32_t posy ) const override;

    retcode_t unregister_keypress( ubutton_t button ) override;
    retcode_t unregister_axis( ubutton_t button ) override;
    retcode_t unregister_axis2d( ubutton_t button ) override;

    virtual ~input_handler_impl() = default;

private:


    std::unordered_map<ubutton_t, std::pair<keypress_handler_fp,void*>> keypress_handlers;
    std::unordered_map<ubutton_t, std::pair<axis_handler_fp,void*>> axis_handlers;
    std::unordered_map<ubutton_t, std::pair<axis2d_handler_fp,void*>> axis2d_handlers;
};

input_handler * input_handler::create_handler() {
    return new input_handler_impl();
}

void input_handler::cleanup_handler( input_handler ** handler ) {
    if ( handler && *handler ) {
        delete *handler;
        handler = nullptr;
    }
}



retcode_t input_handler_impl::register_keypress( ubutton_t button, keypress_handler_fp handler, void * context ) {
    retcode_t result = RET_SUCCESS;
    auto iter = keypress_handlers.find(button);
    if ( iter == keypress_handlers.end() ) {
        keypress_handlers.emplace( button, std::make_pair(handler, context) );
    } else {
        iter->second = std::make_pair(handler, context);
        result = RET_OVERWRITTEN;
    }
    return result;
}

retcode_t input_handler_impl::register_axis( ubutton_t button, axis_handler_fp handler, void * context ) {
    retcode_t result = RET_SUCCESS;
    auto iter = axis_handlers.find(button);
    if ( iter == axis_handlers.end() ) {
        axis_handlers.emplace( button, std::make_pair(handler, context) );
    } else {
        iter->second = std::make_pair(handler, context);
        result = RET_OVERWRITTEN;
    }
    return result;
}

retcode_t input_handler_impl::register_axis2d( ubutton_t button, axis2d_handler_fp handler, void * context ) {
    retcode_t result = RET_SUCCESS;
    auto iter = axis2d_handlers.find(button);
    if ( iter == axis2d_handlers.end() ) {
        axis2d_handlers.emplace( button, std::make_pair(handler, context) );
    } else {
        iter->second = std::make_pair(handler, context);
        result = RET_OVERWRITTEN;
    }
    return result;
}


retcode_t input_handler_impl::keypress( ubutton_t button ) const {
    retcode_t result = RET_SUCCESS;
    auto iter = keypress_handlers.find(button);
    if ( iter == keypress_handlers.end() ) {
        result = RET_EMPTY;
    } else {
        iter->second.first( get_universal_button_action( button ), iter->second.second );
        result = RET_SUCCESS;
    }
    return result;
}

retcode_t input_handler_impl::axis( ubutton_t button, int32_t pos ) const {
    retcode_t result = RET_SUCCESS;
    auto iter = axis_handlers.find(button);
    if ( iter == axis_handlers.end() ) {
        result = RET_EMPTY;
    } else {
        iter->second.first( get_universal_button_action( button ), pos, iter->second.second );
        result = RET_SUCCESS;
    }
    return result;
}

retcode_t input_handler_impl::axis2d( ubutton_t button, int32_t posx, int32_t posy ) const {
    retcode_t result = RET_SUCCESS;
    auto iter = axis2d_handlers.find(button);
    if ( iter == axis2d_handlers.end() ) {
        result = RET_EMPTY;
    } else {
        iter->second.first( get_universal_button_action( button ), posx, posy, iter->second.second );
        result = RET_SUCCESS;
    }
    return result;
}


retcode_t input_handler_impl::unregister_keypress( ubutton_t button ) {
    retcode_t result = RET_SUCCESS;
    auto iter = keypress_handlers.find(button);
    if ( iter == keypress_handlers.end() ) {
        result = RET_EMPTY;
    } else {
        keypress_handlers.erase(iter);
    }
    return result;
}

retcode_t input_handler_impl::unregister_axis( ubutton_t button ) {
    retcode_t result = RET_SUCCESS;
    auto iter = axis_handlers.find(button);
    if ( iter == axis_handlers.end() ) {
        result = RET_EMPTY;
    } else {
        axis_handlers.erase(iter);
    }
    return result;
}

retcode_t input_handler_impl::unregister_axis2d( ubutton_t button ) {
    retcode_t result = RET_SUCCESS;
    auto iter = axis2d_handlers.find(button);
    if ( iter == axis2d_handlers.end() ) {
        result = RET_EMPTY;
    } else {
        axis2d_handlers.erase(iter);
    }
    return result;
}





