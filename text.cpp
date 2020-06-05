#include "include\gui.h"

Text::Text(){
	pos = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
	color = LIGHTGRAY;
	size = 8;
	str = "Lorem Ipsum";
}


Text::~Text(){
}


Text::Text(const std::string &s){
	pos = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
	color = LIGHTGRAY;
	size = 8;
	str = s;
}


Text::Text(const std::string &s, const Vector2 &v){
	pos = v;
	color = LIGHTGRAY;
	size = 10;
	str = s;
}


Text::Text(const std::string &s, const Vector2 &v, const int &fs){
	pos = v;
	color = LIGHTGRAY;
	size = fs;
	str = s;
}


Text::Text(const std::string &s, const Vector2 &v, const int &fs, const Color &c){
	pos = v;
	color = c;
	size = fs;
	str = s;
}


void Text::operator=(const std::string &s){
	str = s;
}

