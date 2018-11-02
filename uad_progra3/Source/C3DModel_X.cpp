#include "../Include/C3DModel_X.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

C3DModel_X::C3DModel_X():
C3DModel(),
m_currentVertex(0),
m_currentNormal(0),
m_currentUV(0),
m_currentVertexFace(0),
m_currentNormalFace(0),
m_currentUVFace(0),
m_Contador(0),
cuerpo(false),
normals(false),
UV(false)
{
	cout << "Constructor: C3DModel_X()" << endl;
}

C3DModel_X::~C3DModel_X()
{
	cout << "Destructor: C3DModel_X()" << endl;
	reset();
}

void C3DModel_X::reset()
{
	C3DModel::reset();

	m_currentVertex = 0;
	m_currentNormal = 0;
	m_currentUV = 0;
	m_currentVertexFace = 0;
	m_currentNormalFace = 0;
	m_currentUVFace = 0;
	m_Contador = 0;
	cuerpo = false;
	normals = false;
	UV = false;
}

bool C3DModel_X::loadFromFile(const char * const filename)
{
	bool loadFromFile = false;
	float CoordenadaXYZ;
	ifstream infile;
	string lineBuffer, token;
	infile.open(filename);
	if (infile.fail())//Error "Archivo no encontrado"
	{
		cout << "Documento inexistente" << endl;
		return loadFromFile;
	}
	while (!infile.eof())
	{
		getline(infile, lineBuffer);
		if (lineBuffer.find(Cuerpo) != string::npos)
		{
			if (cuerpo)
			{
				getline(infile, token, ';');
				cout << "Vertices del modelo: " << token << endl;
				m_numVertices = atoi(token.c_str());
				m_verticesRaw = new float[m_numVertices * 3];
				for (int i = 0; i < m_numVertices; i++)
				{
					m_currentVertex += m_currentVertex != 0 ? 1 : 0;
					getline(infile, lineBuffer);
					istringstream lineBuffer2(lineBuffer);
					getline(lineBuffer2, token, ';');
					CoordenadaXYZ = atoi(token.c_str());
					m_verticesRaw[(m_currentVertex * 3)] = CoordenadaXYZ;
					getline(lineBuffer2, token, ';');
					CoordenadaXYZ = atoi(token.c_str());
					m_verticesRaw[(m_currentVertex * 3) + 1] = CoordenadaXYZ;
					getline(lineBuffer2, token, ';');
					CoordenadaXYZ = atoi(token.c_str());
					m_verticesRaw[(m_currentVertex * 3) + 2] = CoordenadaXYZ;
					m_currentVertex++;
				}
				getline(infile, token, ';');
				cout << "Faces del modelo: " << token << endl;
				m_numFaces = atoi(token.c_str());
				m_vertexIndices = new unsigned short[m_numFaces * 3];
				for (int i = 0; i < m_numFaces; i++)
				{
					m_currentVertexFace += m_currentVertexFace != 0 ? 1 : 0;
					getline(infile, lineBuffer);
					istringstream lineBuffer2(lineBuffer);
					getline(lineBuffer2, token, ';');
					getline(lineBuffer2, token, ',');
					CoordenadaXYZ = atoi(token.c_str());
					m_vertexIndices[(m_currentVertexFace * 3)] = (unsigned short)CoordenadaXYZ;
					getline(lineBuffer2, token, ',');
					CoordenadaXYZ = atoi(token.c_str());
					m_vertexIndices[(m_currentVertexFace * 3) + 1] = (unsigned short)CoordenadaXYZ;
					getline(lineBuffer2, token, ';');
					CoordenadaXYZ = atoi(token.c_str());
					m_vertexIndices[(m_currentVertexFace * 3) + 2] = (unsigned short)CoordenadaXYZ;
					m_currentVertexFace++;
				}
				while (!infile.eof())
				{
					if (lineBuffer.find(Normals) != string::npos)
					{
						if (normals)
						{
							getline(infile, token, ';');
							cout << "Normals del modelo: " << token << endl;
							m_numNormals = atoi(token.c_str());
							m_normalsRaw = new float[m_numNormals * 3];
							for (int i = 0; i < m_numNormals; i++)
							{
								m_currentNormal += m_currentNormal != 0 ? 1 : 0;
								getline(infile, lineBuffer);
								istringstream lineBuffer2(lineBuffer);
								getline(lineBuffer2, token, ';');
								CoordenadaXYZ = atoi(token.c_str());
								m_normalsRaw[(m_currentNormal * 3)] = CoordenadaXYZ;
								getline(lineBuffer2, token, ';');
								CoordenadaXYZ = atoi(token.c_str());
								m_normalsRaw[(m_currentNormal * 3) + 1] = CoordenadaXYZ;
								getline(lineBuffer2, token, ';');
								CoordenadaXYZ = atoi(token.c_str());
								m_normalsRaw[(m_currentNormal * 3) + 2] = CoordenadaXYZ;
								m_currentNormal++;
							}
							getline(infile, token, ';');
							m_numFaces = atoi(token.c_str());
							m_normalIndices = new unsigned short[m_numFaces * 3];
							for (int i = 0; i < m_numFaces; i++)
							{
								m_currentNormalFace += m_currentNormalFace != 0 ? 1 : 0;
								getline(infile, lineBuffer);
								istringstream lineBuffer2(lineBuffer);
								getline(lineBuffer2, token, ';');
								getline(lineBuffer2, token, ',');
								CoordenadaXYZ = atoi(token.c_str());
								m_normalIndices[(m_currentNormalFace * 3)] = (unsigned short)CoordenadaXYZ;
								getline(lineBuffer2, token, ',');
								CoordenadaXYZ = atoi(token.c_str());
								m_normalIndices[(m_currentNormalFace * 3) + 1] = (unsigned short)CoordenadaXYZ;
								getline(lineBuffer2, token, ';');
								CoordenadaXYZ = atoi(token.c_str());
								m_normalIndices[(m_currentNormalFace * 3) + 2] = (unsigned short)CoordenadaXYZ;
								m_currentNormalFace++;
							}
							while (!infile.eof())
							{
								if (lineBuffer.find(UV) != string::npos)
								{
									if (UV)
									{
										getline(infile, token, ';');
										cout << "UV del modelo: " << token << endl;
										m_numUVCoords = atoi(token.c_str());
										m_uvCoordsRaw = new float[m_numUVCoords * 2];
										for (int i = 0; i < m_numUVCoords; i++)
										{
											m_currentUV += m_currentUV != 0 ? 1 : 0;
											getline(infile, lineBuffer);
											istringstream lineBuffer2(lineBuffer);
											getline(lineBuffer2, token, ';');
											CoordenadaXYZ = atoi(token.c_str());
											m_uvCoordsRaw[(m_currentUV * 2)] = CoordenadaXYZ;
											getline(lineBuffer2, token, ';');
											CoordenadaXYZ = atoi(token.c_str());
											m_uvCoordsRaw[(m_currentUV * 2) + 1] = CoordenadaXYZ;
											getline(lineBuffer2, token, ';');
											CoordenadaXYZ = atoi(token.c_str());
											m_uvCoordsRaw[(m_currentUV * 2) + 2] = CoordenadaXYZ;
											m_currentUV++;
										}
										getline(infile, token, ';');
										m_numFaces = atoi(token.c_str());
										m_UVindices = new unsigned short[m_numFaces * 3];
										for (int i = 0; i < m_numFaces; i++)
										{
											m_currentUVFace += m_currentUVFace != 0 ? 1 : 0;
											getline(infile, lineBuffer);
											istringstream lineBuffer2(lineBuffer);
											getline(lineBuffer2, token, ';');
											getline(lineBuffer2, token, ',');
											CoordenadaXYZ = atoi(token.c_str());
											m_UVindices[(m_currentUVFace * 3)] = (unsigned short)CoordenadaXYZ;
											getline(lineBuffer2, token, ',');
											CoordenadaXYZ = atoi(token.c_str());
											m_UVindices[(m_currentUVFace * 3) + 1] = (unsigned short)CoordenadaXYZ;
											getline(lineBuffer2, token, ';');
											CoordenadaXYZ = atoi(token.c_str());
											m_UVindices[(m_currentUVFace * 3) + 2] = (unsigned short)CoordenadaXYZ;
											m_currentUVFace++;
										}
										continue;
									}
									else
									{
										normals = true;
									}
									getline(infile, lineBuffer);
								}
							}
							continue;
						}
						else
						{
							normals = true;
						}
						getline(infile, lineBuffer);

					}
				}
				loadFromFile = true;
			}
			else {
				cuerpo = true;
			}

		}
	}
	infile.close();

	return loadFromFile;
}

