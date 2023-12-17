#include "render_pipeline.h"

#include "ui.h"

void RenderPipeline::SetRenderDevice(RenderDevices device)
{
	render_devaice = device;
	
	switch (device)
	{
	case DirectX9Device:
		render = new DirectX9();
		break;
	default:
		break;
	}
}

void RenderPipeline::BeginScene()
{
	render->BeginScene();
}

void RenderPipeline::DrawSceneContent()
{
	ui->RenderUi(render);
}

void RenderPipeline::EndScene()
{
	render->EndScene();
}


RenderPipeline* RenderPipeline::instance = nullptr;