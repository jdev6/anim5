#include <allegro5/allegro.h>
#include "anim5.h"

anim5_grid anim5_new_grid(int frame_w, int frame_h, int left, int top, int border) {
    return (anim5_grid) {frame_w, frame_h, left, top, border};
}

anim5_animation* _anim5_new_animation(ALLEGRO_BITMAP* bitmap, double duration, anim5_grid grid, anim5_tiles tiles) {
    anim5_animation* anim = al_malloc(sizeof(anim5_animation)); //allocate animation
    anim->duration = duration;
    anim->timer = 0;
    anim->position = 0;
    anim->bitmap = bitmap;

    anim5_tile tile = {0,0};
    int i = 0;
    while (1) {
        tile = tiles[i];
        if (tile.x == -1 && tile.y == -1) //end of frames
            break;
        //coords in the bitmap from the grid
        int x = grid.left + tile.x * grid.frame_w + grid.border * tile.x;
        int y = grid.top  + tile.y * grid.frame_h + grid.border * tile.y;
        //create frame
        anim->frames[i++] = (anim5_frame){.x = x, .y = y, .w = grid.frame_w, .h = grid.frame_h};
    }
    anim->frame_count = i-1;

    return anim;
}

void anim5_destroy_animation(anim5_animation* anim) {
    al_free(anim);
}


void anim5_advance_timer(anim5_animation* anim, double t) {
    anim->timer += t;
    if (anim->timer >= anim->duration) {
        //frame ended
        anim->timer = 0;
        anim->position++;
    }
    if (anim->position > anim->frame_count) {
        //repeat animation
        anim->position = 0;    
    }
}

void anim5_draw_animation(anim5_animation* anim, float x, float y, int flags) {
    anim5_frame frame = anim->frames[anim->position];
    al_draw_bitmap_region(anim->bitmap, frame.x, frame.y, frame.w, frame.h, x, y, flags);
}
