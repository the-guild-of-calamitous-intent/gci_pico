////////////////////////////////////////////////
//  The MIT License (MIT)
//  Copyright (c) 2023 Kevin Walchko
//  see LICENSE for full details
////////////////////////////////////////////////
#pragma once
// #include <math.h>

#if defined __cplusplus
extern "C" {
#endif

#ifndef M_PI
// #define M_PI 3.1415927f
constexpr float M_PI = 3.1415927f;
#endif

// Angular
constexpr float rad2deg = 180.0f / 3.1415927f;
constexpr float deg2rad = 3.1415927f / 180.0f;
// rads/sec -> rpm, 60s/min*rev/(2*pi) -> 30/pi
constexpr float rps2rpm = 30.0f / 3.1415927f;
constexpr float rpm2rps = 3.1415927f / 30.0f; // rpm -> rads/sec

// Magnetism
constexpr float gauss2tesla = 1e-5f;
constexpr float tesla2gauss = 1e5f;

// Standard Air Parameters
// https://en.wikipedia.org/wiki/Standard_sea_level
constexpr float AIR_PRESSURE_PA   = 101325.01576f; // Pa
constexpr float AIR_DENSITY       = 1.225f;        // kg/m^3
constexpr float AIR_TEMPERATURE_K = 288.15f;       // K

// Pressure
constexpr float pa2atm = 9.86923e-6f;
constexpr float atm2pa = 101325.0f;

// Temperature
inline float f2c(float f) { return 0.5555556f * (f - 32.0f); }
inline float c2f(float c) { return 1.8f * c + 32.0f; }
inline float c2k(float c) { return c + 273.15f; }
inline float k2c(float k) { return k - 273.15f; }

// Distance
constexpr float m2mi  = 0.000621371f; // meters to miles
constexpr float mi2m  = 1609.34f;     // miles to meters
constexpr float km2mi = 0.621371f;
constexpr float mi2km = 1.60934f;
constexpr float ft2m  = 0.3048f; // feet to meters

#if defined __cplusplus
}
#endif