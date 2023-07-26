#pragma once

#include <stdbool.h>
#include <stdint.h>


bool load_png(const char *file_name, uint8_t **pixels, uint32_t *width, uint32_t *height, uint32_t *stride);
bool load_png_from_buffer(const uint8_t *buff, const int buff_size, uint8_t **pixels_p, uint32_t *width_p, uint32_t *height_p, uint32_t *stride_p);
