#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "Batch.h"
#include <GLES2\gl2.h>
#include <scene\GameEntity.h>
#include <vector>
#include <graphics\Text.h>
#include <graphics\Shader.h>

namespace pm
{
	/** \brief Keeps track of Drawable GameEntity objects that have been queued to be drawn and optimizes rendering.
	*
	* \ingroup Graphics
	*/

	class SpriteBatch
	{
	public:

		/** \brief Return instance of SpriteBatch. 
		* \return Pointer to SpriteBatch.
		*/
		static SpriteBatch* GetInstance();

		/** \brief Delete pm::SpriteBatch and all associated resources.
		*
		* Deleting pm::SpriteBatch is already part of cleaning routine when application is shut down permanently.
		* As such user will no need to call this unless for very specific reason.
		*/
		void DestroyInstance();

		/** \brief Render all objects that have been queued to be drawn.
		*
		* \sa AddGameEntity(), AddtranslucentGameEntity() and AddText().
		*/
		void Draw();
		
		/** \brief Render all objects with specific shader program.
		*
		* \sa AddGameEntity(), AddtranslucentGameEntity() and AddText().
		*/
		void Draw(Shader* customShader);
		/** \brief Old Draw()-function
		*
		*  Included in case of bugs in new Draw();
		*
		*/
		void DrawOld();

		void DrawText();

		/** @name Batching Functions
		* \brief Store GameEntity objects to be drawn.
		*/
		///@{

		/** \brief Add GameEntity to be drawn.
		*
		* \param[in] entity Pointer to GameEntity.
		* \param[in] transparent Boolean if GameEntity contains transparency.
		*/
		void AddGameEntity(GameEntity* entity, bool transparent);

		/** \brief Add GameEntity to be drawn.
		*
		* \param[in] entity Pointer to GameEntity.
		*/
		void AddGameEntity(GameEntity* entity);

		/** \param[in] gameEntity Pointer to GameEntity object. */
		void AddOpaqueGameEntity(GameEntity* gameEntity);

		/** \brief Add GameEntity object that contains transparency.
		* \param[in] gameEntity Pointer to GameEntity object.
		*/
		void AddTranslucentGameEntity(GameEntity* gameEntity);

		/** \brief Add std::vector of GameEntity objects that contains transparency.
		* \param[in] entityVector Pointer to std::vector<GameEntity*>.
		*/
		void AddOpaqueGameEntity(std::vector<GameEntity*> entityVector);
		
		/** \brief Add Text object that contains transparency.
		* \param[in] textEntity Pointer to pm::Text object.
		*/
		void AddText(Text* textEntity);
		///@}

	private:

		SpriteBatch(); ///< Neccessary for singleton.

		~SpriteBatch() {}; ///< Can't be deleted without calling DestroyInstance.

		bool IsDrawable(GameEntity* gameEntity); ///< Check if GameEntity is drawable.
		
		void CreateLayers(); // Sorts gameEntityVectors on different layers.
		
		void BatchLayerComponents(int layer, bool type); // Batches one layer, type selects if opaque or translucent vector is used.

		void BatchAllLayers(); // Calls CreateLayers() and calls BatchLayerComponents() for every layer.

		void BatchOpaqueComponents(); ///< Makes final translucent batch.

		void BatchTranslucentComponents(); ///< Makes final translucent batch.

		void ParseData(GameEntity* gameEntity, // GameEntity is gutted to form data matrises that can be assimilated into Batch.
			std::vector<GLfloat>* vertexData, 
			std::vector<GLushort>* indexData,
			glm::mat4* transformMatrix,
			GLuint* textureIndex);

		std::vector<GameEntity*> opaqueGameEntityVector; // Vector for all opaque GameEntities that are added during draw cycle.
		std::vector<GameEntity*> translucentGameEntityVector; // Vector for all translucent GameEntities that are added during draw cycle.
		std::vector<Batch> batchVector; ///< Contains all batched draw data. Used in DrawOld(), no use in new draw.
		
		std::vector<std::vector<Batch>> opaqueLayerBatchVector; // Vectors of batched opaque GameEntities, sorted by layer.
		std::vector<std::vector<Batch>> translucentLayerBatchVector; // Vectors of batched translucent GameEntities, sorted by layer.
		static SpriteBatch* instance;

		struct Layer // Storage for layers GameEntities.
		{
			std::vector<GameEntity*> translucentGO;
			std::vector<GameEntity*> opaqueGO;
		};

		std::vector<Layer> Layers; // Storage for every layer.
	};
}

#endif