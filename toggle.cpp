#include "include\gui.h"

Toggle::Toggle(){
	typeID = InterfaceID::TOGGLE;
	rect = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2, 64, 64};
	isActivated = isDisabled = false;
}


Toggle::Toggle(const Vector2 &pos, const Vector2 &size, const Color &on, const Color &off){
	typeID = InterfaceID::TOGGLE;
	rect = {pos.x, pos.y, size.x, size.y};
	colorOn = on;
	colorOff = off;
	isActivated = isDisabled = false;
}


Toggle::Toggle(const Vector2 &pos, const Vector2 &size, const Color &on, const Color &off, const std::string &s){
	typeID = InterfaceID::TOGGLE;
	rect = {pos.x, pos.y, size.x, size.y};
	colorOn = on;
	colorOff = off;
	isActivated = isDisabled = false;
	text = s;
}


void CheckLPressed(Toggle &b){
	if(b.isDisabled)
		return;
	if(IsMouseTogglePressed(MouseButton::MOUSE_LEFT_BUTTON)){
		if(CheckCollisionPointRec(GetMousePosition(), b.rect)){
			b.isActivated = !b.isActivated;
		}
	}
}


void CheckRPressed(Toggle &b){
	if(b.isDisabled)
		return;
	if(IsMouseTogglePressed(MouseButton::MOUSE_RIGHT_BUTTON)){
		if(CheckCollisionPointRec(GetMousePosition(), b.rect)){
			b.isActivated = !b.isActivated;
		}
	}
}


//Check if button has been held 
void CheckLDown(Toggle &b){
	return;
}

//Check if button has been held 
void CheckRDown(Toggle &b){
	return;
}


//Check if button released
void CheckLReleased(Toggle &b){
	return;
}

//Check if button released
void CheckRReleased(Toggle &b){
	return;
}

//Check if button has been released
void CheckLUp(Toggle &b){
	return;
}

//Check if button has been released
void CheckRUp(Toggle &b){
	return;
}


void CheckLClickEvent(Toggle &b){
	CheckLDown(b);
	CheckLPressed(b);
	CheckLReleased(b);
	CheckLUp(b);
}


void CheckRClickEvent(Toggle &b){
	CheckRDown(b);
	CheckRPressed(b);
	CheckRReleased(b);
	CheckRUp(b);
}

