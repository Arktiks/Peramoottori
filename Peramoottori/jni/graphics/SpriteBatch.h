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
	/** \brief Used to define what kind of layer SpriteBatch is using
	*/
	enum LAYERTYPE
	{
		TRANSLUCENT,
		OPAQUE,
		TEXT
	};

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
		void AddOpaqueGameEntityVector(std::vector<GameEntity*> entityVector);
		
		/** \brief Add Text object that contains transparency.
		* \param[in] textEntity Pointer to pm::Text object.
		*/
		void AddText(Text* textEntity);

		/** \brief Add Static game entity object that does not change e.g. backround.
		* \param[in] gameEntity Pointer to pm::GameEntity object.
		*/
		void AddStaticGameEntity(GameEntity* gameEntity);
		///@}


		static void CreateTextShader();

	private:

		SpriteBatch(); ///< Neccessary for singleton.

		~SpriteBatch() {}; ///< Can't be deleted without calling DestroyInstance.

		bool IsDrawable(GameEntity* gameEntity); ///< Check if GameEntity is drawable.

		void CreateLayers(); // Sorts gameEntityVectors on different layers.
		
		void BatchLayerComponents(int layer, LAYERTYPE type); // Batches one layer, type selects if opaque or translucent vector is used.

		void BatchAllLayers(); // Calls CreateLayers() and calls BatchLayerComponents() for every layer.

		void ParseData(GameEntity* gameEntity, // GameEntity is gutted to form data matrises that can be assimilated into Batch.
			std::vector<GLfloat>* vertexData, 
			std::vector<GLushort>* indexData,
			glm::mat4* transformMatrix,
			GLuint* textureIndex);

		std::vector<GameEntity*> opaqueGameEntityVector; // Vector for all opaque GameEntities that are added during draw cycle.
		std::vector<GameEntity*> translucentGameEntityVector; // Vector for all translucent GameEntities that are added during draw cycle.
		std::vector<GameEntity*> textEntityVector; // Vector for all text GameEntities that are added during draw cycle.
		std::vector<Batch> batchVector; ///< Contains all batched draw data. Used in DrawOld(), no use in new draw.
		
		std::vector<std::vector<Batch>> opaqueLayerBatchVector; // Vectors of batched opaque GameEntities, sorted by layer.
		std::vector<std::vector<Batch>> translucentLayerBatchVector; // Vectors of batched translucent GameEntities, sorted by layer.
		std::vector<std::vector<Batch>> textLayerBatchVector; // Vectors of batched text GameEntities, sorted by layer.
		static SpriteBatch* instance;

		Shader textShader;

		struct Layer // Storage for layers GameEntities.
		{
			std::vector<GameEntity*> translucentGO;
			std::vector<GameEntity*> opaqueGO;
			std::vector<GameEntity*> textGO;
		};

		std::vector<Layer> Layers; // Storage for every layer.
	};
}

#endif