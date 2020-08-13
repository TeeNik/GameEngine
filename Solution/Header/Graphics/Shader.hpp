#pragma once
#include <glew.h>
#include <string>
#include "Math/Math.h"

class Shader {
public:
	Shader();
	~Shader();

	bool Load(const std::string& name, const std::string& vertName, const std::string& fragName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	void SetVectorUniform(const char* name, const Vector3& vector);
	void SetFloatUniform(const char* name, const float value);
	inline std::string GetName() { return shaderName; }

private:
	std::string shaderName;
	bool CompileShader(const std::string fileName, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();
	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};