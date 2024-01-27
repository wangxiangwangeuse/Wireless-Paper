#include <cstdint>
#include"Arduino.h"
#ifndef __HTDE01_H__
#define __HTDE01_H__
// enum eink_size_value{
// eink_150,
// eink_154,
// eink_213,
// eink_290,
// };


void ht_de01_begin(); 
void ht_de01_img(uint8_t* WiFi_Logo_bits);

#endif 
