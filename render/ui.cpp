#include "ui.h"

void Ui::RenderUi(CBaseRenderDevice* render)
{
	render->DrawRectFiled(iVec2(100, 100), iVec2(100, 100), D3DXCOLOR(255, 255, 255, 255));
	render->DrawCircle(iVec2(260, 150), 50, 1, 360, D3DXCOLOR(255, 255, 255, 255));
	render->DrawRect(iVec2(320, 100), iVec2(100, 100), 1, D3DXCOLOR(255, 255, 255, 255));
	render->DrawLine(iVec2(430, 100), iVec2(530, 200), 1, D3DXCOLOR(255, 255, 255, 255));
	render->DrawString(iVec2(100, 210), "Test Text", D3DXCOLOR(255, 255, 255, 255));
	render->DrawStringW(iVec2(100, 230), L"Test TextW", D3DXCOLOR(255, 255, 255, 255));

	static void* test_texture = nullptr;

	if (!test_texture) {
		test_texture = render->LoadImageFromFile("C:\\Users\****\\source\\repos\\*******\\x64\\Debug\\data.jpg", iVec2(0, 0));
	}

	render->DrawImage(test_texture, iVec2(540, 100));
}

Ui* Ui::instance = nullptr;