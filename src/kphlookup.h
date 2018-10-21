#include <avr/pgmspace.h>

#ifndef _INCL_KPHLOOKUP
#define _INCL_KPHLOOKUP

#define KPH_LOOKUP_BUFFER_SIZE			178

/*
** The diameter of the anemometer blades in metres...
*/
#define BLADE_DIAMETER					 0.1

#define RPS_TO_KPH_SCALE_FACTOR			((3.14159265 * BLADE_DIAMETER * 3600) / 1000)

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
const char windSpeed0[] PROGMEM = "0.00";
const char windSpeed1[] PROGMEM = "1.13";
const char windSpeed2[] PROGMEM = "2.26";
const char windSpeed3[] PROGMEM = "3.39";
const char windSpeed4[] PROGMEM = "4.52";
const char windSpeed5[] PROGMEM = "5.65";
const char windSpeed6[] PROGMEM = "6.79";
const char windSpeed7[] PROGMEM = "7.92";
const char windSpeed8[] PROGMEM = "9.05";
const char windSpeed9[] PROGMEM = "10.18";
const char windSpeed10[] PROGMEM = "11.31";
const char windSpeed11[] PROGMEM = "12.44";
const char windSpeed12[] PROGMEM = "13.57";
const char windSpeed13[] PROGMEM = "14.70";
const char windSpeed14[] PROGMEM = "15.83";
const char windSpeed15[] PROGMEM = "16.96";
const char windSpeed16[] PROGMEM = "18.10";
const char windSpeed17[] PROGMEM = "19.23";
const char windSpeed18[] PROGMEM = "20.36";
const char windSpeed19[] PROGMEM = "21.49";
const char windSpeed20[] PROGMEM = "22.62";
const char windSpeed21[] PROGMEM = "23.75";
const char windSpeed22[] PROGMEM = "24.88";
const char windSpeed23[] PROGMEM = "26.01";
const char windSpeed24[] PROGMEM = "27.14";
const char windSpeed25[] PROGMEM = "28.27";
const char windSpeed26[] PROGMEM = "29.41";
const char windSpeed27[] PROGMEM = "30.54";
const char windSpeed28[] PROGMEM = "31.67";
const char windSpeed29[] PROGMEM = "32.80";
const char windSpeed30[] PROGMEM = "33.93";
const char windSpeed31[] PROGMEM = "35.06";
const char windSpeed32[] PROGMEM = "36.19";
const char windSpeed33[] PROGMEM = "37.32";
const char windSpeed34[] PROGMEM = "38.45";
const char windSpeed35[] PROGMEM = "39.58";
const char windSpeed36[] PROGMEM = "40.72";
const char windSpeed37[] PROGMEM = "41.85";
const char windSpeed38[] PROGMEM = "42.98";
const char windSpeed39[] PROGMEM = "44.11";
const char windSpeed40[] PROGMEM = "45.24";
const char windSpeed41[] PROGMEM = "46.37";
const char windSpeed42[] PROGMEM = "47.50";
const char windSpeed43[] PROGMEM = "48.63";
const char windSpeed44[] PROGMEM = "49.76";
const char windSpeed45[] PROGMEM = "50.89";
const char windSpeed46[] PROGMEM = "52.02";
const char windSpeed47[] PROGMEM = "53.16";
const char windSpeed48[] PROGMEM = "54.29";
const char windSpeed49[] PROGMEM = "55.42";
const char windSpeed50[] PROGMEM = "56.55";
const char windSpeed51[] PROGMEM = "57.68";
const char windSpeed52[] PROGMEM = "58.81";
const char windSpeed53[] PROGMEM = "59.94";
const char windSpeed54[] PROGMEM = "61.07";
const char windSpeed55[] PROGMEM = "62.20";
const char windSpeed56[] PROGMEM = "63.33";
const char windSpeed57[] PROGMEM = "64.47";
const char windSpeed58[] PROGMEM = "65.60";
const char windSpeed59[] PROGMEM = "66.73";
const char windSpeed60[] PROGMEM = "67.86";
const char windSpeed61[] PROGMEM = "68.99";
const char windSpeed62[] PROGMEM = "70.12";
const char windSpeed63[] PROGMEM = "71.25";
const char windSpeed64[] PROGMEM = "72.38";
const char windSpeed65[] PROGMEM = "73.51";
const char windSpeed66[] PROGMEM = "74.64";
const char windSpeed67[] PROGMEM = "75.78";
const char windSpeed68[] PROGMEM = "76.91";
const char windSpeed69[] PROGMEM = "78.04";
const char windSpeed70[] PROGMEM = "79.17";
const char windSpeed71[] PROGMEM = "80.30";
const char windSpeed72[] PROGMEM = "81.43";
const char windSpeed73[] PROGMEM = "82.56";
const char windSpeed74[] PROGMEM = "83.69";
const char windSpeed75[] PROGMEM = "84.82";
const char windSpeed76[] PROGMEM = "85.95";
const char windSpeed77[] PROGMEM = "87.08";
const char windSpeed78[] PROGMEM = "88.22";
const char windSpeed79[] PROGMEM = "89.35";
const char windSpeed80[] PROGMEM = "90.48";
const char windSpeed81[] PROGMEM = "91.61";
const char windSpeed82[] PROGMEM = "92.74";
const char windSpeed83[] PROGMEM = "93.87";
const char windSpeed84[] PROGMEM = "95.00";
const char windSpeed85[] PROGMEM = "96.13";
const char windSpeed86[] PROGMEM = "97.26";
const char windSpeed87[] PROGMEM = "98.39";
const char windSpeed88[] PROGMEM = "99.53";
const char windSpeed89[] PROGMEM = "100.66";
const char windSpeed90[] PROGMEM = "101.79";
const char windSpeed91[] PROGMEM = "102.92";
const char windSpeed92[] PROGMEM = "104.05";
const char windSpeed93[] PROGMEM = "105.18";
const char windSpeed94[] PROGMEM = "106.31";
const char windSpeed95[] PROGMEM = "107.44";
const char windSpeed96[] PROGMEM = "108.57";
const char windSpeed97[] PROGMEM = "109.70";
const char windSpeed98[] PROGMEM = "110.84";
const char windSpeed99[] PROGMEM = "111.97";
const char windSpeed100[] PROGMEM = "113.10";
const char windSpeed101[] PROGMEM = "114.23";
const char windSpeed102[] PROGMEM = "115.36";
const char windSpeed103[] PROGMEM = "116.49";
const char windSpeed104[] PROGMEM = "117.62";
const char windSpeed105[] PROGMEM = "118.75";
const char windSpeed106[] PROGMEM = "119.88";
const char windSpeed107[] PROGMEM = "121.01";
const char windSpeed108[] PROGMEM = "122.15";
const char windSpeed109[] PROGMEM = "123.28";
const char windSpeed110[] PROGMEM = "124.41";
const char windSpeed111[] PROGMEM = "125.54";
const char windSpeed112[] PROGMEM = "126.67";
const char windSpeed113[] PROGMEM = "127.80";
const char windSpeed114[] PROGMEM = "128.93";
const char windSpeed115[] PROGMEM = "130.06";
const char windSpeed116[] PROGMEM = "131.19";
const char windSpeed117[] PROGMEM = "132.32";
const char windSpeed118[] PROGMEM = "133.45";
const char windSpeed119[] PROGMEM = "134.59";
const char windSpeed120[] PROGMEM = "135.72";
const char windSpeed121[] PROGMEM = "136.85";
const char windSpeed122[] PROGMEM = "137.98";
const char windSpeed123[] PROGMEM = "139.11";
const char windSpeed124[] PROGMEM = "140.24";
const char windSpeed125[] PROGMEM = "141.37";
const char windSpeed126[] PROGMEM = "142.50";
const char windSpeed127[] PROGMEM = "143.63";
const char windSpeed128[] PROGMEM = "144.76";
const char windSpeed129[] PROGMEM = "145.90";
const char windSpeed130[] PROGMEM = "147.03";
const char windSpeed131[] PROGMEM = "148.16";
const char windSpeed132[] PROGMEM = "149.29";
const char windSpeed133[] PROGMEM = "150.42";
const char windSpeed134[] PROGMEM = "151.55";
const char windSpeed135[] PROGMEM = "152.68";
const char windSpeed136[] PROGMEM = "153.81";
const char windSpeed137[] PROGMEM = "154.94";
const char windSpeed138[] PROGMEM = "156.07";
const char windSpeed139[] PROGMEM = "157.21";
const char windSpeed140[] PROGMEM = "158.34";
const char windSpeed141[] PROGMEM = "159.47";
const char windSpeed142[] PROGMEM = "160.60";
const char windSpeed143[] PROGMEM = "161.73";
const char windSpeed144[] PROGMEM = "162.86";
const char windSpeed145[] PROGMEM = "163.99";
const char windSpeed146[] PROGMEM = "165.12";
const char windSpeed147[] PROGMEM = "166.25";
const char windSpeed148[] PROGMEM = "167.38";
const char windSpeed149[] PROGMEM = "168.52";
const char windSpeed150[] PROGMEM = "169.65";
const char windSpeed151[] PROGMEM = "170.78";
const char windSpeed152[] PROGMEM = "171.91";
const char windSpeed153[] PROGMEM = "173.04";
const char windSpeed154[] PROGMEM = "174.17";
const char windSpeed155[] PROGMEM = "175.30";
const char windSpeed156[] PROGMEM = "176.43";
const char windSpeed157[] PROGMEM = "177.56";
const char windSpeed158[] PROGMEM = "178.69";
const char windSpeed159[] PROGMEM = "179.82";
const char windSpeed160[] PROGMEM = "180.96";
const char windSpeed161[] PROGMEM = "182.09";
const char windSpeed162[] PROGMEM = "183.22";
const char windSpeed163[] PROGMEM = "184.35";
const char windSpeed164[] PROGMEM = "185.48";
const char windSpeed165[] PROGMEM = "186.61";
const char windSpeed166[] PROGMEM = "187.74";
const char windSpeed167[] PROGMEM = "188.87";
const char windSpeed168[] PROGMEM = "190.00";
const char windSpeed169[] PROGMEM = "191.13";
const char windSpeed170[] PROGMEM = "192.27";
const char windSpeed171[] PROGMEM = "193.40";
const char windSpeed172[] PROGMEM = "194.53";
const char windSpeed173[] PROGMEM = "195.66";
const char windSpeed174[] PROGMEM = "196.79";
const char windSpeed175[] PROGMEM = "197.92";
const char windSpeed176[] PROGMEM = "199.05";
const char windSpeed177[] PROGMEM = "200.18";

static PGM_P const kphLookup[KPH_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
windSpeed0,
windSpeed1,
windSpeed2,
windSpeed3,
windSpeed4,
windSpeed5,
windSpeed6,
windSpeed7,
windSpeed8,
windSpeed9,
windSpeed10,
windSpeed11,
windSpeed12,
windSpeed13,
windSpeed14,
windSpeed15,
windSpeed16,
windSpeed17,
windSpeed18,
windSpeed19,
windSpeed20,
windSpeed21,
windSpeed22,
windSpeed23,
windSpeed24,
windSpeed25,
windSpeed26,
windSpeed27,
windSpeed28,
windSpeed29,
windSpeed30,
windSpeed31,
windSpeed32,
windSpeed33,
windSpeed34,
windSpeed35,
windSpeed36,
windSpeed37,
windSpeed38,
windSpeed39,
windSpeed40,
windSpeed41,
windSpeed42,
windSpeed43,
windSpeed44,
windSpeed45,
windSpeed46,
windSpeed47,
windSpeed48,
windSpeed49,
windSpeed50,
windSpeed51,
windSpeed52,
windSpeed53,
windSpeed54,
windSpeed55,
windSpeed56,
windSpeed57,
windSpeed58,
windSpeed59,
windSpeed60,
windSpeed61,
windSpeed62,
windSpeed63,
windSpeed64,
windSpeed65,
windSpeed66,
windSpeed67,
windSpeed68,
windSpeed69,
windSpeed70,
windSpeed71,
windSpeed72,
windSpeed73,
windSpeed74,
windSpeed75,
windSpeed76,
windSpeed77,
windSpeed78,
windSpeed79,
windSpeed80,
windSpeed81,
windSpeed82,
windSpeed83,
windSpeed84,
windSpeed85,
windSpeed86,
windSpeed87,
windSpeed88,
windSpeed89,
windSpeed90,
windSpeed91,
windSpeed92,
windSpeed93,
windSpeed94,
windSpeed95,
windSpeed96,
windSpeed97,
windSpeed98,
windSpeed99,
windSpeed100,
windSpeed101,
windSpeed102,
windSpeed103,
windSpeed104,
windSpeed105,
windSpeed106,
windSpeed107,
windSpeed108,
windSpeed109,
windSpeed110,
windSpeed111,
windSpeed112,
windSpeed113,
windSpeed114,
windSpeed115,
windSpeed116,
windSpeed117,
windSpeed118,
windSpeed119,
windSpeed120,
windSpeed121,
windSpeed122,
windSpeed123,
windSpeed124,
windSpeed125,
windSpeed126,
windSpeed127,
windSpeed128,
windSpeed129,
windSpeed130,
windSpeed131,
windSpeed132,
windSpeed133,
windSpeed134,
windSpeed135,
windSpeed136,
windSpeed137,
windSpeed138,
windSpeed139,
windSpeed140,
windSpeed141,
windSpeed142,
windSpeed143,
windSpeed144,
windSpeed145,
windSpeed146,
windSpeed147,
windSpeed148,
windSpeed149,
windSpeed150,
windSpeed151,
windSpeed152,
windSpeed153,
windSpeed154,
windSpeed155,
windSpeed156,
windSpeed157,
windSpeed158,
windSpeed159,
windSpeed160,
windSpeed161,
windSpeed162,
windSpeed163,
windSpeed164,
windSpeed165,
windSpeed166,
windSpeed167,
windSpeed168,
windSpeed169,
windSpeed170,
windSpeed171,
windSpeed172,
windSpeed173,
windSpeed174,
windSpeed175,
windSpeed176,
windSpeed177
};

#endif
