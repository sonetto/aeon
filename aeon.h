#pragma once

typedef struct {
    FT_Face ft_face;

    unsigned max_glyph_width;
    unsigned max_glyph_height;

    void *bitmap;

    unsigned bitmap_width;
    unsigned bitmap_height;

    unsigned pen_x;
    unsigned pen_y;
} aeon_op;

typedef struct {
} aeon_glyph_info;

void aeon_bitmap_alloc(aeon_op *, unsigned);

int aeon_render(aeon_op *, aeon_glyph_info *, unsigned);
