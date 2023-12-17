#pragma once

#include "include.h"
#include "c_base_render_device.h"

class DirectX9 : public  CBaseRenderDevice
{
public:
	DirectX9();
	~DirectX9() {};

	LPDIRECT3DDEVICE9 Device = nullptr;
	LPD3DXFONT Arial16;

	 void BeginScene() override;
	 void EndScene() override;
	 void DrawRect(iVec2 pos, iVec2 size, int think, DWORD color) override;
	 void DrawRectFiled(iVec2 pos, iVec2 size, DWORD color) override;
	 void DrawLine(iVec2 p1, iVec2 p2, int think, DWORD color) override;
	 void DrawCircle(iVec2 pos, float radius, int think, int number_of_sections, DWORD color) override;
	 void* LoadImageFromFile(const char* file, iVec2 size) override;
	 void DrawImage(void* image, iVec2 pos) override;
	 void DrawString(iVec2 pos, const char* text, DWORD color) override;
	 void DrawStringW(iVec2 pos, const wchar_t* text, DWORD color) override;
	 int  GetTextWith(const char* text) override;
};
