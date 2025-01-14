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

Filename: BRDF.h
---------------------------------------------------------------------------*/
#pragma once
#include "Sample.h"
#include "Camera.h"
#include "BrdfShader.h"

class CRtrModel;

class CBrdf : public CSample
{
public:
	CBrdf() = default;
    CBrdf(CBrdf&) = delete;
    CBrdf& operator=(CBrdf) = delete;

	HRESULT OnCreateDevice(ID3D11Device* pDevice);
	void OnFrameRender(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	void OnDestroyDevice();
	void OnResizeWindow();
	bool OnKeyPress(WPARAM KeyCode);
	bool OnMouseEvent(const SMouseData& Data);
    void LoadModel(UINT ModelIndex);
    UINT GetActiveModel() { return m_ActiveModel; }

private:
	void RenderText(ID3D11DeviceContext* pContext);
    void InitUI();

    std::unique_ptr<CRtrModel> m_pModel;
    std::unique_ptr<CBrdfShader> m_pShader;
    CModelViewCamera m_Camera;
    UINT m_ActiveModel = UINT(-1);

    CBrdfShader::SPerFrameData m_ShaderData;
    CBrdfShader::BRDF_MODEL m_BrdfModel = CBrdfShader::BRDF_MODEL::NO_BRDF;
    float3 m_DiffuseColor = m_ShaderData.DiffuseColor;
    float3 m_SpecularColor = m_ShaderData.SpecularColor;
    float3 m_AmbientIntensity = m_ShaderData.AmbientIntensity;
    float m_LightCutoffStart = 50;
    float m_LightCutoffEnd = 0;

    bool m_bAmbientEnabled = true;
    bool m_bSpecularEnabled = true;
    bool m_bDiffuseEnabled = true;

    bool m_bRightButtonDown = false;
    bool m_bMiddleButtonDown = false;
    float2 m_LastMousePos;
};