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
   32;
   -4.789490;-5.723245;-3.954628;,
   4.789490;-5.723245;-3.954628;,
   -3.943448;0.000000;-3.605239;,
   3.943448;0.000000;-3.605239;,
   -4.459824;0.000000;2.831252;,
   4.459824;0.000000;2.831252;,
   -5.355909;-5.723245;3.105633;,
   5.355909;-5.723245;3.105633;,
   0.000000;-5.723245;-4.835426;,
   0.000000;-5.723245;4.835426;,
   0.000000;0.000000;4.408218;,
   0.000000;0.000000;-4.408218;,
   -5.340201;0.000000;-0.000000;,
   0.000000;0.000000;-0.000000;,
   5.340201;0.000000;-0.000000;,
   6.321605;-5.723245;-0.000000;,
   0.000000;-5.723245;-0.000000;,
   -6.321605;-5.723245;-0.000000;,
   0.000000;-5.723245;4.835426;,
   5.340201;0.000000;-0.000000;,
   -6.321605;-5.723245;-0.000000;,
   0.000000;0.000000;4.408218;,
   0.000000;0.000000;-0.000000;,
   -5.340201;0.000000;-0.000000;,
   5.340201;0.000000;-0.000000;,
   0.000000;0.000000;-4.408218;,
   6.321605;-5.723245;-0.000000;,
   0.000000;-5.723245;-0.000000;,
   6.321605;-5.723245;-0.000000;,
   -6.321605;-5.723245;-0.000000;,
   0.000000;-5.723245;-4.835426;,
   -5.340201;0.000000;-0.000000;;
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
   3;22,11,2;,
   3;23,22,2;,
   3;25,22,24;,
   3;3,25,24;,
   3;24,26,1;,
   3;3,24,1;,
   3;28,27,8;,
   3;1,28,8;,
   3;30,27,29;,
   3;0,30,29;,
   3;0,29,31;,
   3;2,0,31;;
   MeshNormals
   {
    32;
    -0.585620;-0.401376;-0.704235;,
    0.585620;-0.401376;-0.704235;,
    -0.520491;0.580793;-0.625914;,
    0.520491;0.580793;-0.625914;,
    -0.583939;0.575469;0.572582;,
    0.583939;0.575469;0.572582;,
    -0.656373;-0.393629;0.643607;,
    0.656373;-0.393629;0.643607;,
    0.000000;-0.393557;-0.919300;,
    0.000000;-0.405019;0.914308;,
    0.000000;0.524613;0.851341;,
    0.000000;0.510606;-0.859815;,
    -0.815754;0.577726;-0.027892;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.938819;-0.342911;-0.032100;,
    0.000000;-1.000000;-0.000000;,
    -0.938819;-0.342911;-0.032100;,
    0.000000;-1.000000;-0.000000;,
    0.815754;0.577726;-0.027892;,
    0.000000;-1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.815754;0.577726;-0.027892;,
    0.000000;1.000000;-0.000000;,
    0.938819;-0.342911;-0.032100;,
    0.000000;-1.000000;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    -0.938819;-0.342911;-0.032100;,
    0.000000;-1.000000;-0.000000;,
    -0.815754;0.577726;-0.027892;;
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
    3;22,11,2;,
    3;23,22,2;,
    3;25,22,24;,
    3;3,25,24;,
    3;24,26,1;,
    3;3,24,1;,
    3;28,27,8;,
    3;1,28,8;,
    3;30,27,29;,
    3;0,30,29;,
    3;0,29,31;,
    3;2,0,31;;
   }
   MeshTextureCoords
   {
    32;
    0.751285;0.577168;,
    0.898590;0.577168;,
    0.764295;0.490582;,
    0.885580;0.490582;,
    0.756331;0.490582;,
    0.893527;0.490582;,
    0.742548;0.577168;,
    0.907310;0.577168;,
    0.824938;0.577168;,
    0.824929;0.577168;,
    0.824929;0.490582;,
    0.824938;0.490582;,
    0.742790;0.490582;,
    0.824929;0.490582;,
    0.907068;0.490582;,
    0.922163;0.577168;,
    0.824929;0.577168;,
    0.727694;0.577168;,
    0.824929;0.577168;,
    0.907068;0.490582;,
    0.727694;0.577168;,
    0.824929;0.490582;,
    0.824938;0.490582;,
    0.742816;0.490582;,
    0.907059;0.490582;,
    0.824938;0.490582;,
    0.922151;0.577168;,
    0.824938;0.577168;,
    0.922151;0.577168;,
    0.727724;0.577168;,
    0.824938;0.577168;,
    0.742816;0.490582;;
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
    32;
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
    13,
    12,
    14,
    11,
    15,
    16,
    15,
    17,
    8,
    12;
   }
  }
 }
}

# Animations definition.

