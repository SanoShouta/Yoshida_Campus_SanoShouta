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
  "data/TEXTURE/kappa.jpg";
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
   -4.418987,-41.642281,-0.000000,1.000000;;
  }
  Mesh
  {
   112;
   12.866156;36.233322;-3.476874;,
   13.033879;40.661247;-5.323160;,
   13.537048;46.456585;3.848513;,
   13.537048;47.673412;-0.625178;,
   12.866156;35.946682;5.284497;,
   13.033879;40.661247;6.871460;,
   12.770317;34.147205;1.197603;,
   13.537048;46.122913;-4.316483;,
   15.092068;33.801678;1.197603;,
   15.572925;35.782276;5.639670;,
   15.572925;35.782276;-2.366416;,
   16.635853;40.292469;-4.848704;,
   17.572241;44.628113;-4.316483;,
   17.420385;46.817520;-0.625178;,
   17.572241;44.961792;3.848513;,
   16.635853;40.292469;6.871460;,
   12.274878;36.962124;-3.095324;,
   12.434888;40.716499;-4.823816;,
   12.914940;47.368801;-0.374669;,
   12.914940;46.207890;3.729976;,
   12.434888;40.716499;6.613998;,
   12.274878;36.218601;5.263421;,
   12.183434;34.501820;1.364341;,
   12.914940;45.927162;-3.896332;,
   15.092052;34.172173;1.364341;,
   15.572906;36.061752;5.443249;,
   15.572906;36.061752;-2.035883;,
   16.244585;40.364674;-4.349371;,
   17.572239;44.459385;-3.896332;,
   17.420385;46.342014;-0.374669;,
   17.572241;44.542206;3.729976;,
   16.635838;40.364674;6.454987;,
   7.018506;41.030018;-5.693613;,
   7.561859;36.726021;-3.726548;,
   8.043203;48.150810;3.848513;,
   8.043203;48.966122;-0.625178;,
   8.026618;36.726021;5.507781;,
   7.797846;41.030018;7.246374;,
   7.606141;34.851006;1.138010;,
   7.581553;46.998642;-5.098876;,
   7.678888;36.962124;-3.333512;,
   8.122297;41.068325;-5.177231;,
   8.122297;48.621258;-0.374669;,
   8.122297;47.861870;3.729976;,
   8.122297;41.068325;6.971685;,
   8.122297;36.962124;5.476437;,
   7.884057;35.172913;1.097975;,
   7.681863;46.762650;-4.642773;,
   6.578174;46.153152;-0.267639;,
   6.154424;41.305252;0.335297;,
   6.566539;38.133614;0.729756;,
   4.418987;41.836887;0.478506;,
   5.022196;44.548237;0.141295;,
   4.940993;44.339207;1.535408;,
   4.948192;41.642281;2.865683;,
   4.928669;39.582199;0.758925;,
   4.968180;40.101402;2.332781;,
   4.765346;40.136230;-0.678537;,
   4.676937;41.950550;-1.384503;,
   4.912120;44.029243;-1.215409;,
   6.651301;41.059429;6.121581;,
   6.705573;47.212410;3.214776;,
   5.606063;41.490204;4.385907;,
   5.584126;45.733475;2.287063;,
   6.733230;37.571510;4.697281;,
   5.626149;38.884258;3.495398;,
   6.363733;36.019924;1.128349;,
   5.455937;37.438396;0.790915;,
   6.736971;47.849941;-0.430183;,
   5.828205;46.535999;-0.243439;,
   6.328195;37.573067;-2.898808;,
   5.295005;38.948952;-1.789909;,
   5.900217;41.360672;-4.538604;,
   5.133230;41.788040;-2.910227;,
   6.289811;46.307610;-4.087610;,
   5.568918;45.125889;-2.602659;,
   9.065743;41.187160;-2.533726;,
   20.149496;41.828011;-1.980625;,
   9.065743;45.493103;-2.418981;,
   20.149496;44.894360;-1.932307;,
   9.065743;45.493103;2.418981;,
   20.149496;44.894360;1.932307;,
   9.065743;41.187160;2.533726;,
   20.149496;41.828011;1.980625;,
   14.607618;41.187160;-3.088943;,
   14.607618;41.187160;3.088943;,
   14.607618;45.493103;2.828437;,
   14.607618;45.493103;-2.828437;,
   9.065743;46.658646;-0.000000;,
   14.607618;46.658646;-0.000000;,
   20.149496;45.656448;-0.000000;,
   20.149496;41.023819;-0.000000;,
   14.607618;40.021618;-0.000000;,
   9.065743;40.021618;-0.000000;,
   9.065743;43.340130;-3.267788;,
   14.607618;43.340130;-3.672778;,
   20.149496;43.340130;-2.576380;,
   20.149496;43.340130;-0.000000;,
   20.149496;43.340130;2.576380;,
   14.607618;43.340130;3.672778;,
   9.065743;43.340130;3.267788;,
   9.065743;43.340130;-0.000000;,
   8.122297;47.861870;3.729976;,
   7.678888;36.962124;-3.333512;,
   20.149496;43.340130;2.576380;,
   9.065743;46.658646;-0.000000;,
   20.149496;45.656448;-0.000000;,
   9.065743;43.340130;-3.267788;,
   20.149496;43.340130;-2.576380;,
   20.149496;41.023819;-0.000000;,
   9.065743;43.340130;3.267788;,
   9.065743;40.021618;-0.000000;;
   196;
   3;32,1,0;,
   3;33,32,0;,
   3;3,35,34;,
   3;2,3,34;,
   3;5,37,36;,
   3;4,5,36;,
   3;38,6,4;,
   3;36,38,4;,
   3;35,3,7;,
   3;39,35,7;,
   3;33,0,6;,
   3;38,33,6;,
   3;37,5,2;,
   3;34,37,2;,
   3;1,32,39;,
   3;7,1,39;,
   3;4,6,8;,
   3;9,4,8;,
   3;6,0,10;,
   3;8,6,10;,
   3;0,1,11;,
   3;10,0,11;,
   3;11,1,7;,
   3;12,11,7;,
   3;7,3,13;,
   3;12,7,13;,
   3;13,3,2;,
   3;14,13,2;,
   3;2,5,15;,
   3;14,2,15;,
   3;15,5,4;,
   3;9,15,4;,
   3;41,40,16;,
   3;17,41,16;,
   3;18,19,43;,
   3;42,18,43;,
   3;20,21,45;,
   3;44,20,45;,
   3;46,45,21;,
   3;22,46,21;,
   3;42,47,23;,
   3;18,42,23;,
   3;40,46,22;,
   3;16,40,22;,
   3;44,43,19;,
   3;20,44,19;,
   3;17,23,47;,
   3;41,17,47;,
   3;21,25,24;,
   3;22,21,24;,
   3;22,24,26;,
   3;16,22,26;,
   3;16,26,27;,
   3;17,16,27;,
   3;27,28,23;,
   3;17,27,23;,
   3;23,28,29;,
   3;18,23,29;,
   3;29,30,19;,
   3;18,29,19;,
   3;19,30,31;,
   3;20,19,31;,
   3;31,25,21;,
   3;20,31,21;,
   3;9,8,24;,
   3;25,9,24;,
   3;8,10,26;,
   3;24,8,26;,
   3;10,11,27;,
   3;26,10,27;,
   3;11,12,28;,
   3;27,11,28;,
   3;12,13,29;,
   3;28,12,29;,
   3;13,14,30;,
   3;29,13,30;,
   3;14,15,31;,
   3;30,14,31;,
   3;15,9,25;,
   3;31,15,25;,
   3;44,49,48;,
   3;43,44,48;,
   3;45,50,49;,
   3;44,45,49;,
   3;102,48,42;,
   3;46,50,45;,
   3;53,52,51;,
   3;54,53,51;,
   3;54,51,55;,
   3;56,54,55;,
   3;51,58,57;,
   3;55,51,57;,
   3;52,59,58;,
   3;51,52,58;,
   3;42,48,47;,
   3;49,41,47;,
   3;48,49,47;,
   3;50,40,41;,
   3;49,50,41;,
   3;103,50,46;,
   3;62,60,61;,
   3;63,62,61;,
   3;65,64,60;,
   3;62,65,60;,
   3;67,66,64;,
   3;65,67,64;,
   3;63,61,68;,
   3;69,63,68;,
   3;71,70,66;,
   3;67,71,66;,
   3;73,72,70;,
   3;71,73,70;,
   3;75,74,72;,
   3;73,75,72;,
   3;69,68,74;,
   3;75,69,74;,
   3;60,37,34;,
   3;61,60,34;,
   3;63,53,54;,
   3;62,63,54;,
   3;64,36,37;,
   3;60,64,37;,
   3;62,54,56;,
   3;65,62,56;,
   3;66,38,36;,
   3;64,66,36;,
   3;65,56,55;,
   3;67,65,55;,
   3;61,34,35;,
   3;68,61,35;,
   3;69,52,53;,
   3;63,69,53;,
   3;70,33,38;,
   3;66,70,38;,
   3;67,55,57;,
   3;71,67,57;,
   3;72,32,33;,
   3;70,72,33;,
   3;71,57,58;,
   3;73,71,58;,
   3;74,39,32;,
   3;72,74,32;,
   3;73,58,59;,
   3;75,73,59;,
   3;68,35,39;,
   3;74,68,39;,
   3;75,59,52;,
   3;69,75,52;,
   3;96,95,87;,
   3;79,96,87;,
   3;90,89,86;,
   3;81,90,86;,
   3;86,99,98;,
   3;81,86,98;,
   3;85,92,91;,
   3;83,85,91;,
   3;104,97,90;,
   3;81,104,90;,
   3;88,101,100;,
   3;80,88,100;,
   3;92,85,82;,
   3;93,92,82;,
   3;99,86,80;,
   3;100,99,80;,
   3;86,89,105;,
   3;80,86,105;,
   3;87,95,94;,
   3;78,87,94;,
   3;89,87,78;,
   3;105,89,78;,
   3;87,89,90;,
   3;79,87,90;,
   3;106,97,96;,
   3;79,106,96;,
   3;91,92,84;,
   3;77,91,84;,
   3;84,92,93;,
   3;76,84,93;,
   3;107,101,105;,
   3;78,107,105;,
   3;95,84,76;,
   3;94,95,76;,
   3;84,95,96;,
   3;77,84,96;,
   3;97,91,77;,
   3;108,97,77;,
   3;109,97,98;,
   3;83,109,98;,
   3;98,99,85;,
   3;83,98,85;,
   3;85,99,100;,
   3;82,85,100;,
   3;101,93,82;,
   3;110,101,82;,
   3;111,101,94;,
   3;76,111,94;;
   MeshNormals
   {
    112;
    0.009601;-0.711655;-0.702464;,
    0.101894;-0.152369;-0.983057;,
    0.205314;0.757016;0.620301;,
    0.259173;0.962416;-0.081148;,
    -0.087692;-0.665846;0.740917;,
    0.043700;0.082463;0.995636;,
    -0.109942;-0.993914;-0.006828;,
    0.186285;0.577818;-0.794622;,
    0.695157;-0.718496;-0.022828;,
    0.703373;-0.551976;0.447871;,
    0.777785;-0.533019;-0.333080;,
    0.844634;-0.225876;-0.485359;,
    0.860179;0.290943;-0.418860;,
    0.812276;0.581576;-0.044456;,
    0.804085;0.422580;0.418179;,
    0.742613;-0.049622;0.667880;,
    -0.003716;0.698211;0.715882;,
    -0.095015;0.159179;0.982667;,
    -0.266255;-0.961435;0.068929;,
    -0.217934;-0.751920;-0.622191;,
    -0.068728;-0.097104;-0.992898;,
    0.066564;0.656714;-0.751196;,
    0.104868;0.994021;0.030402;,
    -0.190547;-0.581740;0.790741;,
    0.785805;0.618101;0.021464;,
    0.739064;0.341480;-0.580669;,
    0.650493;0.432507;0.624337;,
    0.549329;0.023111;0.835286;,
    0.601451;-0.472386;0.644289;,
    0.645576;-0.763022;0.032092;,
    0.639585;-0.621592;-0.452277;,
    0.687538;-0.213619;-0.694016;,
    -0.354505;-0.143003;-0.924054;,
    -0.405598;-0.673900;-0.617535;,
    -0.266817;0.761047;0.591284;,
    -0.229883;0.969470;-0.085334;,
    -0.399041;-0.626331;0.669684;,
    -0.336412;0.039582;0.940883;,
    -0.431409;-0.901628;0.030874;,
    -0.312195;0.595312;-0.740363;,
    0.406089;0.597335;0.691580;,
    0.571218;0.120737;0.811870;,
    0.379089;-0.922852;0.068087;,
    0.251950;-0.708726;-0.658960;,
    0.585171;-0.054335;-0.809087;,
    0.623695;0.531274;-0.573369;,
    0.610482;0.791932;-0.012478;,
    0.522441;-0.557182;0.645449;,
    0.949127;-0.314766;0.008929;,
    0.999934;0.011477;0.000297;,
    0.966974;0.254263;-0.017649;,
    -0.999491;0.012092;0.029527;,
    -0.960800;0.277192;-0.005306;,
    -0.950597;0.254010;0.178453;,
    -0.966378;0.027992;0.255596;,
    -0.976266;-0.212279;0.042915;,
    -0.957530;-0.184180;0.221841;,
    -0.971416;-0.199108;-0.129258;,
    -0.984599;-0.005605;-0.174735;,
    -0.960544;0.232489;-0.152660;,
    -0.768757;0.028289;0.638915;,
    -0.759275;0.518760;0.392923;,
    -0.883912;0.031081;0.466619;,
    -0.887931;0.367743;0.276304;,
    -0.773866;-0.421669;0.472576;,
    -0.899532;-0.277591;0.337322;,
    -0.781927;-0.622149;0.039001;,
    -0.915201;-0.400612;0.043782;,
    -0.754109;0.655650;-0.037971;,
    -0.887900;0.459137;-0.028743;,
    -0.785678;-0.474494;-0.396945;,
    -0.917603;-0.308652;-0.250479;,
    -0.819096;-0.090568;-0.566463;,
    -0.932077;-0.033972;-0.360663;,
    -0.824213;0.394209;-0.406536;,
    -0.925753;0.289732;-0.242976;,
    -0.521216;-0.573269;-0.632216;,
    0.612864;-0.544490;-0.572651;,
    -0.505164;0.596555;-0.623644;,
    0.596066;0.568262;-0.567261;,
    -0.505851;0.596277;0.623353;,
    0.596066;0.568262;0.567261;,
    -0.520001;-0.573743;0.632786;,
    0.612864;-0.544490;0.572651;,
    0.076500;-0.678378;-0.730720;,
    0.077465;-0.678313;0.730678;,
    0.071205;0.697673;0.712869;,
    0.071736;0.697646;-0.712842;,
    -1.000000;0.000000;-0.000000;,
    0.079775;0.996813;-0.000007;,
    0.585683;0.810540;-0.000000;,
    0.591711;-0.806150;-0.000000;,
    0.083333;-0.996522;0.000013;,
    -0.490573;-0.871400;0.000023;,
    -0.521521;0.033390;-0.852585;,
    0.063993;0.035782;-0.997309;,
    0.602372;0.025945;-0.797794;,
    1.000000;0.000000;-0.000000;,
    0.602372;0.025945;0.797794;,
    0.064058;0.035797;0.997304;,
    -0.521431;0.033418;0.852638;,
    -1.000000;0.000000;-0.000000;,
    0.841738;-0.530877;-0.098216;,
    0.900355;0.416384;0.126430;,
    1.000000;0.000000;-0.000000;,
    -0.491340;0.870968;-0.000011;,
    1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;,
    -1.000000;0.000000;-0.000000;;
    196;
    3;32,1,0;,
    3;33,32,0;,
    3;3,35,34;,
    3;2,3,34;,
    3;5,37,36;,
    3;4,5,36;,
    3;38,6,4;,
    3;36,38,4;,
    3;35,3,7;,
    3;39,35,7;,
    3;33,0,6;,
    3;38,33,6;,
    3;37,5,2;,
    3;34,37,2;,
    3;1,32,39;,
    3;7,1,39;,
    3;4,6,8;,
    3;9,4,8;,
    3;6,0,10;,
    3;8,6,10;,
    3;0,1,11;,
    3;10,0,11;,
    3;11,1,7;,
    3;12,11,7;,
    3;7,3,13;,
    3;12,7,13;,
    3;13,3,2;,
    3;14,13,2;,
    3;2,5,15;,
    3;14,2,15;,
    3;15,5,4;,
    3;9,15,4;,
    3;41,40,16;,
    3;17,41,16;,
    3;18,19,43;,
    3;42,18,43;,
    3;20,21,45;,
    3;44,20,45;,
    3;46,45,21;,
    3;22,46,21;,
    3;42,47,23;,
    3;18,42,23;,
    3;40,46,22;,
    3;16,40,22;,
    3;44,43,19;,
    3;20,44,19;,
    3;17,23,47;,
    3;41,17,47;,
    3;21,25,24;,
    3;22,21,24;,
    3;22,24,26;,
    3;16,22,26;,
    3;16,26,27;,
    3;17,16,27;,
    3;27,28,23;,
    3;17,27,23;,
    3;23,28,29;,
    3;18,23,29;,
    3;29,30,19;,
    3;18,29,19;,
    3;19,30,31;,
    3;20,19,31;,
    3;31,25,21;,
    3;20,31,21;,
    3;9,8,24;,
    3;25,9,24;,
    3;8,10,26;,
    3;24,8,26;,
    3;10,11,27;,
    3;26,10,27;,
    3;11,12,28;,
    3;27,11,28;,
    3;12,13,29;,
    3;28,12,29;,
    3;13,14,30;,
    3;29,13,30;,
    3;14,15,31;,
    3;30,14,31;,
    3;15,9,25;,
    3;31,15,25;,
    3;44,49,48;,
    3;43,44,48;,
    3;45,50,49;,
    3;44,45,49;,
    3;102,48,42;,
    3;46,50,45;,
    3;53,52,51;,
    3;54,53,51;,
    3;54,51,55;,
    3;56,54,55;,
    3;51,58,57;,
    3;55,51,57;,
    3;52,59,58;,
    3;51,52,58;,
    3;42,48,47;,
    3;49,41,47;,
    3;48,49,47;,
    3;50,40,41;,
    3;49,50,41;,
    3;103,50,46;,
    3;62,60,61;,
    3;63,62,61;,
    3;65,64,60;,
    3;62,65,60;,
    3;67,66,64;,
    3;65,67,64;,
    3;63,61,68;,
    3;69,63,68;,
    3;71,70,66;,
    3;67,71,66;,
    3;73,72,70;,
    3;71,73,70;,
    3;75,74,72;,
    3;73,75,72;,
    3;69,68,74;,
    3;75,69,74;,
    3;60,37,34;,
    3;61,60,34;,
    3;63,53,54;,
    3;62,63,54;,
    3;64,36,37;,
    3;60,64,37;,
    3;62,54,56;,
    3;65,62,56;,
    3;66,38,36;,
    3;64,66,36;,
    3;65,56,55;,
    3;67,65,55;,
    3;61,34,35;,
    3;68,61,35;,
    3;69,52,53;,
    3;63,69,53;,
    3;70,33,38;,
    3;66,70,38;,
    3;67,55,57;,
    3;71,67,57;,
    3;72,32,33;,
    3;70,72,33;,
    3;71,57,58;,
    3;73,71,58;,
    3;74,39,32;,
    3;72,74,32;,
    3;73,58,59;,
    3;75,73,59;,
    3;68,35,39;,
    3;74,68,39;,
    3;75,59,52;,
    3;69,75,52;,
    3;96,95,87;,
    3;79,96,87;,
    3;90,89,86;,
    3;81,90,86;,
    3;86,99,98;,
    3;81,86,98;,
    3;85,92,91;,
    3;83,85,91;,
    3;104,97,90;,
    3;81,104,90;,
    3;88,101,100;,
    3;80,88,100;,
    3;92,85,82;,
    3;93,92,82;,
    3;99,86,80;,
    3;100,99,80;,
    3;86,89,105;,
    3;80,86,105;,
    3;87,95,94;,
    3;78,87,94;,
    3;89,87,78;,
    3;105,89,78;,
    3;87,89,90;,
    3;79,87,90;,
    3;106,97,96;,
    3;79,106,96;,
    3;91,92,84;,
    3;77,91,84;,
    3;84,92,93;,
    3;76,84,93;,
    3;107,101,105;,
    3;78,107,105;,
    3;95,84,76;,
    3;94,95,76;,
    3;84,95,96;,
    3;77,84,96;,
    3;97,91,77;,
    3;108,97,77;,
    3;109,97,98;,
    3;83,109,98;,
    3;98,99,85;,
    3;83,98,85;,
    3;85,99,100;,
    3;82,85,100;,
    3;101,93,82;,
    3;110,101,82;,
    3;111,101,94;,
    3;76,111,94;;
   }
   MeshTextureCoords
   {
    112;
    0.974674;0.137818;,
    0.975905;0.105306;,
    0.979600;0.062754;,
    0.979600;0.053819;,
    0.974674;0.139923;,
    0.975905;0.105306;,
    0.973970;0.153135;,
    0.979600;0.065204;,
    0.991018;0.155672;,
    0.994548;0.141130;,
    0.994548;0.141130;,
    1.002353;0.108014;,
    1.009228;0.076179;,
    1.008113;0.060104;,
    1.009228;0.073729;,
    1.002353;0.108014;,
    0.970333;0.132467;,
    0.971507;0.104900;,
    0.975032;0.056056;,
    0.975032;0.064580;,
    0.971507;0.104900;,
    0.970333;0.137926;,
    0.969661;0.150531;,
    0.975032;0.066641;,
    0.991018;0.152952;,
    0.994548;0.139078;,
    0.994548;0.139078;,
    0.999480;0.107484;,
    1.009228;0.077418;,
    1.008113;0.063595;,
    1.009228;0.076810;,
    1.002353;0.107484;,
    0.931738;0.102598;,
    0.935727;0.134200;,
    0.939262;0.050314;,
    0.939262;0.044328;,
    0.939140;0.134200;,
    0.937460;0.102598;,
    0.936052;0.147968;,
    0.935872;0.058774;,
    0.936587;0.132467;,
    0.939842;0.102317;,
    0.939842;0.046860;,
    0.939842;0.052436;,
    0.939842;0.102317;,
    0.939842;0.132467;,
    0.938093;0.145604;,
    0.936608;0.060507;,
    0.928505;0.064982;,
    0.925393;0.100577;,
    0.928419;0.123865;,
    0.912651;0.096674;,
    0.917080;0.076766;,
    0.916484;0.078301;,
    0.916537;0.098103;,
    0.916393;0.113229;,
    0.916683;0.109417;,
    0.915194;0.109161;,
    0.914545;0.095839;,
    0.916272;0.080577;,
    0.929042;0.102382;,
    0.929440;0.057204;,
    0.921367;0.099219;,
    0.921206;0.068063;,
    0.929643;0.127992;,
    0.921514;0.118354;,
    0.926930;0.139385;,
    0.920265;0.128970;,
    0.929671;0.052523;,
    0.922998;0.062171;,
    0.926669;0.127981;,
    0.919083;0.117878;,
    0.923527;0.100170;,
    0.917895;0.097033;,
    0.926387;0.063848;,
    0.921094;0.072525;,
    0.705895;0.973738;,
    0.828102;0.966672;,
    0.705895;0.926262;,
    0.828102;0.932863;,
    0.705895;0.926262;,
    0.828102;0.932863;,
    0.705895;0.973738;,
    0.828102;0.966672;,
    0.766998;0.973738;,
    0.766998;0.973738;,
    0.766998;0.926262;,
    0.766998;0.926262;,
    0.705895;0.913411;,
    0.766998;0.913411;,
    0.828102;0.924461;,
    0.828102;0.975539;,
    0.766998;0.986589;,
    0.705895;0.986589;,
    0.705895;0.950000;,
    0.766998;0.950000;,
    0.828102;0.950000;,
    0.828102;0.950000;,
    0.828102;0.950000;,
    0.766998;0.950000;,
    0.705895;0.950000;,
    0.705895;0.950000;,
    0.939842;0.052436;,
    0.936587;0.132467;,
    0.828102;0.950000;,
    0.705895;0.913411;,
    0.828102;0.924461;,
    0.705895;0.950000;,
    0.828102;0.950000;,
    0.828102;0.975539;,
    0.705895;0.950000;,
    0.705895;0.986589;;
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
    43,
    40,
    98,
    88,
    90,
    94,
    96,
    91,
    100,
    93;
   }
  }
 }
}

# Animations definition.

