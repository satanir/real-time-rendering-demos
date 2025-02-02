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

Filename: DxState.cpp
---------------------------------------------------------------------------*/
#include "Common.h"
#include "DxState.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "StringUtils.h"

HRESULT CreateTgaResourceViewFromFile(ID3D11Device* pDevice,
    const wchar_t* Filename,
    bool bSrgb,
    bool bGenMipMaps,
    ID3D11Resource** ppTexture,
    ID3D11ShaderResourceView** ppSrv
    );

ID3D11ShaderResourceView* CreateShaderResourceViewFromFile(ID3D11Device* pDevice, const std::wstring& Filename, bool bSrgb)
{
	// null-call to get the size
	std::wstring fullpath;
	verify(FindFileInCommonDirs(Filename, fullpath));

	ID3D11DeviceContextPtr pCtx;
	pDevice->GetImmediateContext(&pCtx);

	ID3D11ShaderResourceView* pSrv = nullptr;
	const std::wstring dds(L".dds");
    const std::wstring tga(L".tga");

	bool bDDS = HasSuffix(fullpath, dds, false);
    bool bTGA = HasSuffix(fullpath, tga, false);

	if(bDDS)
	{
		verify(DirectX::CreateDDSTextureFromFileEx(pDevice, pCtx, fullpath.c_str(), 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, bSrgb, nullptr, &pSrv));
	}
	else if(bTGA)
    {
        verify(CreateTgaResourceViewFromFile(pDevice, fullpath.c_str(), bSrgb, true, nullptr, &pSrv));
    }
    else
	{
		verify(DirectX::CreateWICTextureFromFileEx(pDevice, pCtx, fullpath.c_str(), 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, bSrgb, nullptr, &pSrv));
	}
	return pSrv;
}

ID3D11RasterizerState* SRasterizerState::SolidNoCull(ID3D11Device* pDevice)
{
	ID3D11RasterizerState* pRast;
	D3D11_RASTERIZER_DESC desc;
	desc.AntialiasedLineEnable = FALSE;
	desc.CullMode = D3D11_CULL_NONE;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0;
	desc.DepthClipEnable = FALSE;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = FALSE;
	desc.MultisampleEnable = FALSE;
	desc.ScissorEnable = FALSE;
	desc.SlopeScaledDepthBias = 0;
	verify(pDevice->CreateRasterizerState(&desc, &pRast));
	return pRast;
}

ID3D11RasterizerState* SRasterizerState::Wireframe(ID3D11Device* pDevice)
{
    ID3D11RasterizerState* pRast;
    D3D11_RASTERIZER_DESC desc;
    desc.AntialiasedLineEnable = FALSE;
    desc.CullMode = D3D11_CULL_NONE;
    desc.DepthBias = 0;
    desc.DepthBiasClamp = 0;
    desc.DepthClipEnable = FALSE;
    desc.FillMode = D3D11_FILL_WIREFRAME;
    desc.FrontCounterClockwise = FALSE;
    desc.MultisampleEnable = FALSE;
    desc.ScissorEnable = FALSE;
    desc.SlopeScaledDepthBias = 0;
    verify(pDevice->CreateRasterizerState(&desc, &pRast));
    return pRast;
}

ID3D11DepthStencilState* SDepthState::NoTests(ID3D11Device* pDevice)
{
	ID3D11DepthStencilState* pDs;
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.StencilEnable = FALSE;
	desc.DepthEnable = FALSE;
	verify(pDevice->CreateDepthStencilState(&desc, &pDs));
	return pDs;
}

ID3D11BlendState* SBlendState::SrcAlpha(ID3D11Device* pDevice)
{
	ID3D11BlendState* pBlend;
	D3D11_BLEND_DESC Desc;
	Desc.AlphaToCoverageEnable = FALSE;
	Desc.IndependentBlendEnable = FALSE;
	Desc.RenderTarget[0].BlendEnable = TRUE;
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

	verify(pDevice->CreateBlendState(&Desc, &pBlend));
	return pBlend;
}

ID3D11SamplerState* SSamplerState::TriLinear(ID3D11Device* pDevice)
{
	D3D11_SAMPLER_DESC SamplerDesc;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.MaxAnisotropy = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MipLODBias = 0;
	ID3D11SamplerState* pLinearSampler;
	verify(pDevice->CreateSamplerState(&SamplerDesc, &pLinearSampler));
	return pLinearSampler;

}

ID3D11SamplerState* SSamplerState::Point(ID3D11Device* pDevice)
{
	D3D11_SAMPLER_DESC SamplerDesc;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	SamplerDesc.MaxAnisotropy = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MipLODBias = 0;
	ID3D11SamplerState* pLinearSampler;
	verify(pDevice->CreateSamplerState(&SamplerDesc, &pLinearSampler));
	return pLinearSampler;

}
