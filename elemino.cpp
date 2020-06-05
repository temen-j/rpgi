#include "include\elemino.h"

Texture Elemino::eleminoTile;
Texture Grid::gridTile;

void GetEleminoGridTextures(){
	Elemino::eleminoTile = LoadTexture("../img/elmntile.png");
	Grid::gridTile = LoadTexture("../img/gridtile.png");
}

Elemino::Elemino(const MinoShape &ms, const Element &el){
	for(size_t i = 0; i < NUM_RECT; ++i){
		rect[i] = {-1, -1, 0, 0};
		useRect[i] = false;
		offset[i] = (Vector2){0,0};
	}
	mish = ms;
	dragTo = (Vector2){0,0};
	color = ElementToColor(el);
	step = 0.0f;
	dragging = false;
	disabled = false;
	elem = el;

	MakeRectangles(*this);
}


void Grid::UpdatePos(){
	for(size_t i = 0; i < NUM_RECT; ++i){
		Vector2 addPos = 
			(Vector2){(float)(i % 4) * RECT_WIDTH, (float)(i / 4) * RECT_WIDTH} +
			(Vector2){RECT_WIDTH / 2, RECT_WIDTH / 2}; //Centers anchors
		anchors[i].pos = pos + addPos;
	}
}


void Grid::UpdatePos(Vector2 &p){
	pos = p;
	for(size_t i = 0; i < NUM_RECT; ++i){
		Vector2 addPos = 
			(Vector2){(float)(i % 4) * RECT_WIDTH, (float)(i / 4) * RECT_WIDTH} +
			(Vector2){RECT_WIDTH / 2, RECT_WIDTH / 2}; //Centers anchors
		anchors[i].pos = pos + addPos;
	}
}

void MakeMinoShape(Elemino &e, const MinoShape &ms){
	// 0000 0001 0010 0011
	// 0100 0101 0110 0111
	// 1000 1001 1010 1011
	// 1100 1101 1110 1111
	switch(ms){
		case MinoShape::II:
			e.count = 8;
			e.useRect[0] = e.useRect[1] = e.useRect[4] = e.useRect[5] = 
				e.useRect[8] = e.useRect[9] = e.useRect[12] = e.useRect[13] = true;
			break;
		case MinoShape::I:
			e.count = 4;
			e.useRect[0] = e.useRect[4] = e.useRect[8] = e.useRect[12] = true;
			break;
		case MinoShape::L:
			e.count = 4;
			e.useRect[0] = e.useRect[4] = e.useRect[8] = e.useRect[9] = true;
			break;
		case MinoShape::J:
			e.count = 4;
			e.useRect[1] = e.useRect[5] = e.useRect[9] = e.useRect[8] = true;
			break;
		case MinoShape::T:
			e.count = 4;
			e.useRect[1] = e.useRect[4] = e.useRect[5] = e.useRect[6] = true;
			break;
		case MinoShape::Z:
			e.count = 4;
			e.useRect[0] = e.useRect[1] = e.useRect[5] = e.useRect[6] = true;
			break;
		case MinoShape::S:
			e.count = 4;
			e.useRect[1] = e.useRect[2] = e.useRect[4] = e.useRect[5] = true;
			break;
		case MinoShape::O:
			e.count = 4;
			e.useRect[0] = e.useRect[1] = e.useRect[4] = e.useRect[5] = true;
			break;
		case MinoShape::ii:
			e.count = 6;
			e.useRect[0] = e.useRect[1] = e.useRect[4] = e.useRect[5] =
				e.useRect[8] = e.useRect[9] = true;
			break;
		case MinoShape::i:
			e.count = 3;
			e.useRect[0] = e.useRect[4] = e.useRect[8] = true;
			break;
		case MinoShape::comma:
			e.count = 2;
			e.useRect[0] = e.useRect[4] = true;
			break;
		case MinoShape::period:
			e.count = 1;
			e.useRect[0] = true;
			break;
		case MinoShape::corner:
			e.count = 3;
			e.useRect[0] = e.useRect[1] = e.useRect[4] = true;
			break;
	}
	if(e.inInventory)
		MakeRectanglesSmall(e);
	else
		MakeRectangles(e);
}


void MakeRectangles(Elemino &e){
	for(size_t i = 0; i < NUM_RECT; ++i){
		if(e.useRect[i]){
			Vector2 addPos = (Vector2){(float)(i % 4) * RECT_WIDTH, (float)(i / 4) * RECT_WIDTH};
			e.rect[i] = {e.pos.x + addPos.x, e.pos.y + addPos.y, RECT_WIDTH, RECT_WIDTH};
		}
	}
}


void MakeRectanglesSmall(Elemino &e){
	for(size_t i = 0; i < NUM_RECT; ++i){
		if(e.useRect[i]){
			Vector2 addPos = (Vector2){(float)(i % 4) * RECT_WIDTH, (float)(i / 4) * RECT_WIDTH};
			addPos = addPos / 2.f;
			float width = RECT_WIDTH / 2.f;
			float height = RECT_WIDTH / 2.f;
			e.rect[i] = {e.pos.x + addPos.x, e.pos.y + addPos.y, width, height};
		}
	}
}


void Enlarge(Elemino &e){
	e.mOffset = GetMousePosition() - e.pos;
	e.mOffset *= -1.f;
	Move(e, e.mOffset); //Position elemino relative to where it was clicked
	MakeRectangles(e);
}


void ComputeOffsets(Elemino &e, Vector2 point){
	for(size_t i = 0; i < NUM_RECT; ++i){
		if(e.useRect[i]){
			e.offset[i] = {point.x - e.rect[i].x, point.y - e.rect[i].y};
		}
	}
}

bool CheckLPressed(Elemino &e, Mouse &mouse){
	bool wasClicked = false;
	if(e.disabled)
		return wasClicked;
	if(IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON)){
		Vector2 mPos = GetMousePosition();

		for(size_t i = 0; i < NUM_RECT; ++i){
			if(e.useRect[i] && CheckCollisionPointRec(mPos, e.rect[i])){
				SetClicked(e, mouse);
				wasClicked = true;
				break;
			}
		}
	}
	return wasClicked;
}


void CheckLDown(Elemino &e){
	if(e.disabled)
		return;
	if(IsMouseButtonDown(MouseButton::MOUSE_LEFT_BUTTON)){
		Vector2 mousePos = GetMousePosition();
		for(size_t i = 0; i < NUM_RECT; ++i){
			if(CheckCollisionPointRec(mousePos, e.rect[i])){
				e.dragging = true;
				break;
			}
		}
	}
}


void CheckLReleased(Elemino &e, Mouse &mouse){
	if(e.disabled)
		return;
	if(IsMouseButtonReleased(MouseButton::MOUSE_LEFT_BUTTON)){
		mouse.touch = nullptr;
		mouse.interface = InterfaceID::INTERFACE_NONE;
		e.dragging = false;
	}
}


void CheckLUp(Elemino &e){
	if(e.disabled)
		return;
	if(IsMouseButtonUp(MouseButton::MOUSE_LEFT_BUTTON)){
		e.dragging = false;
	}
}


void SetClicked(Elemino &e, Mouse &mouse){
	mouse.touch = &e;
	mouse.interface = InterfaceID::ELEMINO;
	e.dragging = true;

	if(e.inInventory)
		Enlarge(e);

	e.inInventory = false;
	e.aligned = false;
	ComputeOffsets(e, GetMousePosition());
	e.mOffset = GetMousePosition() - e.pos; 
	e.step = 0.0f;
}


void Drag(Elemino &e){
	Vector2 mouse = GetMousePosition();
	e.pos = mouse - e.mOffset;
	//std::cout << e.pos.x << " " << e.pos.y << std::endl;
	for(size_t i = 0; i < NUM_RECT; ++i){
		//Put each rect at their offset
		if(e.useRect[i]){
			Vector2 pos = {mouse.x - e.offset[i].x, mouse.y - e.offset[i].y};
			e.rect[i].x = pos.x;
			e.rect[i].y = pos.y;
		}
	}
}


void Rotate(Elemino &e){
	RotateUsedRect(e);
	OffsetRotAxis(e);

	for(size_t i = 0; i < NUM_RECT; ++i)
		e.rect[i] = (Rectangle){-1, -1, 0, 0};

	MakeRectangles(e);
	ComputeOffsets(e, GetMousePosition());
}


void RotateUsedRect(Elemino &e){
	bool temp[NUM_RECT];

	for(size_t i = 0; i < NUM_RECT; ++i){
		int currX = i % 4;
		int currY = i / 4;
		//Rotate 90 degrees and translate right to stay positive
		int x = -currY + 3;
		int y = currX;
		int index = x + 4 * y;
		temp[index] = e.useRect[i];
	}

	for(size_t i = 0; i < NUM_RECT; ++i)
		e.useRect[i] = temp[i];
}


void OffsetRotAxis(Elemino &e){
	//Rotate offset and shift vector
	Vector2 temp;
	temp.x = -e.mOffset.y + 4 * RECT_WIDTH;
	temp.y = e.mOffset.x;

	e.mOffset = temp;
	e.pos = GetMousePosition() - e.mOffset;
}


unsigned int Overlap(const Elemino &e, const Grid &g){
	bool seen[NUM_RECT];

	for(size_t i = 0; i < NUM_RECT; ++i)
		seen[i] = false;
	
	unsigned int count = 0;
	for(size_t i = 0; i < NUM_RECT; ++i){
		if(e.useRect[i]){
			for(size_t j = 0; j < NUM_RECT; ++j){
				if(!g.anchors[j].occupier && CheckCollisionPointRec(g.anchors[j].pos, e.rect[i]) && !seen[j]){
					seen[j] = true;
					count++;
					break; //Or i = NUM_RECT + 1;
				}
			}
		}
	}
	return count;
}


void Move(Elemino &e, const Vector2 &offset){
	e.pos = e.pos + offset;
	for(size_t i = 0; i < NUM_RECT; ++i){
		if(e.useRect[i]){
			e.rect[i].x += offset.x;
			e.rect[i].y += offset.y;
		}
	}
}


void MoveTo(Elemino &e, const Vector2 &newPos){
	e.pos = newPos;
	
	if(e.inInventory)
		MakeRectanglesSmall(e);
	else
		MakeRectangles(e);
}


void Snap(Elemino &e, Grid &g){
	if(e.aligned || Overlap(e, g) == e.count){
		SnapToLinear(e, g);
	}
}


Vector2 Occupy(Elemino &e, Grid &g){
	e.aligned = true;

	bool seen[NUM_RECT];
	bool computedOffset = false;

	for(size_t i = 0; i < NUM_RECT; ++i)
		seen[i] = false;

	Vector2 offset;
	for(size_t i = 0; i < NUM_RECT; ++i){
		if(e.useRect[i]){
			for(size_t j = 0; j < NUM_RECT; ++j){
				if(!g.anchors[j].occupier && CheckCollisionPointRec(g.anchors[j].pos, e.rect[i]) && !seen[j]){
					seen[j] = true;
					g.anchors[j].occupier = &e;

					if(!computedOffset){
						offset = (Vector2){g.anchors[j].pos.x - e.rect[i].x,
							g.anchors[j].pos.y - e.rect[i].y};
						offset.x -= (float)RECT_WIDTH / 2; //Top-left of anchor.pos
						offset.y -= (float)RECT_WIDTH / 2;

						computedOffset = true;
					}
					
					break;
				}
			}
		}
	}
	return offset;
}


void SnapTo(Elemino &e, Grid &g){
	if(!e.aligned){
		Vector2 offset = Occupy(e, g);
		Move(e, offset);
	}
}


void SnapToLinear(Elemino &e, Grid &g){
	if(!e.aligned){
		Vector2 offset = Occupy(e, g);
		e.dragTo = e.pos + offset;
	}
	e.step += 0.1f;
	Vector2 lerpOffset = Lerp(e.step, e.pos, e.dragTo) - e.pos;
	Move(e, lerpOffset);
}


void EleminoSnap(Elemino &e, Grid &g){
	if(!e.aligned){
		Vector2 offset = Occupy(e, g);
		e.dragTo = e.pos + offset;
		e.startPos = e.pos;
	}
	if(e.snapping){
		//Do quadratic interp
		Vector2 diff = e.dragTo - e.startPos;
		float numerator = (float)(e.iStep * e.iStep + e.iStep);
		float frac = numerator / 20.f;

		Vector2 newPos = diff * frac;
		MoveTo(e, newPos);

		e.iStep++;
		if(e.iStep == 4){
			e.iStep = 0;
			e.snapping = false;
		}
	}
}


void Unoccupy(Grid &g){
	for(size_t i = 0; i < NUM_RECT; ++i){
		if(g.anchors[i].occupier){
			if(g.anchors[i].occupier->dragging || !g.anchors[i].occupier->aligned){
				g.anchors[i].occupier = nullptr;
			}
		}
	}
}

