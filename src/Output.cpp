
#include "Output.h"
#include "EEStore.h"
#include "StringFormatter.h"

// print all output states to stream
void Output::printAll(Print *stream){
  for (Output *tt = Output::firstOutput; tt != NULL; tt = tt->nextOutput)
    StringFormatter::send(stream, F("<Y %d %d>\n"), tt->data.id, tt->data.oStatus);
} // Output::printAll

void  Output::activate(int s){
  data.oStatus = (s > 0);
  // set state of output pin to HIGH or LOW
  // depending on whether bit zero of iFlag is set to 0 (ACTIVE=HIGH) or 1 (ACTIVE=LOW)
  digitalWrite(data.pin, data.oStatus ^ bitRead (data.iFlag,0));
  if (num > 0)
    EEPROM.put (num, data.oStatus);
}

///////////////////////////////////////////////////////////////////////////////

void Output::load(){
  struct BrokenOutputData bdata;
  Output *tt;
  bool isBroken=1;

  // This is a scary kluge. As we have two formats in EEPROM due to an
  // earlier bug, we don't know which we encounter now. So we guess
  // that if in all entries this byte has value of 7 or lower this is
  // an iFlag and thus the broken format. Otherwise it would be a pin
  // id. If someone uses only pins 0 to 7 of their arduino, they
  // loose. This is (if you look at an arduino) however unlikely.

  for(uint16_t i=0;i<EEStore::eeStore->data.nOutputs;i++){
    EEPROM.get(EEStore::pointer()+ i*sizeof(struct BrokenOutputData),bdata);
    if (bdata.iFlag > 7) { // it's a pin and not an iFlag!
      isBroken=0;
      break;
    }
  }
  if ( isBroken ) {
    for(uint16_t i=0;i<EEStore::eeStore->data.nOutputs;i++){
      EEPROM.get(EEStore::pointer(),bdata);
      tt=create(bdata.id,bdata.pin,bdata.iFlag);
      tt->data.oStatus=bitRead(tt->data.iFlag,1)?bitRead(tt->data.iFlag,2):bdata.oStatus;      // restore status to EEPROM value is bit 1 of iFlag=0, otherwise set to value of bit 2 of iFlag
      digitalWrite(tt->data.pin,tt->data.oStatus ^ bitRead(tt->data.iFlag,0));
      pinMode(tt->data.pin,OUTPUT);
      tt->num=EEStore::pointer();
      EEStore::advance(sizeof(struct BrokenOutputData));
    }
  } else {
    struct OutputData data;

    for(uint16_t i=0;i<EEStore::eeStore->data.nOutputs;i++){
      EEPROM.get(EEStore::pointer(),data);
      tt=create(data.id,data.pin,data.iFlag);
      tt->data.oStatus=bitRead(tt->data.iFlag,1)?bitRead(tt->data.iFlag,2):data.oStatus;      // restore status to EEPROM value is bit 1 of iFlag=0, otherwise set to value of bit 2 of iFlag
      digitalWrite(tt->data.pin,tt->data.oStatus ^ bitRead(tt->data.iFlag,0));
      pinMode(tt->data.pin,OUTPUT);
      tt->num=EEStore::pointer();
      EEStore::advance(sizeof(struct OutputData));
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void Output::store(){
  Output *tt;

  tt=firstOutput;
  EEStore::eeStore->data.nOutputs=0;

  while(tt!=NULL){
    tt->num=EEStore::pointer();
    EEPROM.put(EEStore::pointer(),tt->data);
    EEStore::advance(sizeof(tt->data));
    tt=tt->nextOutput;
    EEStore::eeStore->data.nOutputs++;
  }

}
///////////////////////////////////////////////////////////////////////////////

void Output::populate (uint16_t id, uint8_t pin, uint8_t iFlag, uint8_t v){
  
  data.id       = id;
  data.pin      = pin;
  data.iFlag    = iFlag;
  data.oStatus  = 0;

  if (v == 1) {
    // sets status to 0 (INACTIVE) is bit 1 of iFlag=0, otherwise set to value of bit 2 of iFlag
    if (bitRead (data.iFlag, 1))
      data.oStatus = bitRead (data.iFlag, 2);
    else
      data.oStatus = 0;

    digitalWrite (data.pin, data.oStatus ^ bitRead (data.iFlag, 0));
    pinMode (data.pin, OUTPUT);
  }
}

/***********************************************************************

DCC++ BASE STATION supports optional OUTPUT control of any unused Arduino Pins for custom purposes.
Pins can be activited or de-activated.  The default is to set ACTIVE pins HIGH and INACTIVE pins LOW.
However, this default behavior can be inverted for any pin in which case ACTIVE=LOW and INACTIVE=HIGH.

Definitions and state (ACTIVE/INACTIVE) for pins are retained in EEPROM and restored on power-up.
The default is to set each defined pin to active or inactive according to its restored state.
However, the default behavior can be modified so that any pin can be forced to be either active or inactive
upon power-up regardless of its previous state before power-down.

To have this sketch utilize one or more Arduino pins as custom outputs, first define/edit/delete
output definitions using the following variation of the "Z" command:

  <Z ID PIN IFLAG>:            creates a new output ID, with specified PIN and IFLAG values.
                               if output ID already exists, it is updated with specificed PIN and IFLAG.
                               note: output state will be immediately set to ACTIVE/INACTIVE and pin will be set to HIGH/LOW
                               according to IFLAG value specifcied (see below).
                               returns: <O> if successful and <X> if unsuccessful (e.g. out of memory)

  <Z ID>:                      deletes definition of output ID
                               returns: <O> if successful and <X> if unsuccessful (e.g. ID does not exist)

  <Z>:                         lists all defined output pins
                               returns: <Y ID PIN IFLAG STATE> for each defined output pin or <X> if no output pins defined

where

  ID: the numeric ID (0-32767) of the output
  PIN: the arduino pin number to use for the output
  STATE: the state of the output (0=INACTIVE / 1=ACTIVE)
  IFLAG: defines the operational behavior of the output based on bits 0, 1, and 2 as follows:

          IFLAG, bit 0:   0 = forward operation (ACTIVE=HIGH / INACTIVE=LOW)
                          1 = inverted operation (ACTIVE=LOW / INACTIVE=HIGH)

          IFLAG, bit 1:   0 = state of pin restored on power-up to either ACTIVE or INACTIVE depending
                              on state before power-down; state of pin set to INACTIVE when first created
                          1 = state of pin set on power-up, or when first created, to either ACTIVE of INACTIVE
                              depending on IFLAG, bit 2

          IFLAG, bit 2:   0 = state of pin set to INACTIVE uponm power-up or when first created
                          1 = state of pin set to ACTIVE uponm power-up or when first created

Once all outputs have been properly defined, use the <E> command to store their definitions to EEPROM.
If you later make edits/additions/deletions to the output definitions, you must invoke the <E> command if you want those
new definitions updated in the EEPROM.  You can also clear everything stored in the EEPROM by invoking the <e> command.

To change the state of outputs that have been defined use:

  <Z ID STATE>:                sets output ID to either ACTIVE or INACTIVE state
                               returns: <Y ID STATE>, or <X> if turnout ID does not exist

where

  ID: the numeric ID (0-32767) of the turnout to control
  STATE: the state of the output (0=INACTIVE / 1=ACTIVE)

When controlled as such, the Arduino updates and stores the direction of each output in EEPROM so
that it is retained even without power.  A list of the current states of each output in the form <Y ID STATE> is generated
by this sketch whenever the <s> status command is invoked.  This provides an efficient way of initializing
the state of any outputs being monitored or controlled by a separate interface or GUI program.

**********************************************************************/
