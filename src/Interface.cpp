#include "Interface.hpp"
#include "App.hpp"
#include "AppState.hpp"
#include "GameState.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

Interface::Interface() {
	static sf::RenderWindow& window = GameState::getInstance().window();
	if(!ImGui::SFML::Init(window)) {
		std::cerr << "Error: Failed to Load ImGui" << std::endl;
	}
}

// Public
void Interface::whileRun() {
	// move this to App.hpp
	//mousePosition = sf::Mouse::getPosition(*fWindow);
	static sf::RenderWindow& window = GameState::getInstance().window();
	static sf::Vector2i& mousePosition = AppState::getInstance().mousePosition();

	ImGui::SFML::Update(window, mClock.restart());
	ImGui::SetNextWindowSize({400, 600});
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
	//auto windowPosition = fWindow->getView().getCenter();
	//ImGui::Text("Window Position: (%d, %d)\n", static_cast<int>(windowPosition.x), static_cast<int>(windowPosition.y));
	ImGui::Text("Mouse Position: (%d, %d)\n", mousePosition.x, mousePosition.y);


	mousePositionUI();
	ImGui::SeparatorText("Entity Selection");
	entitySelectorUI();
	animationSelectorUI();
	ImGui::SeparatorText("Test");
	moveEntityUI();
	saveUI();

	ImGui::End();
}

void Interface::render() {
	//ImGui::SFML::Render(*fWindow);
}

void Interface::events(const sf::Event& event) {
	//ImGui::SFML::ProcessEvent(*fWindow, event);
}

// Public UI Componets
void Interface::pathUI() {

}

void Interface::mousePositionUI() {
}

void Interface::entitySelectorUI() {
	//static std::vector<std::string> list = fAssets->listEntityTags();
	static std::vector<const char*> listChar;
	static int index = 0;
	/*
	if(listChar.empty()) {
		for(std::string& tag: list) {
			listChar.push_back(tag.c_str());
		}
	}
*/

	/*
	if(fEntityTag != "" and fEntityTag != list[index]) {
		for(int i = 0;i < list.size();i++) {
			if(fEntityTag == list[i]) {
				index = i;
			}
		}
	}
*/


	if(!listChar.empty()) {

	//	if(ImGui::Combo("Select Entity", &index, listChar.data(), listChar.size())) {
	//		fEntityTag = list[index];
	//	}
		if(ImGui::ListBox("Select Entity", &index, listChar.data(), listChar.size())) {
			/*
			fEntityTag = list[index];
			fCreateEntity = true;
			*/
		}
	}
}

void Interface::animationSelectorUI() {
	static std::vector<std::string> list;
	static std::vector<const char*> listChar;
	//static std::string prevEntityTag = fEntityTag;
	static int index = 0;
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


	if(!listChar.empty()) {
		ImGui::ListBox("Select Animation", &index, listChar.data(), listChar.size());
//		fAnimationTag = list[index];
	}

//	ImGui::InputInt("Layer", &fLayer);

}

void Interface::moveEntityUI() {
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
}

void Interface::saveUI() {
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
}

// Private
