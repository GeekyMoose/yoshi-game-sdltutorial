#include "gameplay/Player.h"

// -----------------------------------------------------------------------------
// Entity functions override
// -----------------------------------------------------------------------------

void Player::doAnimate() {
    Entity::doAnimate();
    if(speedX==0){
        animEntity.setNbFrames(0);
    }
    else{
        animEntity.setNbFrames(8);
    }
}