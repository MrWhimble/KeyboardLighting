// KeyboardLighting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS

#include <CUESDK.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <atomic>
#include <thread>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <Windows.h>
#include <algorithm>
#include <numeric>

using namespace std;

const CorsairLedId DWordToLedId(DWORD w) {
	switch (w) {
	case 0x08: return CLK_Backspace;
	case 0x09: return CLK_Tab;
	case 0x0D: return CLK_Enter;
	case 0x13: return CLK_PauseBreak;
	case 0x14: return CLK_CapsLock;
	case 0x1B: return CLK_Escape;
	case 0x20: return CLK_Space;
	case 0x21: return CLK_PageUp;
	case 0x22: return CLK_PageDown;
	case 0x23: return CLK_End;
	case 0x24: return CLK_Home;
	case 0x25: return CLK_LeftArrow;
	case 0x26: return CLK_UpArrow;
	case 0x27: return CLK_RightArrow;
	case 0x28: return CLK_DownArrow;
	case 0x2C: return CLK_PrintScreen;
	case 0x2D: return CLK_Insert;
	case 0x2E: return CLK_Delete;
	case 0x30: return CLK_0;
	case 0x31: return CLK_1;
	case 0x32: return CLK_2;
	case 0x33: return CLK_3;
	case 0x34: return CLK_4;
	case 0x35: return CLK_5;
	case 0x36: return CLK_6;
	case 0x37: return CLK_7;
	case 0x38: return CLK_8;
	case 0x39: return CLK_9;
	case 0x41: return CLK_A;
	case 0x42: return CLK_B;
	case 0x43: return CLK_C;
	case 0x44: return CLK_D;
	case 0x45: return CLK_E;
	case 0x46: return CLK_F;
	case 0x47: return CLK_G;
	case 0x48: return CLK_H;
	case 0x49: return CLK_I;
	case 0x4A: return CLK_J;
	case 0x4B: return CLK_K;
	case 0x4C: return CLK_L;
	case 0x4D: return CLK_M;
	case 0x4E: return CLK_N;
	case 0x4F: return CLK_O;
	case 0x50: return CLK_P;
	case 0x51: return CLK_Q;
	case 0x52: return CLK_R;
	case 0x53: return CLK_S;
	case 0x54: return CLK_T;
	case 0x55: return CLK_U;
	case 0x56: return CLK_V;
	case 0x57: return CLK_W;
	case 0x58: return CLK_X;
	case 0x59: return CLK_Y;
	case 0x5A: return CLK_Z;
	case 0x5B: return CLK_LeftGui;
	case 0x5D: return CLK_Application;
	case 0x60: return CLK_Keypad0;
	case 0x61: return CLK_Keypad1;
	case 0x62: return CLK_Keypad2;
	case 0x63: return CLK_Keypad3;
	case 0x64: return CLK_Keypad4;
	case 0x65: return CLK_Keypad5;
	case 0x66: return CLK_Keypad6;
	case 0x67: return CLK_Keypad7;
	case 0x68: return CLK_Keypad8;
	case 0x69: return CLK_Keypad9;
	case 0x6A: return CLK_KeypadAsterisk;
	case 0x6B: return CLK_KeypadPlus;
	case 0x6C: return CLK_KeypadEnter; // seperator key
	case 0x6D: return CLK_KeypadMinus;
	case 0x6E: return CLK_KeypadPeriodAndDelete;
	case 0x6F: return CLK_KeypadSlash;
	case 0x70: return CLK_F1;
	case 0x71: return CLK_F2;
	case 0x72: return CLK_F3;
	case 0x73: return CLK_F4;
	case 0x74: return CLK_F5;
	case 0x75: return CLK_F6;
	case 0x76: return CLK_F7;
	case 0x77: return CLK_F8;
	case 0x78: return CLK_F9;
	case 0x79: return CLK_F10;
	case 0x7A: return CLK_F11;
	case 0x7B: return CLK_F12;
	case 0x90: return CLK_NumLock;
	case 0x91: return CLK_ScrollLock;
	case 0xA0: return CLK_LeftShift;
	case 0xA1: return CLK_RightShift;
	case 0xA2: return CLK_LeftCtrl;
	case 0xA3: return CLK_RightCtrl;
	case 0xA4: return CLK_LeftAlt;
	case 0xA5: return CLK_RightAlt;
	case 0xAD: return CLK_Mute;
	case 0xAE: return CLK_VolumeDown;
	case 0xAF: return CLK_VolumeUp;
	case 0xB0: return CLK_ScanNextTrack;
	case 0xB1: return CLK_ScanPreviousTrack;
	case 0xB2: return CLK_Stop;
	case 0xB3: return CLK_PlayPause;
	case 0xBA: return CLK_SemicolonAndColon;
	case 0xBB: return CLK_EqualsAndPlus;
	case 0xBC: return CLK_CommaAndLessThan;
	case 0xBD: return CLK_MinusAndUnderscore;
	case 0xBE: return CLK_PeriodAndBiggerThan;
	case 0xBF: return CLK_SlashAndQuestionMark;
	case 0xC0: return CLK_ApostropheAndDoubleQuote;
	case 0xDB: return CLK_BracketLeft;
	case 0xDC: return CLK_NonUsBackslash;
	case 0xDD: return CLK_BracketRight;
	case 0xDE: return CLK_NonUsTilde;
	case 0xDF: return CLK_GraveAccentAndTilde;
	default: std::cout << w << "\n"; return CLI_Invalid;
	}
}
const char* LedIdToString(CorsairLedId id) {
	switch (id) {
	case CLK_0: return "CLK_0";
	case CLK_1: return "CLK_1";
	case CLK_2: return "CLK_2";
	case CLK_3: return "CLK_3";
	case CLK_4: return "CLK_4";
	case CLK_5: return "CLK_5";
	case CLK_6: return "CLK_6";
	case CLK_7: return "CLK_7";
	case CLK_8: return "CLK_8";
	case CLK_9: return "CLK_9";
	case CLK_A: return "CLK_A";
	case CLK_ApostropheAndDoubleQuote: return "CLK_ApostropheAndDoubleQuote";
	case CLK_Application: return "CLK_Application";
	case CLK_B: return "CLK_B";
	case CLK_Backslash: return "CLK_Backslash";
	case CLK_Backspace: return "CLK_Backspace";
	case CLK_BracketLeft: return "CLK_BracketLeft";
	case CLK_BracketRight: return "CLK_BracketRight";
	case CLK_Brightness: return "CLK_Brightness";
	case CLK_C: return "CLK_C";
	case CLK_CapsLock: return "CLK_CapsLock";
	case CLK_CommaAndLessThan: return "CLK_CommaAndLessThan";
	case CLK_D: return "CLK_D";
	case CLK_Delete: return "CLK_Delete";
	case CLK_DownArrow: return "CLK_DownArrow";
	case CLK_E: return "CLK_E";
	case CLK_End: return "CLK_End";
	case CLK_Enter: return "CLK_Enter";
	case CLK_EqualsAndPlus: return "CLK_EqualsAndPlus";
	case CLK_Escape: return "CLK_Escape";
	case CLK_F: return "CLK_F";
	case CLK_F1: return "CLK_F1";
	case CLK_F10: return "CLK_F10";
	case CLK_F11: return "CLK_F11";
	case CLK_F12: return "CLK_F12";
	case CLK_F2: return "CLK_F2";
	case CLK_F3: return "CLK_F3";
	case CLK_F4: return "CLK_F4";
	case CLK_F5: return "CLK_F5";
	case CLK_F6: return "CLK_F6";
	case CLK_F7: return "CLK_F7";
	case CLK_F8: return "CLK_F8";
	case CLK_F9: return "CLK_F9";
	case CLK_Fn: return "CLK_Fn";
	case CLK_G: return "CLK_G";
	case CLK_G1: return "CLK_G1";
	case CLK_G10: return "CLK_G10";
	case CLK_G11: return "CLK_G11";
	case CLK_G12: return "CLK_G12";
	case CLK_G13: return "CLK_G13";
	case CLK_G14: return "CLK_G14";
	case CLK_G15: return "CLK_G15";
	case CLK_G16: return "CLK_G16";
	case CLK_G17: return "CLK_G17";
	case CLK_G18: return "CLK_G18";
	case CLK_G2: return "CLK_G2";
	case CLK_G3: return "CLK_G3";
	case CLK_G4: return "CLK_G4";
	case CLK_G5: return "CLK_G5";
	case CLK_G6: return "CLK_G6";
	case CLK_G7: return "CLK_G7";
	case CLK_G8: return "CLK_G8";
	case CLK_G9: return "CLK_G9";
	case CLK_GraveAccentAndTilde: return "CLK_GraveAccentAndTilde";
	case CLK_H: return "CLK_H";
	case CLK_Home: return "CLK_Home";
	case CLK_I: return "CLK_I";
	case CLK_Insert: return "CLK_Insert";
	case CLK_International1: return "CLK_International1";
	case CLK_International2: return "CLK_International2";
	case CLK_International3: return "CLK_International3";
	case CLK_International4: return "CLK_International4";
	case CLK_International5: return "CLK_International5";
	case CLK_J: return "CLK_J";
	case CLK_K: return "CLK_K";
	case CLK_Keypad0: return "CLK_Keypad0";
	case CLK_Keypad1: return "CLK_Keypad1";
	case CLK_Keypad2: return "CLK_Keypad2";
	case CLK_Keypad3: return "CLK_Keypad3";
	case CLK_Keypad4: return "CLK_Keypad4";
	case CLK_Keypad5: return "CLK_Keypad5";
	case CLK_Keypad6: return "CLK_Keypad6";
	case CLK_Keypad7: return "CLK_Keypad7";
	case CLK_Keypad8: return "CLK_Keypad8";
	case CLK_Keypad9: return "CLK_Keypad9";
	case CLK_KeypadAsterisk: return "CLK_KeypadAsterisk";
	case CLK_KeypadComma: return "CLK_KeypadComma";
	case CLK_KeypadEnter: return "CLK_KeypadEnter";
	case CLK_KeypadMinus: return "CLK_KeypadMinus";
	case CLK_KeypadPeriodAndDelete: return "CLK_KeypadPeriodAndDelete";
	case CLK_KeypadPlus: return "CLK_KeypadPlus";
	case CLK_KeypadSlash: return "CLK_KeypadSlash";
	case CLK_L: return "CLK_L";
	case CLK_Lang1: return "CLK_Lang1";
	case CLK_Lang2: return "CLK_Lang2";
	case CLK_LedProgramming: return "CLK_LedProgramming";
	case CLK_LeftAlt: return "CLK_LeftAlt";
	case CLK_LeftArrow: return "CLK_LeftArrow";
	case CLK_LeftCtrl: return "CLK_LeftCtrl";
	case CLK_LeftGui: return "CLK_LeftGui";
	case CLK_LeftShift: return "CLK_LeftShift";
	case CLK_Logo: return "CLK_Logo";
	case CLK_M: return "CLK_M";
	case CLK_M1: return "CLK_M1";
	case CLK_M2: return "CLK_M2";
	case CLK_M3: return "CLK_M3";
	case CLK_MinusAndUnderscore: return "CLK_MinusAndUnderscore";
	case CLK_MR: return "CLK_MR";
	case CLK_Mute: return "CLK_Mute";
	case CLK_N: return "CLK_N";
	case CLK_NonUsBackslash: return "CLK_NonUsBackslash";
	case CLK_NonUsTilde: return "CLK_NonUsTilde";
	case CLK_NumLock: return "CLK_NumLock";
	case CLK_O: return "CLK_O";
	case CLK_P: return "CLK_P";
	case CLK_PageDown: return "CLK_PageDown";
	case CLK_PageUp: return "CLK_PageUp";
	case CLK_PauseBreak: return "CLK_PauseBreak";
	case CLK_PeriodAndBiggerThan: return "CLK_PeriodAndBiggerThan";
	case CLK_PlayPause: return "CLK_PlayPause";
	case CLK_PrintScreen: return "CLK_PrintScreen";
	case CLK_Profile: return "CLK_Profile";
	case CLK_Q: return "CLK_Q";
	case CLK_R: return "CLK_R";
	case CLK_RightAlt: return "CLK_RightAlt";
	case CLK_RightArrow: return "CLK_RightArrow";
	case CLK_RightCtrl: return "CLK_RightCtrl";
	case CLK_RightGui: return "CLK_RightGui";
	case CLK_RightShift: return "CLK_RightShift";
	case CLK_S: return "CLK_S";
	case CLK_ScanNextTrack: return "CLK_ScanNextTrack";
	case CLK_ScanPreviousTrack: return "CLK_ScanPreviousTrack";
	case CLK_ScrollLock: return "CLK_ScrollLock";
	case CLK_SemicolonAndColon: return "CLK_SemicolonAndColon";
	case CLK_SlashAndQuestionMark: return "CLK_SlashAndQuestionMark";
	case CLK_Space: return "CLK_Space";
	case CLK_Stop: return "CLK_Stop";
	case CLK_T: return "CLK_T";
	case CLK_Tab: return "CLK_Tab";
	case CLK_U: return "CLK_U";
	case CLK_UpArrow: return "CLK_UpArrow";
	case CLK_V: return "CLK_V";
	case CLK_VolumeDown: return "CLK_VolumeDown";
	case CLK_VolumeUp: return "CLK_VolumeUp";
	case CLK_W: return "CLK_W";
	case CLK_WinLock: return "CLK_WinLock";
	case CLK_X: return "CLK_X";
	case CLK_Y: return "CLK_Y";
	case CLK_Z: return "CLK_Z";
	default: return "UNKNOWN";
	}
}
const char* toString(CorsairError error)
{
	switch (error) {
	case CE_Success: return "CE_Success";
	case CE_ServerNotFound: return "CE_ServerNotFound";
	case CE_NoControl: return "CE_NoControl";
	case CE_ProtocolHandshakeMissing: return "CE_ProtocolHandshakeMissing";
	case CE_IncompatibleProtocol: return "CE_IncompatibleProtocol";
	case CE_InvalidArguments: return "CE_InvalidArguments";
	default: return "unknown error";
	}
}

using KeyData = unordered_map<int /* Key ID */, int /* Number of Presses */>;
using KeyStates = unordered_map<DWORD, bool>;

KeyData keyData = KeyData();
KeyStates keyStates = KeyStates();
int keyboardDeviceIndex;

vector<pair<int, int>> keyDataCounts; // used to sort keys into most presses
int keyDataUniqueCounts; // Number of unique press totals

HHOOK keyboardHook;
HANDLE console;

vector<CorsairLedColor> ledData;

// Functions:
bool SortFunction(pair<int, int> i, pair<int, int> j) { return i.second < j.second; };
int LerpFloor(float a, float b, float t);
vector<string> Split(const string& s, char delim);
string FillString(string original, int size, bool onLeft = true);
CorsairLedColor GetMappedColor(CorsairLedId id, float normalizedValue);

void GotoXY(int x, int y);

void LoadKeyData();
void HandleEnd();

void UpdateKeyDataCounts();
void WriteKeyDataToConsole(CorsairLedId pressed);

LRESULT CALLBACK KeyboardHookProcedure(int nCode, WPARAM wParam, LPARAM lParam);
//LRESULT CALLBACK WindowsProcedure(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam); // Implement later if I can figure it out.
BOOL WINAPI ConsoleHandler(DWORD CEvent);

// MAIN FUNCTION
int main() {
	// Get the Console
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	// Try to connect to Corsair SDK
	while (true) {
		CorsairPerformProtocolHandshake();
		if (const auto error = CorsairGetLastError()) {
			cout << "Handshake failed: " << toString(error) << "\nPress R to retry or any other key to quit" << endl;
			char in = getchar();
			if (in != 'r' && in != 'R') {
				return -1;
			}
		}
		else {
			break;
		}
	}

	// Get connected Corsair devices
	auto deviceCount = CorsairGetDeviceCount();
	if (deviceCount <= 0) {
		cout << "No corsair devices found\nPress any key to quit." << endl;
		getchar();
		return -1;
	}
	// Find a keyboard with lighting capabilities
	for (auto i = 0; i < deviceCount; ++i) {
		auto info = CorsairGetDeviceInfo(i);
		if (info->type == CDT_Keyboard && info->capsMask == (CDC_Lighting)) {
			keyboardDeviceIndex = i;
			if (const auto ledPositions = CorsairGetLedPositionsByDeviceIndex(keyboardDeviceIndex)) {
				for (auto j = 0; j < ledPositions->numberOfLed; ++j) {
					keyData[static_cast<int>(ledPositions->pLedPosition[j].ledId)] = 0;
				}
			}
			break;
		}
	}
	// Check if the keydata was filled out
	if (keyData.empty()) {
		cout << "No keyboard with controllable lighting found\nPress any key to quit." << endl;
		getchar();
		return -1;
	}

	// fill out key states
	for (auto i = 1; i < 255; i++) {
		keyStates[i] = false;
	}

	std::atomic_bool continueExecution{ true };
	std::thread lightingThread([&continueExecution] {
		while (continueExecution) {
			CorsairSetLedsColorsBufferByDeviceIndex(keyboardDeviceIndex, static_cast<int>(ledData.size()), ledData.data());
			CorsairSetLedsColorsFlushBufferAsync(nullptr, nullptr);
			this_thread::sleep_for(chrono::milliseconds(25));
		}
	});

	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProcedure, GetModuleHandle(NULL), NULL);
	if (keyboardHook) {
		if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE) {
			return -1;
		}

		LoadKeyData();

		std::cout << "STARTED KEYBOARD HEATMAPPER\n";
		CorsairRequestControl(CAM_ExclusiveLightingControl);
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	continueExecution = false;
	if (keyboardHook) {
		UnhookWindowsHookEx(keyboardHook);
	}
	// end thread
	lightingThread.join();

	return 0;
}

// Filling functions:
int LerpFloor(float a, float b, float t) {
	return static_cast<int>(a + max<float>(0.f, min<float>(1.f, t)) * (b - a));
}
vector<string> Split(const string& s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}
string FillString(string original, int size, bool onLeft) {
	auto s = original.size();
	if (onLeft) {
		for (auto i = s; i < size; ++i) {
			original.append(" ");
		}
		return original;
	}
	string temp = "";
	for (auto i = 0; i < size - s; ++i) {
		temp.append(" ");
	}
	temp.append(original);
	return temp;
	
}
CorsairLedColor GetMappedColor(CorsairLedId id, float normalizedValue) {
	auto ledColor = CorsairLedColor();
	ledColor.ledId = id;

	if (LedIdToString(id) == "UNKNOWN" || id == CLK_Fn || id == CLK_WinLock || id == CLK_Profile || id == CLK_G1 || id == CLK_G2 || id == CLK_G3 || id == CLK_G4 || id == CLK_G5 || id == CLK_G6) {
		ledColor.r = 255;
		ledColor.g = 0;
		ledColor.b = 255;
		return ledColor;
	}

	if (normalizedValue < 0.25f) {
		ledColor.r = 0;
		ledColor.g = LerpFloor(0.f, 255.f, normalizedValue * 4.f);
		ledColor.b = 255;
	} else if (normalizedValue < 0.5f) {
		ledColor.r = 0;
		ledColor.g = 255;
		ledColor.b = LerpFloor(255.f, 0.f, (normalizedValue - 0.25f) * 4.f);
	} else if(normalizedValue < 0.75f) {
		ledColor.r = LerpFloor(0.f, 255.f, (normalizedValue - 0.5f) * 4.f);
		ledColor.g = 255;
		ledColor.b = 0;
	} else {
		ledColor.r = 255;
		ledColor.g = LerpFloor(255.f, 0.f, (normalizedValue - 0.75f) * 4.f);
		ledColor.b = 0;
	}

	return ledColor;
}

void GotoXY(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(console, pos);
}

void LoadKeyData() {
	string dataString = "";
	fstream dataFile;
	dataFile.open("D:/_KeyboardLightingData/KeyData.txt", ios::in);
	if (!dataFile) {
		return;
	}
	char ch;
	while (true) {
		dataFile >> ch;
		if (dataFile.eof()) { break; }
		dataString += ch;
	}
	dataFile.close();

	cout << "===== LOADING DATA =====\n";

	vector<string> mainVector = Split(dataString, '|');
	vector<string> subVector;
	stringstream stream;
	int id;
	int value;
	for (auto i = 0; i < static_cast<int>(mainVector.size()); ++i) {

		subVector = Split(mainVector[i], '=');
		id = stoi(subVector[0]);
		value = stoi(subVector[1]);
		if (value < 0) value = 0;
		keyData[id] = value;
	}

	UpdateKeyDataCounts();

	WriteKeyDataToConsole(CLI_Invalid);
}
void HandleEnd() {
	cout << "\nSHUTTING DOWN\n";
	if (keyboardHook) {
		UnhookWindowsHookEx(keyboardHook);
	}
	CorsairReleaseControl(CAM_ExclusiveLightingControl);

	fstream dataFile;
	dataFile.open("D:/_KeyboardLightingData/KeyData.txt", ios::out);
	if (!dataFile) {
		return;
	}
	for (auto& keyValue : keyData) {
		dataFile << keyValue.first << "=" << keyValue.second << "|";
	}
	dataFile.close();
	cout << "COMPLETE\n";
	this_thread::sleep_for(chrono::milliseconds(1000));
}

void UpdateKeyDataCounts() {
	keyDataCounts.clear();
	keyDataUniqueCounts = 0;
	for (auto& keyValue : keyData) {
		keyDataCounts.push_back(keyValue);
	}
	sort(keyDataCounts.begin(), keyDataCounts.end(), SortFunction);
	for (auto i = 0; i < keyDataCounts.size(); ++i) {
		if (i != 0 && keyDataCounts[i].second != keyDataCounts[i - 1].second) {
			++keyDataUniqueCounts;
		}
	}
}
void WriteKeyDataToConsole(CorsairLedId pressed) {
	GotoXY(0, 0);
	int uniqueCounts = 0;
	string output = "";
	ledData.clear();
	for (auto i = 0; i < keyDataCounts.size(); ++i) {
		if (i != 0 && keyDataCounts[i].second != keyDataCounts[i - 1].second) {
			++uniqueCounts;
		}
		auto ledColor = GetMappedColor(static_cast<CorsairLedId>(keyDataCounts[i].first), static_cast<float>(uniqueCounts) / static_cast<float>(keyDataUniqueCounts));
		ledData.push_back(ledColor);
		if (LedIdToString(ledColor.ledId) == "UNKNOWN") continue;
		if (pressed == ledColor.ledId) {
			cout << output;
			SetConsoleTextAttribute(console, 4);
			output = "";
			output.append("ID: ");
			output.append(FillString(LedIdToString(static_cast<CorsairLedId>(keyDataCounts[i].first)), 28));
			output.append("[");
			output.append(FillString(to_string(keyDataCounts[i].second), 6, false));
			output.append("] -> R");
			output.append(FillString(to_string(ledColor.r), 3));
			output.append(" G");
			output.append(FillString(to_string(ledColor.g), 3));
			output.append(" B");
			output.append(FillString(to_string(ledColor.b), 3));
			output.append("\n");
			cout << output;
			SetConsoleTextAttribute(console, 7);
			output = "";
			continue;
		}
		output.append("ID: ");
		output.append(FillString(LedIdToString(static_cast<CorsairLedId>(keyDataCounts[i].first)), 28));
		output.append("[");
		output.append(FillString(to_string(keyDataCounts[i].second), 6, false));
		output.append("] -> R");
		output.append(FillString(to_string(ledColor.r), 3));
		output.append(" G");
		output.append(FillString(to_string(ledColor.g), 3));
		output.append(" B");
		output.append(FillString(to_string(ledColor.b), 3));
		output.append("\n");
	}
	output.append("\n");
	cout << output << endl;
}


LRESULT CALLBACK KeyboardHookProcedure(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

	if (nCode == HC_ACTION) {
		if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN) {
			if (p->vkCode) {
				// check if the key isnt already pressed
				if (keyStates[p->vkCode] == false) {
					CorsairLedId id = DWordToLedId(p->vkCode);
					if (id != CLI_Invalid) {
						if (id == CLK_Enter) {
							if ((p->vkCode & LLKHF_EXTENDED) == LLKHF_EXTENDED) {
								id = CLK_KeypadEnter;
							}
						}
						keyData[id] += 1;
						UpdateKeyDataCounts();
						WriteKeyDataToConsole(id);
					}
				}
				keyStates[p->vkCode] = true;
			}
		}
		else if (wParam == WM_SYSKEYUP || wParam == WM_KEYUP) {
			if (p->vkCode) {
				keyStates[p->vkCode] = false;
			}
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
BOOL WINAPI ConsoleHandler(DWORD CEvent) {
	char mesg[128]; // Dont know if this is needed

	switch (CEvent)
	{
	case CTRL_CLOSE_EVENT:
		HandleEnd();
		break;
	case CTRL_SHUTDOWN_EVENT:
		HandleEnd();
		break;
	default: break;

	}
	return TRUE;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
