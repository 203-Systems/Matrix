 #include "MatrixMath.h"

MatrixMath::MatrixMath(){
}
	
int MatrixMath::num2XY(int num){     //1~64 > 0~7*0~7
	int X = (num-1)/8;
	int Y = (num-1)%8;
	int Array[] = {X,Y};
	return Array;
}

int MatrixMath::num2X(int num){     //1~64 > 0~7*0~7
	int X = (num-1)/8;
	return X;
}

int MatrixMath::num2Y(int num){     //1~64 > 0~7*0~7
	int Y = (num-1)%8;
	return Y;
}

int MatrixMath::MIDI2XY(int key){
  int X;int Y;
if(key>34 && key <99){
  if(key <67){
    X = 7-(key-35)/4;
    Y = (key-35)%4;
  }else{
    X = 7-(key-35)/4;
    Y = (key-35)%4+4;
    }
  }
  int Array[] = {7-X,Y};	
  return Array;
}

int MatrixMath::MIDI2X(int key){
  int X;
if(key>34 && key <99){
  if(key <67){
    X = 7-(key-35)/4;
  }else{
    X = 7-(key-35)/4;
    }
  }
  return 7-X;
}


int MatrixMath::MIDI2Y(int key){
  int Y;
if(key>34 && key <99){
  if(key <67){
    Y = (key-35)%4;
  }else{
    Y = (key-35)%4+4;
    }
  }
  return Y;
}

