#include <avr/pgmspace.h>

#include "types.h"

#ifndef _INCL_KPHLOOKUP
#define _INCL_KPHLOOKUP

#define KPH_LOOKUP_BUFFER_SIZE			178

/******************************************************************************
**
** Calculate the wind speed in kph for values of revolutions per second (rps).
** This is an expensive operation on a microcontroller, hence we calcuate this 
** at compile time and store in flash ROM.
**
** kph = (pi x diameter of anemometer (m) x rps x 3600) / 1000
**
** Revolutions per second (rps) is measured using a reed switch and a magnet attached
** close to the axis of the anemometer blades. If the anemometer blades have a 
** diameter of 10cm (0.1m), then 70 rps is equivalent to a wind speed of 
** ~80 kph (50 mph).
**
** KPH_LOOKUP_BUFFER_SIZE defines the number of slots in our lookup table, and
** therefore the maximum rps that is supported.
**
** This array of const values uses the PROGMEM modifier, a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array, code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/
const decimal24_t windSpeed0 PROGMEM = populate_decimal(0, 0);
const decimal24_t windSpeed1 PROGMEM = populate_decimal(1, 13);
const decimal24_t windSpeed2 PROGMEM = populate_decimal(2, 26);
const decimal24_t windSpeed3 PROGMEM = populate_decimal(3, 39);
const decimal24_t windSpeed4 PROGMEM = populate_decimal(4, 52);
const decimal24_t windSpeed5 PROGMEM = populate_decimal(5, 65);
const decimal24_t windSpeed6 PROGMEM = populate_decimal(6, 78);
const decimal24_t windSpeed7 PROGMEM = populate_decimal(7, 91);
const decimal24_t windSpeed8 PROGMEM = populate_decimal(9, 4);
const decimal24_t windSpeed9 PROGMEM = populate_decimal(10, 17);
const decimal24_t windSpeed10 PROGMEM = populate_decimal(11, 30);
const decimal24_t windSpeed11 PROGMEM = populate_decimal(12, 44);
const decimal24_t windSpeed12 PROGMEM = populate_decimal(13, 57);
const decimal24_t windSpeed13 PROGMEM = populate_decimal(14, 70);
const decimal24_t windSpeed14 PROGMEM = populate_decimal(15, 83);
const decimal24_t windSpeed15 PROGMEM = populate_decimal(16, 96);
const decimal24_t windSpeed16 PROGMEM = populate_decimal(18, 9);
const decimal24_t windSpeed17 PROGMEM = populate_decimal(19, 22);
const decimal24_t windSpeed18 PROGMEM = populate_decimal(20, 35);
const decimal24_t windSpeed19 PROGMEM = populate_decimal(21, 48);
const decimal24_t windSpeed20 PROGMEM = populate_decimal(22, 61);
const decimal24_t windSpeed21 PROGMEM = populate_decimal(23, 75);
const decimal24_t windSpeed22 PROGMEM = populate_decimal(24, 88);
const decimal24_t windSpeed23 PROGMEM = populate_decimal(26, 1);
const decimal24_t windSpeed24 PROGMEM = populate_decimal(27, 14);
const decimal24_t windSpeed25 PROGMEM = populate_decimal(28, 27);
const decimal24_t windSpeed26 PROGMEM = populate_decimal(29, 40);
const decimal24_t windSpeed27 PROGMEM = populate_decimal(30, 53);
const decimal24_t windSpeed28 PROGMEM = populate_decimal(31, 66);
const decimal24_t windSpeed29 PROGMEM = populate_decimal(32, 79);
const decimal24_t windSpeed30 PROGMEM = populate_decimal(33, 92);
const decimal24_t windSpeed31 PROGMEM = populate_decimal(35, 6);
const decimal24_t windSpeed32 PROGMEM = populate_decimal(36, 19);
const decimal24_t windSpeed33 PROGMEM = populate_decimal(37, 32);
const decimal24_t windSpeed34 PROGMEM = populate_decimal(38, 45);
const decimal24_t windSpeed35 PROGMEM = populate_decimal(39, 58);
const decimal24_t windSpeed36 PROGMEM = populate_decimal(40, 71);
const decimal24_t windSpeed37 PROGMEM = populate_decimal(41, 84);
const decimal24_t windSpeed38 PROGMEM = populate_decimal(42, 97);
const decimal24_t windSpeed39 PROGMEM = populate_decimal(44, 10);
const decimal24_t windSpeed40 PROGMEM = populate_decimal(45, 23);
const decimal24_t windSpeed41 PROGMEM = populate_decimal(46, 36);
const decimal24_t windSpeed42 PROGMEM = populate_decimal(47, 50);
const decimal24_t windSpeed43 PROGMEM = populate_decimal(48, 63);
const decimal24_t windSpeed44 PROGMEM = populate_decimal(49, 76);
const decimal24_t windSpeed45 PROGMEM = populate_decimal(50, 89);
const decimal24_t windSpeed46 PROGMEM = populate_decimal(52, 2);
const decimal24_t windSpeed47 PROGMEM = populate_decimal(53, 15);
const decimal24_t windSpeed48 PROGMEM = populate_decimal(54, 28);
const decimal24_t windSpeed49 PROGMEM = populate_decimal(55, 41);
const decimal24_t windSpeed50 PROGMEM = populate_decimal(56, 54);
const decimal24_t windSpeed51 PROGMEM = populate_decimal(57, 67);
const decimal24_t windSpeed52 PROGMEM = populate_decimal(58, 81);
const decimal24_t windSpeed53 PROGMEM = populate_decimal(59, 94);
const decimal24_t windSpeed54 PROGMEM = populate_decimal(61, 7);
const decimal24_t windSpeed55 PROGMEM = populate_decimal(62, 20);
const decimal24_t windSpeed56 PROGMEM = populate_decimal(63, 33);
const decimal24_t windSpeed57 PROGMEM = populate_decimal(64, 46);
const decimal24_t windSpeed58 PROGMEM = populate_decimal(65, 59);
const decimal24_t windSpeed59 PROGMEM = populate_decimal(66, 72);
const decimal24_t windSpeed60 PROGMEM = populate_decimal(67, 85);
const decimal24_t windSpeed61 PROGMEM = populate_decimal(68, 98);
const decimal24_t windSpeed62 PROGMEM = populate_decimal(70, 12);
const decimal24_t windSpeed63 PROGMEM = populate_decimal(71, 25);
const decimal24_t windSpeed64 PROGMEM = populate_decimal(72, 38);
const decimal24_t windSpeed65 PROGMEM = populate_decimal(73, 51);
const decimal24_t windSpeed66 PROGMEM = populate_decimal(74, 64);
const decimal24_t windSpeed67 PROGMEM = populate_decimal(75, 77);
const decimal24_t windSpeed68 PROGMEM = populate_decimal(76, 90);
const decimal24_t windSpeed69 PROGMEM = populate_decimal(78, 3);
const decimal24_t windSpeed70 PROGMEM = populate_decimal(79, 16);
const decimal24_t windSpeed71 PROGMEM = populate_decimal(80, 29);
const decimal24_t windSpeed72 PROGMEM = populate_decimal(81, 43);
const decimal24_t windSpeed73 PROGMEM = populate_decimal(82, 56);
const decimal24_t windSpeed74 PROGMEM = populate_decimal(83, 69);
const decimal24_t windSpeed75 PROGMEM = populate_decimal(84, 82);
const decimal24_t windSpeed76 PROGMEM = populate_decimal(85, 95);
const decimal24_t windSpeed77 PROGMEM = populate_decimal(87, 8);
const decimal24_t windSpeed78 PROGMEM = populate_decimal(88, 21);
const decimal24_t windSpeed79 PROGMEM = populate_decimal(89, 34);
const decimal24_t windSpeed80 PROGMEM = populate_decimal(90, 47);
const decimal24_t windSpeed81 PROGMEM = populate_decimal(91, 60);
const decimal24_t windSpeed82 PROGMEM = populate_decimal(92, 73);
const decimal24_t windSpeed83 PROGMEM = populate_decimal(93, 87);
const decimal24_t windSpeed84 PROGMEM = populate_decimal(95, 0);
const decimal24_t windSpeed85 PROGMEM = populate_decimal(96, 13);
const decimal24_t windSpeed86 PROGMEM = populate_decimal(97, 26);
const decimal24_t windSpeed87 PROGMEM = populate_decimal(98, 39);
const decimal24_t windSpeed88 PROGMEM = populate_decimal(99, 52);
const decimal24_t windSpeed89 PROGMEM = populate_decimal(100, 65);
const decimal24_t windSpeed90 PROGMEM = populate_decimal(101, 78);
const decimal24_t windSpeed91 PROGMEM = populate_decimal(102, 91);
const decimal24_t windSpeed92 PROGMEM = populate_decimal(104, 4);
const decimal24_t windSpeed93 PROGMEM = populate_decimal(105, 18);
const decimal24_t windSpeed94 PROGMEM = populate_decimal(106, 31);
const decimal24_t windSpeed95 PROGMEM = populate_decimal(107, 44);
const decimal24_t windSpeed96 PROGMEM = populate_decimal(108, 57);
const decimal24_t windSpeed97 PROGMEM = populate_decimal(109, 70);
const decimal24_t windSpeed98 PROGMEM = populate_decimal(110, 83);
const decimal24_t windSpeed99 PROGMEM = populate_decimal(111, 96);
const decimal24_t windSpeed100 PROGMEM = populate_decimal(113, 9);
const decimal24_t windSpeed101 PROGMEM = populate_decimal(114, 22);
const decimal24_t windSpeed102 PROGMEM = populate_decimal(115, 35);
const decimal24_t windSpeed103 PROGMEM = populate_decimal(116, 49);
const decimal24_t windSpeed104 PROGMEM = populate_decimal(117, 62);
const decimal24_t windSpeed105 PROGMEM = populate_decimal(118, 75);
const decimal24_t windSpeed106 PROGMEM = populate_decimal(119, 88);
const decimal24_t windSpeed107 PROGMEM = populate_decimal(121, 1);
const decimal24_t windSpeed108 PROGMEM = populate_decimal(122, 14);
const decimal24_t windSpeed109 PROGMEM = populate_decimal(123, 27);
const decimal24_t windSpeed110 PROGMEM = populate_decimal(124, 40);
const decimal24_t windSpeed111 PROGMEM = populate_decimal(125, 53);
const decimal24_t windSpeed112 PROGMEM = populate_decimal(126, 66);
const decimal24_t windSpeed113 PROGMEM = populate_decimal(127, 79);
const decimal24_t windSpeed114 PROGMEM = populate_decimal(128, 93);
const decimal24_t windSpeed115 PROGMEM = populate_decimal(130, 6);
const decimal24_t windSpeed116 PROGMEM = populate_decimal(131, 19);
const decimal24_t windSpeed117 PROGMEM = populate_decimal(132, 32);
const decimal24_t windSpeed118 PROGMEM = populate_decimal(133, 45);
const decimal24_t windSpeed119 PROGMEM = populate_decimal(134, 58);
const decimal24_t windSpeed120 PROGMEM = populate_decimal(135, 71);
const decimal24_t windSpeed121 PROGMEM = populate_decimal(136, 84);
const decimal24_t windSpeed122 PROGMEM = populate_decimal(137, 97);
const decimal24_t windSpeed123 PROGMEM = populate_decimal(139, 10);
const decimal24_t windSpeed124 PROGMEM = populate_decimal(140, 24);
const decimal24_t windSpeed125 PROGMEM = populate_decimal(141, 37);
const decimal24_t windSpeed126 PROGMEM = populate_decimal(142, 50);
const decimal24_t windSpeed127 PROGMEM = populate_decimal(143, 63);
const decimal24_t windSpeed128 PROGMEM = populate_decimal(144, 76);
const decimal24_t windSpeed129 PROGMEM = populate_decimal(145, 89);
const decimal24_t windSpeed130 PROGMEM = populate_decimal(147, 2);
const decimal24_t windSpeed131 PROGMEM = populate_decimal(148, 15);
const decimal24_t windSpeed132 PROGMEM = populate_decimal(149, 28);
const decimal24_t windSpeed133 PROGMEM = populate_decimal(150, 41);
const decimal24_t windSpeed134 PROGMEM = populate_decimal(151, 55);
const decimal24_t windSpeed135 PROGMEM = populate_decimal(152, 68);
const decimal24_t windSpeed136 PROGMEM = populate_decimal(153, 81);
const decimal24_t windSpeed137 PROGMEM = populate_decimal(154, 94);
const decimal24_t windSpeed138 PROGMEM = populate_decimal(156, 7);
const decimal24_t windSpeed139 PROGMEM = populate_decimal(157, 20);
const decimal24_t windSpeed140 PROGMEM = populate_decimal(158, 33);
const decimal24_t windSpeed141 PROGMEM = populate_decimal(159, 46);
const decimal24_t windSpeed142 PROGMEM = populate_decimal(160, 59);
const decimal24_t windSpeed143 PROGMEM = populate_decimal(161, 72);
const decimal24_t windSpeed144 PROGMEM = populate_decimal(162, 86);
const decimal24_t windSpeed145 PROGMEM = populate_decimal(163, 99);
const decimal24_t windSpeed146 PROGMEM = populate_decimal(165, 12);
const decimal24_t windSpeed147 PROGMEM = populate_decimal(166, 25);
const decimal24_t windSpeed148 PROGMEM = populate_decimal(167, 38);
const decimal24_t windSpeed149 PROGMEM = populate_decimal(168, 51);
const decimal24_t windSpeed150 PROGMEM = populate_decimal(169, 64);
const decimal24_t windSpeed151 PROGMEM = populate_decimal(170, 77);
const decimal24_t windSpeed152 PROGMEM = populate_decimal(171, 90);
const decimal24_t windSpeed153 PROGMEM = populate_decimal(173, 3);
const decimal24_t windSpeed154 PROGMEM = populate_decimal(174, 16);
const decimal24_t windSpeed155 PROGMEM = populate_decimal(175, 30);
const decimal24_t windSpeed156 PROGMEM = populate_decimal(176, 43);
const decimal24_t windSpeed157 PROGMEM = populate_decimal(177, 56);
const decimal24_t windSpeed158 PROGMEM = populate_decimal(178, 69);
const decimal24_t windSpeed159 PROGMEM = populate_decimal(179, 82);
const decimal24_t windSpeed160 PROGMEM = populate_decimal(180, 95);
const decimal24_t windSpeed161 PROGMEM = populate_decimal(182, 8);
const decimal24_t windSpeed162 PROGMEM = populate_decimal(183, 21);
const decimal24_t windSpeed163 PROGMEM = populate_decimal(184, 34);
const decimal24_t windSpeed164 PROGMEM = populate_decimal(185, 47);
const decimal24_t windSpeed165 PROGMEM = populate_decimal(186, 61);
const decimal24_t windSpeed166 PROGMEM = populate_decimal(187, 74);
const decimal24_t windSpeed167 PROGMEM = populate_decimal(188, 87);
const decimal24_t windSpeed168 PROGMEM = populate_decimal(190, 0);
const decimal24_t windSpeed169 PROGMEM = populate_decimal(191, 13);
const decimal24_t windSpeed170 PROGMEM = populate_decimal(192, 26);
const decimal24_t windSpeed171 PROGMEM = populate_decimal(193, 39);
const decimal24_t windSpeed172 PROGMEM = populate_decimal(194, 52);
const decimal24_t windSpeed173 PROGMEM = populate_decimal(195, 65);
const decimal24_t windSpeed174 PROGMEM = populate_decimal(196, 78);
const decimal24_t windSpeed175 PROGMEM = populate_decimal(197, 92);
const decimal24_t windSpeed176 PROGMEM = populate_decimal(199, 5);
const decimal24_t windSpeed177 PROGMEM = populate_decimal(200, 18);

static PGM_VOID_P const kphLookup[KPH_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
&windSpeed0,
&windSpeed1,
&windSpeed2,
&windSpeed3,
&windSpeed4,
&windSpeed5,
&windSpeed6,
&windSpeed7,
&windSpeed8,
&windSpeed9,
&windSpeed10,
&windSpeed11,
&windSpeed12,
&windSpeed13,
&windSpeed14,
&windSpeed15,
&windSpeed16,
&windSpeed17,
&windSpeed18,
&windSpeed19,
&windSpeed20,
&windSpeed21,
&windSpeed22,
&windSpeed23,
&windSpeed24,
&windSpeed25,
&windSpeed26,
&windSpeed27,
&windSpeed28,
&windSpeed29,
&windSpeed30,
&windSpeed31,
&windSpeed32,
&windSpeed33,
&windSpeed34,
&windSpeed35,
&windSpeed36,
&windSpeed37,
&windSpeed38,
&windSpeed39,
&windSpeed40,
&windSpeed41,
&windSpeed42,
&windSpeed43,
&windSpeed44,
&windSpeed45,
&windSpeed46,
&windSpeed47,
&windSpeed48,
&windSpeed49,
&windSpeed50,
&windSpeed51,
&windSpeed52,
&windSpeed53,
&windSpeed54,
&windSpeed55,
&windSpeed56,
&windSpeed57,
&windSpeed58,
&windSpeed59,
&windSpeed60,
&windSpeed61,
&windSpeed62,
&windSpeed63,
&windSpeed64,
&windSpeed65,
&windSpeed66,
&windSpeed67,
&windSpeed68,
&windSpeed69,
&windSpeed70,
&windSpeed71,
&windSpeed72,
&windSpeed73,
&windSpeed74,
&windSpeed75,
&windSpeed76,
&windSpeed77,
&windSpeed78,
&windSpeed79,
&windSpeed80,
&windSpeed81,
&windSpeed82,
&windSpeed83,
&windSpeed84,
&windSpeed85,
&windSpeed86,
&windSpeed87,
&windSpeed88,
&windSpeed89,
&windSpeed90,
&windSpeed91,
&windSpeed92,
&windSpeed93,
&windSpeed94,
&windSpeed95,
&windSpeed96,
&windSpeed97,
&windSpeed98,
&windSpeed99,
&windSpeed100,
&windSpeed101,
&windSpeed102,
&windSpeed103,
&windSpeed104,
&windSpeed105,
&windSpeed106,
&windSpeed107,
&windSpeed108,
&windSpeed109,
&windSpeed110,
&windSpeed111,
&windSpeed112,
&windSpeed113,
&windSpeed114,
&windSpeed115,
&windSpeed116,
&windSpeed117,
&windSpeed118,
&windSpeed119,
&windSpeed120,
&windSpeed121,
&windSpeed122,
&windSpeed123,
&windSpeed124,
&windSpeed125,
&windSpeed126,
&windSpeed127,
&windSpeed128,
&windSpeed129,
&windSpeed130,
&windSpeed131,
&windSpeed132,
&windSpeed133,
&windSpeed134,
&windSpeed135,
&windSpeed136,
&windSpeed137,
&windSpeed138,
&windSpeed139,
&windSpeed140,
&windSpeed141,
&windSpeed142,
&windSpeed143,
&windSpeed144,
&windSpeed145,
&windSpeed146,
&windSpeed147,
&windSpeed148,
&windSpeed149,
&windSpeed150,
&windSpeed151,
&windSpeed152,
&windSpeed153,
&windSpeed154,
&windSpeed155,
&windSpeed156,
&windSpeed157,
&windSpeed158,
&windSpeed159,
&windSpeed160,
&windSpeed161,
&windSpeed162,
&windSpeed163,
&windSpeed164,
&windSpeed165,
&windSpeed166,
&windSpeed167,
&windSpeed168,
&windSpeed169,
&windSpeed170,
&windSpeed171,
&windSpeed172,
&windSpeed173,
&windSpeed174,
&windSpeed175,
&windSpeed176,
&windSpeed177
};

#endif
