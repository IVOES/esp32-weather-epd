/* Renderer declarations for esp32-weather-epd.
 * Copyright (C) 2022-2023  Luke Marzen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include <Arduino.h>
#include <time.h>
#include "api_response.h"
#include "config.h"

#define DISP_WIDTH  800
#define DISP_HEIGHT 480

#ifdef DISP_BW
#include <GxEPD2_BW.h>
extern GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display;
#endif
#ifdef DISP_3C
#include <GxEPD2_3C.h>
extern GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT / 2> display;
#endif

typedef enum alignment
{
  LEFT,
  RIGHT,
  CENTER
} alignment_t;

uint16_t getStringWidth(String text);
uint16_t getStringHeight(String text);
void drawString(int16_t x, int16_t y, String text, alignment_t alignment,
                uint16_t color=GxEPD_BLACK);
void drawMultiLnString(int16_t x, int16_t y, String text, alignment_t alignment,
                       uint16_t max_width, uint16_t max_lines,
                       int16_t line_spacing, uint16_t color=GxEPD_BLACK);
void initDisplay();
void drawCurrentConditions(const owm_current_t &current,
                           const owm_daily_t &today,
                           const owm_resp_air_pollution_t &owm_air_pollution,
                           float inTemp, float inHumidity);
void drawForecast(owm_daily_t *const daily, tm timeInfo);
void drawAlerts(std::vector<owm_alerts_t> &alerts,
                const String &city, const String &date);
void drawLocationDate(const String &city, const String &date);
void drawOutlookGraph(owm_hourly_t *const hourly, tm timeInfo);
void drawStatusBar(String statusStr, String refreshTimeStr, int rssi,
                   double batVoltage);
void drawError(const uint8_t *bitmap_196x196,
               const String &errMsgLn1, const String &errMsgLn2);

#endif
