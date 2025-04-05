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

#ifndef LV_ATTRIBUTE_IMG_SYSTEM
#define LV_ATTRIBUTE_IMG_SYSTEM
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SYSTEM uint8_t System_map[] = {
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xe0, 0x00, 
  0x00, 0x0f, 0xf0, 0x00, 
  0x00, 0x0f, 0xf0, 0x00, 
  0x00, 0x0f, 0xf0, 0x00, 
  0x03, 0x1f, 0xf8, 0xc0, 
  0x07, 0xff, 0xff, 0xe0, 
  0x0f, 0xff, 0xff, 0xf0, 
  0x0f, 0xff, 0xff, 0xf0, 
  0x1f, 0xfe, 0x7f, 0xf8, 
  0x1f, 0xf8, 0x1f, 0xf8, 
  0x07, 0xf0, 0x0f, 0xe0, 
  0x03, 0xf0, 0x0f, 0xc0, 
  0x03, 0xe0, 0x07, 0xc0, 
  0x03, 0xe0, 0x07, 0xc0, 
  0x03, 0xf0, 0x0f, 0xc0, 
  0x07, 0xf0, 0x0f, 0xe0, 
  0x1f, 0xf8, 0x1f, 0xf8, 
  0x1f, 0xfe, 0x7f, 0xf8, 
  0x0f, 0xff, 0xff, 0xf0, 
  0x0f, 0xff, 0xff, 0xf0, 
  0x07, 0xff, 0xff, 0xe0, 
  0x03, 0x1f, 0xf8, 0xc0, 
  0x00, 0x0f, 0xf0, 0x00, 
  0x00, 0x0f, 0xf0, 0x00, 
  0x00, 0x0f, 0xf0, 0x00, 
  0x00, 0x07, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t System = {
  .header = { 
    .cf = LV_IMG_CF_ALPHA_1BIT,
    .always_zero = 0,
    .reserved = 0,
    .w = 32,
    .h = 32
  },
  .data_size = 128,
  .data = System_map,
};
