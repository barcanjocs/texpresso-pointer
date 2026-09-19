/*
 * MIT License
 *
 * Copyright (c) 2023 Frédéric Bour <frederic.bour@lakaban.net>
 */

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SDL2/SDL.h>
#include <mupdf/fitz.h>
#include <stdbool.h>

typedef struct txp_renderer_s txp_renderer;

txp_renderer *txp_renderer_new(fz_context *ctx, SDL_Renderer *sdl);
void txp_renderer_free(fz_context *ctx, txp_renderer *r);

enum txp_fit_mode
{
  FIT_WIDTH,
  FIT_PAGE,
};

typedef struct
{
  float zoom;
  enum txp_fit_mode fit;
  fz_point pan;
  bool crop, themed_color, invert_color;
  uint32_t background_color, foreground_color;
} txp_renderer_config;

struct fullscreen_state
{
  txp_renderer_config windowed_backup;
  bool has_backup;
  bool prev_fs;
};

typedef struct
{
  fz_rect page_bounds;
  fz_point window_size;
  fz_point document_size;
  fz_point pan_interval;
} txp_renderer_bounds;

void txp_renderer_set_contents(fz_context *ctx,
                               txp_renderer *self,
                               fz_display_list *dl);

void txp_renderer_set_pages(fz_context *ctx,
                            txp_renderer *self,
                            fz_display_list **pages,
                            int page_count);
float txp_renderer_page_y(fz_context *ctx, txp_renderer *self, int page);
fz_display_list *txp_renderer_get_contents(fz_context *ctx, txp_renderer *self);

txp_renderer_config *txp_renderer_get_config(fz_context *ctx,
                                             txp_renderer *self);

bool txp_renderer_page_bounds(fz_context *ctx,
                              txp_renderer *self,
                              txp_renderer_bounds *result);

bool txp_renderer_page_position(fz_context *ctx,
                                txp_renderer *self,
                                SDL_FRect *rect,
                                fz_point *translate,
                                float *scale);
bool txp_renderer_is_two_column(fz_context *ctx, txp_renderer *self);
void txp_renderer_render(fz_context *ctx, txp_renderer *self);

void txp_renderer_set_scale_factor(fz_context *ctx,
                                   txp_renderer *self,
                                   fz_point scale);

bool txp_renderer_start_selection(fz_context *ctx,
                                  txp_renderer *self,
                                  fz_point pt);

bool txp_renderer_drag_selection(fz_context *ctx,
                                 txp_renderer *self,
                                 fz_point pt);

bool txp_renderer_select_word(fz_context *ctx, txp_renderer *self, fz_point pt);

bool txp_renderer_select_char(fz_context *ctx, txp_renderer *self, fz_point pt);

void txp_renderer_screen_size(fz_context *ctx,
                              txp_renderer *self,
                              int *w,
                              int *h);

fz_point txp_renderer_screen_to_document(fz_context *ctx,
                                         txp_renderer *self,
                                         fz_point pt);

fz_point txp_renderer_document_to_screen(fz_context *ctx,
                                         txp_renderer *self,
                                         fz_point pt);

#endif /* !_RENDERER_H_ */
