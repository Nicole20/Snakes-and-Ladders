#pragma once

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include<glut.h>

using namespace std;

struct coords
{
	float xx, yy, zz;
	coords(float a, float b, float c);
};

struct face
{
	int facenum;
	bool four;
	int faces[4];
	int texcoor[4];
	int mat;  //material number
	face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m);
	face(int facen, int f1, int f2, int f3, int f4, int t1, int t2,
		int t3, int t4, int m);
};

struct material
{
	char name[20];
	float diff[3], amb[3], spec[3], alpha, ns, ni;
	int illum;
	int texture;

	material(char na[20], float alph, float ns1, float ni1,
		float* d, float* am, float* s, float ill, int t);
};

struct texcood
{
	float u, v;
	texcood(float a, float b);
};

class ObjLoader
{
public:
	vector<string*> coord;
	vector<coords*> vertex;
	vector<face*> faces;
	vector<coords*> normal;
	vector<material*> materials;
	vector<unsigned int> texture;
	vector<unsigned int> lists;
	vector<texcood*> texturecoordinate;
	bool isMaterial, isNormal, isTexture;
	unsigned int loadTexture(const char* filename);
	void clean();

	ObjLoader(void);
	~ObjLoader(void);

	int load(const char* filename);
};
