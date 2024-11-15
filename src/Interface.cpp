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

	static std::string& entityTag = AppState::getInstance().entityTag();
	static std::string& animationTag = AppState::getInstance().animtionTag();
	static bool& newEntity = AppState::getInstance().newEntity();
	static bool& deleteEntity = AppState::getInstance().deleteEntity();

	static int eIndex = 0;
	static int aIndex = 0;
	static std::vector<const char*> entityList = AppState::getInstance().textureList();
	static std::vector<const char*> animationList = AppState::getInstance().animationList(entityList[aIndex]);

	if(ImGui::ListBox("Select Entity", &eIndex, entityList.data(), entityList.size())) {
		animationList = AppState::getInstance().animationList(entityList[eIndex]);
		aIndex = 0;
	}
	entityTag = entityList[eIndex];

	ImGui::BeginDisabled(!animationList.size());
	ImGui::ListBox("Select Animation", &aIndex, animationList.data(), animationList.size());
	ImGui::EndDisabled();
	if(animationList.size()) {
		animationTag = animationList[aIndex];
	}

	if(ImGui::Button("Create")) {
		newEntity = true;
	}
	ImGui::SameLine();
	if(ImGui::Button("Delete")) {
		deleteEntity = true;
	}

	//
	// animationSelectorUI();
	//
	ImGui::SeparatorText("Placement Options");
	static bool& followMouse = AppState::getInstance().followMouse();
	static bool& snapGrid = AppState::getInstance().snapGrid();
	static bool& showGrid = AppState::getInstance().showGrid();

	ImGui::Checkbox("Follow Mouse", &followMouse);
	ImGui::Checkbox("Snap Grid", &snapGrid);
	ImGui::Checkbox("Show Grid", &showGrid);

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
		load = true;
	}

	ImGui::End();
}

// Private
