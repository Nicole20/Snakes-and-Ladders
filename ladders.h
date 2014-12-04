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

class ladders
{
public:
	int num, temp1, temp2;
	vector<int> top, bottom;

	ladders(void);

	int getBottom(int spot);

	void check();
	void erase();
};
