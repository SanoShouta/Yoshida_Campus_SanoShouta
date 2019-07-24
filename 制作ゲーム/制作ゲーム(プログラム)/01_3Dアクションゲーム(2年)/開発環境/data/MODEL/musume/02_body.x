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
  "data/TEXTURE/musume.jpg";
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
   82;
   -5.514626;0.000026;-2.952601;,
   5.514626;0.000026;-2.952601;,
   -6.358728;7.452924;-2.729450;,
   6.358728;7.452924;-2.729450;,
   -6.358728;7.452924;2.300723;,
   6.358728;7.452924;2.864317;,
   -5.514626;0.000026;2.406075;,
   5.514626;0.000026;2.406075;,
   0.000000;0.000004;-4.397472;,
   0.000000;0.000004;3.882701;,
   0.000000;9.404997;3.417806;,
   0.000000;9.404997;-2.814650;,
   -6.358728;3.665134;-4.397520;,
   0.000000;3.612616;-6.022518;,
   6.358728;3.665134;-4.397520;,
   6.358728;3.412643;3.342588;,
   0.000000;3.360125;4.449807;,
   -6.358728;3.412643;3.342588;,
   3.008319;0.000007;-4.032975;,
   3.468791;3.612616;-5.500561;,
   3.468791;9.167263;-2.697494;,
   3.468791;9.167263;2.888474;,
   3.468791;3.360125;4.290141;,
   3.008319;0.000011;3.652894;,
   -3.008319;0.000007;-4.032975;,
   -3.008319;0.000011;3.652894;,
   -3.468791;3.360125;4.290141;,
   -3.468791;9.167263;3.256216;,
   -3.468791;9.167263;-2.697494;,
   -3.468791;3.612616;-5.500561;,
   -6.358728;8.021184;-0.195679;,
   -3.468791;9.461034;0.114362;,
   0.000000;9.698774;0.223858;,
   3.468791;9.461034;0.114362;,
   6.358728;8.021184;-0.195679;,
   6.358728;3.412643;-0.360727;,
   5.514626;0.000018;-0.273263;,
   3.008319;0.000000;-0.285339;,
   0.000000;0.000000;-0.187869;,
   -3.008319;0.000000;-0.285339;,
   -5.514626;0.000018;-0.273263;,
   -6.358728;3.412643;-0.360727;,
   -6.358728;5.936261;3.110575;,
   -3.468791;6.638844;4.114874;,
   0.000000;6.757705;4.337161;,
   3.468791;6.638844;4.114874;,
   6.358728;5.936261;3.110575;,
   6.358728;6.220386;-0.278203;,
   6.358728;5.936261;-3.826599;,
   3.468791;6.599729;-4.131089;,
   0.000000;6.718594;-4.099874;,
   -3.468791;6.599729;-4.131089;,
   -6.358728;5.936261;-3.826599;,
   -6.358728;6.220386;-0.278203;,
   0.000000;0.000000;-0.187869;,
   3.008319;0.000000;-0.285339;,
   -3.008319;0.000000;-0.285339;,
   -5.514626;0.000018;-0.273263;,
   -6.358728;5.936261;3.110575;,
   -3.468791;9.461034;0.114362;,
   -6.358728;8.021184;-0.195679;,
   0.000000;9.698774;0.223858;,
   3.468791;9.461034;0.114362;,
   6.358728;8.021184;-0.195679;,
   6.358728;3.412643;-0.360727;,
   6.358728;6.220386;-0.278203;,
   6.358728;5.936261;-3.826599;,
   5.514626;0.000018;-0.273263;,
   3.008319;0.000000;-0.285339;,
   5.514626;0.000018;-0.273263;,
   0.000000;0.000000;-0.187869;,
   3.008319;0.000000;-0.285339;,
   -3.008319;0.000000;-0.285339;,
   0.000000;0.000000;-0.187869;,
   -5.514626;0.000018;-0.273263;,
   -3.008319;0.000000;-0.285339;,
   -6.358728;3.412643;-0.360727;,
   -6.358728;6.220386;-0.278203;,
   6.358728;5.936261;3.110575;,
   6.358728;8.021184;-0.195679;,
   -6.358728;5.936261;-3.826599;,
   -6.358728;8.021184;-0.195679;;
   104;
   3;13,50,49;,
   3;19,13,49;,
   3;33,32,10;,
   3;21,33,10;,
   3;22,45,44;,
   3;16,22,44;,
   3;9,38,37;,
   3;23,9,37;,
   3;35,47,46;,
   3;15,35,46;,
   3;53,41,17;,
   3;42,53,17;,
   3;25,39,54;,
   3;9,25,54;,
   3;44,43,26;,
   3;16,44,26;,
   3;32,31,27;,
   3;10,32,27;,
   3;29,51,50;,
   3;13,29,50;,
   3;8,24,29;,
   3;13,8,29;,
   3;13,19,18;,
   3;8,13,18;,
   3;7,36,35;,
   3;15,7,35;,
   3;22,16,9;,
   3;23,22,9;,
   3;16,26,25;,
   3;9,16,25;,
   3;41,40,6;,
   3;17,41,6;,
   3;18,19,14;,
   3;1,18,14;,
   3;19,49,48;,
   3;14,19,48;,
   3;34,33,21;,
   3;5,34,21;,
   3;45,22,15;,
   3;46,45,15;,
   3;15,22,23;,
   3;7,15,23;,
   3;23,55,36;,
   3;7,23,36;,
   3;56,25,6;,
   3;57,56,6;,
   3;25,26,17;,
   3;6,25,17;,
   3;26,43,58;,
   3;17,26,58;,
   3;27,31,30;,
   3;4,27,30;,
   3;51,29,12;,
   3;52,51,12;,
   3;29,24,0;,
   3;12,29,0;,
   3;59,28,2;,
   3;60,59,2;,
   3;28,59,61;,
   3;11,28,61;,
   3;11,61,62;,
   3;20,11,62;,
   3;20,62,63;,
   3;3,20,63;,
   3;65,64,14;,
   3;66,65,14;,
   3;64,67,1;,
   3;14,64,1;,
   3;69,68,18;,
   3;1,69,18;,
   3;71,70,8;,
   3;18,71,8;,
   3;73,72,24;,
   3;8,73,24;,
   3;24,75,74;,
   3;0,24,74;,
   3;0,74,76;,
   3;12,0,76;,
   3;76,77,52;,
   3;12,76,52;,
   3;43,27,4;,
   3;58,43,4;,
   3;27,43,44;,
   3;10,27,44;,
   3;44,45,21;,
   3;10,44,21;,
   3;21,45,46;,
   3;5,21,46;,
   3;78,47,34;,
   3;5,78,34;,
   3;79,65,48;,
   3;3,79,48;,
   3;48,49,20;,
   3;3,48,20;,
   3;49,50,11;,
   3;20,49,11;,
   3;50,51,28;,
   3;11,50,28;,
   3;28,51,52;,
   3;2,28,52;,
   3;80,77,60;,
   3;2,80,60;,
   3;81,53,58;,
   3;4,81,58;;
   MeshNormals
   {
    82;
    -0.581797;-0.720841;-0.376697;,
    0.581425;-0.721275;-0.376440;,
    -0.714522;0.576133;-0.396898;,
    0.715852;0.575308;-0.395698;,
    -0.777324;0.492564;0.391342;,
    0.741960;0.496052;0.451030;,
    -0.604864;-0.687226;0.402319;,
    0.604864;-0.687226;0.402319;,
    0.000012;-0.838078;-0.545551;,
    -0.000032;-0.768714;0.639593;,
    0.016430;0.795109;0.606244;,
    0.000166;0.826958;-0.562264;,
    -0.818270;-0.100798;-0.565928;,
    0.001821;0.041464;-0.999138;,
    0.822266;-0.100267;-0.560201;,
    0.816297;-0.137724;0.560974;,
    -0.000025;-0.068974;0.997618;,
    -0.815684;-0.137738;0.561862;,
    0.141104;-0.838653;-0.526072;,
    0.223360;-0.001899;-0.974734;,
    0.235097;0.802334;-0.548625;,
    0.272498;0.745036;0.608823;,
    0.206913;-0.088784;0.974323;,
    0.136355;-0.788479;0.599757;,
    -0.141334;-0.838246;-0.526658;,
    -0.136444;-0.788187;0.600120;,
    -0.205839;-0.088190;0.974604;,
    -0.312158;0.745398;0.589016;,
    -0.233763;0.802407;-0.549088;,
    -0.214146;-0.001553;-0.976800;,
    -0.750816;0.660501;-0.003638;,
    -0.285087;0.958491;-0.004453;,
    0.001520;0.999996;-0.002373;,
    0.281560;0.959533;-0.004537;,
    0.745559;0.666411;-0.006099;,
    0.992817;-0.119627;-0.001810;,
    0.796436;-0.604715;-0.002945;,
    0.000001;-1.000000;0.000002;,
    0.000001;-1.000000;0.000002;,
    -0.000001;-1.000000;0.000002;,
    -0.796436;-0.604715;-0.002947;,
    -0.992817;-0.119627;-0.001810;,
    -1.000000;0.000000;-0.000000;,
    -0.222873;0.204580;0.953139;,
    0.012650;0.200928;0.979524;,
    0.191241;0.198008;0.961363;,
    0.638739;0.143810;0.755864;,
    1.000000;0.000000;-0.000000;,
    0.623647;0.342509;-0.702675;,
    0.160670;0.446658;-0.880160;,
    0.001707;0.466124;-0.884718;,
    -0.152063;0.446097;-0.881972;,
    -0.615514;0.343604;-0.709280;,
    -1.000000;0.000000;-0.000000;,
    -0.000001;-1.000000;0.000002;,
    0.000007;-1.000000;0.000003;,
    -0.000007;-1.000000;0.000003;,
    -0.000007;-1.000000;0.000003;,
    -0.690533;0.170429;0.702935;,
    -0.285087;0.958491;-0.004453;,
    -0.750816;0.660501;-0.003638;,
    0.001520;0.999996;-0.002373;,
    0.281560;0.959533;-0.004537;,
    0.745559;0.666411;-0.006099;,
    0.992817;-0.119627;-0.001810;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    0.796436;-0.604715;-0.002945;,
    0.000008;-1.000000;-0.000002;,
    0.000008;-1.000000;-0.000002;,
    0.000001;-1.000000;-0.000001;,
    0.000001;-1.000000;-0.000001;,
    -0.000001;-1.000000;-0.000001;,
    -0.000001;-1.000000;-0.000001;,
    -0.796436;-0.604715;-0.002947;,
    -0.000008;-1.000000;-0.000002;,
    -0.992817;-0.119627;-0.001810;,
    -1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;;
    104;
    3;13,50,49;,
    3;19,13,49;,
    3;33,32,10;,
    3;21,33,10;,
    3;22,45,44;,
    3;16,22,44;,
    3;9,38,37;,
    3;23,9,37;,
    3;35,47,46;,
    3;15,35,46;,
    3;53,41,17;,
    3;42,53,17;,
    3;25,39,54;,
    3;9,25,54;,
    3;44,43,26;,
    3;16,44,26;,
    3;32,31,27;,
    3;10,32,27;,
    3;29,51,50;,
    3;13,29,50;,
    3;8,24,29;,
    3;13,8,29;,
    3;13,19,18;,
    3;8,13,18;,
    3;7,36,35;,
    3;15,7,35;,
    3;22,16,9;,
    3;23,22,9;,
    3;16,26,25;,
    3;9,16,25;,
    3;41,40,6;,
    3;17,41,6;,
    3;18,19,14;,
    3;1,18,14;,
    3;19,49,48;,
    3;14,19,48;,
    3;34,33,21;,
    3;5,34,21;,
    3;45,22,15;,
    3;46,45,15;,
    3;15,22,23;,
    3;7,15,23;,
    3;23,55,36;,
    3;7,23,36;,
    3;56,25,6;,
    3;57,56,6;,
    3;25,26,17;,
    3;6,25,17;,
    3;26,43,58;,
    3;17,26,58;,
    3;27,31,30;,
    3;4,27,30;,
    3;51,29,12;,
    3;52,51,12;,
    3;29,24,0;,
    3;12,29,0;,
    3;59,28,2;,
    3;60,59,2;,
    3;28,59,61;,
    3;11,28,61;,
    3;11,61,62;,
    3;20,11,62;,
    3;20,62,63;,
    3;3,20,63;,
    3;65,64,14;,
    3;66,65,14;,
    3;64,67,1;,
    3;14,64,1;,
    3;69,68,18;,
    3;1,69,18;,
    3;71,70,8;,
    3;18,71,8;,
    3;73,72,24;,
    3;8,73,24;,
    3;24,75,74;,
    3;0,24,74;,
    3;0,74,76;,
    3;12,0,76;,
    3;76,77,52;,
    3;12,76,52;,
    3;43,27,4;,
    3;58,43,4;,
    3;27,43,44;,
    3;10,27,44;,
    3;44,45,21;,
    3;10,44,21;,
    3;21,45,46;,
    3;5,21,46;,
    3;78,47,34;,
    3;5,78,34;,
    3;79,65,48;,
    3;3,79,48;,
    3;48,49,20;,
    3;3,48,20;,
    3;49,50,11;,
    3;20,49,11;,
    3;50,51,28;,
    3;11,50,28;,
    3;28,51,52;,
    3;2,28,52;,
    3;80,77,60;,
    3;2,80,60;,
    3;81,53,58;,
    3;4,81,58;;
   }
   MeshTextureCoords
   {
    82;
    0.755830;0.402850;,
    0.894045;0.402850;,
    0.745252;0.307341;,
    0.904623;0.307341;,
    0.477480;0.306279;,
    0.636886;0.306279;,
    0.488060;0.401808;,
    0.626306;0.401808;,
    0.824938;0.402850;,
    0.557183;0.401808;,
    0.557183;0.281257;,
    0.824938;0.282325;,
    0.745252;0.359117;,
    0.824938;0.359790;,
    0.904623;0.359117;,
    0.636886;0.358066;,
    0.557183;0.358739;,
    0.477480;0.358066;,
    0.862637;0.402850;,
    0.868408;0.359790;,
    0.868408;0.285372;,
    0.600662;0.284305;,
    0.600662;0.358739;,
    0.594891;0.401808;,
    0.787238;0.402850;,
    0.519475;0.401808;,
    0.513704;0.358739;,
    0.513704;0.284305;,
    0.781468;0.285372;,
    0.781468;0.359790;,
    0.477480;0.298995;,
    0.513704;0.280539;,
    0.557183;0.277492;,
    0.600662;0.280539;,
    0.636886;0.298995;,
    0.636886;0.358066;,
    0.626306;0.401808;,
    0.594891;0.401808;,
    0.557183;0.401808;,
    0.519475;0.401808;,
    0.488060;0.401808;,
    0.477480;0.358066;,
    0.477480;0.325719;,
    0.513704;0.316713;,
    0.557183;0.315190;,
    0.600662;0.316713;,
    0.636886;0.325719;,
    0.636886;0.322077;,
    0.904623;0.326777;,
    0.868408;0.329180;,
    0.824938;0.327657;,
    0.781468;0.329180;,
    0.745252;0.326777;,
    0.477480;0.322077;,
    0.557183;0.401808;,
    0.594891;0.401808;,
    0.519475;0.401808;,
    0.488060;0.401808;,
    0.477480;0.325719;,
    0.781468;0.281607;,
    0.745252;0.300059;,
    0.824938;0.278560;,
    0.868408;0.281607;,
    0.904623;0.300059;,
    0.904623;0.359117;,
    0.904623;0.323136;,
    0.904623;0.326777;,
    0.894045;0.402850;,
    0.862637;0.402850;,
    0.894045;0.402850;,
    0.824938;0.402850;,
    0.862637;0.402850;,
    0.787238;0.402850;,
    0.824938;0.402850;,
    0.755830;0.402850;,
    0.787238;0.402850;,
    0.745252;0.359117;,
    0.745252;0.323136;,
    0.636886;0.325719;,
    0.904623;0.300059;,
    0.745252;0.326777;,
    0.477480;0.298995;;
   }
   MeshMaterialList
   {
    1;
    104;
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
    82;
    54;
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
    44,
    45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    38,
    37,
    39,
    40,
    42,
    31,
    30,
    32,
    33,
    34,
    35,
    47,
    48,
    36,
    37,
    36,
    38,
    37,
    39,
    38,
    40,
    39,
    41,
    53,
    46,
    34,
    52,
    30;
   }
  }
 }
}

# Animations definition.

