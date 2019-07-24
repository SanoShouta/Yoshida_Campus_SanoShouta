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
   132;
   0.000000;-0.890160;-1.370197;,
   3.587900;-0.592707;-1.921397;,
   0.000000;0.302101;-0.992137;,
   3.587906;0.527447;-1.631754;,
   0.000000;0.576199;0.884350;,
   3.587906;0.527447;1.523967;,
   0.000000;-0.890160;0.932349;,
   3.587900;-0.592707;1.813610;,
   0.000000;0.669789;-0.596919;,
   3.587906;0.527447;-0.975463;,
   3.587900;-0.592707;-1.087221;,
   0.000000;-0.890160;-0.327914;,
   0.000000;-0.890160;0.513642;,
   3.587900;-0.592707;0.892187;,
   3.587906;0.527447;0.892187;,
   0.000000;0.669789;0.513642;,
   1.720302;-0.925156;-1.692351;,
   1.173449;-2.005061;-1.692351;,
   1.173449;-2.005061;-0.873122;,
   1.720302;-0.848489;-0.591927;,
   1.720302;-0.812230;0.777655;,
   1.720302;-0.925156;1.380601;,
   1.720304;0.712765;1.330446;,
   1.720304;0.902702;0.777655;,
   1.720304;0.902702;-0.860931;,
   1.720304;0.676357;-1.438233;,
   2.960298;-2.668177;-1.261397;,
   2.976779;-1.949649;-1.261397;,
   2.976779;-1.949649;-1.802451;,
   2.960298;-2.668177;-1.802451;,
   0.000000;-0.183844;-1.280563;,
   1.720303;-0.049087;-1.863794;,
   3.587903;0.037089;-2.022490;,
   3.587903;0.037089;1.769834;,
   1.720303;-0.060372;1.610341;,
   0.000000;-0.183844;1.172777;,
   0.000000;0.000000;0.571745;,
   0.000000;0.000000;-0.506445;,
   3.587903;0.037089;-1.030403;,
   3.587903;0.037089;0.883085;,
   0.000000;0.669789;-0.055654;,
   1.720304;0.902702;-0.055654;,
   3.587906;0.527447;-0.055654;,
   3.587903;0.037089;-0.079643;,
   3.587900;-0.592707;-0.097517;,
   1.720302;-0.785954;0.045111;,
   0.000000;-0.750958;0.045111;,
   0.000000;0.000000;-0.000000;,
   5.796158;-1.890607;0.242950;,
   5.424238;-1.984404;0.068157;,
   5.424238;-1.984404;0.851427;,
   5.796158;-1.890607;0.687497;,
   4.955861;-2.020456;0.223316;,
   4.955861;-2.020456;0.687497;,
   5.486775;-1.690477;-2.126946;,
   5.486775;-1.690477;-1.380828;,
   5.801525;-1.506789;-1.490477;,
   5.801525;-1.506789;-1.897520;,
   5.087859;-1.847943;-2.025853;,
   5.087859;-1.847943;-1.602235;,
   4.591479;-1.752852;1.292156;,
   5.032466;-1.771165;1.127081;,
   4.591479;-1.752852;1.820136;,
   5.032466;-1.771165;1.957006;,
   5.407211;-1.676272;1.290425;,
   5.407211;-1.676272;1.851252;,
   5.854429;-1.777468;-0.831196;,
   5.479682;-1.872360;-1.014427;,
   5.479682;-1.872360;-0.190760;,
   5.854429;-1.777468;-0.348126;,
   5.008479;-1.909507;-0.889890;,
   5.008479;-1.909507;-0.370112;,
   2.000881;-2.496801;-1.032528;,
   2.286363;-1.628183;-0.891930;,
   2.286363;-1.628183;-1.782134;,
   2.000881;-2.496801;-1.782134;,
   4.567930;-0.605256;-2.074718;,
   4.393784;-1.045278;-1.973625;,
   4.393784;-1.045278;-1.344728;,
   4.567930;-0.605256;-1.205615;,
   4.698065;-0.232533;-1.232970;,
   4.698065;-0.232533;-1.764637;,
   4.756814;-0.357293;-0.903330;,
   4.586733;-0.694303;-1.022415;,
   4.362826;-1.084832;-0.988555;,
   4.362826;-1.084832;-0.233815;,
   4.586733;-0.694303;-0.135202;,
   4.756814;-0.357293;-0.201890;,
   4.742398;-0.419271;0.093648;,
   4.573554;-0.755404;-0.005743;,
   4.350884;-1.145056;0.062899;,
   4.350884;-1.145056;0.789842;,
   4.573554;-0.755404;0.867256;,
   4.742398;-0.419271;0.789842;,
   4.141502;-1.059876;1.092172;,
   4.141502;-1.059876;1.816873;,
   4.357541;-0.699930;1.863420;,
   4.527620;-0.362920;1.687610;,
   4.527620;-0.362920;1.091306;,
   4.357541;-0.699930;1.005083;,
   0.000000;0.669789;0.513642;,
   0.000000;0.576199;0.884350;,
   0.000000;0.669789;-0.055654;,
   0.000000;0.302101;-0.992137;,
   0.000000;-0.183844;-1.280563;,
   2.960298;-2.668177;-1.261397;,
   2.976779;-1.949649;-1.802451;,
   2.976779;-1.949649;-1.261397;,
   2.960298;-2.668177;-1.802451;,
   2.976779;-1.949649;-1.802451;,
   2.960298;-2.668177;-1.802451;,
   0.000000;-0.183844;1.172777;,
   0.000000;-0.890160;0.513642;,
   0.000000;0.669789;-0.055654;,
   0.000000;-0.750958;0.045111;,
   0.000000;0.669789;-0.596919;,
   5.796158;-1.890607;0.242950;,
   5.796158;-1.890607;0.687497;,
   4.955861;-2.020456;0.687497;,
   4.955861;-2.020456;0.223316;,
   5.801525;-1.506789;-1.897520;,
   5.801525;-1.506789;-1.490477;,
   5.087859;-1.847943;-1.602235;,
   5.087859;-1.847943;-2.025853;,
   4.591479;-1.752852;1.820136;,
   4.591479;-1.752852;1.292156;,
   5.407211;-1.676272;1.290425;,
   5.407211;-1.676272;1.851252;,
   5.854429;-1.777468;-0.831196;,
   5.854429;-1.777468;-0.348126;,
   5.008479;-1.909507;-0.370112;,
   5.008479;-1.909507;-0.889890;;
   196;
   3;3,32,31;,
   3;25,3,31;,
   3;14,42,41;,
   3;23,14,41;,
   3;33,5,22;,
   3;34,33,22;,
   3;44,13,20;,
   3;45,44,20;,
   3;47,36,15;,
   3;40,47,15;,
   3;24,9,3;,
   3;25,24,3;,
   3;16,1,10;,
   3;19,16,10;,
   3;30,37,8;,
   3;2,30,8;,
   3;20,13,7;,
   3;21,20,7;,
   3;22,5,14;,
   3;23,22,14;,
   3;100,36,35;,
   3;4,100,35;,
   3;11,0,17;,
   3;18,11,17;,
   3;0,16,17;,
   3;18,19,11;,
   3;12,46,45;,
   3;20,12,45;,
   3;20,21,6;,
   3;12,20,6;,
   3;34,22,101;,
   3;35,34,101;,
   3;22,23,15;,
   3;4,22,15;,
   3;102,15,23;,
   3;41,102,23;,
   3;24,25,103;,
   3;8,24,103;,
   3;25,31,104;,
   3;103,25,104;,
   3;28,27,26;,
   3;29,28,26;,
   3;27,73,72;,
   3;105,27,72;,
   3;106,74,73;,
   3;107,106,73;,
   3;108,75,74;,
   3;109,108,74;,
   3;105,72,75;,
   3;110,105,75;,
   3;31,16,0;,
   3;104,31,0;,
   3;32,1,16;,
   3;31,32,16;,
   3;21,7,33;,
   3;34,21,33;,
   3;21,34,35;,
   3;6,21,35;,
   3;36,12,6;,
   3;111,36,6;,
   3;36,47,46;,
   3;112,36,46;,
   3;11,37,104;,
   3;0,11,104;,
   3;50,49,48;,
   3;51,50,48;,
   3;53,52,49;,
   3;50,53,49;,
   3;56,55,54;,
   3;57,56,54;,
   3;59,58,54;,
   3;55,59,54;,
   3;62,60,61;,
   3;63,62,61;,
   3;63,61,64;,
   3;65,63,64;,
   3;8,113,41;,
   3;24,8,41;,
   3;42,9,24;,
   3;41,42,24;,
   3;68,67,66;,
   3;69,68,66;,
   3;71,70,67;,
   3;68,71,67;,
   3;19,10,44;,
   3;45,19,44;,
   3;45,46,11;,
   3;19,45,11;,
   3;114,47,37;,
   3;11,114,37;,
   3;37,47,40;,
   3;115,37,40;,
   3;49,89,88;,
   3;116,49,88;,
   3;51,93,92;,
   3;50,51,92;,
   3;116,88,93;,
   3;117,116,93;,
   3;52,90,89;,
   3;49,52,89;,
   3;118,91,90;,
   3;119,118,90;,
   3;50,92,91;,
   3;118,50,91;,
   3;56,80,79;,
   3;55,56,79;,
   3;120,81,80;,
   3;121,120,80;,
   3;54,76,81;,
   3;120,54,81;,
   3;58,77,76;,
   3;54,58,76;,
   3;122,78,77;,
   3;123,122,77;,
   3;55,79,78;,
   3;122,55,78;,
   3;60,94,99;,
   3;61,60,99;,
   3;124,95,94;,
   3;125,124,94;,
   3;63,96,95;,
   3;124,63,95;,
   3;61,99,98;,
   3;126,61,98;,
   3;65,97,96;,
   3;63,65,96;,
   3;126,98,97;,
   3;127,126,97;,
   3;67,83,82;,
   3;128,67,82;,
   3;69,87,86;,
   3;68,69,86;,
   3;128,82,87;,
   3;129,128,87;,
   3;70,84,83;,
   3;67,70,83;,
   3;130,85,84;,
   3;131,130,84;,
   3;68,86,85;,
   3;130,68,85;,
   3;73,19,18;,
   3;72,73,18;,
   3;74,16,19;,
   3;73,74,19;,
   3;75,17,16;,
   3;74,75,16;,
   3;72,18,17;,
   3;75,72,17;,
   3;77,1,32;,
   3;76,77,32;,
   3;78,10,1;,
   3;77,78,1;,
   3;79,38,10;,
   3;78,79,10;,
   3;80,9,38;,
   3;79,80,38;,
   3;81,3,9;,
   3;80,81,9;,
   3;76,32,3;,
   3;81,76,3;,
   3;83,38,9;,
   3;82,83,9;,
   3;84,10,38;,
   3;83,84,38;,
   3;85,44,10;,
   3;84,85,10;,
   3;86,43,44;,
   3;85,86,44;,
   3;87,42,43;,
   3;86,87,43;,
   3;82,9,42;,
   3;87,82,42;,
   3;89,43,42;,
   3;88,89,42;,
   3;90,44,43;,
   3;89,90,43;,
   3;91,13,44;,
   3;90,91,44;,
   3;92,39,13;,
   3;91,92,13;,
   3;93,14,39;,
   3;92,93,39;,
   3;88,42,14;,
   3;93,88,14;,
   3;95,7,13;,
   3;94,95,13;,
   3;96,33,7;,
   3;95,96,7;,
   3;97,5,33;,
   3;96,97,33;,
   3;98,14,5;,
   3;97,98,5;,
   3;99,39,14;,
   3;98,99,14;,
   3;94,13,39;,
   3;99,94,39;;
   MeshNormals
   {
    132;
    -0.719493;-0.225818;-0.656762;,
    -0.189712;-0.738190;-0.647368;,
    -1.000000;0.000000;-0.000000;,
    0.261102;0.826810;-0.498208;,
    -0.760684;0.622201;0.184999;,
    0.299331;0.749410;0.590581;,
    -0.616881;-0.657906;0.431993;,
    -0.255992;-0.675935;0.691072;,
    -0.591360;0.775321;-0.221745;,
    0.439594;0.897193;-0.042458;,
    -0.140387;-0.989997;0.014069;,
    -0.737276;-0.583488;0.340537;,
    -0.428485;-0.896214;-0.114898;,
    -0.208754;-0.977655;-0.024763;,
    0.485977;0.872825;0.044752;,
    -0.550616;0.826088;0.119999;,
    0.084903;-0.115377;-0.989687;,
    -0.516566;-0.507722;-0.689476;,
    -0.316531;-0.704975;0.634680;,
    0.346684;-0.745743;0.568926;,
    0.081894;-0.992491;-0.090862;,
    -0.063804;-0.804069;0.591103;,
    -0.100695;0.756635;0.646037;,
    0.010368;0.993516;0.113217;,
    -0.016858;0.982836;-0.183710;,
    -0.138618;0.764004;-0.630145;,
    0.999737;-0.022931;-0.000000;,
    0.804368;-0.098182;0.585963;,
    0.999737;-0.022931;-0.000000;,
    0.999737;-0.022931;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -0.194757;0.222844;-0.955202;,
    0.001297;0.220546;-0.975376;,
    -0.012602;0.178428;0.983872;,
    -0.188491;0.092213;0.977736;,
    -0.630324;0.022943;0.775993;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    0.985239;-0.168300;-0.031284;,
    0.985842;-0.153115;0.068353;,
    -1.000000;0.000000;-0.000000;,
    0.031853;0.999493;-0.000000;,
    0.465548;0.885015;0.003583;,
    0.988577;-0.148524;0.025599;,
    -0.198287;-0.980120;0.006794;,
    0.065021;-0.997597;0.023939;,
    -0.444727;-0.895191;0.029179;,
    -1.000000;0.000000;-0.000000;,
    0.244539;-0.969639;-0.000000;,
    0.181333;-0.717965;-0.672045;,
    0.140683;-0.721160;0.678334;,
    0.397589;-0.595768;0.697842;,
    -0.042132;-0.782151;-0.621663;,
    0.076744;-0.997051;-0.000000;,
    0.427148;-0.583928;-0.690343;,
    0.311217;-0.714479;0.626629;,
    0.511706;-0.557209;0.653969;,
    0.504042;-0.863679;-0.000000;,
    0.107457;-0.732881;-0.671817;,
    0.367165;-0.930156;-0.000000;,
    -0.123196;-0.801298;-0.585443;,
    0.134336;-0.748084;-0.649864;,
    -0.041490;-0.999139;-0.000000;,
    0.086095;-0.688016;0.720570;,
    0.245472;-0.969404;-0.000000;,
    0.398047;-0.553459;0.731602;,
    0.245469;-0.969404;-0.000000;,
    0.197058;-0.690611;-0.695862;,
    0.132664;-0.737380;0.662322;,
    0.386685;-0.605559;0.695538;,
    -0.019257;-0.757419;-0.652646;,
    0.078590;-0.996907;-0.000000;,
    -0.099730;-0.753075;0.650332;,
    0.588393;0.418980;0.691556;,
    0.394142;0.562124;-0.727096;,
    -0.288203;-0.641820;-0.710638;,
    0.105666;0.198871;-0.974313;,
    -0.518796;-0.582873;-0.625387;,
    -0.424190;-0.678640;0.599592;,
    0.087416;-0.155885;0.983900;,
    0.580345;0.489788;0.650621;,
    0.577003;0.692229;-0.433458;,
    0.583502;0.559055;-0.589052;,
    0.113822;0.065449;-0.991343;,
    -0.471605;-0.552598;-0.687186;,
    -0.494739;-0.606437;0.622469;,
    0.049607;-0.060285;0.996948;,
    0.581446;0.515348;0.629553;,
    0.617305;0.508969;-0.599904;,
    0.119218;-0.004184;-0.992859;,
    -0.494514;-0.561310;-0.663616;,
    -0.532734;-0.552646;0.640918;,
    0.048676;-0.017291;0.998665;,
    0.593600;0.510991;0.621713;,
    -0.501587;-0.575259;-0.646133;,
    -0.593153;-0.472369;0.651949;,
    0.052923;0.143504;0.988234;,
    0.605633;0.581963;0.542704;,
    0.659349;0.452941;-0.600086;,
    0.145136;-0.064482;-0.987308;,
    -1.000000;0.000000;-0.000000;,
    -0.258021;0.335848;0.905887;,
    -0.134166;0.990959;-0.000000;,
    -0.288874;0.668322;-0.685491;,
    -0.650963;0.184578;-0.736327;,
    0.082780;-0.761605;0.642732;,
    0.422100;0.906549;-0.000000;,
    0.422100;0.906549;-0.000000;,
    -0.024552;0.003620;-0.999692;,
    -0.024552;0.003620;-0.999692;,
    -0.175842;-0.984418;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -0.134166;0.990959;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    0.693590;0.449461;-0.562954;,
    0.813000;0.582264;-0.000000;,
    -0.646474;-0.483832;0.589896;,
    -0.822662;-0.568531;-0.000000;,
    0.662049;0.605064;-0.442253;,
    0.755952;0.654627;-0.000000;,
    -0.569100;-0.618848;0.541436;,
    -0.756420;-0.654086;-0.000000;,
    -0.678513;-0.410848;0.608953;,
    -0.838697;-0.544599;-0.000000;,
    0.716433;0.400378;-0.571333;,
    0.830874;0.556461;-0.000000;,
    0.667909;0.499445;-0.551772;,
    0.791229;0.611520;-0.000000;,
    -0.618740;-0.541836;0.568836;,
    -0.787387;-0.616459;-0.000000;;
    196;
    3;3,32,31;,
    3;25,3,31;,
    3;14,42,41;,
    3;23,14,41;,
    3;33,5,22;,
    3;34,33,22;,
    3;44,13,20;,
    3;45,44,20;,
    3;47,36,15;,
    3;40,47,15;,
    3;24,9,3;,
    3;25,24,3;,
    3;16,1,10;,
    3;19,16,10;,
    3;30,37,8;,
    3;2,30,8;,
    3;20,13,7;,
    3;21,20,7;,
    3;22,5,14;,
    3;23,22,14;,
    3;100,36,35;,
    3;4,100,35;,
    3;11,0,17;,
    3;18,11,17;,
    3;0,16,17;,
    3;18,19,11;,
    3;12,46,45;,
    3;20,12,45;,
    3;20,21,6;,
    3;12,20,6;,
    3;34,22,101;,
    3;35,34,101;,
    3;22,23,15;,
    3;4,22,15;,
    3;102,15,23;,
    3;41,102,23;,
    3;24,25,103;,
    3;8,24,103;,
    3;25,31,104;,
    3;103,25,104;,
    3;28,27,26;,
    3;29,28,26;,
    3;27,73,72;,
    3;105,27,72;,
    3;106,74,73;,
    3;107,106,73;,
    3;108,75,74;,
    3;109,108,74;,
    3;105,72,75;,
    3;110,105,75;,
    3;31,16,0;,
    3;104,31,0;,
    3;32,1,16;,
    3;31,32,16;,
    3;21,7,33;,
    3;34,21,33;,
    3;21,34,35;,
    3;6,21,35;,
    3;36,12,6;,
    3;111,36,6;,
    3;36,47,46;,
    3;112,36,46;,
    3;11,37,104;,
    3;0,11,104;,
    3;50,49,48;,
    3;51,50,48;,
    3;53,52,49;,
    3;50,53,49;,
    3;56,55,54;,
    3;57,56,54;,
    3;59,58,54;,
    3;55,59,54;,
    3;62,60,61;,
    3;63,62,61;,
    3;63,61,64;,
    3;65,63,64;,
    3;8,113,41;,
    3;24,8,41;,
    3;42,9,24;,
    3;41,42,24;,
    3;68,67,66;,
    3;69,68,66;,
    3;71,70,67;,
    3;68,71,67;,
    3;19,10,44;,
    3;45,19,44;,
    3;45,46,11;,
    3;19,45,11;,
    3;114,47,37;,
    3;11,114,37;,
    3;37,47,40;,
    3;115,37,40;,
    3;49,89,88;,
    3;116,49,88;,
    3;51,93,92;,
    3;50,51,92;,
    3;116,88,93;,
    3;117,116,93;,
    3;52,90,89;,
    3;49,52,89;,
    3;118,91,90;,
    3;119,118,90;,
    3;50,92,91;,
    3;118,50,91;,
    3;56,80,79;,
    3;55,56,79;,
    3;120,81,80;,
    3;121,120,80;,
    3;54,76,81;,
    3;120,54,81;,
    3;58,77,76;,
    3;54,58,76;,
    3;122,78,77;,
    3;123,122,77;,
    3;55,79,78;,
    3;122,55,78;,
    3;60,94,99;,
    3;61,60,99;,
    3;124,95,94;,
    3;125,124,94;,
    3;63,96,95;,
    3;124,63,95;,
    3;61,99,98;,
    3;126,61,98;,
    3;65,97,96;,
    3;63,65,96;,
    3;126,98,97;,
    3;127,126,97;,
    3;67,83,82;,
    3;128,67,82;,
    3;69,87,86;,
    3;68,69,86;,
    3;128,82,87;,
    3;129,128,87;,
    3;70,84,83;,
    3;67,70,83;,
    3;130,85,84;,
    3;131,130,84;,
    3;68,86,85;,
    3;130,68,85;,
    3;73,19,18;,
    3;72,73,18;,
    3;74,16,19;,
    3;73,74,19;,
    3;75,17,16;,
    3;74,75,16;,
    3;72,18,17;,
    3;75,72,17;,
    3;77,1,32;,
    3;76,77,32;,
    3;78,10,1;,
    3;77,78,1;,
    3;79,38,10;,
    3;78,79,10;,
    3;80,9,38;,
    3;79,80,38;,
    3;81,3,9;,
    3;80,81,9;,
    3;76,32,3;,
    3;81,76,3;,
    3;83,38,9;,
    3;82,83,9;,
    3;84,10,38;,
    3;83,84,38;,
    3;85,44,10;,
    3;84,85,10;,
    3;86,43,44;,
    3;85,86,44;,
    3;87,42,43;,
    3;86,87,43;,
    3;82,9,42;,
    3;87,82,42;,
    3;89,43,42;,
    3;88,89,42;,
    3;90,44,43;,
    3;89,90,43;,
    3;91,13,44;,
    3;90,91,44;,
    3;92,39,13;,
    3;91,92,13;,
    3;93,14,39;,
    3;92,93,39;,
    3;88,42,14;,
    3;93,88,14;,
    3;95,7,13;,
    3;94,95,13;,
    3;96,33,7;,
    3;95,96,7;,
    3;97,5,33;,
    3;96,97,33;,
    3;98,14,5;,
    3;97,98,5;,
    3;99,39,14;,
    3;98,99,14;,
    3;94,13,39;,
    3;99,94,39;;
   }
   MeshTextureCoords
   {
    132;
    0.137290;0.665330;,
    0.118599;0.682469;,
    0.150111;0.636915;,
    0.128421;0.672743;,
    0.213745;0.636915;,
    0.235435;0.672743;,
    0.219585;0.665330;,
    0.245257;0.682469;,
    0.163513;0.629519;,
    0.150676;0.672743;,
    0.146887;0.682469;,
    0.172636;0.665330;,
    0.201174;0.665330;,
    0.214011;0.682469;,
    0.214011;0.672743;,
    0.201174;0.629519;,
    0.126366;0.666034;,
    0.126366;0.706822;,
    0.154147;0.706822;,
    0.163683;0.666034;,
    0.210127;0.666034;,
    0.237490;0.666034;,
    0.228873;0.636663;,
    0.210127;0.629267;,
    0.154560;0.629267;,
    0.134983;0.636663;,
    0.143336;0.714641;,
    0.143336;0.695545;,
    0.120277;0.695545;,
    0.120277;0.714641;,
    0.140330;0.651123;,
    0.120552;0.651349;,
    0.111972;0.677269;,
    0.248712;0.677269;,
    0.243304;0.651349;,
    0.223526;0.651123;,
    0.203144;0.647425;,
    0.166581;0.647425;,
    0.148813;0.677269;,
    0.213702;0.677269;,
    0.181868;0.629519;,
    0.181868;0.629267;,
    0.181868;0.672743;,
    0.181055;0.677269;,
    0.180449;0.682469;,
    0.185285;0.666034;,
    0.185285;0.665330;,
    0.183756;0.647425;,
    0.191994;0.726098;,
    0.183024;0.717628;,
    0.215671;0.717628;,
    0.207069;0.726098;,
    0.191328;0.705779;,
    0.207069;0.705779;,
    0.108430;0.715051;,
    0.140813;0.715051;,
    0.133212;0.720719;,
    0.119408;0.720719;,
    0.115056;0.706783;,
    0.129422;0.706783;,
    0.227574;0.708524;,
    0.221976;0.720431;,
    0.245478;0.708524;,
    0.250120;0.720431;,
    0.227515;0.728960;,
    0.246534;0.728960;,
    0.155569;0.726009;,
    0.147200;0.717480;,
    0.179442;0.717480;,
    0.171950;0.726009;,
    0.153578;0.705573;,
    0.171205;0.705573;,
    0.148741;0.710731;,
    0.153509;0.680790;,
    0.123321;0.680790;,
    0.123321;0.710731;,
    0.110201;0.696160;,
    0.116828;0.694626;,
    0.138154;0.694626;,
    0.144813;0.696160;,
    0.141944;0.696731;,
    0.123915;0.696731;,
    0.153123;0.699376;,
    0.148007;0.697374;,
    0.150232;0.694021;,
    0.175827;0.694021;,
    0.180248;0.697374;,
    0.176909;0.699376;,
    0.186931;0.699421;,
    0.182039;0.697448;,
    0.185888;0.694124;,
    0.210540;0.694124;,
    0.214687;0.697448;,
    0.210540;0.699421;,
    0.220792;0.695496;,
    0.245368;0.695496;,
    0.249416;0.698850;,
    0.240984;0.700852;,
    0.220763;0.700852;,
    0.217839;0.698850;,
    0.201174;0.629519;,
    0.213745;0.636915;,
    0.181868;0.629519;,
    0.150111;0.636915;,
    0.140330;0.651123;,
    0.143336;0.714641;,
    0.120277;0.695545;,
    0.143336;0.695545;,
    0.120277;0.714641;,
    0.120277;0.695545;,
    0.120277;0.714641;,
    0.223526;0.651123;,
    0.201174;0.665330;,
    0.181868;0.629519;,
    0.185285;0.665330;,
    0.163513;0.629519;,
    0.191994;0.726098;,
    0.207069;0.726098;,
    0.207069;0.705779;,
    0.191328;0.705779;,
    0.119408;0.720719;,
    0.133212;0.720719;,
    0.129422;0.706783;,
    0.115056;0.706783;,
    0.245478;0.708524;,
    0.227574;0.708524;,
    0.227515;0.728960;,
    0.246534;0.728960;,
    0.155569;0.726009;,
    0.171950;0.726009;,
    0.171205;0.705573;,
    0.153578;0.705573;;
   }
   MeshMaterialList
   {
    1;
    196;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
    132;
    100;
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
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94,
    95,
    96,
    97,
    98,
    99,
    15,
    4,
    40,
    2,
    30,
    26,
    28,
    27,
    29,
    28,
    29,
    35,
    12,
    40,
    46,
    8,
    48,
    51,
    53,
    52,
    57,
    56,
    59,
    58,
    62,
    60,
    64,
    65,
    66,
    69,
    71,
    70;
   }
  }
 }
}

# Animations definition.

