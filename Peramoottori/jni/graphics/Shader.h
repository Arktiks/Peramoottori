#ifndef SHADER_H
#define SHADER_H

#include <structs/ShaderVertexAttrib.h>
#include <EGL/egl.h>
#include <vector>
#include <string>

namespace pm
{

	/** \brief Custom class for OpenGL shaders.
	*
	* Shaders are user-defined programs designed to run on some stage of rendering pipeline.
	*
	* \ingroup Graphics
	*/

	class Shader
	{
	public:
		
		/** \brief Default constructor
		* Creates incomplete shader object
		*/
		Shader() : created(false), shaderProgram(0), vertex(0), fragment(0) {};

		/** \internal Shader index is set @ AddShader().
		* \brief Copy constructor.
		* \param[in] shader Shader ID of a previous shader.
		*
		*Shader(GLuint shader) : created(true), shaderProgram(shader) {}; */

		/** \brief Add shaders you wish to execute.
		*
		* Contains error handling in form of debug messages and assertion.
		* \param[in] filePath Name of shader file --- example "FRAGMENT_SHADER.txt".
		* \param[in] shaderType GLenum type of shader --- see relevant OpenGL documentation for possible types.
		* \return true if attaching shader was successful.
		*/
		bool AddShader(std::string filePath, GLenum shaderType);

		/** \brief Create final executable shader program object.
		* 
		* Contains assertion.
		* \return true if program was linked succesfully.
		*/
		bool LinkProgram();
		
		/** \brief Confirm if shader program has been linked successfully.
		*
		* \return true if program has been linked succesfully.
		* \return false if program has not been linked yet.
		*/
		bool GetLinkStatus();

		/** \brief Use vertex attributes. */
		void UseVertexAttribs();
		
		/** \brief Use shader program as part of current rendering state. */
		void UseProgram();

		/** \brief Return value of attribute within shader program.
		*
		* \param[in] attributeName Name of attribute requested as std::string.
		* \return Value of requested attribute.
		*/
		GLuint GetAttribLocation(std::string attributeName);

		/**\brief Add new VertexAttribPointer.
		*
		* Specifies data formats and locations of attributes in vertex attributes array.
		* \param[in] attributeName Name of the attribute to be added.
		* \param[in] size Size of the attribute to be added.
		* \param[in] stride Stride of the attribute to be added.
		* \param[in] offset Offset of the attribute to be added.
		*/
		void AddVertexAttribPointer(std::string attributeName, GLint size, GLsizei stride, GLint offset);
	
		/** \brief Returns index assigned for shader program.
		* \return assigned index as GLuint.
		* \return 0 if index has not been assigned.
		*/
		GLuint GetShaderProgramLocation() { return shaderProgram; };

		/** \brief Default destructor
		*/
		~Shader();

	private:

		std::string LoadShader(std::string filePath); ///< Load shader from file.

		bool CheckShaderCompile(GLuint shader); ///< Check shader compilation status.

		bool CheckProgramLink(GLuint program); ///< Check program linking status.

		std::vector<ShaderVertexAttrib> ShaderVertexAttribs;

		GLuint shaderProgram; ///< Program object reference.

		GLuint vertex; ///< Vertex shader reference.

		GLuint fragment; ///< Fragment shader reference.

		bool created; ///< If shader program reference has been set.
	};
}

#endif // SHADER_H