#include <ft2build.h>
#include FT_FREETYPE_H
#include "aeon.h"

#define abort_on_error(where, error) ({ \
    typeof(where) _where = where; \
    typeof(error) _error = error; \
    \
    if(_error) { \
        fprintf( \
            stderr, \
            __FILE__ ":%d: %s error (%#x).\n", \
            __LINE__, \
            _where, \
            _error \
        ); \
    } \
})

const char *default_font_path = (
    "/usr/share/fonts/truetype/fonts-japanese-gothic.ttf"
);

FT_Library ft_library;
FT_Face ft_face;

void init_freetype() {
    FT_Error ft_error;

    ft_error = FT_Init_FreeType(&ft_library);;
    abort_on_error("FreeType", ft_error);
}

void load_font(
    const char *font_path,
    unsigned font_size,
    FT_Face *ft_face
) {
    FT_Error ft_error;

    ft_error = FT_New_Face(ft_library, font_path, 0, ft_face);
    abort_on_error("FreeType", ft_error);

    ft_error = FT_Set_Char_Size(*ft_face, 0, font_size * 64, 300, 300);
    abort_on_error("FreeType", ft_error);
}

int main(unsigned argc, char *argv[]) {
    unsigned glyph_columns = 16;
    unsigned glyph_rows = 1;
    unsigned bitmap_len;

    aeon_op op = {0};
    aeon_glyph_info glyph;

    FILE *f;

    init_freetype();

    load_font(
        argc >= 2
            ? argv[1]
            : default_font_path,
        16,
        &op.ft_face
    );

    op.max_glyph_width = 64;
    op.max_glyph_height = 64;

    op.bitmap_width = op.max_glyph_width * glyph_columns;
    op.bitmap_height = op.max_glyph_width * glyph_columns;

    bitmap_len = op.bitmap_width * op.bitmap_height;

    op.bitmap = malloc(bitmap_len);
    bzero(op.bitmap, bitmap_len);

    aeon_render(&op, &glyph, 0x3059);
    aeon_render(&op, &glyph, 0x308b);

    f = fopen("./bitmap.data", "wb");
    fwrite(op.bitmap, 1, bitmap_len, f);
    fclose(f);

    return 0;
}
