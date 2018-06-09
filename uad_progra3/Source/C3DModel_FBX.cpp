#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "../Include/C3DModel_FBX.h"
using namespace std;




C3DModel_FBX::C3DModel_FBX():
	m_numVertices(0), m_numNormals(0), m_numUVCoords(0), m_numFaces(0)
{
	cout << "Constructor: C3DModel_Fbx()" << endl;
}


C3DModel_FBX::~C3DModel_FBX()
{
	cout << "Destructor: C3DModel_Obj()" << endl;
	reset();
}

void C3DModel_FBX::reset()
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

bool C3DModel_FBX::loadFromFile(const char * const filename)
{
	bool readFileOk = false;

	// Free any previous resources
	reset();
	readObjFile(filename, readFileOk);

	// Display count
	cout << "Finished reading 3D model" << endl;
	cout << "Vertices: " << m_numVertices << endl;
	cout << "Normals: " << m_numNormals << endl;
	cout << "UVCoords: " << m_numUVCoords << endl;
	cout << "Faces: " << m_numFaces << endl;
	if (readFileOk)
	{
		// Check for MAX number of faces
		if (m_numVertices >= 65535 || m_numNormals >= 65535 || m_numUVCoords >= 65535)
		{
			cout << "Error: object cannot have more than 65535 vertices" << endl;
			cout << "Object attempted to load has: " << m_numVertices << " vertices" << endl;
			return false;
		}

		if (m_numNormals == 0)
		{
			m_modelHasNormals = false;
			m_numNormals = m_numVertices;
		}
		else
		{
			m_modelHasNormals = true;
		}

		if (m_numUVCoords == 0)
		{
			m_numUVCoords = m_numVertices;
			m_modelHasUVs = false;
		}
		else
		{
			m_modelHasUVs = true;
		}
		
		m_verticesRaw = new float[m_numVertices * 3];
		m_normalsRaw = new float[m_numNormals * 3];
		m_uvCoordsRaw = new float[m_numUVCoords * 2];
		m_vertexIndices = new unsigned short[m_numFaces * 3];
		m_normalIndices = new unsigned short[m_numFaces * 3];
		m_UVindices = new unsigned short[m_numFaces * 3];
		
		memset(m_vertexIndices, 0, sizeof(unsigned short) * m_numFaces * 3);
		memset(m_normalIndices, 0, sizeof(unsigned short) * m_numFaces * 3);
		memset(m_UVindices, 0, sizeof(unsigned short) * m_numFaces * 3);
		memset(m_verticesRaw, 0, sizeof(float) * m_numVertices * 3);
		memset(m_normalsRaw, 0, sizeof(float) * m_numNormals * 3);
		memset(m_uvCoordsRaw, 0, sizeof(float) * m_numUVCoords * 2);

		readFileOk = readObjFile(filename, false);

		if (readFileOk)
		{
			m_Initialized = true;

			if (!m_modelHasNormals)
			{
				computeFaceNormals();
			}
		}
	}
	else
	{
		cout << "Error ocurred while reading 3D model." << endl;
	}

	return readFileOk;
}

bool C3DModel_FBX::readObjFile(const char * const filename, bool countOnly)
{
	ifstream infile;
	string lineBuffer;
	string token;
	bool readFileOk = true;
	const char *delimiterToken = "Vertices: *";
	const char *delimiterToken2 = "PolygonVertexIndex: *";
	const char *delimiterToken3 = "Normals: *";
	const char *delimiterToken4 = "NormalsW: *";
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
				m_verticesRaw[i] = stof(lineBuffer);
			}
			getline(lineaux2, lineBuffer, '\n');
			m_verticesRaw[m_numVertices-1] = stof(lineBuffer);
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
				int j = i + m_indicesAgregados;
				getline(lineaux4, token, ',');
				m_IVertices.push_back(stof(token));
				if (m_IVertices[j] >= 0) m_signosPositivos++;
				else if (m_signosPositivos == 3)
				{
					m_IVertices[j + 2] = m_IVertices[j - 3];
					m_IVertices[j + 1] = (-m_IVertices[i]) - 1;
					m_IVertices[j] = m_IVertices[j - 1];
					m_signosPositivos = 0;
					m_indicesAgregados += 2;
				}
				else if (m_signosPositivos == 2)m_signosPositivos = 0;
				if (m_signosPositivos > 3 || m_signosPositivos < 2)
				{
					cout << "Lo siento, no se aceptan N-gons" << endl;
					return false;
				}
			}
			getline(lineaux4, token, '\n');
			if (m_signosPositivos == 3)
			{
				m_IVertices[j + 2] = m_IVertices[j - 3];
				m_IVertices[j + 1] = (-m_IVertices[j]) - 1;
				m_IVertices[j] = m_IVertices[j - 1];
			}
			if (m_signosPositivos > 3 || m_signosPositivos < 2)
			{
				cout << "Lo siento, no se aceptan N-gons" << endl;
				return false;
			}
			m_vertexIndices = new unsigned short [m_numIVertices];
			for (int i = 0; i < m_numIVertices; i++)
			{
				m_vertexIndices[i] = m_IVertices[i];
			}
		}
		else if (lineBuffer.find(delimiterToken4) != string::npos)
		{
			istringstream lineaux7(lineBuffer);
			getline(lineaux7, token, '*');
			getline(lineaux7, token, ' ');
			m_numINormals = stof(token);
			m_normalIndices = new unsigned short[m_numNormals];
			getline(infile, lineBuffer);
			istringstream lineaux8(lineBuffer);
			getline(lineaux8, token, ' ');
			for (int i = 0; i < m_numINormals - 1; i++)
			{
				getline(lineaux8, token, ',');
				m_normalIndices[i] = stof(token);
			}
			getline(lineaux8, token, '\n');
			m_normalIndices[m_numVertices - 1] = stof(token);
		}
		else if (lineBuffer.find(delimiterToken3) != string::npos)
		{
			istringstream lineaux5(lineBuffer);
			getline(lineaux5, token, '*');
			getline(lineaux5, token, ' ');
			m_numNormals = stof(token);
			m_normalsRaw = new float[m_numNormals];
			getline(infile, lineBuffer);
			istringstream lineaux6(lineBuffer);
			getline(lineaux6, token, ' ');
			for (int i = 0; i < m_numNormals - 1; i++)
			{
				getline(lineaux6, token, ',');
				m_normalsRaw[i] = stof(token);
			}
			getline(lineaux6, token, '\n');
			m_normalsRaw[m_numNormals - 1] = stof(token);
		}
		else if (lineBuffer.find(delimiterToken6) != string::npos)
		{

		}
		else if (lineBuffer.find(delimiterToken5)!= string::npos)
		{

		}
	}
	infile.close();

	return readFileOk;
}
