#define CREATING_DLL
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "FBXLoaderDLL.h"
using namespace std;




FBXLoaderDLL::FBXLoaderDLL() :
	m_numVertices(0), m_numNormals(0), m_numUVCoords(0), m_numFaces(0)
{
	cout << "Constructor: C3DModel_Fbx()" << endl;
}


FBXLoaderDLL::~FBXLoaderDLL()
{
	cout << "Destructor: C3DModel_Obj()" << endl;
	reset();
}

void FBXLoaderDLL::reset()
{
	C3DModel::reset();


	if (m_vertexIndices != NULL)
	{
		delete[] m_vertexIndices;
		m_vertexIndices = NULL;
	}
	if (m_normalIndices != NULL)
	{
		delete[] m_normalIndices;
		m_normalIndices = NULL;
	}
	if (m_UVindices != NULL)
	{
		delete[] m_UVindices;
		m_UVindices = NULL;
	}
	if (m_verticesRaw != NULL)
	{
		delete[] m_verticesRaw;
		m_verticesRaw = NULL;
	}
	if (m_normalsRaw != NULL)
	{
		delete[] m_normalsRaw;
		m_normalsRaw = NULL;
	}
	if (m_uvCoordsRaw != NULL)
	{
		delete[] m_uvCoordsRaw;
		m_uvCoordsRaw = NULL;
	}
	m_numVertices = 0;
	m_numNormals = 0;
	m_numUVCoords = 0;
	m_numFaces = 0;

	m_Initialized = false;

	m_graphicsMemoryObjectId = 0;
	m_shaderProgramId = 0;
}

bool FBXLoaderDLL::loadFromFile(const char * const filename)
{
	bool readFileOk = false;

	reset();
	readFileOk = readObjFile(filename);

	cout << "Finished reading 3D model" << endl;
	cout << "Vertices: " << m_numVertices << endl;
	cout << "Normals: " << m_numNormals << endl;
	cout << "UVCoords: " << m_numUVCoords << endl;
	cout << "Faces: " << m_numFaces << endl;

	if (readFileOk)
	{
		if (m_numVertices >= 65535 || m_numNormals >= 65535 || m_numUVCoords >= 65535)
		{
			cout << "Error: object cannot have more than 65535 vertices" << endl;
			cout << "Object attempted to load has: " << m_numVertices << " vertices" << endl;
			return false;
		}
		if (readFileOk)
		{
			m_Initialized = true;
		}
	}
	else
	{
		cout << "Error ocurred while reading 3D model." << endl;
	}

	return readFileOk;
}

bool FBXLoaderDLL::readObjFile(const char * const filename)
{
	ifstream infile;
	string lineBuffer;
	string token;
	bool readFileOk = true;
	const char *delimiterToken = "Vertices: *";
	const char *delimiterToken2 = "PolygonVertexIndex: *";
	const char *delimiterToken3 = "Normals: *";
	const char *delimiterToken5 = "UV: *";
	const char *delimiterToken6 = "UVIndex: *";



	infile.open(filename, ios::in);

	if (infile.fail())
	{
		cout << "no se pudo cargar el archivo" << endl;
		return false;

	}

	while (!infile.eof())
	{
		getline(infile, lineBuffer);

		if (lineBuffer.find(delimiterToken) != string::npos)
		{
			istringstream lineaux(lineBuffer);
			getline(lineaux, lineBuffer, '*');
			getline(lineaux, lineBuffer, ' ');
			m_numVertices = stof(lineBuffer);
			m_verticesRaw = new float[m_numVertices];
			getline(infile, lineBuffer);
			istringstream lineaux2(lineBuffer);
			getline(lineaux2, lineBuffer, ' ');
			for (int i = 0; i < (m_numVertices - 1); i++)
			{
				getline(lineaux2, lineBuffer, ',');
				if (lineBuffer.compare(""))
				{
					m_verticesRaw[i] = stof(lineBuffer);
				}
				else
				{
					lineBuffer.clear();
					//getline(lineaux2, lineBuffer);
					string tmpLine;
					getline(infile, tmpLine);
					lineaux2.clear();
					lineaux2.str(tmpLine);
					lineaux2.seekg(0);
					i--;

					//istringstream lineaux2(lineBuffer);
				}
				/*if (lineBuffer != NULL)
				{
				m_verticesRaw[i] = stof(lineBuffer);
				i++;
				}
				else
				{
				getline(infile, lineBuffer);
				istringstream lineaux(lineBuffer);
				}*/
			}
			getline(lineaux2, lineBuffer, '\n');
			m_verticesRaw[m_numVertices - 1] = stof(lineBuffer);
		}
		else if (lineBuffer.find(delimiterToken2) != string::npos)
		{
			int m_signosPositivos = 0, m_indicesAgregados = 0;
			istringstream lineaux3(lineBuffer);
			getline(lineaux3, token, '*');
			getline(lineaux3, token, ' ');
			m_numIVertices = stof(token);
			vector<long>m_IVertices;
			getline(infile, lineBuffer);
			istringstream lineaux4(lineBuffer);
			getline(lineaux4, token, ' ');
			int j;
			for (int i = 0; i < (m_numIVertices - 1); i++)
			{
				j = i + m_indicesAgregados;
				getline(lineaux4, token, ',');
				if (token.compare(""))
				{
					m_IVertices.push_back(stof(token));
					if (m_IVertices[j] >= 0) m_signosPositivos++;
					else if (m_signosPositivos == 3)
					{
						m_IVertices.push_back((-m_IVertices[j]) - 1);
						m_IVertices.push_back(m_IVertices[j - 3]);
						m_IVertices[j] = m_IVertices[j - 1];
						m_signosPositivos = 0;
						m_indicesAgregados += 2;
						m_numFaces++;
					}
					else if (m_signosPositivos == 2)
					{
						m_IVertices[j] = ((-m_IVertices[j]) - 1);
						m_signosPositivos = 0;
						m_numFaces++;
					}
					if (m_signosPositivos > 3)
					{
						cout << "Lo siento, no se aceptan N-gons" << endl;
						return false;
					}
				}
				else
				{
					token.clear();
					string tmpLine;
					getline(infile, tmpLine);
					lineaux4.clear();
					lineaux4.str(tmpLine);
					lineaux4.seekg(0);
					i--;
				}
			}
			getline(lineaux4, token, '\n');
			m_IVertices.push_back(stof(token));
			if (m_signosPositivos == 3)
			{
				m_IVertices.push_back(m_IVertices[j - 2]);
				m_IVertices.push_back((-m_IVertices[j]) - 1);
				m_IVertices[j] = m_IVertices[j - 1];
			}
			else if (m_signosPositivos == 2)
			{
				m_IVertices[j] = ((-m_IVertices[j]) - 1);
				m_numFaces++;
			}
			if (m_signosPositivos > 3)
			{
				cout << "Lo siento, no se aceptan N-gons" << endl;
				return false;
			}
			m_numIVertices += m_indicesAgregados;
			m_vertexIndices = new unsigned short[m_numIVertices];
			for (int i = 0; i < m_numIVertices; i++)
			{
				m_vertexIndices[i] = m_IVertices[i];
			}
		}
		else if (lineBuffer.find(delimiterToken3) != string::npos)
		{
			int m_normals = 0, m_INormals = 0;
			istringstream lineaux5(lineBuffer);
			getline(lineaux5, token, '*');
			getline(lineaux5, token, ' ');
			m_numNormals = stof(token);
			m_normalsRaw = new float[m_numNormals];
			m_normalIndices = new unsigned short[m_numNormals / 3];
			getline(infile, lineBuffer);
			istringstream lineaux6(lineBuffer);
			getline(lineaux6, token, ' ');
			for (int i = 0; i < m_numNormals - 1; i++)
			{
				getline(lineaux6, token, ',');
				if (token.compare(""))
				{
					m_normalsRaw[i] = stof(token);
					m_normals++;
					if (m_normals == 3)
					{
						m_normals = 0;
						m_normalIndices[m_INormals] = m_INormals;
						m_INormals++;
					}
				}
				else
				{
					token.clear();
					string tmpLine;
					getline(infile, tmpLine);
					lineaux6.clear();
					lineaux6.str(tmpLine);
					lineaux6.seekg(0);
					i--;
				}
			}
			getline(lineaux6, token, '\n');
			m_normalsRaw[m_numNormals - 1] = stof(token);
			if (m_normals == 3) m_normalIndices[m_INormals] = m_INormals;
		}
		else if (lineBuffer.find(delimiterToken6) != string::npos)
		{
			istringstream lineaux7(lineBuffer);
			getline(lineaux7, token, '*');
			getline(lineaux7, token, ' ');
			m_numIUVCoords = stof(token);
			m_UVindices = new unsigned short[m_numIUVCoords];
			getline(infile, lineBuffer);
			istringstream lineaux8(lineBuffer);
			getline(lineaux8, token, ' ');
			for (int i = 0; i < m_numIUVCoords - 1; i++)
			{
				getline(lineaux8, token, ',');
				if (token.compare(""))
				{
					m_UVindices[i] = stof(token);
					i++;
				}
				else
				{
					token.clear();
					string tmpLine;
					getline(infile, tmpLine);
					lineaux8.clear();
					lineaux8.str(tmpLine);
					lineaux8.seekg(0);
					i--;
				}
			}
			getline(lineaux8, token, '\n');
			m_UVindices[m_numIUVCoords - 1] = stof(token);
		}
		else if (lineBuffer.find(delimiterToken5) != string::npos)
		{
			istringstream lineaux9(lineBuffer);
			getline(lineaux9, token, '*');
			getline(lineaux9, token, ' ');
			m_numUVCoords = stof(token);
			m_uvCoordsRaw = new float[m_numUVCoords];
			getline(infile, lineBuffer);
			istringstream lineaux10(lineBuffer);
			getline(lineaux10, token, ' ');
			for (int i = 0; i < m_numUVCoords - 1; i++)
			{
				getline(lineaux10, token, ',');
				if (token.compare(""))
				{
					m_uvCoordsRaw[i] = stof(token);
					i++;
				}
				else
				{
					token.clear();
					string tmpLine;
					getline(infile, tmpLine);
					lineaux10.clear();
					lineaux10.str(tmpLine);
					lineaux10.seekg(0);
					i--;
				}
			}
			getline(lineaux10, token, '\n');
			m_uvCoordsRaw[m_numUVCoords - 1] = stof(token);
		}
	}
	infile.close();

	return readFileOk;
}