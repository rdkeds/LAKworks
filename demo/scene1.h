#ifndef SCENE1_H
#define SCENE1_H

#include "common/scene.h"

class Scene1 : public Scene
{
    public:
        Scene1();
        ~Scene1();

        void Update();

    private:

      Gameobject* gameobject;
      Light* light;

};

#endif
