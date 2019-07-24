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
  "data/TEXTURE/kamiko_texx.jpg";
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
   0.000000,-4.213926,-0.000000,1.000000;;
  }
  Mesh
  {
   172;
   0.138128;16.119770;0.634414;,
   2.084918;14.003968;-1.097070;,
   3.018272;12.917872;-1.806662;,
   2.972385;11.086705;-5.123905;,
   3.268103;9.068114;-5.506005;,
   0.138128;11.070264;-3.580314;,
   0.138128;9.068238;-4.208572;,
   4.707433;15.917720;0.203114;,
   4.590152;13.593922;-0.954314;,
   5.196982;13.196757;-0.492412;,
   2.638141;13.327918;4.795846;,
   5.070793;13.603926;3.807275;,
   2.375026;15.786683;3.956658;,
   5.031048;15.441657;3.258913;,
   5.344286;10.756932;2.513687;,
   2.870108;10.692915;4.215195;,
   5.498139;12.266515;0.834654;,
   5.259139;12.835851;-1.409183;,
   5.832836;10.968486;-2.331737;,
   6.125976;10.853705;0.239061;,
   4.984990;16.355646;1.905246;,
   3.219388;16.956739;1.983736;,
   3.422550;16.677044;0.945777;,
   0.138128;16.599274;2.089263;,
   0.138128;16.326324;3.328462;,
   3.983321;13.990965;-1.416185;,
   5.084422;9.068114;1.635395;,
   5.892555;9.068238;-0.336684;,
   3.899487;12.680311;-1.806756;,
   4.793549;12.757954;-1.649496;,
   2.784164;9.068238;3.607598;,
   5.633519;9.068114;-2.766413;,
   5.522396;9.068114;-3.455500;,
   5.451111;11.002934;-3.217219;,
   4.843452;9.068238;-4.203039;,
   4.501457;11.037443;-4.161278;,
   0.138128;9.828502;3.670021;,
   0.138128;10.715734;3.976694;,
   0.138128;13.185627;4.461509;,
   0.138128;13.934764;-0.893048;,
   0.138128;16.024061;0.759978;,
   2.094343;13.898067;-0.979883;,
   0.138128;12.395299;-1.734581;,
   3.032197;12.806719;-1.692914;,
   0.138128;10.950170;-3.480819;,
   2.213687;7.109790;2.181569;,
   0.138128;7.350542;1.434592;,
   0.138128;7.109790;-3.809592;,
   3.004706;7.109665;-4.162560;,
   4.240936;7.109790;-3.334750;,
   4.714012;7.109665;-2.780261;,
   4.747005;7.109665;-2.111961;,
   5.044083;7.109790;-0.809245;,
   4.383364;7.109665;0.770700;,
   4.598154;3.176448;-1.860583;,
   4.321613;6.111154;-1.825355;,
   4.373064;6.286200;-1.813570;,
   4.932976;3.176012;-1.027646;,
   4.636086;6.111154;-1.040681;,
   4.691522;6.284950;-1.018675;,
   4.195048;3.174698;-3.060084;,
   3.944983;6.108966;-2.934957;,
   3.978852;6.282262;-2.977937;,
   4.602155;3.175449;-2.558296;,
   4.328381;6.110029;-2.459583;,
   4.374877;6.284012;-2.492404;,
   0.138128;3.174074;1.333952;,
   0.138128;6.108904;0.388662;,
   0.138128;6.280510;1.291597;,
   2.056755;3.174199;1.689409;,
   1.936567;6.109966;1.505548;,
   1.950790;6.279572;1.580193;,
   3.054438;3.949838;-3.702065;,
   2.867545;6.107777;-3.541209;,
   2.914229;6.283198;-3.577219;,
   4.299795;3.174322;0.465307;,
   4.044916;6.110216;0.355153;,
   4.080394;6.279823;0.417357;,
   0.138128;4.688219;-3.791494;,
   0.138128;6.109278;-3.623825;,
   0.138128;6.286699;-3.662148;,
   -1.818071;13.898067;-0.979883;,
   -2.755926;12.806719;-1.692914;,
   -2.991832;9.068114;-5.506005;,
   -2.696114;11.086705;-5.123905;,
   -4.431161;15.917720;0.203114;,
   -4.313880;13.593922;-0.954314;,
   -4.920711;13.196757;-0.492412;,
   -4.794522;13.603926;3.807275;,
   -2.361885;13.327918;4.795846;,
   -2.098754;15.786683;3.956658;,
   -4.754777;15.441657;3.258913;,
   -5.067999;10.756932;2.513687;,
   -2.593837;10.692915;4.215195;,
   -5.221868;12.266515;0.834654;,
   -4.982852;12.835851;-1.409183;,
   -5.556565;10.968486;-2.331737;,
   -5.849704;10.853705;0.239061;,
   -2.943115;16.956739;1.983736;,
   -4.708718;16.355646;1.905246;,
   -3.146278;16.677044;0.945777;,
   -3.707050;13.990965;-1.416185;,
   -1.808647;14.003968;-1.097070;,
   -5.616283;9.068238;-0.336684;,
   -4.808150;9.068114;1.635395;,
   -2.742001;12.917872;-1.806662;,
   -3.623215;12.680311;-1.806756;,
   -4.517277;12.757954;-1.649496;,
   -4.107092;7.109665;0.770700;,
   -1.937415;7.109790;2.181569;,
   -2.507877;9.068238;3.607598;,
   -4.767812;7.109790;-0.809245;,
   -5.357247;9.068114;-2.766413;,
   -4.470734;7.109665;-2.111961;,
   -5.246124;9.068114;-3.455500;,
   -4.437741;7.109665;-2.780261;,
   -5.174840;11.002934;-3.217219;,
   -2.728434;7.109665;-4.162560;,
   -3.964664;7.109790;-3.334750;,
   -4.567181;9.068238;-4.203039;,
   -4.225185;11.037443;-4.161278;,
   -4.045341;6.111154;-1.825355;,
   -4.321883;3.176448;-1.860583;,
   -4.325883;3.175449;-2.558296;,
   -4.052109;6.110029;-2.459583;,
   -4.096793;6.286200;-1.813570;,
   -4.098590;6.284012;-2.492404;,
   -4.656704;3.176012;-1.027646;,
   -4.415251;6.284950;-1.018675;,
   -4.359814;6.111154;-1.040681;,
   -4.023523;3.174322;0.465307;,
   -3.804122;6.279823;0.417357;,
   -3.768644;6.110216;0.355153;,
   -3.668712;6.108966;-2.934957;,
   -3.918777;3.174698;-3.060084;,
   -2.778166;3.949838;-3.702065;,
   -2.591274;6.107777;-3.541209;,
   -3.702580;6.282262;-2.977937;,
   -2.637958;6.283198;-3.577219;,
   -1.780483;3.174199;1.689409;,
   -1.660295;6.109966;1.505548;,
   -1.674518;6.279572;1.580193;,
   2.084918;14.003968;-1.097070;,
   0.138128;16.024061;0.759978;,
   2.094343;13.898067;-0.979883;,
   3.018272;12.917872;-1.806662;,
   2.094343;13.898067;-0.979883;,
   3.032197;12.806719;-1.692914;,
   0.138128;11.070264;-3.580314;,
   3.032197;12.806719;-1.692914;,
   0.138128;10.950170;-3.480819;,
   0.138128;16.024061;0.759978;,
   0.138128;16.326324;3.328462;,
   0.138128;16.599274;2.089263;,
   0.138128;16.119770;0.634414;,
   0.138128;9.828502;3.670021;,
   0.138128;7.350542;1.434592;,
   0.138128;10.715734;3.976694;,
   0.138128;13.185627;4.461509;,
   0.138128;10.950170;-3.480819;,
   -1.818071;13.898067;-0.979883;,
   0.138128;16.024061;0.759978;,
   0.138128;16.119770;0.634414;,
   -2.755926;12.806719;-1.692914;,
   -1.818071;13.898067;-0.979883;,
   -1.808647;14.003968;-1.097070;,
   0.138128;10.950170;-3.480819;,
   -2.755926;12.806719;-1.692914;,
   -2.742001;12.917872;-1.806662;,
   0.138128;6.108904;0.388662;,
   0.138128;3.174074;1.333952;,
   0.138128;6.280510;1.291597;;
   266;
   3;41,39,40;,
   3;43,42,39;,
   3;41,43,39;,
   3;5,3,4;,
   3;6,5,4;,
   3;9,8,7;,
   3;12,10,11;,
   3;13,12,11;,
   3;15,14,11;,
   3;10,15,11;,
   3;17,9,16;,
   3;18,17,16;,
   3;19,18,16;,
   3;13,20,21;,
   3;12,13,21;,
   3;21,20,7;,
   3;22,21,7;,
   3;21,23,24;,
   3;12,21,24;,
   3;23,21,22;,
   3;0,23,22;,
   3;0,22,25;,
   3;1,0,25;,
   3;14,26,27;,
   3;19,14,27;,
   3;28,2,1;,
   3;25,28,1;,
   3;17,29,8;,
   3;9,17,8;,
   3;30,45,53;,
   3;26,30,53;,
   3;52,27,26;,
   3;53,52,26;,
   3;51,31,27;,
   3;52,51,27;,
   3;51,50,32;,
   3;31,51,32;,
   3;18,33,29;,
   3;17,18,29;,
   3;34,49,48;,
   3;4,34,48;,
   3;35,3,2;,
   3;28,35,2;,
   3;48,47,6;,
   3;4,48,6;,
   3;36,46,45;,
   3;30,36,45;,
   3;37,36,30;,
   3;15,37,30;,
   3;24,38,10;,
   3;12,24,10;,
   3;20,16,9;,
   3;7,20,9;,
   3;13,11,16;,
   3;20,13,16;,
   3;42,43,44;,
   3;26,14,15;,
   3;30,26,15;,
   3;31,18,19;,
   3;27,31,19;,
   3;11,14,19;,
   3;16,11,19;,
   3;32,33,18;,
   3;31,32,18;,
   3;4,3,35;,
   3;34,4,35;,
   3;38,37,15;,
   3;10,38,15;,
   3;25,22,7;,
   3;8,25,7;,
   3;29,28,25;,
   3;8,29,25;,
   3;33,35,28;,
   3;29,33,28;,
   3;35,33,32;,
   3;34,35,32;,
   3;32,50,49;,
   3;34,32,49;,
   3;2,3,5;,
   3;143,0,142;,
   3;144,143,142;,
   3;146,1,145;,
   3;147,146,145;,
   3;149,2,148;,
   3;150,149,148;,
   3;63,54,55;,
   3;64,63,55;,
   3;65,56,54;,
   3;63,65,54;,
   3;57,54,56;,
   3;59,57,56;,
   3;58,55,54;,
   3;57,58,54;,
   3;75,57,59;,
   3;77,75,59;,
   3;76,58,57;,
   3;75,76,57;,
   3;72,60,61;,
   3;73,72,61;,
   3;74,62,60;,
   3;72,74,60;,
   3;63,60,62;,
   3;65,63,62;,
   3;64,61,60;,
   3;63,64,60;,
   3;69,66,67;,
   3;70,69,67;,
   3;71,68,66;,
   3;69,71,66;,
   3;75,69,70;,
   3;76,75,70;,
   3;77,71,69;,
   3;75,77,69;,
   3;78,72,73;,
   3;79,78,73;,
   3;80,74,72;,
   3;78,80,72;,
   3;46,68,71;,
   3;45,46,71;,
   3;80,47,48;,
   3;74,80,48;,
   3;49,62,74;,
   3;48,49,74;,
   3;50,65,62;,
   3;49,50,62;,
   3;65,50,51;,
   3;56,65,51;,
   3;56,51,52;,
   3;59,56,52;,
   3;59,52,53;,
   3;77,59,53;,
   3;45,71,77;,
   3;53,45,77;,
   3;39,81,151;,
   3;82,81,39;,
   3;42,82,39;,
   3;5,6,83;,
   3;84,5,83;,
   3;86,87,85;,
   3;90,91,88;,
   3;89,90,88;,
   3;93,89,88;,
   3;92,93,88;,
   3;96,97,94;,
   3;95,96,94;,
   3;87,95,94;,
   3;91,90,98;,
   3;99,91,98;,
   3;98,100,85;,
   3;99,98,85;,
   3;98,90,152;,
   3;153,98,152;,
   3;153,154,100;,
   3;98,153,100;,
   3;154,102,101;,
   3;100,154,101;,
   3;92,97,103;,
   3;104,92,103;,
   3;106,101,102;,
   3;105,106,102;,
   3;95,87,86;,
   3;107,95,86;,
   3;110,104,108;,
   3;109,110,108;,
   3;111,108,104;,
   3;103,111,104;,
   3;113,111,103;,
   3;112,113,103;,
   3;113,112,114;,
   3;115,113,114;,
   3;96,95,107;,
   3;116,96,107;,
   3;119,83,117;,
   3;118,119,117;,
   3;120,106,105;,
   3;84,120,105;,
   3;117,83,6;,
   3;47,117,6;,
   3;155,110,109;,
   3;156,155,109;,
   3;157,93,110;,
   3;155,157,110;,
   3;152,90,89;,
   3;158,152,89;,
   3;99,85,87;,
   3;94,99,87;,
   3;91,99,94;,
   3;88,91,94;,
   3;82,42,159;,
   3;104,110,93;,
   3;92,104,93;,
   3;112,103,97;,
   3;96,112,97;,
   3;88,94,97;,
   3;92,88,97;,
   3;114,112,96;,
   3;116,114,96;,
   3;83,119,120;,
   3;84,83,120;,
   3;158,89,93;,
   3;157,158,93;,
   3;101,86,85;,
   3;100,101,85;,
   3;107,86,101;,
   3;106,107,101;,
   3;116,107,106;,
   3;120,116,106;,
   3;120,119,114;,
   3;116,120,114;,
   3;114,119,118;,
   3;115,114,118;,
   3;84,105,5;,
   3;161,160,102;,
   3;162,161,102;,
   3;164,163,105;,
   3;165,164,105;,
   3;167,166,5;,
   3;168,167,5;,
   3;123,124,121;,
   3;122,123,121;,
   3;126,123,122;,
   3;125,126,122;,
   3;127,128,125;,
   3;122,127,125;,
   3;129,127,122;,
   3;121,129,122;,
   3;130,131,128;,
   3;127,130,128;,
   3;132,130,127;,
   3;129,132,127;,
   3;135,136,133;,
   3;134,135,133;,
   3;138,135,134;,
   3;137,138,134;,
   3;123,126,137;,
   3;134,123,137;,
   3;124,123,134;,
   3;133,124,134;,
   3;139,140,169;,
   3;170,139,169;,
   3;141,139,170;,
   3;171,141,170;,
   3;130,132,140;,
   3;139,130,140;,
   3;131,130,139;,
   3;141,131,139;,
   3;78,79,136;,
   3;135,78,136;,
   3;80,78,135;,
   3;138,80,135;,
   3;156,109,141;,
   3;171,156,141;,
   3;80,138,117;,
   3;47,80,117;,
   3;118,117,138;,
   3;137,118,138;,
   3;115,118,137;,
   3;126,115,137;,
   3;126,125,113;,
   3;115,126,113;,
   3;125,128,111;,
   3;113,125,111;,
   3;128,131,108;,
   3;111,128,108;,
   3;109,108,131;,
   3;141,109,131;;
   MeshNormals
   {
    172;
    -0.217486;0.705543;-0.674470;,
    -0.387837;0.270253;-0.881218;,
    -0.214334;0.881351;-0.421048;,
    0.050257;0.611893;-0.789342;,
    0.132131;-0.146585;-0.980334;,
    0.195404;0.753497;-0.627742;,
    0.000001;-0.094615;-0.995514;,
    0.670586;0.536644;-0.512179;,
    0.509960;0.509209;-0.693287;,
    0.831210;0.415127;-0.369810;,
    0.135404;0.049285;0.989564;,
    0.806917;0.104150;0.581410;,
    0.104662;0.642932;0.758739;,
    0.628977;0.475047;0.615402;,
    0.802574;-0.191287;0.565053;,
    0.227302;-0.307361;0.924047;,
    0.979136;0.203205;0.001029;,
    0.711438;0.575119;-0.403850;,
    0.935546;0.220079;-0.276259;,
    0.995654;0.044829;0.081634;,
    0.795429;0.601371;0.075140;,
    0.135626;0.984210;0.113740;,
    0.138739;0.811211;-0.568057;,
    0.000000;0.999047;0.043648;,
    0.000000;0.688240;0.725483;,
    0.189453;0.529115;-0.827131;,
    0.726393;-0.428664;0.537215;,
    0.944261;-0.311082;0.107700;,
    0.262751;0.652925;-0.710388;,
    0.456620;0.633392;-0.624750;,
    0.204711;-0.505804;0.838007;,
    0.960049;-0.227968;-0.162285;,
    0.873646;-0.203822;-0.441813;,
    0.698404;0.400286;-0.593299;,
    0.657911;-0.176034;-0.732233;,
    0.499579;0.513081;-0.697974;,
    0.000001;-0.480535;0.876976;,
    0.000000;-0.273355;0.961913;,
    0.000000;0.057448;0.998349;,
    0.000000;0.564202;-0.825636;,
    -0.023166;0.620305;-0.784018;,
    -0.385354;0.290803;-0.875749;,
    0.000000;0.647381;-0.762167;,
    -0.426543;0.361081;-0.829266;,
    -0.099839;0.766552;-0.634373;,
    0.118444;-0.546638;0.828950;,
    0.000001;-0.475757;0.879577;,
    0.000000;-0.378298;-0.925684;,
    0.182947;-0.466284;-0.865511;,
    0.581597;-0.489909;-0.649411;,
    0.824404;-0.459924;-0.329891;,
    0.905823;-0.400861;-0.137093;,
    0.898524;-0.433690;0.067579;,
    0.668016;-0.517029;0.535197;,
    0.080834;-0.990411;-0.112035;,
    -0.978233;-0.094177;0.184910;,
    0.970641;-0.166112;-0.173964;,
    0.068507;-0.997288;0.026905;,
    -0.994889;-0.100519;-0.009541;,
    0.981815;-0.188291;0.024192;,
    -0.002926;-0.993353;-0.115068;,
    -0.651608;-0.094967;0.752588;,
    0.638061;-0.221775;-0.737356;,
    0.033053;-0.985619;-0.165720;,
    -0.939423;-0.098796;0.328213;,
    0.921919;-0.199522;-0.332049;,
    -0.000004;-0.910806;0.412836;,
    -0.000001;-0.183518;-0.983016;,
    0.000001;-0.150728;0.988575;,
    0.708248;-0.657314;0.257534;,
    -0.064965;-0.135440;-0.988653;,
    0.132854;-0.220570;0.966281;,
    0.010936;-0.996215;-0.086228;,
    -0.283246;-0.098955;0.953928;,
    0.255994;-0.204659;-0.944765;,
    0.046456;-0.997181;0.058925;,
    -0.737929;-0.089257;-0.668950;,
    0.728841;-0.242532;0.640288;,
    0.000000;-0.996607;-0.082312;,
    0.000000;-0.097956;0.995191;,
    0.000000;-0.164503;-0.986377;,
    0.383757;0.289218;-0.876974;,
    0.375377;0.819790;-0.432476;,
    -0.132130;-0.146585;-0.980334;,
    -0.050256;0.611893;-0.789342;,
    -0.670586;0.536644;-0.512179;,
    -0.509961;0.509207;-0.693287;,
    -0.831210;0.415125;-0.369812;,
    -0.806918;0.104149;0.581409;,
    -0.135405;0.049285;0.989564;,
    -0.104662;0.642932;0.758739;,
    -0.628977;0.475047;0.615401;,
    -0.802573;-0.191287;0.565054;,
    -0.227302;-0.307362;0.924047;,
    -0.979136;0.203204;0.001028;,
    -0.711440;0.575116;-0.403851;,
    -0.935546;0.220079;-0.276259;,
    -0.995654;0.044828;0.081634;,
    -0.135625;0.984210;0.113740;,
    -0.795429;0.601371;0.075140;,
    -0.138738;0.811211;-0.568057;,
    -0.189452;0.529115;-0.827131;,
    0.389437;0.271833;-0.880026;,
    -0.944261;-0.311081;0.107701;,
    -0.726393;-0.428663;0.537216;,
    0.274908;0.588202;-0.760555;,
    -0.262751;0.652925;-0.710388;,
    -0.456622;0.633391;-0.624749;,
    -0.668016;-0.517029;0.535197;,
    -0.118443;-0.546638;0.828950;,
    -0.204710;-0.505804;0.838007;,
    -0.898524;-0.433690;0.067579;,
    -0.960049;-0.227968;-0.162285;,
    -0.905822;-0.400864;-0.137095;,
    -0.873646;-0.203822;-0.441813;,
    -0.824402;-0.459928;-0.329891;,
    -0.698404;0.400286;-0.593298;,
    -0.182947;-0.466284;-0.865511;,
    -0.581598;-0.489910;-0.649409;,
    -0.657911;-0.176034;-0.732233;,
    -0.499579;0.513081;-0.697974;,
    0.978233;-0.094177;0.184910;,
    -0.080834;-0.990378;-0.112328;,
    -0.033189;-0.985597;-0.165823;,
    0.939423;-0.098796;0.328213;,
    -0.970639;-0.166114;-0.173970;,
    -0.921918;-0.199524;-0.332050;,
    -0.068508;-0.997288;0.026901;,
    -0.981815;-0.188291;0.024192;,
    0.994889;-0.100519;-0.009541;,
    -0.046457;-0.997181;0.058923;,
    -0.728841;-0.242531;0.640288;,
    0.737929;-0.089257;-0.668950;,
    0.651608;-0.094967;0.752588;,
    0.002806;-0.993370;-0.114924;,
    -0.010936;-0.996215;-0.086229;,
    0.283246;-0.098955;0.953928;,
    -0.638065;-0.221776;-0.737352;,
    -0.255994;-0.204659;-0.944765;,
    -0.708249;-0.657311;0.257536;,
    0.064963;-0.135440;-0.988654;,
    -0.132853;-0.220570;0.966281;,
    -0.814419;-0.461546;-0.351707;,
    -0.814419;-0.461546;-0.351707;,
    -0.385354;0.290803;-0.875749;,
    -0.811009;-0.464986;-0.355038;,
    -0.811009;-0.464986;-0.355038;,
    -0.426543;0.361081;-0.829266;,
    -0.662961;0.485479;0.569907;,
    -0.662961;0.485479;0.569907;,
    -0.662961;0.485479;0.569907;,
    0.023166;0.620305;-0.784018;,
    0.000000;0.688240;0.725483;,
    0.000000;0.999047;0.043648;,
    -0.217486;0.705543;-0.674470;,
    0.000001;-0.480535;0.876976;,
    0.000001;-0.475757;0.879577;,
    0.000000;-0.273355;0.961913;,
    0.000000;0.057448;0.998349;,
    0.099840;0.766552;-0.634373;,
    0.814421;-0.461544;-0.351705;,
    0.814421;-0.461544;-0.351705;,
    0.814421;-0.461544;-0.351705;,
    0.811009;-0.464987;-0.355038;,
    0.383757;0.289218;-0.876974;,
    0.811009;-0.464987;-0.355038;,
    0.662963;0.485478;0.569905;,
    0.375377;0.819790;-0.432476;,
    0.662963;0.485478;0.569905;,
    -0.000001;-0.183518;-0.983016;,
    -0.000004;-0.910806;0.412836;,
    0.000001;-0.150728;0.988575;;
    266;
    3;41,39,40;,
    3;43,42,39;,
    3;41,43,39;,
    3;5,3,4;,
    3;6,5,4;,
    3;9,8,7;,
    3;12,10,11;,
    3;13,12,11;,
    3;15,14,11;,
    3;10,15,11;,
    3;17,9,16;,
    3;18,17,16;,
    3;19,18,16;,
    3;13,20,21;,
    3;12,13,21;,
    3;21,20,7;,
    3;22,21,7;,
    3;21,23,24;,
    3;12,21,24;,
    3;23,21,22;,
    3;0,23,22;,
    3;0,22,25;,
    3;1,0,25;,
    3;14,26,27;,
    3;19,14,27;,
    3;28,2,1;,
    3;25,28,1;,
    3;17,29,8;,
    3;9,17,8;,
    3;30,45,53;,
    3;26,30,53;,
    3;52,27,26;,
    3;53,52,26;,
    3;51,31,27;,
    3;52,51,27;,
    3;51,50,32;,
    3;31,51,32;,
    3;18,33,29;,
    3;17,18,29;,
    3;34,49,48;,
    3;4,34,48;,
    3;35,3,2;,
    3;28,35,2;,
    3;48,47,6;,
    3;4,48,6;,
    3;36,46,45;,
    3;30,36,45;,
    3;37,36,30;,
    3;15,37,30;,
    3;24,38,10;,
    3;12,24,10;,
    3;20,16,9;,
    3;7,20,9;,
    3;13,11,16;,
    3;20,13,16;,
    3;42,43,44;,
    3;26,14,15;,
    3;30,26,15;,
    3;31,18,19;,
    3;27,31,19;,
    3;11,14,19;,
    3;16,11,19;,
    3;32,33,18;,
    3;31,32,18;,
    3;4,3,35;,
    3;34,4,35;,
    3;38,37,15;,
    3;10,38,15;,
    3;25,22,7;,
    3;8,25,7;,
    3;29,28,25;,
    3;8,29,25;,
    3;33,35,28;,
    3;29,33,28;,
    3;35,33,32;,
    3;34,35,32;,
    3;32,50,49;,
    3;34,32,49;,
    3;2,3,5;,
    3;143,0,142;,
    3;144,143,142;,
    3;146,1,145;,
    3;147,146,145;,
    3;149,2,148;,
    3;150,149,148;,
    3;63,54,55;,
    3;64,63,55;,
    3;65,56,54;,
    3;63,65,54;,
    3;57,54,56;,
    3;59,57,56;,
    3;58,55,54;,
    3;57,58,54;,
    3;75,57,59;,
    3;77,75,59;,
    3;76,58,57;,
    3;75,76,57;,
    3;72,60,61;,
    3;73,72,61;,
    3;74,62,60;,
    3;72,74,60;,
    3;63,60,62;,
    3;65,63,62;,
    3;64,61,60;,
    3;63,64,60;,
    3;69,66,67;,
    3;70,69,67;,
    3;71,68,66;,
    3;69,71,66;,
    3;75,69,70;,
    3;76,75,70;,
    3;77,71,69;,
    3;75,77,69;,
    3;78,72,73;,
    3;79,78,73;,
    3;80,74,72;,
    3;78,80,72;,
    3;46,68,71;,
    3;45,46,71;,
    3;80,47,48;,
    3;74,80,48;,
    3;49,62,74;,
    3;48,49,74;,
    3;50,65,62;,
    3;49,50,62;,
    3;65,50,51;,
    3;56,65,51;,
    3;56,51,52;,
    3;59,56,52;,
    3;59,52,53;,
    3;77,59,53;,
    3;45,71,77;,
    3;53,45,77;,
    3;39,81,151;,
    3;82,81,39;,
    3;42,82,39;,
    3;5,6,83;,
    3;84,5,83;,
    3;86,87,85;,
    3;90,91,88;,
    3;89,90,88;,
    3;93,89,88;,
    3;92,93,88;,
    3;96,97,94;,
    3;95,96,94;,
    3;87,95,94;,
    3;91,90,98;,
    3;99,91,98;,
    3;98,100,85;,
    3;99,98,85;,
    3;98,90,152;,
    3;153,98,152;,
    3;153,154,100;,
    3;98,153,100;,
    3;154,102,101;,
    3;100,154,101;,
    3;92,97,103;,
    3;104,92,103;,
    3;106,101,102;,
    3;105,106,102;,
    3;95,87,86;,
    3;107,95,86;,
    3;110,104,108;,
    3;109,110,108;,
    3;111,108,104;,
    3;103,111,104;,
    3;113,111,103;,
    3;112,113,103;,
    3;113,112,114;,
    3;115,113,114;,
    3;96,95,107;,
    3;116,96,107;,
    3;119,83,117;,
    3;118,119,117;,
    3;120,106,105;,
    3;84,120,105;,
    3;117,83,6;,
    3;47,117,6;,
    3;155,110,109;,
    3;156,155,109;,
    3;157,93,110;,
    3;155,157,110;,
    3;152,90,89;,
    3;158,152,89;,
    3;99,85,87;,
    3;94,99,87;,
    3;91,99,94;,
    3;88,91,94;,
    3;82,42,159;,
    3;104,110,93;,
    3;92,104,93;,
    3;112,103,97;,
    3;96,112,97;,
    3;88,94,97;,
    3;92,88,97;,
    3;114,112,96;,
    3;116,114,96;,
    3;83,119,120;,
    3;84,83,120;,
    3;158,89,93;,
    3;157,158,93;,
    3;101,86,85;,
    3;100,101,85;,
    3;107,86,101;,
    3;106,107,101;,
    3;116,107,106;,
    3;120,116,106;,
    3;120,119,114;,
    3;116,120,114;,
    3;114,119,118;,
    3;115,114,118;,
    3;84,105,5;,
    3;161,160,102;,
    3;162,161,102;,
    3;164,163,105;,
    3;165,164,105;,
    3;167,166,5;,
    3;168,167,5;,
    3;123,124,121;,
    3;122,123,121;,
    3;126,123,122;,
    3;125,126,122;,
    3;127,128,125;,
    3;122,127,125;,
    3;129,127,122;,
    3;121,129,122;,
    3;130,131,128;,
    3;127,130,128;,
    3;132,130,127;,
    3;129,132,127;,
    3;135,136,133;,
    3;134,135,133;,
    3;138,135,134;,
    3;137,138,134;,
    3;123,126,137;,
    3;134,123,137;,
    3;124,123,134;,
    3;133,124,134;,
    3;139,140,169;,
    3;170,139,169;,
    3;141,139,170;,
    3;171,141,170;,
    3;130,132,140;,
    3;139,130,140;,
    3;131,130,139;,
    3;141,131,139;,
    3;78,79,136;,
    3;135,78,136;,
    3;80,78,135;,
    3;138,80,135;,
    3;156,109,141;,
    3;171,156,141;,
    3;80,138,117;,
    3;47,80,117;,
    3;118,117,138;,
    3;137,118,138;,
    3;115,118,137;,
    3;126,115,137;,
    3;126,125,113;,
    3;115,126,113;,
    3;125,128,111;,
    3;113,125,111;,
    3;128,131,108;,
    3;111,128,108;,
    3;109,108,131;,
    3;141,109,131;;
   }
   MeshTextureCoords
   {
    172;
    0.805168;0.102527;,
    0.689316;0.147816;,
    0.683167;0.171064;,
    0.649175;0.210259;,
    0.649761;0.253467;,
    0.617068;0.210611;,
    0.617068;0.253464;,
    0.718396;0.106853;,
    0.703107;0.156593;,
    0.709493;0.165094;,
    0.778113;0.162287;,
    0.753084;0.156378;,
    0.776514;0.109658;,
    0.749209;0.117043;,
    0.741273;0.217318;,
    0.772909;0.218689;,
    0.724196;0.185005;,
    0.698964;0.172819;,
    0.691115;0.212790;,
    0.717040;0.215247;,
    0.737245;0.097479;,
    0.749992;0.084613;,
    0.733697;0.090599;,
    0.805168;0.092264;,
    0.805168;0.098106;,
    0.694997;0.148094;,
    0.734025;0.253467;,
    0.711310;0.253464;,
    0.689065;0.176148;,
    0.694881;0.174487;,
    0.769917;0.253464;,
    0.686361;0.253467;,
    0.679837;0.253467;,
    0.681532;0.212052;,
    0.670075;0.253464;,
    0.668170;0.211314;,
    0.805168;0.237191;,
    0.805168;0.218200;,
    0.805168;0.165332;,
    0.362159;0.290275;,
    0.362159;0.233958;,
    0.408382;0.291264;,
    0.362159;0.331771;,
    0.430542;0.320681;,
    0.362159;0.370724;,
    0.764109;0.295385;,
    0.805168;0.290231;,
    0.617068;0.295385;,
    0.655708;0.295387;,
    0.673510;0.295385;,
    0.681938;0.295387;,
    0.689313;0.295387;,
    0.705591;0.295385;,
    0.726639;0.295387;,
    0.691626;0.379577;,
    0.690883;0.316760;,
    0.691259;0.313013;,
    0.702774;0.379586;,
    0.702062;0.316760;,
    0.702453;0.313040;,
    0.675908;0.379614;,
    0.675457;0.316807;,
    0.675244;0.313098;,
    0.683668;0.379598;,
    0.683251;0.316784;,
    0.683144;0.313060;,
    0.805168;0.379627;,
    0.805169;0.316808;,
    0.805168;0.313135;,
    0.760044;0.379625;,
    0.759161;0.316785;,
    0.760101;0.313155;,
    0.659982;0.363022;,
    0.659480;0.316832;,
    0.659649;0.313077;,
    0.722772;0.379622;,
    0.721885;0.316780;,
    0.722703;0.313150;,
    0.617068;0.347218;,
    0.617068;0.316800;,
    0.617068;0.313002;,
    0.315936;0.291264;,
    0.293775;0.320681;,
    0.584376;0.253467;,
    0.584962;0.210259;,
    0.515741;0.106853;,
    0.531030;0.156593;,
    0.524644;0.165094;,
    0.481053;0.156378;,
    0.456024;0.162287;,
    0.457623;0.109658;,
    0.484929;0.117043;,
    0.492864;0.217318;,
    0.461228;0.218689;,
    0.509941;0.185005;,
    0.535174;0.172819;,
    0.543022;0.212790;,
    0.517097;0.215247;,
    0.484145;0.084613;,
    0.496892;0.097479;,
    0.500440;0.090599;,
    0.539140;0.148094;,
    0.544821;0.147816;,
    0.522827;0.253464;,
    0.500112;0.253467;,
    0.550970;0.171064;,
    0.545072;0.176148;,
    0.539256;0.174487;,
    0.507498;0.295387;,
    0.470028;0.295385;,
    0.464219;0.253464;,
    0.528546;0.295385;,
    0.547776;0.253467;,
    0.544824;0.295387;,
    0.554300;0.253467;,
    0.552199;0.295387;,
    0.552604;0.212052;,
    0.578429;0.295387;,
    0.560627;0.295385;,
    0.564062;0.253464;,
    0.565967;0.211314;,
    0.543254;0.316760;,
    0.542510;0.379577;,
    0.550469;0.379598;,
    0.550886;0.316784;,
    0.542877;0.313013;,
    0.550993;0.313060;,
    0.531363;0.379586;,
    0.531683;0.313040;,
    0.532075;0.316760;,
    0.511365;0.379622;,
    0.511434;0.313150;,
    0.512252;0.316780;,
    0.558679;0.316807;,
    0.558229;0.379614;,
    0.574154;0.363022;,
    0.574657;0.316832;,
    0.558893;0.313098;,
    0.574488;0.313077;,
    0.474093;0.379625;,
    0.474977;0.316785;,
    0.474036;0.313155;,
    0.689316;0.147816;,
    0.805168;0.104577;,
    0.692608;0.150083;,
    0.683167;0.171064;,
    0.692608;0.150083;,
    0.685192;0.173443;,
    0.617068;0.210611;,
    0.685192;0.173443;,
    0.617068;0.213182;,
    0.362159;0.233958;,
    0.428969;0.098106;,
    0.428969;0.092264;,
    0.428969;0.102527;,
    0.428969;0.237191;,
    0.428969;0.290231;,
    0.428969;0.218200;,
    0.428969;0.165332;,
    0.362159;0.370724;,
    0.541529;0.150083;,
    0.428970;0.104577;,
    0.428969;0.102527;,
    0.548945;0.173443;,
    0.541529;0.150083;,
    0.544821;0.147816;,
    0.617068;0.213182;,
    0.548945;0.173443;,
    0.550970;0.171064;,
    0.428970;0.316808;,
    0.428969;0.379627;,
    0.428969;0.313135;;
   }
   MeshMaterialList
   {
    1;
    266;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
    172;
    142;
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
    137,
    138,
    139,
    140,
    141,
    1,
    40,
    41,
    2,
    41,
    43,
    5,
    43,
    44,
    40,
    24,
    23,
    0,
    36,
    46,
    37,
    38,
    44,
    81,
    40,
    0,
    82,
    81,
    102,
    44,
    82,
    105,
    67,
    66,
    68;
   }
  }
 }
}

# Animations definition.

