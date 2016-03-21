#ifndef SCENE2_H
#define SCENE2_H

#include "common/scene.h"

class Scene2 : public Scene
{
    public:
        Scene2();
        ~Scene2();

        void Update();

    private:

      Gameobject* gameobject;
      Gameobject* gameobject2;

};

#endif
