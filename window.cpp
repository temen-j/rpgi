#include "include\window.h"

Vector2 ScreenCenter(){
	return {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
}

Vector2 Clamp(Vector2 &v, Vector2 min, Vector2 max){
    Vector2 result = v;
    result.x = (result.x > max.x)? max.x : result.x;
    result.x = (result.x < min.x)? min.x : result.x;
    result.y = (result.y > max.y)? max.y : result.y;
    result.y = (result.y < min.y)? min.y : result.y;
    return result;
}

void Update(Mouse &mouse){
	float scale = std::min((float)GetScreenWidth()/SCREENWIDTH, (float)GetScreenHeight()/SCREENHEIGHT);
	Vector2 mouseWindowPos = GetMousePosition();
	mouse.pos = (Vector2){0, 0};
	mouse.pos.x = (mouseWindowPos.x - (GetScreenWidth() - (SCREENWIDTH * scale)) * .5f) / scale;
	mouse.pos.y = (mouseWindowPos.y - (GetScreenHeight() - (SCREENHEIGHT * scale)) * .5f) / scale;
	mouse.pos = Clamp(mouse.pos, (Vector2){0, 0}, (Vector2){SCREENWIDTH, SCREENHEIGHT});
}
