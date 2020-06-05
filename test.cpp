#include <fstream>

#include "include\game.h"
#include "include\gamestate.h"
#include "include\gui.h"
#include "include\tmath.h"
#include "include\elemino.h"
#include "include\element.h"

#include "include\raylib\raylib.h"
#include "include\raylib\raygui.h"

template<typename T>
using Vec = std::vector<T>;

Vector2 ScreenCenter(){
	return {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
}

int main(void){

	const int screenWidth = 960;
	const int screenHeight = 640;
	std::string empty = "";

	InitWindow(screenWidth, screenHeight, "RPG Window");

	Game game; //Lots of stuff loads here!!!!!!!!1

	States *gs = &game.gs;
	gs->curr = GameState::LIMBO;
	gs->prev = gs->curr;

	Mouse mouse;
	mouse.pos = GetMousePosition();

	GlobalTextData gtd;
	//WILL NOT LOAD UNLESS NOT IN SHELL (RUN OUTSIDE TERMINAL)
	gtd.defaultFont = LoadFont("fonts/Inconsolata-Regular.ttf"); //Wtf???

	gtd.imageText = GenImageColor(GetScreenWidth(), GetScreenHeight(), CLEAR);
	GuiSetFont(gtd.defaultFont);

	Console *console =  &game.console;

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		mouse.pos = GetMousePosition();
		ImageClearBackground(&(gtd.imageText), CLEAR); //Clear batched text


		//State Transistion: to console dialog
		if(IsKeyPressed(KEY_GRAVE) && gs->curr != GameState::CONSOLE_DIALOG && !console->justToggled && !console->toggled){
			gs->prev = gs->curr;
			gs->curr = GameState::CONSOLE_DIALOG;
			console->justToggled = true;
			console->toggled = true;
		}

		//State Transistion (Toggle): to inventory, from inventory
		if(IsKeyPressed(KEY_I) && gs->curr != GameState::CONSOLE_DIALOG){
			if(gs->curr != GameState::INVENTORY){
				gs->prev = gs->curr;
				gs->curr = GameState::INVENTORY;
			}
			else{
				GameState temp = gs->curr;
				if(temp == GameState::CONSOLE_DIALOG)
					temp = GameState::LIMBO;
				gs->curr = gs->prev;
				gs->prev = temp;

				if(game.invData && gs->curr != GameState::INVENTORY){
					game.invData->grids = nullptr;
					free(game.invData);
					game.invData = nullptr;
				}
			}
		}

/*		
		if(gs->curr == GameState::LIMBO){
			if(!mouse.touch)
				CheckLPressed(elemino, mouse);
			if(!mouse.touch)
				CheckLPressed(elemino2, mouse);

			CheckLReleased(elemino, mouse);
			CheckLReleased(elemino2, mouse);
			
			if(elemino.dragging)
				Drag(elemino);
			if(elemino2.dragging)
				Drag(elemino2);
			if(IsKeyPressed(KEY_R)){
				if(mouse.touch == &elemino)
					Rotate(elemino);
				if(mouse.touch == &elemino2)
					Rotate(elemino2);
			}

			Unoccupy(grid);

			if(!elemino.dragging)
				Snap(elemino, grid);
			if(!elemino2.dragging)
				Snap(elemino2, grid);
		}
*/
		//TODO: Turn me into a switch?
		if(gs->curr == GameState::LIMBO){
			game.justEnteredState = false;
		}
		else if(gs->curr == GameState::INVENTORY){
			if(!game.invData){
				game.invData = new InventoryData(); //ewww heap alloc
				OpenInventory(game);
			}
			//TODO: Turn this into a function
			for(unsigned int i = 0; i < game.player.inventory.size(); ++i)
				CheckLPressed(game.player.inventory[i], mouse);
			for(unsigned int i = 0; i < game.player.inventory.size(); ++i)
				CheckLReleased(game.player.inventory[i], mouse);
			
			for(unsigned int i = 0; i < game.player.inventory.size(); ++i){
				Elemino *elemino = &game.player.inventory[i];

				if(elemino->dragging){
					if(!game.invData->startedDrag){
						Move(*elemino, elemino->mOffset);
						MakeRectangles(*elemino); //Make elemino bigger again
						ComputeOffsets(*elemino, GetMousePosition());
						game.invData->startedDrag = true;
					}

					Drag(game.player.inventory[i]);

					if(IsKeyPressed(KEY_R)){
						Rotate(*elemino);
					}

					break; //Only drag and rotate one elemino
				}
			}

			Unoccupy(game.invData->grids[0]);
			Unoccupy(game.invData->grids[1]);
			Unoccupy(game.invData->grids[2]);

			for(unsigned int i = 0; i < game.player.inventory.size(); ++i){
				Elemino *elemino = &game.player.inventory[i];
				for(unsigned int j = 0; j < 3; ++j){
					if(!elemino->dragging && !elemino->inInventory)
						Snap(*elemino, game.invData->grids[j]);
				}
			}
		}
		else if(gs->curr == GameState::CONSOLE_DIALOG){
			InputConsole(*console, *gs);
			if(console->command != Dev::Command::none)
				ConsoleCommand(*console, game);
		}

		//GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);
		GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
//-----------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if(gs->curr == GameState::INVENTORY){
			for(size_t i = 0; i < 3; ++i)
				DrawGrid(game.invData->grids[i]);

			DrawInventory(game.player);
		}

		Texture textTexture = LoadTextureFromImage(gtd.imageText);
		DrawTexture(textTexture, 0, 0, WHITE);

		//char *test = "Hello GUI!";
		//GuiTextBox((Rectangle){ 25, 215, 125, 30 }, test, 64, false);

		//Draw console last!!!!!!!!!!
		if(gs->curr == GameState::CONSOLE_DIALOG){
			DrawConsole(*console, gtd);
		}

		EndDrawing();
//-----------------------------------------------------------------------------

		UnloadTexture(textTexture);
	}
	
	CloseWindow();

	return 0;
}

