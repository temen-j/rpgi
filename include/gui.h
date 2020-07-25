#pragma once
#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "window.h"
#include "sprite.h"
#include "interp.h"
#include "elemino.h"
#include "console.h"
#include "gamestate.h"

#include "raylib\raylib.h"
#include "raylib\raygui.h"

struct Anchor;
struct Elemino;
struct Grid;
struct Console;
struct Player;
struct InventoryData;
struct Move;
struct MoveInventoryData;

#ifndef EXTRA_COLORS
#define CLEAR (Color){0,0,0,0}
#define GRIDON (Color){237,218,189,255}
#define GRIDOFF (Color){119,109,95,255}
#define FIRECOLOR (Color){ 255, 100, 0, 255 }
#define WATERCOLOR (Color){ 0, 100, 255, 255 }
#define NATURECOLOR (Color){ 0, 192, 0, 255 }
#define LIGHTNINGCOLOR (Color){ 160, 160, 0, 255 }
#define METALCOLOR (Color){ 152, 168, 192, 255 }
#define ROCKCOLOR (Color){ 128, 96, 32, 255 }
#define SPECTRECOLOR (Color){ 128, 0, 196, 255 }
#define HPGOODCOLOR (Color){224, 48, 80, 255}
#define MPGOODCOLOR (Color){80, 48, 224, 255}
#define HPBADCOLOR (Color){112, 68, 75, 255}
#define MPBADCOLOR (Color){75, 68, 112, 255}
#endif

template<typename T>
using Vec = std::vector<T>;

struct GlobalTextData{
	Font defaultFont;
	int fontSize;
	Image imageText;
};

/* enum InterfaceID: unsigned char{ */
/* 	INTERFACE_NONE, */
/* 	DRAGGABLE, */
/* 	ELEMINO */
/* }; */

struct Interface{
	InterfaceID typeID;
};

/* struct Mouse{ */
/* 	Vector2 pos; */
/* 	InterfaceID interface = InterfaceID::INTERFACE_NONE; */
/* 	void *touch = nullptr; */
/* }; */

struct Panel{
	GuiControlState state = GuiControlState::GUI_STATE_NORMAL;
	Rectangle bounds;
};

struct Label{
    GuiControlState state = GuiControlState::GUI_STATE_NORMAL;
	Rectangle bounds;
	std::string text;
	bool disabled = false;
};

struct ImageLabel : Label{
	Rectangle texBounds;
	Texture tex;
};

struct BoxLabel : Label{
	Rectangle bgBounds;
	Color bgColor;
	Color textColor;
};

struct Button{
    GuiControlState state = GUI_STATE_NORMAL;
    bool pressed = false;
	Rectangle bounds;
	std::string text;
};

struct ImageButton : Button{
	Texture texture;
};

struct Toggle{
    GuiControlState state;
    bool active = false;
	Rectangle bounds;
	std::string text;
};

struct ImageToggle : Toggle{
	Texture texture;
};

struct ScrollBar{
	GuiControlState state;
	Rectangle bounds;
	int value;
	int minValue;
	int maxValue;
	bool isVertical;
	int range;
	int spinnerSize;
	int sliderSize;
    // Arrow buttons [<] [>] [∧] [∨]
    Rectangle arrowUpLeft = { 0 };
    Rectangle arrowDownRight = { 0 };
    // Actual area of the scrollbar excluding the arrow buttons
    Rectangle scrollbar = { 0 };
    // Slider bar that moves     --[///]-----
    Rectangle slider = { 0 };
	ScrollBar(){
		state = GuiControlState::GUI_STATE_NORMAL;
	};
};

struct ListView{
	GuiControlState state;
	ScrollBar scrollbar;
	Rectangle bounds;
	Rectangle itemBounds;
	Vec<std::string> text;
	int focus;
	int scrollIndex;
	int active;
	int itemFocused;
	bool useScrollBar;
	int visibleItems;
	int startIndex, endIndex;
	ListView(){
		state = GuiControlState::GUI_STATE_NORMAL;
	}
};

struct DropDown{
	GuiControlState state;
	Panel panel;
	Rectangle bounds;
	Rectangle itemBounds;
	Vec<std::string> text;
	int active;
	int focus;
	bool editMode;

	DropDown(){
		state = GuiControlState::GUI_STATE_NORMAL;
		editMode = false;
		active = 0;
		focus = 0;
	}
};

struct InventoryPortraits{
	ImageToggle toggles[4];
};

struct CombatPortraits{
	Vec<ImageToggle> toggles;
};


struct StatBar{
	float k; //Coeff of proportionality of HP/MP
	float thickness, length;
	Vector2 pos; //Origin is top left
	bool showNum;
	Color colorGood, colorBad;
};


//raygui functions ------------------------------------------------------------
void Update(Button &);
void Update(ImageButton &);
bool Update(Toggle &);
bool Update(ImageToggle &);
void Update(ScrollBar &);
void Update(ListView &);
bool Update(DropDown &);
void SetupScrollBar(ScrollBar &);
void SetupListView(ListView &);
void SetupDropDown(DropDown &);
void DrawGuiButton(Button &);
void DrawGuiLabel(Label &);
void DrawGuiBoxLabel(BoxLabel &);
void DrawGuiImageButton(ImageButton &);
void DrawGuiImageToggle(ImageToggle &);
void DrawGuiScrollBar(ScrollBar &);
void DrawGuiListView(ListView &);
void DrawGuiPanel(Panel &);
void DrawGuiDropDown(DropDown &);
//-----------------------------------------------------------------------------

//Custom gui functions ------------------------------------------------------------

Color ElementToColor(const Element &);

void DrawMouse(const Mouse &);
void DrawElemino(const Elemino &);
void DrawGrid(const Grid &);
void DrawConsole(const Console &, GlobalTextData &);
void DrawInventory(const Player &);
void DrawMoveInventory(const Player &);
void DrawStatBar(const StatBar &);

//------------------------------------------------------------------------------------


#endif
