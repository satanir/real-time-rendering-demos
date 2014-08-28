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

Filename: ShaderUtils.h
---------------------------------------------------------------------------*/
#pragma once
#include <windows.h>
#include <memory>
#include "Common.h"

template<typename T>
struct CShader
{
	T pShader;
	ID3DBlobPtr pCodeBlob;
	ID3D11ShaderReflectionPtr pReflector;
};

using SVertexShaderPtr = std::unique_ptr<CShader<ID3D11VertexShaderPtr>>;
using SPixelShaderPtr = std::unique_ptr<CShader<ID3D11PixelShaderPtr>>;
using SDomainShaderPtr = std::unique_ptr<CShader<ID3D11DomainShaderPtr>>;
using SHullShaderPtr = std::unique_ptr<CShader<ID3D11HullShaderPtr>>;
using SGeometryShaderPtr = std::unique_ptr<CShader<ID3D11GeometryShaderPtr >> ;

SVertexShaderPtr CreateVsFromFile(ID3D11Device* pDevice, const std::wstring& Filename, const std::string& EntryPoint, const std::string& Target = "vs_5_0");
SPixelShaderPtr  CreatePsFromFile(ID3D11Device* pDevice, const std::wstring& Filename, const std::string& EntryPoint, const std::string& Target = "ps_5_0");
SDomainShaderPtr CreateDsFromFile(ID3D11Device* pDevice, const std::wstring& Filename, const std::string& EntryPoint, const std::string& Target = "ds_5_0");
SHullShaderPtr	  CreateHsFromFile(ID3D11Device* pDevice, const std::wstring& Filename, const std::string& EntryPoint, const std::string& Target = "hs_5_0");
SGeometryShaderPtr CreateGsFromFile(ID3D11Device* pDevice, const std::wstring& Filename, const std::string& EntryPoint, const std::string& Target = "gs_5_0");


// Functions to verify shader variable positions
bool VerifyConstantLocation(ID3D11ShaderReflection* pReflector, const std::string& VarName, UINT CbIndex, UINT Offset);
bool VerifyResourceLocation(ID3D11ShaderReflection* pReflector, const std::string& VarName, UINT SrvIndex, UINT ArraySize);