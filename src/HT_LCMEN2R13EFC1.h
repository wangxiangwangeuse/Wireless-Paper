#ifndef __HT_LCMEN2R13EFC1_H__
#define __HT_LCMEN2R13EFC1_H__
#include "EpdBase.h"

//250*122///////////////////////////////////////

#define USE_213part_BW

#define ALLSCREEN_GRAGHBYTES	4000

/* Display resolution */
#define EPD_WIDTH_213       122
#define EPD_HEIGHT_213      250   



const unsigned char LUT_VCOM[]={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x14, 0x00, 0x01, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
 const unsigned char LUT_WW[] ={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x94, 0x00, 0x01, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const unsigned char LUT_BW[] ={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x94, 0x00, 0x01, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const unsigned char LUT_WB[] ={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x54, 0x00, 0x01, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
}; // 0.4
const unsigned char LUT_BB[] ={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x00, 0x00, 0x54, 0x00, 0x01, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const unsigned char CMD_USER[]={ 
0x00, 0x3F, 0x3F, 0x10, 0X09, 0x13,
};

class HT_LCMEN2R13EFC1:public EpdBase {
    public:
        HT_LCMEN2R13EFC1(uint8_t _rst, uint8_t _dc, uint8_t _cs,  uint8_t _busy, int8_t _clk=-1, uint8_t _spi_num = 0 ,uint32_t _freq = 2000000): \
        EpdBase(_rst, _dc, _cs, _busy, _clk, _spi_num, _freq){}
        ~HT_LCMEN2R13EFC1(){}

    public:
        void EPD_Init(void); //Electronic paper initialization
        void EPD_Update(void);
        void EPD_WhiteScreen_Black(void);
        void EPD_WhiteScreen_White(void);
        void EPD_DeepSleep(void);
        //Display         
        void Clear(void);
        void EPD_ALL_image(const unsigned char *datas);
        void HalLcd_Partial_Update(void);
        void SetFrameMemory(const unsigned char* image_buffer,int x,int y,int image_width,int image_height);
        void ClearFrameMemory(unsigned char color);
        void  EPD_Dis_Part_init(const unsigned char* data);
        void dis_img_Partial_Refresh(const unsigned char* data);
        void  WRITE_LUT_RED();

    private:
        void EPD_Load_Data(unsigned char data);
        void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
        void SetMemoryPointer(int x, int y);
};

#endif