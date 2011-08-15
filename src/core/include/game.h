#ifndef GAME_H
#define GAME_H

#include "global.h"

#include <memory>

namespace Eisenfaust
{
    namespace Core
    {
        class LogicalSpace;
        class VirtualSpace;

        class EF_EXPORT Game
        {
        public:
            Game();
            virtual ~Game();

            virtual void start() = 0;
            virtual void pause() = 0;
            virtual void stop() = 0;

        private:
            std::shared_ptr<LogicalSpace> mLogicalSpace;
            std::shared_ptr<VirtualSpace> mVirtualSpace;
        };
    }
}

#endif // GAME_H

