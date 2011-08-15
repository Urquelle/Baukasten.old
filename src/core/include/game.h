#ifndef GAME_H
#define GAME_H

#include "global.h"

#include <memory>

namespace Baukasten {
    namespace Core {
        class LogicalSpace;
        class VirtualSpace;

        class BAUKASTEN_EXPORT Game {
        public:
            Game();
            virtual ~Game();

            virtual void start();
            virtual void pause();
            virtual void stop();

        private:
            void run();
            void processUserInput();
            void renderScene();

            std::shared_ptr<LogicalSpace> mLogicalSpace;
            std::shared_ptr<VirtualSpace> mVirtualSpace;
            bool mKeepRunning;
        };
    }
}

#endif // GAME_H

