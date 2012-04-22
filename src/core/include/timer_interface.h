#ifndef TIMER_INTERFACE_H_CTPOJPXY
#define TIMER_INTERFACE_H_CTPOJPXY

#include "core/Global"

namespace Baukasten {

	class TimerInterfacePrivate;
	class Timer;

	/*!
	 * \brief TimerInterface class declaration.
	 * \ingroup core
	 * \headerfile TimerInterface "core/TimerInterface"
	 *
	 * interface class implementing Timer management routines. lets you
	 * create, fetch or destroy a timer object.
	 */
	class BAUKASTEN_EXPORT TimerInterface {
	public:

		/*!
		 * \brief singleton method to retrieve TimerInterface object.
		 * \return pointer to the TimerInterface object.
		 */
		static TimerInterface* instance();

		/*!
		 * \brief create a new Timer object.
		 *
		 * creates a new timer object which is stored under the given id. the
		 * created Timer object is returned.
		 *
		 * \note if id is already in the collection, the application exits in
		 * the development version.
		 *
		 * \param id id as the key for the collection.
		 * \return reference to the created Timer object.
		 */
		Timer& createTimer( const string& );

		/*!
		 * \brief get the timer to the given id.
		 * \note if no timer is found under the given id, the application exits.
		 * \param id id of the timer.
		 * \return Timer object that is stored under the given id in the
		 * collection.
		 */
		Timer& timer( const string& );

		/*!
		 * \brief destroy a timer.
		 * removes the timer from collection and deletes the Timer instance.
		 * \param id id of the timer that is destroyed.
		 */
		void   destroyTimer( const string& );

		/*!
		 * \brief update all timer at once.
		 *
		 * goes through the list of timers and calls their update method.
		 */
		void   updateAll() const;

	private:
		TimerInterface();
		virtual ~TimerInterface();

		static TimerInterface* m_instance;

		BK_IMPL_PTR( TimerInterface );
	};
} /* Baukasten */

#endif /* end of include guard: TIMER_INTERFACE_H_CTPOJPXY */

