/**
 * Copyright Carl Kelso, Oct 4, 2024.  All Rights Reserved.
 */

#ifndef SRC_SUPPORT_SDL_H_
#define SRC_SUPPORT_SDL_H_


#define EM_SCALE_QUALITY_NEAREST "0"
#define EM_SCALE_QUALITY_LINEAR "1"
#define EM_SCALE_QUALITY_BEST "2"

#define EM_NEXT_AVAILABLE_RENDERER -1

// Make it so I can change these quickly later...
#define EM_PREFERRED_END_RGBA 1
#define EM_PREFERRED_END_ABGR 0

#define EM_PREFERRED_END EM_PREFERRED_END_RGBA

static inline uint32_t make_color( uint8_t r, uint8_t g, uint8_t b, uint8_t opacity ) {
#if EM_PREFERRED_END == EM_PREFERRED_END_RGBA
    return (r << 24UL) | (g << 16) | (b << 8) | opacity;
#else
    return r | (g << 8UL) | (b << 16) | (opacity << 24);
#endif
}

#if EM_PREFERRED_END == EM_PREFERRED_END_RGBA
# define EM_SetRenderDrawColor( rend, color ) \
    SDL_SetRenderDrawColor( (rend), ( (color) >> 24 ) & 0xFF, \
                            ( (color) >> 16 ) & 0xFF, \
                            ( (color) >> 8 ) & 0xFF, \
                              (color) & 0xFF )
#else

# define EM_SetRenderDrawColor( rend, color ) \
    SDL_SetRenderDrawColor( (rend), (color) & 0xFF, \
                            ( (color) >> 8 ) & 0xFF, \
                            ( (color) >> 16 ) & 0xFF, \
                            ( (color) >> 24 ) & 0xFF )
#endif

typedef int sdl_error_t;
static bool sdl_error_is_failure( sdl_error_t err ) {
    return err < 0;
}

#endif /* SRC_SUPPORT_SDL_H_ */
