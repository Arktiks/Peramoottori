#ifndef SHADER_H
#define SHADER_H

#include <structs/ShaderVertexAttrib.h>
#include <EGL/egl.h>
#include <vector>
#include <string>
#include <resources\TextResource.h>
#include <resources\ResourceManager.h>

namespace pm
{
	class Shader
	{
	public:

		Shader() : created(false), shaderProgram(0), vertex(0), fragment(0) {};

		Shader(GLuint shader) : created(true), shaderProgram(shader) {};

		/// Add shaders to program.
		bool AddShader(std::string filePath, GLenum shaderType);

		/// Create executable program object.
		bool LinkProgram();

		/// Confirm if program has been linked successfully.
		bool GetLinkStatus();

		// ...
		void UseVertexAttribs();

		/// Use program as part of current rendering state.
		void UseProgram();

		/// Return value of attribute within program.
		GLuint GetAttribLocation(std::string attributeName);

		void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);

		GLuint GetShaderProgramLocation() { return shaderProgram; }

		~Shader();

	private:

		std::string LoadShader(std::string filePath);

		bool CheckShaderCompile(GLuint shader); // TODO

		bool CheckProgramLink(GLuint program); // TODO

		std::vector<ShaderVertexAttrib> ShaderVertexAttribs;

		GLuint shaderProgram; ///< Program object reference.

		GLuint vertex; ///< Vertex shader reference.

		GLuint fragment; ///< Fragment shader reference.

		bool created; ///< If shader program reference has been set.
	};
}

#endif // SHADER_H