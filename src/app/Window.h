#pragma once

class Window {
public:
    void init(int p_width, int p_height, const char *p_title);
    void close();

private: 
    int m_width;
    int m_height;
};