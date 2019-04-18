#include <avr/pgmspace.h>

#ifndef _INCL_MBARLOOKUP
#define _INCL_MBARLOOKUP

#define MBAR_LOOKUP_BUFFER_SIZE					 276

#define ADC_MBAR_OFFSET							 686

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
const char pressure0[] PROGMEM = "850.64";
const char pressure1[] PROGMEM = "851.73";
const char pressure2[] PROGMEM = "852.81";
const char pressure3[] PROGMEM = "853.90";
const char pressure4[] PROGMEM = "854.99";
const char pressure5[] PROGMEM = "856.07";
const char pressure6[] PROGMEM = "857.16";
const char pressure7[] PROGMEM = "858.24";
const char pressure8[] PROGMEM = "859.33";
const char pressure9[] PROGMEM = "860.42";
const char pressure10[] PROGMEM = "861.50";
const char pressure11[] PROGMEM = "862.59";
const char pressure12[] PROGMEM = "863.67";
const char pressure13[] PROGMEM = "864.76";
const char pressure14[] PROGMEM = "865.85";
const char pressure15[] PROGMEM = "866.93";
const char pressure16[] PROGMEM = "868.02";
const char pressure17[] PROGMEM = "869.11";
const char pressure18[] PROGMEM = "870.19";
const char pressure19[] PROGMEM = "871.28";
const char pressure20[] PROGMEM = "872.36";
const char pressure21[] PROGMEM = "873.45";
const char pressure22[] PROGMEM = "874.54";
const char pressure23[] PROGMEM = "875.62";
const char pressure24[] PROGMEM = "876.71";
const char pressure25[] PROGMEM = "877.79";
const char pressure26[] PROGMEM = "878.88";
const char pressure27[] PROGMEM = "879.97";
const char pressure28[] PROGMEM = "881.05";
const char pressure29[] PROGMEM = "882.14";
const char pressure30[] PROGMEM = "883.22";
const char pressure31[] PROGMEM = "884.31";
const char pressure32[] PROGMEM = "885.40";
const char pressure33[] PROGMEM = "886.48";
const char pressure34[] PROGMEM = "887.57";
const char pressure35[] PROGMEM = "888.66";
const char pressure36[] PROGMEM = "889.74";
const char pressure37[] PROGMEM = "890.83";
const char pressure38[] PROGMEM = "891.91";
const char pressure39[] PROGMEM = "893.00";
const char pressure40[] PROGMEM = "894.09";
const char pressure41[] PROGMEM = "895.17";
const char pressure42[] PROGMEM = "896.26";
const char pressure43[] PROGMEM = "897.34";
const char pressure44[] PROGMEM = "898.43";
const char pressure45[] PROGMEM = "899.52";
const char pressure46[] PROGMEM = "900.60";
const char pressure47[] PROGMEM = "901.69";
const char pressure48[] PROGMEM = "902.78";
const char pressure49[] PROGMEM = "903.86";
const char pressure50[] PROGMEM = "904.95";
const char pressure51[] PROGMEM = "906.03";
const char pressure52[] PROGMEM = "907.12";
const char pressure53[] PROGMEM = "908.21";
const char pressure54[] PROGMEM = "909.29";
const char pressure55[] PROGMEM = "910.38";
const char pressure56[] PROGMEM = "911.46";
const char pressure57[] PROGMEM = "912.55";
const char pressure58[] PROGMEM = "913.64";
const char pressure59[] PROGMEM = "914.72";
const char pressure60[] PROGMEM = "915.81";
const char pressure61[] PROGMEM = "916.89";
const char pressure62[] PROGMEM = "917.98";
const char pressure63[] PROGMEM = "919.07";
const char pressure64[] PROGMEM = "920.15";
const char pressure65[] PROGMEM = "921.24";
const char pressure66[] PROGMEM = "922.33";
const char pressure67[] PROGMEM = "923.41";
const char pressure68[] PROGMEM = "924.50";
const char pressure69[] PROGMEM = "925.58";
const char pressure70[] PROGMEM = "926.67";
const char pressure71[] PROGMEM = "927.76";
const char pressure72[] PROGMEM = "928.84";
const char pressure73[] PROGMEM = "929.93";
const char pressure74[] PROGMEM = "931.01";
const char pressure75[] PROGMEM = "932.10";
const char pressure76[] PROGMEM = "933.19";
const char pressure77[] PROGMEM = "934.27";
const char pressure78[] PROGMEM = "935.36";
const char pressure79[] PROGMEM = "936.45";
const char pressure80[] PROGMEM = "937.53";
const char pressure81[] PROGMEM = "938.62";
const char pressure82[] PROGMEM = "939.70";
const char pressure83[] PROGMEM = "940.79";
const char pressure84[] PROGMEM = "941.88";
const char pressure85[] PROGMEM = "942.96";
const char pressure86[] PROGMEM = "944.05";
const char pressure87[] PROGMEM = "945.13";
const char pressure88[] PROGMEM = "946.22";
const char pressure89[] PROGMEM = "947.31";
const char pressure90[] PROGMEM = "948.39";
const char pressure91[] PROGMEM = "949.48";
const char pressure92[] PROGMEM = "950.56";
const char pressure93[] PROGMEM = "951.65";
const char pressure94[] PROGMEM = "952.74";
const char pressure95[] PROGMEM = "953.82";
const char pressure96[] PROGMEM = "954.91";
const char pressure97[] PROGMEM = "956.00";
const char pressure98[] PROGMEM = "957.08";
const char pressure99[] PROGMEM = "958.17";
const char pressure100[] PROGMEM = "959.25";
const char pressure101[] PROGMEM = "960.34";
const char pressure102[] PROGMEM = "961.43";
const char pressure103[] PROGMEM = "962.51";
const char pressure104[] PROGMEM = "963.60";
const char pressure105[] PROGMEM = "964.68";
const char pressure106[] PROGMEM = "965.77";
const char pressure107[] PROGMEM = "966.86";
const char pressure108[] PROGMEM = "967.94";
const char pressure109[] PROGMEM = "969.03";
const char pressure110[] PROGMEM = "970.12";
const char pressure111[] PROGMEM = "971.20";
const char pressure112[] PROGMEM = "972.29";
const char pressure113[] PROGMEM = "973.37";
const char pressure114[] PROGMEM = "974.46";
const char pressure115[] PROGMEM = "975.55";
const char pressure116[] PROGMEM = "976.63";
const char pressure117[] PROGMEM = "977.72";
const char pressure118[] PROGMEM = "978.80";
const char pressure119[] PROGMEM = "979.89";
const char pressure120[] PROGMEM = "980.98";
const char pressure121[] PROGMEM = "982.06";
const char pressure122[] PROGMEM = "983.15";
const char pressure123[] PROGMEM = "984.23";
const char pressure124[] PROGMEM = "985.32";
const char pressure125[] PROGMEM = "986.41";
const char pressure126[] PROGMEM = "987.49";
const char pressure127[] PROGMEM = "988.58";
const char pressure128[] PROGMEM = "989.67";
const char pressure129[] PROGMEM = "990.75";
const char pressure130[] PROGMEM = "991.84";
const char pressure131[] PROGMEM = "992.92";
const char pressure132[] PROGMEM = "994.01";
const char pressure133[] PROGMEM = "995.10";
const char pressure134[] PROGMEM = "996.18";
const char pressure135[] PROGMEM = "997.27";
const char pressure136[] PROGMEM = "998.35";
const char pressure137[] PROGMEM = "999.44";
const char pressure138[] PROGMEM = "1000.53";
const char pressure139[] PROGMEM = "1001.61";
const char pressure140[] PROGMEM = "1002.70";
const char pressure141[] PROGMEM = "1003.79";
const char pressure142[] PROGMEM = "1004.87";
const char pressure143[] PROGMEM = "1005.96";
const char pressure144[] PROGMEM = "1007.04";
const char pressure145[] PROGMEM = "1008.13";
const char pressure146[] PROGMEM = "1009.22";
const char pressure147[] PROGMEM = "1010.30";
const char pressure148[] PROGMEM = "1011.39";
const char pressure149[] PROGMEM = "1012.47";
const char pressure150[] PROGMEM = "1013.56";
const char pressure151[] PROGMEM = "1014.65";
const char pressure152[] PROGMEM = "1015.73";
const char pressure153[] PROGMEM = "1016.82";
const char pressure154[] PROGMEM = "1017.90";
const char pressure155[] PROGMEM = "1018.99";
const char pressure156[] PROGMEM = "1020.08";
const char pressure157[] PROGMEM = "1021.16";
const char pressure158[] PROGMEM = "1022.25";
const char pressure159[] PROGMEM = "1023.34";
const char pressure160[] PROGMEM = "1024.42";
const char pressure161[] PROGMEM = "1025.51";
const char pressure162[] PROGMEM = "1026.59";
const char pressure163[] PROGMEM = "1027.68";
const char pressure164[] PROGMEM = "1028.77";
const char pressure165[] PROGMEM = "1029.85";
const char pressure166[] PROGMEM = "1030.94";
const char pressure167[] PROGMEM = "1032.02";
const char pressure168[] PROGMEM = "1033.11";
const char pressure169[] PROGMEM = "1034.20";
const char pressure170[] PROGMEM = "1035.28";
const char pressure171[] PROGMEM = "1036.37";
const char pressure172[] PROGMEM = "1037.46";
const char pressure173[] PROGMEM = "1038.54";
const char pressure174[] PROGMEM = "1039.63";
const char pressure175[] PROGMEM = "1040.71";
const char pressure176[] PROGMEM = "1041.80";
const char pressure177[] PROGMEM = "1042.89";
const char pressure178[] PROGMEM = "1043.97";
const char pressure179[] PROGMEM = "1045.06";
const char pressure180[] PROGMEM = "1046.14";
const char pressure181[] PROGMEM = "1047.23";
const char pressure182[] PROGMEM = "1048.32";
const char pressure183[] PROGMEM = "1049.40";
const char pressure184[] PROGMEM = "1050.49";
const char pressure185[] PROGMEM = "1051.57";
const char pressure186[] PROGMEM = "1052.66";
const char pressure187[] PROGMEM = "1053.75";
const char pressure188[] PROGMEM = "1054.83";
const char pressure189[] PROGMEM = "1055.92";
const char pressure190[] PROGMEM = "1057.01";
const char pressure191[] PROGMEM = "1058.09";
const char pressure192[] PROGMEM = "1059.18";
const char pressure193[] PROGMEM = "1060.26";
const char pressure194[] PROGMEM = "1061.35";
const char pressure195[] PROGMEM = "1062.44";
const char pressure196[] PROGMEM = "1063.52";
const char pressure197[] PROGMEM = "1064.61";
const char pressure198[] PROGMEM = "1065.69";
const char pressure199[] PROGMEM = "1066.78";
const char pressure200[] PROGMEM = "1067.87";
const char pressure201[] PROGMEM = "1068.95";
const char pressure202[] PROGMEM = "1070.04";
const char pressure203[] PROGMEM = "1071.13";
const char pressure204[] PROGMEM = "1072.21";
const char pressure205[] PROGMEM = "1073.30";
const char pressure206[] PROGMEM = "1074.38";
const char pressure207[] PROGMEM = "1075.47";
const char pressure208[] PROGMEM = "1076.56";
const char pressure209[] PROGMEM = "1077.64";
const char pressure210[] PROGMEM = "1078.73";
const char pressure211[] PROGMEM = "1079.81";
const char pressure212[] PROGMEM = "1080.90";
const char pressure213[] PROGMEM = "1081.99";
const char pressure214[] PROGMEM = "1083.07";
const char pressure215[] PROGMEM = "1084.16";
const char pressure216[] PROGMEM = "1085.24";
const char pressure217[] PROGMEM = "1086.33";
const char pressure218[] PROGMEM = "1087.42";
const char pressure219[] PROGMEM = "1088.50";
const char pressure220[] PROGMEM = "1089.59";
const char pressure221[] PROGMEM = "1090.68";
const char pressure222[] PROGMEM = "1091.76";
const char pressure223[] PROGMEM = "1092.85";
const char pressure224[] PROGMEM = "1093.93";
const char pressure225[] PROGMEM = "1095.02";
const char pressure226[] PROGMEM = "1096.11";
const char pressure227[] PROGMEM = "1097.19";
const char pressure228[] PROGMEM = "1098.28";
const char pressure229[] PROGMEM = "1099.36";
const char pressure230[] PROGMEM = "1100.45";
const char pressure231[] PROGMEM = "1101.54";
const char pressure232[] PROGMEM = "1102.62";
const char pressure233[] PROGMEM = "1103.71";
const char pressure234[] PROGMEM = "1104.80";
const char pressure235[] PROGMEM = "1105.88";
const char pressure236[] PROGMEM = "1106.97";
const char pressure237[] PROGMEM = "1108.05";
const char pressure238[] PROGMEM = "1109.14";
const char pressure239[] PROGMEM = "1110.23";
const char pressure240[] PROGMEM = "1111.31";
const char pressure241[] PROGMEM = "1112.40";
const char pressure242[] PROGMEM = "1113.48";
const char pressure243[] PROGMEM = "1114.57";
const char pressure244[] PROGMEM = "1115.66";
const char pressure245[] PROGMEM = "1116.74";
const char pressure246[] PROGMEM = "1117.83";
const char pressure247[] PROGMEM = "1118.91";
const char pressure248[] PROGMEM = "1120.00";
const char pressure249[] PROGMEM = "1121.09";
const char pressure250[] PROGMEM = "1122.17";
const char pressure251[] PROGMEM = "1123.26";
const char pressure252[] PROGMEM = "1124.35";
const char pressure253[] PROGMEM = "1125.43";
const char pressure254[] PROGMEM = "1126.52";
const char pressure255[] PROGMEM = "1127.60";
const char pressure256[] PROGMEM = "1128.69";
const char pressure257[] PROGMEM = "1129.78";
const char pressure258[] PROGMEM = "1130.86";
const char pressure259[] PROGMEM = "1131.95";
const char pressure260[] PROGMEM = "1133.03";
const char pressure261[] PROGMEM = "1134.12";
const char pressure262[] PROGMEM = "1135.21";
const char pressure263[] PROGMEM = "1136.29";
const char pressure264[] PROGMEM = "1137.38";
const char pressure265[] PROGMEM = "1138.47";
const char pressure266[] PROGMEM = "1139.55";
const char pressure267[] PROGMEM = "1140.64";
const char pressure268[] PROGMEM = "1141.72";
const char pressure269[] PROGMEM = "1142.81";
const char pressure270[] PROGMEM = "1143.90";
const char pressure271[] PROGMEM = "1144.98";
const char pressure272[] PROGMEM = "1146.07";
const char pressure273[] PROGMEM = "1147.15";
const char pressure274[] PROGMEM = "1148.24";
const char pressure275[] PROGMEM = "1149.33";

static PGM_P const mbarLookup[MBAR_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
	pressure0,
	pressure1,
	pressure2,
	pressure3,
	pressure4,
	pressure5,
	pressure6,
	pressure7,
	pressure8,
	pressure9,
	pressure10,
	pressure11,
	pressure12,
	pressure13,
	pressure14,
	pressure15,
	pressure16,
	pressure17,
	pressure18,
	pressure19,
	pressure20,
	pressure21,
	pressure22,
	pressure23,
	pressure24,
	pressure25,
	pressure26,
	pressure27,
	pressure28,
	pressure29,
	pressure30,
	pressure31,
	pressure32,
	pressure33,
	pressure34,
	pressure35,
	pressure36,
	pressure37,
	pressure38,
	pressure39,
	pressure40,
	pressure41,
	pressure42,
	pressure43,
	pressure44,
	pressure45,
	pressure46,
	pressure47,
	pressure48,
	pressure49,
	pressure50,
	pressure51,
	pressure52,
	pressure53,
	pressure54,
	pressure55,
	pressure56,
	pressure57,
	pressure58,
	pressure59,
	pressure60,
	pressure61,
	pressure62,
	pressure63,
	pressure64,
	pressure65,
	pressure66,
	pressure67,
	pressure68,
	pressure69,
	pressure70,
	pressure71,
	pressure72,
	pressure73,
	pressure74,
	pressure75,
	pressure76,
	pressure77,
	pressure78,
	pressure79,
	pressure80,
	pressure81,
	pressure82,
	pressure83,
	pressure84,
	pressure85,
	pressure86,
	pressure87,
	pressure88,
	pressure89,
	pressure90,
	pressure91,
	pressure92,
	pressure93,
	pressure94,
	pressure95,
	pressure96,
	pressure97,
	pressure98,
	pressure99,
	pressure100,
	pressure101,
	pressure102,
	pressure103,
	pressure104,
	pressure105,
	pressure106,
	pressure107,
	pressure108,
	pressure109,
	pressure110,
	pressure111,
	pressure112,
	pressure113,
	pressure114,
	pressure115,
	pressure116,
	pressure117,
	pressure118,
	pressure119,
	pressure120,
	pressure121,
	pressure122,
	pressure123,
	pressure124,
	pressure125,
	pressure126,
	pressure127,
	pressure128,
	pressure129,
	pressure130,
	pressure131,
	pressure132,
	pressure133,
	pressure134,
	pressure135,
	pressure136,
	pressure137,
	pressure138,
	pressure139,
	pressure140,
	pressure141,
	pressure142,
	pressure143,
	pressure144,
	pressure145,
	pressure146,
	pressure147,
	pressure148,
	pressure149,
	pressure150,
	pressure151,
	pressure152,
	pressure153,
	pressure154,
	pressure155,
	pressure156,
	pressure157,
	pressure158,
	pressure159,
	pressure160,
	pressure161,
	pressure162,
	pressure163,
	pressure164,
	pressure165,
	pressure166,
	pressure167,
	pressure168,
	pressure169,
	pressure170,
	pressure171,
	pressure172,
	pressure173,
	pressure174,
	pressure175,
	pressure176,
	pressure177,
	pressure178,
	pressure179,
	pressure180,
	pressure181,
	pressure182,
	pressure183,
	pressure184,
	pressure185,
	pressure186,
	pressure187,
	pressure188,
	pressure189,
	pressure190,
	pressure191,
	pressure192,
	pressure193,
	pressure194,
	pressure195,
	pressure196,
	pressure197,
	pressure198,
	pressure199,
	pressure200,
	pressure201,
	pressure202,
	pressure203,
	pressure204,
	pressure205,
	pressure206,
	pressure207,
	pressure208,
	pressure209,
	pressure210,
	pressure211,
	pressure212,
	pressure213,
	pressure214,
	pressure215,
	pressure216,
	pressure217,
	pressure218,
	pressure219,
	pressure220,
	pressure221,
	pressure222,
	pressure223,
	pressure224,
	pressure225,
	pressure226,
	pressure227,
	pressure228,
	pressure229,
	pressure230,
	pressure231,
	pressure232,
	pressure233,
	pressure234,
	pressure235,
	pressure236,
	pressure237,
	pressure238,
	pressure239,
	pressure240,
	pressure241,
	pressure242,
	pressure243,
	pressure244,
	pressure245,
	pressure246,
	pressure247,
	pressure248,
	pressure249,
	pressure250,
	pressure251,
	pressure252,
	pressure253,
	pressure254,
	pressure255,
	pressure256,
	pressure257,
	pressure258,
	pressure259,
	pressure260,
	pressure261,
	pressure262,
	pressure263,
	pressure264,
	pressure265,
	pressure266,
	pressure267,
	pressure268,
	pressure269,
	pressure270,
	pressure271,
	pressure272,
	pressure273,
	pressure274,
	pressure275
};

#endif
