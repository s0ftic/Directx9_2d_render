#pragma once
#include "window_def.h"

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

class WindowManager 
{
private:
	WindowManager() {};
	~WindowManager() {};

	static WindowManager* instance;
	WindowPropertys* shared_settings;

	//class instance
	HWND window_descriptor;
	MSG window_message;
public:
	bool IsActive();
	void HandleMessage();

	HWND GetWindowDescriptor();

	bool SpawnWindow(WNDPROC proc);

	//singletone instances
	static WindowManager* GetSingleton() {
		if (!instance) instance = new WindowManager();
		return instance;
	}

	//return window sherad settings
	WindowPropertys* GetSharedSettings()
	{
		if (!instance) return nullptr;

		//init shared_settings if nullptr
		if (!shared_settings) {
			shared_settings = new WindowPropertys();

			shared_settings->name = "";
			shared_settings->flags = 0;

			shared_settings->size_w = 0;
			shared_settings->size_h = 0;

			shared_settings->start_pos_x = 0;
			shared_settings->start_pos_y = 0;
		}

		return shared_settings;
	}
};
#endif // !WINDOW_MANAGER_H

