#include <fstream>
#include <algorithm>

#include "include\window.h"
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


int main(int argc, char **argv){
	/* const int screenWidth = 960; */
	/* const int screenHeight = 640; */
	std::string empty = "";

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "RPG Window");

	Window::rescaleTarget = LoadRenderTexture(SCREENWIDTH, SCREENHEIGHT);
	SetTextureFilter(Window::rescaleTarget.texture, FILTER_TRILINEAR);

	Game game; //Lots of stuff loads here!!!!!!!!1
	Game::mouse.pos = GetMousePosition();

	Player *player = &game.player;
	AddCharacters(*player);
	SetMaxLevel(*player);
	Console *console =  &game.console;
	GameState *gs = &game.gs;

	gs->curr = State::limbo;
	gs->prev = gs->curr;
	gs->old = gs->prev;

	GlobalTextData gtd;
	gtd.defaultFont = LoadFontEx("../fonts/Inconsolata-SemiBold.ttf", 64, 0, 0);
	SetTextureFilter(gtd.defaultFont.texture, FILTER_BILINEAR);
	gtd.imageText = GenImageColor(GetScreenWidth(), GetScreenHeight(), CLEAR);
	GuiSetFont(gtd.defaultFont);

	GetEleminoGridTextures();

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		/* game.mouse.pos = GetMousePosition(); */
		Update(Game::mouse);
		ImageClearBackground(&(gtd.imageText), CLEAR); //Clear batched text


		if(IsKeyPressed(KEY_GRAVE) && !console->justToggled && !console->toggled){
			console->justToggled = true;
			console->toggled = true;
		}

		//State Transistion (Toggle): to inventory, from inventory
		if(!console->toggled && gs->curr != State::combat_act && gs->curr != State::combat_watch){
			if(IsKeyPressed(KEY_C)){
				game.gs.prev = game.gs.curr;
				game.gs.curr = State::combat_act;
			}
			//Open/Close inventory?
			else if(gs->curr != State::combat_act && gs->curr != State::combat_watch){
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
			else if(gs->curr == State::combat_act || gs->curr == State::combat_watch){
				ret = CombatState(game);
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

		ClearBackground(BLACK);

		BeginTextureMode(Window::rescaleTarget);
		ClearBackground(RAYWHITE);

		if(game.gs.curr == State::combat_act || game.gs.curr == State::combat_watch){
			DrawCombat(game);
		}
		else{
			if(game.inventoryOpen){
				DrawInventory(game.player);
				DrawMouse(game.mouse);
			}
			else if(game.minventoryOpen){
				DrawMoveInventory(game.player);
			}
		}
		if(console->toggled){ //Draw console last
			DrawConsole(*console, gtd);
		}

		EndTextureMode();

		float wScaled = SCREENWIDTH * Window::scale;
		float hScaled = SCREENHEIGHT * Window::scale;
		DrawTexturePro(Window::rescaleTarget.texture, (Rectangle){ 0.0f, 0.0f, (float) Window::rescaleTarget.texture.width, (float) -Window::rescaleTarget.texture.height },
				(Rectangle) {(GetScreenWidth() - wScaled) * 0.5f, (GetScreenHeight() - hScaled) * 0.5f, wScaled, hScaled},
				(Vector2) {0, 0},
				0.0f,
				WHITE);

		EndDrawing();
//-----------------------------------------------------------------------------
	}
	
	UnloadRenderTexture(Window::rescaleTarget);
	UnloadTexture(Elemino::eleminoTile);
	UnloadTexture(Grid::gridTile);
	UnloadFont(gtd.defaultFont);

	DestroyMemPool(&CombatData::diffMemPool);

	CloseWindow();

	return 0;
}

