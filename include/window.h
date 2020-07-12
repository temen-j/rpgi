#ifndef WINDOW_H
#define WINDOW_H

#include <algorithm>

#include "raylib\raylib.h"

const int SCREENWIDTH = 960;
const int SCREENHEIGHT = 640;

struct Window{
	static RenderTexture rescaleTarget;
	static float scale;
};

enum InterfaceID: unsigned char{
	INTERFACE_NONE,
	DRAGGABLE,
	ELEMINO
};

struct Mouse{
	Vector2 pos;
	InterfaceID interface = InterfaceID::INTERFACE_NONE;
	void *touch = nullptr;
};

Vector2 ScreenCenter();

Vector2 Clamp(Vector2 &, Vector2, Vector2);

void Update(Mouse &);

#endif
