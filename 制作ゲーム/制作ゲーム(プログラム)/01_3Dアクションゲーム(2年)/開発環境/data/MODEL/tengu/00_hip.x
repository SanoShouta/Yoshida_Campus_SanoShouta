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
  "data/TEXTURE/tengu.jpg";
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
   26;
   -5.628471;-3.273100;-4.523271;,
   5.628471;-3.273100;-4.523271;,
   -4.634228;3.273100;-4.123642;,
   4.634228;3.273100;-4.123642;,
   -5.241059;3.273100;3.238364;,
   5.241059;3.273100;3.238364;,
   -6.294113;-3.273100;3.552198;,
   6.294113;-3.273100;3.552198;,
   0.000000;-3.273100;-5.530720;,
   0.000000;-3.273100;5.530720;,
   0.000000;3.273100;5.042084;,
   0.000000;3.273100;-5.042084;,
   -6.275653;3.273100;-0.000000;,
   0.000000;3.273100;-0.000000;,
   6.275653;3.273100;-0.000000;,
   7.428970;-3.273100;-0.000000;,
   0.000000;-3.273100;-0.000000;,
   -7.428970;-3.273100;-0.000000;,
   0.000000;-3.273100;5.530720;,
   6.275653;3.273100;-0.000000;,
   -7.428970;-3.273100;-0.000000;,
   0.000000;3.273100;5.042084;,
   -6.275653;3.273100;-0.000000;,
   0.000000;3.273100;-5.042084;,
   7.428970;-3.273100;-0.000000;,
   0.000000;-3.273100;-5.530720;;
   32;
   3;1,8,11;,
   3;3,1,11;,
   3;14,13,10;,
   3;5,14,10;,
   3;5,10,9;,
   3;7,5,9;,
   3;18,16,15;,
   3;7,18,15;,
   3;7,15,19;,
   3;5,7,19;,
   3;12,17,6;,
   3;4,12,6;,
   3;16,9,6;,
   3;20,16,6;,
   3;9,10,4;,
   3;6,9,4;,
   3;21,13,12;,
   3;4,21,12;,
   3;11,8,0;,
   3;2,11,0;,
   3;13,11,2;,
   3;22,13,2;,
   3;23,13,19;,
   3;3,23,19;,
   3;19,15,1;,
   3;3,19,1;,
   3;24,16,8;,
   3;1,24,8;,
   3;25,16,17;,
   3;0,25,17;,
   3;0,17,12;,
   3;2,0,12;;
   MeshNormals
   {
    26;
    -0.581037;-0.399435;-0.709117;,
    0.581037;-0.399435;-0.709117;,
    -0.515567;0.581617;-0.629215;,
    0.515567;0.581617;-0.629215;,
    -0.578558;0.576912;0.576579;,
    0.578558;0.576912;0.576579;,
    -0.651642;-0.391950;0.649413;,
    0.651642;-0.391950;0.649413;,
    0.000000;-0.393180;-0.919462;,
    0.000000;-0.403931;0.914789;,
    0.000000;0.523731;0.851883;,
    0.000000;0.510299;-0.859997;,
    -0.813177;0.581323;-0.028405;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.939624;-0.340630;-0.032822;,
    0.000000;-1.000000;-0.000000;,
    -0.939624;-0.340630;-0.032822;,
    0.000000;-1.000000;-0.000000;,
    0.813177;0.581323;-0.028405;,
    0.000000;-1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;;
    32;
    3;1,8,11;,
    3;3,1,11;,
    3;14,13,10;,
    3;5,14,10;,
    3;5,10,9;,
    3;7,5,9;,
    3;18,16,15;,
    3;7,18,15;,
    3;7,15,19;,
    3;5,7,19;,
    3;12,17,6;,
    3;4,12,6;,
    3;16,9,6;,
    3;20,16,6;,
    3;9,10,4;,
    3;6,9,4;,
    3;21,13,12;,
    3;4,21,12;,
    3;11,8,0;,
    3;2,11,0;,
    3;13,11,2;,
    3;22,13,2;,
    3;23,13,19;,
    3;3,23,19;,
    3;19,15,1;,
    3;3,19,1;,
    3;24,16,8;,
    3;1,24,8;,
    3;25,16,17;,
    3;0,25,17;,
    3;0,17,12;,
    3;2,0,12;;
   }
   MeshTextureCoords
   {
    26;
    0.828933;0.562303;,
    0.944468;0.562303;,
    0.834528;0.488604;,
    0.938873;0.488604;,
    0.827696;0.488604;,
    0.945705;0.488604;,
    0.822100;0.562303;,
    0.951300;0.562303;,
    0.886700;0.562303;,
    0.886700;0.562303;,
    0.886700;0.488604;,
    0.886700;0.488604;,
    0.816048;0.488604;,
    0.886700;0.488604;,
    0.957352;0.488604;,
    0.962947;0.562303;,
    0.886700;0.562303;,
    0.810453;0.562303;,
    0.886700;0.562303;,
    0.957352;0.488604;,
    0.810453;0.562303;,
    0.886700;0.488604;,
    0.816048;0.488604;,
    0.886700;0.488604;,
    0.962947;0.562303;,
    0.886700;0.562303;;
   }
   MeshMaterialList
   {
    1;
    32;
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
    26;
    18;
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
    9,
    14,
    17,
    10,
    12,
    11,
    15,
    8;
   }
  }
 }
}

# Animations definition.

