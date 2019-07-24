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
  "data/TEXTURE/�鐝_lambert3SG_BaseColor.png";
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
   149;
   -4.823303;-75.434944;42.066624;,
   -5.121185;-75.604889;41.196964;,
   -6.347780;-75.650322;41.233288;,
   -5.792578;-75.328758;42.812107;,
   -4.299168;-74.706009;42.126400;,
   -4.448529;-75.130836;41.376949;,
   -4.872533;-73.926155;42.996243;,
   -2.318586;4.128951;-3.752122;,
   -3.127296;1.178912;-3.310095;,
   -0.739818;0.423253;-5.143262;,
   -0.121241;4.560520;-5.010812;,
   -2.592803;5.650486;-1.735391;,
   -4.195224;2.268070;-0.404561;,
   0.365500;7.651973;-3.014419;,
   5.140661;6.431502;-2.134334;,
   3.213315;7.843080;-3.115225;,
   2.883540;4.961167;-5.022529;,
   5.160729;3.855398;-3.206263;,
   4.871305;6.356924;0.360328;,
   2.260947;8.744620;-0.082758;,
   5.329106;3.686116;-0.301519;,
   -6.920083;-74.369743;42.820835;,
   -6.223340;-73.440300;43.053284;,
   -7.319582;-74.751915;41.737026;,
   -7.212049;-73.605316;42.283260;,
   -4.040158;-74.344032;41.678646;,
   -4.311419;-74.895546;40.995338;,
   -5.000556;-75.348793;40.597385;,
   0.019666;8.191294;-0.812325;,
   -1.842821;6.595378;0.779362;,
   0.883516;7.396610;2.631389;,
   -7.282825;-73.163918;41.909191;,
   -7.513520;-73.780998;41.533115;,
   -7.610279;-73.538902;40.883297;,
   -7.276908;-72.759766;41.619637;,
   -6.763965;-72.966148;42.462872;,
   -6.419816;-72.326874;42.305630;,
   4.619897;3.534759;1.688042;,
   5.230027;0.611431;-0.460345;,
   4.170761;1.416902;2.484833;,
   3.680633;5.425852;2.719153;,
   1.971730;2.573523;4.488296;,
   -1.118400;3.287092;4.605579;,
   0.984077;-3.910785;6.944508;,
   -2.212953;-3.515590;7.052072;,
   3.489010;-5.082246;4.632471;,
   3.085929;-12.191523;7.616319;,
   0.620924;-10.987510;9.998027;,
   4.721947;-6.237391;1.516057;,
   4.270054;-13.574996;4.551299;,
   4.212585;-7.181130;-1.630091;,
   3.774640;-14.874845;1.455175;,
   4.716023;0.159997;-3.433967;,
   2.192502;0.116552;-5.353429;,
   1.550264;-7.527215;-3.566920;,
   -1.604516;-7.115425;-3.269661;,
   -2.220559;-15.143043;-0.068812;,
   1.012599;-15.509905;-0.408362;,
   -4.342900;-6.146553;-1.111724;,
   -4.951545;-14.036334;2.035286;,
   -5.479911;-5.012642;1.812727;,
   -6.098273;-12.723291;4.880490;,
   -4.762466;-4.015877;4.926765;,
   -5.312383;-11.435913;7.987211;,
   -3.510947;3.091556;2.576154;,
   -2.604635;-10.688913;10.188930;,
   0.018188;-25.142214;16.746012;,
   -3.205885;-24.876577;16.964125;,
   2.334683;-26.286039;14.555255;,
   3.440424;-27.826990;11.675193;,
   2.810863;-29.304441;8.751002;,
   0.102267;-30.002274;6.953507;,
   -3.025676;-29.598303;7.126071;,
   -5.771877;-28.434067;9.105196;,
   -6.890932;-27.050816;11.929629;,
   -5.926517;-25.645102;14.978665;,
   -3.778618;-38.506504;23.624210;,
   -6.165248;-39.329937;21.928087;,
   -0.801092;-38.645473;23.482553;,
   1.468288;-39.632027;21.637274;,
   2.462284;-41.171829;18.952225;,
   1.509065;-42.545864;16.440372;,
   -0.930378;-43.278591;14.808871;,
   -3.886996;-43.049923;14.794634;,
   -6.221013;-42.077435;16.423994;,
   -7.140217;-40.701023;19.167479;,
   -6.290741;-52.048737;28.745230;,
   -7.144870;-53.259502;26.336399;,
   -4.191842;-51.293270;30.432886;,
   -1.343395;-51.457394;30.429213;,
   0.748099;-52.452175;28.802107;,
   1.406389;-53.812679;26.412184;,
   0.424866;-54.977833;24.078831;,
   -1.691133;-55.661121;22.481789;,
   -4.496696;-55.581512;22.234426;,
   -6.647981;-54.583858;23.849401;,
   -7.468524;-65.255852;32.715237;,
   -7.310706;-66.486343;30.793936;,
   -6.793749;-64.111870;34.589199;,
   -5.066050;-63.268806;36.211372;,
   -2.549492;-63.470161;36.440159;,
   -0.889398;-64.698540;34.919613;,
   -0.607357;-66.022423;32.913708;,
   -1.274526;-67.086342;31.013916;,
   -2.968422;-67.772675;29.526264;,
   -5.574556;-67.636314;29.260084;,
   -7.809080;-73.520393;38.003601;,
   -6.115807;-74.453384;37.126095;,
   -8.047379;-71.967957;39.292667;,
   -7.082548;-70.302254;40.168476;,
   -5.628213;-69.388374;40.518520;,
   -3.998752;-69.362358;40.349094;,
   -2.853920;-70.126884;39.535934;,
   -2.576536;-71.173820;38.713791;,
   -2.902087;-72.545341;38.102245;,
   -4.077552;-73.925919;37.329655;,
   -4.455919;-74.497917;38.921482;,
   -3.559536;-73.721619;39.517868;,
   -5.904757;-74.843277;38.777233;,
   -6.020106;-75.180519;39.754555;,
   -4.774503;-74.979912;39.906116;,
   -7.342817;-74.190826;39.328773;,
   -7.258953;-74.546745;40.169830;,
   -7.739151;-72.964996;40.257763;,
   -7.246060;-71.971588;41.211926;,
   -6.079691;-71.253868;41.768063;,
   -4.557537;-71.229591;41.790264;,
   -5.078516;-72.396118;42.574173;,
   -3.439122;-71.914635;41.071175;,
   -3.946999;-73.073624;41.998840;,
   -3.204407;-72.792969;40.205399;,
   -3.711224;-73.844917;41.110847;,
   -4.041210;-74.457420;40.390472;,
   -4.397617;-73.604218;42.544872;,
   -5.614906;-72.989044;42.911926;,
   -7.276486;-74.773979;40.922909;,
   -6.166937;-75.463867;40.512878;,
   -3.127296;1.178912;-3.310095;,
   -7.319582;-74.751915;41.737026;,
   -4.342900;-6.146553;-1.111724;,
   -4.951545;-14.036334;2.035286;,
   -5.771877;-28.434067;9.105196;,
   -6.221013;-42.077435;16.423994;,
   -6.647981;-54.583858;23.849401;,
   -7.310706;-66.486343;30.793936;,
   -7.809080;-73.520393;38.003601;,
   -7.342817;-74.190826;39.328773;,
   -7.258953;-74.546745;40.169830;,
   -7.276486;-74.773979;40.922909;;
   270;
   3;2,1,0;,
   3;3,2,0;,
   3;5,4,0;,
   3;1,5,0;,
   3;6,3,0;,
   3;4,6,0;,
   3;9,8,7;,
   3;10,9,7;,
   3;12,11,7;,
   3;137,12,7;,
   3;13,10,7;,
   3;11,13,7;,
   3;16,15,14;,
   3;17,16,14;,
   3;19,18,14;,
   3;15,19,14;,
   3;20,17,14;,
   3;18,20,14;,
   3;6,22,21;,
   3;3,6,21;,
   3;2,3,21;,
   3;23,2,21;,
   3;24,138,21;,
   3;22,24,21;,
   3;25,4,5;,
   3;26,25,5;,
   3;27,26,5;,
   3;1,27,5;,
   3;11,29,28;,
   3;13,11,28;,
   3;15,13,28;,
   3;19,15,28;,
   3;30,19,28;,
   3;29,30,28;,
   3;33,32,31;,
   3;34,33,31;,
   3;24,35,31;,
   3;32,24,31;,
   3;36,34,31;,
   3;35,36,31;,
   3;38,20,37;,
   3;39,38,37;,
   3;18,40,37;,
   3;20,18,37;,
   3;41,39,37;,
   3;40,41,37;,
   3;30,42,41;,
   3;40,30,41;,
   3;44,43,41;,
   3;42,44,41;,
   3;45,39,41;,
   3;43,45,41;,
   3;47,46,45;,
   3;43,47,45;,
   3;49,48,45;,
   3;46,49,45;,
   3;38,39,45;,
   3;48,38,45;,
   3;51,50,48;,
   3;49,51,48;,
   3;52,38,48;,
   3;50,52,48;,
   3;20,38,52;,
   3;17,20,52;,
   3;54,53,52;,
   3;50,54,52;,
   3;16,17,52;,
   3;53,16,52;,
   3;55,9,53;,
   3;54,55,53;,
   3;10,16,53;,
   3;9,10,53;,
   3;57,56,55;,
   3;54,57,55;,
   3;59,58,55;,
   3;56,59,55;,
   3;8,9,55;,
   3;58,8,55;,
   3;61,60,139;,
   3;140,61,139;,
   3;12,137,139;,
   3;60,12,139;,
   3;63,62,60;,
   3;61,63,60;,
   3;64,12,60;,
   3;62,64,60;,
   3;11,12,64;,
   3;29,11,64;,
   3;44,42,64;,
   3;62,44,64;,
   3;30,29,64;,
   3;42,30,64;,
   3;65,44,62;,
   3;63,65,62;,
   3;67,65,63;,
   3;75,67,63;,
   3;66,47,65;,
   3;67,66,65;,
   3;43,44,65;,
   3;47,43,65;,
   3;47,66,68;,
   3;46,47,68;,
   3;46,68,69;,
   3;49,46,69;,
   3;49,69,70;,
   3;51,49,70;,
   3;51,70,71;,
   3;57,51,71;,
   3;57,71,72;,
   3;56,57,72;,
   3;56,72,73;,
   3;59,56,73;,
   3;140,141,74;,
   3;61,140,74;,
   3;74,75,63;,
   3;61,74,63;,
   3;77,75,74;,
   3;85,77,74;,
   3;76,67,75;,
   3;77,76,75;,
   3;67,76,78;,
   3;66,67,78;,
   3;66,78,79;,
   3;68,66,79;,
   3;68,79,80;,
   3;69,68,80;,
   3;69,80,81;,
   3;70,69,81;,
   3;70,81,82;,
   3;71,70,82;,
   3;71,82,83;,
   3;72,71,83;,
   3;72,83,84;,
   3;73,72,84;,
   3;142,85,74;,
   3;141,142,74;,
   3;87,85,142;,
   3;95,87,142;,
   3;86,77,85;,
   3;87,86,85;,
   3;77,86,88;,
   3;76,77,88;,
   3;76,88,89;,
   3;78,76,89;,
   3;78,89,90;,
   3;79,78,90;,
   3;79,90,91;,
   3;80,79,91;,
   3;80,91,92;,
   3;81,80,92;,
   3;81,92,93;,
   3;82,81,93;,
   3;82,93,94;,
   3;83,82,94;,
   3;94,143,84;,
   3;83,94,84;,
   3;97,143,94;,
   3;105,97,94;,
   3;96,87,95;,
   3;144,96,95;,
   3;87,96,98;,
   3;86,87,98;,
   3;86,98,99;,
   3;88,86,99;,
   3;88,99,100;,
   3;89,88,100;,
   3;89,100,101;,
   3;90,89,101;,
   3;90,101,102;,
   3;91,90,102;,
   3;91,102,103;,
   3;92,91,103;,
   3;92,103,104;,
   3;93,92,104;,
   3;104,105,94;,
   3;93,104,94;,
   3;107,105,104;,
   3;115,107,104;,
   3;106,97,105;,
   3;107,106,105;,
   3;144,145,108;,
   3;96,144,108;,
   3;96,108,109;,
   3;98,96,109;,
   3;98,109,110;,
   3;99,98,110;,
   3;99,110,111;,
   3;100,99,111;,
   3;100,111,112;,
   3;101,100,112;,
   3;101,112,113;,
   3;102,101,113;,
   3;102,113,114;,
   3;103,102,114;,
   3;114,115,104;,
   3;103,114,104;,
   3;117,116,115;,
   3;114,117,115;,
   3;118,107,115;,
   3;116,118,115;,
   3;120,119,118;,
   3;116,120,118;,
   3;122,121,118;,
   3;119,122,118;,
   3;106,107,118;,
   3;121,106,118;,
   3;33,123,146;,
   3;147,33,146;,
   3;108,145,146;,
   3;123,108,146;,
   3;34,124,123;,
   3;33,34,123;,
   3;109,108,123;,
   3;124,109,123;,
   3;36,125,124;,
   3;34,36,124;,
   3;110,109,124;,
   3;125,110,124;,
   3;127,126,125;,
   3;36,127,125;,
   3;111,110,125;,
   3;126,111,125;,
   3;129,128,126;,
   3;127,129,126;,
   3;112,111,126;,
   3;128,112,126;,
   3;131,130,128;,
   3;129,131,128;,
   3;113,112,128;,
   3;130,113,128;,
   3;132,117,130;,
   3;131,132,130;,
   3;114,113,130;,
   3;117,114,130;,
   3;25,26,132;,
   3;131,25,132;,
   3;27,120,132;,
   3;26,27,132;,
   3;116,117,132;,
   3;120,116,132;,
   3;133,25,131;,
   3;129,133,131;,
   3;127,134,133;,
   3;129,127,133;,
   3;22,6,133;,
   3;134,22,133;,
   3;4,25,133;,
   3;6,4,133;,
   3;36,35,134;,
   3;127,36,134;,
   3;24,22,134;,
   3;35,24,134;,
   3;136,135,122;,
   3;119,136,122;,
   3;32,33,147;,
   3;148,32,147;,
   3;2,23,135;,
   3;136,2,135;,
   3;24,32,148;,
   3;138,24,148;,
   3;120,27,136;,
   3;119,120,136;,
   3;1,2,136;,
   3;27,1,136;,
   3;50,51,57;,
   3;54,50,57;,
   3;19,30,40;,
   3;18,19,40;,
   3;10,13,15;,
   3;16,10,15;;
   MeshNormals
   {
    149;
    0.473008;-0.799673;0.369846;,
    0.385557;-0.919574;-0.075697;,
    -0.299060;-0.953853;0.026990;,
    -0.010198;-0.707650;0.706490;,
    0.790215;-0.477135;0.384581;,
    0.746427;-0.664790;-0.030018;,
    0.440109;-0.115066;0.890542;,
    -0.708599;0.305575;-0.636012;,
    -0.789576;0.062777;-0.610434;,
    -0.351077;-0.056006;-0.934670;,
    -0.332169;0.334596;-0.881878;,
    -0.798654;0.529747;-0.285517;,
    -0.959019;0.251494;-0.130515;,
    -0.380037;0.765324;-0.519471;,
    0.861451;0.449122;-0.237046;,
    0.333649;0.780203;-0.529114;,
    0.318766;0.252886;-0.913475;,
    0.897960;0.088991;-0.430985;,
    0.841875;0.458990;0.283857;,
    0.189279;0.966427;0.173761;,
    0.984675;0.019998;0.173247;,
    -0.550823;-0.311581;0.774281;,
    -0.301335;0.198121;0.932709;,
    -0.846966;-0.447746;0.286659;,
    -0.827186;0.162067;0.538050;,
    0.896578;-0.335394;0.289239;,
    0.767928;-0.634930;-0.084562;,
    0.385392;-0.875202;-0.292395;,
    -0.406373;0.911927;-0.057003;,
    -0.670442;0.709566;0.216847;,
    -0.078895;0.727411;0.681651;,
    -0.851991;0.314522;0.418554;,
    -0.974588;0.004112;0.223965;,
    -0.991753;-0.051470;0.117374;,
    -0.838627;0.323694;0.438095;,
    -0.589799;0.429373;0.683941;,
    -0.436325;0.500075;0.748028;,
    0.868036;0.038277;0.495024;,
    0.992288;-0.054342;0.111410;,
    0.845895;0.044128;0.531522;,
    0.627919;0.337140;0.701466;,
    0.452809;0.246330;0.856905;,
    -0.251046;0.448220;0.857948;,
    0.429923;0.297850;0.852321;,
    -0.297507;0.380265;0.875722;,
    0.847148;0.126921;0.515976;,
    0.853233;0.176567;0.490732;,
    0.437395;0.354123;0.826609;,
    0.993752;-0.028259;0.107975;,
    0.994604;-0.012024;0.103047;,
    0.851029;-0.210624;-0.481027;,
    0.847588;-0.261247;-0.461893;,
    0.861546;-0.118405;-0.493679;,
    0.284582;-0.114944;-0.951736;,
    0.250519;-0.307783;-0.917883;,
    -0.399625;-0.245296;-0.883250;,
    -0.407041;-0.350483;-0.843492;,
    0.240780;-0.410918;-0.879302;,
    -0.816418;-0.096753;-0.569299;,
    -0.821324;-0.185072;-0.539607;,
    -0.990946;0.091623;-0.098140;,
    -0.996770;0.033541;-0.072974;,
    -0.847426;0.276310;0.453344;,
    -0.846137;0.261311;0.464509;,
    -0.809277;0.423384;0.407206;,
    -0.296445;0.409136;0.862976;,
    0.429302;0.379324;0.819642;,
    -0.288976;0.427963;0.856353;,
    0.852620;0.194419;0.485015;,
    0.996483;-0.028985;0.078620;,
    0.832448;-0.311556;-0.458216;,
    0.255424;-0.477094;-0.840916;,
    -0.387530;-0.417668;-0.821811;,
    -0.823615;-0.231679;-0.517671;,
    -0.999089;0.016529;-0.039339;,
    -0.832721;0.268731;0.484107;,
    -0.303402;0.442056;0.844117;,
    -0.827657;0.270484;0.491754;,
    0.400372;0.406869;0.821072;,
    0.849933;0.207114;0.484477;,
    0.997525;-0.062304;0.032587;,
    0.812828;-0.347337;-0.467619;,
    0.297608;-0.507307;-0.808746;,
    -0.355252;-0.459642;-0.813956;,
    -0.839178;-0.248799;-0.483610;,
    -0.999833;0.017404;0.005566;,
    -0.840564;0.266568;0.471586;,
    -0.997815;0.046431;0.046996;,
    -0.348794;0.438117;0.828491;,
    0.381263;0.400832;0.833050;,
    0.866445;0.165086;0.471189;,
    0.993250;-0.115971;0.002187;,
    0.815742;-0.359615;-0.453037;,
    0.353166;-0.504688;-0.787759;,
    -0.343496;-0.464053;-0.816496;,
    -0.874764;-0.217200;-0.433142;,
    -0.992140;0.103726;0.069995;,
    -0.897320;-0.238970;-0.371093;,
    -0.827843;0.341979;0.444663;,
    -0.350894;0.502567;0.790127;,
    0.388880;0.413526;0.823267;,
    0.873584;0.106443;0.474890;,
    0.980392;-0.182909;0.073314;,
    0.848979;-0.428955;-0.308596;,
    0.424811;-0.624536;-0.655355;,
    -0.325952;-0.591963;-0.737113;,
    -0.861920;-0.465141;-0.201836;,
    -0.219820;-0.864711;-0.451612;,
    -0.985954;0.053734;0.158135;,
    -0.776427;0.406560;0.481529;,
    -0.296722;0.577025;0.760920;,
    0.384234;0.470127;0.794572;,
    0.853948;0.125994;0.504875;,
    0.962161;-0.203603;0.181089;,
    0.859733;-0.501875;-0.094766;,
    0.495336;-0.791831;-0.357277;,
    0.492775;-0.839536;-0.228806;,
    0.831503;-0.554362;-0.035853;,
    -0.143313;-0.943671;-0.298238;,
    -0.181851;-0.915266;-0.359469;,
    0.438095;-0.852916;-0.283915;,
    -0.787055;-0.603904;-0.125874;,
    -0.797795;-0.572033;-0.190529;,
    -0.981048;-0.052990;0.186376;,
    -0.789175;0.347053;0.506712;,
    -0.329706;0.539874;0.774487;,
    0.324330;0.461973;0.825464;,
    0.204172;0.416081;0.886110;,
    0.823378;0.119376;0.554795;,
    0.765315;0.062199;0.640643;,
    0.945812;-0.243421;0.214910;,
    0.918377;-0.319378;0.233626;,
    0.786553;-0.612905;-0.075379;,
    0.663860;0.067601;0.744795;,
    0.014315;0.401747;0.915639;,
    -0.843620;-0.529400;-0.089665;,
    -0.260066;-0.911602;-0.318350;,
    -0.789576;0.062777;-0.610434;,
    -0.846966;-0.447746;0.286659;,
    -0.816418;-0.096753;-0.569299;,
    -0.821324;-0.185072;-0.539607;,
    -0.823615;-0.231679;-0.517671;,
    -0.839178;-0.248799;-0.483610;,
    -0.874764;-0.217200;-0.433142;,
    -0.897320;-0.238970;-0.371093;,
    -0.861920;-0.465141;-0.201836;,
    -0.787055;-0.603904;-0.125874;,
    -0.797795;-0.572033;-0.190529;,
    -0.843620;-0.529400;-0.089665;;
    270;
    3;2,1,0;,
    3;3,2,0;,
    3;5,4,0;,
    3;1,5,0;,
    3;6,3,0;,
    3;4,6,0;,
    3;9,8,7;,
    3;10,9,7;,
    3;12,11,7;,
    3;137,12,7;,
    3;13,10,7;,
    3;11,13,7;,
    3;16,15,14;,
    3;17,16,14;,
    3;19,18,14;,
    3;15,19,14;,
    3;20,17,14;,
    3;18,20,14;,
    3;6,22,21;,
    3;3,6,21;,
    3;2,3,21;,
    3;23,2,21;,
    3;24,138,21;,
    3;22,24,21;,
    3;25,4,5;,
    3;26,25,5;,
    3;27,26,5;,
    3;1,27,5;,
    3;11,29,28;,
    3;13,11,28;,
    3;15,13,28;,
    3;19,15,28;,
    3;30,19,28;,
    3;29,30,28;,
    3;33,32,31;,
    3;34,33,31;,
    3;24,35,31;,
    3;32,24,31;,
    3;36,34,31;,
    3;35,36,31;,
    3;38,20,37;,
    3;39,38,37;,
    3;18,40,37;,
    3;20,18,37;,
    3;41,39,37;,
    3;40,41,37;,
    3;30,42,41;,
    3;40,30,41;,
    3;44,43,41;,
    3;42,44,41;,
    3;45,39,41;,
    3;43,45,41;,
    3;47,46,45;,
    3;43,47,45;,
    3;49,48,45;,
    3;46,49,45;,
    3;38,39,45;,
    3;48,38,45;,
    3;51,50,48;,
    3;49,51,48;,
    3;52,38,48;,
    3;50,52,48;,
    3;20,38,52;,
    3;17,20,52;,
    3;54,53,52;,
    3;50,54,52;,
    3;16,17,52;,
    3;53,16,52;,
    3;55,9,53;,
    3;54,55,53;,
    3;10,16,53;,
    3;9,10,53;,
    3;57,56,55;,
    3;54,57,55;,
    3;59,58,55;,
    3;56,59,55;,
    3;8,9,55;,
    3;58,8,55;,
    3;61,60,139;,
    3;140,61,139;,
    3;12,137,139;,
    3;60,12,139;,
    3;63,62,60;,
    3;61,63,60;,
    3;64,12,60;,
    3;62,64,60;,
    3;11,12,64;,
    3;29,11,64;,
    3;44,42,64;,
    3;62,44,64;,
    3;30,29,64;,
    3;42,30,64;,
    3;65,44,62;,
    3;63,65,62;,
    3;67,65,63;,
    3;75,67,63;,
    3;66,47,65;,
    3;67,66,65;,
    3;43,44,65;,
    3;47,43,65;,
    3;47,66,68;,
    3;46,47,68;,
    3;46,68,69;,
    3;49,46,69;,
    3;49,69,70;,
    3;51,49,70;,
    3;51,70,71;,
    3;57,51,71;,
    3;57,71,72;,
    3;56,57,72;,
    3;56,72,73;,
    3;59,56,73;,
    3;140,141,74;,
    3;61,140,74;,
    3;74,75,63;,
    3;61,74,63;,
    3;77,75,74;,
    3;85,77,74;,
    3;76,67,75;,
    3;77,76,75;,
    3;67,76,78;,
    3;66,67,78;,
    3;66,78,79;,
    3;68,66,79;,
    3;68,79,80;,
    3;69,68,80;,
    3;69,80,81;,
    3;70,69,81;,
    3;70,81,82;,
    3;71,70,82;,
    3;71,82,83;,
    3;72,71,83;,
    3;72,83,84;,
    3;73,72,84;,
    3;142,85,74;,
    3;141,142,74;,
    3;87,85,142;,
    3;95,87,142;,
    3;86,77,85;,
    3;87,86,85;,
    3;77,86,88;,
    3;76,77,88;,
    3;76,88,89;,
    3;78,76,89;,
    3;78,89,90;,
    3;79,78,90;,
    3;79,90,91;,
    3;80,79,91;,
    3;80,91,92;,
    3;81,80,92;,
    3;81,92,93;,
    3;82,81,93;,
    3;82,93,94;,
    3;83,82,94;,
    3;94,143,84;,
    3;83,94,84;,
    3;97,143,94;,
    3;105,97,94;,
    3;96,87,95;,
    3;144,96,95;,
    3;87,96,98;,
    3;86,87,98;,
    3;86,98,99;,
    3;88,86,99;,
    3;88,99,100;,
    3;89,88,100;,
    3;89,100,101;,
    3;90,89,101;,
    3;90,101,102;,
    3;91,90,102;,
    3;91,102,103;,
    3;92,91,103;,
    3;92,103,104;,
    3;93,92,104;,
    3;104,105,94;,
    3;93,104,94;,
    3;107,105,104;,
    3;115,107,104;,
    3;106,97,105;,
    3;107,106,105;,
    3;144,145,108;,
    3;96,144,108;,
    3;96,108,109;,
    3;98,96,109;,
    3;98,109,110;,
    3;99,98,110;,
    3;99,110,111;,
    3;100,99,111;,
    3;100,111,112;,
    3;101,100,112;,
    3;101,112,113;,
    3;102,101,113;,
    3;102,113,114;,
    3;103,102,114;,
    3;114,115,104;,
    3;103,114,104;,
    3;117,116,115;,
    3;114,117,115;,
    3;118,107,115;,
    3;116,118,115;,
    3;120,119,118;,
    3;116,120,118;,
    3;122,121,118;,
    3;119,122,118;,
    3;106,107,118;,
    3;121,106,118;,
    3;33,123,146;,
    3;147,33,146;,
    3;108,145,146;,
    3;123,108,146;,
    3;34,124,123;,
    3;33,34,123;,
    3;109,108,123;,
    3;124,109,123;,
    3;36,125,124;,
    3;34,36,124;,
    3;110,109,124;,
    3;125,110,124;,
    3;127,126,125;,
    3;36,127,125;,
    3;111,110,125;,
    3;126,111,125;,
    3;129,128,126;,
    3;127,129,126;,
    3;112,111,126;,
    3;128,112,126;,
    3;131,130,128;,
    3;129,131,128;,
    3;113,112,128;,
    3;130,113,128;,
    3;132,117,130;,
    3;131,132,130;,
    3;114,113,130;,
    3;117,114,130;,
    3;25,26,132;,
    3;131,25,132;,
    3;27,120,132;,
    3;26,27,132;,
    3;116,117,132;,
    3;120,116,132;,
    3;133,25,131;,
    3;129,133,131;,
    3;127,134,133;,
    3;129,127,133;,
    3;22,6,133;,
    3;134,22,133;,
    3;4,25,133;,
    3;6,4,133;,
    3;36,35,134;,
    3;127,36,134;,
    3;24,22,134;,
    3;35,24,134;,
    3;136,135,122;,
    3;119,136,122;,
    3;32,33,147;,
    3;148,32,147;,
    3;2,23,135;,
    3;136,2,135;,
    3;24,32,148;,
    3;138,24,148;,
    3;120,27,136;,
    3;119,120,136;,
    3;1,2,136;,
    3;27,1,136;,
    3;50,51,57;,
    3;54,50,57;,
    3;19,30,40;,
    3;18,19,40;,
    3;10,13,15;,
    3;16,10,15;;
   }
   MeshTextureCoords
   {
    149;
    0.069376;0.080198;,
    0.064903;0.077792;,
    0.059113;0.073982;,
    0.047109;0.075463;,
    0.064036;0.080409;,
    0.065386;0.079462;,
    0.056656;0.080304;,
    0.108714;0.139239;,
    0.110563;0.138266;,
    0.109513;0.137502;,
    0.108509;0.138358;,
    0.107838;0.138978;,
    0.106880;0.139814;,
    0.107861;0.138306;,
    0.107683;0.137746;,
    0.107785;0.137994;,
    0.108152;0.137874;,
    0.107849;0.137498;,
    0.107439;0.137735;,
    0.107518;0.138094;,
    0.107464;0.137406;,
    0.048448;0.076695;,
    0.052683;0.080618;,
    0.053570;0.070342;,
    0.049605;0.081930;,
    0.063318;0.080648;,
    0.064805;0.079516;,
    0.064744;0.077701;,
    0.107591;0.138338;,
    0.107334;0.138606;,
    0.107205;0.138153;,
    0.050417;0.084101;,
    0.048009;0.084595;,
    0.048539;0.086957;,
    0.051320;0.085477;,
    0.052154;0.082947;,
    0.054022;0.084266;,
    0.107166;0.137443;,
    0.107449;0.136901;,
    0.106887;0.137158;,
    0.107134;0.137750;,
    0.106542;0.137659;,
    0.106412;0.138262;,
    0.104871;0.136716;,
    0.104292;0.137740;,
    0.105716;0.135778;,
    0.103634;0.133370;,
    0.102333;0.134624;,
    0.106743;0.135118;,
    0.105040;0.132332;,
    0.107840;0.134716;,
    0.106488;0.131485;,
    0.108067;0.136893;,
    0.108761;0.137102;,
    0.109050;0.134500;,
    0.110376;0.134444;,
    0.109674;0.130035;,
    0.108042;0.130723;,
    0.112166;0.134524;,
    0.111685;0.129286;,
    0.103685;0.140461;,
    0.099314;0.139279;,
    0.103890;0.138996;,
    0.100253;0.137541;,
    0.106500;0.138972;,
    0.101286;0.135922;,
    0.095761;0.127941;,
    0.094169;0.129530;,
    0.097514;0.126417;,
    0.099322;0.124926;,
    0.101138;0.123578;,
    0.103024;0.122324;,
    0.104894;0.121203;,
    0.107063;0.119897;,
    0.091002;0.133272;,
    0.092570;0.131346;,
    0.085833;0.121096;,
    0.083926;0.122951;,
    0.087774;0.119361;,
    0.089842;0.117661;,
    0.091995;0.115870;,
    0.094015;0.114246;,
    0.096094;0.112687;,
    0.098182;0.111211;,
    0.100299;0.109676;,
    0.081996;0.125017;,
    0.074328;0.112979;,
    0.072216;0.115099;,
    0.076449;0.110969;,
    0.078656;0.109019;,
    0.080879;0.107173;,
    0.083103;0.105350;,
    0.085340;0.103598;,
    0.087564;0.101872;,
    0.089870;0.100067;,
    0.070119;0.117319;,
    0.060927;0.103530;,
    0.082478;0.085642;,
    0.063276;0.101432;,
    0.065949;0.099222;,
    0.068589;0.097050;,
    0.071149;0.094951;,
    0.073502;0.093120;,
    0.075702;0.091531;,
    0.077905;0.089876;,
    0.080235;0.087863;,
    0.072196;0.075047;,
    0.070123;0.077927;,
    0.052183;0.091524;,
    0.055884;0.090482;,
    0.059029;0.089768;,
    0.061774;0.088677;,
    0.064136;0.087223;,
    0.065735;0.085627;,
    0.066904;0.083485;,
    0.068464;0.080818;,
    0.066534;0.079251;,
    0.065345;0.081330;,
    0.067371;0.076314;,
    0.065028;0.075095;,
    0.065350;0.078195;,
    0.068831;0.072012;,
    0.064919;0.069761;,
    0.050043;0.089003;,
    0.053000;0.087310;,
    0.056160;0.086413;,
    0.059175;0.085427;,
    0.057136;0.083234;,
    0.061904;0.084251;,
    0.060554;0.082285;,
    0.063896;0.082971;,
    0.063243;0.081286;,
    0.064715;0.080030;,
    0.059148;0.081264;,
    0.055092;0.081917;,
    0.059716;0.068866;,
    0.062466;0.074389;,
    0.107604;0.141009;,
    0.044169;0.082348;,
    0.103654;0.142187;,
    0.098416;0.141127;,
    0.089558;0.135203;,
    0.080169;0.127151;,
    0.092227;0.098195;,
    0.058754;0.105697;,
    0.049291;0.093488;,
    0.046966;0.091224;,
    0.045249;0.089073;,
    0.043971;0.086287;;
   }
   MeshMaterialList
   {
    1;
    270;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
    149;
    137;
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
    100,
    101,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    109,
    110,
    111,
    112,
    113,
    114,
    115,
    116,
    117,
    118,
    119,
    120,
    121,
    122,
    123,
    124,
    125,
    126,
    127,
    128,
    129,
    130,
    131,
    132,
    133,
    134,
    135,
    136,
    8,
    23,
    58,
    59,
    73,
    84,
    95,
    97,
    106,
    121,
    122,
    135;
   }
  }
 }
}

# Animations definition.

