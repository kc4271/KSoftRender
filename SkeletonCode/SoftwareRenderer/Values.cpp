#include "FrameBuffer.h"
#include "globals.h"
#include "Scene.h"

FrameBuffer g_fb(window_width, window_height);
Color g_color(255,255,255);
int g_w = window_width;
int g_h = window_height;
Scene scene;