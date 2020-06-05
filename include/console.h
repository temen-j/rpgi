#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "elemino.h"
#include "element.h"
#include "gamestate.h"
#include "raylib\raylib.h"

template<typename T>
using Vec = std::vector<T>;

const unsigned int MAX_HIST = 16;
const std::string ERR = "ERROR: ";
const std::string INVA_ARG = "Invalid argument! ";
const std::string INVA_CMD = "Invalid command! ";
struct Game;

namespace Dev{
	enum Command{
		none,
		clear,
		give,
		exec
	};

}

const int AUTO_BACKSPACE_DELAY = 20;

struct Console{
	Vec<std::string> history;
	Vec<std::string> commandHistory;
	Vec<std::string> tokens;
	std::string buffer;
	std::string msg;
	unsigned int cursor;
	unsigned int bspcDown;
	unsigned int lDown;
	unsigned int rDown;
	bool justToggled;
	bool toggled;
	Dev::Command command;

	Console(){
		history.resize(0);
		tokens.resize(0);
		buffer = "";
		msg = "";
		cursor = 0;
		justToggled = false;
		toggled = false;
		bspcDown = 0;
		lDown = 0;
		rDown = 0;
		command = Dev::Command::none;
	}
};

void HandleClose(Console &, GameState &);
void HandleDelete(Console &);
void HandleAccept(Console &);
void HandleMoveLeft(Console &);
void HandleMoveRight(Console &);
void HandleRetrieveCommand(Console &);

void InputConsole(Console &, GameState &);
Dev::Command ParseConsole(Console &);
void AddNumArgMessage(Console &, unsigned int, unsigned int);
void AddNumArgMessage(Console &, unsigned int);

void ConsoleCommand(Console &, Game &);
void GiveCommand(Console &, Game &);
void ClearCommand(Console &);
void ExecCommand(Console &, Game &);

#endif
