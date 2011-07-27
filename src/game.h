#ifndef GAME_H
#define GAME_H

namespace Eisenfaust
{
    class Game
    {
    public:
        static Game& instance();

        virtual ~Game();

        void start();
        void pause();
        void stop();
    private:
        Game();

        static Game* m_instance;
    };
}

#endif // GAME_H

