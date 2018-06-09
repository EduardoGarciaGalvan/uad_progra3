#pragma once
#include "C3DModel.h"
#include "CVector3.h"

class C3DModel_FBX :public C3DModel
{
private:
	int m_numVertices, m_numNormals, m_numUVCoords, m_numFaces;
	int m_numIVertices, m_numINormals, m_numIUVCoords, m_numIFaces;
	
	bool readObjFile(const char * const filename);
protected:
	void reset();
	bool loadFromFile(const char * const filename);

public:
	C3DModel_FBX();
	~C3DModel_FBX();
};

