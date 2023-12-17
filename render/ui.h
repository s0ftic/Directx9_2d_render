#pragma once

#include "include.h"
#include "c_base_render_device.h"

class Ui
{
private:
	Ui() {};
	~Ui() {};

	static Ui* instance;
public:
	static Ui* GetSingleton()
	{
		if (!instance) instance = new Ui();
		return instance;
	}

	void RenderUi(CBaseRenderDevice* render);
};

