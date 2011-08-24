#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <game_entity.h>

#include <string>

class ExampleGame : public Baukasten::GameEntity
{
public:
    ExampleGame( const std::string &id );
    virtual ~ExampleGame();

    void start();
    void stop();

	bool keepRunning() const;

protected:
    void run();
	void init();
};

#endif /* end of include guard: GAME_QESA072Y */

