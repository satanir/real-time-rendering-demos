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

    Filname: SilhouetteShader.hlsl
---------------------------------------------------------------------------
*/
cbuffer cbPeFrame : register(b0)
{
	matrix gVPMat;
	float gLineWidth;
}

cbuffer cbPerMesh : register(b1)
{
	matrix gWorld;
}

Texture2D gAlbedo : register (t0);
SamplerState gLinearSampler : register(s0);

struct VS_IN
{
	float4 PosL : POSITION;
	float3 NormalL : NORMAL;
};

float4 ShellExpansionVS(VS_IN vIn) : SV_POSITION
{
    float3 PosW = mul(vIn.PosL, gWorld).xyz;
    float3 NormalW = mul(float4(vIn.NormalL, 0), gWorld).xyz;
	PosW += normalize(NormalW) * gLineWidth;

	return mul(float4(PosW, 1), gVPMat);
}

float4 PS() : SV_TARGET
{
    return float4(0, 0, 0, 1);
}