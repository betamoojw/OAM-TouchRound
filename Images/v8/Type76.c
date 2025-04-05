#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_TYPE76
#define LV_ATTRIBUTE_IMG_TYPE76
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_TYPE76 uint8_t Type76_map[] = {
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x3c, 0x3c, 0x00, 
  0x00, 0x7e, 0x7e, 0x00, 
  0x00, 0xfe, 0xff, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xe0, 0xe7, 0x00, 
  0x00, 0xfe, 0xff, 0x00, 
  0x00, 0x7e, 0x7e, 0x00, 
  0x00, 0x3c, 0x3c, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t Type76 = {
    .header = {
        .cf = LV_IMG_CF_ALPHA_1BIT,
        .always_zero = 0,
        .reserved = 0,
        .w = 32,
        .h = 32
    },
  .data_size = 128,
  .data = Type76_map,
};
