#include <assert.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "aeon.h"

#define return_if(error) ({ \
    typeof(error) _error = error; \
    \
    if(error) { \
        return error; \
    } \
})

void bitblit(
    void *target,
    unsigned target_width,
    const void *source,
    unsigned source_width,
    unsigned source_height,
    unsigned x,
    unsigned y
) {
    unsigned i;

    target = (char *)(target) + (target_width * y) + x;

    for(i = 0; i < source_height; ++i) {
        memcpy(target, source, source_width);
        target = (char *)(target) + target_width;
        source = (const char *)(source) + source_width;
    }
}

void aeon_bitmap_alloc(aeon_op *op, unsigned glyph_count) {
    assert(NULL && "Not implemented.");
}

int aeon_render(
    aeon_op *op,
    aeon_glyph_info *glyph_info,
    unsigned charcode
) {
    FT_Error ft_error;
    FT_Face ft_face = op->ft_face;
    FT_Bitmap *ft_bitmap;

    void *op_bitmap = op->bitmap;
    unsigned op_bitmap_width = op->bitmap_width;
    unsigned op_bitmap_height = op->bitmap_height;

    unsigned max_glyph_width = op->max_glyph_width;
    unsigned max_glyph_height = op->max_glyph_height;

    unsigned *pen_x = &op->pen_x;
    unsigned *pen_y = &op->pen_y;

    ft_error = FT_Load_Char(ft_face, charcode, FT_LOAD_RENDER);
    return_if(ft_error);

    ft_bitmap = &ft_face->glyph->bitmap;

    bitblit(
        op_bitmap,
        op_bitmap_width,
        ft_bitmap->buffer,
        ft_bitmap->width,
        ft_bitmap->rows,
        *pen_x,
        *pen_y
    );

    *pen_x += op->max_glyph_width;

    if(*pen_x + max_glyph_width > op_bitmap_width) {
        *pen_y += max_glyph_height;
        *pen_x = 0;
    }

    assert(*pen_y + max_glyph_height <= op->bitmap_height);

    return 0;
}
