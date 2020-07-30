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
	/* unsigned int id; */
	/* bool playing = false; //FIXME: remove me! */
	bool looping = false;

	unsigned int index = 0;
	unsigned int frameCount = 0;

	Vec<unsigned int> durations; // 0 - infinite, 1,2,3,... - regular duration
	Vec<Rectangle> rects;

	void reset(){
		index = 0;
		frameCount = 0;
	}
};

struct Sprite{
	Texture texture;
	Vector2 pos{0, 0};
	UMap<std::string, Animation> anims;

	Animation *currAnim = nullptr;
	bool playing = false;
	bool flipX = false;
	bool flipY = false;
	
	unsigned int delay = 0;
	Animation *animToBePlayed = nullptr;

	static constexpr float frametime = 1.f / 24.f; //NOTE: to be used with GetFrameTime() from raylib
	static float timer;
	static bool updateAnimFrames;

	void playAnimation(const char *);
	void playAnimation(const char *, unsigned int); //Play an animation after a delay (in frames)
	void updateAnimation();
};


/* struct AnimationStateController{ */
/* 	UMap<unsigned int, Vec<unsigned int> > transistions; //Maps one id to a vector of valid id */ 
/* 	UMap<std::string, Animation> anims; */
/* 	Animation *currAnim = nullptr; */

/* 	bool playing = false; */
/* 	bool looping = false; */
/* 	bool flipX = false; */
/* 	bool flipY = false; */
/* }; */


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
