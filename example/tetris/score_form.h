#ifndef SCORE_FORM_H_MPIAXVNA
#define SCORE_FORM_H_MPIAXVNA

#include <irrlicht/irrlicht_form.h>

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

class ScoreForm : public Baukasten::IrrlichtForm {
public:
	ScoreForm( const string&, Baukasten::IGraphics* );
	virtual ~ScoreForm();

	void render();

private:
	/* data */
};

#endif /* end of include guard: SCORE_FORM_H_MPIAXVNA */

