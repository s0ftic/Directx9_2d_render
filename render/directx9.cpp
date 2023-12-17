#include "directx9.h"

#include "window_manager.h"

DirectX9::DirectX9()
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 OutPut = {};

	WindowManager* window = WindowManager::GetSingleton();

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = window->GetWindowDescriptor();
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = window->GetSharedSettings()->size_w;
	d3dpp.BackBufferHeight = window->GetSharedSettings()->size_h;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT res = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->GetWindowDescriptor(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &OutPut);

	D3DXCreateFont(OutPut, 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Arial16);

	this->Device = OutPut;
}


void DirectX9::BeginScene()
{
	Device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0);
	Device->BeginScene();
}

void DirectX9::EndScene()
{
	Device->EndScene();
	Device->Present(nullptr, nullptr, nullptr, nullptr);
}

void DirectX9::DrawRect(iVec2 pos, iVec2 size, int think, DWORD color)
{
	int x = pos.x;
	int y = pos.y;
	int w = size.y;
	int h = size.y;

	ID3DXLine* p_Line;
	D3DXCreateLine(Device, &p_Line);
	D3DXVECTOR2 positions[5];
	positions[0] = D3DXVECTOR2(x, y);
	positions[1] = D3DXVECTOR2(x + w, y);
	positions[2] = D3DXVECTOR2(x + w, y + h);
	positions[3] = D3DXVECTOR2(x, y + h);
	positions[4] = D3DXVECTOR2(x, y);
	p_Line->SetWidth(think);
	p_Line->Draw(positions, 5, color);
	p_Line->End();
	p_Line->Release();
}

void DirectX9::DrawRectFiled(iVec2 pos, iVec2 size, DWORD color)
{
	D3DRECT rect = { pos.x,pos.y,pos.x + size.x,pos.y + size.y };
	Device->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DirectX9::DrawLine(iVec2 p1, iVec2 p2, int think, DWORD color)
{
	ID3DXLine* line;
	D3DXCreateLine(Device, &line);
	D3DXVECTOR2 linePos[] = { D3DXVECTOR2(p1.x,p1.y),D3DXVECTOR2(p2.x,p2.y) };
	line->SetWidth(think);
	line->SetAntialias(true);
	line->SetGLLines(true);
	line->Begin();
	line->Draw(linePos, 2, color);
	line->End();
	line->Release();
}

void DirectX9::DrawCircle(iVec2 pos, float radius, int think, int number_of_sections, DWORD color)
{
	ID3DXLine* p_Line;
	D3DXCreateLine(Device, &p_Line);
	float si, co, nsi, nco, sw;
	bool antialiasing = p_Line->GetAntialias();
	p_Line->SetAntialias(true);
	sw = p_Line->GetWidth();
	p_Line->SetWidth(think);
	D3DXVECTOR2 rect[2];

	float step = M_PI * 2.0 / number_of_sections;
	float dec = step / 50;

	for (float i = 0; i < M_PI * 2.0; i += step)
	{
		si = pos.x + (sin(i - dec) * radius);
		co = pos.y + (cos(i - dec) * radius);

		nsi = pos.x + (sin(i + step + dec) * radius);
		nco = pos.y + (cos(i + step + dec) * radius);

		rect[0].x = si;
		rect[0].y = co;

		rect[1].x = nsi;
		rect[1].y = nco;

		p_Line->Draw(rect, 2, color);
	}
	p_Line->SetAntialias(antialiasing);
	p_Line->SetWidth(sw);
}

void DirectX9::DrawString(iVec2 pos, const char* text, DWORD color)
{
	RECT fontPos = { pos.x,pos.y,0,0 };
	Arial16->DrawTextA(NULL, text, -1, &fontPos, DT_NOCLIP, color);
}

void* DirectX9::LoadImageFromFile(const char* file, iVec2 size)
{
	LPDIRECT3DTEXTURE9 texture = nullptr;
	D3DXCreateTextureFromFileExA(Device, file, size.x, size.y, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, 0, 0, &texture);
	void* texture_ptr = malloc(sizeof(LPDIRECT3DTEXTURE9));
	memcpy(texture_ptr, &texture, sizeof(LPDIRECT3DTEXTURE9));
	return texture_ptr;
}

void DirectX9::DrawImage(void* image, iVec2 pos)
{
	LPD3DXSPRITE sprite;
	D3DXCreateSprite(Device,&sprite);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 pos3d;
	pos3d.x = pos.x;
	pos3d.y = pos.y;
	pos3d.z = 0;

	LPDIRECT3DTEXTURE9 texture = *static_cast<LPDIRECT3DTEXTURE9*>(image);


	sprite->Draw(texture,NULL,NULL,&pos3d, D3DXCOLOR(255,255,255,255));
	sprite->End();
	sprite->Release();
}

void DirectX9::DrawStringW(iVec2 pos, const wchar_t* text, DWORD color)
{
	RECT fontPos = { pos.x,pos.y,0,0 };
	Arial16->DrawTextW(NULL, text, -1, &fontPos, DT_NOCLIP, color);
}

int  DirectX9::GetTextWith(const char* text)
{
	RECT rcRect = { 0 };
	Arial16->DrawText(NULL, text, strlen(text), &rcRect, DT_CALCRECT,D3DCOLOR_XRGB(0, 0, 0));
	return rcRect.right - rcRect.left;
}