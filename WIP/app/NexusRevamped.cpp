void NexusRevamped()
{
  struct NexusElement
  {
    uint8_t spawn; //location of spawn 0~8 top down,
    uint8_t hue; //0~15 203palette
    uint8_t ttl = 0; //time to live
  }

  uint32_t randertimer = 0;
  uint32_t spawntimer = 0;

  while (/*!Serials*/) {
    if(mills() - randertimer >= 1000/FPS)
    {

    }
  }

}
