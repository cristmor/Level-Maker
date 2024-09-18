#include "Interface.h"

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
	ImGui::SetNextWindowSize({400, 400});
	ImGui::Begin("Level Editor");

	// UI Elements
	pathUI();
	mousePositionUI();
	ImGui::Separator();
	entitySelectorUI();

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

	if(!listChar.empty()) {
	//	if(ImGui::Combo("Select Entity", &index, listChar.data(), listChar.size())) {
	//		fEntityTag = list[index];
	//	}
		ImGui::ListBox("Select Entity", &index, listChar.data(), listChar.size());
		fEntityTag = list[index];
	}
}

// Get Data From UI Componets
const std::string Interface::getEntityTag() const {
	return fEntityTag;
}

// Private
