/*****************************************************************
*CEngine
*GameData.h by Chris Lewis
*Declares Game Data class for handling storage of all game objects, level data etc.
*****************************************************************/

#ifndef CENGINE_GAMEDATA_H
#define CENGINE_GAMEDATA_H

#include <list>
#include <vector>
#include <set>
#include <boost/shared_ptr.hpp>
#include "GameObject.h"

namespace CEngine
{
	/// \class CEngine::GameObjectPointer
	/// \brief Alias for boost::shared_ptr<GameObject>, used by GameData class for GameObject pointers
	typedef boost::shared_ptr<GameObject> GameObjectPointer;
	/// \class CEngine::GameObjectCollection
	/// \brief Alias for the internal collection used to store GameObjects. Can be used to get the right iterator type for GameObjects.
	typedef std::list<GameObjectPointer> GameObjectCollection;

	/// \brief Class to hold all active game state data, e.g. managing instances of game objects, current level data, etc.
	///
	/// The GameData class acts as storage for all main data related to the current game-state, like storing all active game objects
	/// in the game, data on the current level and so on. It will also house when appropriate other information designed to work on the
	/// game-state, such as BSP-trees for collision. It is designed to be interfaced with by Game States (and others) to work on the current
	/// game state.
	/// It provides Begin() and End() functions to use for iterating through GameObjects without needing access to the collections themselves.
	class GameData
	{
	public:
		//! Default Constructor, creates empty game data
		GameData();
		/// \brief Copy Constructor. Will perform a deep copy of all GameObjects in the other GameData instance as well as all
		/// GameObjects that are waiting to be added. However copying of those waiting to be removed is not possible and as
		/// such this constructor imposes the restriction that the list of objects waiting to be removed on the other GameData instance
		/// MUST be empty prior to copying.
		GameData(const GameData& target);
		/// \brief Assignment Operator. Works just like the Copy Constructor but clears out any existing data before copying.
		const GameData& operator = (const GameData& target);
		//! Destructor. Makes sure all existing game data is cleaned up.
		~GameData();

		//Declare exception classes
		/// \brief Exception class for errors when copying data from one GameData instance to another. Currently only includes
		/// attempting to copy when objects are present in the Removal List.
		class CopyException : public std::exception
		{
		public:
			CopyException(const char *what) : std::exception(what) {}
		};

		//Declare public functions
		/// \brief Requests a new object be added to the game state. Note that the new object will not be actually added into the proper
		/// game state until a Batch Add is performed (at the start of a new program Update)
		///
		/// \param object A (most likely new'd) pointer to the object to add in. Can be properly created with the GameObjectPointer constructor.
		/// \return void
		void AddObject(GameObjectPointer object);
		/// \brief Performs a batch add of objects into the game state, putting all requested new objects into our actual object collection.
		/// \return void
		void PerformBatchAdd();
		/// \brief Requests that an object referenced by the specified iterator be removed from the game state. Note that will not actually
		/// be removed until a Batch Remove is performed (at the end of a new program Update). Also checks to see that the target
		/// iterator has not already been requested to remove.
		///
		/// \param target The GameObject Collection iterator referencing the object to be removed.
		/// \return void
		void RemoveObject(GameObjectCollection::iterator target);
		/// \brief Requests that a range of iterators be removed from the game state (largely the same as the first RemoveObject).
		///
		/// \param begin Iterator indicating the start of a range of objects to remove.
		/// \param end End iterator which specifies where to stop removing (will NOT remove the end iterator itself)
		/// \return void
		void RemoveObject(GameObjectCollection::iterator begin, GameObjectCollection::iterator end);
		/// \brief Performs a batch remove of all objects currently waiting to be removed from the game state
		/// \return void
		void PerformBatchRemove();
		/// \brief Clears out all existing data. This includes all current Game Objects plus any that are waiting to be added, and naturally
		/// cancels out all pending removals. Useful as a flatout reset for your game data where appropriate. Should be perfectly safe as long
		/// as you don't try to access the old data in any way (e.g. through hanging references) and so on.
		/// \return void
		void ClearAll();
		/// \brief Returns the starting iterator for our collection of GameObjects.
		/// \return An iterator referencing the start of our GameObjects collection.
		GameObjectCollection::iterator Begin();
		/// \brief Returns the end iterator for our collection of GameObjects.
		/// \return An iterator signifying the last element in our collection.
		GameObjectCollection::iterator End();
		/// \brief Returns the no. of GameObjects currently in our collection
		/// \return An integer representing our collection size.
		int ObjectCount() const;

	private:
		//Declare private functions
		//! Copies data from another GameData. Used in Copy Constructor and oeperator =
		void Copy(const GameData &target);

		//Declare private properties
		//Collection of GameObjectPointers to add into our collection on the next batch add
		std::vector<GameObjectPointer> AddList;
		//Collection of all game objects currently in our game state
		GameObjectCollection Objects;
		//Collection of iterators referencing objects to be removed in our next batch remove
		std::vector<GameObjectCollection::iterator> RemoveList;
	};

	/// \example Examples/ExampleGameData.cpp
	/// Demonstrates use of the various methods and important concepts of the GameData class.
}

#endif