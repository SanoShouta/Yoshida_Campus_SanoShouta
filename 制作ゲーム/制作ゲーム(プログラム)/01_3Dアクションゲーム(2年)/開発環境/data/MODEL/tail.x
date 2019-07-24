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
 44;
 -3.22993;2.30280;8.56961;,
 0.07316;4.61632;9.49992;,
 0.07316;4.17672;1.85788;,
 -2.40398;2.60616;2.35619;,
 -3.25886;-0.39162;4.94094;,
 -4.61489;-0.95597;8.61388;,
 -3.26311;-2.90111;5.06995;,
 -3.30619;-3.43366;8.61388;,
 -0.01574;-4.84472;5.23332;,
 0.07316;-5.83503;8.83538;,
 -3.96669;1.69307;17.55386;,
 0.07316;4.61925;18.47099;,
 0.07316;-6.26156;17.69572;,
 -3.75676;-3.58094;17.28107;,
 -3.40221;0.61274;27.69905;,
 0.07316;2.93753;28.43885;,
 0.07316;-4.81729;28.51883;,
 -2.82770;-3.74998;27.81753;,
 -1.91506;-1.64227;34.06402;,
 0.07316;0.54833;34.64107;,
 0.07316;-3.44583;34.53033;,
 0.07316;-1.57539;38.29599;,
 -5.17374;-1.39841;17.25269;,
 -3.80216;-1.39841;27.88508;,
 3.37625;2.30280;8.56961;,
 2.55030;2.60616;2.14945;,
 4.76122;-0.95597;8.61388;,
 3.71034;-0.42503;5.18315;,
 3.45251;-3.43366;8.61388;,
 2.54759;-2.90841;5.48131;,
 4.11301;1.69307;17.55386;,
 3.90309;-3.58094;17.28107;,
 3.54853;0.61274;27.69905;,
 2.97403;-3.74998;27.81753;,
 2.06139;-1.64227;34.06402;,
 5.32006;-1.39841;17.25269;,
 3.94848;-1.39841;27.88508;,
 -1.89612;-1.13926;0.41697;,
 -1.45368;-2.30068;0.55540;,
 -1.87878;0.85170;0.41697;,
 -0.01326;3.33585;0.36299;,
 1.36689;-2.46659;0.41697;,
 1.82889;-0.91804;0.41697;,
 1.66631;0.85173;0.27851;;
 
 46;
 4;0,1,2,3;,
 4;3,4,5,0;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;0,10,11,1;,
 4;9,12,13,7;,
 4;10,14,15,11;,
 4;12,16,17,13;,
 4;14,18,19,15;,
 4;16,20,18,17;,
 4;18,20,21,19;,
 4;5,22,10,0;,
 4;5,7,13,22;,
 4;22,23,14,10;,
 4;17,23,22,13;,
 3;23,18,14;,
 3;17,18,23;,
 4;24,25,2,1;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,9,8;,
 4;24,1,11,30;,
 4;9,28,31,12;,
 4;30,11,15,32;,
 4;12,31,33,16;,
 4;32,15,19,34;,
 4;16,33,34,20;,
 4;34,19,21,20;,
 4;26,24,30,35;,
 4;26,35,31,28;,
 4;35,30,32,36;,
 4;33,31,35,36;,
 3;36,32,34;,
 3;33,36,34;,
 4;6,37,38,8;,
 4;4,39,37,6;,
 3;3,39,4;,
 4;39,3,2,40;,
 4;8,41,42,29;,
 4;29,42,43,27;,
 3;43,25,27;,
 4;25,43,40,2;,
 3;8,38,41;,
 4;43,37,39,40;,
 4;43,42,41,37;,
 3;41,38,37;;
 
 MeshMaterialList {
  1;
  46;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}
