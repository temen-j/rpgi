#include "include\gui.h"
/* #include "include\move.h" */
#include "include\player.h"

#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#define __cpluplus
#include "raylib\raygui.h"
#endif

//Lifted from raygui to work with button object
void Update(Button &button){
	auto state = button.state;
	auto pressed = button.pressed;
	auto bounds = button.bounds;

    if ((state != GUI_STATE_DISABLED) && !guiLocked)
    {
        Vector2 mousePoint = GetMousePosition();

        // Check button state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = GUI_STATE_PRESSED;
            else state = GUI_STATE_FOCUSED;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) pressed = true;
        }
    }

	button.state = state;
	button.pressed = pressed;
	button.bounds = bounds;
}


void Update(ImageButton &button){
	Update(button.button);
}


bool Update(Toggle &toggle){
	auto state = toggle.state;
	auto active = toggle.active;
	auto bounds = toggle.bounds;

    if ((state != GUI_STATE_DISABLED) && !guiLocked)
    {
        Vector2 mousePoint = GetMousePosition();

        // Check toggle button state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = GUI_STATE_PRESSED;
            else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                state = GUI_STATE_NORMAL;
                active = !active;
            }
            else state = GUI_STATE_FOCUSED;
        }
    }

	toggle.state = state;
	toggle.active = active;
	toggle.bounds = bounds;
	return active;
}


bool Update(ImageToggle &toggle){
	return Update(toggle.toggle);
}


void SetupScrollBar(ScrollBar &sb){
	sb.state = GuiControlState::GUI_STATE_NORMAL;
    sb.isVertical = (sb.bounds.width > sb.bounds.height)? false : true;
    sb.spinnerSize = GuiGetStyle(SCROLLBAR, ARROWS_VISIBLE)? (sb.isVertical? sb.bounds.width - 2*GuiGetStyle(SCROLLBAR, BORDER_WIDTH) : sb.bounds.height - 2*GuiGetStyle(SCROLLBAR, BORDER_WIDTH)) : 0;
	
    // Normalize value
    if (sb.value > sb.maxValue) sb.value = sb.maxValue;
    if (sb.value < sb.minValue) sb.value = sb.minValue;
	sb.range = sb.maxValue - sb.minValue;
    sb.sliderSize = GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE);
    sb.arrowUpLeft = RAYGUI_CLITERAL(Rectangle){ (float)sb.bounds.x + GuiGetStyle(SCROLLBAR, BORDER_WIDTH), (float)sb.bounds.y + GuiGetStyle(SCROLLBAR, BORDER_WIDTH), (float)sb.spinnerSize, (float)sb.spinnerSize };

    if (sb.isVertical)
    {
        sb.arrowDownRight = RAYGUI_CLITERAL(Rectangle){ (float)sb.bounds.x + GuiGetStyle(SCROLLBAR, BORDER_WIDTH), (float)sb.bounds.y + sb.bounds.height - sb.spinnerSize - GuiGetStyle(SCROLLBAR, BORDER_WIDTH), (float)sb.spinnerSize, (float)sb.spinnerSize};
        sb.scrollbar = RAYGUI_CLITERAL(Rectangle){ sb.bounds.x + GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_PADDING), sb.arrowUpLeft.y + sb.arrowUpLeft.height, sb.bounds.width - 2*(GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_PADDING)), sb.bounds.height - sb.arrowUpLeft.height - sb.arrowDownRight.height - 2*GuiGetStyle(SCROLLBAR, BORDER_WIDTH) };
        sb.sliderSize = (sb.sliderSize >= sb.scrollbar.height)? (sb.scrollbar.height - 2) : sb.sliderSize;     // Make sure the slider won't get outside of the scrollbar
        sb.slider = RAYGUI_CLITERAL(Rectangle){ (float)sb.bounds.x + GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING), (float)sb.scrollbar.y + (int)(((float)(sb.value - sb.minValue)/sb.range)*(sb.scrollbar.height - sb.sliderSize)), (float)sb.bounds.width - 2*(GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING)), (float)sb.sliderSize };
    }
    else
    {
        sb.arrowDownRight = RAYGUI_CLITERAL(Rectangle){ (float)sb.bounds.x + sb.bounds.width - sb.spinnerSize - GuiGetStyle(SCROLLBAR, BORDER_WIDTH), (float)sb.bounds.y + GuiGetStyle(SCROLLBAR, BORDER_WIDTH), (float)sb.spinnerSize, (float)sb.spinnerSize};
        sb.scrollbar = RAYGUI_CLITERAL(Rectangle){ sb.arrowUpLeft.x + sb.arrowUpLeft.width, sb.bounds.y + GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_PADDING), sb.bounds.width - sb.arrowUpLeft.width - sb.arrowDownRight.width - 2*GuiGetStyle(SCROLLBAR, BORDER_WIDTH), sb.bounds.height - 2*(GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_PADDING))};
        sb.sliderSize = (sb.sliderSize >= sb.scrollbar.width)? (sb.scrollbar.width - 2) : sb.sliderSize;       // Make sure the slider won't get outside of the scrollbar
        sb.slider = RAYGUI_CLITERAL(Rectangle){ (float)sb.scrollbar.x + (int)(((float)(sb.value - sb.minValue)/sb.range)*(sb.scrollbar.width - sb.sliderSize)), (float)sb.bounds.y + GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING), (float)sb.sliderSize, (float)sb.bounds.height - 2*(GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING)) };
    }
}


void SetupListView(ListView &lw){
	lw.state = GuiControlState::GUI_STATE_NORMAL;
    lw.itemFocused = (&lw.focus == nullptr)? -1 : lw.focus;
    int itemSelected = lw.active;
    lw.useScrollBar = false;
    if ((GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING))*lw.text.size() > lw.bounds.height) lw.useScrollBar = true;
	
    lw.itemBounds.x = lw.bounds.x + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING);
    lw.itemBounds.y = lw.bounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING) + GuiGetStyle(DEFAULT, BORDER_WIDTH);
    lw.itemBounds.width = lw.bounds.width - 2*GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING) - GuiGetStyle(DEFAULT, BORDER_WIDTH);
    lw.itemBounds.height = GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
    if (lw.useScrollBar) lw.itemBounds.width -= GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH);

    lw.visibleItems = lw.bounds.height/(GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING));
    if (lw.visibleItems > lw.text.size()) lw.visibleItems = lw.text.size();

    lw.startIndex = (&lw.scrollIndex == nullptr)? 0 : lw.scrollIndex;
    if ((lw.startIndex < 0) || (lw.startIndex > (lw.text.size() - lw.visibleItems))) lw.startIndex = 0;
    lw.endIndex = lw.startIndex + lw.visibleItems;

	
    if (lw.useScrollBar)
    {
        Rectangle scrollBarBounds = {
            lw.bounds.x + lw.bounds.width - GuiGetStyle(LISTVIEW, BORDER_WIDTH) - GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH),
            lw.bounds.y + GuiGetStyle(LISTVIEW, BORDER_WIDTH), (float)GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH),
            lw.bounds.height - 2*GuiGetStyle(DEFAULT, BORDER_WIDTH)
        };

        // Calculate percentage of visible items and apply same percentage to scrollbar
        float percentVisible = (float)(lw.endIndex - lw.startIndex)/lw.text.size();
        float sliderSize = lw.bounds.height*percentVisible;

        int prevSliderSize = GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE);   // Save default slider size
        int prevScrollSpeed = GuiGetStyle(SCROLLBAR, SCROLL_SPEED); // Save default scroll speed
        GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE, sliderSize);            // Change slider size
        GuiSetStyle(SCROLLBAR, SCROLL_SPEED, lw.text.size() - lw.visibleItems); // Change scroll speed

		lw.scrollbar.bounds = scrollBarBounds;
		lw.scrollbar.value = lw.startIndex;
		lw.scrollbar.minValue = 0;
		lw.scrollbar.maxValue = lw.text.size() - lw.visibleItems;
		SetupScrollBar(lw.scrollbar);
    }
}


void Update(ScrollBar &sb){
    if ((sb.state != GUI_STATE_DISABLED) && !guiLocked)
    {
        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, sb.bounds))
        {
            sb.state = GUI_STATE_FOCUSED;

            // Handle mouse wheel
            int wheel = GetMouseWheelMove();
            if (wheel != 0) sb.value += wheel;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mousePoint, sb.arrowUpLeft)) sb.value -= sb.range/GuiGetStyle(SCROLLBAR, SCROLL_SPEED);
                else if (CheckCollisionPointRec(mousePoint, sb.arrowDownRight)) sb.value += sb.range/GuiGetStyle(SCROLLBAR, SCROLL_SPEED);

                sb.state = GUI_STATE_PRESSED;
            }
            else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                if (!sb.isVertical)
                {
                    Rectangle scrollArea = { sb.arrowUpLeft.x + sb.arrowUpLeft.width, sb.arrowUpLeft.y, sb.scrollbar.width, sb.bounds.height - 2*GuiGetStyle(SCROLLBAR, BORDER_WIDTH)};
                    if (CheckCollisionPointRec(mousePoint, scrollArea))
						sb.value = ((float)(mousePoint.x - scrollArea.x - sb.slider.width/2)*sb.range)/(scrollArea.width - sb.slider.width) + sb.minValue;
                }
                else
                {
                    Rectangle scrollArea = { sb.arrowUpLeft.x, sb.arrowUpLeft.y+sb.arrowUpLeft.height, sb.bounds.width - 2*GuiGetStyle(SCROLLBAR, BORDER_WIDTH),  sb.scrollbar.height};
                    if (CheckCollisionPointRec(mousePoint, scrollArea))
						sb.value = ((float)(mousePoint.y - scrollArea.y - sb.slider.height/2)*sb.range)/(scrollArea.height - sb.slider.height) + sb.minValue;
                }
            }
        }
		else{
			sb.state = GuiControlState::GUI_STATE_NORMAL;
		}

        // Normalize value
        if (sb.value > sb.maxValue) sb.value = sb.maxValue;
        if (sb.value < sb.minValue) sb.value = sb.minValue;

		if (sb.isVertical)
			sb.slider = RAYGUI_CLITERAL(Rectangle){ (float)sb.bounds.x + GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING), (float)sb.scrollbar.y + (int)(((float)(sb.value - sb.minValue)/sb.range)*(sb.scrollbar.height - sb.sliderSize)), (float)sb.bounds.width - 2*(GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING)), (float)sb.sliderSize };
		else
			sb.slider = RAYGUI_CLITERAL(Rectangle){ (float)sb.scrollbar.x + (int)(((float)(sb.value - sb.minValue)/sb.range)*(sb.scrollbar.width - sb.sliderSize)), (float)sb.bounds.y + GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING), (float)sb.sliderSize, (float)sb.bounds.height - 2*(GuiGetStyle(SCROLLBAR, BORDER_WIDTH) + GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING)) };
    }
}


void Update(ListView &lw){
    if ((lw.state != GUI_STATE_DISABLED) && !guiLocked)
    {
        Vector2 mousePoint = GetMousePosition();

        // Check mouse inside list view
        if (CheckCollisionPointRec(mousePoint, lw.bounds))
        {
            lw.state = GUI_STATE_FOCUSED;

            // Check focused and selected item
            for (int i = 0; i < lw.visibleItems; i++)
            {
                if (CheckCollisionPointRec(mousePoint, lw.itemBounds))
                {
                    lw.itemFocused = lw.startIndex + i;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        if (lw.active == (lw.startIndex + i)) lw.active = -1;
                        else lw.active = lw.startIndex + i;
                    }
                    break;
                }

                // Update item rectangle y position for next item
                lw.itemBounds.y += (GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING));
            }

            if (lw.useScrollBar)
            {
                int wheelMove = GetMouseWheelMove();
                lw.startIndex -= wheelMove;

                if (lw.startIndex < 0) lw.startIndex = 0;
                else if (lw.startIndex > (lw.text.size() - lw.visibleItems)) lw.startIndex = lw.text.size() - lw.visibleItems;

                lw.endIndex = lw.startIndex + lw.visibleItems;
                if (lw.endIndex > lw.text.size()) lw.endIndex = lw.text.size();

				lw.scrollbar.value = lw.startIndex;
				lw.scrollbar.minValue = 0;
				lw.scrollbar.maxValue = lw.text.size() - lw.visibleItems;
				Update(lw.scrollbar);
				lw.startIndex = lw.scrollbar.value;
            }
        }
        else{
			lw.itemFocused = -1;
			lw.state = GuiControlState::GUI_STATE_NORMAL;
		}

        // Reset item rectangle y to [0]
        lw.itemBounds.y = lw.bounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING) + GuiGetStyle(DEFAULT, BORDER_WIDTH);
    }
    if (&lw.focus != nullptr) lw.focus = lw.itemFocused;
    if (&lw.scrollIndex != nullptr) lw.scrollIndex = lw.startIndex;
}


void DrawGuiButton(Button &button){
	Rectangle bounds = button.bounds;
	const char *text = button.text.c_str();
    GuiControlState state = button.state;

    GuiDrawRectangle(bounds, GuiGetStyle(BUTTON, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(BUTTON, BORDER + (state*3))), guiAlpha), Fade(GetColor(GuiGetStyle(BUTTON, BASE + (state*3))), guiAlpha));
    GuiDrawText(text, GetTextBounds(BUTTON, bounds), GuiGetStyle(BUTTON, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(BUTTON, TEXT + (state*3))), guiAlpha));
}


void DrawGuiImageButton(ImageButton &ib){
	Rectangle bounds = ib.button.bounds;
	const char *text = ib.button.text.c_str();
    GuiControlState state = ib.button.state;
	Rectangle texSource = (Rectangle){ 0, 0, (float)ib.texture.width, (float)ib.texture.height };

    if (text != nullptr) GuiDrawText(text, GetTextBounds(BUTTON, bounds), GuiGetStyle(BUTTON, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(BUTTON, TEXT + (state*3))), guiAlpha));
    if (ib.texture.id > 0) DrawTextureRec(ib.texture, texSource, RAYGUI_CLITERAL(Vector2){ bounds.x, bounds.y}, Fade(GetColor(GuiGetStyle(BUTTON, TEXT + (state*3))), guiAlpha));
}


void DrawGuiImageToggle(ImageToggle &ito){
	Rectangle bounds = ito.toggle.bounds;
	const char *text = ito.toggle.text.c_str();
    GuiControlState state = ito.toggle.state;
	Rectangle texSource = (Rectangle){ 0, 0, (float)ito.texture.width, (float)ito.texture.height };

    if (text != nullptr) GuiDrawText(text, GetTextBounds(TOGGLE, bounds), GuiGetStyle(TOGGLE, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(TOGGLE, TEXT + (state*3))), guiAlpha));
    if (ito.texture.id > 0){
		if(ito.toggle.active)
			DrawTextureRec(ito.texture, texSource, RAYGUI_CLITERAL(Vector2){ bounds.x, bounds.y}, WHITE);
		else
			DrawTextureRec(ito.texture, texSource, RAYGUI_CLITERAL(Vector2){ bounds.x, bounds.y}, GRAY);
	}
}

void DrawGuiLabel(Label &label){
    GuiDrawText(label.text.c_str(), GetTextBounds(LABEL, label.bounds), GuiGetStyle(LABEL, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LABEL, (label.state == GUI_STATE_DISABLED)? TEXT_COLOR_DISABLED : TEXT_COLOR_NORMAL)), guiAlpha));
}

void DrawGuiBoxLabel(BoxLabel &label){
	DrawRectangleRec(label.bgBounds, label.bgColor);
    GuiDrawText(label.text.c_str(), GetTextBounds(LABEL, label.bounds), GuiGetStyle(LABEL, TEXT_ALIGNMENT), label.textColor);
}


void DrawGuiListView(ListView &lw){
    GuiDrawRectangle(lw.bounds, GuiGetStyle(DEFAULT, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER + lw.state*3)), guiAlpha), GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));     // Draw background

	if(lw.text.size() == 0)
		return;
	Rectangle itemBounds = lw.itemBounds;
    // Draw visible items
    for (int i = 0; i < lw.visibleItems; i++)
    {
        if (lw.state == GUI_STATE_DISABLED)
        {
            if ((lw.startIndex + i) == lw.active) GuiDrawRectangle(itemBounds, GuiGetStyle(LISTVIEW, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER_COLOR_DISABLED)), guiAlpha), Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_DISABLED)), guiAlpha));

            GuiDrawText(lw.text[lw.startIndex + i].c_str(), GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_DISABLED)), guiAlpha));
        }
        else
        {
            if ((lw.startIndex + i) == lw.active)
            {
                // Draw item selected
                GuiDrawRectangle(itemBounds, GuiGetStyle(LISTVIEW, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER_COLOR_PRESSED)), guiAlpha), Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_PRESSED)), guiAlpha));
                GuiDrawText(lw.text[lw.startIndex + i].c_str(), GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_PRESSED)), guiAlpha));
            }
            else if ((lw.startIndex + i) == lw.itemFocused)
            {
                // Draw item focused
                GuiDrawRectangle(itemBounds, GuiGetStyle(LISTVIEW, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER_COLOR_FOCUSED)), guiAlpha), Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_FOCUSED)), guiAlpha));
                GuiDrawText(lw.text[lw.startIndex + i].c_str(), GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_FOCUSED)), guiAlpha));
            }
            else
            {
                // Draw item normal
                GuiDrawText(lw.text[lw.startIndex + i].c_str(), GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_NORMAL)), guiAlpha));
            }
        }

        // Update item rectangle y position for next item
        itemBounds.y += (GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING));
    }

    if (lw.useScrollBar)
    {
        // Calculate percentage of visible items and apply same percentage to scrollbar
        float percentVisible = (float)(lw.endIndex - lw.startIndex)/lw.text.size();
        float sliderSize = lw.bounds.height*percentVisible;

        GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE, sliderSize);            // Change slider size
        GuiSetStyle(SCROLLBAR, SCROLL_SPEED, lw.text.size() - lw.visibleItems); // Change scroll speed

		DrawGuiScrollBar(lw.scrollbar);
    }
    //--------------------------------------------------------------------

    /* if (&lw.focus != NULL) lw.focus = lw.itemFocused; */
    /* if (&lw.scrollIndex != NULL) lw.scrollIndex = lw.startIndex; */
}


void DrawGuiScrollBar(ScrollBar &sb){
    GuiDrawRectangle(sb.bounds, GuiGetStyle(SCROLLBAR, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER + sb.state*3)), guiAlpha), Fade(GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_DISABLED)), guiAlpha));   // Draw the background
    
    GuiDrawRectangle(sb.scrollbar, 0, BLANK, Fade(GetColor(GuiGetStyle(BUTTON, BASE_COLOR_NORMAL)), guiAlpha));     // Draw the scrollbar active area background
    GuiDrawRectangle(sb.slider, 0, BLANK, Fade(GetColor(GuiGetStyle(SLIDER, BORDER + sb.state*3)), guiAlpha));         // Draw the slider bar

    // Draw arrows
    const int padding = (sb.spinnerSize - GuiGetStyle(SCROLLBAR, ARROWS_SIZE))/2;
    const Vector2 lineCoords[] =
    {
        // Coordinates for <     0,1,2
        { sb.arrowUpLeft.x + padding, sb.arrowUpLeft.y + sb.spinnerSize/2 },
        { sb.arrowUpLeft.x + sb.spinnerSize - padding, sb.arrowUpLeft.y + padding },
        { sb.arrowUpLeft.x + sb.spinnerSize - padding, sb.arrowUpLeft.y + sb.spinnerSize - padding },

        // Coordinates for >     3,4,5
        { sb.arrowDownRight.x + padding, sb.arrowDownRight.y + padding },
        { sb.arrowDownRight.x + sb.spinnerSize - padding, sb.arrowDownRight.y + sb.spinnerSize/2 },
        { sb.arrowDownRight.x + padding, sb.arrowDownRight.y + sb.spinnerSize - padding },

        // Coordinates for ∧     6,7,8
        { sb.arrowUpLeft.x + sb.spinnerSize/2, sb.arrowUpLeft.y + padding },
        { sb.arrowUpLeft.x + padding, sb.arrowUpLeft.y + sb.spinnerSize - padding },
        { sb.arrowUpLeft.x + sb.spinnerSize - padding, sb.arrowUpLeft.y + sb.spinnerSize - padding },

        // Coordinates for ∨     9,10,11
        { sb.arrowDownRight.x + padding, sb.arrowDownRight.y + padding },
        { sb.arrowDownRight.x + sb.spinnerSize/2, sb.arrowDownRight.y + sb.spinnerSize - padding },
        { sb.arrowDownRight.x + sb.spinnerSize - padding, sb.arrowDownRight.y + padding }
    };

    Color lineColor = Fade(GetColor(GuiGetStyle(BUTTON, TEXT + sb.state*3)), guiAlpha);

    if (GuiGetStyle(SCROLLBAR, ARROWS_VISIBLE))
    {
        if (sb.isVertical)
        {
            DrawTriangle(lineCoords[6], lineCoords[7], lineCoords[8], lineColor);
            DrawTriangle(lineCoords[9], lineCoords[10], lineCoords[11], lineColor);
        }
        else
        {
            DrawTriangle(lineCoords[2], lineCoords[1], lineCoords[0], lineColor);
            DrawTriangle(lineCoords[5], lineCoords[4], lineCoords[3], lineColor);
        }
    }
}


Color ElementToColor(const Element &e){
	switch(e){
		case Element::fire:
			return FIRECOLOR;
			break;
		case Element::water:
			return WATERCOLOR;
			break;
		case Element::nature:
			return NATURECOLOR;
			break;
		case Element::lightning:
			return LIGHTNINGCOLOR;
			break;
		case Element::metal:
			return METALCOLOR;
			break;
		case Element::rock:
			return ROCKCOLOR;
			break;
		case Element::spectre:
			return SPECTRECOLOR;
			break;
		default:
			return BLANK;
			break;
	}
	return CLEAR;
}

void Anchor::operator=(const Vector2 &v){
	pos.x = v.x;
	pos.y = v.y;
}


void DrawMouse(const Mouse &mouse){
	if(!mouse.touch)
		return;
	switch(mouse.interface){
	case InterfaceID::ELEMINO:
		DrawElemino(*static_cast<Elemino *>(mouse.touch));
		break;
	default:
		break;
	}
}


void DrawElemino(const Elemino &e){
	for(size_t i = 0; i < 16; ++i){
		if(e.useRect[i]){
			DrawTextureEx(Elemino::eleminoTile, (Vector2){e.rect[i].x, e.rect[i].y}, 0.f, (2 - e.inInventory) * .5f, e.color);
			//DrawRectangleRec(e.rect[i], e.color);	
		}
	}
}


void DrawGrid(const Grid &g){
	Rectangle rect;

	for(size_t i = 0; i < NUM_RECT; ++i){
		float x = g.anchors[i].pos.x;
		float y = g.anchors[i].pos.y;
		rect = (Rectangle){x - RECT_WIDTH / 2, y - RECT_WIDTH / 2, RECT_WIDTH, RECT_WIDTH}; //FIXME: no need for rect

		if(!g.anchors[i].disabled)
			DrawTextureEx(Grid::gridTile, (Vector2){rect.x, rect.y}, 0.f, 1.f, g.colorOn);
		else
			DrawTextureEx(Grid::gridTile, (Vector2){rect.x, rect.y}, 0.f, 1.f, g.colorOff);
	}

	for(unsigned int i = 0; i < g.attached.size(); ++i){
		DrawElemino(*g.attached[i]);
	}
}


void DrawConsole(const Console &c, GlobalTextData &gtd){
	Rectangle rect = (Rectangle){0,0, (float)GetScreenWidth(), 64};
	DrawRectangleRec(rect, BLACK);

	std::string lines[4];
	for(unsigned int i = 0; i < 4; ++i)
		lines[i] = "";

	Rectangle bounds = (Rectangle){0, 48, (float)GetScreenWidth(), 16};
	lines[0] = "$:" + c.buffer;
	GuiDrawText(lines[0].c_str(), bounds, GUI_TEXT_ALIGN_LEFT,  MAGENTA);

	//Add 2 to cursor in the substr b/c of the "$:"
	Rectangle cursor = {bounds.x + GetTextWidth(lines[0].substr(0, c.cursor + 2).c_str()) + 2, bounds.y, 8, 16};

	DrawRectangleRec(cursor, MAGENTA);

	//Draw the history of the console
	for(unsigned int i = 1; i < 4 && (i-1) < c.history.size(); ++i){
		Rectangle bounds = (Rectangle){0, 48 - (float)(i * 16), (float)GetScreenWidth(), 16};
		lines[i] = c.history[i-1];
		GuiDrawText(lines[i].c_str(), bounds, GUI_TEXT_ALIGN_LEFT,  MAGENTA);
	}
}


void DrawInventory(const Player &player){
	for(size_t i = 0; i < 4; ++i)
		DrawGuiImageToggle(player.invData->portraits.toggles[i]);

	for(size_t i = 0; i < 3; ++i)
		DrawGrid(player.invData->grids[i]);

	Rectangle rect = {INV_POS.x, INV_POS.y, INV_GRID_WIDTH, INV_GRID_WIDTH};
	DrawRectangleRec(rect, GRAY);

	for(size_t i = 0; i < NUM_STATS; ++i)
		DrawGuiLabel(player.invData->statText[i]);

	unsigned int max = player.invData->MAX_INV_DISP;
	unsigned int size = player.inventory.size();

	for(unsigned int i = 0; i < size && i < max; ++i)
		DrawElemino(*(player.inventory[i]));

	if(!player.invData->tooltip.disabled)
		DrawGuiBoxLabel(player.invData->tooltip);
}


void DrawMoveInventory(const Player &player){
	for(size_t i = 0; i < 4; ++i)
		DrawGuiImageToggle(player.minvData->portraits.toggles[i]);

	DrawGuiListView(player.minvData->movesCurrList);
	DrawGuiListView(player.minvData->movesAvailList);
}

