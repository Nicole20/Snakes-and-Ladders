#include "stdafx.h"
#include "ObjLoader.h"

coords::coords(float a, float b, float c)
{
	xx = a;
	yy = b;
	zz = c;
}

face::face(int facen, int f1, int f2, int f3,
	int t1, int t2, int t3, int m)
{
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	texcoor[0] = t1;
	texcoor[1] = t2;
	texcoor[2] = t3;
	four = false;
	mat = m;
}
face::face(int facen, int f1, int f2, int f3, int f4,
	int t1, int t2, int t3, int t4, int m)
{
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
	texcoor[0] = t1;
	texcoor[1] = t2;
	texcoor[2] = t3;
	texcoor[3] = t4;
	four = true;
	mat = m;
}

material::material(char na[20], float alph, float ns1, float ni1,
	float* d, float* am, float* s, float ill, int t)
{
	for (int i = 0; i < 20; i++)
	{
		name[i] = na[i];
	}

	alpha = alph;
	ns = ns1;
	ni = ni1;

	for (int i = 0; i < 3; i++)
	{
		diff[i] = d[i];
		amb[i] = am[i];
		spec[i] = s[i];
	}

	illum = ill;
	texture = t;
}

texcood::texcood(float a, float b)
{
	u = a;
	v = b;
}

void ObjLoader::clean()
{
	for (unsigned int i = 0; i < coord.size(); i++)
		delete coord[i];
	for (unsigned int i = 0; i < faces.size(); i++)
		delete faces[i];
	for (unsigned int i = 0; i < normal.size(); i++)
		delete normal[i];
	for (unsigned int i = 0; i < vertex.size(); i++)
		delete vertex[i];
	for (unsigned int i = 0; i < materials.size(); i++)
		delete materials[i];
	for (unsigned int i = 0; i < texturecoordinate.size(); i++)
		delete texturecoordinate[i];

	coord.clear();
	faces.clear();
	normal.clear();
	vertex.clear();
	materials.clear();
	texturecoordinate.clear();
}

int ObjLoader::load(const char* filename)
{
	ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Not opened\n";
		return -1;
	}

	char buff[256];
	int currmat = 0;

	while (!in.eof())
	{
		in.getline(buff, 256);
		coord.push_back(new string(buff));
	}

	for (unsigned int i = 0; i < coord.size(); i++)
	{
		if ((*coord[i])[0] == '#' || (*coord[i])[0] == 'o' ||
			(*coord[i])[0] == 's')
		{
			continue;
		}
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == ' ')
		{
			float tempx, tempy, tempz;

			sscanf_s(coord[i]->c_str(), "v %f %f %f", &tempx, &tempy, &tempz);
			vertex.push_back(new coords(tempx, tempy, tempz));
		}
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == 'n')
		{
			float tempx, tempy, tempz;

			sscanf_s(coord[i]->c_str(), "vn %f %f %f", &tempx, &tempy, &tempz);
			normal.push_back(new coords(tempx, tempy, tempz));
		}
		else if ((*coord[i])[0] == 'f')
		{
			int a, b, c, d;
			int t[4];

			if (count(coord[i]->begin(), coord[i]->end(), ' ') == 4)
			{
				sscanf_s(coord[i]->c_str(), "f %d %d %d %d", &a, &b, &c, &d);
				faces.push_back(new face(4, a, b, c, d,
					t[0], t[1], t[2], t[3], currmat));
			}
			else
			{
				sscanf_s(coord[i]->c_str(), "f %d %d %d", &a, &b, &c);
				faces.push_back(new face(3, a, b, c, t[0], t[1], t[2], currmat));
			}
		}
		else if ((*coord[i])[0] == 'u' && (*coord[i])[1] == 's'
			&& (*coord[i])[2] == 'e')
		{
			char temp[20];
			sscanf_s(coord[i]->c_str(), "usemtl %s", temp, sizeof(temp));

			for (unsigned int ii = 0; ii < materials.size(); ii++)
			{
				if (strcmp(materials[ii]->name, temp) == 0)
				{
					currmat = ii;
					break;
				}
			}
		}
		else if ((*coord[i])[0] == 'm' && (*coord[i])[1] == 't'
			&& (*coord[i])[2] == 'l' && (*coord[i])[3] == 'l')
		{
			char file[20];
			sscanf_s(coord[i]->c_str(), "mtllib %s", file, sizeof(file));

			ifstream mtlin(file);
			if (!mtlin.is_open())
			{
				cout << "Cannot open\n";
				clean();
				return -1;
			}

			isMaterial = true;
			vector<string> temp;
			char c[200];

			while (!mtlin.eof())
			{
				mtlin.getline(c, 200);
				temp.push_back(c);
			}

			char matname[20];  //material name
			char filename[20];
			float amb[3], diff[3], spec[3], alpha, ns, ni;
			int illum;
			unsigned int texture;
			bool ismat = false;
			strcpy_s(filename, "\0");

			for (unsigned int i = 0; i < temp.size(); i++)
			{
				if (temp[i][0] == '#')
				{
					continue;
				}
				else if (temp[i][0] == 'n' && temp[i][1] == 'e' && temp[i][2] == 'w')
				{
					if (ismat)
					{
						if (strcmp(filename, "\0") != 0)
						{
							materials.push_back(new material(matname,
								alpha, ns, ni, diff, amb, spec, illum, texture));
							strcpy_s(filename, "\0");
						}
						else
						{
							materials.push_back(new material(matname,
								alpha, ns, ni, diff, amb, spec, illum, -1));
						}
					}
					ismat = false;
					sscanf_s(temp[i].c_str(), "newmtl %s", matname,
						sizeof(matname));
				}
				else if (temp[i][0] == 'N' && temp[i][1] == 's')
				{
					sscanf_s(temp[i].c_str(), "Ns %f", &ns);
					ismat = true;
				}
				else if (temp[i][0] == 'K' && temp[i][1] == 'a')
				{
					sscanf_s(temp[i].c_str(), "Ka %f %f %f",
						&amb[0], &amb[1], &amb[2]);
					ismat = true;
				}
				else if (temp[i][0] == 'K' && temp[i][1] == 'd')
				{
					sscanf_s(temp[i].c_str(), "Kd %f %f %f",
						&diff[0], &diff[1], &diff[2]);
					ismat = true;
				}
				else if (temp[i][0] == 'K' && temp[i][1] == 's')
				{
					sscanf_s(temp[i].c_str(), "Ks %f %f %f",
						&spec[0], &spec[1], &spec[2]);
					ismat = true;
				}
				else if (temp[i][0] == 'N' && temp[i][1] == 'i')
				{
					sscanf_s(temp[i].c_str(), "Ni %f", &ni);
					ismat = true;
				}
				else if (temp[i][0] == 'd' && temp[i][1] == ' ')
				{
					sscanf_s(temp[i].c_str(), "d %f", &alpha);
					ismat = true;
				}
				else if (temp[i][0] == 'i' && temp[i][1] == 'l')
				{
					sscanf_s(temp[i].c_str(), "illum %d", &illum);
					ismat = true;
				}
				else if (temp[i][0] == 'm' && temp[i][1] == 'a')
				{
					sscanf_s(temp[i].c_str(), "map_Kd %s", filename);
					texture = loadTexture(filename);
					ismat = true;
				}
			}

			if (ismat)
			{
				if (strcmp(filename, "\0") != 0)
				{
					materials.push_back(new material(matname,
						alpha, ns, ni, diff, amb, spec, illum, texture));
				}
				else
				{
					materials.push_back(new material(matname,
						alpha, ns, ni, diff, amb, spec, illum, -1));
				}
			}
		}
		else if ((*coord[i])[0] == 'v' && (*coord[i])[0] == 't')
		{
			float u, v;
			sscanf_s(coord[i]->c_str(), "vt %f %f", &u, &v);
			texturecoordinate.push_back(new texcood(u, 1 - v));
			isTexture = true;
		}
	}

	if (materials.size() == 0)
	{
		isMaterial = false;
	}
	else
	{
		isMaterial = true;
	}

	return 1;
}

unsigned int ObjLoader::loadTexture(const char* filename)
{
	unsigned int num;
	glGenTextures(1, &num);

	glBindTexture(GL_TEXTURE_2D, num);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	texture.push_back(num);
	return num;
}

ObjLoader::ObjLoader(void)
{
	isMaterial = false;
	isTexture = false;
	isNormal = false;
}

ObjLoader::~ObjLoader(void)
{
	clean();

	vector<unsigned int>::const_iterator it_t, it_l;

	for (it_t = texture.begin(); it_t != texture.end(); it_t++)
	{
		glDeleteTextures(1, &(*it_t));
	}

	for (it_l = lists.begin(); it_l != lists.end(); it_l++)
	{
		glDeleteLists(*it_l, 1);
	}
}
