#include "config.h"
#include "GCodeInterpreter.h"
#include "SMotor.h"
#include"Communication.h"

SMotor XStepper;
SMotor YStepper;
SMotor ZStepper;
SMotor TableStepper;

SMotor::SMotor( ){
  
  _abs_possition=0;
  _enable=0;
}

SMotor::~SMotor(){}

/* autor: Maciek Wiecheć
  Inicjalizacja pinów
*/

void SMotor::Init(uint8_t DirPin, uint8_t StepPin, uint8_t EnPin){
  _dir_pin=DirPin;
  _step_pin=StepPin;
  _enable_pin=EnPin;
  pinMode(_dir_pin, OUTPUT);
  pinMode(_step_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  digitalWrite(_enable_pin, HIGH);
  _enable = true;
}

/* autor: Maciek Wiecheć
  Podgląd aktualniej pozycji w swojej osi
*/
long SMotor::GetAbsPossition(){
  return _abs_possition;
}

/* autor: Maciek Wiecheć
  Podgląd czy enable T/F
*/
bool SMotor::GetBoolEnable(){
  return _enable;
}


/* autor: Maciek Wiecheć
  Ustawianie Enable, nie wiem czy potrzebne ale jest
*/
void SMotor::SetEnable(bool EN){
  _enable=EN;
  digitalWrite(_enable_pin, EN);
}


/* autor: Maciek Wiecheć
  Wykonanie pojedynczego kroku
*/
void SMotor::Step (int DIR){
	//MMcomm.SendMessage("step en: " + (String)_enable);
  if(_enable==0){
    if(DIR>0) digitalWrite(_dir_pin,HIGH);
    else digitalWrite(_dir_pin, LOW);

    digitalWrite(_step_pin,HIGH);
    digitalWrite(_step_pin,LOW);
	//MMcomm.SendMessage("step" + (String)DIR);
  }
  
}

