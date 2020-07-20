#include "..\include\sprite.h"

UMapHash<const char *, Texture, Hash_sbdm> TextureManager::textures;

void PlayAnimation(Sprite &spr, const char *str){
	auto iter = spr.anims.find(str);

	if(iter != spr.anims.end()){
		if(spr.currAnim && spr.currAnim->playing && spr.currAnim == &iter->second)
			return;

		spr.currAnim = &iter->second;
		spr.bounds = &spr.currAnim->imageRects[0];
		spr.currAnim->playing = true;
	}
}


void Update(Sprite &spr){
	if(spr.currAnim){
		Update(*spr.currAnim);
		auto &rect = spr.currAnim->imageRects[spr.currAnim->rectIndex];
		if(spr.bounds != &rect)
			spr.bounds = &rect;
	}
}


void Update(Animation &anim){
	static const float epsilon = 0.001f;

	anim.currTime += GetFrameTime();	
	if(fabs(anim.currTime - Sprite::frametime) > epsilon){
		anim.currTime = 0.0f;
		anim.frameCount++;

		if(anim.imageDuration[anim.imageIndex].first == 0){
			return;
		}
		else if(anim.frameCount > anim.imageDuration[anim.imageIndex].first){
			anim.frameCount = 0;

			if(anim.imageDuration[anim.imageIndex].second)
				anim.rectIndex++;
			anim.imageIndex++;

			if(anim.imageIndex > anim.imageDuration.size()){
				if(!anim.looping)
					anim.playing = false;
				anim.imageIndex = 0;
				anim.rectIndex = 0;
			}
		}
	}
}

