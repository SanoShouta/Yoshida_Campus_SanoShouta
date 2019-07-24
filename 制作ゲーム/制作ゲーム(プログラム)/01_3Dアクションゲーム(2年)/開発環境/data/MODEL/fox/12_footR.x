xof 0303txt 0032

# X File Templates declaration.

template AnimTicksPerSecond
{
 <9e415a43-7ba6-4a73-8743-b73d47e88476>
 DWORD AnimTicksPerSecond;
}
template Frame
{
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}
template Matrix4x4
{
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}
template FrameTransformMatrix
{
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}
template Vector
{
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}
template Coords2d
{
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}
template ColorRGB
{
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}
template ColorRGBA
{
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}
template IndexedColor
{
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}
template MeshFace
{
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}
template MeshNormals
{
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}
template MeshVertexColors
{
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}
template MeshTextureCoords
{
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}
template Mesh
{
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}
template TextureFilename
{
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}
template Material
{
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}
template MeshMaterialList
{
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}
template VertexDuplicationIndices
{
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader
{
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights
{
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}
template Animation
{
 <3d82ab4f-62da-11cf-ab39-0020af71e433>
 [...]
}
template AnimationSet
{
 <3d82ab50-62da-11cf-ab39-0020af71e433>
 [Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]
}
template FloatKeys
{
 <10dd46a9-775b-11cf-8f52-0040333594a3>
 DWORD nValues;
 array FLOAT values[nValues];
}
template TimedFloatKeys
{
 <f406b180-7b3b-11cf-8f52-0040333594a3>
 DWORD time;
 FloatKeys tfkeys;
}
template AnimationKey
{
 <10dd46a8-775b-11cf-8f52-0040333594a3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

# Global definition.


# Materials definition.

Material Material_1
{
 0.800000;0.800000;0.800000;1.000000;;
 5.000000;
 0.300000;0.300000;0.300000;;
 0.000000;0.000000;0.000000;;
 TextureFilename
 {
  "data/TEXTURE/kitune.jpg";
 }
}

# Models definition.

Frame Model
{
 FrameTransformMatrix
 {
  1.000000,0.000000,0.000000,0.000000,
  0.000000,1.000000,0.000000,0.000000,
  0.000000,0.000000,1.000000,0.000000,
  0.000000,0.000000,0.000000,1.000000;;
 }
 Frame Mesh_1
 {
  FrameTransformMatrix
  {
   1.000000,0.000000,0.000000,0.000000,
   0.000000,1.000000,0.000000,0.000000,
   0.000000,0.000000,1.000000,0.000000,
   0.000000,0.000000,0.000000,1.000000;;
  }
  Mesh
  {
   86;
   1.684611;-1.917760;-5.215958;,
   -1.684613;-1.917760;-5.215958;,
   1.684611;-0.557240;-5.215958;,
   -1.684613;-0.557240;-5.215958;,
   2.020917;-0.557240;1.216197;,
   -2.020920;-0.557240;1.216197;,
   2.020917;-1.917760;1.216197;,
   -2.020920;-1.917760;1.216197;,
   2.292554;-0.557240;-2.609709;,
   -2.292555;-0.557240;-2.609709;,
   -2.292555;-1.917760;-2.609709;,
   2.292554;-1.917760;-2.609709;,
   2.292554;-1.917760;-0.000000;,
   -2.292555;-1.917760;-0.000000;,
   -2.292555;-0.557240;-0.000000;,
   2.292554;-0.557240;-0.000000;,
   0.000000;-1.917760;-5.850898;,
   0.000000;-1.917760;-2.609709;,
   0.000000;-1.917760;-0.000000;,
   0.000000;-1.917760;1.477885;,
   0.000000;-0.557240;1.477885;,
   0.000000;-0.557240;-5.850898;,
   -1.684613;-1.237500;-5.215958;,
   -2.292555;-1.237500;-2.609709;,
   -2.292555;-1.237500;-0.000000;,
   -2.020920;-1.237500;1.216197;,
   0.000000;-1.237500;1.477885;,
   2.020917;-1.237500;1.216197;,
   2.292554;-1.237500;-0.000000;,
   2.292554;-1.237500;-2.609709;,
   1.684611;-1.237500;-5.215958;,
   0.000000;-1.237500;-5.850898;,
   -1.492554;0.000000;-0.069185;,
   0.000000;0.000000;-0.000000;,
   0.000000;0.000000;-2.609709;,
   -1.492554;0.000000;-2.517640;,
   0.000000;0.000000;-4.995962;,
   -1.002600;0.000000;-4.618076;,
   0.000000;0.000000;1.013769;,
   -1.333935;0.000000;0.841038;,
   1.492554;0.000000;-0.069185;,
   1.333934;0.000000;0.841038;,
   1.492554;0.000000;-2.517640;,
   1.002599;0.000000;-4.618077;,
   -1.684613;-1.237500;-5.215958;,
   -1.684613;-0.557240;-5.215958;,
   -2.020920;-0.557240;1.216197;,
   -2.020920;-1.237500;1.216197;,
   0.000000;-1.917760;-5.850898;,
   0.000000;-1.917760;1.477885;,
   2.020917;-0.557240;1.216197;,
   2.020917;-1.237500;1.216197;,
   1.684611;-1.237500;-5.215958;,
   1.684611;-0.557240;-5.215958;,
   2.292554;-1.917760;-0.000000;,
   2.292554;-1.917760;-2.609709;,
   -2.292555;-1.917760;-2.609709;,
   -2.292555;-1.917760;-0.000000;,
   -2.292555;-1.917760;-2.609709;,
   -1.684613;-1.917760;-5.215958;,
   -2.292555;-1.917760;-0.000000;,
   -2.020920;-1.917760;1.216197;,
   -2.020920;-1.237500;1.216197;,
   0.000000;-1.917760;1.477885;,
   -2.020920;-1.917760;1.216197;,
   -2.020920;-1.237500;1.216197;,
   0.000000;-1.237500;1.477885;,
   2.020917;-1.237500;1.216197;,
   2.020917;-1.917760;1.216197;,
   2.292554;-1.917760;-0.000000;,
   2.020917;-1.917760;1.216197;,
   2.292554;-1.917760;-2.609709;,
   1.684611;-1.917760;-5.215958;,
   1.684611;-1.237500;-5.215958;,
   0.000000;-1.917760;-5.850898;,
   1.684611;-1.917760;-5.215958;,
   1.684611;-1.237500;-5.215958;,
   -1.684613;-1.237500;-5.215958;,
   -1.684613;-1.917760;-5.215958;,
   -2.292555;-0.557240;-2.609709;,
   -2.292555;-0.557240;-0.000000;,
   -2.020920;-0.557240;1.216197;,
   0.000000;-0.557240;1.477885;,
   2.020917;-0.557240;1.216197;,
   2.292554;-0.557240;-0.000000;,
   2.292554;-0.557240;-2.609709;;
   84;
   3;31,22,3;,
   3;21,31,3;,
   3;34,35,32;,
   3;33,34,32;,
   3;20,5,25;,
   3;26,20,25;,
   3;14,9,23;,
   3;24,14,23;,
   3;8,15,28;,
   3;29,8,28;,
   3;37,35,34;,
   3;36,37,34;,
   3;44,23,9;,
   3;45,44,9;,
   3;10,1,16;,
   3;17,10,16;,
   3;2,8,29;,
   3;30,2,29;,
   3;7,13,18;,
   3;19,7,18;,
   3;46,14,24;,
   3;47,46,24;,
   3;32,39,38;,
   3;33,32,38;,
   3;27,28,15;,
   3;4,27,15;,
   3;48,0,11;,
   3;17,48,11;,
   3;18,12,6;,
   3;49,18,6;,
   3;26,51,50;,
   3;20,26,50;,
   3;38,41,40;,
   3;33,38,40;,
   3;40,42,34;,
   3;33,40,34;,
   3;34,42,43;,
   3;36,34,43;,
   3;21,53,52;,
   3;31,21,52;,
   3;17,55,54;,
   3;18,17,54;,
   3;56,17,18;,
   3;57,56,18;,
   3;59,58,23;,
   3;44,59,23;,
   3;23,58,60;,
   3;24,23,60;,
   3;24,60,61;,
   3;62,24,61;,
   3;65,64,63;,
   3;66,65,63;,
   3;63,68,67;,
   3;66,63,67;,
   3;70,69,28;,
   3;27,70,28;,
   3;28,69,71;,
   3;29,28,71;,
   3;29,71,72;,
   3;73,29,72;,
   3;76,75,74;,
   3;31,76,74;,
   3;74,78,77;,
   3;31,74,77;,
   3;32,35,79;,
   3;80,32,79;,
   3;37,36,21;,
   3;3,37,21;,
   3;35,37,3;,
   3;79,35,3;,
   3;39,32,80;,
   3;81,39,80;,
   3;38,39,81;,
   3;82,38,81;,
   3;41,38,82;,
   3;83,41,82;,
   3;40,41,83;,
   3;84,40,83;,
   3;42,40,84;,
   3;85,42,84;,
   3;36,43,2;,
   3;21,36,2;,
   3;43,42,85;,
   3;2,43,85;;
   MeshNormals
   {
    86;
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.679962;0.644262;-0.350113;,
    -0.436106;0.644262;-0.628282;,
    0.975954;0.000000;0.217979;,
    -0.128417;0.000000;0.991720;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.879383;0.465234;-0.101205;,
    -0.879383;0.465234;-0.101205;,
    -0.887388;-0.449570;-0.102127;,
    0.000000;-1.000000;-0.000000;,
    0.887954;-0.449380;0.097955;,
    0.000000;-1.000000;-0.000000;,
    -0.882074;0.461666;0.093855;,
    0.882637;0.460593;0.093844;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-0.450193;0.892931;,
    0.000000;0.340877;0.940108;,
    0.000000;0.487263;-0.873255;,
    -0.352686;0.000000;-0.935742;,
    -0.993443;0.000000;-0.114332;,
    -0.993970;0.000000;0.109650;,
    -0.128417;0.000000;0.991720;,
    0.000000;0.000000;1.000000;,
    0.975954;0.000000;0.217979;,
    0.993970;0.000000;0.109651;,
    0.993443;0.000000;-0.114332;,
    0.973856;0.000000;-0.227165;,
    0.000000;0.000000;-1.000000;,
    -0.300158;0.953420;0.029909;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    -0.295791;0.954646;-0.034042;,
    0.000000;0.959455;-0.281863;,
    -0.268196;0.934234;-0.235112;,
    0.000000;0.906022;0.423231;,
    -0.249765;0.911432;0.326968;,
    0.301302;0.953058;0.029963;,
    0.251362;0.910906;0.327213;,
    0.295791;0.954646;-0.034042;,
    0.268196;0.934234;-0.235112;,
    -0.973856;0.000000;-0.227165;,
    -0.973856;0.000000;-0.227165;,
    -0.671576;0.590832;0.447105;,
    -0.975954;0.000000;0.217977;,
    0.000000;-0.471276;-0.881986;,
    0.000000;-1.000000;-0.000000;,
    0.321747;0.579161;0.749034;,
    0.128417;0.000000;0.991720;,
    0.352687;0.000000;-0.935742;,
    0.352687;0.000000;-0.935742;,
    0.000000;-1.000000;-0.000000;,
    0.887388;-0.449570;-0.102127;,
    0.000000;-1.000000;-0.000000;,
    -0.887954;-0.449380;0.097955;,
    -0.887388;-0.449570;-0.102127;,
    -0.973856;0.000000;-0.227165;,
    -0.887954;-0.449380;0.097955;,
    -0.975954;0.000000;0.217977;,
    -0.975954;0.000000;0.217977;,
    0.000000;-0.450193;0.892931;,
    -0.128417;0.000000;0.991720;,
    -0.128417;0.000000;0.991720;,
    0.000000;0.000000;1.000000;,
    0.128417;0.000000;0.991720;,
    0.128417;0.000000;0.991720;,
    0.887954;-0.449380;0.097955;,
    0.975954;0.000000;0.217979;,
    0.887388;-0.449570;-0.102127;,
    0.973856;0.000000;-0.227165;,
    0.973856;0.000000;-0.227165;,
    0.000000;-0.471276;-0.881986;,
    0.352687;0.000000;-0.935742;,
    0.352687;0.000000;-0.935742;,
    -0.352686;0.000000;-0.935742;,
    -0.352686;0.000000;-0.935742;,
    -0.879383;0.465234;-0.101205;,
    -0.882074;0.461666;0.093855;,
    -0.671576;0.590832;0.447105;,
    0.000000;0.340877;0.940108;,
    0.321747;0.579161;0.749034;,
    0.882637;0.460593;0.093844;,
    0.879383;0.465234;-0.101205;;
    84;
    3;31,22,3;,
    3;21,31,3;,
    3;34,35,32;,
    3;33,34,32;,
    3;20,5,25;,
    3;26,20,25;,
    3;14,9,23;,
    3;24,14,23;,
    3;8,15,28;,
    3;29,8,28;,
    3;37,35,34;,
    3;36,37,34;,
    3;44,23,9;,
    3;45,44,9;,
    3;10,1,16;,
    3;17,10,16;,
    3;2,8,29;,
    3;30,2,29;,
    3;7,13,18;,
    3;19,7,18;,
    3;46,14,24;,
    3;47,46,24;,
    3;32,39,38;,
    3;33,32,38;,
    3;27,28,15;,
    3;4,27,15;,
    3;48,0,11;,
    3;17,48,11;,
    3;18,12,6;,
    3;49,18,6;,
    3;26,51,50;,
    3;20,26,50;,
    3;38,41,40;,
    3;33,38,40;,
    3;40,42,34;,
    3;33,40,34;,
    3;34,42,43;,
    3;36,34,43;,
    3;21,53,52;,
    3;31,21,52;,
    3;17,55,54;,
    3;18,17,54;,
    3;56,17,18;,
    3;57,56,18;,
    3;59,58,23;,
    3;44,59,23;,
    3;23,58,60;,
    3;24,23,60;,
    3;24,60,61;,
    3;62,24,61;,
    3;65,64,63;,
    3;66,65,63;,
    3;63,68,67;,
    3;66,63,67;,
    3;70,69,28;,
    3;27,70,28;,
    3;28,69,71;,
    3;29,28,71;,
    3;29,71,72;,
    3;73,29,72;,
    3;76,75,74;,
    3;31,76,74;,
    3;74,78,77;,
    3;31,74,77;,
    3;32,35,79;,
    3;80,32,79;,
    3;37,36,21;,
    3;3,37,21;,
    3;35,37,3;,
    3;79,35,3;,
    3;39,32,80;,
    3;81,39,80;,
    3;38,39,81;,
    3;82,38,81;,
    3;41,38,82;,
    3;83,41,82;,
    3;40,41,83;,
    3;84,40,83;,
    3;42,40,84;,
    3;85,42,84;,
    3;36,43,2;,
    3;21,36,2;,
    3;43,42,85;,
    3;2,43,85;;
   }
   MeshTextureCoords
   {
    86;
    0.052307;0.904758;,
    0.124248;0.904758;,
    0.023597;0.924673;,
    0.153449;0.924673;,
    0.031079;0.947657;,
    0.179134;0.835984;,
    0.045126;0.760102;,
    0.131429;0.760102;,
    0.023246;0.947657;,
    0.155455;0.947657;,
    0.137229;0.849109;,
    0.039326;0.849109;,
    0.039326;0.793385;,
    0.137229;0.793385;,
    0.155455;0.947657;,
    0.023246;0.947657;,
    0.090502;0.920960;,
    0.088278;0.849109;,
    0.088278;0.793385;,
    0.088278;0.754514;,
    0.176801;0.835984;,
    0.089867;0.932774;,
    0.137925;0.964203;,
    0.155455;0.964203;,
    0.155455;0.964203;,
    0.179134;0.847062;,
    0.164176;0.847062;,
    0.031079;0.964203;,
    0.023246;0.964203;,
    0.023246;0.964203;,
    0.040776;0.964203;,
    0.091466;0.964203;,
    0.137229;0.793385;,
    0.088278;0.793385;,
    0.088278;0.849109;,
    0.137229;0.849109;,
    0.090502;0.920960;,
    0.124248;0.904758;,
    0.088278;0.754514;,
    0.131429;0.760102;,
    0.039326;0.793385;,
    0.045126;0.760102;,
    0.039326;0.849109;,
    0.052307;0.904758;,
    0.137925;0.964203;,
    0.153449;0.924673;,
    0.147622;0.947657;,
    0.147622;0.964203;,
    0.090502;0.920960;,
    0.088278;0.754514;,
    0.149217;0.835984;,
    0.149217;0.847062;,
    0.040776;0.964203;,
    0.023597;0.924673;,
    0.039326;0.793385;,
    0.039326;0.849109;,
    0.137229;0.849109;,
    0.137229;0.793385;,
    0.155455;0.983818;,
    0.137925;0.983818;,
    0.155455;0.983818;,
    0.147622;0.983818;,
    0.147622;0.964203;,
    0.091254;0.983818;,
    0.147622;0.983818;,
    0.147622;0.964203;,
    0.091466;0.964203;,
    0.031079;0.964203;,
    0.031079;0.983818;,
    0.023246;0.983818;,
    0.031079;0.983818;,
    0.023246;0.983818;,
    0.040776;0.983818;,
    0.040776;0.964203;,
    0.091254;0.983818;,
    0.040776;0.983818;,
    0.040776;0.964203;,
    0.137925;0.964203;,
    0.137925;0.983818;,
    0.137229;0.849109;,
    0.137229;0.793385;,
    0.131429;0.760102;,
    0.088278;0.754514;,
    0.045126;0.760102;,
    0.039326;0.793385;,
    0.039326;0.849109;;
   }
   MeshMaterialList
   {
    1;
    84;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;
    {Material_1}
   }
   VertexDuplicationIndices
   {
    86;
    44;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    22,
    3,
    5,
    25,
    16,
    19,
    4,
    27,
    30,
    2,
    12,
    11,
    10,
    13,
    10,
    1,
    13,
    7,
    25,
    19,
    7,
    25,
    26,
    27,
    6,
    12,
    6,
    11,
    0,
    30,
    16,
    0,
    30,
    22,
    1,
    9,
    14,
    5,
    20,
    4,
    15,
    8;
   }
  }
 }
}

# Animations definition.

