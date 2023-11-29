#include "CustomColor.h"

// 0: 검은색, 1: 흰색
sf::Color CustomColor::Gray(float brightness) {
    return sf::Color(
        (int) 255 * brightness, 
        (int) 255 * brightness,
        (int) 255 * brightness,
        255
    );
}
