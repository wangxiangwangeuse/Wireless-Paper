#include "picture.h"
#include "e_ink_display.h"
uint16_t einksize = EINK;

#if einksize == 0
  #include "DEPG0150BxS810FxX_BW.h"
  DEPG0150BxS810FxX_BW epdbw(1, 2, 3, 2, 4); // reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
#elif einksize == 1
  #include "DEPG0213Bx800FxX_BW.h"
  DEPG0213Bx800FxX_BW epdbw(1, 2, 3, 4, 5); // reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
#elif einksize == 2
  #include "DEPG0290BxS800FxX_BW.h"
  DEPG0290BxS800FxX_BW epdbw(6, 4, 5, 3, 2); // reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
#elif einksize == 3
  #include "DEPG0154BxS800FxX_BW.h"
  DEPG0154BxS800FxX_BW epdbw(1, 2, 4, 2, 3); // reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
#endif

unsigned char img[1024];
Paint pt(img, 0, 0);

unsigned long time_start_ms;
unsigned long time_now_s;
#define COLORED     0
#define UNCOLORED   1


void setup() {

  Serial.begin(115200);
  epdbw.EPD_Init(); //Electronic paper initialization
  epdbw.EPD_ALL_image(gImage_154image_bw);	//Refresh the picture in full screen
  delay(1000);
  epdbw.Clear();

  pt.SetWidth(200);
  pt.SetHeight(24);

  Serial.println("e-Paper Paint");
  pt.Clear(COLORED);
  pt.DrawStringAt(30, 4, "E-ink - 1.54!", &Font16, UNCOLORED);
  epdbw.SetFrameMemory(pt.GetImage(), 0, 10, pt.GetWidth(), pt.GetHeight());
  delay(100);

  pt.Clear(UNCOLORED);
  pt.DrawStringAt(30, 4, "e-Paper Demo", &Font16, COLORED);
  epdbw.SetFrameMemory(pt.GetImage(), 0, 30, pt.GetWidth(), pt.GetHeight());
  delay(100);

  pt.SetWidth(64);
  pt.SetHeight(64);

  pt.Clear(UNCOLORED);
  pt.DrawRectangle(0, 0, 40, 50, COLORED);
  pt.DrawLine(0, 0, 40, 50, COLORED);
  pt.DrawLine(40, 0, 0, 50, COLORED);
  epdbw.SetFrameMemory(pt.GetImage(), 16, 60, pt.GetWidth(), pt.GetHeight());
  delay(100);

  pt.Clear(UNCOLORED);
  pt.DrawCircle(32, 32, 30, COLORED);
  epdbw.SetFrameMemory(pt.GetImage(), 120, 60, pt.GetWidth(), pt.GetHeight());

  pt.Clear(UNCOLORED);
  pt.DrawFilledRectangle(0, 0, 40, 50, COLORED);
  epdbw.SetFrameMemory(pt.GetImage(), 16, 130, pt.GetWidth(), pt.GetHeight());
  delay(100);

  pt.Clear(UNCOLORED);
  pt.DrawFilledCircle(32, 32, 30, COLORED);
  epdbw.SetFrameMemory(pt.GetImage(), 120, 130, pt.GetWidth(), pt.GetHeight());
  epdbw.HalLcd_Partial_Update();
  delay(2000);

  epdbw.EPD_Init(); //Electronic paper initialization
  epdbw.EPD_ALL_image(gImage_154image_bw);	//Refresh the picture in full screen
  epdbw.Clear();
  epdbw.DisplayPartBaseImage(gImage_154image_partial_bw_2);
  delay(1000);
  epdbw.HalLcd_Partial();

  Serial.println("e-Paper print number");
  pt.SetWidth(50);
  pt.SetHeight(60);
  pt.Clear(UNCOLORED);
  pt.SetRotate(ROTATE_270);

  char i = 0;
  char str[10][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (i = 0; i < 10; i++) {
    pt.Clear(UNCOLORED);
    pt.DrawStringAt(10, 10, str[i], &Font24, COLORED);
    epdbw.SetFrameMemory(pt.GetImage(), 80, 70, pt.GetWidth(), pt.GetHeight());
    epdbw.HalLcd_Partial_Update();
    delay(100);
  }

  // epdbw.EPD_Init(); //Electronic paper initialization
  // epdbw.EPD_ALL_image(gImage_154image_bw); //Refresh the picture in full screen
  // delay(1000);
  // epdbw.Clear();
  // epdbw.EPD_WhiteScreen_Black();
  // delay(1000);
  // epdbw.EPD_WhiteScreen_White();
  // epdbw.EPD_DeepSleep();  //Enter deep sleep
}
void loop() {

}