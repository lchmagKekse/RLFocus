#include "pch.h"
#include "RLFocus.h"
#include <Windows.h>


BAKKESMOD_PLUGIN(RLFocus, "Window Focus", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void RLFocus::onLoad()
{
	_globalCvarManager = cvarManager;

	cvarManager->registerCvar("RLFocus_Mode", "0", "0 = disabled, 1 = only sound, 2 = set focus to RL", false, true, 0, true, 2)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		Plugin_Mode = cvar.getIntValue();
	});

	cvarManager->registerCvar("onKickOff", "0", "Focus on KickOff", false, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		onKickOff = cvar.getBoolValue();
	});

	cvarManager->registerCvar("onGameJoin", "0", "Focus on GameJoin", false, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		onGameJoin = cvar.getBoolValue();
	});

	cvarManager->registerCvar("onGameStart", "0", "Focus on GameStart", false, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		onGameStart = cvar.getBoolValue();
	});

	gameWrapper->HookEventPost("Function GameEvent_Soccar_TA.Countdown.BeginState",
		[this](std::string eventName) {
		if(onKickOff && Plugin_Mode != 0 && gameWrapper->IsInOnlineGame())
			setFocus();
	});

	gameWrapper->HookEventPost("Function ProjectX.OnlineGameJoinGame_X.StartJoin",
		[this](std::string eventName) {
		if (onGameJoin && Plugin_Mode != 0)
			setFocus();
	});

	gameWrapper->HookEventPost("Function TAGame.Team_TA.PostBeginPlay",
		[this](std::string eventName) {
		if(onGameStart && Plugin_Mode != 0)
			setFocus();
	});
}

void RLFocus::onUnload()
{
}

void RLFocus::setFocus() {

	HWND RocketLeague = FindWindowA(NULL, "Rocket League (64-bit, DX11, Cooked)");

	if (!RocketLeague) return;

	if (Plugin_Mode == 1) {
		SendMessage(RocketLeague, WM_SETFOCUS, 0, 0);
		return;
	}

	if (Plugin_Mode == 2) {
		SetForegroundWindow(RocketLeague);
		return;
	}
}