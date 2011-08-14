#ifndef GAME_H
#define GAME_H

#include <memory>

namespace Eisenfaust
{
    namespace Core
    {
        class LogicalSpace;
        class VirtualSpace;

        class Game
        {
        public:
            Game();
            virtual ~Game();

            virtual void start();
            virtual void pause();
            virtual void stop();

        private:
            std::shared_ptr<LogicalSpace> mLogicalSpace;
            std::shared_ptr<VirtualSpace> mVirtualSpace;
        };
    }
}

#endif // GAME_H

