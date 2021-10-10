//********************************************************************
// File EbDawson.h                                     Dawson Integral
//********************************************************************
#ifndef _EbDawson_h_
#define _EbDawson_h_
// Brought to you by courtesy of Extra Byte, www.ebyte.it
// For details, see www.dx.doi.org/10.3247/SL4Soft12.001
// Version 1.0 (2012)

typedef long double REAL;

//********************************************************************
// McCabe's continued fraction algorithm
//********************************************************************
// For details, see www.dx.doi.org/10.3247/SL4Soft12.001

REAL DawsonByMcCabeCF(REAL x);   // Slow, but precise to 17 dec.digits

//********************************************************************
// Stan Sykora's rational function approximations
//********************************************************************
// The approximations were optimized for best RELATIVE error
// The numeric postfix denotes the approximation order

double Dawson1(double x);       // max rel.error 45616 ppm
double Dawson2(double x);       // max rel.error  5185 ppm
double Dawson3(double x);       // max rel.error   693 ppm
double Dawson4(double x);       // max rel.error    90 ppm
double Dawson5(double x);       // max rel.error    10 ppm

//********************************************************************
#endif

