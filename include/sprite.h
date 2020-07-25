#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <iostream>
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

struct Animation{
	bool playing = false;
	bool looping = false;

	unsigned int index = 0;
	unsigned int frameCount = 0;

	Vec<unsigned int> durations; // 0 - infinite, 1,2,3,... - regular duration
	Vec<Rectangle> rects;

	void reset();
};

struct Sprite{
	Texture *texture = nullptr;
	Vector2 pos{0, 0};
	UMap<std::string, Animation> anims;

	Animation *currAnim = nullptr;
	
	unsigned int delay = 0;
	std::string animToBePlayed;
	
	static constexpr float frametime = 1.f / 24.f; //NOTE: to be used with GetFrameTime() from raylib
	static float timer;
	static bool updateAnimFrames;

	void playAnimation(const char *);
	void playAnimation(const char *, unsigned int); //Play an animation after a delay (in frames)
	void updateAnimation(bool);
};


struct TextureManager{
	static UMap<std::string, Texture> textures;

	Texture & operator[](const char *path){
		return textures[std::string(path)];
	}
};

//Call every frame to ensure the 'closest' updates to sprite framerate
void UpdateAnimationFrame(float dt);

//-
void Update(Sprite &);

//-
void Update(Animation &);

//Draw sprite with its animation, if no anim. just draw the whole texture
void DrawSprite(Sprite &);

//-
Sprite LoadSprite(const char *);

//-
Sprite LoadSprite(unsigned char *);

#endif
