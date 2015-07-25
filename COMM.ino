/**************************************************************************/
/*************************      VCO CONTROL      **************************/
/** Program to control the input of the VCO                              **/
/** Circuit to be done                                                   **/
/**                                                                      **/
/**     ARDUINO                                                          **/
/**   ANALOG PIN -------- RESISTOR 330OHM ---------------- VCO INPUT     **/
/**                                            |                         **/
/**                                            |                         **/
/**                                            |                         **/
/**                                        CAPACITOR                     **/
/**                                          10 uF                       **/
/**                                            |                         **/
/**                                            |                         **/
/**                                           GND                        **/
/**                                                                      **/
/**************************************************************************/
/**************************************************************************/



/*****************************/
/********** DEFINES **********/
/*****************************/
#define VCO_ANALOG_OUTPUT_447MHz 194;    /* Analog output constant to obtain 447 MHz on VCO output */
#define VCO_ANALOG_OUTPUT_445MHz 182;    /* Analog output constant to obtain 445 MHz on VCO output */
#define VCO_ANALOG_OUTPUT_443MHz 170;    /* Analog output constant to obtain 443 MHz on VCO output */
#define VCO_ANALOG_PIN  5                /* Analog output pin to VCO input. Preferrably */
#define VCO_SIGNALPERIOD_MS 3000         /* Analog output signal change period */
#define VCO_OUPTUT_VALUE_SHIFT  2        /* Value to add to the analog output in each period */



int VCO_current_Analog_Output = VCO_ANALOG_OUTPUT_445MHz;          /* Current analog output on VCO pin */
int VCO_max_Analog_Output = VCO_ANALOG_OUTPUT_447MHz;              /* Boundaries of the VCO input */
int VCO_min_Analog_Output = VCO_ANALOG_OUTPUT_443MHz;

unsigned long VCO_time = 0;                                        /* Time control variables */
unsigned long VCO_lastTime = 0;

void setup() {}

/*
 * AddS [VCO_OUPTUT_VALUE_SHIFT] to the VCO input each [VCO_SIGNALPERIOD_MS] milliseconds. 
 * The VCO output frequency varies continuously within 443 MHz and 447 MHz. 
 * Change the "#define" variables to obtain other frequencies.
 * 
 * VCO parameters:
 * * Kv = 0.12 V/MHz = 6.12 int units/MHz
 */ 
void loop() {
  
    
    VCO_time = millis();                                                /* Get current time */
    
    if( VCO_time - VCO_lastTime > VCO_SIGNALPERIOD_MS ){                /* Check whether we have to change the analog output value */
    
            if( VCO_current_Analog_Output >= VCO_max_Analog_Output ){   /* Check if the output is at maximum */
                VCO_current_Analog_Output = VCO_min_Analog_Output;      /* Restore the output to the VCO minimum input */
                
            } else {   
                VCO_current_Analog_Output += VCO_OUPTUT_VALUE_SHIFT;    /* Otherwise, keep adding */
            }
            
        VCO_lastTime = VCO_time;                                        /* Refresh time variables */
        analogWrite(VCO_ANALOG_PIN,VCO_current_Analog_Output);          /* Refresh the analog output */   
    }
}
