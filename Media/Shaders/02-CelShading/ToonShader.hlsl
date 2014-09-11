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

    Filname: BasicDiffuse.hlsl
---------------------------------------------------------------------------
*/
cbuffer cbPeFrame : register(b0)
{
	matrix gVPMat;
	float3 gLightPosW;
	float3 gLightIntensity;
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
	float2 TexC : TEXCOORD;
};

struct VS_OUT
{
	float4 svPos : SV_POSITION;
    float3 PosW : POSITION;
	float2 TexC : TEXCOORD;
	float3 NormalW : NORMAL;
};

VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
    float4 PosW = mul(vIn.PosL, gWorld);
    vOut.PosW = PosW.xyz;
	vOut.svPos = mul(PosW, gVPMat);
	vOut.TexC = vIn.TexC;
	vOut.NormalW = mul(float4(vIn.NormalL, 0), gWorld).xyz;
	return vOut;
}

float CalculateSpecIntensity(float3 PosW, float3 NormalW)
{
    float3 LightDirW = normalize(gLightPosW - PosW);
    float3 H = normalize(LightDirW + NormalW);
    float NdotH = max(0, dot(NormalW, H));
    float Intensity = pow(NdotH, 1000);
    return Intensity;
}

float4 BasicDiffusePS(VS_OUT vOut) : SV_TARGET
{
	float3 n = normalize(vOut.NormalW);
    // Light dir
    float3 LightDir = gLightPosW - vOut.PosW;
    LightDir = normalize(LightDir);

    //Diffuse term
    float NdotL = max(0, dot(n, LightDir));
    float3 IntensityD = NdotL * gLightIntensity;

    float3 c = gAlbedo.Sample(gLinearSampler, vOut.TexC).xyz;
    c = c * IntensityD + CalculateSpecIntensity(vOut.PosW, n);
	return float4(c, 1);
}

float4 GoochShadingPS(VS_OUT vOut) : SV_TARGET
{
    const float3 Blue = float3(0, 0.0, 0.4);
    const float3 Yellow = float3(0.2, 0.15, 0);
    const float alpha = 0.1;
    const float beta = 0.7;
    float3 LightDir = normalize(gLightPosW - vOut.PosW);

    float3 diffuse = gAlbedo.Sample(gLinearSampler, vOut.TexC).xyz;

    float3 Cool = alpha * diffuse + Blue;
    float3 Warm = beta * diffuse + Yellow;

    float3 N = normalize(vOut.NormalW);
    float NdotL = dot(N, LightDir);
    float factor = (1 + NdotL) * 0.5;
    float3 c = factor*Warm + (1 - factor)*Cool;
    c = c + CalculateSpecIntensity(vOut.PosW, N).xxx;
    return float4(c, 1);
}