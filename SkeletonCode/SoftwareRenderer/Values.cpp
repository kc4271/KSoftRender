#include "FrameBuffer.h"
#include "globals.h"

FrameBuffer g_fb(window_width, window_height);
u08 g_color[3] = {255,255,255};
int g_w = window_width;
int g_h = window_height;