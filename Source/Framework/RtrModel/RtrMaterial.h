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

Filename: RtrMaterial.h
---------------------------------------------------------------------------*/
#pragma once
#include "..\Common.h"

struct aiMaterial;

class CRtrMaterial
{
public:
    CRtrMaterial(const std::string& Name);
	CRtrMaterial(const aiMaterial* pAiMaterial, ID3D11Device* pDevice, const std::string& Folder);

	enum MAP_TYPE
	{
		DIFFUSE_MAP,
		NORMAL_MAP,
		SPECULAR_MAP,
		HEIGHT_MAP,
		ALPHA_MAP,

		MATERIAL_MAP_TYPE_COUNT
	};

	ID3D11ShaderResourceView* GetSRV(MAP_TYPE Type) const { return m_SRV[Type].GetInterfacePtr(); }
    bool IsDoubleSided() const {return m_bDoubleSided;}

    const float3& GetDiffuseColor() const {return m_DiffuseColor;}
    const float3& GetSpecularColor() const {return m_SpecularColor;}
    float GetShininess() const {return m_Shininess;}

    // Getters for UI
    float3* GetDiffuseColorPtr() {return &m_DiffuseColor;}
    float3* GetSpecularColorPtr() { return &m_SpecularColor; }
    float* GetShininessPtr() {return &m_Shininess;}

    void SetDiffuseColor(const float3& Diffuse)  {m_DiffuseColor = Diffuse;}
    void SetSpecularColor(const float3& Specular) {m_SpecularColor = Specular;}
    void SetShininess(float Shininess) {m_Shininess = Shininess;}

private:
	bool m_bHasTextures = false;
	ID3D11ShaderResourceViewPtr m_SRV[MATERIAL_MAP_TYPE_COUNT];
	float3 m_DiffuseColor   = float3(1, 1, 1);
    float3 m_SpecularColor  = float3(0, 0, 0);
    float m_Shininess       = 1;
    bool m_bDoubleSided     = false;
	std::string m_Name;
};