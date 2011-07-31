#ifndef GAME_H
#define GAME_H

namespace Eisenfaust
{
    class Game
    {
    public:
        Game();
        virtual ~Game();

        void start();
        void pause();
        void stop();
    };
}

#endif // GAME_H

