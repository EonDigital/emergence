/**
 * Copyright Carl Kelso, Oct 4, 2024.  All Rights Reserved.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "core_types.h"
#include "support_sdl.h"
#include "simple_logger.h"

enum {
    default_h = 480,
    default_w = 640,
    default_x = SDL_WINDOWPOS_CENTERED,
    default_y = SDL_WINDOWPOS_CENTERED,

    default_image_init_flags = IMG_INIT_PNG,

    // Prevent absurd input blocking
    default_poll_limit = 1000,
};

const char default_sprite_sheet[] = "res/sprites.png";

typedef struct {
    SDL_Window * win;
    SDL_Renderer * renderer;
    SDL_Texture * sprite_sheet;
} system_t;

system_t sys;

retcode_t video_init() {
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, EM_SCALE_QUALITY_NEAREST);

    // Setup our window
    sys.win = SDL_CreateWindow("Emergence",
                               default_x, default_y,
                               default_w, default_h,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );
    if ( !sys.win ) { return RET_NULL | RET_GROUP_VIDEO; }
    // Window flags to consider:
    // RESIZABLE, MAXIMIZED, FULLSCREEN, FULLSCREEN_DESKTOP, INPUT_GRABBED, ALLOW_HIGHDPI
    // This is where Vulkan or OpenGL might apply...
    // https://wiki.libsdl.org/SDL2/SDL_CreateWindow


    // Setup our renderer
    sys.renderer = SDL_CreateRenderer(
        sys.win, EM_NEXT_AVAILABLE_RENDERER, SDL_RENDERER_ACCELERATED );
    // Renderer flags to consider:
    // SOFTWARE, ACCELERATED, PRESENTVSYNC, TARGETTEXTURE (this could be helpful...)
    // TODO: Consider fallback to SOFTWARE if this fails...
    if ( !sys.renderer ) { return RET_NULL | RET_GROUP_RENDERER; }

    sdl_error_t err = EM_SetRenderDrawColor( sys.renderer, 0xFFFFFFFF );
    if ( sdl_error_is_failure(err) ) {
        LOG_ERROR("Couldn't initialize the draw color");
    }

    return RET_SUCCESS;
}

SDL_Texture * load_texture_from_file( SDL_Renderer * renderer, const char name[] ) {
    // Load our sprite sheet... likely need to move this to handle multiple, but for now this is fine.
    SDL_Surface * surface = IMG_Load( name );
    SDL_Texture * texture = NULL;
    if ( surface ) {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );
    }
    return texture;
}

retcode_t video_cleanup() {

    // Do this in the reverse order of video_init

    if ( sys.renderer ) {
        SDL_DestroyRenderer( sys.renderer );
        sys.renderer = NULL;
    }

    if ( sys.win ) {
        SDL_DestroyWindow( sys.win );
        sys.win = NULL;
    }
    return RET_SUCCESS;
}

retcode_t image_init() {
    // Support image file handling
    uint32_t imgsupport = IMG_Init( default_image_init_flags );

    return (imgsupport == default_image_init_flags) ? RET_SUCCESS : RET_UNSUPPORTED | RET_GROUP_IMAGE;
}

retcode_t image_cleanup() {
    if ( sys.sprite_sheet ) {
        SDL_DestroyTexture(sys.sprite_sheet);
    }

    IMG_Quit();

    return RET_SUCCESS;
}

int main( int argc, char ** argv ) {
    (void) argc; (void) argv;
    SDL_Init( SDL_INIT_VIDEO );

    video_init();

    image_init();
    sys.sprite_sheet = load_texture_from_file( sys.renderer, default_sprite_sheet );

    bool running = true;
    while( running ) {
        SDL_Event event;

        int poll_limit = default_poll_limit;
        while ( poll_limit && SDL_PollEvent( &event ) != 0 ) {
            switch ( event.type ) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYUP:
                if ( event.key.keysym.sym == SDLK_q ) {
                    running = false;
                }
                break;
            }
        }

        SDL_RenderClear( sys.renderer );
        SDL_RenderCopy(sys.renderer, sys.sprite_sheet, NULL, NULL);
        SDL_RenderPresent( sys.renderer );
    }

    image_cleanup();

    video_cleanup();

    SDL_Quit();
}
