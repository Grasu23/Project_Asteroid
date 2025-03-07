#pragma once

#include <memory>

///@brief
///Singleton pattern-based class that ensures the encapsulation of the screen's height and width and the game's multiplier.
///The singleton design pattern is used to ensure that the dimensions are safely stored in only one instance of the class.
///

class DefaultParameters {
private:
  int RenderWidth;
  int RenderHeight;
  float Multiplier;
  float AspectRatio;

  /// 
  /// @brief Pointer to the singleton class pointer
  /// that designates the screen's width and height
  /// and the game's overall multiplier.
  /// 

  static DefaultParameters * DefPars;

  DefaultParameters ( ) = default;
  ~DefaultParameters ( ) = default;

public:

  static DefaultParameters* & GetInstance ( );

  static void SetRenderDimensions ( int, int );
  static void SetMultiplier ( float );
  static float GetMultiplier ( );
  static int GetRenderWidth ( );
  static int GetRenderHeight ( );

  static void FreeInstance ( );

  DefaultParameters ( const DefaultParameters & ) = delete;
  DefaultParameters & operator = ( const DefaultParameters & ) = delete;

};

enum MenuStates { MENU, PLAYING, PAUSE, SETTINGS, EXIT};

enum WeaponTypes{LASER};