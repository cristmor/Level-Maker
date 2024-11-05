#include "AppState.hpp"

#include <iostream>
AppState::AppState() {
	for(const auto& entry: std::filesystem::recursive_directory_iterator(mAssetPath)) {
		if(entry.is_regular_file()) {
			mPaths.push_back(entry.path());
		}
	}
	std::sort(mPaths.begin(), mPaths.end(), [](const std::filesystem::path& a, const std::filesystem::path& b) { return a.filename().string() < b.filename().string(); });
	mFilenames.reserve(mPaths.size());
	mFilenamesChar.reserve(mPaths.size());
	for(const auto& path : mPaths) {
		mFilenames.push_back(path.filename().stem().string());
		mFilenamesChar.push_back(mFilenames.back().c_str());
	}

	const AnimationMap& map = GameState::getInstance().assets().getAnimationMap();
	for(auto& pair : map) {
		mAnimationList.push_back(pair.second.tag());
	}
	std::sort(mAnimationList.begin(), mAnimationList.end());
}

// Public
std::vector<const char*> AppState::animationList(std::string tag) {
	const AnimationMap& map = GameState::getInstance().assets().getAnimationMap();
	std::vector<const char*> out;
	for(auto& aTag: mAnimationList) {
		if(tag == aTag.substr(0, tag.size())) {
			out.push_back(aTag.c_str());
		}
	}
	return out;
}
