#include "include\window.h"

float Window::scale = 1.f;
RenderTexture2D Window::rescaleTarget;

Vector2 ScreenCenter(){
	return {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
}

Vector2 Clamp(const Vector2 &v, Vector2 min, Vector2 max){
    Vector2 result = v;
    result.x = (result.x > max.x)? max.x : result.x;
    result.x = (result.x < min.x)? min.x : result.x;
    result.y = (result.y > max.y)? max.y : result.y;
    result.y = (result.y < min.y)? min.y : result.y;
    return result;
}

void Update(Mouse &mouse){
	Vector2 mouseWindowPos = GetMousePosition();
	mouse.pos = (Vector2){0, 0};
	mouse.pos.x = (mouseWindowPos.x - (GetScreenWidth() - (SCREENWIDTH * Window::scale)) * .5f) / Window::scale;
	mouse.pos.y = (mouseWindowPos.y - (GetScreenHeight() - (SCREENHEIGHT * Window::scale)) * .5f) / Window::scale;
	mouse.pos = Clamp(mouse.pos, (Vector2){0, 0}, (Vector2){SCREENWIDTH, SCREENHEIGHT});
}

void UpdateWindow(){
	Window::scale = std::min((float)GetScreenWidth()/SCREENWIDTH, (float)GetScreenHeight()/SCREENHEIGHT);
}

void WindowSetup(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
    /* SetConfigFlags(FLAG_WINDOW_RESIZABLE); */
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "RPG Window");
	SetWindowMinSize(SCREENWIDTH, SCREENHEIGHT);

	Window::rescaleTarget = LoadRenderTexture(SCREENWIDTH, SCREENHEIGHT);
	SetTextureFilter(Window::rescaleTarget.texture, FILTER_BILINEAR);
}


