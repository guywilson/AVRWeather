#include <avr/pgmspace.h>

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
const char rainfall0[] PROGMEM = "0.00";
const char rainfall1[] PROGMEM = "0.22";
const char rainfall2[] PROGMEM = "0.45";
const char rainfall3[] PROGMEM = "0.67";
const char rainfall4[] PROGMEM = "0.89";
const char rainfall5[] PROGMEM = "1.11";
const char rainfall6[] PROGMEM = "1.34";
const char rainfall7[] PROGMEM = "1.56";
const char rainfall8[] PROGMEM = "1.78";
const char rainfall9[] PROGMEM = "2.01";
const char rainfall10[] PROGMEM = "2.23";
const char rainfall11[] PROGMEM = "2.45";
const char rainfall12[] PROGMEM = "2.67";
const char rainfall13[] PROGMEM = "2.90";
const char rainfall14[] PROGMEM = "3.12";
const char rainfall15[] PROGMEM = "3.34";
const char rainfall16[] PROGMEM = "3.57";
const char rainfall17[] PROGMEM = "3.79";
const char rainfall18[] PROGMEM = "4.01";
const char rainfall19[] PROGMEM = "4.23";
const char rainfall20[] PROGMEM = "4.46";
const char rainfall21[] PROGMEM = "4.68";
const char rainfall22[] PROGMEM = "4.90";
const char rainfall23[] PROGMEM = "5.12";
const char rainfall24[] PROGMEM = "5.35";
const char rainfall25[] PROGMEM = "5.57";
const char rainfall26[] PROGMEM = "5.79";
const char rainfall27[] PROGMEM = "6.02";
const char rainfall28[] PROGMEM = "6.24";
const char rainfall29[] PROGMEM = "6.46";
const char rainfall30[] PROGMEM = "6.68";
const char rainfall31[] PROGMEM = "6.91";
const char rainfall32[] PROGMEM = "7.13";
const char rainfall33[] PROGMEM = "7.35";
const char rainfall34[] PROGMEM = "7.58";
const char rainfall35[] PROGMEM = "7.80";
const char rainfall36[] PROGMEM = "8.02";
const char rainfall37[] PROGMEM = "8.24";
const char rainfall38[] PROGMEM = "8.47";
const char rainfall39[] PROGMEM = "8.69";
const char rainfall40[] PROGMEM = "8.91";
const char rainfall41[] PROGMEM = "9.14";
const char rainfall42[] PROGMEM = "9.36";
const char rainfall43[] PROGMEM = "9.58";
const char rainfall44[] PROGMEM = "9.80";
const char rainfall45[] PROGMEM = "10.03";
const char rainfall46[] PROGMEM = "10.25";
const char rainfall47[] PROGMEM = "10.47";
const char rainfall48[] PROGMEM = "10.70";
const char rainfall49[] PROGMEM = "10.92";
const char rainfall50[] PROGMEM = "11.14";
const char rainfall51[] PROGMEM = "11.36";
const char rainfall52[] PROGMEM = "11.59";
const char rainfall53[] PROGMEM = "11.81";
const char rainfall54[] PROGMEM = "12.03";
const char rainfall55[] PROGMEM = "12.25";
const char rainfall56[] PROGMEM = "12.48";
const char rainfall57[] PROGMEM = "12.70";
const char rainfall58[] PROGMEM = "12.92";
const char rainfall59[] PROGMEM = "13.15";
const char rainfall60[] PROGMEM = "13.37";
const char rainfall61[] PROGMEM = "13.59";
const char rainfall62[] PROGMEM = "13.81";
const char rainfall63[] PROGMEM = "14.04";
const char rainfall64[] PROGMEM = "14.26";
const char rainfall65[] PROGMEM = "14.48";
const char rainfall66[] PROGMEM = "14.71";
const char rainfall67[] PROGMEM = "14.93";
const char rainfall68[] PROGMEM = "15.15";
const char rainfall69[] PROGMEM = "15.37";
const char rainfall70[] PROGMEM = "15.60";
const char rainfall71[] PROGMEM = "15.82";
const char rainfall72[] PROGMEM = "16.04";
const char rainfall73[] PROGMEM = "16.27";
const char rainfall74[] PROGMEM = "16.49";
const char rainfall75[] PROGMEM = "16.71";
const char rainfall76[] PROGMEM = "16.93";
const char rainfall77[] PROGMEM = "17.16";
const char rainfall78[] PROGMEM = "17.38";
const char rainfall79[] PROGMEM = "17.60";
const char rainfall80[] PROGMEM = "17.83";
const char rainfall81[] PROGMEM = "18.05";
const char rainfall82[] PROGMEM = "18.27";
const char rainfall83[] PROGMEM = "18.49";
const char rainfall84[] PROGMEM = "18.72";
const char rainfall85[] PROGMEM = "18.94";
const char rainfall86[] PROGMEM = "19.16";
const char rainfall87[] PROGMEM = "19.39";
const char rainfall88[] PROGMEM = "19.61";
const char rainfall89[] PROGMEM = "19.83";
const char rainfall90[] PROGMEM = "20.05";
const char rainfall91[] PROGMEM = "20.28";
const char rainfall92[] PROGMEM = "20.50";
const char rainfall93[] PROGMEM = "20.72";
const char rainfall94[] PROGMEM = "20.94";
const char rainfall95[] PROGMEM = "21.17";
const char rainfall96[] PROGMEM = "21.39";
const char rainfall97[] PROGMEM = "21.61";
const char rainfall98[] PROGMEM = "21.84";
const char rainfall99[] PROGMEM = "22.06";
const char rainfall100[] PROGMEM = "22.28";
const char rainfall101[] PROGMEM = "22.50";
const char rainfall102[] PROGMEM = "22.73";
const char rainfall103[] PROGMEM = "22.95";
const char rainfall104[] PROGMEM = "23.17";
const char rainfall105[] PROGMEM = "23.40";
const char rainfall106[] PROGMEM = "23.62";
const char rainfall107[] PROGMEM = "23.84";
const char rainfall108[] PROGMEM = "24.06";
const char rainfall109[] PROGMEM = "24.29";
const char rainfall110[] PROGMEM = "24.51";
const char rainfall111[] PROGMEM = "24.73";
const char rainfall112[] PROGMEM = "24.96";
const char rainfall113[] PROGMEM = "25.18";
const char rainfall114[] PROGMEM = "25.40";
const char rainfall115[] PROGMEM = "25.62";
const char rainfall116[] PROGMEM = "25.85";
const char rainfall117[] PROGMEM = "26.07";
const char rainfall118[] PROGMEM = "26.29";
const char rainfall119[] PROGMEM = "26.52";
const char rainfall120[] PROGMEM = "26.74";
const char rainfall121[] PROGMEM = "26.96";
const char rainfall122[] PROGMEM = "27.18";
const char rainfall123[] PROGMEM = "27.41";
const char rainfall124[] PROGMEM = "27.63";
const char rainfall125[] PROGMEM = "27.85";
const char rainfall126[] PROGMEM = "28.07";
const char rainfall127[] PROGMEM = "28.30";
const char rainfall128[] PROGMEM = "28.52";
const char rainfall129[] PROGMEM = "28.74";
const char rainfall130[] PROGMEM = "28.97";
const char rainfall131[] PROGMEM = "29.19";
const char rainfall132[] PROGMEM = "29.41";
const char rainfall133[] PROGMEM = "29.63";
const char rainfall134[] PROGMEM = "29.86";
const char rainfall135[] PROGMEM = "30.08";
const char rainfall136[] PROGMEM = "30.30";
const char rainfall137[] PROGMEM = "30.53";
const char rainfall138[] PROGMEM = "30.75";
const char rainfall139[] PROGMEM = "30.97";
const char rainfall140[] PROGMEM = "31.19";
const char rainfall141[] PROGMEM = "31.42";
const char rainfall142[] PROGMEM = "31.64";
const char rainfall143[] PROGMEM = "31.86";
const char rainfall144[] PROGMEM = "32.09";
const char rainfall145[] PROGMEM = "32.31";
const char rainfall146[] PROGMEM = "32.53";
const char rainfall147[] PROGMEM = "32.75";
const char rainfall148[] PROGMEM = "32.98";
const char rainfall149[] PROGMEM = "33.20";
const char rainfall150[] PROGMEM = "33.42";
const char rainfall151[] PROGMEM = "33.65";
const char rainfall152[] PROGMEM = "33.87";
const char rainfall153[] PROGMEM = "34.09";
const char rainfall154[] PROGMEM = "34.31";
const char rainfall155[] PROGMEM = "34.54";
const char rainfall156[] PROGMEM = "34.76";
const char rainfall157[] PROGMEM = "34.98";
const char rainfall158[] PROGMEM = "35.21";
const char rainfall159[] PROGMEM = "35.43";
const char rainfall160[] PROGMEM = "35.65";
const char rainfall161[] PROGMEM = "35.87";
const char rainfall162[] PROGMEM = "36.10";
const char rainfall163[] PROGMEM = "36.32";
const char rainfall164[] PROGMEM = "36.54";
const char rainfall165[] PROGMEM = "36.76";
const char rainfall166[] PROGMEM = "36.99";
const char rainfall167[] PROGMEM = "37.21";
const char rainfall168[] PROGMEM = "37.43";
const char rainfall169[] PROGMEM = "37.66";
const char rainfall170[] PROGMEM = "37.88";
const char rainfall171[] PROGMEM = "38.10";
const char rainfall172[] PROGMEM = "38.32";
const char rainfall173[] PROGMEM = "38.55";
const char rainfall174[] PROGMEM = "38.77";
const char rainfall175[] PROGMEM = "38.99";
const char rainfall176[] PROGMEM = "39.22";
const char rainfall177[] PROGMEM = "39.44";
const char rainfall178[] PROGMEM = "39.66";
const char rainfall179[] PROGMEM = "39.88";
const char rainfall180[] PROGMEM = "40.11";
const char rainfall181[] PROGMEM = "40.33";
const char rainfall182[] PROGMEM = "40.55";
const char rainfall183[] PROGMEM = "40.78";
const char rainfall184[] PROGMEM = "41.00";
const char rainfall185[] PROGMEM = "41.22";
const char rainfall186[] PROGMEM = "41.44";
const char rainfall187[] PROGMEM = "41.67";
const char rainfall188[] PROGMEM = "41.89";
const char rainfall189[] PROGMEM = "42.11";
const char rainfall190[] PROGMEM = "42.34";
const char rainfall191[] PROGMEM = "42.56";
const char rainfall192[] PROGMEM = "42.78";
const char rainfall193[] PROGMEM = "43.00";
const char rainfall194[] PROGMEM = "43.23";
const char rainfall195[] PROGMEM = "43.45";
const char rainfall196[] PROGMEM = "43.67";
const char rainfall197[] PROGMEM = "43.89";
const char rainfall198[] PROGMEM = "44.12";
const char rainfall199[] PROGMEM = "44.34";
const char rainfall200[] PROGMEM = "44.56";
const char rainfall201[] PROGMEM = "44.79";
const char rainfall202[] PROGMEM = "45.01";
const char rainfall203[] PROGMEM = "45.23";
const char rainfall204[] PROGMEM = "45.45";
const char rainfall205[] PROGMEM = "45.68";
const char rainfall206[] PROGMEM = "45.90";
const char rainfall207[] PROGMEM = "46.12";
const char rainfall208[] PROGMEM = "46.35";
const char rainfall209[] PROGMEM = "46.57";
const char rainfall210[] PROGMEM = "46.79";
const char rainfall211[] PROGMEM = "47.01";
const char rainfall212[] PROGMEM = "47.24";
const char rainfall213[] PROGMEM = "47.46";
const char rainfall214[] PROGMEM = "47.68";
const char rainfall215[] PROGMEM = "47.91";
const char rainfall216[] PROGMEM = "48.13";
const char rainfall217[] PROGMEM = "48.35";
const char rainfall218[] PROGMEM = "48.57";
const char rainfall219[] PROGMEM = "48.80";
const char rainfall220[] PROGMEM = "49.02";
const char rainfall221[] PROGMEM = "49.24";
const char rainfall222[] PROGMEM = "49.47";
const char rainfall223[] PROGMEM = "49.69";
const char rainfall224[] PROGMEM = "49.91";
const char rainfall225[] PROGMEM = "50.13";
const char rainfall226[] PROGMEM = "50.36";
const char rainfall227[] PROGMEM = "50.58";
const char rainfall228[] PROGMEM = "50.80";
const char rainfall229[] PROGMEM = "51.03";
const char rainfall230[] PROGMEM = "51.25";
const char rainfall231[] PROGMEM = "51.47";
const char rainfall232[] PROGMEM = "51.69";
const char rainfall233[] PROGMEM = "51.92";
const char rainfall234[] PROGMEM = "52.14";
const char rainfall235[] PROGMEM = "52.36";
const char rainfall236[] PROGMEM = "52.58";
const char rainfall237[] PROGMEM = "52.81";
const char rainfall238[] PROGMEM = "53.03";
const char rainfall239[] PROGMEM = "53.25";
const char rainfall240[] PROGMEM = "53.48";
const char rainfall241[] PROGMEM = "53.70";
const char rainfall242[] PROGMEM = "53.92";
const char rainfall243[] PROGMEM = "54.14";
const char rainfall244[] PROGMEM = "54.37";
const char rainfall245[] PROGMEM = "54.59";
const char rainfall246[] PROGMEM = "54.81";
const char rainfall247[] PROGMEM = "55.04";
const char rainfall248[] PROGMEM = "55.26";
const char rainfall249[] PROGMEM = "55.48";
const char rainfall250[] PROGMEM = "55.70";
const char rainfall251[] PROGMEM = "55.93";
const char rainfall252[] PROGMEM = "56.15";
const char rainfall253[] PROGMEM = "56.37";
const char rainfall254[] PROGMEM = "56.60";

static PGM_P const rainfallLookup[RAINFALL_LOOKUP_BUFFER_SIZE] PROGMEM =
{
rainfall0,
rainfall1,
rainfall2,
rainfall3,
rainfall4,
rainfall5,
rainfall6,
rainfall7,
rainfall8,
rainfall9,
rainfall10,
rainfall11,
rainfall12,
rainfall13,
rainfall14,
rainfall15,
rainfall16,
rainfall17,
rainfall18,
rainfall19,
rainfall20,
rainfall21,
rainfall22,
rainfall23,
rainfall24,
rainfall25,
rainfall26,
rainfall27,
rainfall28,
rainfall29,
rainfall30,
rainfall31,
rainfall32,
rainfall33,
rainfall34,
rainfall35,
rainfall36,
rainfall37,
rainfall38,
rainfall39,
rainfall40,
rainfall41,
rainfall42,
rainfall43,
rainfall44,
rainfall45,
rainfall46,
rainfall47,
rainfall48,
rainfall49,
rainfall50,
rainfall51,
rainfall52,
rainfall53,
rainfall54,
rainfall55,
rainfall56,
rainfall57,
rainfall58,
rainfall59,
rainfall60,
rainfall61,
rainfall62,
rainfall63,
rainfall64,
rainfall65,
rainfall66,
rainfall67,
rainfall68,
rainfall69,
rainfall70,
rainfall71,
rainfall72,
rainfall73,
rainfall74,
rainfall75,
rainfall76,
rainfall77,
rainfall78,
rainfall79,
rainfall80,
rainfall81,
rainfall82,
rainfall83,
rainfall84,
rainfall85,
rainfall86,
rainfall87,
rainfall88,
rainfall89,
rainfall90,
rainfall91,
rainfall92,
rainfall93,
rainfall94,
rainfall95,
rainfall96,
rainfall97,
rainfall98,
rainfall99,
rainfall100,
rainfall101,
rainfall102,
rainfall103,
rainfall104,
rainfall105,
rainfall106,
rainfall107,
rainfall108,
rainfall109,
rainfall110,
rainfall111,
rainfall112,
rainfall113,
rainfall114,
rainfall115,
rainfall116,
rainfall117,
rainfall118,
rainfall119,
rainfall120,
rainfall121,
rainfall122,
rainfall123,
rainfall124,
rainfall125,
rainfall126,
rainfall127,
rainfall128,
rainfall129,
rainfall130,
rainfall131,
rainfall132,
rainfall133,
rainfall134,
rainfall135,
rainfall136,
rainfall137,
rainfall138,
rainfall139,
rainfall140,
rainfall141,
rainfall142,
rainfall143,
rainfall144,
rainfall145,
rainfall146,
rainfall147,
rainfall148,
rainfall149,
rainfall150,
rainfall151,
rainfall152,
rainfall153,
rainfall154,
rainfall155,
rainfall156,
rainfall157,
rainfall158,
rainfall159,
rainfall160,
rainfall161,
rainfall162,
rainfall163,
rainfall164,
rainfall165,
rainfall166,
rainfall167,
rainfall168,
rainfall169,
rainfall170,
rainfall171,
rainfall172,
rainfall173,
rainfall174,
rainfall175,
rainfall176,
rainfall177,
rainfall178,
rainfall179,
rainfall180,
rainfall181,
rainfall182,
rainfall183,
rainfall184,
rainfall185,
rainfall186,
rainfall187,
rainfall188,
rainfall189,
rainfall190,
rainfall191,
rainfall192,
rainfall193,
rainfall194,
rainfall195,
rainfall196,
rainfall197,
rainfall198,
rainfall199,
rainfall200,
rainfall201,
rainfall202,
rainfall203,
rainfall204,
rainfall205,
rainfall206,
rainfall207,
rainfall208,
rainfall209,
rainfall210,
rainfall211,
rainfall212,
rainfall213,
rainfall214,
rainfall215,
rainfall216,
rainfall217,
rainfall218,
rainfall219,
rainfall220,
rainfall221,
rainfall222,
rainfall223,
rainfall224,
rainfall225,
rainfall226,
rainfall227,
rainfall228,
rainfall229,
rainfall230,
rainfall231,
rainfall232,
rainfall233,
rainfall234,
rainfall235,
rainfall236,
rainfall237,
rainfall238,
rainfall239,
rainfall240,
rainfall241,
rainfall242,
rainfall243,
rainfall244,
rainfall245,
rainfall246,
rainfall247,
rainfall248,
rainfall249,
rainfall250,
rainfall251,
rainfall252,
rainfall253,
rainfall254
};

#endif