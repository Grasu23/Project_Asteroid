//
// Created by haisa on 26/11/2024.
//
#pragma once

#include "./Entity.hpp"
#include "./CollisionBox.hpp"

#pragma once

class Projectile : public Entity, public CollisionBox {
private:
  int projectile_type;
  int projectile_damage;
public:

};

