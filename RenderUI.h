#pragma once
#include "Core/Window.h"
#include "Core/D3DManager.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "Renderer.h"

class RenderUI
{
public:
	RenderUI(HWND,D3DManager*,ImGuiIO&,Renderer*);

	void render();

	void setStyle();

	void update(ID3D11RenderTargetView* renderTarget);

	~RenderUI();
private:
	HWND hwnd;
	ImGuiIO& io;
	Renderer* renderer;
};

