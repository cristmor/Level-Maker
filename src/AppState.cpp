#include "AppState.hpp"

#include <iostream>
AppState::AppState() {
	const AnimationMap& animationMap = GameState::getInstance().assets().getAnimationMap();
	const TextureMap& textureMap = GameState::getInstance().assets().getTextureMap();
	for(auto& pair : animationMap) {
		mAnimationList.push_back(pair.first);
	}
	for(auto& pair : textureMap) {
		mTextureList.push_back(pair.first);
	}
	std::sort(mAnimationList.begin(), mAnimationList.end());
	std::sort(mTextureList.begin(), mTextureList.end());
}

// Public
std::vector<const char*> AppState::animationList(std::string tag) {
	std::vector<const char*> out;
	for(auto& aTag : mAnimationList) {
		if(tag == aTag.substr(0, tag.size())) {
			out.push_back(aTag.c_str());
		}
	}
	return out;
}

std::vector<const char*> AppState::textureList() {
	std::vector<const char*> out;
	for(auto& tTag : mTextureList) {
		out.push_back(tTag.c_str());
	}
	return out;
}
