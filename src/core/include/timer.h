#ifndef TIMER_H_LNXYQFUZ
#define TIMER_H_LNXYQFUZ

#include "core/Global"

namespace Baukasten {

	class TimerPrivate;

	/*!
	 * \ingroup core
	 * \headerfile Timer "core/Timer"
	 * \brief Timer class declaration.
	 *
	 * provides a high resolution timer functionality.
	 */
	class BAUKASTEN_EXPORT Timer {
	public:

		/*!
		 * \brief reset the timer.
		 *
		 * resets the time that passed since the timer started.
		 */
		void reset();

		/*!
		 * \brief starts the timer.
		 *
		 * initialises the internal values and sets the elapsed time to 0.
		 */
		void start();

		/*!
		 * \brief pauses the timer.
		 *
		 * elapsed isn't updated if the timer is set to pause.
		 */
		void setPause( bool );

		/*!
		 * \brief query if timer is paused.
		 * \return bool true if timer is paused, false otherwise.
		 */
		bool isPaused() const;

		/*!
		 * \brief set the scale that the timer should run at.
		 *
		 * calibrate the timer to run at a certain pace. for instance
		 * setting scale to 0.5 will result in all operations based on
		 * this timer to run at half of the normal speed.
		 *
		 * \param scale value by that the timer is scaled.
		 */
		void setTimeScale( const f32 );

		/*!
		 * \brief query the current scale of the timer.
		 * \return float timer's scale rate.
		 */
		f32  timeScale() const;

		/*!
		 * \brief cpu cycles that passed.
		 * \return u64 cpu cycles that have passed since the timer
		 * was started.
		 */
		u64  cycles() const;

		/*!
		 * \brief time that passed.
		 *
		 * \return f32 seconds that have passed since the timer
		 * was started.
		 */
		f32  time() const;

		/*!
		 * \brief update the timer.
		 * elapsed time is recalculated here, if the timer isn't paused.
		 */
		void update();

	private:
		friend class TimerInterfacePrivate;

		explicit Timer();
		Timer( const Timer& );
		Timer operator=( const Timer& );
		virtual ~Timer();

		BK_IMPL_PTR( Timer );
	};
} /* Baukasten */

#endif /* end of include guard: TIMER_H_LNXYQFUZ */

