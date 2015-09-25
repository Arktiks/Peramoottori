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
		
		///\brief Default constructor for Shader.
		Shader() : created(false), shaderProgram(0), vertex(0), fragment(0) {};

		///\brief Shader copy constructor.
		// \param[in] shader Shader ID of a previous shader. 
		Shader(GLuint shader) : created(true), shaderProgram(shader) {};

		
		///\brief Add shaders to program.
		// \param[in] filePath Name of the shader file.
		// \param[in] shaderType GLenum type of the shader.
		// \return Returns false if adding shader failed.
		bool AddShader(std::string filePath, GLenum shaderType);

		///\brief Create executable program object.
		// \return Returns true.
		bool LinkProgram();
		
		///\brief Confirm if program has been linked successfully.
		// \return Returns bool wether program has been linked successfully.
		bool GetLinkStatus();

		
		///\brief Use vertex attributes
		void UseVertexAttribs();

		
		///\brief Use program as part of current rendering state.
		void UseProgram();

	
		///\brief Return value of attribute within program.
		// \param[in] attributeName Name of the attribute requested
		// \return Returns the value of requested parameter.
		GLuint GetAttribLocation(std::string attributeName);

		///\brief Makes a new VertexAttribPointer that is placed in shaderVertexAtribute vector
		//	\param[in] attributeName Name of the attribute to be added.
		//	\param[in] size Size of the attribute to be added.
		//	\param[in] stride Stride of the attribute to be added.
		//	\param[in] offset Offset of the attribute to be added.
		void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);
		
		
	
		///\brief Returns the shaderprogram ID
		// \return Returns the GLuint number of the program.
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