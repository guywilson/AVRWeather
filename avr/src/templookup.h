#include <avr/pgmspace.h>

#include "types.h"

#ifndef _INCL_TEMPLOOKUP
#define _INCL_TEMPLOOKUP

#define TEMP_LOOKUP_BUFFER_SIZE			 532

#define ADC_TEMP_OFFSET					  51

#define ADC_TEMP_MIN					   0
#define ADC_TEMP_MAX					 531

/******************************************************************************
**
** From an ADC input linked to an Analogue Devices AD22100 temperature sensor
** with a range of -50C to 150C. The sensor output is 0.25v to 4.75v but we
** are only interested in the range -50C to 65C (The highest temperate ever
** recorded on earth is 56.7C in Death Valley, California) so that yields a
** voltage range of 0.25v to 2.84v.
**
** The transfer function from C to V for the sensor is:
**     V = 1.375 + (0.0225 * C)
**
**     e.g. for -50C, V = 1.375 + (0.0225 * -50) = 0.25v
**
** Given that the ADC input range is 0v - 5v equating to 0 - 1023 (10-bit)
** then re-arranging to get C from the ADC value, we use:
**     C = (((ADC / 1023) * 5) - 1.375) / 0.0225
**
** This is an expensive operation on a microcontroller, hence we calcuate this 
** upfront and store in flash ROM.
**
** This array of const values uses the PROGMEM modifier, a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array, code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/
const decimal24_t temp0 PROGMEM = populate_decimal(-50, 24);
const decimal24_t temp1 PROGMEM = populate_decimal(-50, 3);
const decimal24_t temp2 PROGMEM = populate_decimal(-49, 81);
const decimal24_t temp3 PROGMEM = populate_decimal(-49, 59);
const decimal24_t temp4 PROGMEM = populate_decimal(-49, 38);
const decimal24_t temp5 PROGMEM = populate_decimal(-49, 16);
const decimal24_t temp6 PROGMEM = populate_decimal(-48, 94);
const decimal24_t temp7 PROGMEM = populate_decimal(-48, 72);
const decimal24_t temp8 PROGMEM = populate_decimal(-48, 51);
const decimal24_t temp9 PROGMEM = populate_decimal(-48, 29);
const decimal24_t temp10 PROGMEM = populate_decimal(-48, 7);
const decimal24_t temp11 PROGMEM = populate_decimal(-47, 86);
const decimal24_t temp12 PROGMEM = populate_decimal(-47, 64);
const decimal24_t temp13 PROGMEM = populate_decimal(-47, 42);
const decimal24_t temp14 PROGMEM = populate_decimal(-47, 20);
const decimal24_t temp15 PROGMEM = populate_decimal(-46, 99);
const decimal24_t temp16 PROGMEM = populate_decimal(-46, 77);
const decimal24_t temp17 PROGMEM = populate_decimal(-46, 55);
const decimal24_t temp18 PROGMEM = populate_decimal(-46, 33);
const decimal24_t temp19 PROGMEM = populate_decimal(-46, 12);
const decimal24_t temp20 PROGMEM = populate_decimal(-45, 90);
const decimal24_t temp21 PROGMEM = populate_decimal(-45, 68);
const decimal24_t temp22 PROGMEM = populate_decimal(-45, 47);
const decimal24_t temp23 PROGMEM = populate_decimal(-45, 25);
const decimal24_t temp24 PROGMEM = populate_decimal(-45, 3);
const decimal24_t temp25 PROGMEM = populate_decimal(-44, 81);
const decimal24_t temp26 PROGMEM = populate_decimal(-44, 60);
const decimal24_t temp27 PROGMEM = populate_decimal(-44, 38);
const decimal24_t temp28 PROGMEM = populate_decimal(-44, 16);
const decimal24_t temp29 PROGMEM = populate_decimal(-43, 95);
const decimal24_t temp30 PROGMEM = populate_decimal(-43, 73);
const decimal24_t temp31 PROGMEM = populate_decimal(-43, 51);
const decimal24_t temp32 PROGMEM = populate_decimal(-43, 29);
const decimal24_t temp33 PROGMEM = populate_decimal(-43, 8);
const decimal24_t temp34 PROGMEM = populate_decimal(-42, 86);
const decimal24_t temp35 PROGMEM = populate_decimal(-42, 64);
const decimal24_t temp36 PROGMEM = populate_decimal(-42, 42);
const decimal24_t temp37 PROGMEM = populate_decimal(-42, 21);
const decimal24_t temp38 PROGMEM = populate_decimal(-41, 99);
const decimal24_t temp39 PROGMEM = populate_decimal(-41, 77);
const decimal24_t temp40 PROGMEM = populate_decimal(-41, 56);
const decimal24_t temp41 PROGMEM = populate_decimal(-41, 34);
const decimal24_t temp42 PROGMEM = populate_decimal(-41, 12);
const decimal24_t temp43 PROGMEM = populate_decimal(-40, 90);
const decimal24_t temp44 PROGMEM = populate_decimal(-40, 69);
const decimal24_t temp45 PROGMEM = populate_decimal(-40, 47);
const decimal24_t temp46 PROGMEM = populate_decimal(-40, 25);
const decimal24_t temp47 PROGMEM = populate_decimal(-40, 4);
const decimal24_t temp48 PROGMEM = populate_decimal(-39, 82);
const decimal24_t temp49 PROGMEM = populate_decimal(-39, 60);
const decimal24_t temp50 PROGMEM = populate_decimal(-39, 38);
const decimal24_t temp51 PROGMEM = populate_decimal(-39, 17);
const decimal24_t temp52 PROGMEM = populate_decimal(-38, 95);
const decimal24_t temp53 PROGMEM = populate_decimal(-38, 73);
const decimal24_t temp54 PROGMEM = populate_decimal(-38, 51);
const decimal24_t temp55 PROGMEM = populate_decimal(-38, 30);
const decimal24_t temp56 PROGMEM = populate_decimal(-38, 8);
const decimal24_t temp57 PROGMEM = populate_decimal(-37, 86);
const decimal24_t temp58 PROGMEM = populate_decimal(-37, 65);
const decimal24_t temp59 PROGMEM = populate_decimal(-37, 43);
const decimal24_t temp60 PROGMEM = populate_decimal(-37, 21);
const decimal24_t temp61 PROGMEM = populate_decimal(-36, 99);
const decimal24_t temp62 PROGMEM = populate_decimal(-36, 78);
const decimal24_t temp63 PROGMEM = populate_decimal(-36, 56);
const decimal24_t temp64 PROGMEM = populate_decimal(-36, 34);
const decimal24_t temp65 PROGMEM = populate_decimal(-36, 13);
const decimal24_t temp66 PROGMEM = populate_decimal(-35, 91);
const decimal24_t temp67 PROGMEM = populate_decimal(-35, 69);
const decimal24_t temp68 PROGMEM = populate_decimal(-35, 47);
const decimal24_t temp69 PROGMEM = populate_decimal(-35, 26);
const decimal24_t temp70 PROGMEM = populate_decimal(-35, 4);
const decimal24_t temp71 PROGMEM = populate_decimal(-34, 82);
const decimal24_t temp72 PROGMEM = populate_decimal(-34, 60);
const decimal24_t temp73 PROGMEM = populate_decimal(-34, 39);
const decimal24_t temp74 PROGMEM = populate_decimal(-34, 17);
const decimal24_t temp75 PROGMEM = populate_decimal(-33, 95);
const decimal24_t temp76 PROGMEM = populate_decimal(-33, 74);
const decimal24_t temp77 PROGMEM = populate_decimal(-33, 52);
const decimal24_t temp78 PROGMEM = populate_decimal(-33, 30);
const decimal24_t temp79 PROGMEM = populate_decimal(-33, 8);
const decimal24_t temp80 PROGMEM = populate_decimal(-32, 87);
const decimal24_t temp81 PROGMEM = populate_decimal(-32, 65);
const decimal24_t temp82 PROGMEM = populate_decimal(-32, 43);
const decimal24_t temp83 PROGMEM = populate_decimal(-32, 22);
const decimal24_t temp84 PROGMEM = populate_decimal(-32, 0);
const decimal24_t temp85 PROGMEM = populate_decimal(-31, 78);
const decimal24_t temp86 PROGMEM = populate_decimal(-31, 56);
const decimal24_t temp87 PROGMEM = populate_decimal(-31, 35);
const decimal24_t temp88 PROGMEM = populate_decimal(-31, 13);
const decimal24_t temp89 PROGMEM = populate_decimal(-30, 91);
const decimal24_t temp90 PROGMEM = populate_decimal(-30, 69);
const decimal24_t temp91 PROGMEM = populate_decimal(-30, 48);
const decimal24_t temp92 PROGMEM = populate_decimal(-30, 26);
const decimal24_t temp93 PROGMEM = populate_decimal(-30, 4);
const decimal24_t temp94 PROGMEM = populate_decimal(-29, 83);
const decimal24_t temp95 PROGMEM = populate_decimal(-29, 61);
const decimal24_t temp96 PROGMEM = populate_decimal(-29, 39);
const decimal24_t temp97 PROGMEM = populate_decimal(-29, 17);
const decimal24_t temp98 PROGMEM = populate_decimal(-28, 96);
const decimal24_t temp99 PROGMEM = populate_decimal(-28, 74);
const decimal24_t temp100 PROGMEM = populate_decimal(-28, 52);
const decimal24_t temp101 PROGMEM = populate_decimal(-28, 30);
const decimal24_t temp102 PROGMEM = populate_decimal(-28, 9);
const decimal24_t temp103 PROGMEM = populate_decimal(-27, 87);
const decimal24_t temp104 PROGMEM = populate_decimal(-27, 65);
const decimal24_t temp105 PROGMEM = populate_decimal(-27, 44);
const decimal24_t temp106 PROGMEM = populate_decimal(-27, 22);
const decimal24_t temp107 PROGMEM = populate_decimal(-27, 0);
const decimal24_t temp108 PROGMEM = populate_decimal(-26, 78);
const decimal24_t temp109 PROGMEM = populate_decimal(-26, 57);
const decimal24_t temp110 PROGMEM = populate_decimal(-26, 35);
const decimal24_t temp111 PROGMEM = populate_decimal(-26, 13);
const decimal24_t temp112 PROGMEM = populate_decimal(-25, 92);
const decimal24_t temp113 PROGMEM = populate_decimal(-25, 70);
const decimal24_t temp114 PROGMEM = populate_decimal(-25, 48);
const decimal24_t temp115 PROGMEM = populate_decimal(-25, 26);
const decimal24_t temp116 PROGMEM = populate_decimal(-25, 5);
const decimal24_t temp117 PROGMEM = populate_decimal(-24, 83);
const decimal24_t temp118 PROGMEM = populate_decimal(-24, 61);
const decimal24_t temp119 PROGMEM = populate_decimal(-24, 39);
const decimal24_t temp120 PROGMEM = populate_decimal(-24, 18);
const decimal24_t temp121 PROGMEM = populate_decimal(-23, 96);
const decimal24_t temp122 PROGMEM = populate_decimal(-23, 74);
const decimal24_t temp123 PROGMEM = populate_decimal(-23, 53);
const decimal24_t temp124 PROGMEM = populate_decimal(-23, 31);
const decimal24_t temp125 PROGMEM = populate_decimal(-23, 9);
const decimal24_t temp126 PROGMEM = populate_decimal(-22, 87);
const decimal24_t temp127 PROGMEM = populate_decimal(-22, 66);
const decimal24_t temp128 PROGMEM = populate_decimal(-22, 44);
const decimal24_t temp129 PROGMEM = populate_decimal(-22, 22);
const decimal24_t temp130 PROGMEM = populate_decimal(-22, 1);
const decimal24_t temp131 PROGMEM = populate_decimal(-21, 79);
const decimal24_t temp132 PROGMEM = populate_decimal(-21, 57);
const decimal24_t temp133 PROGMEM = populate_decimal(-21, 35);
const decimal24_t temp134 PROGMEM = populate_decimal(-21, 14);
const decimal24_t temp135 PROGMEM = populate_decimal(-20, 92);
const decimal24_t temp136 PROGMEM = populate_decimal(-20, 70);
const decimal24_t temp137 PROGMEM = populate_decimal(-20, 48);
const decimal24_t temp138 PROGMEM = populate_decimal(-20, 27);
const decimal24_t temp139 PROGMEM = populate_decimal(-20, 5);
const decimal24_t temp140 PROGMEM = populate_decimal(-19, 83);
const decimal24_t temp141 PROGMEM = populate_decimal(-19, 62);
const decimal24_t temp142 PROGMEM = populate_decimal(-19, 40);
const decimal24_t temp143 PROGMEM = populate_decimal(-19, 18);
const decimal24_t temp144 PROGMEM = populate_decimal(-18, 96);
const decimal24_t temp145 PROGMEM = populate_decimal(-18, 75);
const decimal24_t temp146 PROGMEM = populate_decimal(-18, 53);
const decimal24_t temp147 PROGMEM = populate_decimal(-18, 31);
const decimal24_t temp148 PROGMEM = populate_decimal(-18, 10);
const decimal24_t temp149 PROGMEM = populate_decimal(-17, 88);
const decimal24_t temp150 PROGMEM = populate_decimal(-17, 66);
const decimal24_t temp151 PROGMEM = populate_decimal(-17, 44);
const decimal24_t temp152 PROGMEM = populate_decimal(-17, 23);
const decimal24_t temp153 PROGMEM = populate_decimal(-17, 1);
const decimal24_t temp154 PROGMEM = populate_decimal(-16, 79);
const decimal24_t temp155 PROGMEM = populate_decimal(-16, 57);
const decimal24_t temp156 PROGMEM = populate_decimal(-16, 36);
const decimal24_t temp157 PROGMEM = populate_decimal(-16, 14);
const decimal24_t temp158 PROGMEM = populate_decimal(-15, 92);
const decimal24_t temp159 PROGMEM = populate_decimal(-15, 71);
const decimal24_t temp160 PROGMEM = populate_decimal(-15, 49);
const decimal24_t temp161 PROGMEM = populate_decimal(-15, 27);
const decimal24_t temp162 PROGMEM = populate_decimal(-15, 5);
const decimal24_t temp163 PROGMEM = populate_decimal(-14, 84);
const decimal24_t temp164 PROGMEM = populate_decimal(-14, 62);
const decimal24_t temp165 PROGMEM = populate_decimal(-14, 40);
const decimal24_t temp166 PROGMEM = populate_decimal(-14, 19);
const decimal24_t temp167 PROGMEM = populate_decimal(-13, 97);
const decimal24_t temp168 PROGMEM = populate_decimal(-13, 75);
const decimal24_t temp169 PROGMEM = populate_decimal(-13, 53);
const decimal24_t temp170 PROGMEM = populate_decimal(-13, 32);
const decimal24_t temp171 PROGMEM = populate_decimal(-13, 10);
const decimal24_t temp172 PROGMEM = populate_decimal(-12, 88);
const decimal24_t temp173 PROGMEM = populate_decimal(-12, 66);
const decimal24_t temp174 PROGMEM = populate_decimal(-12, 45);
const decimal24_t temp175 PROGMEM = populate_decimal(-12, 23);
const decimal24_t temp176 PROGMEM = populate_decimal(-12, 1);
const decimal24_t temp177 PROGMEM = populate_decimal(-11, 80);
const decimal24_t temp178 PROGMEM = populate_decimal(-11, 58);
const decimal24_t temp179 PROGMEM = populate_decimal(-11, 36);
const decimal24_t temp180 PROGMEM = populate_decimal(-11, 14);
const decimal24_t temp181 PROGMEM = populate_decimal(-10, 93);
const decimal24_t temp182 PROGMEM = populate_decimal(-10, 71);
const decimal24_t temp183 PROGMEM = populate_decimal(-10, 49);
const decimal24_t temp184 PROGMEM = populate_decimal(-10, 28);
const decimal24_t temp185 PROGMEM = populate_decimal(-10, 6);
const decimal24_t temp186 PROGMEM = populate_decimal(-9, 84);
const decimal24_t temp187 PROGMEM = populate_decimal(-9, 62);
const decimal24_t temp188 PROGMEM = populate_decimal(-9, 41);
const decimal24_t temp189 PROGMEM = populate_decimal(-9, 19);
const decimal24_t temp190 PROGMEM = populate_decimal(-8, 97);
const decimal24_t temp191 PROGMEM = populate_decimal(-8, 75);
const decimal24_t temp192 PROGMEM = populate_decimal(-8, 54);
const decimal24_t temp193 PROGMEM = populate_decimal(-8, 32);
const decimal24_t temp194 PROGMEM = populate_decimal(-8, 10);
const decimal24_t temp195 PROGMEM = populate_decimal(-7, 89);
const decimal24_t temp196 PROGMEM = populate_decimal(-7, 67);
const decimal24_t temp197 PROGMEM = populate_decimal(-7, 45);
const decimal24_t temp198 PROGMEM = populate_decimal(-7, 23);
const decimal24_t temp199 PROGMEM = populate_decimal(-7, 2);
const decimal24_t temp200 PROGMEM = populate_decimal(-6, 80);
const decimal24_t temp201 PROGMEM = populate_decimal(-6, 58);
const decimal24_t temp202 PROGMEM = populate_decimal(-6, 37);
const decimal24_t temp203 PROGMEM = populate_decimal(-6, 15);
const decimal24_t temp204 PROGMEM = populate_decimal(-5, 93);
const decimal24_t temp205 PROGMEM = populate_decimal(-5, 71);
const decimal24_t temp206 PROGMEM = populate_decimal(-5, 50);
const decimal24_t temp207 PROGMEM = populate_decimal(-5, 28);
const decimal24_t temp208 PROGMEM = populate_decimal(-5, 6);
const decimal24_t temp209 PROGMEM = populate_decimal(-4, 84);
const decimal24_t temp210 PROGMEM = populate_decimal(-4, 63);
const decimal24_t temp211 PROGMEM = populate_decimal(-4, 41);
const decimal24_t temp212 PROGMEM = populate_decimal(-4, 19);
const decimal24_t temp213 PROGMEM = populate_decimal(-3, 98);
const decimal24_t temp214 PROGMEM = populate_decimal(-3, 76);
const decimal24_t temp215 PROGMEM = populate_decimal(-3, 54);
const decimal24_t temp216 PROGMEM = populate_decimal(-3, 32);
const decimal24_t temp217 PROGMEM = populate_decimal(-3, 11);
const decimal24_t temp218 PROGMEM = populate_decimal(-2, 89);
const decimal24_t temp219 PROGMEM = populate_decimal(-2, 67);
const decimal24_t temp220 PROGMEM = populate_decimal(-2, 46);
const decimal24_t temp221 PROGMEM = populate_decimal(-2, 24);
const decimal24_t temp222 PROGMEM = populate_decimal(-2, 2);
const decimal24_t temp223 PROGMEM = populate_decimal(-1, 80);
const decimal24_t temp224 PROGMEM = populate_decimal(-1, 59);
const decimal24_t temp225 PROGMEM = populate_decimal(-1, 37);
const decimal24_t temp226 PROGMEM = populate_decimal(-1, 15);
const decimal24_t temp227 PROGMEM = populate_decimal(0, 93);
const decimal24_t temp228 PROGMEM = populate_decimal(0, 72);
const decimal24_t temp229 PROGMEM = populate_decimal(0, 50);
const decimal24_t temp230 PROGMEM = populate_decimal(0, 28);
const decimal24_t temp231 PROGMEM = populate_decimal(0, 7);
const decimal24_t temp232 PROGMEM = populate_decimal(0, 14);
const decimal24_t temp233 PROGMEM = populate_decimal(0, 36);
const decimal24_t temp234 PROGMEM = populate_decimal(0, 58);
const decimal24_t temp235 PROGMEM = populate_decimal(0, 79);
const decimal24_t temp236 PROGMEM = populate_decimal(1, 1);
const decimal24_t temp237 PROGMEM = populate_decimal(1, 23);
const decimal24_t temp238 PROGMEM = populate_decimal(1, 44);
const decimal24_t temp239 PROGMEM = populate_decimal(1, 66);
const decimal24_t temp240 PROGMEM = populate_decimal(1, 88);
const decimal24_t temp241 PROGMEM = populate_decimal(2, 10);
const decimal24_t temp242 PROGMEM = populate_decimal(2, 31);
const decimal24_t temp243 PROGMEM = populate_decimal(2, 53);
const decimal24_t temp244 PROGMEM = populate_decimal(2, 75);
const decimal24_t temp245 PROGMEM = populate_decimal(2, 97);
const decimal24_t temp246 PROGMEM = populate_decimal(3, 18);
const decimal24_t temp247 PROGMEM = populate_decimal(3, 40);
const decimal24_t temp248 PROGMEM = populate_decimal(3, 62);
const decimal24_t temp249 PROGMEM = populate_decimal(3, 83);
const decimal24_t temp250 PROGMEM = populate_decimal(4, 5);
const decimal24_t temp251 PROGMEM = populate_decimal(4, 27);
const decimal24_t temp252 PROGMEM = populate_decimal(4, 49);
const decimal24_t temp253 PROGMEM = populate_decimal(4, 70);
const decimal24_t temp254 PROGMEM = populate_decimal(4, 92);
const decimal24_t temp255 PROGMEM = populate_decimal(5, 14);
const decimal24_t temp256 PROGMEM = populate_decimal(5, 36);
const decimal24_t temp257 PROGMEM = populate_decimal(5, 57);
const decimal24_t temp258 PROGMEM = populate_decimal(5, 79);
const decimal24_t temp259 PROGMEM = populate_decimal(6, 1);
const decimal24_t temp260 PROGMEM = populate_decimal(6, 22);
const decimal24_t temp261 PROGMEM = populate_decimal(6, 44);
const decimal24_t temp262 PROGMEM = populate_decimal(6, 66);
const decimal24_t temp263 PROGMEM = populate_decimal(6, 88);
const decimal24_t temp264 PROGMEM = populate_decimal(7, 9);
const decimal24_t temp265 PROGMEM = populate_decimal(7, 31);
const decimal24_t temp266 PROGMEM = populate_decimal(7, 53);
const decimal24_t temp267 PROGMEM = populate_decimal(7, 74);
const decimal24_t temp268 PROGMEM = populate_decimal(7, 96);
const decimal24_t temp269 PROGMEM = populate_decimal(8, 18);
const decimal24_t temp270 PROGMEM = populate_decimal(8, 40);
const decimal24_t temp271 PROGMEM = populate_decimal(8, 61);
const decimal24_t temp272 PROGMEM = populate_decimal(8, 83);
const decimal24_t temp273 PROGMEM = populate_decimal(9, 5);
const decimal24_t temp274 PROGMEM = populate_decimal(9, 27);
const decimal24_t temp275 PROGMEM = populate_decimal(9, 48);
const decimal24_t temp276 PROGMEM = populate_decimal(9, 70);
const decimal24_t temp277 PROGMEM = populate_decimal(9, 92);
const decimal24_t temp278 PROGMEM = populate_decimal(10, 13);
const decimal24_t temp279 PROGMEM = populate_decimal(10, 35);
const decimal24_t temp280 PROGMEM = populate_decimal(10, 57);
const decimal24_t temp281 PROGMEM = populate_decimal(10, 79);
const decimal24_t temp282 PROGMEM = populate_decimal(11, 0);
const decimal24_t temp283 PROGMEM = populate_decimal(11, 22);
const decimal24_t temp284 PROGMEM = populate_decimal(11, 44);
const decimal24_t temp285 PROGMEM = populate_decimal(11, 65);
const decimal24_t temp286 PROGMEM = populate_decimal(11, 87);
const decimal24_t temp287 PROGMEM = populate_decimal(12, 9);
const decimal24_t temp288 PROGMEM = populate_decimal(12, 31);
const decimal24_t temp289 PROGMEM = populate_decimal(12, 52);
const decimal24_t temp290 PROGMEM = populate_decimal(12, 74);
const decimal24_t temp291 PROGMEM = populate_decimal(12, 96);
const decimal24_t temp292 PROGMEM = populate_decimal(13, 18);
const decimal24_t temp293 PROGMEM = populate_decimal(13, 39);
const decimal24_t temp294 PROGMEM = populate_decimal(13, 61);
const decimal24_t temp295 PROGMEM = populate_decimal(13, 83);
const decimal24_t temp296 PROGMEM = populate_decimal(14, 4);
const decimal24_t temp297 PROGMEM = populate_decimal(14, 26);
const decimal24_t temp298 PROGMEM = populate_decimal(14, 48);
const decimal24_t temp299 PROGMEM = populate_decimal(14, 70);
const decimal24_t temp300 PROGMEM = populate_decimal(14, 91);
const decimal24_t temp301 PROGMEM = populate_decimal(15, 13);
const decimal24_t temp302 PROGMEM = populate_decimal(15, 35);
const decimal24_t temp303 PROGMEM = populate_decimal(15, 56);
const decimal24_t temp304 PROGMEM = populate_decimal(15, 78);
const decimal24_t temp305 PROGMEM = populate_decimal(16, 0);
const decimal24_t temp306 PROGMEM = populate_decimal(16, 22);
const decimal24_t temp307 PROGMEM = populate_decimal(16, 43);
const decimal24_t temp308 PROGMEM = populate_decimal(16, 65);
const decimal24_t temp309 PROGMEM = populate_decimal(16, 87);
const decimal24_t temp310 PROGMEM = populate_decimal(17, 9);
const decimal24_t temp311 PROGMEM = populate_decimal(17, 30);
const decimal24_t temp312 PROGMEM = populate_decimal(17, 52);
const decimal24_t temp313 PROGMEM = populate_decimal(17, 74);
const decimal24_t temp314 PROGMEM = populate_decimal(17, 95);
const decimal24_t temp315 PROGMEM = populate_decimal(18, 17);
const decimal24_t temp316 PROGMEM = populate_decimal(18, 39);
const decimal24_t temp317 PROGMEM = populate_decimal(18, 61);
const decimal24_t temp318 PROGMEM = populate_decimal(18, 82);
const decimal24_t temp319 PROGMEM = populate_decimal(19, 4);
const decimal24_t temp320 PROGMEM = populate_decimal(19, 26);
const decimal24_t temp321 PROGMEM = populate_decimal(19, 47);
const decimal24_t temp322 PROGMEM = populate_decimal(19, 69);
const decimal24_t temp323 PROGMEM = populate_decimal(19, 91);
const decimal24_t temp324 PROGMEM = populate_decimal(20, 13);
const decimal24_t temp325 PROGMEM = populate_decimal(20, 34);
const decimal24_t temp326 PROGMEM = populate_decimal(20, 56);
const decimal24_t temp327 PROGMEM = populate_decimal(20, 78);
const decimal24_t temp328 PROGMEM = populate_decimal(21, 0);
const decimal24_t temp329 PROGMEM = populate_decimal(21, 21);
const decimal24_t temp330 PROGMEM = populate_decimal(21, 43);
const decimal24_t temp331 PROGMEM = populate_decimal(21, 65);
const decimal24_t temp332 PROGMEM = populate_decimal(21, 86);
const decimal24_t temp333 PROGMEM = populate_decimal(22, 8);
const decimal24_t temp334 PROGMEM = populate_decimal(22, 30);
const decimal24_t temp335 PROGMEM = populate_decimal(22, 52);
const decimal24_t temp336 PROGMEM = populate_decimal(22, 73);
const decimal24_t temp337 PROGMEM = populate_decimal(22, 95);
const decimal24_t temp338 PROGMEM = populate_decimal(23, 17);
const decimal24_t temp339 PROGMEM = populate_decimal(23, 38);
const decimal24_t temp340 PROGMEM = populate_decimal(23, 60);
const decimal24_t temp341 PROGMEM = populate_decimal(23, 82);
const decimal24_t temp342 PROGMEM = populate_decimal(24, 4);
const decimal24_t temp343 PROGMEM = populate_decimal(24, 25);
const decimal24_t temp344 PROGMEM = populate_decimal(24, 47);
const decimal24_t temp345 PROGMEM = populate_decimal(24, 69);
const decimal24_t temp346 PROGMEM = populate_decimal(24, 91);
const decimal24_t temp347 PROGMEM = populate_decimal(25, 12);
const decimal24_t temp348 PROGMEM = populate_decimal(25, 34);
const decimal24_t temp349 PROGMEM = populate_decimal(25, 56);
const decimal24_t temp350 PROGMEM = populate_decimal(25, 77);
const decimal24_t temp351 PROGMEM = populate_decimal(25, 99);
const decimal24_t temp352 PROGMEM = populate_decimal(26, 21);
const decimal24_t temp353 PROGMEM = populate_decimal(26, 43);
const decimal24_t temp354 PROGMEM = populate_decimal(26, 64);
const decimal24_t temp355 PROGMEM = populate_decimal(26, 86);
const decimal24_t temp356 PROGMEM = populate_decimal(27, 8);
const decimal24_t temp357 PROGMEM = populate_decimal(27, 29);
const decimal24_t temp358 PROGMEM = populate_decimal(27, 51);
const decimal24_t temp359 PROGMEM = populate_decimal(27, 73);
const decimal24_t temp360 PROGMEM = populate_decimal(27, 95);
const decimal24_t temp361 PROGMEM = populate_decimal(28, 16);
const decimal24_t temp362 PROGMEM = populate_decimal(28, 38);
const decimal24_t temp363 PROGMEM = populate_decimal(28, 60);
const decimal24_t temp364 PROGMEM = populate_decimal(28, 82);
const decimal24_t temp365 PROGMEM = populate_decimal(29, 3);
const decimal24_t temp366 PROGMEM = populate_decimal(29, 25);
const decimal24_t temp367 PROGMEM = populate_decimal(29, 47);
const decimal24_t temp368 PROGMEM = populate_decimal(29, 68);
const decimal24_t temp369 PROGMEM = populate_decimal(29, 90);
const decimal24_t temp370 PROGMEM = populate_decimal(30, 12);
const decimal24_t temp371 PROGMEM = populate_decimal(30, 34);
const decimal24_t temp372 PROGMEM = populate_decimal(30, 55);
const decimal24_t temp373 PROGMEM = populate_decimal(30, 77);
const decimal24_t temp374 PROGMEM = populate_decimal(30, 99);
const decimal24_t temp375 PROGMEM = populate_decimal(31, 20);
const decimal24_t temp376 PROGMEM = populate_decimal(31, 42);
const decimal24_t temp377 PROGMEM = populate_decimal(31, 64);
const decimal24_t temp378 PROGMEM = populate_decimal(31, 86);
const decimal24_t temp379 PROGMEM = populate_decimal(32, 7);
const decimal24_t temp380 PROGMEM = populate_decimal(32, 29);
const decimal24_t temp381 PROGMEM = populate_decimal(32, 51);
const decimal24_t temp382 PROGMEM = populate_decimal(32, 73);
const decimal24_t temp383 PROGMEM = populate_decimal(32, 94);
const decimal24_t temp384 PROGMEM = populate_decimal(33, 16);
const decimal24_t temp385 PROGMEM = populate_decimal(33, 38);
const decimal24_t temp386 PROGMEM = populate_decimal(33, 59);
const decimal24_t temp387 PROGMEM = populate_decimal(33, 81);
const decimal24_t temp388 PROGMEM = populate_decimal(34, 3);
const decimal24_t temp389 PROGMEM = populate_decimal(34, 25);
const decimal24_t temp390 PROGMEM = populate_decimal(34, 46);
const decimal24_t temp391 PROGMEM = populate_decimal(34, 68);
const decimal24_t temp392 PROGMEM = populate_decimal(34, 90);
const decimal24_t temp393 PROGMEM = populate_decimal(35, 12);
const decimal24_t temp394 PROGMEM = populate_decimal(35, 33);
const decimal24_t temp395 PROGMEM = populate_decimal(35, 55);
const decimal24_t temp396 PROGMEM = populate_decimal(35, 77);
const decimal24_t temp397 PROGMEM = populate_decimal(35, 98);
const decimal24_t temp398 PROGMEM = populate_decimal(36, 20);
const decimal24_t temp399 PROGMEM = populate_decimal(36, 42);
const decimal24_t temp400 PROGMEM = populate_decimal(36, 64);
const decimal24_t temp401 PROGMEM = populate_decimal(36, 85);
const decimal24_t temp402 PROGMEM = populate_decimal(37, 7);
const decimal24_t temp403 PROGMEM = populate_decimal(37, 29);
const decimal24_t temp404 PROGMEM = populate_decimal(37, 50);
const decimal24_t temp405 PROGMEM = populate_decimal(37, 72);
const decimal24_t temp406 PROGMEM = populate_decimal(37, 94);
const decimal24_t temp407 PROGMEM = populate_decimal(38, 16);
const decimal24_t temp408 PROGMEM = populate_decimal(38, 37);
const decimal24_t temp409 PROGMEM = populate_decimal(38, 59);
const decimal24_t temp410 PROGMEM = populate_decimal(38, 81);
const decimal24_t temp411 PROGMEM = populate_decimal(39, 3);
const decimal24_t temp412 PROGMEM = populate_decimal(39, 24);
const decimal24_t temp413 PROGMEM = populate_decimal(39, 46);
const decimal24_t temp414 PROGMEM = populate_decimal(39, 68);
const decimal24_t temp415 PROGMEM = populate_decimal(39, 89);
const decimal24_t temp416 PROGMEM = populate_decimal(40, 11);
const decimal24_t temp417 PROGMEM = populate_decimal(40, 33);
const decimal24_t temp418 PROGMEM = populate_decimal(40, 55);
const decimal24_t temp419 PROGMEM = populate_decimal(40, 76);
const decimal24_t temp420 PROGMEM = populate_decimal(40, 98);
const decimal24_t temp421 PROGMEM = populate_decimal(41, 20);
const decimal24_t temp422 PROGMEM = populate_decimal(41, 41);
const decimal24_t temp423 PROGMEM = populate_decimal(41, 63);
const decimal24_t temp424 PROGMEM = populate_decimal(41, 85);
const decimal24_t temp425 PROGMEM = populate_decimal(42, 7);
const decimal24_t temp426 PROGMEM = populate_decimal(42, 28);
const decimal24_t temp427 PROGMEM = populate_decimal(42, 50);
const decimal24_t temp428 PROGMEM = populate_decimal(42, 72);
const decimal24_t temp429 PROGMEM = populate_decimal(42, 94);
const decimal24_t temp430 PROGMEM = populate_decimal(43, 15);
const decimal24_t temp431 PROGMEM = populate_decimal(43, 37);
const decimal24_t temp432 PROGMEM = populate_decimal(43, 59);
const decimal24_t temp433 PROGMEM = populate_decimal(43, 80);
const decimal24_t temp434 PROGMEM = populate_decimal(44, 2);
const decimal24_t temp435 PROGMEM = populate_decimal(44, 24);
const decimal24_t temp436 PROGMEM = populate_decimal(44, 46);
const decimal24_t temp437 PROGMEM = populate_decimal(44, 67);
const decimal24_t temp438 PROGMEM = populate_decimal(44, 89);
const decimal24_t temp439 PROGMEM = populate_decimal(45, 11);
const decimal24_t temp440 PROGMEM = populate_decimal(45, 32);
const decimal24_t temp441 PROGMEM = populate_decimal(45, 54);
const decimal24_t temp442 PROGMEM = populate_decimal(45, 76);
const decimal24_t temp443 PROGMEM = populate_decimal(45, 98);
const decimal24_t temp444 PROGMEM = populate_decimal(46, 19);
const decimal24_t temp445 PROGMEM = populate_decimal(46, 41);
const decimal24_t temp446 PROGMEM = populate_decimal(46, 63);
const decimal24_t temp447 PROGMEM = populate_decimal(46, 85);
const decimal24_t temp448 PROGMEM = populate_decimal(47, 6);
const decimal24_t temp449 PROGMEM = populate_decimal(47, 28);
const decimal24_t temp450 PROGMEM = populate_decimal(47, 50);
const decimal24_t temp451 PROGMEM = populate_decimal(47, 71);
const decimal24_t temp452 PROGMEM = populate_decimal(47, 93);
const decimal24_t temp453 PROGMEM = populate_decimal(48, 15);
const decimal24_t temp454 PROGMEM = populate_decimal(48, 37);
const decimal24_t temp455 PROGMEM = populate_decimal(48, 58);
const decimal24_t temp456 PROGMEM = populate_decimal(48, 80);
const decimal24_t temp457 PROGMEM = populate_decimal(49, 2);
const decimal24_t temp458 PROGMEM = populate_decimal(49, 23);
const decimal24_t temp459 PROGMEM = populate_decimal(49, 45);
const decimal24_t temp460 PROGMEM = populate_decimal(49, 67);
const decimal24_t temp461 PROGMEM = populate_decimal(49, 89);
const decimal24_t temp462 PROGMEM = populate_decimal(50, 10);
const decimal24_t temp463 PROGMEM = populate_decimal(50, 32);
const decimal24_t temp464 PROGMEM = populate_decimal(50, 54);
const decimal24_t temp465 PROGMEM = populate_decimal(50, 76);
const decimal24_t temp466 PROGMEM = populate_decimal(50, 97);
const decimal24_t temp467 PROGMEM = populate_decimal(51, 19);
const decimal24_t temp468 PROGMEM = populate_decimal(51, 41);
const decimal24_t temp469 PROGMEM = populate_decimal(51, 62);
const decimal24_t temp470 PROGMEM = populate_decimal(51, 84);
const decimal24_t temp471 PROGMEM = populate_decimal(52, 6);
const decimal24_t temp472 PROGMEM = populate_decimal(52, 28);
const decimal24_t temp473 PROGMEM = populate_decimal(52, 49);
const decimal24_t temp474 PROGMEM = populate_decimal(52, 71);
const decimal24_t temp475 PROGMEM = populate_decimal(52, 93);
const decimal24_t temp476 PROGMEM = populate_decimal(53, 14);
const decimal24_t temp477 PROGMEM = populate_decimal(53, 36);
const decimal24_t temp478 PROGMEM = populate_decimal(53, 58);
const decimal24_t temp479 PROGMEM = populate_decimal(53, 80);
const decimal24_t temp480 PROGMEM = populate_decimal(54, 1);
const decimal24_t temp481 PROGMEM = populate_decimal(54, 23);
const decimal24_t temp482 PROGMEM = populate_decimal(54, 45);
const decimal24_t temp483 PROGMEM = populate_decimal(54, 67);
const decimal24_t temp484 PROGMEM = populate_decimal(54, 88);
const decimal24_t temp485 PROGMEM = populate_decimal(55, 10);
const decimal24_t temp486 PROGMEM = populate_decimal(55, 32);
const decimal24_t temp487 PROGMEM = populate_decimal(55, 53);
const decimal24_t temp488 PROGMEM = populate_decimal(55, 75);
const decimal24_t temp489 PROGMEM = populate_decimal(55, 97);
const decimal24_t temp490 PROGMEM = populate_decimal(56, 19);
const decimal24_t temp491 PROGMEM = populate_decimal(56, 40);
const decimal24_t temp492 PROGMEM = populate_decimal(56, 62);
const decimal24_t temp493 PROGMEM = populate_decimal(56, 84);
const decimal24_t temp494 PROGMEM = populate_decimal(57, 5);
const decimal24_t temp495 PROGMEM = populate_decimal(57, 27);
const decimal24_t temp496 PROGMEM = populate_decimal(57, 49);
const decimal24_t temp497 PROGMEM = populate_decimal(57, 71);
const decimal24_t temp498 PROGMEM = populate_decimal(57, 92);
const decimal24_t temp499 PROGMEM = populate_decimal(58, 14);
const decimal24_t temp500 PROGMEM = populate_decimal(58, 36);
const decimal24_t temp501 PROGMEM = populate_decimal(58, 58);
const decimal24_t temp502 PROGMEM = populate_decimal(58, 79);
const decimal24_t temp503 PROGMEM = populate_decimal(59, 1);
const decimal24_t temp504 PROGMEM = populate_decimal(59, 23);
const decimal24_t temp505 PROGMEM = populate_decimal(59, 44);
const decimal24_t temp506 PROGMEM = populate_decimal(59, 66);
const decimal24_t temp507 PROGMEM = populate_decimal(59, 88);
const decimal24_t temp508 PROGMEM = populate_decimal(60, 10);
const decimal24_t temp509 PROGMEM = populate_decimal(60, 31);
const decimal24_t temp510 PROGMEM = populate_decimal(60, 53);
const decimal24_t temp511 PROGMEM = populate_decimal(60, 75);
const decimal24_t temp512 PROGMEM = populate_decimal(60, 96);
const decimal24_t temp513 PROGMEM = populate_decimal(61, 18);
const decimal24_t temp514 PROGMEM = populate_decimal(61, 40);
const decimal24_t temp515 PROGMEM = populate_decimal(61, 62);
const decimal24_t temp516 PROGMEM = populate_decimal(61, 83);
const decimal24_t temp517 PROGMEM = populate_decimal(62, 5);
const decimal24_t temp518 PROGMEM = populate_decimal(62, 27);
const decimal24_t temp519 PROGMEM = populate_decimal(62, 49);
const decimal24_t temp520 PROGMEM = populate_decimal(62, 70);
const decimal24_t temp521 PROGMEM = populate_decimal(62, 92);
const decimal24_t temp522 PROGMEM = populate_decimal(63, 14);
const decimal24_t temp523 PROGMEM = populate_decimal(63, 35);
const decimal24_t temp524 PROGMEM = populate_decimal(63, 57);
const decimal24_t temp525 PROGMEM = populate_decimal(63, 79);
const decimal24_t temp526 PROGMEM = populate_decimal(64, 1);
const decimal24_t temp527 PROGMEM = populate_decimal(64, 22);
const decimal24_t temp528 PROGMEM = populate_decimal(64, 44);
const decimal24_t temp529 PROGMEM = populate_decimal(64, 66);
const decimal24_t temp530 PROGMEM = populate_decimal(64, 87);
const decimal24_t temp531 PROGMEM = populate_decimal(65, 9);

static PGM_VOID_P const tempLookup[TEMP_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
&temp0,
&temp1,
&temp2,
&temp3,
&temp4,
&temp5,
&temp6,
&temp7,
&temp8,
&temp9,
&temp10,
&temp11,
&temp12,
&temp13,
&temp14,
&temp15,
&temp16,
&temp17,
&temp18,
&temp19,
&temp20,
&temp21,
&temp22,
&temp23,
&temp24,
&temp25,
&temp26,
&temp27,
&temp28,
&temp29,
&temp30,
&temp31,
&temp32,
&temp33,
&temp34,
&temp35,
&temp36,
&temp37,
&temp38,
&temp39,
&temp40,
&temp41,
&temp42,
&temp43,
&temp44,
&temp45,
&temp46,
&temp47,
&temp48,
&temp49,
&temp50,
&temp51,
&temp52,
&temp53,
&temp54,
&temp55,
&temp56,
&temp57,
&temp58,
&temp59,
&temp60,
&temp61,
&temp62,
&temp63,
&temp64,
&temp65,
&temp66,
&temp67,
&temp68,
&temp69,
&temp70,
&temp71,
&temp72,
&temp73,
&temp74,
&temp75,
&temp76,
&temp77,
&temp78,
&temp79,
&temp80,
&temp81,
&temp82,
&temp83,
&temp84,
&temp85,
&temp86,
&temp87,
&temp88,
&temp89,
&temp90,
&temp91,
&temp92,
&temp93,
&temp94,
&temp95,
&temp96,
&temp97,
&temp98,
&temp99,
&temp100,
&temp101,
&temp102,
&temp103,
&temp104,
&temp105,
&temp106,
&temp107,
&temp108,
&temp109,
&temp110,
&temp111,
&temp112,
&temp113,
&temp114,
&temp115,
&temp116,
&temp117,
&temp118,
&temp119,
&temp120,
&temp121,
&temp122,
&temp123,
&temp124,
&temp125,
&temp126,
&temp127,
&temp128,
&temp129,
&temp130,
&temp131,
&temp132,
&temp133,
&temp134,
&temp135,
&temp136,
&temp137,
&temp138,
&temp139,
&temp140,
&temp141,
&temp142,
&temp143,
&temp144,
&temp145,
&temp146,
&temp147,
&temp148,
&temp149,
&temp150,
&temp151,
&temp152,
&temp153,
&temp154,
&temp155,
&temp156,
&temp157,
&temp158,
&temp159,
&temp160,
&temp161,
&temp162,
&temp163,
&temp164,
&temp165,
&temp166,
&temp167,
&temp168,
&temp169,
&temp170,
&temp171,
&temp172,
&temp173,
&temp174,
&temp175,
&temp176,
&temp177,
&temp178,
&temp179,
&temp180,
&temp181,
&temp182,
&temp183,
&temp184,
&temp185,
&temp186,
&temp187,
&temp188,
&temp189,
&temp190,
&temp191,
&temp192,
&temp193,
&temp194,
&temp195,
&temp196,
&temp197,
&temp198,
&temp199,
&temp200,
&temp201,
&temp202,
&temp203,
&temp204,
&temp205,
&temp206,
&temp207,
&temp208,
&temp209,
&temp210,
&temp211,
&temp212,
&temp213,
&temp214,
&temp215,
&temp216,
&temp217,
&temp218,
&temp219,
&temp220,
&temp221,
&temp222,
&temp223,
&temp224,
&temp225,
&temp226,
&temp227,
&temp228,
&temp229,
&temp230,
&temp231,
&temp232,
&temp233,
&temp234,
&temp235,
&temp236,
&temp237,
&temp238,
&temp239,
&temp240,
&temp241,
&temp242,
&temp243,
&temp244,
&temp245,
&temp246,
&temp247,
&temp248,
&temp249,
&temp250,
&temp251,
&temp252,
&temp253,
&temp254,
&temp255,
&temp256,
&temp257,
&temp258,
&temp259,
&temp260,
&temp261,
&temp262,
&temp263,
&temp264,
&temp265,
&temp266,
&temp267,
&temp268,
&temp269,
&temp270,
&temp271,
&temp272,
&temp273,
&temp274,
&temp275,
&temp276,
&temp277,
&temp278,
&temp279,
&temp280,
&temp281,
&temp282,
&temp283,
&temp284,
&temp285,
&temp286,
&temp287,
&temp288,
&temp289,
&temp290,
&temp291,
&temp292,
&temp293,
&temp294,
&temp295,
&temp296,
&temp297,
&temp298,
&temp299,
&temp300,
&temp301,
&temp302,
&temp303,
&temp304,
&temp305,
&temp306,
&temp307,
&temp308,
&temp309,
&temp310,
&temp311,
&temp312,
&temp313,
&temp314,
&temp315,
&temp316,
&temp317,
&temp318,
&temp319,
&temp320,
&temp321,
&temp322,
&temp323,
&temp324,
&temp325,
&temp326,
&temp327,
&temp328,
&temp329,
&temp330,
&temp331,
&temp332,
&temp333,
&temp334,
&temp335,
&temp336,
&temp337,
&temp338,
&temp339,
&temp340,
&temp341,
&temp342,
&temp343,
&temp344,
&temp345,
&temp346,
&temp347,
&temp348,
&temp349,
&temp350,
&temp351,
&temp352,
&temp353,
&temp354,
&temp355,
&temp356,
&temp357,
&temp358,
&temp359,
&temp360,
&temp361,
&temp362,
&temp363,
&temp364,
&temp365,
&temp366,
&temp367,
&temp368,
&temp369,
&temp370,
&temp371,
&temp372,
&temp373,
&temp374,
&temp375,
&temp376,
&temp377,
&temp378,
&temp379,
&temp380,
&temp381,
&temp382,
&temp383,
&temp384,
&temp385,
&temp386,
&temp387,
&temp388,
&temp389,
&temp390,
&temp391,
&temp392,
&temp393,
&temp394,
&temp395,
&temp396,
&temp397,
&temp398,
&temp399,
&temp400,
&temp401,
&temp402,
&temp403,
&temp404,
&temp405,
&temp406,
&temp407,
&temp408,
&temp409,
&temp410,
&temp411,
&temp412,
&temp413,
&temp414,
&temp415,
&temp416,
&temp417,
&temp418,
&temp419,
&temp420,
&temp421,
&temp422,
&temp423,
&temp424,
&temp425,
&temp426,
&temp427,
&temp428,
&temp429,
&temp430,
&temp431,
&temp432,
&temp433,
&temp434,
&temp435,
&temp436,
&temp437,
&temp438,
&temp439,
&temp440,
&temp441,
&temp442,
&temp443,
&temp444,
&temp445,
&temp446,
&temp447,
&temp448,
&temp449,
&temp450,
&temp451,
&temp452,
&temp453,
&temp454,
&temp455,
&temp456,
&temp457,
&temp458,
&temp459,
&temp460,
&temp461,
&temp462,
&temp463,
&temp464,
&temp465,
&temp466,
&temp467,
&temp468,
&temp469,
&temp470,
&temp471,
&temp472,
&temp473,
&temp474,
&temp475,
&temp476,
&temp477,
&temp478,
&temp479,
&temp480,
&temp481,
&temp482,
&temp483,
&temp484,
&temp485,
&temp486,
&temp487,
&temp488,
&temp489,
&temp490,
&temp491,
&temp492,
&temp493,
&temp494,
&temp495,
&temp496,
&temp497,
&temp498,
&temp499,
&temp500,
&temp501,
&temp502,
&temp503,
&temp504,
&temp505,
&temp506,
&temp507,
&temp508,
&temp509,
&temp510,
&temp511,
&temp512,
&temp513,
&temp514,
&temp515,
&temp516,
&temp517,
&temp518,
&temp519,
&temp520,
&temp521,
&temp522,
&temp523,
&temp524,
&temp525,
&temp526,
&temp527,
&temp528,
&temp529,
&temp530,
&temp531
};

#endif
