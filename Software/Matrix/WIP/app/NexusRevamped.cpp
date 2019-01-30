NexusRevamped::NexusRevamped()
{
  LED.enableOverlayMode();

  Timer updateTimer;
  Timer spawnTimer;
}

NexusRevamped::~NexusRevamped()
{
    LED.disableOverlayMode();
    LED.fill_solid(0);
}

void NexusRevamped::tick()
{
  if(spawnTimer.tick(1500))
  {
    NexusRevamped::spawn()
  }

  if(updateTimer.tick(1000/UPS))
  {
    NexusRevamped::update();
  }
  NexusRevamped::readKey();
}

void NexusElement::readKey()
{
  for(int i = 0; i < MULTIPRESS; i++)
  {
    if(KeyPad.list[i].velocity > 128)
    return;

    if(KeyPad.list[i].velocity > 0)
    {
      NexusRevamped::spawnInput(KeyPad.list[i].xy);
    }
  }
}

void NexusRevamped::update()
{
  for(int i = 0; i < MAXELEMENT; i ++)
  {
    if(element[i].ttl > 0)
    element[i].ttl --;
    if(userElement[i].ttl > 0)
    userElement[i].ttl --;
  }
}

void NexusRevamped::render()
{
  for(int i = 0; i < MAXELEMENT;++)
  {
    //Calc pixels to render

    if(element[i].location & b11000000 == 0)
    {

      for(int t = 0; t < 6; t ++)
      {
        LED.setXYPalette(element[i].location & b11000000, t, 0, t + ttl) //outdated api
      }

    }
    else if(element[i].location & b11000000 == 1)
    {

    }
    else if(element[i].location & b11000000 == 2)
    {

    }
    else if(element[i].location & b11000000 == 3)
    {

    }

  }


}

void NexusRevamped::spawn()
{
  NexusRevamped::createElement(nextElement);
  nextElement ++;

  if(nextElement == MAXELEMENT)  //overrite
  nextElement = 0;

  return;
}

void NexusRevamped::createElement(u8 i)
{
  element[i].step = 0;
  element[i].hue = random(16);
  element[i].location = random(4) * b1000000 + random(8);
}

void NexusRevamped::spawnInput(u8 xy)
{
  NexusRevamped::createUserElement(nextUserElement, xy);
  nextUserElement ++;

  if(nextUserElement == MAXUSERELEMENT)
  nextUserElement = 0;

  return;
}

void NexusRevamped::createUserElement(u8 i, u8 xy)
{
  element[i].step = 0;
  element[i].hue = random(16);
  element[i].xy = xy;
}
