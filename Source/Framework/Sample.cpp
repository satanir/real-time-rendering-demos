/*
---------------------------------------------------------------------------
Real Time Rendering Demos
---------------------------------------------------------------------------

Copyright (c) 2014 - Nir Benty

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other
materials provided with the distribution.

* Neither the name of Nir Benty, nor the names of other
contributors may be used to endorse or promote products
derived from this software without specific prior
written permission from Nir Benty.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Filename: Sample.cpp
---------------------------------------------------------------------------*/
#include <sstream>
#include "Sample.h"
#include "Font.h"

void CSample::Run()
{
	// Create the window
	if (m_Window.Create(this) != S_OK)
	{
		PostQuitMessage(0);
		return;
	}

	// Create the device
	m_pDevice = std::make_unique<CDevice>(m_Window);
	assert(m_pDevice);
	OnCreateDevice(m_pDevice->GetD3DDevice());

	// Create UI
	InitUI();	

    // Create font and text helper
    std::unique_ptr<CFont> pFont = std::make_unique<CFont>(m_pDevice->GetD3DDevice());
	m_pTextRenderer = std::make_unique<CTextRenderer>(m_pDevice->GetD3DDevice());
	m_pTextRenderer->SetFont(pFont);

	ResetClock();

	// Enter the message loop
	MessageLoop();

	// Shutdown
	OnDestroyDevice();
	TwTerminate();
}

void CSample::InitUI()
{
	TwInit(TW_DIRECT3D11, m_pDevice->GetD3DDevice());
	TwWindowSize(m_Window.GetClientWidth(), m_Window.GetClientHeight());
	m_pTwBar = TwNewBar("Sample UI");
	assert(m_pTwBar);
	SetUiPos();

	OnInitUI();
}

void CSample::SetWindowParams(const WCHAR* Title, int Width, int Height)
{
	m_Window.SetParams(Title, &CSample::WindowProc, Width, Height);
}

LRESULT CALLBACK CSample::WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CSample* pSample;
	// If this is a create message, store the pointer to the sample object in the user-data window space
	if (Msg == WM_CREATE)
	{
		CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)lParam;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pCreateStruct->lpCreateParams);
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
	else
	{
		pSample = (CSample*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}

	// Let the UI handle events
	if (TwEventWin(hwnd, Msg, wParam, lParam))
	{
		return 0;
	}

	// Handle rest of event
	switch(Msg)
	{
	case WM_SIZE:
		if(wParam != SIZE_MINIMIZED)
		{
			pSample->ResizeWindow();
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		pSample->HandleKeyPress(wParam);
		break;
	default:
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
	return 0;
}

void CSample::MessageLoop()
{
	MSG Msg;
	while (1)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (Msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			RenderFrame();
		}
	}
}

void CSample::RenderFrame()
{
	Tick();
	if(m_pDevice->IsWindowOccluded() == false)
	{
		ID3D11DeviceContext* pCtx = m_pDevice->GetImmediateContext();
		ID3D11RenderTargetView* pRTV = m_pDevice->GetBackBufferRTV();

		// Bind RTV and DSV
		pCtx->OMSetRenderTargets(1, &pRTV, m_pDevice->GetBackBufferDSV());

		OnFrameRender(m_pDevice->GetD3DDevice(), m_pDevice->GetImmediateContext());

		TwDraw();

		m_pDevice->Present(m_bVsync);
	}
}

void CSample::ResizeWindow()
{
	m_pDevice->ResizeWindow();
	SetUiPos();
	ResetClock();
}

void CSample::SetUiPos()
{
	int BarSize[2];
	TwGetParam(m_pTwBar, nullptr, "size", TW_PARAM_INT32, 2, BarSize);
	int BarPosition[2] = { m_Window.GetClientWidth() - 10 - BarSize[0], 10 };
	TwSetParam(m_pTwBar, nullptr, "position", TW_PARAM_INT32, 2, BarPosition);
}

void CSample::ResetClock()
{
	m_StartTime = std::chrono::system_clock::now();
	m_FrameCount = 0;
}

void CSample::Tick()
{
	m_FrameCount++;
}

float CSample::CalcFps()
{
	auto Now = std::chrono::system_clock::now();
	std::chrono::duration<double> ElapsedTime = Now - m_StartTime;
	double fps = double(m_FrameCount) / ElapsedTime.count();
	return float(fps);
}

const std::wstring CSample::GetFPSString()
{
	std::wstringstream ss;
	ss << INT(CalcFps()) << " FPS. ";
	ss << "VSYNC " << (m_bVsync ? "ON" : "OFF" ) << " Press 'V' to toggle.";
	return ss.str();
}

void CSample::HandleKeyPress(WPARAM KeyCode)
{
	if (OnKeyPress(KeyCode))
	{
		return;
	}

	switch(KeyCode)
	{
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	case 'V':
		m_bVsync = !m_bVsync;
		ResetClock();
		break;
	}
}

bool CSample::OnKeyPress(WPARAM KeyCode)
{
	return false;
}

void CSample::OnInitUI()
{

}