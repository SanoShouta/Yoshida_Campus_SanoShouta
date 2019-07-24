xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 70;
 0.60274;-0.31621;-9.05012;,
 0.60274;-10.74487;-9.73634;,
 7.33414;-10.74487;-6.94811;,
 6.35962;-3.90991;-6.46286;,
 10.12237;-10.74487;-0.21668;,
 9.54964;-5.39856;-0.21668;,
 7.33414;-10.74487;6.51472;,
 6.35962;-3.90991;6.02950;,
 0.60274;-10.74487;9.30295;,
 0.60274;-0.31621;8.61676;,
 -6.12866;-10.74487;6.51472;,
 -5.15417;3.27751;6.02950;,
 -8.91689;-10.74487;-0.21668;,
 -8.74688;4.76609;-0.21668;,
 -6.12866;-10.74487;-6.94811;,
 -5.15417;3.27751;-6.46286;,
 0.60274;-10.74487;-9.73634;,
 0.60274;-0.31621;-9.05012;,
 0.60274;-21.17335;-9.54830;,
 7.20118;-21.17335;-6.81512;,
 9.93433;-21.17335;-0.21668;,
 7.20118;-21.17335;6.38176;,
 0.60274;-21.17335;9.11491;,
 -5.99570;-21.17335;6.38176;,
 -8.72888;-21.17335;-0.21668;,
 -5.99570;-21.17335;-6.81512;,
 0.60274;-21.17335;-9.54830;,
 0.60274;-31.60192;-9.13868;,
 6.91153;-31.60192;-6.52550;,
 9.52474;-31.60192;-0.21668;,
 6.91153;-31.60192;6.09211;,
 0.60274;-31.60192;8.70529;,
 -5.70608;-31.60192;6.09211;,
 -8.31926;-31.60192;-0.21668;,
 -5.70608;-31.60192;-6.52550;,
 0.60274;-31.60192;-9.13868;,
 0.60274;-42.03048;-8.78969;,
 6.66478;-42.03048;-6.27872;,
 9.17575;-42.03048;-0.21668;,
 6.66478;-42.03048;5.84533;,
 0.60274;-42.03048;8.35633;,
 -5.45930;-42.03048;5.84533;,
 -7.97027;-42.03048;-0.21668;,
 -5.45930;-42.03048;-6.27872;,
 0.60274;-42.03048;-8.78969;,
 0.60274;-52.45912;-9.45566;,
 7.13569;-52.45912;-6.74963;,
 9.84172;-52.45912;-0.21668;,
 7.13569;-52.45912;6.31627;,
 0.60274;-52.45912;9.02230;,
 -5.93021;-52.45912;6.31627;,
 -8.63624;-52.45912;-0.21668;,
 -5.93021;-52.45912;-6.74963;,
 0.60274;-52.45912;-9.45566;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-0.31621;-0.21668;,
 0.60274;-52.45912;-0.21668;,
 0.60274;-52.45912;-0.21668;,
 0.60274;-52.45912;-0.21668;,
 0.60274;-52.45912;-0.21668;,
 0.60274;-52.45912;-0.21668;,
 0.60274;-52.45912;-0.21668;,
 0.60274;-52.45912;-0.21668;,
 0.60274;-52.45912;-0.21668;;
 
 56;
 4;3,2,1,0;,
 4;5,4,2,3;,
 4;7,6,4,5;,
 4;9,8,6,7;,
 4;11,10,8,9;,
 4;13,12,10,11;,
 4;15,14,12,13;,
 4;17,16,14,15;,
 4;2,19,18,1;,
 4;4,20,19,2;,
 4;6,21,20,4;,
 4;8,22,21,6;,
 4;10,23,22,8;,
 4;12,24,23,10;,
 4;14,25,24,12;,
 4;16,26,25,14;,
 4;19,28,27,18;,
 4;20,29,28,19;,
 4;21,30,29,20;,
 4;22,31,30,21;,
 4;23,32,31,22;,
 4;24,33,32,23;,
 4;25,34,33,24;,
 4;26,35,34,25;,
 4;28,37,36,27;,
 4;29,38,37,28;,
 4;30,39,38,29;,
 4;31,40,39,30;,
 4;32,41,40,31;,
 4;33,42,41,32;,
 4;34,43,42,33;,
 4;35,44,43,34;,
 4;37,46,45,36;,
 4;38,47,46,37;,
 4;39,48,47,38;,
 4;40,49,48,39;,
 4;41,50,49,40;,
 4;42,51,50,41;,
 4;43,52,51,42;,
 4;44,53,52,43;,
 3;3,0,54;,
 3;5,3,55;,
 3;7,5,56;,
 3;9,7,57;,
 3;11,9,58;,
 3;13,11,59;,
 3;15,13,60;,
 3;17,15,61;,
 3;45,46,62;,
 3;46,47,63;,
 3;47,48,64;,
 3;48,49,65;,
 3;49,50,66;,
 3;50,51,67;,
 3;51,52,68;,
 3;52,53,69;;
 
 MeshMaterialList {
  1;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.700000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  56;
  0.507842;0.861451;-0.000000;,
  0.016232;0.080956;-0.996585;,
  0.704898;0.116190;-0.699727;,
  0.814837;0.579690;0.000000;,
  0.704898;0.116188;0.699728;,
  0.016232;0.080953;0.996586;,
  -0.681922;0.055008;0.729353;,
  -0.998825;0.048465;0.000000;,
  -0.681923;0.055010;-0.729353;,
  0.008102;0.031355;-0.999476;,
  0.707540;0.049578;-0.704932;,
  0.998158;0.060671;0.000000;,
  0.707539;0.049578;0.704933;,
  0.008102;0.031355;0.999476;,
  -0.694938;0.018739;0.718825;,
  -0.999891;0.014735;0.000000;,
  -0.694939;0.018739;-0.718825;,
  0.000000;-0.028640;-0.999590;,
  0.706817;-0.028640;-0.706816;,
  0.999590;-0.028640;0.000000;,
  0.706816;-0.028640;0.706817;,
  0.000000;-0.028640;0.999590;,
  -0.706816;-0.028640;0.706818;,
  -0.999590;-0.028639;0.000000;,
  -0.706817;-0.028640;-0.706817;,
  0.000000;-0.036347;-0.999339;,
  0.706639;-0.036346;-0.706640;,
  0.999339;-0.036346;0.000001;,
  0.706639;-0.036347;0.706640;,
  0.000000;-0.036347;0.999339;,
  -0.706639;-0.036347;0.706640;,
  -0.999339;-0.036347;0.000001;,
  -0.706640;-0.036347;-0.706639;,
  0.000000;0.015165;-0.999885;,
  0.707025;0.015165;-0.707026;,
  0.999885;0.015166;0.000001;,
  0.707025;0.015166;0.707025;,
  0.000000;0.015166;0.999885;,
  -0.707026;0.015166;0.707025;,
  -0.999885;0.015165;0.000001;,
  -0.707026;0.015165;-0.707025;,
  0.000000;0.063730;-0.997967;,
  0.705669;0.063730;-0.705669;,
  0.997967;0.063730;0.000000;,
  0.705670;0.063731;0.705669;,
  0.000000;0.063731;0.997967;,
  -0.705670;0.063731;0.705669;,
  -0.997967;0.063730;0.000000;,
  -0.705669;0.063730;-0.705669;,
  0.000000;-1.000000;0.000000;,
  0.529538;0.848286;0.000000;,
  0.511722;0.858856;-0.022502;,
  0.511722;0.858856;0.022502;,
  0.503549;0.863351;-0.032621;,
  0.477585;0.878586;-0.000000;,
  0.503549;0.863351;0.032621;;
  56;
  4;2,10,9,1;,
  4;3,11,10,2;,
  4;4,12,11,3;,
  4;5,13,12,4;,
  4;6,14,13,5;,
  4;7,15,14,6;,
  4;8,16,15,7;,
  4;1,9,16,8;,
  4;10,18,17,9;,
  4;11,19,18,10;,
  4;12,20,19,11;,
  4;13,21,20,12;,
  4;14,22,21,13;,
  4;15,23,22,14;,
  4;16,24,23,15;,
  4;9,17,24,16;,
  4;18,26,25,17;,
  4;19,27,26,18;,
  4;20,28,27,19;,
  4;21,29,28,20;,
  4;22,30,29,21;,
  4;23,31,30,22;,
  4;24,32,31,23;,
  4;17,25,32,24;,
  4;26,34,33,25;,
  4;27,35,34,26;,
  4;28,36,35,27;,
  4;29,37,36,28;,
  4;30,38,37,29;,
  4;31,39,38,30;,
  4;32,40,39,31;,
  4;25,33,40,32;,
  4;34,42,41,33;,
  4;35,43,42,34;,
  4;36,44,43,35;,
  4;37,45,44,36;,
  4;38,46,45,37;,
  4;39,47,46,38;,
  4;40,48,47,39;,
  4;33,41,48,40;,
  3;51,50,0;,
  3;3,51,0;,
  3;52,3,0;,
  3;50,52,0;,
  3;53,50,0;,
  3;54,53,0;,
  3;55,54,0;,
  3;50,55,0;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;;
 }
 MeshTextureCoords {
  70;
  0.000000;0.000000;,
  0.000000;0.200000;,
  0.125000;0.200000;,
  0.125000;0.000000;,
  0.250000;0.200000;,
  0.250000;0.000000;,
  0.375000;0.200000;,
  0.375000;0.000000;,
  0.500000;0.200000;,
  0.500000;0.000000;,
  0.625000;0.200000;,
  0.625000;0.000000;,
  0.750000;0.200000;,
  0.750000;0.000000;,
  0.875000;0.200000;,
  0.875000;0.000000;,
  1.000000;0.200000;,
  1.000000;0.000000;,
  0.000000;0.400000;,
  0.125000;0.400000;,
  0.250000;0.400000;,
  0.375000;0.400000;,
  0.500000;0.400000;,
  0.625000;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  1.000000;0.400000;,
  0.000000;0.600000;,
  0.125000;0.600000;,
  0.250000;0.600000;,
  0.375000;0.600000;,
  0.500000;0.600000;,
  0.625000;0.600000;,
  0.750000;0.600000;,
  0.875000;0.600000;,
  1.000000;0.600000;,
  0.000000;0.800000;,
  0.125000;0.800000;,
  0.250000;0.800000;,
  0.375000;0.800000;,
  0.500000;0.800000;,
  0.625000;0.800000;,
  0.750000;0.800000;,
  0.875000;0.800000;,
  1.000000;0.800000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
