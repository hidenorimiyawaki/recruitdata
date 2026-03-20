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
 18;
 464.10947;384.60071;-314.92322;,
 464.10947;384.60071;281.28455;,
 373.45712;377.21344;281.28455;,
 373.45712;377.21344;-314.92322;,
 286.28812;355.33643;281.28455;,
 286.28812;355.33643;-314.92322;,
 205.95273;319.80908;281.28455;,
 205.95273;319.80908;-314.92322;,
 135.53833;271.99823;281.28455;,
 135.53833;271.99823;-314.92322;,
 77.74995;213.74017;281.28455;,
 77.74995;213.74017;-314.92322;,
 34.81005;147.27396;281.28455;,
 34.81005;147.27396;-314.92322;,
 8.36779;75.15406;281.28455;,
 8.36779;75.15406;-314.92322;,
 -0.56077;0.15209;281.28455;,
 -0.56077;0.15209;-314.92322;;
 
 8;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;;
 
 MeshMaterialList {
  1;
  8;
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
   5.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.500000;0.500000;;
   TextureFilename {
    "Sky10.jpg";
   }
  }
 }
 MeshNormals {
  9;
  0.081221;-0.996696;-0.000000;,
  0.162873;-0.986647;-0.000000;,
  0.325118;-0.945673;-0.000000;,
  0.485062;-0.874480;-0.000000;,
  0.638822;-0.769354;-0.000000;,
  0.779162;-0.626823;-0.000000;,
  0.894937;-0.446192;-0.000000;,
  0.972525;-0.232800;-0.000000;,
  0.992989;-0.118210;-0.000000;;
  8;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;;
 }
 MeshTextureCoords {
  18;
  -1.000000;0.034370;
  -0.005000;0.000000;
  -0.047180;0.037750;
  -0.992280;0.072110;
  -0.039110;0.106960;
  -0.984210;0.141320;
  -0.030990;0.204980;
  -0.976090;0.239340;
  -0.023000;0.358000;
  -0.968230;0.362400;
  -0.016000;0.501000;
  -0.960940;0.505760;
  -0.009000;0.650000;
  -0.954500;0.663920;
  -0.004000;0.806000;
  -0.949150;0.830810;
  0.000000;0.996000;
  -0.945100;1.000000;;
 }
}
