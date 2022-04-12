#include "pch.h"
#include "RLFocus.h"

std::string RLFocus::GetPluginName() {
	return "Window Focus";
}

void RLFocus::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void RLFocus::RenderSettings() {

	CVarWrapper RLFocus_Mode = cvarManager->getCvar("RLFocus_Mode");
	if (!RLFocus_Mode) { return; }
	int Plugin_Mode = RLFocus_Mode.getIntValue();

	if(ImGui::RadioButton("Plugin disabled", &Plugin_Mode, 0))
		RLFocus_Mode.setValue(Plugin_Mode);

	ImGui::SameLine();
	if(ImGui::RadioButton("Activate sound", &Plugin_Mode, 1))
		RLFocus_Mode.setValue(Plugin_Mode);

	ImGui::SameLine();
	if(ImGui::RadioButton("Set Window-Focus", &Plugin_Mode, 2))
		RLFocus_Mode.setValue(Plugin_Mode);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Note: Focus does not work in Fullscreen Mode\nIf you want to focus RocketLeague change the Display Mode to Borderless/Windowed");


	ImGui::NewLine();
	ImGui::Text("Focus/activate sound:");

	CVarWrapper onKickOff = cvarManager->getCvar("onKickOff");
	if (!onKickOff) return;
	bool onKickOffEnabled = onKickOff.getBoolValue();
	if (ImGui::Checkbox("on kickoff countdown", &onKickOffEnabled))
		onKickOff.setValue(onKickOffEnabled);
	if (ImGui::IsItemHovered()) 
		ImGui::SetTooltip("Set focus/activate sound when a kickoff starts");

	CVarWrapper onGameJoin = cvarManager->getCvar("onGameJoin");
	if (!onGameJoin) return;
	bool onGameJoinEnabled = onGameJoin.getBoolValue();
	if (ImGui::Checkbox("on joining countdown", &onGameJoinEnabled)) 
		onGameJoin.setValue(onGameJoinEnabled);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Set focus/activate sound when you join a game");

	CVarWrapper onGameStart = cvarManager->getCvar("onGameStart");
	if (!onGameStart) return;
	bool onGameStartEnabled = onGameStart.getBoolValue();
	if (ImGui::Checkbox("on game start", &onGameStartEnabled)) 
		onGameStart.setValue(onGameStartEnabled);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Set focus/activate sound when a game starts");

	ImGui::NewLine();
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.4f, 0.5f), "Made by LchmagKekse");
}