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
  "data/TEXTURE/tree_tex.jpg";
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
   0.000000,147.777710,0.000000,1.000000;;
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
    124;
    1.796411;-31.358387;0.583689;,
    1.528118;-31.358387;1.110243;,
    1.110243;-31.358387;1.528118;,
    0.583689;-31.358387;1.796411;,
    0.000000;-31.358387;1.888858;,
    -0.583689;-31.358387;1.796410;,
    -1.110243;-31.358387;1.528118;,
    -1.528118;-31.358387;1.110242;,
    -1.796410;-31.358387;0.583689;,
    -1.888857;-31.358387;-0.000000;,
    -1.796410;-31.358387;-0.583689;,
    -1.528118;-31.358387;-1.110242;,
    -1.110242;-31.358387;-1.528118;,
    -0.583689;-31.358387;-1.796410;,
    -0.000000;-31.358387;-1.888857;,
    0.583689;-31.358387;-1.796410;,
    1.110242;-31.358387;-1.528117;,
    1.528117;-31.358387;-1.110242;,
    1.796410;-31.358387;-0.583689;,
    1.888857;-31.358387;-0.000000;,
    1.796411;31.358387;0.583689;,
    1.528118;31.358387;1.110243;,
    1.110243;31.358387;1.528118;,
    0.583689;31.358387;1.796411;,
    0.000000;31.358387;1.888858;,
    -0.583689;31.358387;1.796410;,
    -1.110243;31.358387;1.528118;,
    -1.528118;31.358387;1.110242;,
    -1.796410;31.358387;0.583689;,
    -1.888857;31.358387;-0.000000;,
    -1.796410;31.358387;-0.583689;,
    -1.528118;31.358387;-1.110242;,
    -1.110242;31.358387;-1.528118;,
    -0.583689;31.358387;-1.796410;,
    -0.000000;31.358387;-1.888857;,
    0.583689;31.358387;-1.796410;,
    1.110242;31.358387;-1.528117;,
    1.528117;31.358387;-1.110242;,
    1.796410;31.358387;-0.583689;,
    1.888857;31.358387;-0.000000;,
    0.000000;-31.358387;-0.000000;,
    0.000000;31.358387;-0.000000;,
    1.796411;-31.358387;0.583689;,
    1.796411;31.358387;0.583689;,
    1.528118;-31.358387;1.110243;,
    1.796411;-31.358387;0.583689;,
    1.110243;-31.358387;1.528118;,
    1.528118;-31.358387;1.110243;,
    0.583689;-31.358387;1.796411;,
    1.110243;-31.358387;1.528118;,
    0.000000;-31.358387;1.888858;,
    0.583689;-31.358387;1.796411;,
    -0.583689;-31.358387;1.796410;,
    0.000000;-31.358387;1.888858;,
    -1.110243;-31.358387;1.528118;,
    -0.583689;-31.358387;1.796410;,
    -1.528118;-31.358387;1.110242;,
    -1.110243;-31.358387;1.528118;,
    -1.796410;-31.358387;0.583689;,
    -1.528118;-31.358387;1.110242;,
    -1.888857;-31.358387;-0.000000;,
    -1.796410;-31.358387;0.583689;,
    -1.796410;-31.358387;-0.583689;,
    -1.888857;-31.358387;-0.000000;,
    -1.528118;-31.358387;-1.110242;,
    -1.796410;-31.358387;-0.583689;,
    -1.110242;-31.358387;-1.528118;,
    -1.528118;-31.358387;-1.110242;,
    -0.583689;-31.358387;-1.796410;,
    -1.110242;-31.358387;-1.528118;,
    -0.000000;-31.358387;-1.888857;,
    -0.583689;-31.358387;-1.796410;,
    0.583689;-31.358387;-1.796410;,
    -0.000000;-31.358387;-1.888857;,
    1.110242;-31.358387;-1.528117;,
    0.583689;-31.358387;-1.796410;,
    1.528117;-31.358387;-1.110242;,
    1.110242;-31.358387;-1.528117;,
    1.796410;-31.358387;-0.583689;,
    1.528117;-31.358387;-1.110242;,
    1.888857;-31.358387;-0.000000;,
    1.796410;-31.358387;-0.583689;,
    1.796411;-31.358387;0.583689;,
    1.888857;-31.358387;-0.000000;,
    1.796411;31.358387;0.583689;,
    1.528118;31.358387;1.110243;,
    1.528118;31.358387;1.110243;,
    1.110243;31.358387;1.528118;,
    1.110243;31.358387;1.528118;,
    0.583689;31.358387;1.796411;,
    0.583689;31.358387;1.796411;,
    0.000000;31.358387;1.888858;,
    0.000000;31.358387;1.888858;,
    -0.583689;31.358387;1.796410;,
    -0.583689;31.358387;1.796410;,
    -1.110243;31.358387;1.528118;,
    -1.110243;31.358387;1.528118;,
    -1.528118;31.358387;1.110242;,
    -1.528118;31.358387;1.110242;,
    -1.796410;31.358387;0.583689;,
    -1.796410;31.358387;0.583689;,
    -1.888857;31.358387;-0.000000;,
    -1.888857;31.358387;-0.000000;,
    -1.796410;31.358387;-0.583689;,
    -1.796410;31.358387;-0.583689;,
    -1.528118;31.358387;-1.110242;,
    -1.528118;31.358387;-1.110242;,
    -1.110242;31.358387;-1.528118;,
    -1.110242;31.358387;-1.528118;,
    -0.583689;31.358387;-1.796410;,
    -0.583689;31.358387;-1.796410;,
    -0.000000;31.358387;-1.888857;,
    -0.000000;31.358387;-1.888857;,
    0.583689;31.358387;-1.796410;,
    0.583689;31.358387;-1.796410;,
    1.110242;31.358387;-1.528117;,
    1.110242;31.358387;-1.528117;,
    1.528117;31.358387;-1.110242;,
    1.528117;31.358387;-1.110242;,
    1.796410;31.358387;-0.583689;,
    1.796410;31.358387;-0.583689;,
    1.888857;31.358387;-0.000000;,
    1.888857;31.358387;-0.000000;,
    1.796411;31.358387;0.583689;;
    80;
    3;21,1,0;,
    3;20,21,0;,
    3;22,2,1;,
    3;21,22,1;,
    3;23,3,2;,
    3;22,23,2;,
    3;24,4,3;,
    3;23,24,3;,
    3;25,5,4;,
    3;24,25,4;,
    3;26,6,5;,
    3;25,26,5;,
    3;27,7,6;,
    3;26,27,6;,
    3;28,8,7;,
    3;27,28,7;,
    3;29,9,8;,
    3;28,29,8;,
    3;30,10,9;,
    3;29,30,9;,
    3;31,11,10;,
    3;30,31,10;,
    3;32,12,11;,
    3;31,32,11;,
    3;33,13,12;,
    3;32,33,12;,
    3;34,14,13;,
    3;33,34,13;,
    3;35,15,14;,
    3;34,35,14;,
    3;36,16,15;,
    3;35,36,15;,
    3;37,17,16;,
    3;36,37,16;,
    3;38,18,17;,
    3;37,38,17;,
    3;39,19,18;,
    3;38,39,18;,
    3;43,42,19;,
    3;39,43,19;,
    3;40,45,44;,
    3;40,47,46;,
    3;40,49,48;,
    3;40,51,50;,
    3;40,53,52;,
    3;40,55,54;,
    3;40,57,56;,
    3;40,59,58;,
    3;40,61,60;,
    3;40,63,62;,
    3;40,65,64;,
    3;40,67,66;,
    3;40,69,68;,
    3;40,71,70;,
    3;40,73,72;,
    3;40,75,74;,
    3;40,77,76;,
    3;40,79,78;,
    3;40,81,80;,
    3;40,83,82;,
    3;41,85,84;,
    3;41,87,86;,
    3;41,89,88;,
    3;41,91,90;,
    3;41,93,92;,
    3;41,95,94;,
    3;41,97,96;,
    3;41,99,98;,
    3;41,101,100;,
    3;41,103,102;,
    3;41,105,104;,
    3;41,107,106;,
    3;41,109,108;,
    3;41,111,110;,
    3;41,113,112;,
    3;41,115,114;,
    3;41,117,116;,
    3;41,119,118;,
    3;41,121,120;,
    3;41,123,122;;
    MeshNormals
    {
     124;
     0.848525;-0.451657;0.275702;,
     0.721798;-0.451657;0.524417;,
     0.524417;-0.451657;0.721799;,
     0.275702;-0.451657;0.848525;,
     -0.000000;-0.451657;0.892192;,
     -0.275702;-0.451657;0.848525;,
     -0.524417;-0.451657;0.721798;,
     -0.721799;-0.451657;0.524417;,
     -0.848525;-0.451657;0.275702;,
     -0.892192;-0.451657;-0.000000;,
     -0.848525;-0.451657;-0.275702;,
     -0.721798;-0.451657;-0.524417;,
     -0.524417;-0.451657;-0.721798;,
     -0.275702;-0.451657;-0.848525;,
     0.000000;-0.451657;-0.892192;,
     0.275703;-0.451657;-0.848525;,
     0.524417;-0.451657;-0.721798;,
     0.721798;-0.451657;-0.524417;,
     0.848525;-0.451657;-0.275702;,
     0.892192;-0.451656;-0.000001;,
     0.848525;0.451657;0.275702;,
     0.721798;0.451657;0.524417;,
     0.524417;0.451657;0.721799;,
     0.275702;0.451657;0.848525;,
     -0.000000;0.451657;0.892192;,
     -0.275702;0.451657;0.848525;,
     -0.524417;0.451657;0.721798;,
     -0.721799;0.451657;0.524417;,
     -0.848525;0.451657;0.275702;,
     -0.892192;0.451657;-0.000000;,
     -0.848525;0.451657;-0.275702;,
     -0.721798;0.451657;-0.524417;,
     -0.524417;0.451657;-0.721798;,
     -0.275702;0.451657;-0.848525;,
     0.000000;0.451657;-0.892192;,
     0.275703;0.451657;-0.848525;,
     0.524417;0.451657;-0.721798;,
     0.721798;0.451657;-0.524417;,
     0.848525;0.451657;-0.275702;,
     0.892192;0.451656;-0.000001;,
     0.000000;-1.000000;-0.000000;,
     0.000000;1.000000;-0.000000;,
     0.848525;-0.451657;0.275702;,
     0.848525;0.451657;0.275702;,
     0.000000;-1.000000;-0.000000;,
     0.848525;-0.451657;0.275702;,
     0.000000;-1.000000;-0.000000;,
     0.721798;-0.451657;0.524417;,
     0.000000;-1.000000;-0.000000;,
     0.524417;-0.451657;0.721799;,
     0.000000;-1.000000;-0.000000;,
     0.275702;-0.451657;0.848525;,
     0.000000;-1.000000;-0.000000;,
     -0.000000;-0.451657;0.892192;,
     0.000000;-1.000000;-0.000000;,
     -0.275702;-0.451657;0.848525;,
     0.000000;-1.000000;-0.000000;,
     -0.524417;-0.451657;0.721798;,
     0.000000;-1.000000;-0.000000;,
     -0.721799;-0.451657;0.524417;,
     0.000000;-1.000000;-0.000000;,
     -0.848525;-0.451657;0.275702;,
     0.000000;-1.000000;-0.000000;,
     -0.892192;-0.451657;-0.000000;,
     0.000000;-1.000000;-0.000000;,
     -0.848525;-0.451657;-0.275702;,
     0.000000;-1.000000;-0.000000;,
     -0.721798;-0.451657;-0.524417;,
     0.000000;-1.000000;-0.000000;,
     -0.524417;-0.451657;-0.721798;,
     0.000000;-1.000000;-0.000000;,
     -0.275702;-0.451657;-0.848525;,
     0.000000;-1.000000;-0.000000;,
     0.000000;-0.451657;-0.892192;,
     0.000000;-1.000000;-0.000000;,
     0.275703;-0.451657;-0.848525;,
     0.000000;-1.000000;-0.000000;,
     0.524417;-0.451657;-0.721798;,
     0.000000;-1.000000;-0.000000;,
     0.721798;-0.451657;-0.524417;,
     0.000000;-1.000000;-0.000000;,
     0.848525;-0.451657;-0.275702;,
     0.000000;-1.000000;-0.000000;,
     0.892192;-0.451656;-0.000001;,
     0.000000;1.000000;-0.000000;,
     0.721798;0.451657;0.524417;,
     0.000000;1.000000;-0.000000;,
     0.524417;0.451657;0.721799;,
     0.000000;1.000000;-0.000000;,
     0.275702;0.451657;0.848525;,
     0.000000;1.000000;-0.000000;,
     -0.000000;0.451657;0.892192;,
     0.000000;1.000000;-0.000000;,
     -0.275702;0.451657;0.848525;,
     0.000000;1.000000;-0.000000;,
     -0.524417;0.451657;0.721798;,
     0.000000;1.000000;-0.000000;,
     -0.721799;0.451657;0.524417;,
     0.000000;1.000000;-0.000000;,
     -0.848525;0.451657;0.275702;,
     0.000000;1.000000;-0.000000;,
     -0.892192;0.451657;-0.000000;,
     0.000000;1.000000;-0.000000;,
     -0.848525;0.451657;-0.275702;,
     0.000000;1.000000;-0.000000;,
     -0.721798;0.451657;-0.524417;,
     0.000000;1.000000;-0.000000;,
     -0.524417;0.451657;-0.721798;,
     0.000000;1.000000;-0.000000;,
     -0.275702;0.451657;-0.848525;,
     0.000000;1.000000;-0.000000;,
     0.000000;0.451657;-0.892192;,
     0.000000;1.000000;-0.000000;,
     0.275703;0.451657;-0.848525;,
     0.000000;1.000000;-0.000000;,
     0.524417;0.451657;-0.721798;,
     0.000000;1.000000;-0.000000;,
     0.721798;0.451657;-0.524417;,
     0.000000;1.000000;-0.000000;,
     0.848525;0.451657;-0.275702;,
     0.000000;1.000000;-0.000000;,
     0.892192;0.451656;-0.000001;,
     0.000000;1.000000;-0.000000;,
     0.848525;0.451657;0.275702;;
     80;
     3;21,1,0;,
     3;20,21,0;,
     3;22,2,1;,
     3;21,22,1;,
     3;23,3,2;,
     3;22,23,2;,
     3;24,4,3;,
     3;23,24,3;,
     3;25,5,4;,
     3;24,25,4;,
     3;26,6,5;,
     3;25,26,5;,
     3;27,7,6;,
     3;26,27,6;,
     3;28,8,7;,
     3;27,28,7;,
     3;29,9,8;,
     3;28,29,8;,
     3;30,10,9;,
     3;29,30,9;,
     3;31,11,10;,
     3;30,31,10;,
     3;32,12,11;,
     3;31,32,11;,
     3;33,13,12;,
     3;32,33,12;,
     3;34,14,13;,
     3;33,34,13;,
     3;35,15,14;,
     3;34,35,14;,
     3;36,16,15;,
     3;35,36,15;,
     3;37,17,16;,
     3;36,37,16;,
     3;38,18,17;,
     3;37,38,17;,
     3;39,19,18;,
     3;38,39,18;,
     3;43,42,19;,
     3;39,43,19;,
     3;40,45,44;,
     3;40,47,46;,
     3;40,49,48;,
     3;40,51,50;,
     3;40,53,52;,
     3;40,55,54;,
     3;40,57,56;,
     3;40,59,58;,
     3;40,61,60;,
     3;40,63,62;,
     3;40,65,64;,
     3;40,67,66;,
     3;40,69,68;,
     3;40,71,70;,
     3;40,73,72;,
     3;40,75,74;,
     3;40,77,76;,
     3;40,79,78;,
     3;40,81,80;,
     3;40,83,82;,
     3;41,85,84;,
     3;41,87,86;,
     3;41,89,88;,
     3;41,91,90;,
     3;41,93,92;,
     3;41,95,94;,
     3;41,97,96;,
     3;41,99,98;,
     3;41,101,100;,
     3;41,103,102;,
     3;41,105,104;,
     3;41,107,106;,
     3;41,109,108;,
     3;41,111,110;,
     3;41,113,112;,
     3;41,115,114;,
     3;41,117,116;,
     3;41,119,118;,
     3;41,121,120;,
     3;41,123,122;;
    }
    MeshTextureCoords
    {
     124;
     0.375000;0.687500;,
     0.387500;0.687500;,
     0.400000;0.687500;,
     0.412500;0.687500;,
     0.425000;0.687500;,
     0.437500;0.687500;,
     0.450000;0.687500;,
     0.462500;0.687500;,
     0.475000;0.687500;,
     0.487500;0.687500;,
     0.500000;0.687500;,
     0.512500;0.687500;,
     0.525000;0.687500;,
     0.537500;0.687500;,
     0.550000;0.687500;,
     0.562500;0.687500;,
     0.575000;0.687500;,
     0.587500;0.687500;,
     0.600000;0.687500;,
     0.612500;0.687500;,
     0.375000;0.311560;,
     0.387500;0.311560;,
     0.400000;0.311560;,
     0.412500;0.311560;,
     0.425000;0.311560;,
     0.437500;0.311560;,
     0.450000;0.311560;,
     0.462500;0.311560;,
     0.475000;0.311560;,
     0.487500;0.311560;,
     0.500000;0.311560;,
     0.512500;0.311560;,
     0.525000;0.311560;,
     0.537500;0.311560;,
     0.550000;0.311560;,
     0.562500;0.311560;,
     0.575000;0.311560;,
     0.587500;0.311560;,
     0.600000;0.311560;,
     0.612500;0.311560;,
     0.500000;0.850000;,
     0.500000;0.162500;,
     0.625000;0.687500;,
     0.625000;0.311560;,
     0.626409;0.935592;,
     0.648603;0.892034;,
     0.591842;0.970159;,
     0.626409;0.935592;,
     0.548284;0.992353;,
     0.591842;0.970159;,
     0.500000;1.000000;,
     0.548284;0.992353;,
     0.451716;0.992353;,
     0.500000;1.000000;,
     0.408159;0.970159;,
     0.451716;0.992353;,
     0.373591;0.935591;,
     0.408159;0.970159;,
     0.351397;0.892034;,
     0.373591;0.935591;,
     0.343750;0.843750;,
     0.351397;0.892034;,
     0.351397;0.795466;,
     0.343750;0.843750;,
     0.373591;0.751909;,
     0.351397;0.795466;,
     0.408159;0.717341;,
     0.373591;0.751909;,
     0.451716;0.695147;,
     0.408159;0.717341;,
     0.500000;0.687500;,
     0.451716;0.695147;,
     0.548284;0.695147;,
     0.500000;0.687500;,
     0.591841;0.717341;,
     0.548284;0.695147;,
     0.626409;0.751909;,
     0.591841;0.717341;,
     0.648603;0.795466;,
     0.626409;0.751909;,
     0.656250;0.843750;,
     0.648603;0.795466;,
     0.648603;0.892034;,
     0.656250;0.843750;,
     0.648603;0.107966;,
     0.626409;0.064409;,
     0.626409;0.064409;,
     0.591841;0.029841;,
     0.591841;0.029841;,
     0.548284;0.007647;,
     0.548284;0.007647;,
     0.500000;0.000000;,
     0.500000;0.000000;,
     0.451716;0.007647;,
     0.451716;0.007647;,
     0.408159;0.029841;,
     0.408159;0.029841;,
     0.373591;0.064409;,
     0.373591;0.064409;,
     0.351397;0.107966;,
     0.351397;0.107966;,
     0.343750;0.156250;,
     0.343750;0.156250;,
     0.351397;0.204534;,
     0.351397;0.204534;,
     0.373591;0.248091;,
     0.373591;0.248091;,
     0.408159;0.282659;,
     0.408159;0.282659;,
     0.451716;0.304853;,
     0.451716;0.304853;,
     0.500000;0.312500;,
     0.500000;0.312500;,
     0.548284;0.304853;,
     0.548284;0.304853;,
     0.591842;0.282659;,
     0.591842;0.282659;,
     0.626409;0.248092;,
     0.626409;0.248092;,
     0.648603;0.204534;,
     0.648603;0.204534;,
     0.656250;0.156250;,
     0.656250;0.156250;,
     0.648603;0.107966;;
    }
    MeshMaterialList
    {
     1;
     80;
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
     124;
     42;
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
     0,
     20,
     1,
     0,
     2,
     1,
     3,
     2,
     4,
     3,
     5,
     4,
     6,
     5,
     7,
     6,
     8,
     7,
     9,
     8,
     10,
     9,
     11,
     10,
     12,
     11,
     13,
     12,
     14,
     13,
     15,
     14,
     16,
     15,
     17,
     16,
     18,
     17,
     19,
     18,
     0,
     19,
     20,
     21,
     21,
     22,
     22,
     23,
     23,
     24,
     24,
     25,
     25,
     26,
     26,
     27,
     27,
     28,
     28,
     29,
     29,
     30,
     30,
     31,
     31,
     32,
     32,
     33,
     33,
     34,
     34,
     35,
     35,
     36,
     36,
     37,
     37,
     38,
     38,
     39,
     39,
     20;
    }
   }
  }
 }
}

# Animations definition.

