void NexusRevamped()
{
  struct NexusElement
  {
    u8 spawn; //location of spawn 0~8 top down,
    u8 hue; //0~15 203palette
    u8 ttl = 0; //time to live
  }

  u32 randertimer = 0;
  u32 spawntimer = 0;

  while (/*!Serials*/) {
    if(mills() - randertimer >= 1000/FPS)
    {

    }
  }

}
