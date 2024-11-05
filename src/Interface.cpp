#include "Interface.hpp"
#include "App.hpp"
#include "AppState.hpp"
#include "GameState.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "imgui.h"

Interface::Interface() {
	static sf::RenderWindow& window = GameState::getInstance().window();
	if(!ImGui::SFML::Init(window)) {
		std::cerr << "Error: Failed to Load ImGui" << std::endl;
	}
}

Interface::~Interface() {
	ImGui::SFML::Shutdown();
}

// Public
void Interface::update() {
	static sf::RenderWindow& window = GameState::getInstance().window();
	static sf::Vector2i& mousePosition = AppState::getInstance().mousePosition();
	static sf::Vector2i& cameraPosition = AppState::getInstance().cameraPosition();
	static std::string& entityTag = AppState::getInstance().entityTag();

	ImGui::SFML::Update(window, mClock.restart());
	ImGui::SetNextWindowSize({400, 600});
	ImGui::SetNextWindowPos({WINDOW_SIZE_X - 400, 0});
	ImGui::Begin("Level Editor");

	// UI Elements

	// Path
	ImGui::SeparatorText("Basic Information");
	static std::string str = "Level path: " + OUTPUT_FILENAME;
	static int strSize = str.size() + 1;
	char label[20];
	std::strncpy(label, str.c_str(), strSize);
	ImGui::Text(label, IM_ARRAYSIZE(label));

	// Window and Mouse Position
	auto windowPosition = window.getView().getCenter();
	ImGui::Text("Window Position: (%d, %d)\n", static_cast<int>(windowPosition.x), static_cast<int>(windowPosition.y));
	ImGui::SameLine();
	if(ImGui::Button("Reset")) {
		cameraPosition = {0, 0};
	}
	ImGui::Text("Mouse Position: (%d, %d)\n", mousePosition.x, mousePosition.y);


	//mousePositionUI();
	ImGui::SeparatorText("Entity Selection");

	static std::vector<const char*>& entityList = AppState::getInstance().filenamesChar();
	static std::vector<const char*> animationList = AppState::getInstance().animationList(entityTag);
	static int eIndex = 0;
	static int aIndex = 0;

	/*
	if(fEntityTag != "" and fEntityTag != list[index]) {
		for(int i = 0;i < list.size();i++) {
			if(fEntityTag == list[i]) {
				index = i;
			}
		}
	}
*/


	//if(!listChar.empty()) {

	//	if(ImGui::Combo("Select Entity", &index, listChar.data(), listChar.size())) {
	//		fEntityTag = list[index];
	//	}
		if(ImGui::ListBox("Select Entity", &eIndex, entityList.data(), entityList.size())) {
			entityTag = entityList[eIndex];
			animationList = AppState::getInstance().animationList(entityTag);
			//fCreateEntity = true;
		}
	//}

	//static std::string prevEntityTag = fEntityTag;
	//static int index = 0;
	/*
	if(fEntityTag != prevEntityTag) {
		listChar.clear();
		list = fAssets->listAnimationTags(fEntityTag);
		for(std::string& tag: list) {
			listChar.push_back(tag.c_str());
		}
		prevEntityTag = fEntityTag;
	}
	*/

	/*
	if(fAnimationTag!= "" and fAnimationTag != list[index]) {
		for(int i = 0;i < list.size();i++) {
			if(fAnimationTag == list[i]) {
				index = i;
			}
		}
	}
*/


	//if(!listChar.empty()) {
		if(ImGui::ListBox("Select Animation", &aIndex, animationList.data(), animationList.size())) {
		}
//		fAnimationTag = list[index];
	//}

//	ImGui::InputInt("Layer", &fLayer);

	//animationSelectorUI();
	ImGui::SeparatorText("Test");
	static bool& followMouse = AppState::getInstance().followMouse();
	static bool& snapGrid = AppState::getInstance().snapGrid();
	static bool& showGrid = AppState::getInstance().showGrid();
	static bool& deleteEntity = AppState::getInstance().deleteEntity();

	ImGui::Checkbox("Follow Mouse", &followMouse);
	ImGui::Checkbox("Snap Grid", &snapGrid);
	ImGui::Checkbox("Show Grid", &showGrid);
	if(ImGui::Button("Delete")) {
		deleteEntity = true;
	}

	static std::string& filename = AppState::getInstance().filename();
	static bool& save = AppState::getInstance().save();
	static bool& load = AppState::getInstance().load();

	ImGui::SeparatorText("File Settings");
	char buf[32];
	std::strncpy(buf, filename.c_str(), 32);
	ImGui::InputText("File Name", buf, IM_ARRAYSIZE(buf));
	filename = buf;

	if (ImGui::Button("Save")) {
		save = true;
	}
	ImGui::SameLine();
	if(ImGui::Button("Load")) {
		save = true;
	}

	ImGui::End();
}

// Private
