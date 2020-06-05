#pragma once
#ifndef ELEMINO_H
#define ELEMINO_H

#define GRIDON (Color){237,218,189,255}
#define GRIDOFF (Color){119,109,95,255}

#include <vector>

#include "element.h"
#include "gui.h"
#include "tmath.h"
#include "interp.h"

#include "raylib\raylib.h"

struct Mouse;

template<typename T>
using Vec = std::vector<T>;

const unsigned int NUM_RECT = 16;
static const int RECT_WIDTH = 32;

//For dragging things around

struct Anchor{
	Vector2 pos;
	bool isOccupied = false;

	void operator=(const Vector2 &);
};

enum MinoShape{
	II,
	I,
	L,
	J,
	T,
	Z,
	S,
	O,
	ii,
	i,
	comma,
	period,
	corner
};

struct Elemino{
	static Texture eleminoTile;
	MinoShape mish;
	Rectangle rect[NUM_RECT];
	bool useRect[NUM_RECT]; //Is this using a certain rectangle in this elemino shape?

	Vector2 offset[NUM_RECT]; //Each rect from the mouse
	Vector2 pos; //Pos of the whole elemino, NOT just the indiv rects
	Vector2 startPos;
	Vector2 mOffset; //Offset from mouse to position
	Vector2 dragTo; //For later in LinearSnap

	Color color;
	Element elem;

	float step; //for interpolation
	bool dragging, disabled, aligned, snapping;
	unsigned int count;
	int iStep;

	bool inInventory = true;

	Elemino(){
		for(size_t i = 0; i < NUM_RECT; ++i){
			rect[i] = {-1, -1, 0, 0};
			useRect[i] = false;
			offset[i] = (Vector2){0,0};
		}
		mish = MinoShape::period;
		dragTo = (Vector2){0,0};
		startPos = (Vector2){0,0};
		color = (Color){192, 192, 255, 255};
		step = 0.0f;
		dragging = false;
		disabled = false;
		aligned = false;
		snapping = false;
		iStep = 0;
		elem = Element::none;
	}
	Elemino(const MinoShape &, const Element &);

};

struct MinoAnchor : Anchor{
	Elemino *occupier = nullptr;
	bool disabled = false;

	MinoAnchor(){
		occupier = nullptr;
		disabled = false;
	}
};

struct Grid{
	static Texture gridTile;
	Vector2 pos;
	MinoAnchor anchors[NUM_RECT];
	Element elem[NUM_RECT];
	Vec<Elemino *> attached;
	Color colorOn, colorOff;
	bool disabled;

	Grid(){
		disabled = true;
		pos = (Vector2){0, 0};
		//colorOn = BEIGE;
		colorOn = GRIDON;
		//TODO: Create Color operations (ex. like division)
		colorOff = GRIDOFF;
		
		for(size_t i = 0; i < NUM_RECT; ++i){
			elem[i] = Element::none;
			
			Vector2 addPos = 
				(Vector2){(float)(i % 4) * RECT_WIDTH, (float)(i / 4) * RECT_WIDTH} +
				(Vector2){RECT_WIDTH / 2, RECT_WIDTH / 2}; //Centers anchors
			anchors[i].pos = pos + addPos;
		}
	}
	~Grid(){
	}

	void UpdatePos();
	void UpdatePos(Vector2 &);
};

Color ElementToColor(const Element &);
void GetEleminoGridTextures();

void Move(Elemino &, const Vector2 &);
void MoveTo(Elemino &, const Vector2 &);

void MakeMinoShape(Elemino &e, const MinoShape &ms); //Assigns elemino rects
void MakeRectangles(Elemino &e); //Grid size
void MakeRectanglesSmall(Elemino &e); //Inventory size
void Enlarge(Elemino &e); //Make the elemino the appropriate size
void ComputeOffsets(Elemino &e, Vector2 point); //Finds the offset of each rect to mouse
bool CheckLPressed(Elemino &e, Mouse &); //Handles what happens if an elemino is clicked on
void CheckLDown(Elemino &e); //Drag this rusty bitch
void CheckLReleased(Elemino &e, Mouse &); //Stop dragging this rusty bitch
void CheckLUp(Elemino &e);
void SetClicked(Elemino &e, Mouse &mouse); //What the elmino should do when clicked on
void Drag(Elemino &e); //Moves the elemino to the mouse by an offset

void Rotate(Elemino &e);
void RotateUsedRect(Elemino &e);
//Offset e.pos such that the axis of rot stays at mouse position
void OffsetRotAxis(Elemino &e);

unsigned int Overlap(const Elemino &, const Grid &); //Returns # of overlapping rects
Vector2 Occupy(Elemino &, Grid &); //Returns offset from occupied anchor to e.rect
void Snap(Elemino &, Grid &);
void SnapTo(Elemino &, Grid &);
void SnapToLinear(Elemino &, Grid &);
void EleminoSnap(Elemino &);

void Unoccupy(Grid &);

#endif
