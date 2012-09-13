/*
  MCP4131 Digital Potentiometer example (for Maple IDE)
 
Example to test MCP4131 from sparkfun: http://www.sparkfun.com/products/10613
 
 Circuit:
 * MCP4131 attached to pins 9, 11, 12, 13 (Pin 10 on Maple cannot be used as CS when Master)
 * SDO is connected to a 4.7K resitor before it connect to the shared SDI/SDO Pin
 * Analog inputs attached to pins A0 through A5 (optional)
 
Original Example Created by Dennis Liang on 11/20/2011 (For Arduino)
Orginal MCP4161 implementation from https://github.com/declanshanaghy/ArduinoLibraries/tree/master/MCP4161

Modified for Maple IDE by BD (Johnnyonthespot) 9/12/2012
This MCP4161 implementation is found @ https://github.com/johnnyonthespot/MapleLibraries
 
 */

#include <MCP4131.h>

//setup an intance of MCP4131
MCP4131 MCP4131(9); // with a CS pin of 9 (pin 10 cannot be used as chip select line on Maple)

int tapValue = 1;        // will store last time LED was updated

void setup(void)
{
  SerialUSB.println("MCP4231 Test:");
  
  //Initialize MCP4131 to 0
  MCP4131.setTap(MCP4131_MIN); //Sets the pot to 0.

  if (MCP4131.initTCON())  //init the pot, connect wiper0, and turn ON pot
  {
    SerialUSB.println("Init Error!");
  }
  
  
}

void loop(void)
{
  delay(1000);
  
  if (MCP4131.readTCON()==false)
  {
    SerialUSB.print("TCON:");
    SerialUSB.println(MCP4131.Tcon_Reg, BIN); ///wiper and shutdown control bits //should be all one
  }
    
  if (MCP4131.readStatus()==false)
  {
    SerialUSB.print("STATUS:");
    SerialUSB.println(MCP4131.Status_Reg, BIN); ///wiper and shutdown control bits //should be all one
  }
  
   if (MCP4131.readTap()==false)
  {
    SerialUSB.print("WIPER:");
    SerialUSB.println(MCP4131.Wiper_Reg, DEC); //Where the wiper position
  }
 
   if (MCP4131.setTap(tapValue))
  {
    SerialUSB.println("setTap Error!");
  }
   else
  {
    tapValue++;    
    if (tapValue > 128)
   {
	 tapValue = 0;
   }
     SerialUSB.print("WIPER AFTER SET:");
     SerialUSB.println(MCP4131.Wiper_Reg, DEC); //Wiper register is updated
   }
    
    if (MCP4131.increment())
   {
     SerialUSB.println("increment Error!"); //Try to Increment
   }
    
   if (MCP4131.readTap()==false)
  {
     SerialUSB.print("WIPER AFTER INCREMENT:");
     SerialUSB.println(MCP4131.Wiper_Reg, DEC);
  }
     
    
   if (MCP4131.decrement())
  {
     SerialUSB.println("decrement Error!"); //Try to decrement
  }
   
   if (MCP4131.readTap()==false)
   {
     SerialUSB.print("WIPER AFTER DECREMENT:");
     SerialUSB.println(MCP4131.Wiper_Reg, DEC);
   }
 
}