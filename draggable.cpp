#include "include\gui.h"
#include "interp.h"
#include <iostream>

Draggable::Draggable(){
	typeID = InterfaceID::DRAG;
	rect = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2, 64, 64};
	step = 0.0f;
	isDragging = isDisabled = false;
	text = "";
	text.pos.x = rect.x + rect.width / 2;
	text.pos.y = rect.y + rect.height / 2;
}


Draggable::Draggable(const Vector2 &pos, const Vector2 &size, const Color &on, const Color &off){
	typeID = InterfaceID::DRAG;
	rect = {pos.x, pos.y, size.x, size.y};
	step = 0.0f;
	isDragging = isDisabled = false;
	colorOn = on;
	colorOff = off;
	text = "";
	text.pos.x = rect.x + rect.width / 2;
	text.pos.y = rect.y + rect.height / 2;
}


Draggable::Draggable(const Vector2 &pos, const Vector2 &size, const Color &on, const Color &off, const std::string &s){
	typeID = InterfaceID::DRAG;
	rect = {pos.x, pos.y, size.x, size.y};
	step = 0.0f;
	isDragging = isDisabled = false;
	colorOn = on;
	colorOff = off;
	text = "";
	text.pos.x = rect.x + rect.width / 2;
	text.pos.y = rect.y + rect.height / 2;
	text = s;
}


void InitDraggable(Draggable &d, const Vector2 &pos, const Vector2 &size, const Color &on, const Color &off, const std::string &s){
	d.rect.x = pos.x;
	d.rect.y = pos.y;
	d.rect.width = size.x;
	d.rect.height = size.y;
	d.colorOn = on;
	d.colorOff = off;
	d.text = s;
}


void CheckLPressed(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON)){
		Vector2 mousePos = GetMousePosition();
		if(CheckCollisionPointRec(mousePos, d.rect)){
			d.isDragging = true;
			d.offset = {mousePos.x - d.rect.x, mousePos.y - d.rect.y};
			if(d.anchor)
				d.anchor->isOccupied = false;
			d.anchor = nullptr;
			d.step = 0.0f;
		}
	}
}


void CheckRPressed(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonPressed(MouseButton::MOUSE_RIGHT_BUTTON)){
		Vector2 mousePos = GetMousePosition();
		if(CheckCollisionPointRec(mousePos, d.rect)){
			d.isDragging = true;
			d.offset = {mousePos.x - d.rect.x, mousePos.y - d.rect.y};
			if(d.anchor)
				d.anchor->isOccupied = false;
			d.anchor = nullptr;
			d.step = 0.0f;
		}
	}
}

//Check if button has been held 
void CheckLDown(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonDown(MouseButton::MOUSE_LEFT_BUTTON)){
		if(CheckCollisionPointRec(GetMousePosition(), d.rect)){
			d.isDragging = true;
		}
	}
}

//Check if button has been held 
void CheckRDown(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonDown(MouseButton::MOUSE_RIGHT_BUTTON)){
		if(CheckCollisionPointRec(GetMousePosition(), d.rect)){
			d.isDragging = true;
		}
	}
}

//Check if button released
void CheckLReleased(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonReleased(MouseButton::MOUSE_LEFT_BUTTON)){
		d.isDragging = false;
	}
}

//Check if button released
void CheckRReleased(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonReleased(MouseButton::MOUSE_RIGHT_BUTTON)){
		d.isDragging = false;
	}
}

//Check if button has been released
void CheckLUp(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonUp(MouseButton::MOUSE_LEFT_BUTTON)){
		d.isDragging = false;
	}
}

//Check if button has been released
void CheckRUp(Draggable &d){
	if(d.isDisabled)
		return;
	if(IsMouseButtonUp(MouseButton::MOUSE_RIGHT_BUTTON)){
		d.isDragging = false;
	}
}


void CheckLClickEvent(Draggable &d){
	CheckLDown(d);
	CheckLPressed(d);
	CheckLReleased(d);
	CheckLUp(d);
	if(d.isDragging)
		Drag(d);
}


void CheckRClickEvent(Draggable &d){
	CheckRDown(d);
	CheckRPressed(d);
	CheckRReleased(d);
	CheckRUp(d);
}


void Drag(Draggable &d){
	Vector2 mouse = GetMousePosition();
	Vector2 pos = {mouse.x - d.offset.x, mouse.y - d.offset.y};
	d.rect = {pos.x, pos.y, d.rect.width, d.rect.height};
}


void LinearSnap(Draggable &d, Anchor &anchor){
	if(CheckCollisionPointRec(anchor.pos, d.rect)){
		if(!anchor.isOccupied){
			anchor.isOccupied = true;
			d.anchor = &anchor;
		}
	}

	if(!d.anchor)
		return;
	
	d.step += 0.1f; //For now it is 10%

	Vector2 curr = {d.rect.x + d.rect.width / 2, d.rect.y + d.rect.height / 2};
	Vector2 pos = Lerp(d.step, curr, d.anchor->pos);

	d.rect.x = pos.x - d.rect.width / 2;
	d.rect.y = pos.y - d.rect.height / 2;
}


void LinearSnap(Draggable &d, Vec<Anchor> &anchors){
	if(!d.isDragging){
		for(size_t i = 0; i < anchors.size(); ++i){
			LinearSnap(d, anchors[i]);
			if(d.anchor)
				return;
		}
	}
}


void LinearSnap(Draggable &d, Vec<Anchor *> &anchors){
	if(!d.isDragging){
		for(size_t i = 0; i < anchors.size(); ++i){
			LinearSnap(d, *anchors[i]);
			if(d.anchor)
				return;
		}
	}
}


void LinearSnap(Vec<Interface *> &interfs, Vec<Anchor *> &anchors){
	for(size_t i = 0; i < interfs.size(); ++i){
		if(interfs[i] && interfs[i]->typeID == InterfaceID::DRAG){
			LinearSnap(*static_cast<Draggable *>(interfs[i]), anchors);
		}
	}
}
