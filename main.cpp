#include <iostream>
#include <ostream>
#include <raylib.h>
//#include <raymath.h>
#include <cmath>

static float ScreenWidth = 1280;
static float ScreenHeight = 800;
static float DefaultRotation = 30;
//
// Implicit, sprite-ul face un unghi de 30 de grade la stanga fata de verticala

static float Multiplier = 2.f; // de variabila asta depinde factorul de multiplicare al tuturor variatiilor

//Inceput implementare clasa singleton pentru a nu a mai tine parametrii impliciti ca variabile globale

class DefaultParameters
{
private:
  float ScreenWidth;
  float ScreenHeight;
  float DefaultRotation;
  float Multiplier;
  
  static DefaultParameters* InstancePtr;
  DefaultParameters();

public:
  DefaultParameters(const DefaultParameters& obj) = delete;
  
  static DefaultParameters* GetInstance() { return InstancePtr; }
  void set_screen_width(const float screen_width)
  {
    ScreenWidth = screen_width;
  }
  void set_screen_height(const float screen_height)
  {
    ScreenHeight = screen_height;
  }
  void set_default_rotation(const float default_rotation)
  {
    DefaultRotation = default_rotation;
  }
  void set_multiplier(const float multiplier) { Multiplier = multiplier; }
};

enum { MENU, SETTINGS, PLAYING, PAUSE, SHUTDOWN };

class Projectile
{
private:
  unsigned ProjectileType;
  unsigned ProjectileSpeed;
  unsigned ProjectileDamage;
  Vector2 ProjectilePosition;

public:
  Projectile() = default;
  
  Projectile(unsigned ProjectileType,
             unsigned ProjectileSpeed,
             unsigned ProjectileDamage,
             const Vector2& ProjectilePosition)
    : ProjectileType( ProjectileType)
      , ProjectileSpeed( ProjectileSpeed)
      , ProjectileDamage( ProjectileDamage)
      , ProjectilePosition( ProjectilePosition)
  {
    std::cout << "S-a creat proiectilul " << this->ProjectileType << '\n';
  }
  
  Projectile(const Projectile& other)
    : ProjectileType( other .ProjectileType)
      , ProjectileSpeed( other .ProjectileSpeed)
      , ProjectileDamage(other.ProjectileDamage)
      , ProjectilePosition(other.ProjectilePosition)
  {
    std::cout << "S-a copiat proiectilul " << this->ProjectileType << '\n';
  }
  
  Projectile& operator=(const Projectile& other)
  {
    if (this == &other)
      return *this;
    ProjectileType = other .ProjectileType;
    ProjectileSpeed = other .ProjectileSpeed;
    ProjectileDamage = other.ProjectileDamage;
    ProjectilePosition = other.ProjectilePosition;
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Projectile& obj)
  {
    return os << "ProjectileType: " << obj.ProjectileType
              << "\nProjectyleSpeed: " << obj.ProjectileSpeed
              << "\nProjectileDamage: " << obj.ProjectileDamage
              << "\nProjectilePosition.x: " << obj.ProjectilePosition.x
              << "\nProjectilePosition.y: " << obj.ProjectilePosition.y << '\n';
  }
  
  ~Projectile() { std::cout << "Proiectilul a fost ratat\n"; }
};

class Player
{
private:
  std::string PlayerName;
  short PlayerLevel;
  short PlayerLives;
  float Rotation;
  Vector2 PlayerPosition;
  float Radius;
  int Sides;

public:
  Player() = default;
  
  Player(const std::string& PlayerName,
         short PlayerLevel,
         short PlayerLives,
         float Rotation,
         const Vector2& PlayerPosition,
         float Radius,
         int Sides)
    : PlayerName( PlayerName)
      , PlayerLevel( PlayerLevel)
      , PlayerLives( PlayerLives)
      , Rotation( Rotation)
      , PlayerPosition( PlayerPosition)
      , Radius( Radius)
      , Sides( Sides)
  {
    std::cout << "A fost creat jucatorul " << this->PlayerName << '\n';
  }
  
  Player(const Player& other)
    : PlayerName{ other.PlayerName }
      , PlayerLevel{ other.PlayerLevel }
      , PlayerLives{ other .PlayerLives }
      , Rotation{ other.Rotation }
      , PlayerPosition{ other.PlayerPosition }
      , Radius{ other.Radius }
      , Sides{ other.Sides }
  {
    std::cout << "A fost copiat jucatorul " << this->PlayerName << '\n';
  }
  
  Player& operator=(const Player& other)
  {
    if (this == &other)
      return *this;
    PlayerName = other.PlayerName;
    PlayerLevel = other.PlayerLevel;
    PlayerLives = other .PlayerLives;
    Rotation = other.Rotation;
    PlayerPosition = other.PlayerPosition;
    Radius = other.Radius;
    Sides = other.Sides;
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Player& obj)
  {
    return os << "PlayerName: " << obj.PlayerName << '\n'
              << " PlayerLevel: " << obj.PlayerLevel << '\n'
              << " PlayerLives: " << obj.PlayerLives << '\n'
              << " Rotation: " << obj.Rotation << '\n'
              << " PlayerPosition: " << obj.PlayerPosition.x << ' '
              << obj.PlayerPosition.y << '\n'
              << " Radius: " << obj.Radius << '\n'
              << " Sides: " << obj.Sides << '\n';
  }
  
  ~Player() { std::cout << "Jucator distrus\n"; }
  
  void Draw() const;
  
  void Update();
  
  Vector2 GetPos() const;
  
  void ShowPos() const;
};


void
Player::Draw() const
{
  DrawPolyLinesEx(
    this->PlayerPosition, this->Sides, this->Radius, this->Rotation, 2, RED);
}

void
Player::Update()
{
  bool rotated = 0; // cand playerul se misca inainte sau inapoi, daca nu se
  // previne intrarea
  // in ultima pereche de checkuri pentru rotatie, aceasta se va face de 2 ori
  // deci jucatorul se va roti de 2 ori mai mult daca se misca inainte-inapoi
  // (ar merge lasat feature si nu bug???? hmmmmm...)
  // de aia exista bool-ul asta
  if (IsKeyDown(KEY_UP)) {
    this->PlayerPosition.x +=
      cos((this->Rotation - 120) * DEG2RAD) * 1.5 * Multiplier;
    this->PlayerPosition.y +=
      sin((this->Rotation - 120) * DEG2RAD) * 1.5 * Multiplier;
    /*
    if (IsKeyDown(KEY_RIGHT)) {
      this->Rotation += 2 * Multiplier;
      rotated = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
      this->Rotation -= 2 * Multiplier;
      rotated = true;
    }
    */
  }
  if (IsKeyDown(KEY_DOWN)) {
    this->PlayerPosition.x -=
      cos((this->Rotation - 120) * DEG2RAD) * 1.5 * Multiplier;
    this->PlayerPosition.y -=
      sin((this->Rotation - 120) * DEG2RAD) * 1.5 * Multiplier;
    
    if (IsKeyDown(KEY_RIGHT)) {
      this->Rotation -= 2 * Multiplier;
      rotated = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
      this->Rotation += 2 * Multiplier;
      rotated = true;
    }
  }
  
  if (!rotated) {
    if (IsKeyDown(KEY_RIGHT)) {
      this->Rotation += 2 * Multiplier;
    }
    if (IsKeyDown(KEY_LEFT)) {
      this->Rotation -= 2 * Multiplier;
    }
  }
  
  if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
    Projectile p1(1, 10, 10, this->PlayerPosition);
    std::cout << "\n\n\n--Trage--\n\n\n";
  }
  
  // pentru ca jucatorul sa nu iasa din fereastra
  // trebuie impuse limite superioare/inferioare pentru unde poate ajunge
  // caracterul
  
  if (this->PlayerPosition.x < Radius / 2.)
    this->PlayerPosition.x = Radius / 2.;
  if (this->PlayerPosition.x > ScreenWidth - Radius / 2.)
    this->PlayerPosition.x = ScreenWidth - Radius / 2.;
  if (this->PlayerPosition.y < Radius / 2.)
    this->PlayerPosition.y = Radius / 2.;
  if (this->PlayerPosition.y > ScreenHeight - Radius / 2.)
    this->PlayerPosition.y = ScreenHeight - Radius / 2.;
  
  this->Draw();
  this->ShowPos();
}

void
Player::ShowPos() const
{
  std::cout << "Pozitie: " << this->PlayerPosition.x << ' '
            << this->PlayerPosition.y << '\n';
}

Vector2
Player::GetPos() const
{
  return this->PlayerPosition;
}


class Enemy
{
private:
  std::string EnemyName;
  short HealthPoints;
  short EnemyLevel;
  short EnemySpeed;

public:
  Enemy() = default;
  
  Enemy(const std::string& EnemyName,
        short HealthPoints,
        short EnemyLevel,
        short EnemySpeed)
    : EnemyName( EnemyName)
      , HealthPoints( HealthPoints)
      , EnemyLevel( EnemyLevel)
      , EnemySpeed( EnemySpeed)
  {
    std::cout << "Inamicul " << this->EnemyName << " a fost creat\n";
  }
  
  Enemy(const Enemy& other)
    : EnemyName{ other.EnemyName }
      , HealthPoints{ other.HealthPoints }
      , EnemyLevel{ other.EnemyLevel }
      , EnemySpeed{ other.EnemySpeed }
  {
    std::cout << "S-a copiat inamicul " << this->EnemyName << '\n';
  }
  
  Enemy& operator=(const Enemy& other)
  {
    if (this == &other)
      return *this;
    EnemyName = other.EnemyName;
    HealthPoints = other.HealthPoints;
    EnemyLevel = other.EnemyLevel;
    EnemySpeed = other.EnemySpeed;
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Enemy& obj) {
    return os
      << "EnemyName: " << obj.EnemyName
      << "\nHealthPoints: " << obj.HealthPoints
      << "\nEnemyLevel: " << obj.EnemyLevel
      << "\nEnemySpeed: " << obj.EnemySpeed;
  }
  
  ~Enemy() { std::cout << "Inamic Distrus\n"; }
};

class Menu
{
private:
  char state;

public:
  Menu() = default;
  
  Menu(char state)
    : state(state)
  {
    std::cout << "S-a creat meniul " << this->state << '\n';
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Menu& obj)
  {
    return os << "state: " << obj.state;
  }
  
  static void RunApp(Player&);
  
  ~Menu() { std::cout << "Gata cu fotosinteza, la culcare toata lumea!\n"; };
};

void
Menu::RunApp(Player& player)
{
  SetConfigFlags (FLAG_WINDOW_RESIZABLE);
  InitWindow(ScreenWidth, ScreenHeight, "Project Asteroid");
  SetTargetFPS(60);
  HideCursor();
  
  while (!WindowShouldClose()) {
    
    ScreenWidth=(float)GetScreenWidth();
    ScreenHeight=(float)GetScreenHeight();
    
    BeginDrawing();
    ClearBackground(BLACK);
    
    player.Update(); // apel catre functia de update pentru player
    
    EndDrawing();
  }
  
  CloseWindow();
}

int
main()
{
  
  Player p1("Gigel",
            1,
            5,
            DefaultRotation,
            { ScreenWidth / 2.f, ScreenHeight / 2.f },
            ScreenWidth / 60.,
            3);
  
  std::cout << p1;
  
  Menu Meniu(1);
  
  Meniu.RunApp(p1);
  
  Player* p2 = &p1;
  
  std::cout << p2;
  
  Enemy e1("Dorel", 10, 2, 100);
  
  std::cout << e1;
  
  Projectile pr1(1, 10, 50, p1.GetPos());
  std::cout << pr1;
}



