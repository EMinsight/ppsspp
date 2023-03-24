// Copyright (c) 2012- PPSSPP Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official git repository and contact information can be found at
// https://github.com/hrydgard/ppsspp and http://www.ppsspp.org/.

#include "../Core/Host.h"
#include "InputDevice.h"
#include "Common/CommonWindows.h"
#include <list>
#include <memory>

extern float g_mouseDeltaX;
extern float g_mouseDeltaY;

class WindowsHost : public Host {
public:
	WindowsHost();

	~WindowsHost() {
		UpdateConsolePosition();
	}

	void PollControllers() override;

	void ToggleDebugConsoleVisibility() override;

	bool CreateDesktopShortcut(std::string argumentPath, std::string title) override;

	void NotifyUserMessage(const std::string &message, float duration = 1.0f, u32 color = 0x00FFFFFF, const char *id = nullptr) override;
	void SendUIMessage(const std::string &message, const std::string &value) override;

private:
	void SetConsolePosition();
	void UpdateConsolePosition();

	size_t numDinputDevices_ = 0;

	std::list<std::unique_ptr<InputDevice>> input;
};
