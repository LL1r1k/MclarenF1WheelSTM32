#ifndef __FONTS_H
#define __FONTS_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef struct {
	uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
	uint8_t  width, height;    // Bitmap dimensions in pixels
	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor pos to UL corner
 } GFXglyph;

typedef struct {
  const uint8_t *table;
  GFXglyph *glyph;
  uint8_t   first, last; // ASCII extents
  uint8_t   yAdvance;    // Newline distance (y axis)
  
} GFXfont;

extern const GFXfont FreeSans24pt7b;
extern const GFXfont FreeSans18pt7b;
extern const GFXfont FreeSans12pt7b;
extern const GFXfont FreeSans9pt7b;
extern const GFXfont MokiLean18pt7b;

#ifdef __cplusplus
}
#endif
  
#endif /* __FONTS_H */
