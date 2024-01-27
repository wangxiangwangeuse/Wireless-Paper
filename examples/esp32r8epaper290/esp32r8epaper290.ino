/*
DEPG0290BxS75AFxX_BW is a 2.9 inch black and white screen
Display Resolution 128(H)×296(V)
*/
#include "DEPG0290BxS800FxX_BW.h"
#include "picture.h"

#define UNDEFINED -1
#if defined( ESP32 )
    #define RST_PIN         16
    #define DC_PIN          22
    #define CS_PIN          18
    #define BUSY_PIN        23
    #define CLK_PIN         5

    DEPG0290BxS800FxX_BW epd290bw(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin

#endif

void setup() {
    Serial.begin(115200);
    epd290bw.EPD_Init(); //Electronic paper initialization
    epd290bw.EPD_ALL_image(gImage_290image_bw);	//Refresh the picture in full screen
    
}
void loop() {

}