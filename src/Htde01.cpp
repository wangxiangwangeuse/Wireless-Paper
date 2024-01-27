#include"Htde01.h"


#if eink_size == 0

 #include "DEPG0150BxS810FxX_BW.h"
 #define RST_PIN         16
	#define DC_PIN          22
	#define CS_PIN          18
	#define BUSY_PIN        23
	#define CLK_PIN         5

	DEPG0150BxS810FxX_BW htde01(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
//  DEPG0150BxS810FxX_BW htde01(6, 5, 4, 7, 3, 2, -1, 6000000); //rst,dc,cs,busy,sck,mosi,miso,frequency

#elif eink_size == 1

#include "DEPG0150BxS810FxX_BW.h"
 #define RST_PIN         6
	#define DC_PIN          5
	#define CS_PIN          4
	#define BUSY_PIN        7
	#define CLK_PIN         3

	DEPG0154BxS800FxX_BW htde01(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
//  DEPG0150BxS810FxX_BW htde01(6, 5, 4, 7, 3, 2, -1, 6000000); //rst,dc,cs,busy,sck,mosi,miso,frequency
#elif eink_size == 2
#include "ht213.h"
 #define RST_PIN         6
	#define DC_PIN          5
	#define CS_PIN          4
	#define BUSY_PIN        7
	#define CLK_PIN         3

	ht213 htde01(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
// ht213   htde01(6, 5, 4, 7, 3, 2, -1, 6000000); //rst,dc,cs,busy,sck,mosi,miso,frequency
#else eink_size == 3
#include "DEPG0290BxS800FxX_BW.h"
   #define RST_PIN         6
	#define DC_PIN          5
	#define CS_PIN          4
	#define BUSY_PIN        7
	#define CLK_PIN         3

	ht213 htde01(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin

// DEPG0290BxS75AFxX_BW   htde01(6, 5, 4, 7, 3, 2, -1, 6000000); //rst,dc,cs,busy,sck,mosi,miso,frequency
#endif // eink_154


void ht_de01_begin(){
  htde01.EPD_Init();
}
void ht_de01_img(uint8_t* WiFi_Logo_bits){
  htde01.EPD_ALL_image(WiFi_Logo_bits);	//Refresh the picture in full screen
}
