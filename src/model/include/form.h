#ifndef FORM_H
#define FORM_H

#include "model/Drawable"
#include "model/EntityManager"
#include "model/Global"
#include "model/StateManager"

#include <string>

namespace Baukasten {
	class IGraphics;
	class LogicalSpace;
	class VirtualSpace;

	/*!
	 * \ingroup model
	 * @{
	 *
	 * \class Form
	 * \brief implementation of the Form entity in the model.
	 * \headerfile Form "model/Form"
	 *
	 * Form represents the graphics presentation layer of each Entity.
	 * this class communicates directly with the graphicsService in
	 * order to draw every part of the game.
	 *
	 * here's an example taken from examples/tetris game and its score
	 * drawing routine.
	 *
	 * \include examples/tetris/score_form.cpp
	 */
	class BAUKASTEN_EXPORT Form : public Drawable,
	public EntityManager, public StateManager {
	public:
		/*!
		 * \brief constructor
		 *
		 * \param id unique name of the object.
		 */
		Form( const string& );

		/*! destructor */
		virtual ~Form();

		/*!
		 * \brief add a GameEntity object to LogicalSpace.
		 *
		 * this is just a convenience method, that in turn calls
		 * the addToLSpace( const string&, GameEntity* ) method with
		 * GameEntity::id() as the first argument.
		 *
		 * \sa addToLSpace( const string&, GameEntity* )
		 *
		 * \param entity GameEntity object.
		 */
		void addToLSpace( GameEntity* );

		/*!
		 * \brief add a GameEntity object to LogicalSpace.
		 *
		 * takes the given GameEntity object and puts it to the form's
		 * logical space collection. in this collection are only those
		 * objects that are active in this time of the game.
		 *
		 * __only the actions of the active objects are executed__.
		 *
		 * \param id id of the GameEntity in the collection.
		 * \param entity GameEntity object.
		 */
		void addToLSpace( const string&, GameEntity* );

		/*!
		 * \brief remove an object from the LogicalSpace.
		 *
		 * removes the GameEntity object from the LogicalSpace that is
		 * stored under the given id.
		 *
		 * \param id id under that the GameEntity is stored in LogicalSpace.
		 */
		void removeFromLSpace( const string& );

		/*!
		 * \brief retrieve the LogicalSpace collection.
		 *
		 * \return a pointer to the LogicalSpace collection.
		 */
		LogicalSpace* lSpace() const;

		/*!
		 * \brief add a Form object to the VirtualSpace.
		 *
		 * adds a Form object to the VirtualSpace collection. as Form
		 * represents the graphical representation of a GameEntity, adding
		 * this representation to the virtual space results in this
		 * object being drawn eventually.
		 *
		 * this is a convenience method, which delegates the further
		 * procedure to the addToVSpace() method with the given Form object's
		 * id.
		 *
		 * \param entity Form object of the GameEntity.
		 * \sa addToVSpace( const string&, Form* )
		 */
		void addToVSpace( Form* );

		/*!
		 * \brief add a Form object to the VirtualSpace.
		 *
		 * adds a Form object to the VirtualSpace collection. as Form
		 * represents the graphical representation of a GameEntity, adding
		 * this representation to the virtual space results in this
		 * object being drawn eventually.
		 *
		 * keep in mind that the id has to be unique in the target collection.
		 * in case the id is already present, the application exits.
		 *
		 * \param id id to store the Form object in the collection.
		 * \param entity Form object of the GameEntity.
		 */
		void addToVSpace( const string&, Form* );

		/*!
		 * \brief remove a Form object from the VirtualSpace.
		 *
		 * removes a Form object from the VirtualSpace that is stored
		 * under the given id.
		 *
		 * \param id id under which the Form object is stored in the collection.
		 */
		void removeFromVSpace( const string& );

		/*!
		 * \brief retrieve the VirtualSpace collection.
		 *
		 * \return a pointer to the VirtualSpace collection.
		 */
		VirtualSpace* vSpace() const;

		/*!
		 * \brief constructs the scene to be drawn.
		 *
		 * goes through the VirtualSpace objects to call their constructScene()
		 * method and their render() method.
		 */
		virtual void constructScene();

		/*!
		 * \brief draw the scene.
		 *
		 * whatever has to be done to graphically represent the wanted object, this
		 * is the right place to do this.
		 */
		virtual void render();

		/*!
		* \brief getter method for the IGraphics implementation.
		* \return the object from a class that implements the IGraphics
		* interface.
		*/
		IGraphics& graphics();

	private:
		shared_ptr<LogicalSpace> m_lSpace;
		shared_ptr<VirtualSpace> m_vSpace;
	};
	/** @} */
}

#endif // FORM_H

