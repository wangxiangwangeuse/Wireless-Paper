#include "HT_LCMEN2R13EFC1.h"
#include "picture_part.h"

#define DRIVER_OUTPUT_CONTROL 0x01
#define BOOSTER_SOFT_START_CONTROL 0x0C
#define GATE_SCAN_START_POSITION 0x0F
#define DEEP_SLEEP_MODE 0x10
#define DATA_ENTRY_MODE_SETTING 0x11
#define SW_RESET 0x12
#define TEMPERATURE_SENSOR_CONTROL 0x1A
#define MASTER_ACTIVATION 0x20
#define DISPLAY_UPDATE_CONTROL_1 0x21
#define DISPLAY_UPDATE_CONTROL_2 0x22
#define WRITE_RAM 0x24
#define WRITE_VCOM_REGISTER 0x2C
#define WRITE_LUT_REGISTER 0x32
#define SET_DUMMY_LINE_PERIOD 0x3A
#define SET_GATE_TIME 0x3B
#define BORDER_WAVEFORM_CONTROL 0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION 0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION 0x45
#define SET_RAM_X_ADDRESS_COUNTER 0x4E
#define SET_RAM_Y_ADDRESS_COUNTER 0x4F
#define TERMINATE_FRAME_READ_WRITE 0xFF
#define PIC_BLACK 252
#define PIC_WHITE 255
#define PIC_A 1
#define PIC_B 2
#define PIC_HLINE 3
#define PIC_VLINE 4
#define PIC_C 5
#define PIC_D 6
#define PIC_E 7
#define PIC_R 8

#define PIC_1 9
#define PIC_2 10
#define PIC_3 11
#define PIC_4 12
#define PIC_5 13
#define PIC_0 14
#define PIC_6 15
/************************************** init ************************************************/
void HT_LCMEN2R13EFC1::EPD_Init(void)
{
    /* this calls the peripheral hardware interface, see epdif */
#if defined(ESP32)
    SPI.begin(this->clk_pin, MISO, 2, this->cs_pin);

#elif defined(ESP8266)
    SPI.pins(this->clk_pin, MISO, MOSI, this->cs_pin);
    SPI.begin();
#endif
    if (IfInit() != 0)
    {
        Serial.print("e-Paper init failed");
        return;
    }
    Reset();
    WaitUntilIdle();
    SendCommand(0x12); // soft reset
    WaitUntilIdle();
    SendCommand(0x4D);
    SendData(0x55);

    SendCommand(0xA9);
    SendData(0x25);

    SendCommand(0xF3);
    SendData(0x0A);
    Serial.println("e-Paper init OK!");
}

/****************************** All screen update *******************************************/
void HT_LCMEN2R13EFC1::EPD_ALL_image(const unsigned char *datas)
{
    unsigned int i;

    // SendCommand(0x4E);
    // SendData(0x00);

    // SendCommand(0x4F);
    // SendData(0xf9);
    // SendData(0x00);
    // WaitUntilIdle();
    // EPD_Update();

    SendCommand(0x13); // write RAM for black(0)/white (1)

    for (int i = 0; i < ALLSCREEN_GRAGHBYTES; i++)
    {
        SendData(pgm_read_byte(&datas[i]));
    }

  EPD_Update();
}

/********************************* update ***************************************************/
void HT_LCMEN2R13EFC1::EPD_Update(void)
{
     SendCommand(0x04); // Power ON
    WaitUntilIdle();
    delay(10);

    SendCommand(0x12); // Display Refresh
    delay(10);
    WaitUntilIdle();

    SendCommand(0x02); // Power OFF
    WaitUntilIdle();
    delay(20);
}

/********************************** deep sleep **********************************************/
void HT_LCMEN2R13EFC1::EPD_DeepSleep(void)
{
    SendCommand(0x07); // enter deep sleep
    SendData(0xa5);
    DelayMs(100);
}

/********************************* Display All Black ****************************************/
void HT_LCMEN2R13EFC1::EPD_WhiteScreen_Black(void)
{
    EPD_Load_Data(0x00);
}

/********************************* Display All White ****************************************/
void HT_LCMEN2R13EFC1::EPD_WhiteScreen_White(void)
{
    EPD_Load_Data(0xff);
}

/********************************** Load Data ***********************************************/
void HT_LCMEN2R13EFC1::EPD_Load_Data(unsigned char data)
{
    unsigned int i, k;
    SendCommand(0x4E);
    SendData(0x00);

    SendCommand(0x4F);
    SendData(0xf9);
    SendData(0x00);

    WaitUntilIdle();
    SendCommand(0x13); // write RAM for black(0)/white (1)

    for (k = 0; k < 250; k++)
    {
        for (i = 0; i < 16; i++)
        {
            SendData(data);
        }
    }
    EPD_Update();
}
// 写波形数据表

void HT_LCMEN2R13EFC1::WRITE_LUT_RED()
{
    unsigned int count;

    WaitUntilIdle();
    SendCommand(0x20);
    for (count = 0; count < 42; count++)
    {
        SendData(LUT_VCOM[count]);
    }

    WaitUntilIdle();
    SendCommand(0x21); // 白
    for (count = 0; count < 42; count++)
    {
        SendData(LUT_WW[count]);
    }

    WaitUntilIdle();
    SendCommand(0x22); // 白
    for (count = 0; count < 42; count++)
    {
        SendData(LUT_BW[count]);
    }

    WaitUntilIdle();
    SendCommand(0x23); // 黑
    for (count = 0; count < 42; count++)
    {
        SendData(LUT_WB[count]);
    }

    SendCommand(0x24); // 黑
    for (count = 0; count < 42; count++)
    {
        SendData(LUT_BB[count]);
    }
}

///////////////////////////Part update//////////////////////////////////////////////
void HT_LCMEN2R13EFC1::EPD_Dis_Part_init(const unsigned char *data)
{

    unsigned int row, col;
    unsigned int pcnt;

    SendCommand(0x91); // DTM1 Write
    WaitUntilIdle();

    SendCommand(0x09);
    WaitUntilIdle();

    SendData(0x00);
    SendData(0x7F);

    SendData(0x00);
    SendData(0xF9);

    SendData(0x01);

    SendCommand(0x10); // DTM1 Write
    WaitUntilIdle();
    pcnt = 0;
    for (col = 0; col < 4000; col++)
    {
        SendData(data[pcnt]);

        pcnt++;
    }

    SendCommand(0x13); // DTM1 Write
    WaitUntilIdle();

    for (col = 0; col < 4000; col++)
    {

        SendData(data[pcnt]);

        pcnt++;
    }

    SendCommand(0x92); // DTM1 Write

    // 	SendCommand(0x44);       // set RAM x address start/end, in page 35
    // 	SendData(x_start);    		// RAM x address start
    // 	SendData(x_end);    			// RAM x address end
    // 	SendCommand(0x45);       // set RAM y address start/end, in page 35
    // 	SendData(y_start2);    	// RAM y address start
    // 	SendData(y_start1);   	 	// RAM y address start
    // 	SendData(y_end2);    		// RAM y address end
    // 	SendData(y_end1);    		// RAM y address end

    // 	SendCommand(0x4E);   // set RAM x address count to 0;
    // 	SendData(x_start);
    // 	SendCommand(0x4F);   // set RAM y address count to 0X127;
    // 	SendData(y_start2);
    // 	SendData(y_start1);

    //   if(color_mode==MONO)
    //     SendCommand(0x24);   //write RAM for black(0)/white (1)

    //   if(color_mode==RED)
    //     SendCommand(0x26);   //write RAM for black(0)/white (1)

    // 	for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
    //    {
    //      SendData(* datas);
    // 			datas++;
    //    }

    // EPD_Update();
}

void HT_LCMEN2R13EFC1::dis_img_Partial_Refresh(const unsigned char *data)
{
    unsigned int row, col;
    unsigned int pcnt;
    unsigned char Byte1, Byte2, Byte3;

    //    SendCommand(0x00); //PSR
    //   SendData(0xF7);//黑白
    //   SendData(0x48);//

    SendCommand(0x91); // partial in
    WaitUntilIdle();
    SendCommand(0x00);
    WaitUntilIdle();

    SendData(0x40);
    SendData(0x5F); // V End 32

    SendData(0x91); //
    SendData(0xA1); // H End 48/8=6
    SendData(0x01);

    //    SendCommand(0x10);	// DTM1 Write
    //    WaitUntilIdle();
    //    pcnt = 0;
    //    for(col=0; col<24; col++)
    //    {
    //        for(row=0; row<4; row++)
    //        {
    //            switch (num)
    //            {
    //              case PIC_0:
    //         //     SendData(~gImage_0_BW[pcnt]);
    //              //    SendData(0x00);
    //                break;
    //                case PIC_1:
    //              SendData(gImage_1_BW[pcnt]);
    //
    //                break;
    //
    //                case PIC_2:
    //                SendData(gImage_2_BW[pcnt]);
    //                break;
    //
    //                case PIC_3:
    //                SendData(gImage_3_BW[pcnt]);
    //                break;
    //
    //                case PIC_4:
    //                SendData(gImage_4_BW[pcnt]);
    //                break;
    //
    //                case PIC_5:
    //                SendData(gImage_5_BW[pcnt]);
    //                break;
    //                case PIC_6:
    //           //     SendData(~gImage_6_BW[pcnt]);
    //                break;
    //                default:
    //                break;
    //
    //            }
    //
    //            pcnt++;
    //        }
    //    }

    SendCommand(0x13); // DTM1 Write
    WaitUntilIdle();
    pcnt = 0;
    for (col = 0; col < 96; col++)
    {

        SendData(data[pcnt]);
        pcnt++;
    }

    SendCommand(0x92); // partial out
    WaitUntilIdle();

    WRITE_LUT_RED(); // O波形
    WaitUntilIdle();

    SendCommand(0x04); // Power ON
    WaitUntilIdle();
    delay(10);

    SendCommand(0x12); // Display Refresh
    delay(10);
    WaitUntilIdle();

    SendCommand(0x02); // Power OFF
    WaitUntilIdle();
    delay(20);
}
/* HT_LCMEN2R13EFC1 END */

/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 */
void HT_LCMEN2R13EFC1::SetFrameMemory(
    const unsigned char *image_buffer,
    int x,
    int y,
    int image_width,
    int image_height)
{
    int x_end;
    int y_end;

    if (
        image_buffer == NULL ||
        x < 0 || image_width < 0 ||
        y < 0 || image_height < 0)
    {
        return;
    }
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= EPD_WIDTH_213)
    {
        x_end = EPD_WIDTH_213 - 1;
    }
    else
    {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= EPD_HEIGHT_213)
    {
        y_end = EPD_HEIGHT_213 - 1;
    }
    else
    {
        y_end = y + image_height - 1;
    }
    SetMemoryArea(x, y, x_end, y_end);
    SetMemoryPointer(x, y);
    SendCommand(WRITE_RAM);
    /* send the image data */
    for (int j = 0; j < y_end - y + 1; j++)
    {
        for (int i = 0; i < (x_end - x + 1) / 8; i++)
        {
            SendData(image_buffer[i + j * (image_width / 8)]);
        }
    }
}

/**
 *  @brief: clear the frame memory with the specified color.
 *          this won't update the display.
 */
void HT_LCMEN2R13EFC1::ClearFrameMemory(unsigned char color)
{

    SendCommand(0x10);
    /* send the color data */
    for (int i = 0; i < EPD_WIDTH_213 / 8 * EPD_HEIGHT_213; i++)
    {
        SendData(color);
    }
}
/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will
 *          set the other memory area.
 */
void HT_LCMEN2R13EFC1::HalLcd_Partial_Update(void)
{
    SendCommand(DISPLAY_UPDATE_CONTROL_2);

    SendData(0xc4);

    SendCommand(MASTER_ACTIVATION);
    SendCommand(TERMINATE_FRAME_READ_WRITE);

    WaitUntilIdle();
}

/**
 *  @brief: private function to specify the memory area for data R/W
 */

void HT_LCMEN2R13EFC1::SetMemoryArea(int x_start, int y_start, int x_end, int y_end)
{
    SendCommand(0x11); // data entry mode
    SendData(0x03);
    SendCommand(0x44);
    // SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x_start >> 3) & 0xFF);
    SendData((x_end >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
    SendData(y_start & 0xFF);
    SendData((y_start >> 8) & 0xFF);
    SendData(y_end & 0xFF);
    SendData((y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void HT_LCMEN2R13EFC1::SetMemoryPointer(int x, int y)
{
    SendCommand(SET_RAM_X_ADDRESS_COUNTER);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
    SendData(y & 0xFF);
    SendData((y >> 8) & 0xFF);
}

void HT_LCMEN2R13EFC1::Clear(void)
{
    int w, h;
    w = (EPD_WIDTH_213 % 8 == 0) ? (EPD_WIDTH_213 / 8) : (EPD_WIDTH_213 / 8 + 1);
    h = EPD_HEIGHT_213;

    SendCommand(0x13);
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            SendData(0xff);
        }
    }
    SendCommand(0x04); // Power ON
    WaitUntilIdle();
    delay(10);

    SendCommand(0x12); // Display Refresh
    delay(10);
    WaitUntilIdle();

    SendCommand(0x02); // Power OFF
    WaitUntilIdle();
    delay(20);
    // EPD_Update();
}
//////////////////////////////////////////////////////////////////////////////////////
