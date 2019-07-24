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
 0.870130;0.870130;0.870130;1.000000;;
 52.272728;
 0.032468;0.032468;0.032468;;
 0.000000;0.000000;0.000000;;
 TextureFilename
 {
  "data/TEXTURE/ishi_tex.jpg";
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
 Frame Null_1
 {
  FrameTransformMatrix
  {
   4.962314,0.000000,0.000000,0.000000,
   0.000000,4.962314,0.000000,0.000000,
   0.000000,0.000000,4.962314,0.000000,
   0.000000,0.819297,0.000000,1.000000;;
  }
  Frame Mesh_11
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
    21;
    -61.888229;0.000000;-25.502272;,
    -50.377811;0.000000;-41.413521;,
    -33.935955;0.000000;-53.270954;,
    -14.172337;0.000000;-59.913864;,
    6.978635;0.000000;-60.691898;,
    27.446503;0.000000;-55.529125;,
    45.227627;0.000000;-44.930668;,
    58.581615;0.000000;-29.934101;,
    66.201218;0.000000;-12.007391;,
    67.340546;0.000000;7.094668;,
    61.888184;0.000000;25.502268;,
    50.377743;0.000000;41.413513;,
    33.935936;0.000000;53.270950;,
    14.172299;0.000000;59.913799;,
    -6.978625;0.000000;60.691898;,
    -27.446447;0.000000;55.529060;,
    -45.227612;0.000000;44.930672;,
    -58.581596;0.000000;29.934118;,
    -66.201172;0.000000;12.007431;,
    -67.340553;0.000000;-7.094638;,
    0.000002;0.000000;0.000015;;
    20;
    3;20,1,0;,
    3;20,2,1;,
    3;20,3,2;,
    3;20,4,3;,
    3;20,5,4;,
    3;20,6,5;,
    3;20,7,6;,
    3;20,8,7;,
    3;20,9,8;,
    3;20,10,9;,
    3;20,11,10;,
    3;20,12,11;,
    3;20,13,12;,
    3;20,14,13;,
    3;20,15,14;,
    3;20,16,15;,
    3;20,17,16;,
    3;20,18,17;,
    3;20,19,18;,
    3;20,0,19;;
    MeshNormals
    {
     21;
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;;
     20;
     3;20,1,0;,
     3;20,2,1;,
     3;20,3,2;,
     3;20,4,3;,
     3;20,5,4;,
     3;20,6,5;,
     3;20,7,6;,
     3;20,8,7;,
     3;20,9,8;,
     3;20,10,9;,
     3;20,11,10;,
     3;20,12,11;,
     3;20,13,12;,
     3;20,14,13;,
     3;20,15,14;,
     3;20,16,15;,
     3;20,17,16;,
     3;20,18,17;,
     3;20,19,18;,
     3;20,0,19;;
    }
    MeshTextureCoords
    {
     21;
     0.345492;0.975528;,
     0.500000;1.000000;,
     0.654509;0.975528;,
     0.793893;0.904508;,
     0.904509;0.793892;,
     0.975529;0.654508;,
     1.000000;0.500000;,
     0.975528;0.345491;,
     0.904508;0.206107;,
     0.793892;0.095492;,
     0.654508;0.024472;,
     0.500000;0.000000;,
     0.345491;0.024472;,
     0.206107;0.095492;,
     0.095492;0.206108;,
     0.024472;0.345492;,
     0.000000;0.500000;,
     0.024472;0.654508;,
     0.095492;0.793892;,
     0.206108;0.904508;,
     0.500000;0.500000;;
    }
    MeshMaterialList
    {
     1;
     20;
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
     21;
     21;
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
     20;
    }
   }
  }
 }
}

# Animations definition.

