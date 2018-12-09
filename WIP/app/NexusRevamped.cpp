NexusRevamped::NexusRevamped()
{
  LED.enableOverlayMode();

  Timer updateTimer;
  Timer spawnTimer;

  while(!USBComposite.isReady())
  {
    if(spawnTimer.tick(1500))
    {
      NexusRevamped::spawn()
    }

    if(updateTimer.tick(1000/UPS))
    {
      NexusRevamped::update(0);
    }
    NexusRevamped::ReadKey();
  }

  LED.enableOverlayMode();
  NexusRevamped::~NexusRevamped();
}

NexusRevamped::~NexusRevamped()
{

}

void NexusElement::ReadKey()
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
  for(int i = 0; i < 20; i ++)
  {
    if(element[i].ttl > 0)
    element[i].ttl --;
    if(userElement[i].ttl > 0)
    userElement[i].ttl --;
  }
}

void NexusRevamped::render()
{
  

}

void NexusRevamped::spawn()
{
  NexusRevamped::createElement(nextElement);
  nextElement ++;

  if(nextElement == 20)
  nextElement = 0;

  return;
}

void NexusRevamped::createElement(u8 i)
{
  element[i].ttl = 12;
  element[i].hue = random(16);
  element[i].location = random(32);
}

void NexusRevamped::spawnInput(u8 xy)
{
  NexusRevamped::createUserElement(nextUserElement, xy);
  nextUserElement ++;

  if(nextUserElement == 20)
  nextUserElement = 0;

  return;
}

void NexusRevamped::createUserElement(u8 i, u8 xy)
{
  element[i].ttl = 12;
  element[i].hue = random(16);
  element[i].xy = xy;
}
