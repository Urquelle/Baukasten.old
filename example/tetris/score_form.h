#ifndef SCORE_FORM_H_MPIAXVNA
#define SCORE_FORM_H_MPIAXVNA

#include "model/Form"
#include "model/Global"

class ScoreForm : public Baukasten::Form {
public:
	ScoreForm( const string&, Baukasten::IGraphics* );
	virtual ~ScoreForm();

	void render();

private:
	/* data */
};

#endif /* end of include guard: SCORE_FORM_H_MPIAXVNA */

