#include "Assets.hpp"
#include <iostream>

Assets::Assets() {
	std::ifstream file("/home/cristmor/dev/cpp/SpriteCapture/data.txt");

	AssetData d;
	while(file.good()) {
		file >> d.textureTag
			>> d.animationTag
			>> d.count
			>> d.speed
			>> d.sizeX
			>> d.sizeY
			>> d.row
			>> d.column
			>> d.isCustom
			>> d.boundingBoxX
			>> d.boundingBoxY
			>> d.offsetX
			>> d.offsetY
			>> d.path;

		addTexture(d.textureTag, d.path);
		mAnimationMap[d.animationTag] = Animation(d.animationTag, d.count, d.speed, d.sizeX, d.sizeY, d.row, d.column, d.isCustom, { static_cast<int>(d.offsetX), static_cast<int>(d.offsetY) }, { d.boundingBoxX, d.boundingBoxY }, mTextureMap[d.textureTag]);
	}
	file.close();

}

// Private
void Assets::addTexture(std::string tag, std::string path) {
	if(mTextureMap.find(tag) != mTextureMap.end()) {
		return;
	}
	else if(!mTextureMap[tag].loadFromFile(path)) {
		std::cout << ("failed to load texture: " + path) << std::endl;
	}
}
