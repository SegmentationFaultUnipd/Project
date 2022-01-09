#ifndef COLOR_H
#define COLOR_H

namespace chess {
    enum Color {
        WHITE,
        BLACK
    };

    inline Color opposite(Color color) {
        return color == WHITE ? BLACK : WHITE;
    }
}

#endif //COLOR_H