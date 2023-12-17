#include "include.h"

#include "window_manager.h"
#include "render_pipeline.h"

LRESULT WINAPI wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
}

WindowManager* window_manager;

int CrateWindow()
{
	window_manager = WindowManager::GetSingleton();
	WindowPropertys* propertys = window_manager->GetSharedSettings();

	propertys->name = "TestRender";
	propertys->flags = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;

	propertys->size_w = 800;
	propertys->size_h = 600;

	propertys->start_pos_x = 0;
	propertys->start_pos_y = 0;

	if (!window_manager->SpawnWindow(wnd_proc)) {
		return STATUS_ERROR;
	}

	return STATUS_SUCCESS;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
	if (CrateWindow() != STATUS_SUCCESS) {
		return STATUS_ERROR;
	}
	
	RenderPipeline* render_pipeline = RenderPipeline::GetSingleton();
	render_pipeline->SetRenderDevice(DirectX9Device);

	do
	{
		window_manager->HandleMessage();

		render_pipeline->BeginScene();
		render_pipeline->DrawSceneContent();
		render_pipeline->EndScene();

	} while (window_manager->IsActive());

    return STATUS_SUCCESS;
}