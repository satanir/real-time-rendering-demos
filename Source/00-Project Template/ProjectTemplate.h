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

Filename: ProjectTemplate.h
---------------------------------------------------------------------------*/
#pragma once
#include "Sample.h"
#include "Camera.h"

class CRtrModel;
class CShaderTemplate;

class CProjectTemplate : public CSample
{
public:
	CProjectTemplate() = default;
    CProjectTemplate(CProjectTemplate&) = delete;
    CProjectTemplate& operator=(CProjectTemplate) = delete;

	HRESULT OnCreateDevice(ID3D11Device* pDevice);
	void OnFrameRender(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	void OnDestroyDevice();
	void OnResizeWindow();
	bool OnKeyPress(WPARAM KeyCode);
	bool OnMouseEvent(const SMouseData& Data);

private:
	void RenderText(ID3D11DeviceContext* pContext);
    void InitUI();

    std::unique_ptr<CRtrModel> m_pModel;
    std::unique_ptr<CShaderTemplate> m_pShader;
    CModelViewCamera m_Camera;

    float3 m_LightDir = float3(0.5f, 0, 1);
    float3 m_LightIntensity = float3(0.66f, 0.66f, 0.66f);
};