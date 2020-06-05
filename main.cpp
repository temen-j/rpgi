#include <fstream>

#include "include\move.h"
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

int main(int argc, char **argv){
	const int screenWidth = 960;
	const int screenHeight = 640;
	std::string empty = "";

	InitWindow(screenWidth, screenHeight, "RPG Window");

	Game game; //Lots of stuff loads here!!!!!!!!1
	game.mouse.pos = GetMousePosition();

	Player *player = &game.player;
	AddCharacters(*player);
	SetMaxLevel(*player);
	Console *console =  &game.console;
	GameState *gs = &game.gs;

	gs->curr = State::limbo;
	gs->prev = gs->curr;
	gs->old = gs->prev;

	GlobalTextData gtd;
	gtd.defaultFont = LoadFont("../fonts/Inconsolata-SemiBold.ttf");
	gtd.imageText = GenImageColor(GetScreenWidth(), GetScreenHeight(), CLEAR);
	GuiSetFont(gtd.defaultFont);

	GetEleminoGridTextures();

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		game.mouse.pos = GetMousePosition();
		ImageClearBackground(&(gtd.imageText), CLEAR); //Clear batched text


		if(IsKeyPressed(KEY_GRAVE) && !console->justToggled && !console->toggled){
			console->justToggled = true;
			console->toggled = true;
		}

		//State Transistion (Toggle): to inventory, from inventory
		if(!console->toggled){
			//Open/Close inventory?
			if(IsKeyPressed(KEY_I)){
				if(!game.inventoryOpen){
					game.inventoryOpen = true;
					game.minventoryOpen = false;
					game.justEnteredState = true;
				}
				else
					game.inventoryOpen = false;
			}
			else if(IsKeyReleased(KEY_I)){
				if(game.inventoryOpen)
					game.justEnteredState = false;
			}

			if(IsKeyPressed(KEY_O)){
				if(!game.minventoryOpen){
					game.minventoryOpen = true;
					game.inventoryOpen = false;
					game.justEnteredState = true;
				}
				else
					game.minventoryOpen = false;
			}
			else if(IsKeyReleased(KEY_O)){
				if(game.minventoryOpen)
					game.justEnteredState = false;
			}
		}

		//Cleanup if im not in the state
		if(!game.inventoryOpen && player->invData){
			UnloadTexturesFrom(*(player->invData));
			delete player->invData;
			player->invData = nullptr;
		}
		if(!game.minventoryOpen && player->minvData){
			UnloadTexturesFrom(*(player->minvData));
			delete player->minvData;
			player->minvData = nullptr;
		}
		/* if(gs->curr != State::console_dialog){ */
		/* } */
		//TODO: Turn me into a switch?
		if(console->toggled){
			InputConsole(*console, *gs);
			if(console->command != Dev::Command::none)
				ConsoleCommand(*console, game);
		}
		else{
			int ret;
			if(gs->curr == State::limbo){
				game.justEnteredState = false;
			}
			if(game.inventoryOpen){
				ret = InventoryState(game);
			}
			if(game.minventoryOpen){
				ret = MoveInventoryState(game);
			}
		}


		GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
//-----------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if(game.inventoryOpen){
			DrawInventory(game.player);
			DrawMouse(game.mouse);
		}
		if(game.minventoryOpen){
			DrawMoveInventory(game.player);
		}
		if(console->toggled){ //Draw console last
			DrawConsole(*console, gtd);
		}

		EndDrawing();
//-----------------------------------------------------------------------------
	}
	
	UnloadTexture(Elemino::eleminoTile);
	UnloadTexture(Grid::gridTile);
	UnloadFont(gtd.defaultFont);

	CloseWindow();

	return 0;
}

