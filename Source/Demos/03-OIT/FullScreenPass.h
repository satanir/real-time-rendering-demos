/*
---------------------------------------------------------------------------
Real Time Rendering Demos
---------------------------------------------------------------------------

Copyright (c) 2011 - Nir Benty

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

    Filename: FullScreenPass.h
---------------------------------------------------------------------------*/
#pragma once
#include "DXUT.h"
#include "d3dx11effect.h"

class CFullScreenPass
{
public:
    static CFullScreenPass* Create(ID3D11Device* pDevice);

    void DrawBackToFrontBlend(ID3D11DeviceContext* pContext, ID3D11ShaderResourceView* pSRV);
    ~CFullScreenPass()
    {
        SAFE_RELEASE(m_pFX);
        SAFE_RELEASE(m_pVertexBuffer);
        SAFE_RELEASE(m_pInputLayout);
        SAFE_RELEASE(m_pBackToFrontBlendState);
        SAFE_RELEASE(m_pNoDepthTestState);
    }
private:
    bool CreateEffect(ID3D11Device* pDevice);
    void CreateBackToFrontBlendState(ID3D11Device* pDevice);
    void CreateNoDepthTestState(ID3D11Device* pDevice);

    CFullScreenPass() {};

    ID3D11Buffer* m_pVertexBuffer;
    ID3D11InputLayout* m_pInputLayout;
    ID3DX11Effect* m_pFX;
    ID3DX11EffectTechnique* m_pTexLdTech;
    ID3DX11EffectShaderResourceVariable* m_pSrvVar;
    ID3D11BlendState* m_pBackToFrontBlendState;
    ID3D11DepthStencilState* m_pNoDepthTestState;
};
