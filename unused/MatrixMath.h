#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif
 
 class MatrixMath{
	 public:
	 MatrixMath();
	 int num2XY(int num);
	 int num2X(int num);
	 int num2Y(int num);
	 int MIDI2XY(int key);
	 int MIDI2X(int key);
	 int MIDI2Y(int key);
 };