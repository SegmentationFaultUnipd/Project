/**
 * @file Color.h
 * @author Filippo Mazzarotto
 * @date 2022-01-23
 */

#ifndef COLOR_H
#define COLOR_H

namespace chess {
    enum Color {
        WHITE,
        BLACK
    };

	static const std::string COLOR_NAMES[] = { "BIANCO", "NERO" };

    inline Color opposite(Color color) {
        return color == WHITE ? BLACK : WHITE;
    }
}

#endif //COLOR_H