#include "Interface.h"
#include "imgui.h"

Interface::Interface(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<Assets>& assets):
	fWindow(window),
	fAssets(assets) {
	if(!ImGui::SFML::Init(*window)) {
		std::cerr << "Error: Failed to load ImGui" << std::endl;
	}
}

Interface::~Interface() {
}

// Public
void Interface::whileRun() {
	mousePosition = sf::Mouse::getPosition(*fWindow);

	ImGui::SFML::Update(*fWindow, fClock.restart());
	ImGui::SetNextWindowSize({400, 600});
	ImGui::Begin("Level Editor");

	// UI Elements
	ImGui::SeparatorText("Basic Information");
	pathUI();
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
	ImGui::SFML::Render(*fWindow);
}

void Interface::events(const sf::Event& event) {
	ImGui::SFML::ProcessEvent(*fWindow, event);
}

// Public UI Componets
void Interface::pathUI() {
	static std::string str = "Level path: " + OUTPUT_FILENAME;
	static int strSize = str.size() + 1;
	char label[20];
	std::strncpy(label, str.c_str(), strSize);
	ImGui::Text(label, IM_ARRAYSIZE(label));

}

void Interface::mousePositionUI() {
	ImGui::Text("Mouse Position: (%d, %d)\n", mousePosition.x, mousePosition.y);
}

void Interface::entitySelectorUI() {
	static std::vector<std::string> list = fAssets->listEntityTags();
	static std::vector<const char*> listChar;
	static int index = 0;
	if(listChar.empty()) {
		for(std::string& tag: list) {
			listChar.push_back(tag.c_str());
		}
	}

	if(fEntityTag != "" and fEntityTag != list[index]) {
		for(int i = 0;i < list.size();i++) {
			if(fEntityTag == list[i]) {
				index = i;
			}
		}
	}


	if(!listChar.empty()) {

	//	if(ImGui::Combo("Select Entity", &index, listChar.data(), listChar.size())) {
	//		fEntityTag = list[index];
	//	}
		if(ImGui::ListBox("Select Entity", &index, listChar.data(), listChar.size())) {
			fEntityTag = list[index];
			fCreateEntity = true;
		}
	}
}

void Interface::animationSelectorUI() {
	static std::vector<std::string> list;
	static std::vector<const char*> listChar;
	static std::string prevEntityTag = fEntityTag;
	static int index = 0;
	if(fEntityTag != prevEntityTag) {
		listChar.clear();
		list = fAssets->listAnimationTags(fEntityTag);
		for(std::string& tag: list) {
			listChar.push_back(tag.c_str());
		}
		prevEntityTag = fEntityTag;
	}

	if(fAnimationTag!= "" and fAnimationTag != list[index]) {
		for(int i = 0;i < list.size();i++) {
			if(fAnimationTag == list[i]) {
				index = i;
			}
		}
	}


	if(!listChar.empty()) {
		ImGui::ListBox("Select Animation", &index, listChar.data(), listChar.size());
		fAnimationTag = list[index];
	}

	ImGui::InputInt("Layer", &fLayer);

}

void Interface::moveEntityUI() {
	ImGui::Checkbox("Follow Mouse", &fFollowMouse);
	ImGui::Checkbox("Snap Grid", &fSnapGrid);
	ImGui::Checkbox("Show Grid", &fShowGrid);
	if(ImGui::Button("Delete")) {
		fDeleteEntity = true;
	}
}

void Interface::saveUI() {
	ImGui::SeparatorText("File Settings");
	char buf[32];
	std::strncpy(buf, fFilename.c_str(), 32);
	ImGui::InputText("File Name", buf, IM_ARRAYSIZE(buf));
	fFilename = buf;

	if (ImGui::Button("Save")) {
		fSave = true;
	}
	ImGui::SameLine();
	if(ImGui::Button("Load")) {
		fLoad = true;
	}
}

// Get Data From UI Componets
const std::string Interface::getEntityTag() const {
	return fEntityTag;
}

const std::string Interface::getAnimation() const {
	return fAnimationTag;
}

const std::string Interface::getFilename() const {
	return fFilename;
}

int& Interface::layer() {
	return fLayer;
}

bool& Interface::followMouse() {
	return fFollowMouse;
}

bool& Interface::snapGrid() {
	return fSnapGrid;
}

bool& Interface::showGrid() {
	return fShowGrid;
}

bool& Interface::createEntity() {
	return fCreateEntity;
}

bool& Interface::deleteEntity() {
	return fDeleteEntity;
}

bool& Interface::save() {
	return fSave;
}

bool& Interface::load() {
	return fLoad;
}

void Interface::setEntityTag(const std::string& tag) {
	fEntityTag = tag;
}

void Interface::setAnimationTag(const std::string& tag) {
	fAnimationTag = tag;
}

void Interface::setLayer(const int& layer) {
	fLayer = layer;
}

// Private
