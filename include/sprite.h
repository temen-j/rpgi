#ifndef SPRITE_H
#define SPRITE_H

#include <cmath>
#include <vector>
#include <unordered_map>

#include "raylib\raylib.h"

template<typename T>
using Vec = std::vector<T>;

template<typename T, typename U>
using Pair = std::pair<T, U>;

template<typename T, typename U>
using UMap = std::unordered_map<T, U>;

template<typename T, typename U, typename V>
using UMapHash = std::unordered_map<T, U, V>;

//------------------------------------------------------------------------------
/* Copyright (c) Sindre Sorhus <sindresorhus@gmail.com> (sindresorhus.com) */
/* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: */
/* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */
struct Hash_sbdm{
	size_t operator()(const char *str) const {
		size_t hash = 0;

		for(auto c = 0; *(str + c) != 0; c++)
			hash = *(str + c) + (hash << 6) + (hash << 16) - hash;

		return hash;
	}
};
//------------------------------------------------------------------------------

struct Animation{
	bool playing = false;
	bool looping = false;

	unsigned int imageIndex = 0; //For indexing into imageDuration
	unsigned int rectIndex = 0;
	unsigned int frameCount = 0;
	float currTime = 0.0f;

	Vec<Pair<unsigned int, bool> > imageDuration; // 0 - infinite, 1,2,3,... - regular duration
	//bool is for: advance the rectIndex?
	Vec<Rectangle> imageRects;
};

struct Sprite{
	Texture *texture = nullptr;
	Rectangle *bounds = nullptr;
	Vector2 pos{0, 0};
	UMapHash<const char *, Animation, Hash_sbdm> anims;

	Animation *currAnim = nullptr;
	
	static constexpr float frametime = 1.f / 24.f; //NOTE: to be used with GetFrameTime() from raylib
};


struct TextureManager{
	static UMapHash<const char *, Texture, Hash_sbdm> textures;

	Texture & operator[](const char *path){
		return textures[path];
	}
};


void PlayAnimation(Sprite &, const char *);
void Update(Sprite &);
void Update(Animation &);


#endif
