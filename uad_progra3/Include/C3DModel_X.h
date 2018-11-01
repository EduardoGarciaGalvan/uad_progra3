#pragma once
#include "C3DModel.h"
#include "CVector3.h"

class C3DModel_X : public C3DModel {
public:
	C3DModel_X();
	~C3DModel_X();
private:
	int m_currentVertex, m_currentNormal, m_currentUV, m_currentFace;
	bool openFile(const char * const filename);
	bool readXFile(const char * const filename);
	bool parseXLine(
		std::string line,
		bool countOnly,
		int lineNumber);
	char *Cuerpo = "Mesh mesh", *Normals = "MeshNormals normals";

protected:
	void reset();
	bool loadFromFile(const char * const filename);

};