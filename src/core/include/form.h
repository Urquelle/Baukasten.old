#ifndef FORM_H
#define FORM_H

#include "global.h"
#include "drawable.h"

#include <string>

namespace Baukasten {
    namespace Core {
        class BAUKASTEN_EXPORT Form : public Drawable {
        public:
            Form();
            virtual ~Form() = 0;

        protected:
            std::string mMeshName;

            // can contain space objects
        };
    }
}

#endif // FORM_H

