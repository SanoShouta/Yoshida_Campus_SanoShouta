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
   58;
   -2.583511;3.321222;21.366100;,
   2.583511;3.321222;21.366100;,
   -0.763964;-2.396069;1.036835;,
   0.763964;-2.396069;1.036835;,
   -0.864002;-0.591618;1.036829;,
   0.864002;-0.591618;1.036829;,
   -2.889047;7.862628;16.562378;,
   2.889047;7.862628;16.562378;,
   0.000000;2.754662;21.965385;,
   0.000000;8.975286;15.385447;,
   0.000000;-0.061324;1.036835;,
   0.000000;-2.666093;1.036829;,
   -1.282716;-1.543701;1.036829;,
   0.000000;-0.046671;-0.000000;,
   1.282716;-1.543701;1.036829;,
   4.227896;5.864978;18.675413;,
   0.000000;14.155993;22.826141;,
   -4.227896;5.864978;18.675413;,
   -2.477611;-4.289038;10.502870;,
   0.000000;-5.007126;10.711610;,
   2.477611;-4.289038;10.502870;,
   4.095641;-1.064976;9.565652;,
   2.782861;1.466934;8.829644;,
   0.000000;2.877173;8.419703;,
   -2.782861;1.466934;8.829644;,
   -4.095641;-1.064976;9.565652;,
   -2.921887;-1.981609;16.700104;,
   0.000000;-2.816052;17.198486;,
   2.921887;-1.981609;16.700104;,
   4.803442;1.764897;14.462450;,
   3.273938;4.707092;12.705189;,
   0.000000;6.345856;11.726423;,
   -3.273938;4.707092;12.705189;,
   -4.803442;1.764897;14.462450;,
   -1.763136;-0.383516;4.514993;,
   0.000000;0.558951;4.400635;,
   1.763136;-0.383516;4.514993;,
   2.603181;-2.075600;4.720322;,
   1.565808;-4.230252;4.981784;,
   0.000000;-4.710150;5.040018;,
   -1.565808;-4.230252;4.981784;,
   -2.603181;-2.075600;4.720322;,
   1.598168;10.453369;19.990225;,
   2.338795;9.556030;21.325239;,
   1.429152;8.413384;23.025215;,
   0.000000;8.158887;23.403837;,
   -1.429152;8.413384;23.025215;,
   -2.338795;9.556030;21.325239;,
   -1.598168;10.453369;19.990225;,
   0.000000;10.953174;19.246639;,
   0.827669;-0.996146;0.369733;,
   0.557495;-0.381816;0.369727;,
   0.000000;-0.039642;0.369733;,
   -0.557495;-0.381816;0.369727;,
   -0.827669;-0.996146;0.369733;,
   -0.492946;-1.517111;0.369733;,
   0.000000;-1.691342;0.369733;,
   0.492946;-1.517111;0.369733;;
   112;
   3;19,39,38;,
   3;20,19,38;,
   3;13,52,51;,
   3;35,23,22;,
   3;36,35,22;,
   3;16,43,42;,
   3;21,37,36;,
   3;22,21,36;,
   3;41,25,24;,
   3;34,41,24;,
   3;16,49,48;,
   3;23,35,34;,
   3;24,23,34;,
   3;13,54,53;,
   3;39,19,18;,
   3;40,39,18;,
   3;13,55,54;,
   3;13,57,56;,
   3;37,21,20;,
   3;38,37,20;,
   3;16,44,43;,
   3;16,46,45;,
   3;25,41,40;,
   3;18,25,40;,
   3;19,27,26;,
   3;18,19,26;,
   3;27,19,20;,
   3;28,27,20;,
   3;21,29,28;,
   3;20,21,28;,
   3;29,21,22;,
   3;30,29,22;,
   3;23,31,30;,
   3;22,23,30;,
   3;31,23,24;,
   3;32,31,24;,
   3;25,33,32;,
   3;24,25,32;,
   3;33,25,18;,
   3;26,33,18;,
   3;27,8,0;,
   3;26,27,0;,
   3;8,27,28;,
   3;1,8,28;,
   3;29,15,1;,
   3;28,29,1;,
   3;15,29,30;,
   3;7,15,30;,
   3;30,31,9;,
   3;7,30,9;,
   3;9,31,32;,
   3;6,9,32;,
   3;33,17,6;,
   3;32,33,6;,
   3;17,33,26;,
   3;0,17,26;,
   3;35,10,4;,
   3;34,35,4;,
   3;10,35,36;,
   3;5,10,36;,
   3;36,37,14;,
   3;5,36,14;,
   3;14,37,38;,
   3;3,14,38;,
   3;38,39,11;,
   3;3,38,11;,
   3;11,39,40;,
   3;2,11,40;,
   3;40,41,12;,
   3;2,40,12;,
   3;12,41,34;,
   3;4,12,34;,
   3;16,45,44;,
   3;16,48,47;,
   3;16,47,46;,
   3;16,42,49;,
   3;13,50,57;,
   3;13,53,52;,
   3;13,56,55;,
   3;13,51,50;,
   3;42,43,15;,
   3;7,42,15;,
   3;43,44,1;,
   3;15,43,1;,
   3;44,45,8;,
   3;1,44,8;,
   3;45,46,0;,
   3;8,45,0;,
   3;46,47,17;,
   3;0,46,17;,
   3;47,48,6;,
   3;17,47,6;,
   3;49,9,6;,
   3;48,49,6;,
   3;49,42,7;,
   3;9,49,7;,
   3;50,51,5;,
   3;14,50,5;,
   3;51,52,10;,
   3;5,51,10;,
   3;52,53,4;,
   3;10,52,4;,
   3;53,54,12;,
   3;4,53,12;,
   3;54,55,2;,
   3;12,54,2;,
   3;56,11,2;,
   3;55,56,2;,
   3;56,57,3;,
   3;11,56,3;,
   3;57,50,14;,
   3;3,57,14;;
   MeshNormals
   {
    58;
    -0.650614;-0.292903;0.700649;,
    0.651031;-0.295308;0.699251;,
    -0.498956;-0.597993;-0.627253;,
    0.499423;-0.598299;-0.626590;,
    -0.733009;0.656610;-0.177656;,
    0.732744;0.656416;-0.179453;,
    -0.711972;0.622998;-0.323989;,
    0.712483;0.621824;-0.325120;,
    0.000037;-0.462527;0.886605;,
    0.000000;0.848076;-0.529874;,
    -0.000299;0.996627;-0.082068;,
    -0.000000;-0.745944;-0.666009;,
    -0.888966;-0.012910;-0.457792;,
    0.000000;0.274252;-0.961658;,
    0.889334;-0.013286;-0.457065;,
    0.970390;0.186344;0.153686;,
    -0.000000;0.875767;0.482733;,
    -0.969425;0.189544;0.155849;,
    -0.652351;-0.756056;0.053075;,
    0.000078;-0.990648;0.136443;,
    0.652483;-0.755888;0.053856;,
    0.976938;-0.054295;-0.206502;,
    0.698991;0.548248;-0.459169;,
    0.001108;0.797032;-0.603936;,
    -0.696334;0.547539;-0.464026;,
    -0.976041;-0.053999;-0.210781;,
    -0.676443;-0.608735;0.414567;,
    0.000102;-0.827037;0.562147;,
    0.677290;-0.608403;0.413672;,
    0.999522;0.006935;-0.030142;,
    0.723359;0.528811;-0.443971;,
    0.000986;0.760669;-0.649139;,
    -0.721744;0.527964;-0.447594;,
    -0.999481;0.005989;-0.031646;,
    -0.708002;0.629526;-0.320047;,
    -0.000163;0.936224;-0.351404;,
    0.708023;0.629317;-0.320411;,
    0.948470;-0.044213;-0.313768;,
    0.607729;-0.743270;-0.279669;,
    -0.000009;-0.963946;-0.266098;,
    -0.607493;-0.742814;-0.281390;,
    -0.947713;-0.043950;-0.316083;,
    0.694605;0.641217;-0.326136;,
    0.911673;0.340610;0.229862;,
    0.587126;0.027815;0.809018;,
    0.000023;-0.079048;0.996871;,
    -0.586272;0.030790;0.809529;,
    -0.909762;0.344532;0.231584;,
    -0.693678;0.642776;-0.325036;,
    0.000000;0.821414;-0.570333;,
    0.662010;0.039394;-0.748459;,
    0.706844;0.653507;-0.270740;,
    0.000000;0.999977;0.006741;,
    -0.706844;0.653507;-0.270741;,
    -0.661383;0.039765;-0.748993;,
    -0.287681;-0.337058;-0.896455;,
    -0.000000;-0.397748;-0.917495;,
    0.288253;-0.337497;-0.896106;;
    112;
    3;19,39,38;,
    3;20,19,38;,
    3;13,52,51;,
    3;35,23,22;,
    3;36,35,22;,
    3;16,43,42;,
    3;21,37,36;,
    3;22,21,36;,
    3;41,25,24;,
    3;34,41,24;,
    3;16,49,48;,
    3;23,35,34;,
    3;24,23,34;,
    3;13,54,53;,
    3;39,19,18;,
    3;40,39,18;,
    3;13,55,54;,
    3;13,57,56;,
    3;37,21,20;,
    3;38,37,20;,
    3;16,44,43;,
    3;16,46,45;,
    3;25,41,40;,
    3;18,25,40;,
    3;19,27,26;,
    3;18,19,26;,
    3;27,19,20;,
    3;28,27,20;,
    3;21,29,28;,
    3;20,21,28;,
    3;29,21,22;,
    3;30,29,22;,
    3;23,31,30;,
    3;22,23,30;,
    3;31,23,24;,
    3;32,31,24;,
    3;25,33,32;,
    3;24,25,32;,
    3;33,25,18;,
    3;26,33,18;,
    3;27,8,0;,
    3;26,27,0;,
    3;8,27,28;,
    3;1,8,28;,
    3;29,15,1;,
    3;28,29,1;,
    3;15,29,30;,
    3;7,15,30;,
    3;30,31,9;,
    3;7,30,9;,
    3;9,31,32;,
    3;6,9,32;,
    3;33,17,6;,
    3;32,33,6;,
    3;17,33,26;,
    3;0,17,26;,
    3;35,10,4;,
    3;34,35,4;,
    3;10,35,36;,
    3;5,10,36;,
    3;36,37,14;,
    3;5,36,14;,
    3;14,37,38;,
    3;3,14,38;,
    3;38,39,11;,
    3;3,38,11;,
    3;11,39,40;,
    3;2,11,40;,
    3;40,41,12;,
    3;2,40,12;,
    3;12,41,34;,
    3;4,12,34;,
    3;16,45,44;,
    3;16,48,47;,
    3;16,47,46;,
    3;16,42,49;,
    3;13,50,57;,
    3;13,53,52;,
    3;13,56,55;,
    3;13,51,50;,
    3;42,43,15;,
    3;7,42,15;,
    3;43,44,1;,
    3;15,43,1;,
    3;44,45,8;,
    3;1,44,8;,
    3;45,46,0;,
    3;8,45,0;,
    3;46,47,17;,
    3;0,46,17;,
    3;47,48,6;,
    3;17,47,6;,
    3;49,9,6;,
    3;48,49,6;,
    3;49,42,7;,
    3;9,49,7;,
    3;50,51,5;,
    3;14,50,5;,
    3;51,52,10;,
    3;5,51,10;,
    3;52,53,4;,
    3;10,52,4;,
    3;53,54,12;,
    3;4,53,12;,
    3;54,55,2;,
    3;12,54,2;,
    3;56,11,2;,
    3;55,56,2;,
    3;56,57,3;,
    3;11,56,3;,
    3;57,50,14;,
    3;3,57,14;;
   }
   MeshTextureCoords
   {
    58;
    0.623966;0.067126;,
    0.623966;0.162257;,
    0.249678;0.100626;,
    0.249678;0.128757;,
    0.249678;0.098784;,
    0.249678;0.130599;,
    0.535523;0.061501;,
    0.535523;0.167883;,
    0.634999;0.114692;,
    0.513854;0.114692;,
    0.249678;0.114692;,
    0.249678;0.114692;,
    0.249678;0.091075;,
    0.230588;0.114692;,
    0.249678;0.138308;,
    0.574426;0.192533;,
    0.650847;0.114692;,
    0.574427;0.036851;,
    0.423960;0.069076;,
    0.427803;0.114692;,
    0.423960;0.160308;,
    0.406704;0.190098;,
    0.393153;0.165928;,
    0.385606;0.114692;,
    0.393153;0.063456;,
    0.406704;0.039286;,
    0.538059;0.060896;,
    0.547234;0.114692;,
    0.538059;0.168487;,
    0.496860;0.203129;,
    0.464507;0.174969;,
    0.446487;0.114692;,
    0.464507;0.054414;,
    0.496860;0.026254;,
    0.313715;0.082230;,
    0.311610;0.114692;,
    0.313715;0.147153;,
    0.317496;0.162619;,
    0.322309;0.143520;,
    0.323382;0.114692;,
    0.322309;0.085863;,
    0.317496;0.066764;,
    0.598634;0.144116;,
    0.623213;0.157752;,
    0.654512;0.141004;,
    0.661483;0.114692;,
    0.654512;0.088379;,
    0.623213;0.071631;,
    0.598634;0.085267;,
    0.584944;0.114692;,
    0.237396;0.129930;,
    0.237396;0.124956;,
    0.237396;0.114692;,
    0.237396;0.104428;,
    0.237396;0.099453;,
    0.237396;0.105616;,
    0.237396;0.114692;,
    0.237396;0.123767;;
   }
   MeshMaterialList
   {
    1;
    112;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
    58;
    58;
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
    54,
    55,
    56,
    57;
   }
  }
 }
}

# Animations definition.

