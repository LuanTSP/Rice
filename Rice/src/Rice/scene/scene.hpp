#include "../core/application.hpp"

namespace Rice
{
    class Scene
    {
        public:
            // Function called automatically when the Scene
            // is loaded into view.
            virtual void onLoad() = 0;

            // Function called automatically every frame
            // @param dt: float (delta time between frames in secons)
            virtual void onUpdate(float dt) = 0;
        private:
    };
}