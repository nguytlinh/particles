// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "confetti.h"

using namespace std;
using namespace agl;
using namespace glm;

void Confetti::createParticles(int size) 
{
   mTexture = theRenderer.loadTexture("../textures/particle.png");
   // TODO: Create particles

   for (int i = 0; i < size; i++) {
       vec3 veloc = random_unit_vector();
       Particle p = { random_unit_cube(), vec3(0.5 * veloc.x, 0.5 * veloc.y, 0.5 * veloc.z), vec4(random_unit_vector(), 1.0), 0.25f, 1.0f };
       mParticles.push_back(p);
   }
}

void Confetti::update(float dt)
{
    for (int i = 0; i < mParticles.size(); i++) {
        Particle current = mParticles[i];
        vec3 pos = current.pos;
        vec3 vel = current.vel;
        if (pos.z <= -1 || pos.z >= 1)
            vel.z = -vel.z;
        if (pos.x <= -1 || pos.x >= 1) 
            vel.x = -vel.x;
        if (pos.y <= -1 || pos.y >= 1) 
            vel.y = -vel.y;
        current.vel = vel;
        current.pos = pos + (vel * dt);
        
        mParticles[i] = current;
    }

    // cheap sort
    if (mParticles.size() > 1) 
    {
        Particle p = mParticles[0];
        for (int i = 1; i < mParticles.size(); i++) 
        {
            Particle currP = mParticles[i];
            float d1 = distance(theRenderer.cameraPosition(), p.pos);
            float d2 = distance(theRenderer.cameraPosition(), currP.pos);
         
            if (d2 > d1) swap(mParticles[i], mParticles[i - 1]);
            
            p = mParticles[i];
        }
    }
   
}

