/***************************************************************
*CEngine
*State.h by Chris Lewis
*Declares abstract class State for definition of State behaviours
***************************************************************/

#ifndef CENGINE_STATE_H
#define CENGINE_STATE_H

//Declare inside CEngine namespace
namespace CEngine
{
	//Forward-declare StateMachine
	class StateMachine;

	/// \brief Abstract class used as a base to create implementation State classes.
	///
	/// The State class is an abstract class to use as a base for any class you wish to use in a StateMachine. These classes
	/// must naturally define the implementation of their State be it game logic or other behaviours.
	/// When a State is entered to via StateMachine::ChangeState(), the Enter method is called to perform any setup.
	/// The Update method is designed to be called as part of a main loop to perform the required logic for a game.
	/// The Exit method is called when the StateMachine is entering into another State, to perform any necessary clean-up.
	class State
	{
	public:
		//! Required constructor to specify the StateMachine owning this State
		State(StateMachine *_Owner) : Owner(_Owner) {};
		//! Virtual destructor to ensure valid destructor calls in children
		virtual ~State() {};

		//Declare pure virtual State functions
		//! Pure virtual method to be called when the State is transitioned into- perform any setup here
		virtual void Enter() = 0;
		//! Pure virtual method to be called when constantly updating the State- do any main loop logic here
		virtual void Update(float deltaTime) = 0;
		//! Pure virtual method to be called when a State is being transitioned out of- perform any clean-up here
		virtual void Exit() = 0;
		/// \brief Pure virtual Clone method. Allows polymorphic cloning of State instances where necessary.
		/// Very important to implement if you plan on copying StateMachines in your code!
		///
		/// \param NewOwner A pointer to the new StateMachine which is to own this copy.
		virtual State *Clone(StateMachine *NewOwner) const = 0;

	protected:
		//Declare protected properties
		//! Pointer to the owning StateMachine- this can be used to influence the Owner as necessary
		StateMachine *Owner;
	};
}

#endif