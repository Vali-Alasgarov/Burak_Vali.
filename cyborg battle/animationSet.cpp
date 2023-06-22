#include "animationSet.h"

AnimationSet::~AnimationSet(){
	cleanup(spriteSheet);
	if (whiteSpriteSheet != NULL)
		cleanup(whiteSpriteSheet);
}

Animation* AnimationSet::getAnimation(string name){
	for (list<Animation>::iterator animation = animations.begin(); animation != animations.end(); animation++){
		Animation* anim = &(*animation);

		//if we find a match on name, return that animation from the list
		if (name == anim->name)
		{
			return anim;
		}
	}

	return NULL;
}

//loads a fdset file, also takes a list of what types of data we expect to loading.

void AnimationSet::loadAnimationSet(string fileName, list<DataGroupType> &groupTypes, bool setColourKey, int transparentPixelIndex, bool createWhiteTexture){

	ifstream file;
	string resPath = getResourcePath();
	file.open(resPath + fileName);
	if (file.good())
	{
		getline(file, imageName);
		if (setColourKey)
		{
			SDL_Surface* spriteSurface = loadSurface(resPath + imageName, Globals::renderer);

			//for transparency, we will grab the [transparentPixelIndex] from the surface we just made
			SDL_Color* transparentPixel = &spriteSurface->format->palette->colors[transparentPixelIndex];
			SDL_SetColorKey(spriteSurface, 1, SDL_MapRGB(spriteSurface->format, transparentPixel->r, transparentPixel->g, transparentPixel->b));

			spriteSheet = convertSurfaceToTexture(spriteSurface, Globals::renderer, false);

			if (createWhiteTexture)
			{
				SDL_Surface* whiteSurface = loadSurface(resPath + "allwhite.png", Globals::renderer);
				surfacePaletteSwap(spriteSurface, whiteSurface);
				SDL_SetColorKey(spriteSurface, 1, SDL_MapRGB(spriteSurface->format, transparentPixel->r, transparentPixel->g, transparentPixel->b));
				whiteSpriteSheet = convertSurfaceToTexture(spriteSurface, Globals::renderer, false); //create the texture whilst destroying the surface

				cleanup(whiteSurface);
			}
			else{
				whiteSpriteSheet = NULL;
			}

			cleanup(spriteSurface);
		}
		else
			spriteSheet = loadTexture(resPath + imageName, Globals::renderer);

		string buffer;
		getline(file, buffer);
		stringstream ss;
		buffer = Globals::clipOffDataHeader(buffer);
		ss << buffer;
		int numberOfAnimations;
		ss >> numberOfAnimations;

		for (int i = 0; i < numberOfAnimations; i++)
		{
			Animation newAnimation;
			newAnimation.loadAnimation(file, groupTypes);
			animations.push_back(newAnimation);
		}

	}
	file.close();


}