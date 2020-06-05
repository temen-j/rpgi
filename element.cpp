#include "include\element.h"

bool Valid(const Element &e){
	return !(e < Element::fire || e > Element::spectre);
}

//Calculate the effectiveness, the Element multiplier
float Effectiveness(const Element &attack, const Element defender[2]){
	float chart[7][7] = {
		{1.0f, .75f, 1.5f, 1.5f, 1.5f, .75f, .75f},
		{1.5f, 1.0f, .75f, .75f, 1.5f, 1.5f, .75f},
		{.75f, 1.5f, 1.0f, 1.5f, .75f, 1.5f, .75f},
		{.75f, 1.5f, .75f, 1.0f, 1.5f, .75f, 1.5f},
		{.75f, .75f, 1.5f, .75f, 1.0f, 1.5f, 1.5f},
		{1.5f, .75f, .75f, 1.5f, .75f, 1.0f, 1.5f},
		{1.5f, 1.5f, 1.5f, .75f, .75f, .75f, 1.0f}
	};
	//TODO: make this more efficient that just generating the chart each call
	if (Valid(attack) && Valid(defender[0]) && Valid(defender[1]))
		return chart[attack - 1][defender[0] - 1] * chart[attack - 1][defender[1] - 1];
	else if (Valid(attack) && Valid(defender[0]) && !Valid(defender[1]))
		return chart[attack - 1][defender[0] - 1];
	else if (Valid(attack) && !Valid(defender[0]) && Valid(defender[1]))
		return chart[attack - 1][defender[1] - 1];

	return -0.0f;
}


std::string to_string(const Element &e){
	switch(e){
		case Element::error:
			return "ERROR";
			break;
		case Element::none:
			return "NONE";
			break;
		case Element::fire:
			return "Fire";
			break;
		case Element::water:
			return "Water";
			break;
		case Element::nature:
			return "Nature";
			break;
		case Element::lightning:
			return "Lightning";
			break;
		case Element::metal:
			return "Metal";
			break;
		case Element::rock:
			return "Rock";
			break;
		case Element::spectre:
			return "Spectre";
			break;
		default:
			return "ERROR";
			break;
	}
}

