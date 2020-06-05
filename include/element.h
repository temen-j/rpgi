#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

static const int NUMELEMENTS = 7;

enum Element{
	error = -1,
	none = 0,
	fire = 1,
	water = 2,
	nature = 3,
	lightning = 4,
	metal = 5,
	rock = 6,
	spectre = 7
};


bool Valid(const Element &e);
float Effectiveness(const Element &attack, const Element defender[2]);
std::string to_string(const Element &);

#endif
