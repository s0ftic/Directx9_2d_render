#pragma once

#include "directx9.h"
#include "ui.h"

enum RenderDevices : int
{
	DirectX9Device = 1
};

class RenderPipeline
{
private:
	RenderPipeline() { ui = Ui::GetSingleton(); };
	~RenderPipeline() {};
	
	static RenderPipeline* instance;
	RenderDevices render_devaice;

	CBaseRenderDevice* render;
	Ui* ui;
public:
	static RenderPipeline* GetSingleton() {
		if (!instance) instance = new RenderPipeline();
		return instance;
	}

	void SetRenderDevice(RenderDevices device);

	void BeginScene();
	void DrawSceneContent();
	void EndScene();
};

