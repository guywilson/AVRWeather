#include <avr/pgmspace.h>

#include "types.h"

#ifndef _INCL_MBARLOOKUP
#define _INCL_MBARLOOKUP

#define MBAR_LOOKUP_BUFFER_SIZE					 276

#define ADC_MBAR_OFFSET							 686

#define ADC_MBAR_MIN							   0
#define ADC_MBAR_MAX							 275

/******************************************************************************
**
** From an ADC input linked to an NXP MPX4115A barometric pressure sensor
** with a range of 150mbar to 1150mbar, through an AD623 instrumentation
** amplifier with a gain of 4.03. The comparator input of the amp is set to
** 3.235v from a voltage divider which equates to 824.44mbar. The output
** voltage of the sensor at 1098.89mbar is 4.47v which gives a voltage range of
** 4.47v - 3.235v = 1.25v, the output from the amp will swing from 0v - 5v
** (824.44 - 1098.89mbar).
** We are only interested in atmospheric pressure in the range
** 824.44mbar to 1098.89mbar (at sea level, the lowest recorded air pressure is
** 870mbar, the highest is 1083.8mbar).
**
** The transfer function of the sensor is (pressure in kPa):
**     Vout = Vs * ((0.009 * P) - 0.095)
**
**     e.g. with a pressure of 870mbar:
**     Vout = 5 * ((0.009 * 87) - 0.095) = 3.44v
**
**     Re-arranging to get pressure in mbar:
**     Pmbar = (((Vout / 5) + 0.095) / 0.009) * 10
**
** As the output of the sensor (and therefore the amplifier) is linear, we can
** use the equation of a straight line:
**
**     y = mx + b
**
** Where y is the pressure in mbar:
**
**     y = ((1150 - 824.44) / (1212.42 - 0) * ADC) + 824.44
**     y = ((325.56 / 1212.42) * ADC) + 824.44
**
** This is an expensive operation on a microcontroller, hence we calcuate this 
** up-front and store in flash ROM.
**
** This array of const values uses the PROGMEM modifier, a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array, code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/
const decimal24_t pressure0 PROGMEM = populate_decimal(850, 64);
const decimal24_t pressure1 PROGMEM = populate_decimal(851, 72);
const decimal24_t pressure2 PROGMEM = populate_decimal(852, 81);
const decimal24_t pressure3 PROGMEM = populate_decimal(853, 89);
const decimal24_t pressure4 PROGMEM = populate_decimal(854, 98);
const decimal24_t pressure5 PROGMEM = populate_decimal(856, 7);
const decimal24_t pressure6 PROGMEM = populate_decimal(857, 15);
const decimal24_t pressure7 PROGMEM = populate_decimal(858, 24);
const decimal24_t pressure8 PROGMEM = populate_decimal(859, 32);
const decimal24_t pressure9 PROGMEM = populate_decimal(860, 41);
const decimal24_t pressure10 PROGMEM = populate_decimal(861, 50);
const decimal24_t pressure11 PROGMEM = populate_decimal(862, 58);
const decimal24_t pressure12 PROGMEM = populate_decimal(863, 67);
const decimal24_t pressure13 PROGMEM = populate_decimal(864, 76);
const decimal24_t pressure14 PROGMEM = populate_decimal(865, 84);
const decimal24_t pressure15 PROGMEM = populate_decimal(866, 93);
const decimal24_t pressure16 PROGMEM = populate_decimal(868, 1);
const decimal24_t pressure17 PROGMEM = populate_decimal(869, 10);
const decimal24_t pressure18 PROGMEM = populate_decimal(870, 19);
const decimal24_t pressure19 PROGMEM = populate_decimal(871, 27);
const decimal24_t pressure20 PROGMEM = populate_decimal(872, 36);
const decimal24_t pressure21 PROGMEM = populate_decimal(873, 44);
const decimal24_t pressure22 PROGMEM = populate_decimal(874, 53);
const decimal24_t pressure23 PROGMEM = populate_decimal(875, 62);
const decimal24_t pressure24 PROGMEM = populate_decimal(876, 70);
const decimal24_t pressure25 PROGMEM = populate_decimal(877, 79);
const decimal24_t pressure26 PROGMEM = populate_decimal(878, 88);
const decimal24_t pressure27 PROGMEM = populate_decimal(879, 96);
const decimal24_t pressure28 PROGMEM = populate_decimal(881, 5);
const decimal24_t pressure29 PROGMEM = populate_decimal(882, 13);
const decimal24_t pressure30 PROGMEM = populate_decimal(883, 22);
const decimal24_t pressure31 PROGMEM = populate_decimal(884, 31);
const decimal24_t pressure32 PROGMEM = populate_decimal(885, 39);
const decimal24_t pressure33 PROGMEM = populate_decimal(886, 48);
const decimal24_t pressure34 PROGMEM = populate_decimal(887, 56);
const decimal24_t pressure35 PROGMEM = populate_decimal(888, 65);
const decimal24_t pressure36 PROGMEM = populate_decimal(889, 74);
const decimal24_t pressure37 PROGMEM = populate_decimal(890, 82);
const decimal24_t pressure38 PROGMEM = populate_decimal(891, 91);
const decimal24_t pressure39 PROGMEM = populate_decimal(892, 99);
const decimal24_t pressure40 PROGMEM = populate_decimal(894, 8);
const decimal24_t pressure41 PROGMEM = populate_decimal(895, 17);
const decimal24_t pressure42 PROGMEM = populate_decimal(896, 25);
const decimal24_t pressure43 PROGMEM = populate_decimal(897, 34);
const decimal24_t pressure44 PROGMEM = populate_decimal(898, 43);
const decimal24_t pressure45 PROGMEM = populate_decimal(899, 51);
const decimal24_t pressure46 PROGMEM = populate_decimal(900, 60);
const decimal24_t pressure47 PROGMEM = populate_decimal(901, 68);
const decimal24_t pressure48 PROGMEM = populate_decimal(902, 77);
const decimal24_t pressure49 PROGMEM = populate_decimal(903, 86);
const decimal24_t pressure50 PROGMEM = populate_decimal(904, 94);
const decimal24_t pressure51 PROGMEM = populate_decimal(906, 3);
const decimal24_t pressure52 PROGMEM = populate_decimal(907, 11);
const decimal24_t pressure53 PROGMEM = populate_decimal(908, 20);
const decimal24_t pressure54 PROGMEM = populate_decimal(909, 29);
const decimal24_t pressure55 PROGMEM = populate_decimal(910, 37);
const decimal24_t pressure56 PROGMEM = populate_decimal(911, 46);
const decimal24_t pressure57 PROGMEM = populate_decimal(912, 55);
const decimal24_t pressure58 PROGMEM = populate_decimal(913, 63);
const decimal24_t pressure59 PROGMEM = populate_decimal(914, 72);
const decimal24_t pressure60 PROGMEM = populate_decimal(915, 80);
const decimal24_t pressure61 PROGMEM = populate_decimal(916, 89);
const decimal24_t pressure62 PROGMEM = populate_decimal(917, 98);
const decimal24_t pressure63 PROGMEM = populate_decimal(919, 6);
const decimal24_t pressure64 PROGMEM = populate_decimal(920, 15);
const decimal24_t pressure65 PROGMEM = populate_decimal(921, 23);
const decimal24_t pressure66 PROGMEM = populate_decimal(922, 32);
const decimal24_t pressure67 PROGMEM = populate_decimal(923, 41);
const decimal24_t pressure68 PROGMEM = populate_decimal(924, 49);
const decimal24_t pressure69 PROGMEM = populate_decimal(925, 58);
const decimal24_t pressure70 PROGMEM = populate_decimal(926, 66);
const decimal24_t pressure71 PROGMEM = populate_decimal(927, 75);
const decimal24_t pressure72 PROGMEM = populate_decimal(928, 84);
const decimal24_t pressure73 PROGMEM = populate_decimal(929, 92);
const decimal24_t pressure74 PROGMEM = populate_decimal(931, 1);
const decimal24_t pressure75 PROGMEM = populate_decimal(932, 10);
const decimal24_t pressure76 PROGMEM = populate_decimal(933, 18);
const decimal24_t pressure77 PROGMEM = populate_decimal(934, 27);
const decimal24_t pressure78 PROGMEM = populate_decimal(935, 35);
const decimal24_t pressure79 PROGMEM = populate_decimal(936, 44);
const decimal24_t pressure80 PROGMEM = populate_decimal(937, 53);
const decimal24_t pressure81 PROGMEM = populate_decimal(938, 61);
const decimal24_t pressure82 PROGMEM = populate_decimal(939, 70);
const decimal24_t pressure83 PROGMEM = populate_decimal(940, 78);
const decimal24_t pressure84 PROGMEM = populate_decimal(941, 87);
const decimal24_t pressure85 PROGMEM = populate_decimal(942, 96);
const decimal24_t pressure86 PROGMEM = populate_decimal(944, 4);
const decimal24_t pressure87 PROGMEM = populate_decimal(945, 13);
const decimal24_t pressure88 PROGMEM = populate_decimal(946, 22);
const decimal24_t pressure89 PROGMEM = populate_decimal(947, 30);
const decimal24_t pressure90 PROGMEM = populate_decimal(948, 39);
const decimal24_t pressure91 PROGMEM = populate_decimal(949, 47);
const decimal24_t pressure92 PROGMEM = populate_decimal(950, 56);
const decimal24_t pressure93 PROGMEM = populate_decimal(951, 65);
const decimal24_t pressure94 PROGMEM = populate_decimal(952, 73);
const decimal24_t pressure95 PROGMEM = populate_decimal(953, 82);
const decimal24_t pressure96 PROGMEM = populate_decimal(954, 90);
const decimal24_t pressure97 PROGMEM = populate_decimal(955, 99);
const decimal24_t pressure98 PROGMEM = populate_decimal(957, 8);
const decimal24_t pressure99 PROGMEM = populate_decimal(958, 16);
const decimal24_t pressure100 PROGMEM = populate_decimal(959, 25);
const decimal24_t pressure101 PROGMEM = populate_decimal(960, 33);
const decimal24_t pressure102 PROGMEM = populate_decimal(961, 42);
const decimal24_t pressure103 PROGMEM = populate_decimal(962, 51);
const decimal24_t pressure104 PROGMEM = populate_decimal(963, 59);
const decimal24_t pressure105 PROGMEM = populate_decimal(964, 68);
const decimal24_t pressure106 PROGMEM = populate_decimal(965, 77);
const decimal24_t pressure107 PROGMEM = populate_decimal(966, 85);
const decimal24_t pressure108 PROGMEM = populate_decimal(967, 94);
const decimal24_t pressure109 PROGMEM = populate_decimal(969, 2);
const decimal24_t pressure110 PROGMEM = populate_decimal(970, 11);
const decimal24_t pressure111 PROGMEM = populate_decimal(971, 20);
const decimal24_t pressure112 PROGMEM = populate_decimal(972, 28);
const decimal24_t pressure113 PROGMEM = populate_decimal(973, 37);
const decimal24_t pressure114 PROGMEM = populate_decimal(974, 45);
const decimal24_t pressure115 PROGMEM = populate_decimal(975, 54);
const decimal24_t pressure116 PROGMEM = populate_decimal(976, 63);
const decimal24_t pressure117 PROGMEM = populate_decimal(977, 71);
const decimal24_t pressure118 PROGMEM = populate_decimal(978, 80);
const decimal24_t pressure119 PROGMEM = populate_decimal(979, 89);
const decimal24_t pressure120 PROGMEM = populate_decimal(980, 97);
const decimal24_t pressure121 PROGMEM = populate_decimal(982, 6);
const decimal24_t pressure122 PROGMEM = populate_decimal(983, 14);
const decimal24_t pressure123 PROGMEM = populate_decimal(984, 23);
const decimal24_t pressure124 PROGMEM = populate_decimal(985, 32);
const decimal24_t pressure125 PROGMEM = populate_decimal(986, 40);
const decimal24_t pressure126 PROGMEM = populate_decimal(987, 49);
const decimal24_t pressure127 PROGMEM = populate_decimal(988, 57);
const decimal24_t pressure128 PROGMEM = populate_decimal(989, 66);
const decimal24_t pressure129 PROGMEM = populate_decimal(990, 75);
const decimal24_t pressure130 PROGMEM = populate_decimal(991, 83);
const decimal24_t pressure131 PROGMEM = populate_decimal(992, 92);
const decimal24_t pressure132 PROGMEM = populate_decimal(994, 0);
const decimal24_t pressure133 PROGMEM = populate_decimal(995, 9);
const decimal24_t pressure134 PROGMEM = populate_decimal(996, 18);
const decimal24_t pressure135 PROGMEM = populate_decimal(997, 26);
const decimal24_t pressure136 PROGMEM = populate_decimal(998, 35);
const decimal24_t pressure137 PROGMEM = populate_decimal(999, 44);
const decimal24_t pressure138 PROGMEM = populate_decimal(1000, 52);
const decimal24_t pressure139 PROGMEM = populate_decimal(1001, 61);
const decimal24_t pressure140 PROGMEM = populate_decimal(1002, 69);
const decimal24_t pressure141 PROGMEM = populate_decimal(1003, 78);
const decimal24_t pressure142 PROGMEM = populate_decimal(1004, 87);
const decimal24_t pressure143 PROGMEM = populate_decimal(1005, 95);
const decimal24_t pressure144 PROGMEM = populate_decimal(1007, 4);
const decimal24_t pressure145 PROGMEM = populate_decimal(1008, 12);
const decimal24_t pressure146 PROGMEM = populate_decimal(1009, 21);
const decimal24_t pressure147 PROGMEM = populate_decimal(1010, 30);
const decimal24_t pressure148 PROGMEM = populate_decimal(1011, 38);
const decimal24_t pressure149 PROGMEM = populate_decimal(1012, 47);
const decimal24_t pressure150 PROGMEM = populate_decimal(1013, 56);
const decimal24_t pressure151 PROGMEM = populate_decimal(1014, 64);
const decimal24_t pressure152 PROGMEM = populate_decimal(1015, 73);
const decimal24_t pressure153 PROGMEM = populate_decimal(1016, 81);
const decimal24_t pressure154 PROGMEM = populate_decimal(1017, 90);
const decimal24_t pressure155 PROGMEM = populate_decimal(1018, 99);
const decimal24_t pressure156 PROGMEM = populate_decimal(1020, 7);
const decimal24_t pressure157 PROGMEM = populate_decimal(1021, 16);
const decimal24_t pressure158 PROGMEM = populate_decimal(1022, 24);
const decimal24_t pressure159 PROGMEM = populate_decimal(1023, 33);
const decimal24_t pressure160 PROGMEM = populate_decimal(1024, 42);
const decimal24_t pressure161 PROGMEM = populate_decimal(1025, 50);
const decimal24_t pressure162 PROGMEM = populate_decimal(1026, 59);
const decimal24_t pressure163 PROGMEM = populate_decimal(1027, 68);
const decimal24_t pressure164 PROGMEM = populate_decimal(1028, 76);
const decimal24_t pressure165 PROGMEM = populate_decimal(1029, 85);
const decimal24_t pressure166 PROGMEM = populate_decimal(1030, 93);
const decimal24_t pressure167 PROGMEM = populate_decimal(1032, 2);
const decimal24_t pressure168 PROGMEM = populate_decimal(1033, 11);
const decimal24_t pressure169 PROGMEM = populate_decimal(1034, 19);
const decimal24_t pressure170 PROGMEM = populate_decimal(1035, 28);
const decimal24_t pressure171 PROGMEM = populate_decimal(1036, 36);
const decimal24_t pressure172 PROGMEM = populate_decimal(1037, 45);
const decimal24_t pressure173 PROGMEM = populate_decimal(1038, 54);
const decimal24_t pressure174 PROGMEM = populate_decimal(1039, 62);
const decimal24_t pressure175 PROGMEM = populate_decimal(1040, 71);
const decimal24_t pressure176 PROGMEM = populate_decimal(1041, 79);
const decimal24_t pressure177 PROGMEM = populate_decimal(1042, 88);
const decimal24_t pressure178 PROGMEM = populate_decimal(1043, 97);
const decimal24_t pressure179 PROGMEM = populate_decimal(1045, 5);
const decimal24_t pressure180 PROGMEM = populate_decimal(1046, 14);
const decimal24_t pressure181 PROGMEM = populate_decimal(1047, 23);
const decimal24_t pressure182 PROGMEM = populate_decimal(1048, 31);
const decimal24_t pressure183 PROGMEM = populate_decimal(1049, 40);
const decimal24_t pressure184 PROGMEM = populate_decimal(1050, 48);
const decimal24_t pressure185 PROGMEM = populate_decimal(1051, 57);
const decimal24_t pressure186 PROGMEM = populate_decimal(1052, 66);
const decimal24_t pressure187 PROGMEM = populate_decimal(1053, 74);
const decimal24_t pressure188 PROGMEM = populate_decimal(1054, 83);
const decimal24_t pressure189 PROGMEM = populate_decimal(1055, 91);
const decimal24_t pressure190 PROGMEM = populate_decimal(1057, 0);
const decimal24_t pressure191 PROGMEM = populate_decimal(1058, 9);
const decimal24_t pressure192 PROGMEM = populate_decimal(1059, 17);
const decimal24_t pressure193 PROGMEM = populate_decimal(1060, 26);
const decimal24_t pressure194 PROGMEM = populate_decimal(1061, 35);
const decimal24_t pressure195 PROGMEM = populate_decimal(1062, 43);
const decimal24_t pressure196 PROGMEM = populate_decimal(1063, 52);
const decimal24_t pressure197 PROGMEM = populate_decimal(1064, 60);
const decimal24_t pressure198 PROGMEM = populate_decimal(1065, 69);
const decimal24_t pressure199 PROGMEM = populate_decimal(1066, 78);
const decimal24_t pressure200 PROGMEM = populate_decimal(1067, 86);
const decimal24_t pressure201 PROGMEM = populate_decimal(1068, 95);
const decimal24_t pressure202 PROGMEM = populate_decimal(1070, 3);
const decimal24_t pressure203 PROGMEM = populate_decimal(1071, 12);
const decimal24_t pressure204 PROGMEM = populate_decimal(1072, 21);
const decimal24_t pressure205 PROGMEM = populate_decimal(1073, 29);
const decimal24_t pressure206 PROGMEM = populate_decimal(1074, 38);
const decimal24_t pressure207 PROGMEM = populate_decimal(1075, 46);
const decimal24_t pressure208 PROGMEM = populate_decimal(1076, 55);
const decimal24_t pressure209 PROGMEM = populate_decimal(1077, 64);
const decimal24_t pressure210 PROGMEM = populate_decimal(1078, 72);
const decimal24_t pressure211 PROGMEM = populate_decimal(1079, 81);
const decimal24_t pressure212 PROGMEM = populate_decimal(1080, 90);
const decimal24_t pressure213 PROGMEM = populate_decimal(1081, 98);
const decimal24_t pressure214 PROGMEM = populate_decimal(1083, 7);
const decimal24_t pressure215 PROGMEM = populate_decimal(1084, 15);
const decimal24_t pressure216 PROGMEM = populate_decimal(1085, 24);
const decimal24_t pressure217 PROGMEM = populate_decimal(1086, 33);
const decimal24_t pressure218 PROGMEM = populate_decimal(1087, 41);
const decimal24_t pressure219 PROGMEM = populate_decimal(1088, 50);
const decimal24_t pressure220 PROGMEM = populate_decimal(1089, 58);
const decimal24_t pressure221 PROGMEM = populate_decimal(1090, 67);
const decimal24_t pressure222 PROGMEM = populate_decimal(1091, 76);
const decimal24_t pressure223 PROGMEM = populate_decimal(1092, 84);
const decimal24_t pressure224 PROGMEM = populate_decimal(1093, 93);
const decimal24_t pressure225 PROGMEM = populate_decimal(1095, 2);
const decimal24_t pressure226 PROGMEM = populate_decimal(1096, 10);
const decimal24_t pressure227 PROGMEM = populate_decimal(1097, 19);
const decimal24_t pressure228 PROGMEM = populate_decimal(1098, 27);
const decimal24_t pressure229 PROGMEM = populate_decimal(1099, 36);
const decimal24_t pressure230 PROGMEM = populate_decimal(1100, 45);
const decimal24_t pressure231 PROGMEM = populate_decimal(1101, 53);
const decimal24_t pressure232 PROGMEM = populate_decimal(1102, 62);
const decimal24_t pressure233 PROGMEM = populate_decimal(1103, 70);
const decimal24_t pressure234 PROGMEM = populate_decimal(1104, 79);
const decimal24_t pressure235 PROGMEM = populate_decimal(1105, 88);
const decimal24_t pressure236 PROGMEM = populate_decimal(1106, 96);
const decimal24_t pressure237 PROGMEM = populate_decimal(1108, 5);
const decimal24_t pressure238 PROGMEM = populate_decimal(1109, 13);
const decimal24_t pressure239 PROGMEM = populate_decimal(1110, 22);
const decimal24_t pressure240 PROGMEM = populate_decimal(1111, 31);
const decimal24_t pressure241 PROGMEM = populate_decimal(1112, 39);
const decimal24_t pressure242 PROGMEM = populate_decimal(1113, 48);
const decimal24_t pressure243 PROGMEM = populate_decimal(1114, 57);
const decimal24_t pressure244 PROGMEM = populate_decimal(1115, 65);
const decimal24_t pressure245 PROGMEM = populate_decimal(1116, 74);
const decimal24_t pressure246 PROGMEM = populate_decimal(1117, 82);
const decimal24_t pressure247 PROGMEM = populate_decimal(1118, 91);
const decimal24_t pressure248 PROGMEM = populate_decimal(1120, 0);
const decimal24_t pressure249 PROGMEM = populate_decimal(1121, 8);
const decimal24_t pressure250 PROGMEM = populate_decimal(1122, 17);
const decimal24_t pressure251 PROGMEM = populate_decimal(1123, 25);
const decimal24_t pressure252 PROGMEM = populate_decimal(1124, 34);
const decimal24_t pressure253 PROGMEM = populate_decimal(1125, 43);
const decimal24_t pressure254 PROGMEM = populate_decimal(1126, 51);
const decimal24_t pressure255 PROGMEM = populate_decimal(1127, 60);
const decimal24_t pressure256 PROGMEM = populate_decimal(1128, 69);
const decimal24_t pressure257 PROGMEM = populate_decimal(1129, 77);
const decimal24_t pressure258 PROGMEM = populate_decimal(1130, 86);
const decimal24_t pressure259 PROGMEM = populate_decimal(1131, 94);
const decimal24_t pressure260 PROGMEM = populate_decimal(1133, 3);
const decimal24_t pressure261 PROGMEM = populate_decimal(1134, 12);
const decimal24_t pressure262 PROGMEM = populate_decimal(1135, 20);
const decimal24_t pressure263 PROGMEM = populate_decimal(1136, 29);
const decimal24_t pressure264 PROGMEM = populate_decimal(1137, 37);
const decimal24_t pressure265 PROGMEM = populate_decimal(1138, 46);
const decimal24_t pressure266 PROGMEM = populate_decimal(1139, 55);
const decimal24_t pressure267 PROGMEM = populate_decimal(1140, 63);
const decimal24_t pressure268 PROGMEM = populate_decimal(1141, 72);
const decimal24_t pressure269 PROGMEM = populate_decimal(1142, 80);
const decimal24_t pressure270 PROGMEM = populate_decimal(1143, 89);
const decimal24_t pressure271 PROGMEM = populate_decimal(1144, 98);
const decimal24_t pressure272 PROGMEM = populate_decimal(1146, 6);
const decimal24_t pressure273 PROGMEM = populate_decimal(1147, 15);
const decimal24_t pressure274 PROGMEM = populate_decimal(1148, 24);
const decimal24_t pressure275 PROGMEM = populate_decimal(1149, 32);

static PGM_VOID_P const mbarLookup[MBAR_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
&pressure0,
&pressure1,
&pressure2,
&pressure3,
&pressure4,
&pressure5,
&pressure6,
&pressure7,
&pressure8,
&pressure9,
&pressure10,
&pressure11,
&pressure12,
&pressure13,
&pressure14,
&pressure15,
&pressure16,
&pressure17,
&pressure18,
&pressure19,
&pressure20,
&pressure21,
&pressure22,
&pressure23,
&pressure24,
&pressure25,
&pressure26,
&pressure27,
&pressure28,
&pressure29,
&pressure30,
&pressure31,
&pressure32,
&pressure33,
&pressure34,
&pressure35,
&pressure36,
&pressure37,
&pressure38,
&pressure39,
&pressure40,
&pressure41,
&pressure42,
&pressure43,
&pressure44,
&pressure45,
&pressure46,
&pressure47,
&pressure48,
&pressure49,
&pressure50,
&pressure51,
&pressure52,
&pressure53,
&pressure54,
&pressure55,
&pressure56,
&pressure57,
&pressure58,
&pressure59,
&pressure60,
&pressure61,
&pressure62,
&pressure63,
&pressure64,
&pressure65,
&pressure66,
&pressure67,
&pressure68,
&pressure69,
&pressure70,
&pressure71,
&pressure72,
&pressure73,
&pressure74,
&pressure75,
&pressure76,
&pressure77,
&pressure78,
&pressure79,
&pressure80,
&pressure81,
&pressure82,
&pressure83,
&pressure84,
&pressure85,
&pressure86,
&pressure87,
&pressure88,
&pressure89,
&pressure90,
&pressure91,
&pressure92,
&pressure93,
&pressure94,
&pressure95,
&pressure96,
&pressure97,
&pressure98,
&pressure99,
&pressure100,
&pressure101,
&pressure102,
&pressure103,
&pressure104,
&pressure105,
&pressure106,
&pressure107,
&pressure108,
&pressure109,
&pressure110,
&pressure111,
&pressure112,
&pressure113,
&pressure114,
&pressure115,
&pressure116,
&pressure117,
&pressure118,
&pressure119,
&pressure120,
&pressure121,
&pressure122,
&pressure123,
&pressure124,
&pressure125,
&pressure126,
&pressure127,
&pressure128,
&pressure129,
&pressure130,
&pressure131,
&pressure132,
&pressure133,
&pressure134,
&pressure135,
&pressure136,
&pressure137,
&pressure138,
&pressure139,
&pressure140,
&pressure141,
&pressure142,
&pressure143,
&pressure144,
&pressure145,
&pressure146,
&pressure147,
&pressure148,
&pressure149,
&pressure150,
&pressure151,
&pressure152,
&pressure153,
&pressure154,
&pressure155,
&pressure156,
&pressure157,
&pressure158,
&pressure159,
&pressure160,
&pressure161,
&pressure162,
&pressure163,
&pressure164,
&pressure165,
&pressure166,
&pressure167,
&pressure168,
&pressure169,
&pressure170,
&pressure171,
&pressure172,
&pressure173,
&pressure174,
&pressure175,
&pressure176,
&pressure177,
&pressure178,
&pressure179,
&pressure180,
&pressure181,
&pressure182,
&pressure183,
&pressure184,
&pressure185,
&pressure186,
&pressure187,
&pressure188,
&pressure189,
&pressure190,
&pressure191,
&pressure192,
&pressure193,
&pressure194,
&pressure195,
&pressure196,
&pressure197,
&pressure198,
&pressure199,
&pressure200,
&pressure201,
&pressure202,
&pressure203,
&pressure204,
&pressure205,
&pressure206,
&pressure207,
&pressure208,
&pressure209,
&pressure210,
&pressure211,
&pressure212,
&pressure213,
&pressure214,
&pressure215,
&pressure216,
&pressure217,
&pressure218,
&pressure219,
&pressure220,
&pressure221,
&pressure222,
&pressure223,
&pressure224,
&pressure225,
&pressure226,
&pressure227,
&pressure228,
&pressure229,
&pressure230,
&pressure231,
&pressure232,
&pressure233,
&pressure234,
&pressure235,
&pressure236,
&pressure237,
&pressure238,
&pressure239,
&pressure240,
&pressure241,
&pressure242,
&pressure243,
&pressure244,
&pressure245,
&pressure246,
&pressure247,
&pressure248,
&pressure249,
&pressure250,
&pressure251,
&pressure252,
&pressure253,
&pressure254,
&pressure255,
&pressure256,
&pressure257,
&pressure258,
&pressure259,
&pressure260,
&pressure261,
&pressure262,
&pressure263,
&pressure264,
&pressure265,
&pressure266,
&pressure267,
&pressure268,
&pressure269,
&pressure270,
&pressure271,
&pressure272,
&pressure273,
&pressure274,
&pressure275
};

#endif
