#pragma once

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<math.h>
#include<ctime>
#include<glut.h>

using namespace std;

class snakes
{
public:
	int num, temp1, temp2;
	vector<int> head, tail;

	snakes(void);

	int getHead(int spot);

	void check();
	void erase();
};
