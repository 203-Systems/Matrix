#ifndef NEXUS_H
#define NEXUS_H

#define UPS 4 //UpdatePerSec
#define MAXELEMENT 20
#define MAXUSERELEMENT 20

#include "Arduino.h"
#include <USBComposite.h>
// #include "../Parameter/MatrixVariable.h"
// #include "../Parameter/MatrixParameter.h"
// #include "../Core/MatrixSystem.h"
#include "../HAL/KeyPad.h"
#include "../HAL/LED.h"
#include "../HAL/Timer.h"

extern LED LED;
extern KeyPad KeyPad;

struct NexusElement
{
  u8 location; //b11000000 for side b00111111 for # but currently only support for 8
  u8 hue; //0~15 203palette
  u8 step = 255; //time to live
};

struct UserElement
{
  u8 xy;
  u8 hue; //0~15 203palette
  u8 step = 255; //time to live
};

class NexusRevamped
{
public:
  NexusRevamped();
  ~NexusRevamped();
  void tick();
private:
  void readKey()
  void update();
  void render();
  void spawn();
  void createElement();
  void spawnInput();
  void createUserElement();
  NexusElement element[MAXELEMENT];
  UserElement userElement[MAXUSERELEMENT];
  u8 nextElement = 0;
  u8 nextUserElement = 0;
};
