#include "..\include\sprite.h"
#include "..\include\combat.h"

UMap<std::string, Texture> TextureManager::textures;
float Sprite::timer = 0.f;
bool Sprite::updateAnimFrames = false;


void Sprite::playAnimation(const char *str){
	auto iter = anims.find(str);

	if(iter != anims.end()){
		if(currAnim && playing && currAnim == &iter->second)
			return; //Early-ish exit b/c already at and playing currAnim

		currAnim = &iter->second;
		playing = true;
		delay = 0;
	}
}


void Sprite::playAnimation(const char *str, unsigned int delay){
	auto iter = anims.find(str);

	if(iter != anims.end()){
		if(currAnim && playing && currAnim == &iter->second)
			return; //Early-ish exit b/c already at currAnim

		this->delay = delay;
		animToBePlayed = &iter->second;
	}
}


void Sprite::playAnimation(const char *str, void (*func)()){
	playAnimation(str);
	if(currAnim || animToBePlayed)
		onAnimationEnd = func;
}


void Sprite::playAnimation(const char *str, unsigned int delay, void (*func)()){
	playAnimation(str, delay);
	if(currAnim || animToBePlayed)
		onAnimationEnd = func;
}


void Sprite::updateAnimation(){
	if(Sprite::updateAnimFrames && currAnim && playing){
		currAnim->frameCount++;

		if(currAnim->frameCount > currAnim->durations[currAnim->index]){
			currAnim->frameCount = 0;
			currAnim->index++;

			if(currAnim->index > currAnim->durations.size()-1){
				currAnim->index = 0;
				playing = currAnim->looping;

				if(!playing){
					currAnim = nullptr;
					if(onAnimationEnd){
						onAnimationEnd();
						onAnimationEnd = nullptr;
					}
				}
			}
		}
	}
}


void UpdateAnimationFrame(float dt){
	constexpr auto epsilon = 0.001f;

	Sprite::timer += dt; //Could adjust speed depending on this op
	if(fabs(Sprite::timer - Sprite::frametime) < epsilon || Sprite::timer > Sprite::frametime){
		Sprite::timer = 0.f; //could be timer - frametime
		Sprite::updateAnimFrames = true;
	}
	else
		Sprite::updateAnimFrames = false;
}


void Update(Sprite &spr){
	if(Sprite::updateAnimFrames && spr.delay > 0)
		spr.delay--;
	if(spr.delay < 1 && spr.animToBePlayed){
		spr.playing = true;
		spr.currAnim->reset();
		spr.currAnim = spr.animToBePlayed;
		spr.animToBePlayed = nullptr;
	}

	spr.updateAnimation();
}


void DrawSprite(Sprite &spr){
	if(spr.currAnim){
		Rectangle src = spr.currAnim->rects[spr.currAnim->index];
		Rectangle dest = {spr.pos.x, spr.pos.y, src.width, src.height};
		src.width = spr.flipX ? -src.width : src.width;
		DrawTexturePro(spr.texture, src, dest, {0,0}, 0.f, WHITE);
	}
	else{
		DrawTextureEx(spr.texture, {0,0}, 0.f, 0.f, WHITE);
	}
}


Sprite LoadSprite(unsigned char *embedded){
	Sprite spr;
	void *iter = embedded;
	
	const unsigned int numAnims = *(unsigned int*)iter;
	iter += sizeof(int);
	
	for(unsigned int i = 0; i < numAnims; ++i){
		std::string animName = "";

		//Find the end of the c-string
		for(; *((char *)iter) != 0; iter += sizeof(char))
			animName += *((char*)iter);
		iter += sizeof(char); //Advance forward past the zero
		
		const int numFrames = *(int*)iter;
		iter += sizeof(int);
		Animation anim;
		anim.durations.reserve(numFrames); //Do only one alloc for optimization
		anim.rects.reserve(numFrames);
		
		int len = 0; //To be length of data decompressed
		const unsigned int compressedSize = *(unsigned int*)iter; //Length of data compressed
		iter += sizeof(int);
		unsigned char *data = DecompressData((unsigned char*)iter, compressedSize, &len);

		//Make the frames
		void *spot = iter; //Save the spot where iter was
		iter = data;
		for(void *end = iter + numFrames * (sizeof(int)*5); iter != end; iter += sizeof(int)*5){
			anim.durations.push_back(*(unsigned int*)iter);
			Rectangle rect = {*(int*)(iter+sizeof(int)), *(int*)(iter+sizeof(int)*2), *(int*)(iter+sizeof(int)*3), *(int*)(iter+sizeof(int)*4)};
			anim.rects.push_back(rect);
		}
		iter = spot + compressedSize * sizeof(unsigned char); //Return back to the spot in the actual data

		free(data);

		spr.anims[animName.c_str()] = anim;
	}
	
	return spr;
}


