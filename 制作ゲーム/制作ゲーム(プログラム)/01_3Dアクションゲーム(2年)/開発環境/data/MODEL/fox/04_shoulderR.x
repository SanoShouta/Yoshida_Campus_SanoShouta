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
   112;
   -1.977269;-1.853519;-1.673740;,
   -10.782290;-1.744846;-1.455583;,
   -1.977269;0.713013;-1.607910;,
   -10.782290;0.447620;-1.426598;,
   -1.977269;0.713013;1.167639;,
   -10.782290;0.447620;0.891734;,
   -1.977269;-1.853519;1.233469;,
   -10.782290;-1.744846;0.920720;,
   -5.898483;-2.143960;-1.965658;,
   -5.898483;-2.143960;1.430794;,
   -5.898483;0.677643;1.287573;,
   -5.898483;0.677643;-1.822437;,
   -1.977269;1.407733;-0.220136;,
   -5.898483;1.441400;-0.267432;,
   -10.782290;0.992517;-0.267432;,
   -10.782290;-2.319858;-0.267432;,
   -5.898483;-2.907718;-0.267432;,
   -1.977269;-2.548239;-0.220136;,
   -1.977269;-0.570251;-2.094873;,
   -5.898483;-0.733157;-2.286635;,
   -10.782290;-0.663672;-1.812969;,
   -10.782290;-0.663672;-0.267432;,
   -10.782290;-0.663672;1.278105;,
   -5.898483;-0.733157;1.751771;,
   -1.977269;-0.570251;1.654602;,
   -1.977269;-0.570251;-0.220136;,
   -6.621274;-5.015671;-1.957778;,
   -6.775548;-2.614697;-2.938537;,
   -7.238359;0.965234;2.114268;,
   -7.238359;2.526770;-0.693302;,
   -6.621274;-5.324179;2.502777;,
   -6.775548;-2.614697;3.308809;,
   -6.533123;-6.653271;0.422074;,
   -7.238359;0.703308;-3.009867;,
   -9.176450;-7.432300;0.422074;,
   -9.944768;-5.877524;2.683600;,
   -9.944768;-5.877524;-1.392426;,
   -10.596417;-3.411975;-2.695471;,
   -11.457703;-0.008490;-3.009867;,
   -11.318027;2.316516;-0.693302;,
   -11.457703;0.253448;2.114268;,
   -10.596417;-3.411975;3.308809;,
   -6.077419;-4.443554;-1.763524;,
   -6.224594;-2.571326;-2.682721;,
   -6.666145;2.287652;-0.536089;,
   -6.666145;0.770007;2.039876;,
   -6.224594;-2.571326;3.176909;,
   -6.077419;-4.507626;2.492047;,
   -5.993309;-5.878473;0.506962;,
   -6.666145;0.549640;-2.746192;,
   -9.176435;-7.141461;0.506962;,
   -9.944751;-5.658139;2.583600;,
   -9.944751;-5.658139;-1.224146;,
   -10.236530;-3.355295;-2.439661;,
   -11.457698;-0.140942;-2.746192;,
   -11.318027;1.943249;-0.536089;,
   -11.457703;-0.075922;2.039876;,
   -10.596403;-3.355295;3.095448;,
   -1.106135;-2.076907;-2.575069;,
   -1.337342;-3.491998;-1.716172;,
   -1.542161;1.933850;1.740353;,
   -1.542161;2.828113;-0.570690;,
   -1.535104;-3.491998;2.153727;,
   -1.437759;-2.076907;2.881738;,
   -1.356184;-4.548090;0.322454;,
   -1.345721;1.284894;-2.881738;,
   -1.387139;-3.359015;-1.551460;,
   -1.575817;-2.055337;-2.357310;,
   -1.575817;2.633868;-0.441281;,
   -1.575817;1.771100;1.679118;,
   -1.575817;-2.055337;2.765901;,
   -1.575817;-3.359015;2.140591;,
   -1.474442;-4.366778;0.305677;,
   -1.388405;1.151978;-2.646121;,
   -0.918768;1.543140;-0.385990;,
   -0.738456;-1.187424;-0.032671;,
   -0.913817;-2.399759;0.151365;,
   0.000000;0.000000;0.027721;,
   -0.256675;1.247449;-0.174741;,
   -0.222121;1.129712;0.545438;,
   -0.225185;-0.109613;1.034396;,
   -0.216878;-1.382687;0.145974;,
   -0.233690;-1.090243;0.809670;,
   -0.147382;-1.159445;-0.381183;,
   -0.109761;-0.215692;-0.845036;,
   -0.209835;0.627374;-0.875594;,
   -0.949885;-1.760925;2.407412;,
   -0.972978;2.139764;1.412975;,
   -0.505119;-0.760492;1.675476;,
   -0.495785;1.654340;0.933731;,
   -0.984747;-2.716357;1.814065;,
   -0.513666;-1.842856;1.101088;,
   -0.827520;-3.590283;0.318406;,
   -0.441238;-2.443750;0.176995;,
   -0.986339;2.498846;-0.469958;,
   -0.599644;2.106360;-0.373489;,
   -0.812398;-2.715478;-1.369285;,
   -0.372759;-1.827142;-0.707032;,
   -0.630286;-1.591251;-2.088000;,
   -0.303921;-0.742261;-1.401312;,
   -0.796065;1.195093;-2.359331;,
   -0.489314;0.877075;-1.592227;,
   -10.782290;0.992517;-0.267432;,
   -1.977269;-0.570251;1.654602;,
   -10.782290;-0.663672;-1.812969;,
   -1.977269;1.407733;-0.220136;,
   -10.782290;-2.319858;-0.267432;,
   -10.782290;-0.663672;1.278105;,
   -1.977269;-2.548239;-0.220136;,
   -1.977269;-0.570251;-2.094873;,
   -1.575817;1.771100;1.679118;,
   -1.387139;-3.359015;-1.551460;;
   196;
   3;20,3,11;,
   3;19,20,11;,
   3;14,5,10;,
   3;13,14,10;,
   3;10,5,22;,
   3;23,10,22;,
   3;9,7,15;,
   3;16,9,15;,
   3;22,5,102;,
   3;21,22,102;,
   3;12,4,24;,
   3;25,12,24;,
   3;16,17,6;,
   3;9,16,6;,
   3;23,103,4;,
   3;10,23,4;,
   3;10,4,12;,
   3;13,10,12;,
   3;11,2,18;,
   3;19,11,18;,
   3;13,12,2;,
   3;11,13,2;,
   3;11,3,14;,
   3;13,11,14;,
   3;14,3,104;,
   3;21,14,104;,
   3;15,1,8;,
   3;16,15,8;,
   3;8,0,17;,
   3;16,8,17;,
   3;18,2,105;,
   3;25,18,105;,
   3;19,18,0;,
   3;8,19,0;,
   3;8,1,20;,
   3;19,8,20;,
   3;21,20,1;,
   3;106,21,1;,
   3;15,7,107;,
   3;21,15,107;,
   3;22,7,9;,
   3;23,22,9;,
   3;9,6,103;,
   3;23,9,103;,
   3;25,103,6;,
   3;108,25,6;,
   3;17,0,109;,
   3;25,17,109;,
   3;58,59,26;,
   3;27,58,26;,
   3;29,28,60;,
   3;61,29,60;,
   3;31,30,62;,
   3;63,31,62;,
   3;64,62,30;,
   3;32,64,30;,
   3;61,65,33;,
   3;29,61,33;,
   3;59,64,32;,
   3;26,59,32;,
   3;63,60,28;,
   3;31,63,28;,
   3;27,33,65;,
   3;58,27,65;,
   3;30,35,34;,
   3;32,30,34;,
   3;32,34,36;,
   3;26,32,36;,
   3;26,36,37;,
   3;27,26,37;,
   3;37,38,33;,
   3;27,37,33;,
   3;33,38,39;,
   3;29,33,39;,
   3;39,40,28;,
   3;29,39,28;,
   3;28,40,41;,
   3;31,28,41;,
   3;41,35,30;,
   3;31,41,30;,
   3;67,43,42;,
   3;66,67,42;,
   3;44,68,69;,
   3;45,44,69;,
   3;46,70,71;,
   3;47,46,71;,
   3;72,48,47;,
   3;71,72,47;,
   3;68,44,49;,
   3;73,68,49;,
   3;66,42,48;,
   3;72,66,48;,
   3;70,46,45;,
   3;69,70,45;,
   3;43,67,73;,
   3;49,43,73;,
   3;47,48,50;,
   3;51,47,50;,
   3;48,42,52;,
   3;50,48,52;,
   3;42,43,53;,
   3;52,42,53;,
   3;53,43,49;,
   3;54,53,49;,
   3;49,44,55;,
   3;54,49,55;,
   3;55,44,45;,
   3;56,55,45;,
   3;45,46,57;,
   3;56,45,57;,
   3;57,46,47;,
   3;51,57,47;,
   3;35,51,50;,
   3;34,35,50;,
   3;34,50,52;,
   3;36,34,52;,
   3;36,52,53;,
   3;37,36,53;,
   3;37,53,54;,
   3;38,37,54;,
   3;38,54,55;,
   3;39,38,55;,
   3;39,55,56;,
   3;40,39,56;,
   3;40,56,57;,
   3;41,40,57;,
   3;41,57,51;,
   3;35,41,51;,
   3;70,110,74;,
   3;75,70,74;,
   3;71,70,75;,
   3;76,71,75;,
   3;74,69,68;,
   3;76,72,71;,
   3;79,80,77;,
   3;78,79,77;,
   3;80,82,81;,
   3;77,80,81;,
   3;77,81,83;,
   3;84,77,83;,
   3;78,77,84;,
   3;85,78,84;,
   3;74,68,73;,
   3;75,74,73;,
   3;67,75,73;,
   3;76,75,67;,
   3;111,76,67;,
   3;76,66,72;,
   3;88,89,87;,
   3;86,88,87;,
   3;91,88,86;,
   3;90,91,86;,
   3;93,91,90;,
   3;92,93,90;,
   3;89,95,94;,
   3;87,89,94;,
   3;97,93,92;,
   3;96,97,92;,
   3;99,97,96;,
   3;98,99,96;,
   3;101,99,98;,
   3;100,101,98;,
   3;95,101,100;,
   3;94,95,100;,
   3;86,87,60;,
   3;63,86,60;,
   3;89,88,80;,
   3;79,89,80;,
   3;90,86,63;,
   3;62,90,63;,
   3;88,91,82;,
   3;80,88,82;,
   3;92,90,62;,
   3;64,92,62;,
   3;91,93,81;,
   3;82,91,81;,
   3;87,94,61;,
   3;60,87,61;,
   3;95,89,79;,
   3;78,95,79;,
   3;96,92,64;,
   3;59,96,64;,
   3;93,97,83;,
   3;81,93,83;,
   3;98,96,59;,
   3;58,98,59;,
   3;97,99,84;,
   3;83,97,84;,
   3;100,98,58;,
   3;65,100,58;,
   3;99,101,85;,
   3;84,99,85;,
   3;94,100,65;,
   3;61,94,65;,
   3;101,95,78;,
   3;85,101,78;;
   MeshNormals
   {
    112;
    0.542250;-0.543294;-0.640934;,
    -0.561293;-0.534863;-0.631563;,
    0.494925;0.576555;-0.650103;,
    -0.536925;0.559253;-0.631623;,
    0.482636;0.581049;0.655320;,
    -0.536925;0.559253;0.631623;,
    0.530943;-0.547844;0.646504;,
    -0.561293;-0.534863;0.631563;,
    -0.015757;-0.646360;-0.762870;,
    -0.024794;-0.646183;0.762780;,
    -0.039994;0.662644;0.747866;,
    -0.030833;0.662901;-0.748072;,
    0.494209;0.869343;0.000021;,
    -0.039135;0.999234;0.000012;,
    -0.542059;0.840341;-0.000000;,
    -0.563244;-0.826290;-0.000000;,
    -0.014261;-0.999898;0.000114;,
    0.545363;-0.838200;0.000190;,
    0.505244;0.030382;-0.862442;,
    -0.022440;0.031469;-0.999253;,
    -0.533719;0.023461;-0.845336;,
    -1.000000;0.000000;-0.000000;,
    -0.533719;0.023461;0.845336;,
    -0.034316;0.031431;0.998917;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    0.154484;-0.637946;-0.754427;,
    0.042521;-0.253273;-0.966460;,
    -0.055192;0.632328;0.772732;,
    -0.092053;0.991894;-0.087590;,
    0.197517;-0.588719;0.783835;,
    0.049481;-0.005129;0.998762;,
    0.296058;-0.955040;-0.015726;,
    -0.028790;0.406094;-0.913378;,
    -0.665873;-0.744606;-0.046639;,
    -0.710537;-0.554702;0.432946;,
    -0.753577;-0.558081;-0.347373;,
    -0.831579;-0.286089;-0.476057;,
    -0.833202;0.205996;-0.513167;,
    -0.802331;0.594131;-0.057214;,
    -0.747985;0.337251;0.571646;,
    -0.703102;-0.124599;0.700088;,
    -0.162227;0.649778;0.742611;,
    -0.048424;0.264792;0.963089;,
    0.104964;-0.991832;0.072473;,
    0.063014;-0.622890;-0.779767;,
    -0.044965;0.009026;-0.998948;,
    -0.196684;0.584675;-0.787065;,
    -0.303659;0.952780;0.001125;,
    0.032379;-0.408246;0.912297;,
    -0.867489;0.497436;-0.004534;,
    -0.705881;0.256716;-0.660173;,
    -0.630250;0.353086;0.691459;,
    -0.533552;0.115290;0.837873;,
    -0.618484;-0.310090;0.722026;,
    -0.757633;-0.652179;0.025575;,
    -0.685820;-0.502331;-0.526607;,
    -0.695864;-0.155472;-0.701143;,
    0.483498;-0.255916;-0.837100;,
    0.585232;-0.588934;-0.557369;,
    0.183649;0.680121;0.709724;,
    0.167447;0.981052;-0.097457;,
    0.564755;-0.534310;0.628940;,
    0.409697;-0.051742;0.910753;,
    0.671950;-0.739773;0.034911;,
    0.369195;0.437513;-0.819925;,
    -0.522790;0.625148;0.579552;,
    -0.646944;0.198197;0.736329;,
    -0.485448;-0.871921;0.063985;,
    -0.309832;-0.692697;-0.651288;,
    -0.649078;0.027996;-0.760207;,
    -0.688386;0.461007;-0.559997;,
    -0.740216;0.671506;-0.034059;,
    -0.592152;-0.402900;0.697873;,
    -0.957997;-0.286774;0.001565;,
    -0.999307;0.035889;-0.009878;,
    -0.981390;0.190936;-0.020443;,
    0.999358;0.023710;0.026844;,
    0.965291;0.256931;-0.046911;,
    0.947175;0.239811;0.212955;,
    0.963718;0.022293;0.265990;,
    0.983420;-0.170733;0.061124;,
    0.964161;-0.155151;0.215224;,
    0.979253;-0.178864;-0.095242;,
    0.982697;-0.017976;-0.184343;,
    0.952871;0.185869;-0.239771;,
    0.786358;-0.037166;0.616652;,
    0.615735;0.576173;0.537490;,
    0.890369;-0.002122;0.455235;,
    0.860950;0.373146;0.345727;,
    0.871574;-0.323305;0.368556;,
    0.935493;-0.219422;0.276959;,
    0.915922;-0.397870;0.052787;,
    0.958346;-0.279083;0.060711;,
    0.623622;0.776917;-0.086570;,
    0.871803;0.482187;-0.086340;,
    0.895477;-0.362756;-0.257931;,
    0.954543;-0.249807;-0.162619;,
    0.876765;-0.161073;-0.453143;,
    0.945849;-0.078604;-0.314946;,
    0.800041;0.326174;-0.503532;,
    0.911772;0.232327;-0.338669;,
    -1.000000;0.000000;-0.000000;,
    0.489317;0.030652;0.871567;,
    -1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    -0.948079;-0.093221;-0.304067;,
    -0.958692;0.099169;0.266599;;
    196;
    3;20,3,11;,
    3;19,20,11;,
    3;14,5,10;,
    3;13,14,10;,
    3;10,5,22;,
    3;23,10,22;,
    3;9,7,15;,
    3;16,9,15;,
    3;22,5,102;,
    3;21,22,102;,
    3;12,4,24;,
    3;25,12,24;,
    3;16,17,6;,
    3;9,16,6;,
    3;23,103,4;,
    3;10,23,4;,
    3;10,4,12;,
    3;13,10,12;,
    3;11,2,18;,
    3;19,11,18;,
    3;13,12,2;,
    3;11,13,2;,
    3;11,3,14;,
    3;13,11,14;,
    3;14,3,104;,
    3;21,14,104;,
    3;15,1,8;,
    3;16,15,8;,
    3;8,0,17;,
    3;16,8,17;,
    3;18,2,105;,
    3;25,18,105;,
    3;19,18,0;,
    3;8,19,0;,
    3;8,1,20;,
    3;19,8,20;,
    3;21,20,1;,
    3;106,21,1;,
    3;15,7,107;,
    3;21,15,107;,
    3;22,7,9;,
    3;23,22,9;,
    3;9,6,103;,
    3;23,9,103;,
    3;25,103,6;,
    3;108,25,6;,
    3;17,0,109;,
    3;25,17,109;,
    3;58,59,26;,
    3;27,58,26;,
    3;29,28,60;,
    3;61,29,60;,
    3;31,30,62;,
    3;63,31,62;,
    3;64,62,30;,
    3;32,64,30;,
    3;61,65,33;,
    3;29,61,33;,
    3;59,64,32;,
    3;26,59,32;,
    3;63,60,28;,
    3;31,63,28;,
    3;27,33,65;,
    3;58,27,65;,
    3;30,35,34;,
    3;32,30,34;,
    3;32,34,36;,
    3;26,32,36;,
    3;26,36,37;,
    3;27,26,37;,
    3;37,38,33;,
    3;27,37,33;,
    3;33,38,39;,
    3;29,33,39;,
    3;39,40,28;,
    3;29,39,28;,
    3;28,40,41;,
    3;31,28,41;,
    3;41,35,30;,
    3;31,41,30;,
    3;67,43,42;,
    3;66,67,42;,
    3;44,68,69;,
    3;45,44,69;,
    3;46,70,71;,
    3;47,46,71;,
    3;72,48,47;,
    3;71,72,47;,
    3;68,44,49;,
    3;73,68,49;,
    3;66,42,48;,
    3;72,66,48;,
    3;70,46,45;,
    3;69,70,45;,
    3;43,67,73;,
    3;49,43,73;,
    3;47,48,50;,
    3;51,47,50;,
    3;48,42,52;,
    3;50,48,52;,
    3;42,43,53;,
    3;52,42,53;,
    3;53,43,49;,
    3;54,53,49;,
    3;49,44,55;,
    3;54,49,55;,
    3;55,44,45;,
    3;56,55,45;,
    3;45,46,57;,
    3;56,45,57;,
    3;57,46,47;,
    3;51,57,47;,
    3;35,51,50;,
    3;34,35,50;,
    3;34,50,52;,
    3;36,34,52;,
    3;36,52,53;,
    3;37,36,53;,
    3;37,53,54;,
    3;38,37,54;,
    3;38,54,55;,
    3;39,38,55;,
    3;39,55,56;,
    3;40,39,56;,
    3;40,56,57;,
    3;41,40,57;,
    3;41,57,51;,
    3;35,41,51;,
    3;70,110,74;,
    3;75,70,74;,
    3;71,70,75;,
    3;76,71,75;,
    3;74,69,68;,
    3;76,72,71;,
    3;79,80,77;,
    3;78,79,77;,
    3;80,82,81;,
    3;77,80,81;,
    3;77,81,83;,
    3;84,77,83;,
    3;78,77,84;,
    3;85,78,84;,
    3;74,68,73;,
    3;75,74,73;,
    3;67,75,73;,
    3;76,75,67;,
    3;111,76,67;,
    3;76,66,72;,
    3;88,89,87;,
    3;86,88,87;,
    3;91,88,86;,
    3;90,91,86;,
    3;93,91,90;,
    3;92,93,90;,
    3;89,95,94;,
    3;87,89,94;,
    3;97,93,92;,
    3;96,97,92;,
    3;99,97,96;,
    3;98,99,96;,
    3;101,99,98;,
    3;100,101,98;,
    3;95,101,100;,
    3;94,95,100;,
    3;86,87,60;,
    3;63,86,60;,
    3;89,88,80;,
    3;79,89,80;,
    3;90,86,63;,
    3;62,90,63;,
    3;88,91,82;,
    3;80,88,82;,
    3;92,90,62;,
    3;64,92,62;,
    3;91,93,81;,
    3;82,91,81;,
    3;87,94,61;,
    3;60,87,61;,
    3;95,89,79;,
    3;78,95,79;,
    3;96,92,64;,
    3;59,96,64;,
    3;93,97,83;,
    3;81,93,83;,
    3;98,96,59;,
    3;58,98,59;,
    3;97,99,84;,
    3;83,97,84;,
    3;100,98,58;,
    3;65,100,58;,
    3;99,101,85;,
    3;84,99,85;,
    3;94,100,65;,
    3;61,94,65;,
    3;101,95,78;,
    3;85,101,78;;
   }
   MeshTextureCoords
   {
    112;
    0.012931;0.260992;,
    0.101914;0.255847;,
    0.012931;0.226422;,
    0.101914;0.231229;,
    0.012931;0.226422;,
    0.101914;0.231229;,
    0.012931;0.260992;,
    0.101914;0.255847;,
    0.057422;0.260992;,
    0.057422;0.260992;,
    0.057422;0.226422;,
    0.057422;0.226422;,
    0.012931;0.217065;,
    0.057422;0.217065;,
    0.101914;0.225111;,
    0.101914;0.262303;,
    0.057422;0.270349;,
    0.012931;0.270349;,
    0.012931;0.243707;,
    0.057422;0.243707;,
    0.101914;0.243707;,
    0.101914;0.243707;,
    0.101914;0.243707;,
    0.057422;0.243707;,
    0.012931;0.243707;,
    0.012931;0.243707;,
    0.934989;0.244853;,
    0.936481;0.205469;,
    0.940956;0.153922;,
    0.940956;0.143099;,
    0.934989;0.247403;,
    0.936481;0.205469;,
    0.934136;0.263409;,
    0.940956;0.156890;,
    0.954787;0.266482;,
    0.959064;0.248865;,
    0.959064;0.248865;,
    0.968518;0.208749;,
    0.976847;0.170186;,
    0.975497;0.150712;,
    0.976847;0.167218;,
    0.968518;0.208749;,
    0.929730;0.238371;,
    0.931153;0.204978;,
    0.935423;0.145809;,
    0.935423;0.156134;,
    0.931153;0.204978;,
    0.929730;0.244984;,
    0.928916;0.260254;,
    0.935423;0.158631;,
    0.954787;0.263186;,
    0.959064;0.246380;,
    0.959064;0.246380;,
    0.965038;0.208107;,
    0.976847;0.171686;,
    0.975497;0.154941;,
    0.976847;0.170950;,
    0.968518;0.208107;,
    0.882977;0.202189;,
    0.887810;0.240471;,
    0.892091;0.138853;,
    0.892091;0.131601;,
    0.891943;0.240471;,
    0.889909;0.202189;,
    0.888203;0.257149;,
    0.887985;0.149101;,
    0.888851;0.238371;,
    0.892794;0.201848;,
    0.892794;0.134668;,
    0.892794;0.141423;,
    0.892794;0.201848;,
    0.892794;0.238371;,
    0.890675;0.254285;,
    0.888877;0.151200;,
    0.879060;0.156621;,
    0.875291;0.199741;,
    0.878957;0.227951;,
    0.859855;0.195012;,
    0.865220;0.170896;,
    0.864498;0.172755;,
    0.864562;0.196743;,
    0.864389;0.215067;,
    0.864740;0.210449;,
    0.862936;0.210139;,
    0.862150;0.194001;,
    0.864241;0.175512;,
    0.879711;0.201928;,
    0.880193;0.147200;,
    0.870414;0.198096;,
    0.870219;0.160354;,
    0.880439;0.232951;,
    0.870592;0.221275;,
    0.877153;0.246752;,
    0.869078;0.234135;,
    0.880473;0.141529;,
    0.872390;0.153216;,
    0.876837;0.232937;,
    0.867647;0.220699;,
    0.873030;0.199248;,
    0.866208;0.195447;,
    0.876495;0.155247;,
    0.870083;0.165758;,
    0.101914;0.225111;,
    0.012931;0.243707;,
    0.101914;0.243707;,
    0.012931;0.217065;,
    0.101914;0.262303;,
    0.101914;0.243707;,
    0.012931;0.270349;,
    0.012931;0.243707;,
    0.892794;0.141423;,
    0.888851;0.238371;;
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
    112;
    102;
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
    14,
    24,
    20,
    12,
    15,
    22,
    17,
    18,
    69,
    66;
   }
  }
 }
}

# Animations definition.

