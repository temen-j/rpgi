#include "include\gui.h"

Menu::Menu(){
	//interfs.resize(16);
	//nchors.resize(16);
	for(size_t i = 0; i < interfs.size(); ++i)
		interfs[i] = nullptr;
	for(size_t i = 0; i < anchors.size(); ++i)
		anchors[i] = nullptr;
	rect = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2, 192, 192};
	color = GRAY;
	text = "";
}

Menu::~Menu(){
	for(size_t i = 0; i < interfs.size(); ++i){
		if(interfs[i])
			delete interfs[i];
		interfs[i] = nullptr;
	}

	for(size_t i = 0; i < anchors.size(); ++i){
		if(anchors[i])
			delete anchors[i];
		anchors[i] = nullptr;
	}
}


Menu::Menu(const Vector2 &pos, const Vector2 &size, const Color &col){
	interfs.resize(16);
	anchors.resize(16);
	for(size_t i = 0; i < interfs.size(); ++i)
		interfs[i] = nullptr;
	for(size_t i = 0; i < anchors.size(); ++i)
		anchors[i] = nullptr;
	rect = {pos.x, pos.y, size.x, size.y};
	color = col;
	text = "";
}


Menu::Menu(const Vector2 &pos, const Vector2 &size, const Color &col, const std::string &s){
	interfs.resize(16);
	anchors.resize(16);
	for(size_t i = 0; i < interfs.size(); ++i)
		interfs[i] = nullptr;
	for(size_t i = 0; i < anchors.size(); ++i)
		anchors[i] = nullptr;
	rect = {pos.x, pos.y, size.x, size.y};
	color = col;
	text = s;
}


void CheckLClickEvent(Menu &m){
	for(uint32_t i = 0; i < m.interfs.size(); ++i){
		if(m.interfs[i]){
			switch(m.interfs[i]->typeID){
				case InterfaceID::BUTTON:
					CheckLClickEvent(*static_cast<Button *>(m.interfs[i]));
					break;/*
				case InterfaceID::TOGGLE:
					CheckLClickEvent((Toggle)*m.interfs[i]);
					break;*/
				case InterfaceID::DRAG:
					CheckLClickEvent(*static_cast<Draggable *>(m.interfs[i]));
					break;
				case InterfaceID::MENU:
					CheckLClickEvent(*static_cast<Menu *>(m.interfs[i]));
					break;
			}
		}
	}
}

void CheckRClickEvent(Menu &m){
	for(uint32_t i = 0; i < m.interfs.size(); ++i){
		if(m.interfs[i]){
			switch(m.interfs[i]->typeID){
				case InterfaceID::BUTTON:
					CheckLClickEvent(*static_cast<Button *>(m.interfs[i]));
					break;/*
				case InterfaceID::TOGGLE:
					CheckLClickEvent((Toggle)*m.interfs[i]);
					break;*/
				case InterfaceID::DRAG:
					CheckLClickEvent(*static_cast<Draggable *>(m.interfs[i]));
					break;
				case InterfaceID::MENU:
					CheckLClickEvent(*static_cast<Menu *>(m.interfs[i]));
					break;
			}
		}
	}
}

