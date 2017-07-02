#ifndef _ANIM5_H
#define _ANIM5_H

#include <allegro5/allegro.h>

#ifndef ANIM5_MAX_FRAMES
    #define ANIM5_MAX_FRAMES 64
#endif

typedef struct {
    int frame_w;
    int frame_h;
    int left;
    int top;
    int border;
} anim5_grid;

//these are for drawing
typedef struct {
    int x;
    int y;
    int w;
    int h;
} anim5_frame;
typedef anim5_frame anim5_frames[ANIM5_MAX_FRAMES];

typedef struct {
    double duration; //of each frame
    double timer;
    int position;
    int frame_count;
    ALLEGRO_BITMAP* bitmap;
    anim5_frames frames;
} anim5_animation;

//these are just for creating the animation (used by _anim5_new_animation)
typedef struct {
    int x;
    int y;
} anim5_tile;
typedef anim5_tile anim5_tiles[ANIM5_MAX_FRAMES];

anim5_grid anim5_new_grid(int frame_w, int frame_h, int left, int top, int border);
anim5_animation* _anim5_new_animation(ALLEGRO_BITMAP* bitmap, double duration, anim5_grid grid, anim5_tiles tiles);
//wrapper macro

#define anim5_new_animation(bmp, d, g, ...) _anim5_new_animation(bmp, d, g, (anim5_tiles){ __VA_ARGS__, {-1,-1} } )

void anim5_destroy_animation(anim5_animation* anim);
void anim5_advance_timer(anim5_animation* anim, double t);
void anim5_draw_animation(anim5_animation* anim, double x, double y, int flags);

#endif
