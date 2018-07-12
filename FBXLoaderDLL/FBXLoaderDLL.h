#pragma once

#ifdef CREATING_DLL
#define TEST_DLL extern"C" _declspec(dllexport)
#else
#define TEST_DLL extern"C" _declspec(dllimport)
#endif //CREATING_DLL

#include "../uad_progra3/Include/C3DModel.h"
#include "../uad_progra3/Include/CVector3.h"

class FBXLoaderDLL :public C3DModel
{
private:
	int m_numVertices, m_numNormals, m_numUVCoords, m_numFaces;
	int m_numIVertices, m_numIUVCoords;

	bool readObjFile(const char * const filename);
protected:
	void reset();
	bool loadFromFile(const char * const filename);

public:
	FBXLoaderDLL();
	~FBXLoaderDLL();
};
