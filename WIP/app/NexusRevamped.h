#ifndef NEXUS_H
#define NEXUS_H

#define UPS 4 //UpdatePerSec

#include "Arduino.h"
#include <USBComposite.h>
// #include "../parameter/MatrixVariable.h"
// #include "../parameter/MatrixParameter.h"
// #include "../core/MatrixSystem.h"
#include "../core/KeyPad.h"
#include "../core/LED.h"
#include "../core/Timer.h"

extern LED LED;
extern KeyPad KeyPad;

struct NexusElement
{
  u8 location; //location of spawn 0~7 top to bottom,8~15 right to left, 16~23 bottom to top, 24~31 right to left
  u8 hue; //0~15 203palette
  u8 ttl = 0; //time to live
};

struct UserElement
{
  u8 xy;
  u8 hue; //0~15 203palette
  u8 ttl = 0; //time to live
};

class NexusRevamped
{
public:
  NexusRevamped();
  ~NexusRevamped();
private:
  void update();
  void render();
  void spawn();
  void createElement();
  void spawnInput();
  void createUserElement();
  NexusElement element[20];
  UserElement userElement[20];
  u8 nextElement = 0;
  u8 nextUserElement = 0;
};
