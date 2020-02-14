#pragma once

class VertexArray {

public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indeces, unsigned int numIndeces);

	~VertexArray();

	void SetActive();

	inline unsigned int GetNumVerts() const { return numVerts; }
	inline unsigned int GetNumIndices() const { return numIndices; }

private:
	unsigned int numVerts;
	unsigned int numIndices;
	unsigned int indexBuffer;
	unsigned int vertexBuffer;
	unsigned int vertexArray;

};
