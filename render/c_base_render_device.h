#pragma once
#include "math.h"

typedef unsigned long DWORD;

class CBaseRenderDevice
{
public:
	virtual void BeginScene() {};
	virtual void EndScene() {};

	virtual void DrawRect(iVec2 pos, iVec2 size,int think, DWORD color) {};
	virtual void DrawRectFiled(iVec2 pos, iVec2 size, DWORD color) {};
	virtual void DrawLine(iVec2 p1, iVec2 p2, int think, DWORD color) {};
	virtual void DrawCircle(iVec2 pos, float radius, int think, int number_of_sections, DWORD color) {};
	virtual void DrawString(iVec2 pos, const char* text, DWORD color) {};
	virtual void* LoadImageFromFile(const char* file, iVec2 size) { return nullptr; };
	virtual void DrawImage(void* image,iVec2 pos) {};
	virtual void DrawStringW(iVec2 pos, const wchar_t* text, DWORD color) {};
	virtual int  GetTextWith(const char* text) { return 1; };
};


