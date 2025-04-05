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

#ifndef LV_ATTRIBUTE_IMG_TYPE71
#define LV_ATTRIBUTE_IMG_TYPE71
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_TYPE71 uint8_t Type71_map[] = {
  0x00, 0x00, 0x20, 0x00, 
  0x00, 0x00, 0x78, 0x00, 
  0x00, 0x00, 0xf8, 0x00, 
  0x00, 0x00, 0x78, 0x00, 
  0x00, 0x00, 0x70, 0x00, 
  0x00, 0x01, 0x00, 0x00, 
  0x00, 0x0f, 0xc0, 0x00, 
  0x00, 0x7f, 0xc0, 0x00, 
  0x00, 0xff, 0xe0, 0x00, 
  0x00, 0xe7, 0xf0, 0x00, 
  0x00, 0xc7, 0xf0, 0x00, 
  0x00, 0xc7, 0xbf, 0x80, 
  0x00, 0xcf, 0xbf, 0x80, 
  0x00, 0xcf, 0x80, 0x00, 
  0x00, 0xcf, 0x00, 0x00, 
  0x00, 0x0f, 0x80, 0x00, 
  0x00, 0x1f, 0x80, 0x00, 
  0x00, 0x1f, 0xc0, 0x00, 
  0x00, 0x1f, 0xc0, 0x00, 
  0x00, 0x1d, 0xe0, 0x00, 
  0x00, 0x3c, 0xf0, 0x00, 
  0x00, 0x38, 0xf0, 0x00, 
  0x00, 0x38, 0x70, 0x00, 
  0x00, 0x70, 0x70, 0x00, 
  0x00, 0x70, 0x70, 0x00, 
  0x00, 0x70, 0x70, 0x00, 
  0x00, 0x60, 0x70, 0x00, 
  0x00, 0xe0, 0x70, 0x00, 
  0x00, 0xe0, 0x70, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t Type71 = {
    .header = {
        .cf = LV_IMG_CF_ALPHA_1BIT,
        .always_zero = 0,
        .reserved = 0,
        .w = 32,
        .h = 32
    },
  .data_size = 128,
  .data = Type71_map,
};
