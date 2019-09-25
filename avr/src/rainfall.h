#include <avr/pgmspace.h>

#include "types.h"

#ifndef _INCL_RAINFALL
#define _INCL_RAINFALL

#define RAINFALL_LOOKUP_BUFFER_SIZE		255

#define PI								3.14159265

#define TIPPING_BUCKET_VOLUME			1750		// In mm^3 (1 cm^3 | 1 ml = 1000mm^3)
#define COLLECTING_FUNNEL_RADIUS		50			// In mm

#define TIPS_TO_MM_SCALE_FACTOR			(TIPPING_BUCKET_VOLUME / (PI * COLLECTING_FUNNEL_RADIUS * COLLECTING_FUNNEL_RADIUS))


/******************************************************************************
**
** Calculate the rainfall in mm for values of number of tips. This is an
** expensive operation on a microcontroller, hence we calcuate this at 
** compile time and store in flash ROM.
**
** (Tipping bucket volume (mm^3) x # tips) / Collecting funnel area (mm^2)
**
** Tips is measured using a reed switch and a magnet attached to the tipping
** bucket. If the tipping bucket has a volume of 1750 mm^3 and the collecting funnel
** has a radius of 50 mm, then 233 tips per hour (tph) is equivalent to a rate of 
** rainfall of 51.94 mm/hour, which if maintained over a 48 hour period is the 
** highest rainfall ever recorded (Chennai, India - 2493mm).
**
** RAINFALL_LOOKUP_BUFFER_SIZE defines the number of slots in our lookup table, and
** therefore the maximum tph that is supported.
**
** This array of const values uses the PROGMEM modifier, a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array, code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/
const decimal24_t rainfall0 PROGMEM = populate_decimal(0, 0);
const decimal24_t rainfall1 PROGMEM = populate_decimal(0, 22);
const decimal24_t rainfall2 PROGMEM = populate_decimal(0, 44);
const decimal24_t rainfall3 PROGMEM = populate_decimal(0, 66);
const decimal24_t rainfall4 PROGMEM = populate_decimal(0, 89);
const decimal24_t rainfall5 PROGMEM = populate_decimal(1, 11);
const decimal24_t rainfall6 PROGMEM = populate_decimal(1, 33);
const decimal24_t rainfall7 PROGMEM = populate_decimal(1, 55);
const decimal24_t rainfall8 PROGMEM = populate_decimal(1, 78);
const decimal24_t rainfall9 PROGMEM = populate_decimal(2, 0);
const decimal24_t rainfall10 PROGMEM = populate_decimal(2, 22);
const decimal24_t rainfall11 PROGMEM = populate_decimal(2, 45);
const decimal24_t rainfall12 PROGMEM = populate_decimal(2, 67);
const decimal24_t rainfall13 PROGMEM = populate_decimal(2, 89);
const decimal24_t rainfall14 PROGMEM = populate_decimal(3, 11);
const decimal24_t rainfall15 PROGMEM = populate_decimal(3, 34);
const decimal24_t rainfall16 PROGMEM = populate_decimal(3, 56);
const decimal24_t rainfall17 PROGMEM = populate_decimal(3, 78);
const decimal24_t rainfall18 PROGMEM = populate_decimal(4, 1);
const decimal24_t rainfall19 PROGMEM = populate_decimal(4, 23);
const decimal24_t rainfall20 PROGMEM = populate_decimal(4, 45);
const decimal24_t rainfall21 PROGMEM = populate_decimal(4, 67);
const decimal24_t rainfall22 PROGMEM = populate_decimal(4, 90);
const decimal24_t rainfall23 PROGMEM = populate_decimal(5, 12);
const decimal24_t rainfall24 PROGMEM = populate_decimal(5, 34);
const decimal24_t rainfall25 PROGMEM = populate_decimal(5, 57);
const decimal24_t rainfall26 PROGMEM = populate_decimal(5, 79);
const decimal24_t rainfall27 PROGMEM = populate_decimal(6, 1);
const decimal24_t rainfall28 PROGMEM = populate_decimal(6, 23);
const decimal24_t rainfall29 PROGMEM = populate_decimal(6, 46);
const decimal24_t rainfall30 PROGMEM = populate_decimal(6, 68);
const decimal24_t rainfall31 PROGMEM = populate_decimal(6, 90);
const decimal24_t rainfall32 PROGMEM = populate_decimal(7, 13);
const decimal24_t rainfall33 PROGMEM = populate_decimal(7, 35);
const decimal24_t rainfall34 PROGMEM = populate_decimal(7, 57);
const decimal24_t rainfall35 PROGMEM = populate_decimal(7, 79);
const decimal24_t rainfall36 PROGMEM = populate_decimal(8, 2);
const decimal24_t rainfall37 PROGMEM = populate_decimal(8, 24);
const decimal24_t rainfall38 PROGMEM = populate_decimal(8, 46);
const decimal24_t rainfall39 PROGMEM = populate_decimal(8, 68);
const decimal24_t rainfall40 PROGMEM = populate_decimal(8, 91);
const decimal24_t rainfall41 PROGMEM = populate_decimal(9, 13);
const decimal24_t rainfall42 PROGMEM = populate_decimal(9, 35);
const decimal24_t rainfall43 PROGMEM = populate_decimal(9, 58);
const decimal24_t rainfall44 PROGMEM = populate_decimal(9, 80);
const decimal24_t rainfall45 PROGMEM = populate_decimal(10, 2);
const decimal24_t rainfall46 PROGMEM = populate_decimal(10, 24);
const decimal24_t rainfall47 PROGMEM = populate_decimal(10, 47);
const decimal24_t rainfall48 PROGMEM = populate_decimal(10, 69);
const decimal24_t rainfall49 PROGMEM = populate_decimal(10, 91);
const decimal24_t rainfall50 PROGMEM = populate_decimal(11, 14);
const decimal24_t rainfall51 PROGMEM = populate_decimal(11, 36);
const decimal24_t rainfall52 PROGMEM = populate_decimal(11, 58);
const decimal24_t rainfall53 PROGMEM = populate_decimal(11, 80);
const decimal24_t rainfall54 PROGMEM = populate_decimal(12, 3);
const decimal24_t rainfall55 PROGMEM = populate_decimal(12, 25);
const decimal24_t rainfall56 PROGMEM = populate_decimal(12, 47);
const decimal24_t rainfall57 PROGMEM = populate_decimal(12, 70);
const decimal24_t rainfall58 PROGMEM = populate_decimal(12, 92);
const decimal24_t rainfall59 PROGMEM = populate_decimal(13, 14);
const decimal24_t rainfall60 PROGMEM = populate_decimal(13, 36);
const decimal24_t rainfall61 PROGMEM = populate_decimal(13, 59);
const decimal24_t rainfall62 PROGMEM = populate_decimal(13, 81);
const decimal24_t rainfall63 PROGMEM = populate_decimal(14, 3);
const decimal24_t rainfall64 PROGMEM = populate_decimal(14, 26);
const decimal24_t rainfall65 PROGMEM = populate_decimal(14, 48);
const decimal24_t rainfall66 PROGMEM = populate_decimal(14, 70);
const decimal24_t rainfall67 PROGMEM = populate_decimal(14, 92);
const decimal24_t rainfall68 PROGMEM = populate_decimal(15, 15);
const decimal24_t rainfall69 PROGMEM = populate_decimal(15, 37);
const decimal24_t rainfall70 PROGMEM = populate_decimal(15, 59);
const decimal24_t rainfall71 PROGMEM = populate_decimal(15, 82);
const decimal24_t rainfall72 PROGMEM = populate_decimal(16, 4);
const decimal24_t rainfall73 PROGMEM = populate_decimal(16, 26);
const decimal24_t rainfall74 PROGMEM = populate_decimal(16, 48);
const decimal24_t rainfall75 PROGMEM = populate_decimal(16, 71);
const decimal24_t rainfall76 PROGMEM = populate_decimal(16, 93);
const decimal24_t rainfall77 PROGMEM = populate_decimal(17, 15);
const decimal24_t rainfall78 PROGMEM = populate_decimal(17, 37);
const decimal24_t rainfall79 PROGMEM = populate_decimal(17, 60);
const decimal24_t rainfall80 PROGMEM = populate_decimal(17, 82);
const decimal24_t rainfall81 PROGMEM = populate_decimal(18, 4);
const decimal24_t rainfall82 PROGMEM = populate_decimal(18, 27);
const decimal24_t rainfall83 PROGMEM = populate_decimal(18, 49);
const decimal24_t rainfall84 PROGMEM = populate_decimal(18, 71);
const decimal24_t rainfall85 PROGMEM = populate_decimal(18, 93);
const decimal24_t rainfall86 PROGMEM = populate_decimal(19, 16);
const decimal24_t rainfall87 PROGMEM = populate_decimal(19, 38);
const decimal24_t rainfall88 PROGMEM = populate_decimal(19, 60);
const decimal24_t rainfall89 PROGMEM = populate_decimal(19, 83);
const decimal24_t rainfall90 PROGMEM = populate_decimal(20, 5);
const decimal24_t rainfall91 PROGMEM = populate_decimal(20, 27);
const decimal24_t rainfall92 PROGMEM = populate_decimal(20, 49);
const decimal24_t rainfall93 PROGMEM = populate_decimal(20, 72);
const decimal24_t rainfall94 PROGMEM = populate_decimal(20, 94);
const decimal24_t rainfall95 PROGMEM = populate_decimal(21, 16);
const decimal24_t rainfall96 PROGMEM = populate_decimal(21, 39);
const decimal24_t rainfall97 PROGMEM = populate_decimal(21, 61);
const decimal24_t rainfall98 PROGMEM = populate_decimal(21, 83);
const decimal24_t rainfall99 PROGMEM = populate_decimal(22, 5);
const decimal24_t rainfall100 PROGMEM = populate_decimal(22, 28);
const decimal24_t rainfall101 PROGMEM = populate_decimal(22, 50);
const decimal24_t rainfall102 PROGMEM = populate_decimal(22, 72);
const decimal24_t rainfall103 PROGMEM = populate_decimal(22, 95);
const decimal24_t rainfall104 PROGMEM = populate_decimal(23, 17);
const decimal24_t rainfall105 PROGMEM = populate_decimal(23, 39);
const decimal24_t rainfall106 PROGMEM = populate_decimal(23, 61);
const decimal24_t rainfall107 PROGMEM = populate_decimal(23, 84);
const decimal24_t rainfall108 PROGMEM = populate_decimal(24, 6);
const decimal24_t rainfall109 PROGMEM = populate_decimal(24, 28);
const decimal24_t rainfall110 PROGMEM = populate_decimal(24, 50);
const decimal24_t rainfall111 PROGMEM = populate_decimal(24, 73);
const decimal24_t rainfall112 PROGMEM = populate_decimal(24, 95);
const decimal24_t rainfall113 PROGMEM = populate_decimal(25, 17);
const decimal24_t rainfall114 PROGMEM = populate_decimal(25, 40);
const decimal24_t rainfall115 PROGMEM = populate_decimal(25, 62);
const decimal24_t rainfall116 PROGMEM = populate_decimal(25, 84);
const decimal24_t rainfall117 PROGMEM = populate_decimal(26, 6);
const decimal24_t rainfall118 PROGMEM = populate_decimal(26, 29);
const decimal24_t rainfall119 PROGMEM = populate_decimal(26, 51);
const decimal24_t rainfall120 PROGMEM = populate_decimal(26, 73);
const decimal24_t rainfall121 PROGMEM = populate_decimal(26, 96);
const decimal24_t rainfall122 PROGMEM = populate_decimal(27, 18);
const decimal24_t rainfall123 PROGMEM = populate_decimal(27, 40);
const decimal24_t rainfall124 PROGMEM = populate_decimal(27, 62);
const decimal24_t rainfall125 PROGMEM = populate_decimal(27, 85);
const decimal24_t rainfall126 PROGMEM = populate_decimal(28, 7);
const decimal24_t rainfall127 PROGMEM = populate_decimal(28, 29);
const decimal24_t rainfall128 PROGMEM = populate_decimal(28, 52);
const decimal24_t rainfall129 PROGMEM = populate_decimal(28, 74);
const decimal24_t rainfall130 PROGMEM = populate_decimal(28, 96);
const decimal24_t rainfall131 PROGMEM = populate_decimal(29, 18);
const decimal24_t rainfall132 PROGMEM = populate_decimal(29, 41);
const decimal24_t rainfall133 PROGMEM = populate_decimal(29, 63);
const decimal24_t rainfall134 PROGMEM = populate_decimal(29, 85);
const decimal24_t rainfall135 PROGMEM = populate_decimal(30, 8);
const decimal24_t rainfall136 PROGMEM = populate_decimal(30, 30);
const decimal24_t rainfall137 PROGMEM = populate_decimal(30, 52);
const decimal24_t rainfall138 PROGMEM = populate_decimal(30, 74);
const decimal24_t rainfall139 PROGMEM = populate_decimal(30, 97);
const decimal24_t rainfall140 PROGMEM = populate_decimal(31, 19);
const decimal24_t rainfall141 PROGMEM = populate_decimal(31, 41);
const decimal24_t rainfall142 PROGMEM = populate_decimal(31, 64);
const decimal24_t rainfall143 PROGMEM = populate_decimal(31, 86);
const decimal24_t rainfall144 PROGMEM = populate_decimal(32, 8);
const decimal24_t rainfall145 PROGMEM = populate_decimal(32, 30);
const decimal24_t rainfall146 PROGMEM = populate_decimal(32, 53);
const decimal24_t rainfall147 PROGMEM = populate_decimal(32, 75);
const decimal24_t rainfall148 PROGMEM = populate_decimal(32, 97);
const decimal24_t rainfall149 PROGMEM = populate_decimal(33, 19);
const decimal24_t rainfall150 PROGMEM = populate_decimal(33, 42);
const decimal24_t rainfall151 PROGMEM = populate_decimal(33, 64);
const decimal24_t rainfall152 PROGMEM = populate_decimal(33, 86);
const decimal24_t rainfall153 PROGMEM = populate_decimal(34, 9);
const decimal24_t rainfall154 PROGMEM = populate_decimal(34, 31);
const decimal24_t rainfall155 PROGMEM = populate_decimal(34, 53);
const decimal24_t rainfall156 PROGMEM = populate_decimal(34, 75);
const decimal24_t rainfall157 PROGMEM = populate_decimal(34, 98);
const decimal24_t rainfall158 PROGMEM = populate_decimal(35, 20);
const decimal24_t rainfall159 PROGMEM = populate_decimal(35, 42);
const decimal24_t rainfall160 PROGMEM = populate_decimal(35, 65);
const decimal24_t rainfall161 PROGMEM = populate_decimal(35, 87);
const decimal24_t rainfall162 PROGMEM = populate_decimal(36, 9);
const decimal24_t rainfall163 PROGMEM = populate_decimal(36, 31);
const decimal24_t rainfall164 PROGMEM = populate_decimal(36, 54);
const decimal24_t rainfall165 PROGMEM = populate_decimal(36, 76);
const decimal24_t rainfall166 PROGMEM = populate_decimal(36, 98);
const decimal24_t rainfall167 PROGMEM = populate_decimal(37, 21);
const decimal24_t rainfall168 PROGMEM = populate_decimal(37, 43);
const decimal24_t rainfall169 PROGMEM = populate_decimal(37, 65);
const decimal24_t rainfall170 PROGMEM = populate_decimal(37, 87);
const decimal24_t rainfall171 PROGMEM = populate_decimal(38, 10);
const decimal24_t rainfall172 PROGMEM = populate_decimal(38, 32);
const decimal24_t rainfall173 PROGMEM = populate_decimal(38, 54);
const decimal24_t rainfall174 PROGMEM = populate_decimal(38, 77);
const decimal24_t rainfall175 PROGMEM = populate_decimal(38, 99);
const decimal24_t rainfall176 PROGMEM = populate_decimal(39, 21);
const decimal24_t rainfall177 PROGMEM = populate_decimal(39, 43);
const decimal24_t rainfall178 PROGMEM = populate_decimal(39, 66);
const decimal24_t rainfall179 PROGMEM = populate_decimal(39, 88);
const decimal24_t rainfall180 PROGMEM = populate_decimal(40, 10);
const decimal24_t rainfall181 PROGMEM = populate_decimal(40, 32);
const decimal24_t rainfall182 PROGMEM = populate_decimal(40, 55);
const decimal24_t rainfall183 PROGMEM = populate_decimal(40, 77);
const decimal24_t rainfall184 PROGMEM = populate_decimal(40, 99);
const decimal24_t rainfall185 PROGMEM = populate_decimal(41, 22);
const decimal24_t rainfall186 PROGMEM = populate_decimal(41, 44);
const decimal24_t rainfall187 PROGMEM = populate_decimal(41, 66);
const decimal24_t rainfall188 PROGMEM = populate_decimal(41, 88);
const decimal24_t rainfall189 PROGMEM = populate_decimal(42, 11);
const decimal24_t rainfall190 PROGMEM = populate_decimal(42, 33);
const decimal24_t rainfall191 PROGMEM = populate_decimal(42, 55);
const decimal24_t rainfall192 PROGMEM = populate_decimal(42, 78);
const decimal24_t rainfall193 PROGMEM = populate_decimal(43, 0);
const decimal24_t rainfall194 PROGMEM = populate_decimal(43, 22);
const decimal24_t rainfall195 PROGMEM = populate_decimal(43, 44);
const decimal24_t rainfall196 PROGMEM = populate_decimal(43, 67);
const decimal24_t rainfall197 PROGMEM = populate_decimal(43, 89);
const decimal24_t rainfall198 PROGMEM = populate_decimal(44, 11);
const decimal24_t rainfall199 PROGMEM = populate_decimal(44, 34);
const decimal24_t rainfall200 PROGMEM = populate_decimal(44, 56);
const decimal24_t rainfall201 PROGMEM = populate_decimal(44, 78);
const decimal24_t rainfall202 PROGMEM = populate_decimal(45, 0);
const decimal24_t rainfall203 PROGMEM = populate_decimal(45, 23);
const decimal24_t rainfall204 PROGMEM = populate_decimal(45, 45);
const decimal24_t rainfall205 PROGMEM = populate_decimal(45, 67);
const decimal24_t rainfall206 PROGMEM = populate_decimal(45, 90);
const decimal24_t rainfall207 PROGMEM = populate_decimal(46, 12);
const decimal24_t rainfall208 PROGMEM = populate_decimal(46, 34);
const decimal24_t rainfall209 PROGMEM = populate_decimal(46, 56);
const decimal24_t rainfall210 PROGMEM = populate_decimal(46, 79);
const decimal24_t rainfall211 PROGMEM = populate_decimal(47, 1);
const decimal24_t rainfall212 PROGMEM = populate_decimal(47, 23);
const decimal24_t rainfall213 PROGMEM = populate_decimal(47, 46);
const decimal24_t rainfall214 PROGMEM = populate_decimal(47, 68);
const decimal24_t rainfall215 PROGMEM = populate_decimal(47, 90);
const decimal24_t rainfall216 PROGMEM = populate_decimal(48, 12);
const decimal24_t rainfall217 PROGMEM = populate_decimal(48, 35);
const decimal24_t rainfall218 PROGMEM = populate_decimal(48, 57);
const decimal24_t rainfall219 PROGMEM = populate_decimal(48, 79);
const decimal24_t rainfall220 PROGMEM = populate_decimal(49, 1);
const decimal24_t rainfall221 PROGMEM = populate_decimal(49, 24);
const decimal24_t rainfall222 PROGMEM = populate_decimal(49, 46);
const decimal24_t rainfall223 PROGMEM = populate_decimal(49, 68);
const decimal24_t rainfall224 PROGMEM = populate_decimal(49, 91);
const decimal24_t rainfall225 PROGMEM = populate_decimal(50, 13);
const decimal24_t rainfall226 PROGMEM = populate_decimal(50, 35);
const decimal24_t rainfall227 PROGMEM = populate_decimal(50, 57);
const decimal24_t rainfall228 PROGMEM = populate_decimal(50, 80);
const decimal24_t rainfall229 PROGMEM = populate_decimal(51, 2);
const decimal24_t rainfall230 PROGMEM = populate_decimal(51, 24);
const decimal24_t rainfall231 PROGMEM = populate_decimal(51, 47);
const decimal24_t rainfall232 PROGMEM = populate_decimal(51, 69);
const decimal24_t rainfall233 PROGMEM = populate_decimal(51, 91);
const decimal24_t rainfall234 PROGMEM = populate_decimal(52, 13);
const decimal24_t rainfall235 PROGMEM = populate_decimal(52, 36);
const decimal24_t rainfall236 PROGMEM = populate_decimal(52, 58);
const decimal24_t rainfall237 PROGMEM = populate_decimal(52, 80);
const decimal24_t rainfall238 PROGMEM = populate_decimal(53, 3);
const decimal24_t rainfall239 PROGMEM = populate_decimal(53, 25);
const decimal24_t rainfall240 PROGMEM = populate_decimal(53, 47);
const decimal24_t rainfall241 PROGMEM = populate_decimal(53, 69);
const decimal24_t rainfall242 PROGMEM = populate_decimal(53, 92);
const decimal24_t rainfall243 PROGMEM = populate_decimal(54, 14);
const decimal24_t rainfall244 PROGMEM = populate_decimal(54, 36);
const decimal24_t rainfall245 PROGMEM = populate_decimal(54, 59);
const decimal24_t rainfall246 PROGMEM = populate_decimal(54, 81);
const decimal24_t rainfall247 PROGMEM = populate_decimal(55, 3);
const decimal24_t rainfall248 PROGMEM = populate_decimal(55, 25);
const decimal24_t rainfall249 PROGMEM = populate_decimal(55, 48);
const decimal24_t rainfall250 PROGMEM = populate_decimal(55, 70);
const decimal24_t rainfall251 PROGMEM = populate_decimal(55, 92);
const decimal24_t rainfall252 PROGMEM = populate_decimal(56, 14);
const decimal24_t rainfall253 PROGMEM = populate_decimal(56, 37);
const decimal24_t rainfall254 PROGMEM = populate_decimal(56, 59);

static PGM_VOID_P const rainfallLookup[RAINFALL_LOOKUP_BUFFER_SIZE] PROGMEM =
{
&rainfall0,
&rainfall1,
&rainfall2,
&rainfall3,
&rainfall4,
&rainfall5,
&rainfall6,
&rainfall7,
&rainfall8,
&rainfall9,
&rainfall10,
&rainfall11,
&rainfall12,
&rainfall13,
&rainfall14,
&rainfall15,
&rainfall16,
&rainfall17,
&rainfall18,
&rainfall19,
&rainfall20,
&rainfall21,
&rainfall22,
&rainfall23,
&rainfall24,
&rainfall25,
&rainfall26,
&rainfall27,
&rainfall28,
&rainfall29,
&rainfall30,
&rainfall31,
&rainfall32,
&rainfall33,
&rainfall34,
&rainfall35,
&rainfall36,
&rainfall37,
&rainfall38,
&rainfall39,
&rainfall40,
&rainfall41,
&rainfall42,
&rainfall43,
&rainfall44,
&rainfall45,
&rainfall46,
&rainfall47,
&rainfall48,
&rainfall49,
&rainfall50,
&rainfall51,
&rainfall52,
&rainfall53,
&rainfall54,
&rainfall55,
&rainfall56,
&rainfall57,
&rainfall58,
&rainfall59,
&rainfall60,
&rainfall61,
&rainfall62,
&rainfall63,
&rainfall64,
&rainfall65,
&rainfall66,
&rainfall67,
&rainfall68,
&rainfall69,
&rainfall70,
&rainfall71,
&rainfall72,
&rainfall73,
&rainfall74,
&rainfall75,
&rainfall76,
&rainfall77,
&rainfall78,
&rainfall79,
&rainfall80,
&rainfall81,
&rainfall82,
&rainfall83,
&rainfall84,
&rainfall85,
&rainfall86,
&rainfall87,
&rainfall88,
&rainfall89,
&rainfall90,
&rainfall91,
&rainfall92,
&rainfall93,
&rainfall94,
&rainfall95,
&rainfall96,
&rainfall97,
&rainfall98,
&rainfall99,
&rainfall100,
&rainfall101,
&rainfall102,
&rainfall103,
&rainfall104,
&rainfall105,
&rainfall106,
&rainfall107,
&rainfall108,
&rainfall109,
&rainfall110,
&rainfall111,
&rainfall112,
&rainfall113,
&rainfall114,
&rainfall115,
&rainfall116,
&rainfall117,
&rainfall118,
&rainfall119,
&rainfall120,
&rainfall121,
&rainfall122,
&rainfall123,
&rainfall124,
&rainfall125,
&rainfall126,
&rainfall127,
&rainfall128,
&rainfall129,
&rainfall130,
&rainfall131,
&rainfall132,
&rainfall133,
&rainfall134,
&rainfall135,
&rainfall136,
&rainfall137,
&rainfall138,
&rainfall139,
&rainfall140,
&rainfall141,
&rainfall142,
&rainfall143,
&rainfall144,
&rainfall145,
&rainfall146,
&rainfall147,
&rainfall148,
&rainfall149,
&rainfall150,
&rainfall151,
&rainfall152,
&rainfall153,
&rainfall154,
&rainfall155,
&rainfall156,
&rainfall157,
&rainfall158,
&rainfall159,
&rainfall160,
&rainfall161,
&rainfall162,
&rainfall163,
&rainfall164,
&rainfall165,
&rainfall166,
&rainfall167,
&rainfall168,
&rainfall169,
&rainfall170,
&rainfall171,
&rainfall172,
&rainfall173,
&rainfall174,
&rainfall175,
&rainfall176,
&rainfall177,
&rainfall178,
&rainfall179,
&rainfall180,
&rainfall181,
&rainfall182,
&rainfall183,
&rainfall184,
&rainfall185,
&rainfall186,
&rainfall187,
&rainfall188,
&rainfall189,
&rainfall190,
&rainfall191,
&rainfall192,
&rainfall193,
&rainfall194,
&rainfall195,
&rainfall196,
&rainfall197,
&rainfall198,
&rainfall199,
&rainfall200,
&rainfall201,
&rainfall202,
&rainfall203,
&rainfall204,
&rainfall205,
&rainfall206,
&rainfall207,
&rainfall208,
&rainfall209,
&rainfall210,
&rainfall211,
&rainfall212,
&rainfall213,
&rainfall214,
&rainfall215,
&rainfall216,
&rainfall217,
&rainfall218,
&rainfall219,
&rainfall220,
&rainfall221,
&rainfall222,
&rainfall223,
&rainfall224,
&rainfall225,
&rainfall226,
&rainfall227,
&rainfall228,
&rainfall229,
&rainfall230,
&rainfall231,
&rainfall232,
&rainfall233,
&rainfall234,
&rainfall235,
&rainfall236,
&rainfall237,
&rainfall238,
&rainfall239,
&rainfall240,
&rainfall241,
&rainfall242,
&rainfall243,
&rainfall244,
&rainfall245,
&rainfall246,
&rainfall247,
&rainfall248,
&rainfall249,
&rainfall250,
&rainfall251,
&rainfall252,
&rainfall253,
&rainfall254
};

#endif