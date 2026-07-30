#include "Food.h"
#include <raylib.h>

Food::Food(int p_xpos, int p_ypos) {
  m_xpos = p_xpos;
  m_ypos = p_ypos;
}

void Food::render() { DrawCircle(m_xpos, m_ypos, 3.0F, BLUE); }

int Food::get_x_pos() {
    return m_xpos;
}

int Food::get_y_pos() {
    return m_ypos;
}