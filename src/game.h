#ifndef GAME_H
#define GAME_H

#include <memory>

namespace Eisenfaust
{
    class LogicalSpace;
    class VirtualSpace;

    class Game
    {
    public:
        Game();
        virtual ~Game();

        void start();
        void pause();
        void stop();

    private:
        std::shared_ptr<LogicalSpace> m_lSpace;
        std::shared_ptr<VirtualSpace> m_vSpace;
    };
}

#endif // GAME_H

