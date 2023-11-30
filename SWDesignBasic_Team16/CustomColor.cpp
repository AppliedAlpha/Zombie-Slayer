#include "CustomColor.h"

// 0: ������, 1: ���
sf::Color CustomColor::Gray(float brightness) {
    return sf::Color(
        (int) 255 * brightness, 
        (int) 255 * brightness,
        (int) 255 * brightness,
        255
    );
}
