#pragma once
#include "C3DModel.h"
#include "CVector3.h"

class C3DModel_X : public C3DModel {
public:
	C3DModel_X();
	~C3DModel_X();
private:
	int m_currentVertex, m_currentNormal,
		m_currentUV, m_currentVertexFace,
		m_currentNormalFace, m_currentUVFace,
		m_numVertices, m_numNormals,
		m_numUVCoords, m_numFaces,
		m_Contador;

	unsigned short *m_vertexIndices,
		*m_normalIndices,
		*m_UVindices;                                      // Dynamically-allocated array of UV coord indices for this model

	float *m_verticesRaw,
		*m_normalsRaw,
		*m_uvCoordsRaw;

	char *Cuerpo = "Mesh",
		*Normals = "MeshNormals",
		*UV = "MeshTextureCoords";
	bool m_cuerpo, m_normals, m_UV;
protected:
	void reset();
	bool loadFromFile(const char * const filename);
	void render();
};