#ifndef GAME_GFX_COLOR_HPP
#define GAME_GFX_COLOR_HPP

namespace tv {
    struct Color {
        int r = 0;
        int g = 0;
        int b = 0;
        int a = 0;

        Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a){};
        Color(int rgba) {
            r = rgba >> 24;
            g = (rgba >> 16) & 0xff;
            b = (rgba >> 8) & 0xff;
            a = rgba & 0xff;
        }
    };
}

#endif // GAME_GFX_COLOR_HPP
