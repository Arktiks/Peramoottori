#ifndef BATCH_H
#define BATCH_H

#include <glm\mat4x4.hpp>
#include <GLES2\gl2.h>
#include <vector>

namespace pm
{

	/** \brief SpriteBatch class organizes to-be drawn GameEntities into groups (Batch)
	* to optimize performance.
	*
	* Most likely developer does not need to create his own batches and should instead
	* use the functions found in SpriteBatch class.
	*/

	class Batch
	{

	public:
		
		Batch() : textureIndex(0) {};
		
		Batch(std::vector<GLfloat> vertexData,
			std::vector<GLushort> indexData,
			glm::mat4 transformMatrix,
			GLuint textureIndex);

		/** ----- */
		void AddData(std::vector <GLfloat> vertexData,
			std::vector<GLushort>indexData,
			glm::mat4 transformMatrix);

		/** \return Reference to totalVertexData vector. */
		std::vector<GLfloat>* GetVertexDataPointer() { return &totalVertexData; }

		/** \return Reference to totalIndexData vector. */
		std::vector<GLushort>* GetIndexDataPointer() { return &totalIndexData; }

		/** \return Reference to transformMatrixVector vector. */
		std::vector<glm::mat4>* GetTransformMatrixPointer() { return &transformMatrixVector; }

		// Planned to be deleted depending on testing results.
		//std::vector<GLfloat> GetVertexData() { return totalVertexData; }
		//std::vector<GLushort> GetIndexData() { return totalIndexData; }

		std::vector<GLfloat> totalVertexData; ///< Vertices batched to be drawn.
		std::vector<GLushort> totalIndexData; ///< Index buffer of batch.
		std::vector<glm::mat4> transformMatrixVector; ///< Possible transformations that have been applied to batch.
		GLuint textureIndex; ///< Index where texture of to-be drawn batch has been bound.
	};
}

#endif