# anim5

a animation libraery for allegro5. http://liballeg.org/

inspired bye https://github.com/kikito/anim8

# documentation

exampple

```c
//iinitialiazion
ALLEGRO_BITMAP* bmp = al_load_bitmap("sheet.bmp");

anim5_grid grid = anim5_new_grid(16,16, 0,0,0); //to divide sheet into 16x16 tiles with 0 off set and 0 border

//This line, crates animation with bmp and grid, each frame takes 0.1 seconds and it uses tiles 0,0 and 0,1 of the sheet
anim5_animation anim = anim5_new_animation(bmp, 0.1, grid, {0,0}, {0,1});

//.......

while (1) {
	//main game loop,get deltatime some how
	anim5_advance_timer(anim, delta_time);
	//...
	//to draw
	anim5_draw_animation(anim, 100, 200, 0);
}

//THIS DOS not FREE THE BMP. must be freed by yourself
anim5_destroy_animation(anim);
al_destroy_bitmap(bmp);
//quit other stuff...
```

functions

`anim5_grid anim5_new_grid(int frame_w, int frame_h, int left, int top, int border)`

returns GRID used for creating animation, frame\_w/h: frame width/height; left and top are for left and top offsets and border is border between tiles

`anim5_animation* anim5_new_animation(bitmap, duration, grid, tiles)`

**macro** to create animation, wrapper over `_anim5_new_animation(ALLEGRO_BITMAP* bmp, double duration, anim5_grid grid, anim5_tile tiles[ANIM5_MAX_FRAMES])`. this function exects a tile of {-1,-1} at the end for separator witch is given by the macro. if not, it WIll porbably segfault. and `ANIM5_MAX_FRAMES` is a macro you can define it in the command line also when compiling but its defaults to 64

`void anim5_destroy_animation(anim5_animation* anim)`

frees animation BUT NOT the bitmap..

`void anim5_advance_timer(anim5_animation* anim, double t)`

advances timer of anim, by t which can be delta time, or IN FIXED frame rate game even could just be 1; then durations are in frames of lenth

`void anim5_draw_animation(anim5_animation* anim, float x, float y, int flags)`

draws animatinon as in al\_draw\_bitmap[http://liballeg.org/a5docs/trunk/graphics.html#al_draw_bitmap]
