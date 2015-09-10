#ifndef SHADER_H
#define SHADER_H

#include <structs/ShaderVertexAttrib.h>
#include <EGL/egl.h>
#include <vector>
#include <string>

namespace pm
{
	class Shader
	{
	public:

		/// Constructor for Shader.
		Shader() : created(false), shaderProgram(0), vertex(0), fragment(0) {};

		Shader(GLuint shader) : created(true), shaderProgram(shader) {};

		/// Add shaders to program.
		bool AddShader(std::string filePath, GLenum shaderType);

		/// Create executable program object.
		bool LinkProgram();

		/// Confirm if program has been linked successfully.
		bool GetLinkStatus();

		void UseVertexAttribs();

		/// Use program as part of current rendering state.
		void UseProgram();

		/// Return value of attribute within program.
		GLuint GetAttribLocation(std::string attributeName);

		/// Makes a new VertexAttribPointer that is placed in shaderVertexAtribute vector
		void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);

		/// Return program
		GLuint GetShaderProgramLocation() { return shaderProgram; };

		~Shader();

	private:

		std::string LoadShader(std::string filePath); ///< loads shader from txt file

		bool CheckShaderCompile(GLuint shader); ///< Check shader compilation status

		bool CheckProgramLink(GLuint program); ///< Check program linking status

		std::vector<ShaderVertexAttrib> ShaderVertexAttribs;

		GLuint shaderProgram; ///< Program object reference.

		GLuint vertex; ///< Vertex shader reference.

		GLuint fragment; ///< Fragment shader reference.

		bool created; ///< If shader program reference has been set.
	};
}

#endif // SHADER_H