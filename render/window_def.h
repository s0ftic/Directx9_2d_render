#pragma once
#include "include.h"

#ifndef WINDOW_DEF_H
#define WINDOW_DEF_H

struct WindowPropertys
{
	const char* name;
	size_t size_w;
	size_t size_h;
	int start_pos_x;
	int start_pos_y;
	DWORD flags;
};

#endif // !WINDOW_DEF_H
