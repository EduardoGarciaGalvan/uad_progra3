#include "../Include/C3DModel_X.h"
#include <iostream>
#include <fstream>
using namespace std;

C3DModel_X::C3DModel_X():
C3DModel(),
m_currentVertex(0),
m_currentNormal(0),
m_currentUV(0),
m_currentFace(0)
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
	m_currentFace = 0;
}

bool C3DModel_X::loadFromFile(const char * const filename)
{
	bool readFileOk = false;
	reset();
	readFileOk = readXFile(filename);
}

bool C3DModel_X::readXFile(const char * const filename)
{
	ifstream infile;
	string lineBuffer;
	bool readFileOk = true;
	int lineNumber = 0;

	infile.open(filename);

	while (!infile.eof())
	{
		getline(infile, lineBuffer);
		lineNumber++;

		if (!(this->parseXLine(lineBuffer, true, lineNumber)))
		{
			readFileOk = false;
			break;
		}
	}
	infile.close();

	return readFileOk;
}

bool C3DModel_X::parseXLine(std::string line, bool countOnly, int lineNumber)
{
	return false;
}
