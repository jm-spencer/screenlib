#include "display/lvgl.h"


/***********************************************************************************
 * synchronizer_nbp.ttf 7 px Font in U+0030 (0) .. U+0039 (9)  range with 1 bpp
 * Sparse font with only these characters: 0123456789
 *
 * font by total FontGeek DTF, Ltd. - https://www.fontspace.com/total-fontgeek-dtf-ltd/synchronizer-nbp
 * converted by the lvgl font converter - https://littlevgl.com/ttf-font-to-c-array
 * all credit to them
***********************************************************************************/

/*Store the image of the letters (glyph)*/
static const uint8_t smallFont_glyph_bitmap[] =
{
  /*Unicode: U+0030 (0) , Width: 5 */
  0x00,  //.....
  0x70,  //.%%%.
  0x98,  //%..%%
  0xa8,  //%.%.%
  0xc8,  //%%..%
  0x88,  //%...%
  0x70,  //.%%%.


  /*Unicode: U+0031 (1) , Width: 2 */
  0x00,  //..
  0x40,  //.%
  0xc0,  //%%
  0x40,  //.%
  0x40,  //.%
  0x40,  //.%
  0x40,  //.%


  /*Unicode: U+0032 (2) , Width: 5 */
  0x00,  //.....
  0x70,  //.%%%.
  0x88,  //%...%
  0x30,  //..%%.
  0x40,  //.%...
  0x80,  //%....
  0xf8,  //%%%%%


  /*Unicode: U+0033 (3) , Width: 5 */
  0x00,  //.....
  0x70,  //.%%%.
  0x88,  //%...%
  0x30,  //..%%.
  0x08,  //....%
  0x88,  //%...%
  0x70,  //.%%%.


  /*Unicode: U+0034 (4) , Width: 5 */
  0x00,  //.....
  0x10,  //...%.
  0x30,  //..%%.
  0x50,  //.%.%.
  0xf8,  //%%%%%
  0x10,  //...%.
  0x10,  //...%.


  /*Unicode: U+0035 (5) , Width: 5 */
  0x00,  //.....
  0xf8,  //%%%%%
  0x80,  //%....
  0xf0,  //%%%%.
  0x08,  //....%
  0x08,  //....%
  0xf0,  //%%%%.


  /*Unicode: U+0036 (6) , Width: 5 */
  0x00,  //.....
  0x70,  //.%%%.
  0x80,  //%....
  0xf0,  //%%%%.
  0x88,  //%...%
  0x88,  //%...%
  0x70,  //.%%%.


  /*Unicode: U+0037 (7) , Width: 5 */
  0x00,  //.....
  0xf8,  //%%%%%
  0x08,  //....%
  0x10,  //...%.
  0x20,  //..%..
  0x20,  //..%..
  0x20,  //..%..


  /*Unicode: U+0038 (8) , Width: 5 */
  0x00,  //.....
  0x70,  //.%%%.
  0x88,  //%...%
  0x70,  //.%%%.
  0x88,  //%...%
  0x88,  //%...%
  0x70,  //.%%%.


  /*Unicode: U+0039 (9) , Width: 5 */
  0x00,  //.....
  0x70,  //.%%%.
  0x88,  //%...%
  0x88,  //%...%
  0x78,  //.%%%%
  0x08,  //....%
  0x70,  //.%%%.


};


/*Store the glyph descriptions*/
static const lv_font_glyph_dsc_t smallFont_glyph_dsc[] =
{
  {.w_px = 5,	.glyph_index = 0},	/*Unicode: U+0030 (0)*/
  {.w_px = 2,	.glyph_index = 7},	/*Unicode: U+0031 (1)*/
  {.w_px = 5,	.glyph_index = 14},	/*Unicode: U+0032 (2)*/
  {.w_px = 5,	.glyph_index = 21},	/*Unicode: U+0033 (3)*/
  {.w_px = 5,	.glyph_index = 28},	/*Unicode: U+0034 (4)*/
  {.w_px = 5,	.glyph_index = 35},	/*Unicode: U+0035 (5)*/
  {.w_px = 5,	.glyph_index = 42},	/*Unicode: U+0036 (6)*/
  {.w_px = 5,	.glyph_index = 49},	/*Unicode: U+0037 (7)*/
  {.w_px = 5,	.glyph_index = 56},	/*Unicode: U+0038 (8)*/
  {.w_px = 5,	.glyph_index = 63},	/*Unicode: U+0039 (9)*/
};

/*List of unicode characters*/
static const uint32_t smallFont_unicode_list[] = {
  48,	/*Unicode: U+0030 (0)*/
  49,	/*Unicode: U+0031 (1)*/
  50,	/*Unicode: U+0032 (2)*/
  51,	/*Unicode: U+0033 (3)*/
  52,	/*Unicode: U+0034 (4)*/
  53,	/*Unicode: U+0035 (5)*/
  54,	/*Unicode: U+0036 (6)*/
  55,	/*Unicode: U+0037 (7)*/
  56,	/*Unicode: U+0038 (8)*/
  57,	/*Unicode: U+0039 (9)*/
  0,    /*End indicator*/
};

lv_font_t smallFont =
{
    .unicode_first = 48,	/*First Unicode letter in this font*/
    .unicode_last = 57,	/*Last Unicode letter in this font*/
    .h_px = 7,				/*Font height in pixels*/
    .glyph_bitmap = smallFont_glyph_bitmap,	/*Bitmap of glyphs*/
    .glyph_dsc = smallFont_glyph_dsc,		/*Description of glyphs*/
    .unicode_list = smallFont_unicode_list,	/*List of unicode characters*/
    .get_bitmap = lv_font_get_bitmap_sparse,	/*Function pointer to get glyph's bitmap*/
    .get_width = lv_font_get_width_sparse,	/*Function pointer to get glyph's width*/
    .bpp = 1,				/*Bit per pixel*/
    .next_page = NULL,		/*Pointer to a font extension*/
};
