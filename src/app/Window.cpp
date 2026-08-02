#include "Window.h"
#include <raylib.h>

void Window::init(int p_width, int p_height, const char *p_title) {
  m_width = p_width;
  m_height = p_height;
  InitWindow(p_width, p_height, p_title);
}

void Window::close() { CloseWindow(); }