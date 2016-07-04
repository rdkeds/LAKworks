#ifndef SCENE2_H
#define SCENE2_H

#include "common/scene.h"

class Scene2 : public Scene
{
    public:
        Scene2();
        ~Scene2();

        void Update(GLFWwindow* window);

    private:

      Gameobject* playerController;

      Gameobject* cockpitWalls;
      Gameobject* cockpitChair1;
      Gameobject* cockpitChair2;
      Gameobject* cockpitChair3;
      Gameobject* cockpitTerminal;
      Gameobject* cockpitScreen1;
      Gameobject* cockpitScreen2;
      Gameobject* cockpitScreen3;
      Gameobject* cockpitSteer1;
      Gameobject* cockpitSteer2;
      Gameobject* cockpitMapBase;
      Gameobject* cockpitHoloCone;
      Gameobject* cockpitHoloSphere1;
      Gameobject* cockpitHoloSphere2;
      Gameobject* cockpitHoloSphere3;
      Gameobject* cockpitHoloSphere4;
      Gameobject* cockpitHoloSphere5;
      Gameobject* cockpitFloor;

};

#endif
