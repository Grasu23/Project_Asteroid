#pragma once


class CollisionBox {
protected:
  ///@brief Describes the size of the entity (player, enemy or projectile)
  ///based on its collision box radius.
  float Radius;
public:
  CollisionBox ( float );
  CollisionBox ( ) = default;
  ~CollisionBox ( ) = default;
};
