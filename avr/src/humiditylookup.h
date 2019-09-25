#include <avr/pgmspace.h>

#include "types.h"

#ifndef _INCL_HUMIDITYLOOKUP
#define _INCL_HUMIDITYLOOKUP

#define HUMIDITY_LOOKUP_BUFFER_SIZE		700

/*
** Minimum sensor output corresponding to 0% RH is 800mv. The minimum
** ADC value at 800mv is 163", hence we subtract the offset defined here
** from the value before using as the index into the array below...
*/
#define ADC_HUMIDITY_OFFSET				    163

#define ADC_HUMIDITY_MIN					  0
#define ADC_HUMIDITY_MAX					699

/******************************************************************************
**
** From an ADC input linked to a Honeywell HIH-4000 humidity sensor
** with a range of 0 - 100% relative humidity.
**
** Define the relative humidity (RH) for ADC values between 163 - 804
** corresponding to sensor voltages of 800mV to 3.9V which are the lower and
** upper ranges from the sensor for 0% RH to 100% RH.
**
** Vo = Vs(0.0062 * RH + 0.16)
**
** RH = ((ADC / 1023) - 0.16) / 0.0062
**
** This is an expensive operation on a microcontroller", hence we calculate this
** upfront and store in flash ROM.
**
** This array of const values uses the PROGMEM modifier", a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array", code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/

const decimal24_t humidity0 PROGMEM = populate_decimal(0, 0);
const decimal24_t humidity1 PROGMEM = populate_decimal(0, 5);
const decimal24_t humidity2 PROGMEM = populate_decimal(0, 20);
const decimal24_t humidity3 PROGMEM = populate_decimal(0, 36);
const decimal24_t humidity4 PROGMEM = populate_decimal(0, 52);
const decimal24_t humidity5 PROGMEM = populate_decimal(0, 68);
const decimal24_t humidity6 PROGMEM = populate_decimal(0, 83);
const decimal24_t humidity7 PROGMEM = populate_decimal(0, 99);
const decimal24_t humidity8 PROGMEM = populate_decimal(1, 15);
const decimal24_t humidity9 PROGMEM = populate_decimal(1, 31);
const decimal24_t humidity10 PROGMEM = populate_decimal(1, 46);
const decimal24_t humidity11 PROGMEM = populate_decimal(1, 62);
const decimal24_t humidity12 PROGMEM = populate_decimal(1, 78);
const decimal24_t humidity13 PROGMEM = populate_decimal(1, 94);
const decimal24_t humidity14 PROGMEM = populate_decimal(2, 10);
const decimal24_t humidity15 PROGMEM = populate_decimal(2, 25);
const decimal24_t humidity16 PROGMEM = populate_decimal(2, 41);
const decimal24_t humidity17 PROGMEM = populate_decimal(2, 57);
const decimal24_t humidity18 PROGMEM = populate_decimal(2, 73);
const decimal24_t humidity19 PROGMEM = populate_decimal(2, 88);
const decimal24_t humidity20 PROGMEM = populate_decimal(3, 4);
const decimal24_t humidity21 PROGMEM = populate_decimal(3, 20);
const decimal24_t humidity22 PROGMEM = populate_decimal(3, 36);
const decimal24_t humidity23 PROGMEM = populate_decimal(3, 51);
const decimal24_t humidity24 PROGMEM = populate_decimal(3, 67);
const decimal24_t humidity25 PROGMEM = populate_decimal(3, 83);
const decimal24_t humidity26 PROGMEM = populate_decimal(3, 99);
const decimal24_t humidity27 PROGMEM = populate_decimal(4, 14);
const decimal24_t humidity28 PROGMEM = populate_decimal(4, 30);
const decimal24_t humidity29 PROGMEM = populate_decimal(4, 46);
const decimal24_t humidity30 PROGMEM = populate_decimal(4, 62);
const decimal24_t humidity31 PROGMEM = populate_decimal(4, 78);
const decimal24_t humidity32 PROGMEM = populate_decimal(4, 93);
const decimal24_t humidity33 PROGMEM = populate_decimal(5, 9);
const decimal24_t humidity34 PROGMEM = populate_decimal(5, 25);
const decimal24_t humidity35 PROGMEM = populate_decimal(5, 41);
const decimal24_t humidity36 PROGMEM = populate_decimal(5, 56);
const decimal24_t humidity37 PROGMEM = populate_decimal(5, 72);
const decimal24_t humidity38 PROGMEM = populate_decimal(5, 88);
const decimal24_t humidity39 PROGMEM = populate_decimal(6, 4);
const decimal24_t humidity40 PROGMEM = populate_decimal(6, 19);
const decimal24_t humidity41 PROGMEM = populate_decimal(6, 35);
const decimal24_t humidity42 PROGMEM = populate_decimal(6, 51);
const decimal24_t humidity43 PROGMEM = populate_decimal(6, 67);
const decimal24_t humidity44 PROGMEM = populate_decimal(6, 83);
const decimal24_t humidity45 PROGMEM = populate_decimal(6, 98);
const decimal24_t humidity46 PROGMEM = populate_decimal(7, 14);
const decimal24_t humidity47 PROGMEM = populate_decimal(7, 30);
const decimal24_t humidity48 PROGMEM = populate_decimal(7, 46);
const decimal24_t humidity49 PROGMEM = populate_decimal(7, 61);
const decimal24_t humidity50 PROGMEM = populate_decimal(7, 77);
const decimal24_t humidity51 PROGMEM = populate_decimal(7, 93);
const decimal24_t humidity52 PROGMEM = populate_decimal(8, 9);
const decimal24_t humidity53 PROGMEM = populate_decimal(8, 24);
const decimal24_t humidity54 PROGMEM = populate_decimal(8, 40);
const decimal24_t humidity55 PROGMEM = populate_decimal(8, 56);
const decimal24_t humidity56 PROGMEM = populate_decimal(8, 72);
const decimal24_t humidity57 PROGMEM = populate_decimal(8, 87);
const decimal24_t humidity58 PROGMEM = populate_decimal(9, 3);
const decimal24_t humidity59 PROGMEM = populate_decimal(9, 19);
const decimal24_t humidity60 PROGMEM = populate_decimal(9, 35);
const decimal24_t humidity61 PROGMEM = populate_decimal(9, 51);
const decimal24_t humidity62 PROGMEM = populate_decimal(9, 66);
const decimal24_t humidity63 PROGMEM = populate_decimal(9, 82);
const decimal24_t humidity64 PROGMEM = populate_decimal(9, 98);
const decimal24_t humidity65 PROGMEM = populate_decimal(10, 14);
const decimal24_t humidity66 PROGMEM = populate_decimal(10, 29);
const decimal24_t humidity67 PROGMEM = populate_decimal(10, 45);
const decimal24_t humidity68 PROGMEM = populate_decimal(10, 61);
const decimal24_t humidity69 PROGMEM = populate_decimal(10, 77);
const decimal24_t humidity70 PROGMEM = populate_decimal(10, 92);
const decimal24_t humidity71 PROGMEM = populate_decimal(11, 8);
const decimal24_t humidity72 PROGMEM = populate_decimal(11, 24);
const decimal24_t humidity73 PROGMEM = populate_decimal(11, 40);
const decimal24_t humidity74 PROGMEM = populate_decimal(11, 55);
const decimal24_t humidity75 PROGMEM = populate_decimal(11, 71);
const decimal24_t humidity76 PROGMEM = populate_decimal(11, 87);
const decimal24_t humidity77 PROGMEM = populate_decimal(12, 3);
const decimal24_t humidity78 PROGMEM = populate_decimal(12, 19);
const decimal24_t humidity79 PROGMEM = populate_decimal(12, 34);
const decimal24_t humidity80 PROGMEM = populate_decimal(12, 50);
const decimal24_t humidity81 PROGMEM = populate_decimal(12, 66);
const decimal24_t humidity82 PROGMEM = populate_decimal(12, 82);
const decimal24_t humidity83 PROGMEM = populate_decimal(12, 97);
const decimal24_t humidity84 PROGMEM = populate_decimal(13, 13);
const decimal24_t humidity85 PROGMEM = populate_decimal(13, 29);
const decimal24_t humidity86 PROGMEM = populate_decimal(13, 45);
const decimal24_t humidity87 PROGMEM = populate_decimal(13, 60);
const decimal24_t humidity88 PROGMEM = populate_decimal(13, 76);
const decimal24_t humidity89 PROGMEM = populate_decimal(13, 92);
const decimal24_t humidity90 PROGMEM = populate_decimal(14, 8);
const decimal24_t humidity91 PROGMEM = populate_decimal(14, 24);
const decimal24_t humidity92 PROGMEM = populate_decimal(14, 39);
const decimal24_t humidity93 PROGMEM = populate_decimal(14, 55);
const decimal24_t humidity94 PROGMEM = populate_decimal(14, 71);
const decimal24_t humidity95 PROGMEM = populate_decimal(14, 87);
const decimal24_t humidity96 PROGMEM = populate_decimal(15, 2);
const decimal24_t humidity97 PROGMEM = populate_decimal(15, 18);
const decimal24_t humidity98 PROGMEM = populate_decimal(15, 34);
const decimal24_t humidity99 PROGMEM = populate_decimal(15, 50);
const decimal24_t humidity100 PROGMEM = populate_decimal(15, 65);
const decimal24_t humidity101 PROGMEM = populate_decimal(15, 81);
const decimal24_t humidity102 PROGMEM = populate_decimal(15, 97);
const decimal24_t humidity103 PROGMEM = populate_decimal(16, 13);
const decimal24_t humidity104 PROGMEM = populate_decimal(16, 28);
const decimal24_t humidity105 PROGMEM = populate_decimal(16, 44);
const decimal24_t humidity106 PROGMEM = populate_decimal(16, 60);
const decimal24_t humidity107 PROGMEM = populate_decimal(16, 76);
const decimal24_t humidity108 PROGMEM = populate_decimal(16, 92);
const decimal24_t humidity109 PROGMEM = populate_decimal(17, 7);
const decimal24_t humidity110 PROGMEM = populate_decimal(17, 23);
const decimal24_t humidity111 PROGMEM = populate_decimal(17, 39);
const decimal24_t humidity112 PROGMEM = populate_decimal(17, 55);
const decimal24_t humidity113 PROGMEM = populate_decimal(17, 70);
const decimal24_t humidity114 PROGMEM = populate_decimal(17, 86);
const decimal24_t humidity115 PROGMEM = populate_decimal(18, 2);
const decimal24_t humidity116 PROGMEM = populate_decimal(18, 18);
const decimal24_t humidity117 PROGMEM = populate_decimal(18, 33);
const decimal24_t humidity118 PROGMEM = populate_decimal(18, 49);
const decimal24_t humidity119 PROGMEM = populate_decimal(18, 65);
const decimal24_t humidity120 PROGMEM = populate_decimal(18, 81);
const decimal24_t humidity121 PROGMEM = populate_decimal(18, 97);
const decimal24_t humidity122 PROGMEM = populate_decimal(19, 12);
const decimal24_t humidity123 PROGMEM = populate_decimal(19, 28);
const decimal24_t humidity124 PROGMEM = populate_decimal(19, 44);
const decimal24_t humidity125 PROGMEM = populate_decimal(19, 60);
const decimal24_t humidity126 PROGMEM = populate_decimal(19, 75);
const decimal24_t humidity127 PROGMEM = populate_decimal(19, 91);
const decimal24_t humidity128 PROGMEM = populate_decimal(20, 7);
const decimal24_t humidity129 PROGMEM = populate_decimal(20, 23);
const decimal24_t humidity130 PROGMEM = populate_decimal(20, 38);
const decimal24_t humidity131 PROGMEM = populate_decimal(20, 54);
const decimal24_t humidity132 PROGMEM = populate_decimal(20, 70);
const decimal24_t humidity133 PROGMEM = populate_decimal(20, 86);
const decimal24_t humidity134 PROGMEM = populate_decimal(21, 1);
const decimal24_t humidity135 PROGMEM = populate_decimal(21, 17);
const decimal24_t humidity136 PROGMEM = populate_decimal(21, 33);
const decimal24_t humidity137 PROGMEM = populate_decimal(21, 49);
const decimal24_t humidity138 PROGMEM = populate_decimal(21, 65);
const decimal24_t humidity139 PROGMEM = populate_decimal(21, 80);
const decimal24_t humidity140 PROGMEM = populate_decimal(21, 96);
const decimal24_t humidity141 PROGMEM = populate_decimal(22, 12);
const decimal24_t humidity142 PROGMEM = populate_decimal(22, 28);
const decimal24_t humidity143 PROGMEM = populate_decimal(22, 43);
const decimal24_t humidity144 PROGMEM = populate_decimal(22, 59);
const decimal24_t humidity145 PROGMEM = populate_decimal(22, 75);
const decimal24_t humidity146 PROGMEM = populate_decimal(22, 91);
const decimal24_t humidity147 PROGMEM = populate_decimal(23, 6);
const decimal24_t humidity148 PROGMEM = populate_decimal(23, 22);
const decimal24_t humidity149 PROGMEM = populate_decimal(23, 38);
const decimal24_t humidity150 PROGMEM = populate_decimal(23, 54);
const decimal24_t humidity151 PROGMEM = populate_decimal(23, 70);
const decimal24_t humidity152 PROGMEM = populate_decimal(23, 85);
const decimal24_t humidity153 PROGMEM = populate_decimal(24, 1);
const decimal24_t humidity154 PROGMEM = populate_decimal(24, 17);
const decimal24_t humidity155 PROGMEM = populate_decimal(24, 33);
const decimal24_t humidity156 PROGMEM = populate_decimal(24, 48);
const decimal24_t humidity157 PROGMEM = populate_decimal(24, 64);
const decimal24_t humidity158 PROGMEM = populate_decimal(24, 80);
const decimal24_t humidity159 PROGMEM = populate_decimal(24, 96);
const decimal24_t humidity160 PROGMEM = populate_decimal(25, 11);
const decimal24_t humidity161 PROGMEM = populate_decimal(25, 27);
const decimal24_t humidity162 PROGMEM = populate_decimal(25, 43);
const decimal24_t humidity163 PROGMEM = populate_decimal(25, 59);
const decimal24_t humidity164 PROGMEM = populate_decimal(25, 74);
const decimal24_t humidity165 PROGMEM = populate_decimal(25, 90);
const decimal24_t humidity166 PROGMEM = populate_decimal(26, 6);
const decimal24_t humidity167 PROGMEM = populate_decimal(26, 22);
const decimal24_t humidity168 PROGMEM = populate_decimal(26, 38);
const decimal24_t humidity169 PROGMEM = populate_decimal(26, 53);
const decimal24_t humidity170 PROGMEM = populate_decimal(26, 69);
const decimal24_t humidity171 PROGMEM = populate_decimal(26, 85);
const decimal24_t humidity172 PROGMEM = populate_decimal(27, 1);
const decimal24_t humidity173 PROGMEM = populate_decimal(27, 16);
const decimal24_t humidity174 PROGMEM = populate_decimal(27, 32);
const decimal24_t humidity175 PROGMEM = populate_decimal(27, 48);
const decimal24_t humidity176 PROGMEM = populate_decimal(27, 64);
const decimal24_t humidity177 PROGMEM = populate_decimal(27, 79);
const decimal24_t humidity178 PROGMEM = populate_decimal(27, 95);
const decimal24_t humidity179 PROGMEM = populate_decimal(28, 11);
const decimal24_t humidity180 PROGMEM = populate_decimal(28, 27);
const decimal24_t humidity181 PROGMEM = populate_decimal(28, 42);
const decimal24_t humidity182 PROGMEM = populate_decimal(28, 58);
const decimal24_t humidity183 PROGMEM = populate_decimal(28, 74);
const decimal24_t humidity184 PROGMEM = populate_decimal(28, 90);
const decimal24_t humidity185 PROGMEM = populate_decimal(29, 6);
const decimal24_t humidity186 PROGMEM = populate_decimal(29, 21);
const decimal24_t humidity187 PROGMEM = populate_decimal(29, 37);
const decimal24_t humidity188 PROGMEM = populate_decimal(29, 53);
const decimal24_t humidity189 PROGMEM = populate_decimal(29, 69);
const decimal24_t humidity190 PROGMEM = populate_decimal(29, 84);
const decimal24_t humidity191 PROGMEM = populate_decimal(30, 0);
const decimal24_t humidity192 PROGMEM = populate_decimal(30, 16);
const decimal24_t humidity193 PROGMEM = populate_decimal(30, 32);
const decimal24_t humidity194 PROGMEM = populate_decimal(30, 47);
const decimal24_t humidity195 PROGMEM = populate_decimal(30, 63);
const decimal24_t humidity196 PROGMEM = populate_decimal(30, 79);
const decimal24_t humidity197 PROGMEM = populate_decimal(30, 95);
const decimal24_t humidity198 PROGMEM = populate_decimal(31, 11);
const decimal24_t humidity199 PROGMEM = populate_decimal(31, 26);
const decimal24_t humidity200 PROGMEM = populate_decimal(31, 42);
const decimal24_t humidity201 PROGMEM = populate_decimal(31, 58);
const decimal24_t humidity202 PROGMEM = populate_decimal(31, 74);
const decimal24_t humidity203 PROGMEM = populate_decimal(31, 89);
const decimal24_t humidity204 PROGMEM = populate_decimal(32, 5);
const decimal24_t humidity205 PROGMEM = populate_decimal(32, 21);
const decimal24_t humidity206 PROGMEM = populate_decimal(32, 37);
const decimal24_t humidity207 PROGMEM = populate_decimal(32, 52);
const decimal24_t humidity208 PROGMEM = populate_decimal(32, 68);
const decimal24_t humidity209 PROGMEM = populate_decimal(32, 84);
const decimal24_t humidity210 PROGMEM = populate_decimal(33, 0);
const decimal24_t humidity211 PROGMEM = populate_decimal(33, 15);
const decimal24_t humidity212 PROGMEM = populate_decimal(33, 31);
const decimal24_t humidity213 PROGMEM = populate_decimal(33, 47);
const decimal24_t humidity214 PROGMEM = populate_decimal(33, 63);
const decimal24_t humidity215 PROGMEM = populate_decimal(33, 79);
const decimal24_t humidity216 PROGMEM = populate_decimal(33, 94);
const decimal24_t humidity217 PROGMEM = populate_decimal(34, 10);
const decimal24_t humidity218 PROGMEM = populate_decimal(34, 26);
const decimal24_t humidity219 PROGMEM = populate_decimal(34, 42);
const decimal24_t humidity220 PROGMEM = populate_decimal(34, 57);
const decimal24_t humidity221 PROGMEM = populate_decimal(34, 73);
const decimal24_t humidity222 PROGMEM = populate_decimal(34, 89);
const decimal24_t humidity223 PROGMEM = populate_decimal(35, 5);
const decimal24_t humidity224 PROGMEM = populate_decimal(35, 20);
const decimal24_t humidity225 PROGMEM = populate_decimal(35, 36);
const decimal24_t humidity226 PROGMEM = populate_decimal(35, 52);
const decimal24_t humidity227 PROGMEM = populate_decimal(35, 68);
const decimal24_t humidity228 PROGMEM = populate_decimal(35, 84);
const decimal24_t humidity229 PROGMEM = populate_decimal(35, 99);
const decimal24_t humidity230 PROGMEM = populate_decimal(36, 15);
const decimal24_t humidity231 PROGMEM = populate_decimal(36, 31);
const decimal24_t humidity232 PROGMEM = populate_decimal(36, 47);
const decimal24_t humidity233 PROGMEM = populate_decimal(36, 62);
const decimal24_t humidity234 PROGMEM = populate_decimal(36, 78);
const decimal24_t humidity235 PROGMEM = populate_decimal(36, 94);
const decimal24_t humidity236 PROGMEM = populate_decimal(37, 10);
const decimal24_t humidity237 PROGMEM = populate_decimal(37, 25);
const decimal24_t humidity238 PROGMEM = populate_decimal(37, 41);
const decimal24_t humidity239 PROGMEM = populate_decimal(37, 57);
const decimal24_t humidity240 PROGMEM = populate_decimal(37, 73);
const decimal24_t humidity241 PROGMEM = populate_decimal(37, 88);
const decimal24_t humidity242 PROGMEM = populate_decimal(38, 4);
const decimal24_t humidity243 PROGMEM = populate_decimal(38, 20);
const decimal24_t humidity244 PROGMEM = populate_decimal(38, 36);
const decimal24_t humidity245 PROGMEM = populate_decimal(38, 52);
const decimal24_t humidity246 PROGMEM = populate_decimal(38, 67);
const decimal24_t humidity247 PROGMEM = populate_decimal(38, 83);
const decimal24_t humidity248 PROGMEM = populate_decimal(38, 99);
const decimal24_t humidity249 PROGMEM = populate_decimal(39, 15);
const decimal24_t humidity250 PROGMEM = populate_decimal(39, 30);
const decimal24_t humidity251 PROGMEM = populate_decimal(39, 46);
const decimal24_t humidity252 PROGMEM = populate_decimal(39, 62);
const decimal24_t humidity253 PROGMEM = populate_decimal(39, 78);
const decimal24_t humidity254 PROGMEM = populate_decimal(39, 93);
const decimal24_t humidity255 PROGMEM = populate_decimal(40, 9);
const decimal24_t humidity256 PROGMEM = populate_decimal(40, 25);
const decimal24_t humidity257 PROGMEM = populate_decimal(40, 41);
const decimal24_t humidity258 PROGMEM = populate_decimal(40, 57);
const decimal24_t humidity259 PROGMEM = populate_decimal(40, 72);
const decimal24_t humidity260 PROGMEM = populate_decimal(40, 88);
const decimal24_t humidity261 PROGMEM = populate_decimal(41, 4);
const decimal24_t humidity262 PROGMEM = populate_decimal(41, 20);
const decimal24_t humidity263 PROGMEM = populate_decimal(41, 35);
const decimal24_t humidity264 PROGMEM = populate_decimal(41, 51);
const decimal24_t humidity265 PROGMEM = populate_decimal(41, 67);
const decimal24_t humidity266 PROGMEM = populate_decimal(41, 83);
const decimal24_t humidity267 PROGMEM = populate_decimal(41, 98);
const decimal24_t humidity268 PROGMEM = populate_decimal(42, 14);
const decimal24_t humidity269 PROGMEM = populate_decimal(42, 30);
const decimal24_t humidity270 PROGMEM = populate_decimal(42, 46);
const decimal24_t humidity271 PROGMEM = populate_decimal(42, 61);
const decimal24_t humidity272 PROGMEM = populate_decimal(42, 77);
const decimal24_t humidity273 PROGMEM = populate_decimal(42, 93);
const decimal24_t humidity274 PROGMEM = populate_decimal(43, 9);
const decimal24_t humidity275 PROGMEM = populate_decimal(43, 25);
const decimal24_t humidity276 PROGMEM = populate_decimal(43, 40);
const decimal24_t humidity277 PROGMEM = populate_decimal(43, 56);
const decimal24_t humidity278 PROGMEM = populate_decimal(43, 72);
const decimal24_t humidity279 PROGMEM = populate_decimal(43, 88);
const decimal24_t humidity280 PROGMEM = populate_decimal(44, 3);
const decimal24_t humidity281 PROGMEM = populate_decimal(44, 19);
const decimal24_t humidity282 PROGMEM = populate_decimal(44, 35);
const decimal24_t humidity283 PROGMEM = populate_decimal(44, 51);
const decimal24_t humidity284 PROGMEM = populate_decimal(44, 66);
const decimal24_t humidity285 PROGMEM = populate_decimal(44, 82);
const decimal24_t humidity286 PROGMEM = populate_decimal(44, 98);
const decimal24_t humidity287 PROGMEM = populate_decimal(45, 14);
const decimal24_t humidity288 PROGMEM = populate_decimal(45, 30);
const decimal24_t humidity289 PROGMEM = populate_decimal(45, 45);
const decimal24_t humidity290 PROGMEM = populate_decimal(45, 61);
const decimal24_t humidity291 PROGMEM = populate_decimal(45, 77);
const decimal24_t humidity292 PROGMEM = populate_decimal(45, 93);
const decimal24_t humidity293 PROGMEM = populate_decimal(46, 8);
const decimal24_t humidity294 PROGMEM = populate_decimal(46, 24);
const decimal24_t humidity295 PROGMEM = populate_decimal(46, 40);
const decimal24_t humidity296 PROGMEM = populate_decimal(46, 56);
const decimal24_t humidity297 PROGMEM = populate_decimal(46, 71);
const decimal24_t humidity298 PROGMEM = populate_decimal(46, 87);
const decimal24_t humidity299 PROGMEM = populate_decimal(47, 3);
const decimal24_t humidity300 PROGMEM = populate_decimal(47, 19);
const decimal24_t humidity301 PROGMEM = populate_decimal(47, 34);
const decimal24_t humidity302 PROGMEM = populate_decimal(47, 50);
const decimal24_t humidity303 PROGMEM = populate_decimal(47, 66);
const decimal24_t humidity304 PROGMEM = populate_decimal(47, 82);
const decimal24_t humidity305 PROGMEM = populate_decimal(47, 98);
const decimal24_t humidity306 PROGMEM = populate_decimal(48, 13);
const decimal24_t humidity307 PROGMEM = populate_decimal(48, 29);
const decimal24_t humidity308 PROGMEM = populate_decimal(48, 45);
const decimal24_t humidity309 PROGMEM = populate_decimal(48, 61);
const decimal24_t humidity310 PROGMEM = populate_decimal(48, 76);
const decimal24_t humidity311 PROGMEM = populate_decimal(48, 92);
const decimal24_t humidity312 PROGMEM = populate_decimal(49, 8);
const decimal24_t humidity313 PROGMEM = populate_decimal(49, 24);
const decimal24_t humidity314 PROGMEM = populate_decimal(49, 39);
const decimal24_t humidity315 PROGMEM = populate_decimal(49, 55);
const decimal24_t humidity316 PROGMEM = populate_decimal(49, 71);
const decimal24_t humidity317 PROGMEM = populate_decimal(49, 87);
const decimal24_t humidity318 PROGMEM = populate_decimal(50, 2);
const decimal24_t humidity319 PROGMEM = populate_decimal(50, 18);
const decimal24_t humidity320 PROGMEM = populate_decimal(50, 34);
const decimal24_t humidity321 PROGMEM = populate_decimal(50, 50);
const decimal24_t humidity322 PROGMEM = populate_decimal(50, 66);
const decimal24_t humidity323 PROGMEM = populate_decimal(50, 81);
const decimal24_t humidity324 PROGMEM = populate_decimal(50, 97);
const decimal24_t humidity325 PROGMEM = populate_decimal(51, 13);
const decimal24_t humidity326 PROGMEM = populate_decimal(51, 29);
const decimal24_t humidity327 PROGMEM = populate_decimal(51, 44);
const decimal24_t humidity328 PROGMEM = populate_decimal(51, 60);
const decimal24_t humidity329 PROGMEM = populate_decimal(51, 76);
const decimal24_t humidity330 PROGMEM = populate_decimal(51, 92);
const decimal24_t humidity331 PROGMEM = populate_decimal(52, 7);
const decimal24_t humidity332 PROGMEM = populate_decimal(52, 23);
const decimal24_t humidity333 PROGMEM = populate_decimal(52, 39);
const decimal24_t humidity334 PROGMEM = populate_decimal(52, 55);
const decimal24_t humidity335 PROGMEM = populate_decimal(52, 71);
const decimal24_t humidity336 PROGMEM = populate_decimal(52, 86);
const decimal24_t humidity337 PROGMEM = populate_decimal(53, 2);
const decimal24_t humidity338 PROGMEM = populate_decimal(53, 18);
const decimal24_t humidity339 PROGMEM = populate_decimal(53, 34);
const decimal24_t humidity340 PROGMEM = populate_decimal(53, 49);
const decimal24_t humidity341 PROGMEM = populate_decimal(53, 65);
const decimal24_t humidity342 PROGMEM = populate_decimal(53, 81);
const decimal24_t humidity343 PROGMEM = populate_decimal(53, 97);
const decimal24_t humidity344 PROGMEM = populate_decimal(54, 12);
const decimal24_t humidity345 PROGMEM = populate_decimal(54, 28);
const decimal24_t humidity346 PROGMEM = populate_decimal(54, 44);
const decimal24_t humidity347 PROGMEM = populate_decimal(54, 60);
const decimal24_t humidity348 PROGMEM = populate_decimal(54, 75);
const decimal24_t humidity349 PROGMEM = populate_decimal(54, 91);
const decimal24_t humidity350 PROGMEM = populate_decimal(55, 7);
const decimal24_t humidity351 PROGMEM = populate_decimal(55, 23);
const decimal24_t humidity352 PROGMEM = populate_decimal(55, 39);
const decimal24_t humidity353 PROGMEM = populate_decimal(55, 54);
const decimal24_t humidity354 PROGMEM = populate_decimal(55, 70);
const decimal24_t humidity355 PROGMEM = populate_decimal(55, 86);
const decimal24_t humidity356 PROGMEM = populate_decimal(56, 2);
const decimal24_t humidity357 PROGMEM = populate_decimal(56, 17);
const decimal24_t humidity358 PROGMEM = populate_decimal(56, 33);
const decimal24_t humidity359 PROGMEM = populate_decimal(56, 49);
const decimal24_t humidity360 PROGMEM = populate_decimal(56, 65);
const decimal24_t humidity361 PROGMEM = populate_decimal(56, 80);
const decimal24_t humidity362 PROGMEM = populate_decimal(56, 96);
const decimal24_t humidity363 PROGMEM = populate_decimal(57, 12);
const decimal24_t humidity364 PROGMEM = populate_decimal(57, 28);
const decimal24_t humidity365 PROGMEM = populate_decimal(57, 44);
const decimal24_t humidity366 PROGMEM = populate_decimal(57, 59);
const decimal24_t humidity367 PROGMEM = populate_decimal(57, 75);
const decimal24_t humidity368 PROGMEM = populate_decimal(57, 91);
const decimal24_t humidity369 PROGMEM = populate_decimal(58, 7);
const decimal24_t humidity370 PROGMEM = populate_decimal(58, 22);
const decimal24_t humidity371 PROGMEM = populate_decimal(58, 38);
const decimal24_t humidity372 PROGMEM = populate_decimal(58, 54);
const decimal24_t humidity373 PROGMEM = populate_decimal(58, 70);
const decimal24_t humidity374 PROGMEM = populate_decimal(58, 85);
const decimal24_t humidity375 PROGMEM = populate_decimal(59, 1);
const decimal24_t humidity376 PROGMEM = populate_decimal(59, 17);
const decimal24_t humidity377 PROGMEM = populate_decimal(59, 33);
const decimal24_t humidity378 PROGMEM = populate_decimal(59, 48);
const decimal24_t humidity379 PROGMEM = populate_decimal(59, 64);
const decimal24_t humidity380 PROGMEM = populate_decimal(59, 80);
const decimal24_t humidity381 PROGMEM = populate_decimal(59, 96);
const decimal24_t humidity382 PROGMEM = populate_decimal(60, 12);
const decimal24_t humidity383 PROGMEM = populate_decimal(60, 27);
const decimal24_t humidity384 PROGMEM = populate_decimal(60, 43);
const decimal24_t humidity385 PROGMEM = populate_decimal(60, 59);
const decimal24_t humidity386 PROGMEM = populate_decimal(60, 75);
const decimal24_t humidity387 PROGMEM = populate_decimal(60, 90);
const decimal24_t humidity388 PROGMEM = populate_decimal(61, 6);
const decimal24_t humidity389 PROGMEM = populate_decimal(61, 22);
const decimal24_t humidity390 PROGMEM = populate_decimal(61, 38);
const decimal24_t humidity391 PROGMEM = populate_decimal(61, 53);
const decimal24_t humidity392 PROGMEM = populate_decimal(61, 69);
const decimal24_t humidity393 PROGMEM = populate_decimal(61, 85);
const decimal24_t humidity394 PROGMEM = populate_decimal(62, 1);
const decimal24_t humidity395 PROGMEM = populate_decimal(62, 17);
const decimal24_t humidity396 PROGMEM = populate_decimal(62, 32);
const decimal24_t humidity397 PROGMEM = populate_decimal(62, 48);
const decimal24_t humidity398 PROGMEM = populate_decimal(62, 64);
const decimal24_t humidity399 PROGMEM = populate_decimal(62, 80);
const decimal24_t humidity400 PROGMEM = populate_decimal(62, 95);
const decimal24_t humidity401 PROGMEM = populate_decimal(63, 11);
const decimal24_t humidity402 PROGMEM = populate_decimal(63, 27);
const decimal24_t humidity403 PROGMEM = populate_decimal(63, 43);
const decimal24_t humidity404 PROGMEM = populate_decimal(63, 58);
const decimal24_t humidity405 PROGMEM = populate_decimal(63, 74);
const decimal24_t humidity406 PROGMEM = populate_decimal(63, 90);
const decimal24_t humidity407 PROGMEM = populate_decimal(64, 6);
const decimal24_t humidity408 PROGMEM = populate_decimal(64, 21);
const decimal24_t humidity409 PROGMEM = populate_decimal(64, 37);
const decimal24_t humidity410 PROGMEM = populate_decimal(64, 53);
const decimal24_t humidity411 PROGMEM = populate_decimal(64, 69);
const decimal24_t humidity412 PROGMEM = populate_decimal(64, 85);
const decimal24_t humidity413 PROGMEM = populate_decimal(65, 0);
const decimal24_t humidity414 PROGMEM = populate_decimal(65, 16);
const decimal24_t humidity415 PROGMEM = populate_decimal(65, 32);
const decimal24_t humidity416 PROGMEM = populate_decimal(65, 48);
const decimal24_t humidity417 PROGMEM = populate_decimal(65, 63);
const decimal24_t humidity418 PROGMEM = populate_decimal(65, 79);
const decimal24_t humidity419 PROGMEM = populate_decimal(65, 95);
const decimal24_t humidity420 PROGMEM = populate_decimal(66, 11);
const decimal24_t humidity421 PROGMEM = populate_decimal(66, 26);
const decimal24_t humidity422 PROGMEM = populate_decimal(66, 42);
const decimal24_t humidity423 PROGMEM = populate_decimal(66, 58);
const decimal24_t humidity424 PROGMEM = populate_decimal(66, 74);
const decimal24_t humidity425 PROGMEM = populate_decimal(66, 90);
const decimal24_t humidity426 PROGMEM = populate_decimal(67, 5);
const decimal24_t humidity427 PROGMEM = populate_decimal(67, 21);
const decimal24_t humidity428 PROGMEM = populate_decimal(67, 37);
const decimal24_t humidity429 PROGMEM = populate_decimal(67, 53);
const decimal24_t humidity430 PROGMEM = populate_decimal(67, 68);
const decimal24_t humidity431 PROGMEM = populate_decimal(67, 84);
const decimal24_t humidity432 PROGMEM = populate_decimal(68, 0);
const decimal24_t humidity433 PROGMEM = populate_decimal(68, 16);
const decimal24_t humidity434 PROGMEM = populate_decimal(68, 31);
const decimal24_t humidity435 PROGMEM = populate_decimal(68, 47);
const decimal24_t humidity436 PROGMEM = populate_decimal(68, 63);
const decimal24_t humidity437 PROGMEM = populate_decimal(68, 79);
const decimal24_t humidity438 PROGMEM = populate_decimal(68, 94);
const decimal24_t humidity439 PROGMEM = populate_decimal(69, 10);
const decimal24_t humidity440 PROGMEM = populate_decimal(69, 26);
const decimal24_t humidity441 PROGMEM = populate_decimal(69, 42);
const decimal24_t humidity442 PROGMEM = populate_decimal(69, 58);
const decimal24_t humidity443 PROGMEM = populate_decimal(69, 73);
const decimal24_t humidity444 PROGMEM = populate_decimal(69, 89);
const decimal24_t humidity445 PROGMEM = populate_decimal(70, 5);
const decimal24_t humidity446 PROGMEM = populate_decimal(70, 21);
const decimal24_t humidity447 PROGMEM = populate_decimal(70, 36);
const decimal24_t humidity448 PROGMEM = populate_decimal(70, 52);
const decimal24_t humidity449 PROGMEM = populate_decimal(70, 68);
const decimal24_t humidity450 PROGMEM = populate_decimal(70, 84);
const decimal24_t humidity451 PROGMEM = populate_decimal(70, 99);
const decimal24_t humidity452 PROGMEM = populate_decimal(71, 15);
const decimal24_t humidity453 PROGMEM = populate_decimal(71, 31);
const decimal24_t humidity454 PROGMEM = populate_decimal(71, 47);
const decimal24_t humidity455 PROGMEM = populate_decimal(71, 62);
const decimal24_t humidity456 PROGMEM = populate_decimal(71, 78);
const decimal24_t humidity457 PROGMEM = populate_decimal(71, 94);
const decimal24_t humidity458 PROGMEM = populate_decimal(72, 10);
const decimal24_t humidity459 PROGMEM = populate_decimal(72, 26);
const decimal24_t humidity460 PROGMEM = populate_decimal(72, 41);
const decimal24_t humidity461 PROGMEM = populate_decimal(72, 57);
const decimal24_t humidity462 PROGMEM = populate_decimal(72, 73);
const decimal24_t humidity463 PROGMEM = populate_decimal(72, 89);
const decimal24_t humidity464 PROGMEM = populate_decimal(73, 4);
const decimal24_t humidity465 PROGMEM = populate_decimal(73, 20);
const decimal24_t humidity466 PROGMEM = populate_decimal(73, 36);
const decimal24_t humidity467 PROGMEM = populate_decimal(73, 52);
const decimal24_t humidity468 PROGMEM = populate_decimal(73, 67);
const decimal24_t humidity469 PROGMEM = populate_decimal(73, 83);
const decimal24_t humidity470 PROGMEM = populate_decimal(73, 99);
const decimal24_t humidity471 PROGMEM = populate_decimal(74, 15);
const decimal24_t humidity472 PROGMEM = populate_decimal(74, 31);
const decimal24_t humidity473 PROGMEM = populate_decimal(74, 46);
const decimal24_t humidity474 PROGMEM = populate_decimal(74, 62);
const decimal24_t humidity475 PROGMEM = populate_decimal(74, 78);
const decimal24_t humidity476 PROGMEM = populate_decimal(74, 94);
const decimal24_t humidity477 PROGMEM = populate_decimal(75, 9);
const decimal24_t humidity478 PROGMEM = populate_decimal(75, 25);
const decimal24_t humidity479 PROGMEM = populate_decimal(75, 41);
const decimal24_t humidity480 PROGMEM = populate_decimal(75, 57);
const decimal24_t humidity481 PROGMEM = populate_decimal(75, 72);
const decimal24_t humidity482 PROGMEM = populate_decimal(75, 88);
const decimal24_t humidity483 PROGMEM = populate_decimal(76, 4);
const decimal24_t humidity484 PROGMEM = populate_decimal(76, 20);
const decimal24_t humidity485 PROGMEM = populate_decimal(76, 35);
const decimal24_t humidity486 PROGMEM = populate_decimal(76, 51);
const decimal24_t humidity487 PROGMEM = populate_decimal(76, 67);
const decimal24_t humidity488 PROGMEM = populate_decimal(76, 83);
const decimal24_t humidity489 PROGMEM = populate_decimal(76, 99);
const decimal24_t humidity490 PROGMEM = populate_decimal(77, 14);
const decimal24_t humidity491 PROGMEM = populate_decimal(77, 30);
const decimal24_t humidity492 PROGMEM = populate_decimal(77, 46);
const decimal24_t humidity493 PROGMEM = populate_decimal(77, 62);
const decimal24_t humidity494 PROGMEM = populate_decimal(77, 77);
const decimal24_t humidity495 PROGMEM = populate_decimal(77, 93);
const decimal24_t humidity496 PROGMEM = populate_decimal(78, 9);
const decimal24_t humidity497 PROGMEM = populate_decimal(78, 25);
const decimal24_t humidity498 PROGMEM = populate_decimal(78, 40);
const decimal24_t humidity499 PROGMEM = populate_decimal(78, 56);
const decimal24_t humidity500 PROGMEM = populate_decimal(78, 72);
const decimal24_t humidity501 PROGMEM = populate_decimal(78, 88);
const decimal24_t humidity502 PROGMEM = populate_decimal(79, 4);
const decimal24_t humidity503 PROGMEM = populate_decimal(79, 19);
const decimal24_t humidity504 PROGMEM = populate_decimal(79, 35);
const decimal24_t humidity505 PROGMEM = populate_decimal(79, 51);
const decimal24_t humidity506 PROGMEM = populate_decimal(79, 67);
const decimal24_t humidity507 PROGMEM = populate_decimal(79, 82);
const decimal24_t humidity508 PROGMEM = populate_decimal(79, 98);
const decimal24_t humidity509 PROGMEM = populate_decimal(80, 14);
const decimal24_t humidity510 PROGMEM = populate_decimal(80, 30);
const decimal24_t humidity511 PROGMEM = populate_decimal(80, 45);
const decimal24_t humidity512 PROGMEM = populate_decimal(80, 61);
const decimal24_t humidity513 PROGMEM = populate_decimal(80, 77);
const decimal24_t humidity514 PROGMEM = populate_decimal(80, 93);
const decimal24_t humidity515 PROGMEM = populate_decimal(81, 8);
const decimal24_t humidity516 PROGMEM = populate_decimal(81, 24);
const decimal24_t humidity517 PROGMEM = populate_decimal(81, 40);
const decimal24_t humidity518 PROGMEM = populate_decimal(81, 56);
const decimal24_t humidity519 PROGMEM = populate_decimal(81, 72);
const decimal24_t humidity520 PROGMEM = populate_decimal(81, 87);
const decimal24_t humidity521 PROGMEM = populate_decimal(82, 3);
const decimal24_t humidity522 PROGMEM = populate_decimal(82, 19);
const decimal24_t humidity523 PROGMEM = populate_decimal(82, 35);
const decimal24_t humidity524 PROGMEM = populate_decimal(82, 50);
const decimal24_t humidity525 PROGMEM = populate_decimal(82, 66);
const decimal24_t humidity526 PROGMEM = populate_decimal(82, 82);
const decimal24_t humidity527 PROGMEM = populate_decimal(82, 98);
const decimal24_t humidity528 PROGMEM = populate_decimal(83, 13);
const decimal24_t humidity529 PROGMEM = populate_decimal(83, 29);
const decimal24_t humidity530 PROGMEM = populate_decimal(83, 45);
const decimal24_t humidity531 PROGMEM = populate_decimal(83, 61);
const decimal24_t humidity532 PROGMEM = populate_decimal(83, 77);
const decimal24_t humidity533 PROGMEM = populate_decimal(83, 92);
const decimal24_t humidity534 PROGMEM = populate_decimal(84, 8);
const decimal24_t humidity535 PROGMEM = populate_decimal(84, 24);
const decimal24_t humidity536 PROGMEM = populate_decimal(84, 40);
const decimal24_t humidity537 PROGMEM = populate_decimal(84, 55);
const decimal24_t humidity538 PROGMEM = populate_decimal(84, 71);
const decimal24_t humidity539 PROGMEM = populate_decimal(84, 87);
const decimal24_t humidity540 PROGMEM = populate_decimal(85, 3);
const decimal24_t humidity541 PROGMEM = populate_decimal(85, 18);
const decimal24_t humidity542 PROGMEM = populate_decimal(85, 34);
const decimal24_t humidity543 PROGMEM = populate_decimal(85, 50);
const decimal24_t humidity544 PROGMEM = populate_decimal(85, 66);
const decimal24_t humidity545 PROGMEM = populate_decimal(85, 81);
const decimal24_t humidity546 PROGMEM = populate_decimal(85, 97);
const decimal24_t humidity547 PROGMEM = populate_decimal(86, 13);
const decimal24_t humidity548 PROGMEM = populate_decimal(86, 29);
const decimal24_t humidity549 PROGMEM = populate_decimal(86, 45);
const decimal24_t humidity550 PROGMEM = populate_decimal(86, 60);
const decimal24_t humidity551 PROGMEM = populate_decimal(86, 76);
const decimal24_t humidity552 PROGMEM = populate_decimal(86, 92);
const decimal24_t humidity553 PROGMEM = populate_decimal(87, 8);
const decimal24_t humidity554 PROGMEM = populate_decimal(87, 23);
const decimal24_t humidity555 PROGMEM = populate_decimal(87, 39);
const decimal24_t humidity556 PROGMEM = populate_decimal(87, 55);
const decimal24_t humidity557 PROGMEM = populate_decimal(87, 71);
const decimal24_t humidity558 PROGMEM = populate_decimal(87, 86);
const decimal24_t humidity559 PROGMEM = populate_decimal(88, 2);
const decimal24_t humidity560 PROGMEM = populate_decimal(88, 18);
const decimal24_t humidity561 PROGMEM = populate_decimal(88, 34);
const decimal24_t humidity562 PROGMEM = populate_decimal(88, 49);
const decimal24_t humidity563 PROGMEM = populate_decimal(88, 65);
const decimal24_t humidity564 PROGMEM = populate_decimal(88, 81);
const decimal24_t humidity565 PROGMEM = populate_decimal(88, 97);
const decimal24_t humidity566 PROGMEM = populate_decimal(89, 13);
const decimal24_t humidity567 PROGMEM = populate_decimal(89, 28);
const decimal24_t humidity568 PROGMEM = populate_decimal(89, 44);
const decimal24_t humidity569 PROGMEM = populate_decimal(89, 60);
const decimal24_t humidity570 PROGMEM = populate_decimal(89, 76);
const decimal24_t humidity571 PROGMEM = populate_decimal(89, 91);
const decimal24_t humidity572 PROGMEM = populate_decimal(90, 7);
const decimal24_t humidity573 PROGMEM = populate_decimal(90, 23);
const decimal24_t humidity574 PROGMEM = populate_decimal(90, 39);
const decimal24_t humidity575 PROGMEM = populate_decimal(90, 54);
const decimal24_t humidity576 PROGMEM = populate_decimal(90, 70);
const decimal24_t humidity577 PROGMEM = populate_decimal(90, 86);
const decimal24_t humidity578 PROGMEM = populate_decimal(91, 2);
const decimal24_t humidity579 PROGMEM = populate_decimal(91, 18);
const decimal24_t humidity580 PROGMEM = populate_decimal(91, 33);
const decimal24_t humidity581 PROGMEM = populate_decimal(91, 49);
const decimal24_t humidity582 PROGMEM = populate_decimal(91, 65);
const decimal24_t humidity583 PROGMEM = populate_decimal(91, 81);
const decimal24_t humidity584 PROGMEM = populate_decimal(91, 96);
const decimal24_t humidity585 PROGMEM = populate_decimal(92, 12);
const decimal24_t humidity586 PROGMEM = populate_decimal(92, 28);
const decimal24_t humidity587 PROGMEM = populate_decimal(92, 44);
const decimal24_t humidity588 PROGMEM = populate_decimal(92, 59);
const decimal24_t humidity589 PROGMEM = populate_decimal(92, 75);
const decimal24_t humidity590 PROGMEM = populate_decimal(92, 91);
const decimal24_t humidity591 PROGMEM = populate_decimal(93, 7);
const decimal24_t humidity592 PROGMEM = populate_decimal(93, 22);
const decimal24_t humidity593 PROGMEM = populate_decimal(93, 38);
const decimal24_t humidity594 PROGMEM = populate_decimal(93, 54);
const decimal24_t humidity595 PROGMEM = populate_decimal(93, 70);
const decimal24_t humidity596 PROGMEM = populate_decimal(93, 86);
const decimal24_t humidity597 PROGMEM = populate_decimal(94, 1);
const decimal24_t humidity598 PROGMEM = populate_decimal(94, 17);
const decimal24_t humidity599 PROGMEM = populate_decimal(94, 33);
const decimal24_t humidity600 PROGMEM = populate_decimal(94, 49);
const decimal24_t humidity601 PROGMEM = populate_decimal(94, 64);
const decimal24_t humidity602 PROGMEM = populate_decimal(94, 80);
const decimal24_t humidity603 PROGMEM = populate_decimal(94, 96);
const decimal24_t humidity604 PROGMEM = populate_decimal(95, 12);
const decimal24_t humidity605 PROGMEM = populate_decimal(95, 27);
const decimal24_t humidity606 PROGMEM = populate_decimal(95, 43);
const decimal24_t humidity607 PROGMEM = populate_decimal(95, 59);
const decimal24_t humidity608 PROGMEM = populate_decimal(95, 75);
const decimal24_t humidity609 PROGMEM = populate_decimal(95, 91);
const decimal24_t humidity610 PROGMEM = populate_decimal(96, 6);
const decimal24_t humidity611 PROGMEM = populate_decimal(96, 22);
const decimal24_t humidity612 PROGMEM = populate_decimal(96, 38);
const decimal24_t humidity613 PROGMEM = populate_decimal(96, 54);
const decimal24_t humidity614 PROGMEM = populate_decimal(96, 69);
const decimal24_t humidity615 PROGMEM = populate_decimal(96, 85);
const decimal24_t humidity616 PROGMEM = populate_decimal(97, 1);
const decimal24_t humidity617 PROGMEM = populate_decimal(97, 17);
const decimal24_t humidity618 PROGMEM = populate_decimal(97, 32);
const decimal24_t humidity619 PROGMEM = populate_decimal(97, 48);
const decimal24_t humidity620 PROGMEM = populate_decimal(97, 64);
const decimal24_t humidity621 PROGMEM = populate_decimal(97, 80);
const decimal24_t humidity622 PROGMEM = populate_decimal(97, 95);
const decimal24_t humidity623 PROGMEM = populate_decimal(98, 11);
const decimal24_t humidity624 PROGMEM = populate_decimal(98, 27);
const decimal24_t humidity625 PROGMEM = populate_decimal(98, 43);
const decimal24_t humidity626 PROGMEM = populate_decimal(98, 59);
const decimal24_t humidity627 PROGMEM = populate_decimal(98, 74);
const decimal24_t humidity628 PROGMEM = populate_decimal(98, 90);
const decimal24_t humidity629 PROGMEM = populate_decimal(99, 6);
const decimal24_t humidity630 PROGMEM = populate_decimal(99, 22);
const decimal24_t humidity631 PROGMEM = populate_decimal(99, 37);
const decimal24_t humidity632 PROGMEM = populate_decimal(99, 53);
const decimal24_t humidity633 PROGMEM = populate_decimal(99, 69);
const decimal24_t humidity634 PROGMEM = populate_decimal(99, 85);
const decimal24_t humidity635 PROGMEM = populate_decimal(100, 0);
const decimal24_t humidity636 PROGMEM = populate_decimal(100, 16);
const decimal24_t humidity637 PROGMEM = populate_decimal(100, 32);
const decimal24_t humidity638 PROGMEM = populate_decimal(100, 48);
const decimal24_t humidity639 PROGMEM = populate_decimal(100, 64);
const decimal24_t humidity640 PROGMEM = populate_decimal(100, 79);
const decimal24_t humidity641 PROGMEM = populate_decimal(100, 95);
const decimal24_t humidity642 PROGMEM = populate_decimal(101, 11);
const decimal24_t humidity643 PROGMEM = populate_decimal(101, 27);
const decimal24_t humidity644 PROGMEM = populate_decimal(101, 42);
const decimal24_t humidity645 PROGMEM = populate_decimal(101, 58);
const decimal24_t humidity646 PROGMEM = populate_decimal(101, 74);
const decimal24_t humidity647 PROGMEM = populate_decimal(101, 90);
const decimal24_t humidity648 PROGMEM = populate_decimal(102, 5);
const decimal24_t humidity649 PROGMEM = populate_decimal(102, 21);
const decimal24_t humidity650 PROGMEM = populate_decimal(102, 37);
const decimal24_t humidity651 PROGMEM = populate_decimal(102, 53);
const decimal24_t humidity652 PROGMEM = populate_decimal(102, 68);
const decimal24_t humidity653 PROGMEM = populate_decimal(102, 84);
const decimal24_t humidity654 PROGMEM = populate_decimal(103, 0);
const decimal24_t humidity655 PROGMEM = populate_decimal(103, 16);
const decimal24_t humidity656 PROGMEM = populate_decimal(103, 32);
const decimal24_t humidity657 PROGMEM = populate_decimal(103, 47);
const decimal24_t humidity658 PROGMEM = populate_decimal(103, 63);
const decimal24_t humidity659 PROGMEM = populate_decimal(103, 79);
const decimal24_t humidity660 PROGMEM = populate_decimal(103, 95);
const decimal24_t humidity661 PROGMEM = populate_decimal(104, 10);
const decimal24_t humidity662 PROGMEM = populate_decimal(104, 26);
const decimal24_t humidity663 PROGMEM = populate_decimal(104, 42);
const decimal24_t humidity664 PROGMEM = populate_decimal(104, 58);
const decimal24_t humidity665 PROGMEM = populate_decimal(104, 73);
const decimal24_t humidity666 PROGMEM = populate_decimal(104, 89);
const decimal24_t humidity667 PROGMEM = populate_decimal(105, 5);
const decimal24_t humidity668 PROGMEM = populate_decimal(105, 21);
const decimal24_t humidity669 PROGMEM = populate_decimal(105, 37);
const decimal24_t humidity670 PROGMEM = populate_decimal(105, 52);
const decimal24_t humidity671 PROGMEM = populate_decimal(105, 68);
const decimal24_t humidity672 PROGMEM = populate_decimal(105, 84);
const decimal24_t humidity673 PROGMEM = populate_decimal(106, 0);
const decimal24_t humidity674 PROGMEM = populate_decimal(106, 15);
const decimal24_t humidity675 PROGMEM = populate_decimal(106, 31);
const decimal24_t humidity676 PROGMEM = populate_decimal(106, 47);
const decimal24_t humidity677 PROGMEM = populate_decimal(106, 63);
const decimal24_t humidity678 PROGMEM = populate_decimal(106, 78);
const decimal24_t humidity679 PROGMEM = populate_decimal(106, 94);
const decimal24_t humidity680 PROGMEM = populate_decimal(107, 10);
const decimal24_t humidity681 PROGMEM = populate_decimal(107, 26);
const decimal24_t humidity682 PROGMEM = populate_decimal(107, 41);
const decimal24_t humidity683 PROGMEM = populate_decimal(107, 57);
const decimal24_t humidity684 PROGMEM = populate_decimal(107, 73);
const decimal24_t humidity685 PROGMEM = populate_decimal(107, 89);
const decimal24_t humidity686 PROGMEM = populate_decimal(108, 5);
const decimal24_t humidity687 PROGMEM = populate_decimal(108, 20);
const decimal24_t humidity688 PROGMEM = populate_decimal(108, 36);
const decimal24_t humidity689 PROGMEM = populate_decimal(108, 52);
const decimal24_t humidity690 PROGMEM = populate_decimal(108, 68);
const decimal24_t humidity691 PROGMEM = populate_decimal(108, 83);
const decimal24_t humidity692 PROGMEM = populate_decimal(108, 99);
const decimal24_t humidity693 PROGMEM = populate_decimal(109, 15);
const decimal24_t humidity694 PROGMEM = populate_decimal(109, 31);
const decimal24_t humidity695 PROGMEM = populate_decimal(109, 46);
const decimal24_t humidity696 PROGMEM = populate_decimal(109, 62);
const decimal24_t humidity697 PROGMEM = populate_decimal(109, 78);
const decimal24_t humidity698 PROGMEM = populate_decimal(109, 94);
const decimal24_t humidity699 PROGMEM = populate_decimal(110, 9);
const decimal24_t humidity700 PROGMEM = populate_decimal(110, 25);

static PGM_VOID_P const humidityLookup[HUMIDITY_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
&humidity0,
&humidity1,
&humidity2,
&humidity3,
&humidity4,
&humidity5,
&humidity6,
&humidity7,
&humidity8,
&humidity9,
&humidity10,
&humidity11,
&humidity12,
&humidity13,
&humidity14,
&humidity15,
&humidity16,
&humidity17,
&humidity18,
&humidity19,
&humidity20,
&humidity21,
&humidity22,
&humidity23,
&humidity24,
&humidity25,
&humidity26,
&humidity27,
&humidity28,
&humidity29,
&humidity30,
&humidity31,
&humidity32,
&humidity33,
&humidity34,
&humidity35,
&humidity36,
&humidity37,
&humidity38,
&humidity39,
&humidity40,
&humidity41,
&humidity42,
&humidity43,
&humidity44,
&humidity45,
&humidity46,
&humidity47,
&humidity48,
&humidity49,
&humidity50,
&humidity51,
&humidity52,
&humidity53,
&humidity54,
&humidity55,
&humidity56,
&humidity57,
&humidity58,
&humidity59,
&humidity60,
&humidity61,
&humidity62,
&humidity63,
&humidity64,
&humidity65,
&humidity66,
&humidity67,
&humidity68,
&humidity69,
&humidity70,
&humidity71,
&humidity72,
&humidity73,
&humidity74,
&humidity75,
&humidity76,
&humidity77,
&humidity78,
&humidity79,
&humidity80,
&humidity81,
&humidity82,
&humidity83,
&humidity84,
&humidity85,
&humidity86,
&humidity87,
&humidity88,
&humidity89,
&humidity90,
&humidity91,
&humidity92,
&humidity93,
&humidity94,
&humidity95,
&humidity96,
&humidity97,
&humidity98,
&humidity99,
&humidity100,
&humidity101,
&humidity102,
&humidity103,
&humidity104,
&humidity105,
&humidity106,
&humidity107,
&humidity108,
&humidity109,
&humidity110,
&humidity111,
&humidity112,
&humidity113,
&humidity114,
&humidity115,
&humidity116,
&humidity117,
&humidity118,
&humidity119,
&humidity120,
&humidity121,
&humidity122,
&humidity123,
&humidity124,
&humidity125,
&humidity126,
&humidity127,
&humidity128,
&humidity129,
&humidity130,
&humidity131,
&humidity132,
&humidity133,
&humidity134,
&humidity135,
&humidity136,
&humidity137,
&humidity138,
&humidity139,
&humidity140,
&humidity141,
&humidity142,
&humidity143,
&humidity144,
&humidity145,
&humidity146,
&humidity147,
&humidity148,
&humidity149,
&humidity150,
&humidity151,
&humidity152,
&humidity153,
&humidity154,
&humidity155,
&humidity156,
&humidity157,
&humidity158,
&humidity159,
&humidity160,
&humidity161,
&humidity162,
&humidity163,
&humidity164,
&humidity165,
&humidity166,
&humidity167,
&humidity168,
&humidity169,
&humidity170,
&humidity171,
&humidity172,
&humidity173,
&humidity174,
&humidity175,
&humidity176,
&humidity177,
&humidity178,
&humidity179,
&humidity180,
&humidity181,
&humidity182,
&humidity183,
&humidity184,
&humidity185,
&humidity186,
&humidity187,
&humidity188,
&humidity189,
&humidity190,
&humidity191,
&humidity192,
&humidity193,
&humidity194,
&humidity195,
&humidity196,
&humidity197,
&humidity198,
&humidity199,
&humidity200,
&humidity201,
&humidity202,
&humidity203,
&humidity204,
&humidity205,
&humidity206,
&humidity207,
&humidity208,
&humidity209,
&humidity210,
&humidity211,
&humidity212,
&humidity213,
&humidity214,
&humidity215,
&humidity216,
&humidity217,
&humidity218,
&humidity219,
&humidity220,
&humidity221,
&humidity222,
&humidity223,
&humidity224,
&humidity225,
&humidity226,
&humidity227,
&humidity228,
&humidity229,
&humidity230,
&humidity231,
&humidity232,
&humidity233,
&humidity234,
&humidity235,
&humidity236,
&humidity237,
&humidity238,
&humidity239,
&humidity240,
&humidity241,
&humidity242,
&humidity243,
&humidity244,
&humidity245,
&humidity246,
&humidity247,
&humidity248,
&humidity249,
&humidity250,
&humidity251,
&humidity252,
&humidity253,
&humidity254,
&humidity255,
&humidity256,
&humidity257,
&humidity258,
&humidity259,
&humidity260,
&humidity261,
&humidity262,
&humidity263,
&humidity264,
&humidity265,
&humidity266,
&humidity267,
&humidity268,
&humidity269,
&humidity270,
&humidity271,
&humidity272,
&humidity273,
&humidity274,
&humidity275,
&humidity276,
&humidity277,
&humidity278,
&humidity279,
&humidity280,
&humidity281,
&humidity282,
&humidity283,
&humidity284,
&humidity285,
&humidity286,
&humidity287,
&humidity288,
&humidity289,
&humidity290,
&humidity291,
&humidity292,
&humidity293,
&humidity294,
&humidity295,
&humidity296,
&humidity297,
&humidity298,
&humidity299,
&humidity300,
&humidity301,
&humidity302,
&humidity303,
&humidity304,
&humidity305,
&humidity306,
&humidity307,
&humidity308,
&humidity309,
&humidity310,
&humidity311,
&humidity312,
&humidity313,
&humidity314,
&humidity315,
&humidity316,
&humidity317,
&humidity318,
&humidity319,
&humidity320,
&humidity321,
&humidity322,
&humidity323,
&humidity324,
&humidity325,
&humidity326,
&humidity327,
&humidity328,
&humidity329,
&humidity330,
&humidity331,
&humidity332,
&humidity333,
&humidity334,
&humidity335,
&humidity336,
&humidity337,
&humidity338,
&humidity339,
&humidity340,
&humidity341,
&humidity342,
&humidity343,
&humidity344,
&humidity345,
&humidity346,
&humidity347,
&humidity348,
&humidity349,
&humidity350,
&humidity351,
&humidity352,
&humidity353,
&humidity354,
&humidity355,
&humidity356,
&humidity357,
&humidity358,
&humidity359,
&humidity360,
&humidity361,
&humidity362,
&humidity363,
&humidity364,
&humidity365,
&humidity366,
&humidity367,
&humidity368,
&humidity369,
&humidity370,
&humidity371,
&humidity372,
&humidity373,
&humidity374,
&humidity375,
&humidity376,
&humidity377,
&humidity378,
&humidity379,
&humidity380,
&humidity381,
&humidity382,
&humidity383,
&humidity384,
&humidity385,
&humidity386,
&humidity387,
&humidity388,
&humidity389,
&humidity390,
&humidity391,
&humidity392,
&humidity393,
&humidity394,
&humidity395,
&humidity396,
&humidity397,
&humidity398,
&humidity399,
&humidity400,
&humidity401,
&humidity402,
&humidity403,
&humidity404,
&humidity405,
&humidity406,
&humidity407,
&humidity408,
&humidity409,
&humidity410,
&humidity411,
&humidity412,
&humidity413,
&humidity414,
&humidity415,
&humidity416,
&humidity417,
&humidity418,
&humidity419,
&humidity420,
&humidity421,
&humidity422,
&humidity423,
&humidity424,
&humidity425,
&humidity426,
&humidity427,
&humidity428,
&humidity429,
&humidity430,
&humidity431,
&humidity432,
&humidity433,
&humidity434,
&humidity435,
&humidity436,
&humidity437,
&humidity438,
&humidity439,
&humidity440,
&humidity441,
&humidity442,
&humidity443,
&humidity444,
&humidity445,
&humidity446,
&humidity447,
&humidity448,
&humidity449,
&humidity450,
&humidity451,
&humidity452,
&humidity453,
&humidity454,
&humidity455,
&humidity456,
&humidity457,
&humidity458,
&humidity459,
&humidity460,
&humidity461,
&humidity462,
&humidity463,
&humidity464,
&humidity465,
&humidity466,
&humidity467,
&humidity468,
&humidity469,
&humidity470,
&humidity471,
&humidity472,
&humidity473,
&humidity474,
&humidity475,
&humidity476,
&humidity477,
&humidity478,
&humidity479,
&humidity480,
&humidity481,
&humidity482,
&humidity483,
&humidity484,
&humidity485,
&humidity486,
&humidity487,
&humidity488,
&humidity489,
&humidity490,
&humidity491,
&humidity492,
&humidity493,
&humidity494,
&humidity495,
&humidity496,
&humidity497,
&humidity498,
&humidity499,
&humidity500,
&humidity501,
&humidity502,
&humidity503,
&humidity504,
&humidity505,
&humidity506,
&humidity507,
&humidity508,
&humidity509,
&humidity510,
&humidity511,
&humidity512,
&humidity513,
&humidity514,
&humidity515,
&humidity516,
&humidity517,
&humidity518,
&humidity519,
&humidity520,
&humidity521,
&humidity522,
&humidity523,
&humidity524,
&humidity525,
&humidity526,
&humidity527,
&humidity528,
&humidity529,
&humidity530,
&humidity531,
&humidity532,
&humidity533,
&humidity534,
&humidity535,
&humidity536,
&humidity537,
&humidity538,
&humidity539,
&humidity540,
&humidity541,
&humidity542,
&humidity543,
&humidity544,
&humidity545,
&humidity546,
&humidity547,
&humidity548,
&humidity549,
&humidity550,
&humidity551,
&humidity552,
&humidity553,
&humidity554,
&humidity555,
&humidity556,
&humidity557,
&humidity558,
&humidity559,
&humidity560,
&humidity561,
&humidity562,
&humidity563,
&humidity564,
&humidity565,
&humidity566,
&humidity567,
&humidity568,
&humidity569,
&humidity570,
&humidity571,
&humidity572,
&humidity573,
&humidity574,
&humidity575,
&humidity576,
&humidity577,
&humidity578,
&humidity579,
&humidity580,
&humidity581,
&humidity582,
&humidity583,
&humidity584,
&humidity585,
&humidity586,
&humidity587,
&humidity588,
&humidity589,
&humidity590,
&humidity591,
&humidity592,
&humidity593,
&humidity594,
&humidity595,
&humidity596,
&humidity597,
&humidity598,
&humidity599,
&humidity600,
&humidity601,
&humidity602,
&humidity603,
&humidity604,
&humidity605,
&humidity606,
&humidity607,
&humidity608,
&humidity609,
&humidity610,
&humidity611,
&humidity612,
&humidity613,
&humidity614,
&humidity615,
&humidity616,
&humidity617,
&humidity618,
&humidity619,
&humidity620,
&humidity621,
&humidity622,
&humidity623,
&humidity624,
&humidity625,
&humidity626,
&humidity627,
&humidity628,
&humidity629,
&humidity630,
&humidity631,
&humidity632,
&humidity633,
&humidity634,
&humidity635,
&humidity636,
&humidity637,
&humidity638,
&humidity639,
&humidity640,
&humidity641,
&humidity642,
&humidity643,
&humidity644,
&humidity645,
&humidity646,
&humidity647,
&humidity648,
&humidity649,
&humidity650,
&humidity651,
&humidity652,
&humidity653,
&humidity654,
&humidity655,
&humidity656,
&humidity657,
&humidity658,
&humidity659,
&humidity660,
&humidity661,
&humidity662,
&humidity663,
&humidity664,
&humidity665,
&humidity666,
&humidity667,
&humidity668,
&humidity669,
&humidity670,
&humidity671,
&humidity672,
&humidity673,
&humidity674,
&humidity675,
&humidity676,
&humidity677,
&humidity678,
&humidity679,
&humidity680,
&humidity681,
&humidity682,
&humidity683,
&humidity684,
&humidity685,
&humidity686,
&humidity687,
&humidity688,
&humidity689,
&humidity690,
&humidity691,
&humidity692,
&humidity693,
&humidity694,
&humidity695,
&humidity696,
&humidity697,
&humidity698,
&humidity699
};

#endif
