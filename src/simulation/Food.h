#pragma once
#include <raylib.h>

class Food {
public:
  Food(int p_xpos, int p_ypos);
  void render();
  int get_x_pos();
  int get_y_pos();

  private:
  int m_xpos;
  int m_ypos;
  float m_energy = 0.50;
};