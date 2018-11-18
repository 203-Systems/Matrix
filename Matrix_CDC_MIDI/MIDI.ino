void MIDIon() {
  if (Return) {
    if (CDCenable) {
      CDC.print(channel);
      CDC.print("\ton\t");
      CDC.print(note);
      CDC.print("\t");
      CDC.println(velocity);
    }
  }
}

void MIDIoff() 
{
  if (Return) 
  {
    
    if (CDCenable) 
    {
      CDC.print(channel);
      CDC.print("\toff\t");
      CDC.print(note);
      CDC.print("\t");
      CDC.println(velocity);
    }
  }
}

