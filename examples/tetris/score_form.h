#ifndef SCORE_FORM_H_MPIAXVNA
#define SCORE_FORM_H_MPIAXVNA

#include "model/Form"
#include "model/Global"

namespace Baukasten {
	class IFont;
} /* Baukasten */

class ScoreForm : public Baukasten::Form {
public:
	ScoreForm( const std::string& );
	virtual ~ScoreForm();

	void render();

private:
	Baukasten::IFont* m_font;
};

#endif /* end of include guard: SCORE_FORM_H_MPIAXVNA */

