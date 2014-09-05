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

Filename: RtrModel.h
---------------------------------------------------------------------------*/
#pragma once
#include "Common.h"
#include "RtrModel\RtrMaterial.h"
#include "RtrModel\RtrMesh.h"
#include <vector>
#include <map>

struct aiScene;
struct aiNode;

using string_int_map = std::map < std::string, int > ;

struct SDrawListNode
{
	std::vector<CRtrMesh*> pMeshes;
	float4x4 Transformation;
};


struct SBone
{
	SBone() { ZeroMemory(this, sizeof(this)); }
	std::string Name;
	UINT BoneID;
	UINT ParentID;
	float4x4 Matrix;
	float4x4 InvMatrix;
};

using ModelDrawList = std::vector < SDrawListNode > ;

class CRtrModel
{
public:
	static CRtrModel* CreateFromFile(const std::wstring& Filename, ID3D11Device* pDevice);
	~CRtrModel();
	const CRtrMaterial* GetMaterial(UINT MaterialID) const { return m_Materials[MaterialID]; }

	float GetRadius() const { return m_Radius; }
	const float3& GetCenter() const { return m_Center; }
	UINT GetVertexCount() { return m_VertexCount; }
	UINT GetPrimitiveCount() { return m_PrimitiveCount; }
		
	const ModelDrawList& GetDrawList() const { return m_DrawList; }
private:
	CRtrModel();
	bool Init(const aiScene* pScene, ID3D11Device* pDevice, const std::string& ModelFolder);
	bool CreateMaterials(const aiScene* pScene, ID3D11Device* pDevice, const std::string& ModelFolder);
	bool CreateDrawList(const aiScene* pScene, ID3D11Device* pDevice);

	bool ParseAiSceneNode(const aiNode* pCurrnet, const aiScene* pScene, ID3D11Device* pDevice, std::map<UINT, UINT>& AiToRtrMeshId);
	void LoadBones(const aiScene* pScene, string_int_map& BoneMap);
	UINT InitBone(const aiNode* pCurNode, UINT ParentID, UINT BoneID, string_int_map& BoneMap);

	void CalculateModelProperties();
	float m_Radius;
	float3 m_Center;

	UINT m_VertexCount;
	UINT m_PrimitiveCount;
	UINT m_BonesCount;

	std::vector<const CRtrMaterial*> m_Materials;
	ModelDrawList m_DrawList;
	std::vector<CRtrMesh*> m_Meshes;
	std::unique_ptr<SBone[]> m_Bones;
};