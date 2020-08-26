#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>
/* #include <unordered_map> */

#include "raylib\raylib.h"
#include "robin_hood\robin_hood.h"

template<typename T>
using Vec = std::vector<T>;

template<typename T, typename U>
using Pair = std::pair<T, U>;

/* template<typename T, typename U> */
/* using UMap = std::unordered_map<T, U>; */
template<typename T, typename U>
using UMap = robin_hood::unordered_flat_map<T, U>;

struct Animation{
	/* unsigned int id; */
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

	/* bool animDone = false; */
	void (*onAnimationEnd)() = nullptr;

	static constexpr float frametime = 1.f / 24.f; //NOTE: to be used with GetFrameTime() from raylib
	static float timer;
	static bool updateAnimFrames;

	void playAnimation(const char *);
	void playAnimation(const char *, unsigned int); //Play an animation after a delay (in frames)
	void playAnimation(const char *, void (*func)()); //Exec the function on animation end
	void playAnimation(const char *, unsigned int, void (*func)());
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

struct SpriteManager{
	//Have some memory pools to decrease allocation
	/* static MemPool combat_actor_sprite_pool; */
	/* static MemPool combat_fx_sprite_pool; */
	/* static MemPool overworld_sprite_pool; */
	/* static MemPool inventory_sprite_pool; */

	static Vec<Sprite> combat_actor_sprites;
	static Vec<Sprite> combat_fx_sprites;
	static Vec<Sprite> overworld_sprites;
	static Vec<Sprite> inventory_sprites;
	static int count;
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


bool UnloadSprite(Sprite &);



#endif
