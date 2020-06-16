#include "include\console.h"
#include "include\game.h"
#include "include\player.h"


void HandleClose(Console &console, GameState &gs){
	if(IsKeyPressed(KEY_GRAVE) && !console.justToggled){
		console.toggled = false;
		return;
	}
	if(IsKeyReleased(KEY_GRAVE))
		console.justToggled = false;
}


void HandleDelete(Console &console){
	if(IsKeyPressed(KEY_BACKSPACE)){
		if(console.buffer.length() > 0 && console.cursor > 0){
			console.buffer.erase(console.cursor - 1, 1);
			console.cursor--;
		}
	}
	else if(IsKeyDown(KEY_BACKSPACE)){
		if(console.bspcDown >= AUTO_BACKSPACE_DELAY){
			if(console.buffer.length() > 0 && console.cursor > 0){
				console.buffer.erase(console.cursor - 1, 1);
				console.cursor--;
			}
		}
		console.bspcDown++;
	}
	if(IsKeyReleased(KEY_BACKSPACE))
		console.bspcDown = 0;
}


void HandleAccept(Console &console){
	if(IsKeyPressed(KEY_ENTER)){
		if(console.buffer.length() > 0){
			console.history.insert(console.history.begin(), console.buffer);
			console.commandHistory.insert(console.commandHistory.begin(), console.buffer);
			console.command = ParseConsole(console);
			console.buffer = "";
			console.cursor = 0;
			console.tokens.resize(0);
		}
	}
}


void HandleMoveLeft(Console &console){
	if(IsKeyPressed(KEY_LEFT)){
		if(console.buffer.length() > 0 && console.cursor > 0){
			console.cursor--;
		}
	}
	else if(IsKeyDown(KEY_LEFT)){
		if(console.lDown >= AUTO_BACKSPACE_DELAY){
			if(console.buffer.length() > 0 && console.cursor > 0){
				console.cursor--;
			}
		}
		console.lDown++;
	}
	if(IsKeyReleased(KEY_LEFT))
		console.lDown = 0;
}


void HandleMoveRight(Console &console){
	if(IsKeyPressed(KEY_RIGHT)){
		if(console.buffer.length() > 0 && console.cursor < console.buffer.length()){
			console.cursor++;
		}
	}
	else if(IsKeyDown(KEY_RIGHT)){
		if(console.rDown >= AUTO_BACKSPACE_DELAY){
			if(console.buffer.length() > 0 && console.cursor < console.buffer.length()){
				console.cursor++;
			}
		}
		console.rDown++;
	}
	if(IsKeyReleased(KEY_RIGHT))
		console.rDown = 0;
}


void HandleRetrieveCommand(Console &console){
	if(IsKeyPressed(KEY_UP)){
		if(console.commandHistory.size() > 0){
			console.buffer = console.commandHistory[0];
			console.cursor = console.buffer.length();
			return;
		}
	}
}


void InputConsole(Console &console, GameState &gs){
	HandleClose(console, gs);

	//Loop through queued key presses
	for(int key = GetKeyPressed(); key != 0; key = GetKeyPressed()){
		switch(key){
		case 0:
			break;
		case KEY_GRAVE:
			break;
		default:
			console.buffer.insert(console.cursor, 1, (char)key);
			console.cursor++;
			break;
		}
	}

	HandleRetrieveCommand(console);
	HandleDelete(console);
	HandleAccept(console);
	HandleMoveLeft(console);
	HandleMoveRight(console);

}


Dev::Command ParseConsole(Console &c){
	char separator = ' ';
	std::string token = "";

	for(unsigned int i = 0; i < c.buffer.size(); ++i){
		if(c.buffer[i] != separator){
			token += c.buffer[i];
		}
		else{
			if(token.size() != 0){
				c.tokens.push_back(token);
				token = "";
			}
		}
	}
	if(token.size() != 0){
		c.tokens.push_back(token);
		token = "";
	}
	if(c.tokens.size() > 0){
		if(c.tokens[0] == "clear"){
			if(c.tokens.size() == 1)
				return Dev::Command::clear;
			else
				AddNumArgMessage(c, 1);
		}
		else if(c.tokens[0] == "exec"){
			if(c.tokens.size() == 2)
				return Dev::Command::exec;
			else
				AddNumArgMessage(c, 2);
		}
		else if(c.tokens[0] == "give"){
			if(c.tokens.size() == 3)
				return Dev::Command::give;
			else
				AddNumArgMessage(c, 3);
		}
		else if (c.tokens[0] == "heal"){
			return Dev::Command::heal;
		}
		else{
			c.msg = ERR + INVA_CMD;
			c.history.insert(c.history.begin(), c.msg);
		}
	}
	return Dev::Command::none;
}


void AddNumArgMessage(Console &c, unsigned int min, unsigned int max){
	if(c.tokens.size() < min){
		c.msg = ERR + "\"" + c.tokens[0] + "\" has been provided too few arguments";
		c.history.insert(c.history.begin(), c.msg);
	}
	else if(c.tokens.size() > max){
		c.msg = ERR + "\"" + c.tokens[0] + "\" has been provided too many arguments";
		c.history.insert(c.history.begin(), c.msg);
	}
	//FIXME: This might not add any message
}


void AddNumArgMessage(Console &c, unsigned int exact){
	if(c.tokens.size() < exact){
		c.msg = ERR + "\"" + c.tokens[0] + "\" has been provided too few arguments";
		c.history.insert(c.history.begin(), c.msg);
	}
	else{ //Assume greater than
		c.msg = ERR + "\"" + c.tokens[0] + "\" has been provided too many arguments";
		c.history.insert(c.history.begin(), c.msg);
	}
}


void ConsoleCommand(Console &c, Game &game){
	switch(c.command){
	case Dev::Command::clear:
		ClearCommand(c);
		break;
	case Dev::Command::give:
		GiveCommand(c, game);
		break;
	case Dev::Command::exec:
		ExecCommand(c, game);
		break;
	case Dev::Command::heal:
		HealCommand(c, game);
		break;
	default:
		break;
	}

	c.command = Dev::Command::none;
}


void GiveCommand(Console &c, Game &game){
	Element param1 = Element::none;
	MinoShape param2 = (MinoShape)-1;

	if(c.tokens[1] == "fire")
		param1 = Element::fire;
	else if(c.tokens[1] == "water")
		param1 = Element::water;
	else if(c.tokens[1] == "nature")
		param1 = Element::nature;
	else if(c.tokens[1] == "lightning")
		param1 = Element::lightning;
	else if(c.tokens[1] == "metal")
		param1 = Element::metal;
	else if(c.tokens[1] == "rock")
		param1 = Element::rock;
	else if(c.tokens[1] == "spectre")
		param1 = Element::spectre;

	if(c.tokens[2] == "II")
		param2 = MinoShape::II;
	else if(c.tokens[2] == "I")
		param2 = MinoShape::I;
	else if(c.tokens[2] == "L")
		param2 = MinoShape::L;
	else if(c.tokens[2] == "J")
		param2 = MinoShape::J;
	else if(c.tokens[2] == "T")
		param2 = MinoShape::T;
	else if(c.tokens[2] == "Z")
		param2 = MinoShape::Z;
	else if(c.tokens[2] == "S")
		param2 = MinoShape::S;
	else if(c.tokens[2] == "O")
		param2 = MinoShape::O;
	else if(c.tokens[2] == "ii")
		param2 = MinoShape::ii;
	else if(c.tokens[2] == "i")
		param2 = MinoShape::i;
	else if(c.tokens[2] == "comma")
		param2 = MinoShape::comma;
	else if(c.tokens[2] == "period")
		param2 = MinoShape::period;
	else if(c.tokens[2] == "corner")
		param2 = MinoShape::corner;

	if(Valid(param1) && param2 != (MinoShape)-1){
		Elemino elemino(param2, param1);
		elemino.pos = (Vector2){(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
		MakeMinoShape(elemino, elemino.mish);
		elemino.disabled = true;

		Elemino *storage = TotalEleminoes::storage;
		storage[TotalEleminoes::size] = elemino; //Add elemino to the reserves

		game.player.inventory.push_back(&storage[TotalEleminoes::size]); //Save the elemino index to refer to later
		TotalEleminoes::size++;

		if(game.player.invData){
			UpdateInteractable(game.player);
			PositionEleminoes(*game.player.invData);
		}
	}
	else if(!Valid(param1)){
		c.msg = ERR + INVA_ARG + c.tokens[1] + " is an invalid element.";
		c.history.insert(c.history.begin(), c.msg);
	}
	else if(param2 == (MinoShape)-1){
		c.msg = ERR + INVA_ARG + c.tokens[2] + " is an invalid elemino shape.";
		c.history.insert(c.history.begin(), c.msg);
	}
}

void ClearCommand(Console &c){
	c.msg = "";
	c.history.insert(c.history.begin(), c.msg);
	c.history.insert(c.history.begin(), c.msg);
	c.history.insert(c.history.begin(), c.msg);
}


void ExecCommand(Console &c, Game &game){
	std::ifstream ifs;
	std::string configPath = "../config/";
	ifs.open((configPath + c.tokens[1]).c_str());

	Vec<std::string> commands; //Store commands from file first

	if(!ifs.is_open()){
		c.msg = ERR + INVA_ARG + c.tokens[1] + " could not be opened.";
		c.history.insert(c.history.begin(), c.msg);
		return;
	}

	//Read in all the commands from the file
	while(ifs.good()){
		std::string command;
		std::getline(ifs, command);

		if(command.length() > 0)
			commands.push_back(command);
	}

	ifs.close();

	Console worker; //Executes the commands, TODO: Make this not fucking stupid
	bool keepExec = commands.size() > 0;
	//Parse and perform each command
	while(keepExec){
		worker.buffer = commands[0];

		worker.command = ParseConsole(worker);
		if(worker.command != Dev::Command::none)
			ConsoleCommand(worker, game);

		worker.tokens.resize(0);
		commands.erase(commands.begin());

		keepExec = commands.size() > 0;
	}
}


void HealCommand(Console &c, Game &game){
	bool fullHeal = false;
	bool specificHeal = false;
	bool allCharacters = false;
	bool specificCharacter = false;
	bool badInput = false;
	int healAmt = -1;
	int character = -1;
	if((c.tokens[1] == "f" && c.tokens[2] != "f") || (c.tokens[2] == "f" && c.tokens[1] != "f"))
		fullHeal = true;
	else{
		healAmt = std::stoi(c.tokens[2]);
		if(healAmt > -1)
			specificHeal = true;
	}

	if((c.tokens[1] == "a" && c.tokens[2] != "a") || (c.tokens[2] == "a" && c.tokens[1] != "a"))
		allCharacters = true;
	else{
		character = std::stoi(c.tokens[1]);
		if(character > -1 && character < 4){
			specificCharacter = true;
		}
	}


	if(allCharacters){
		if(fullHeal){
			for(unsigned int i = 0; i < game.player.team.members.size(); ++i)
				FullHealActor(*game.player.team.members[i]);
		}
		else if(specificHeal){
			for(unsigned int i = 0; i < game.player.team.members.size(); ++i)
				HealActor(*game.player.team.members[i], healAmt);
		}
		else
			badInput = true;
	}
	else if(specificCharacter){
		if(fullHeal){
			FullHealActor(*game.player.team.members[character]);
		}
		else if(specificHeal){
			HealActor(*game.player.team.members[character], healAmt);
		}
		else{
			badInput = true;
		}
	}
	else
		badInput = true;
	if(badInput){
		//TODO: print invalid message in the console
	}
}




