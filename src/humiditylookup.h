#include <avr/pgmspace.h>

#ifndef _INCL_HUMIDITYLOOKUP
#define _INCL_HUMIDITYLOOKUP

#define HUMIDITY_LOOKUP_BUFFER_SIZE		636

/*
** Minimum sensor output corresponding to 0% RH is 800mv. The minimum
** ADC value at 800mv is 163", hence we subtract the offset defined here
** from the value before using as the index into the array below...
*/
#define ADC_HUMIDITY_OFFSET				163

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
const char humidity0[] PROGMEM = "0.00";
const char humidity1[] PROGMEM = "0.05";
const char humidity2[] PROGMEM = "0.21";
const char humidity3[] PROGMEM = "0.37";
const char humidity4[] PROGMEM = "0.52";
const char humidity5[] PROGMEM = "0.68";
const char humidity6[] PROGMEM = "0.84";
const char humidity7[] PROGMEM = "1.00";
const char humidity8[] PROGMEM = "1.15";
const char humidity9[] PROGMEM = "1.31";
const char humidity10[] PROGMEM = "1.47";
const char humidity11[] PROGMEM = "1.63";
const char humidity12[] PROGMEM = "1.78";
const char humidity13[] PROGMEM = "1.94";
const char humidity14[] PROGMEM = "2.10";
const char humidity15[] PROGMEM = "2.26";
const char humidity16[] PROGMEM = "2.42";
const char humidity17[] PROGMEM = "2.57";
const char humidity18[] PROGMEM = "2.73";
const char humidity19[] PROGMEM = "2.89";
const char humidity20[] PROGMEM = "3.05";
const char humidity21[] PROGMEM = "3.20";
const char humidity22[] PROGMEM = "3.36";
const char humidity23[] PROGMEM = "3.52";
const char humidity24[] PROGMEM = "3.68";
const char humidity25[] PROGMEM = "3.83";
const char humidity26[] PROGMEM = "3.99";
const char humidity27[] PROGMEM = "4.15";
const char humidity28[] PROGMEM = "4.31";
const char humidity29[] PROGMEM = "4.47";
const char humidity30[] PROGMEM = "4.62";
const char humidity31[] PROGMEM = "4.78";
const char humidity32[] PROGMEM = "4.94";
const char humidity33[] PROGMEM = "5.10";
const char humidity34[] PROGMEM = "5.25";
const char humidity35[] PROGMEM = "5.41";
const char humidity36[] PROGMEM = "5.57";
const char humidity37[] PROGMEM = "5.73";
const char humidity38[] PROGMEM = "5.88";
const char humidity39[] PROGMEM = "6.04";
const char humidity40[] PROGMEM = "6.20";
const char humidity41[] PROGMEM = "6.36";
const char humidity42[] PROGMEM = "6.51";
const char humidity43[] PROGMEM = "6.67";
const char humidity44[] PROGMEM = "6.83";
const char humidity45[] PROGMEM = "6.99";
const char humidity46[] PROGMEM = "7.15";
const char humidity47[] PROGMEM = "7.30";
const char humidity48[] PROGMEM = "7.46";
const char humidity49[] PROGMEM = "7.62";
const char humidity50[] PROGMEM = "7.78";
const char humidity51[] PROGMEM = "7.93";
const char humidity52[] PROGMEM = "8.09";
const char humidity53[] PROGMEM = "8.25";
const char humidity54[] PROGMEM = "8.41";
const char humidity55[] PROGMEM = "8.56";
const char humidity56[] PROGMEM = "8.72";
const char humidity57[] PROGMEM = "8.88";
const char humidity58[] PROGMEM = "9.04";
const char humidity59[] PROGMEM = "9.19";
const char humidity60[] PROGMEM = "9.35";
const char humidity61[] PROGMEM = "9.51";
const char humidity62[] PROGMEM = "9.67";
const char humidity63[] PROGMEM = "9.83";
const char humidity64[] PROGMEM = "9.98";
const char humidity65[] PROGMEM = "10.14";
const char humidity66[] PROGMEM = "10.30";
const char humidity67[] PROGMEM = "10.46";
const char humidity68[] PROGMEM = "10.61";
const char humidity69[] PROGMEM = "10.77";
const char humidity70[] PROGMEM = "10.93";
const char humidity71[] PROGMEM = "11.09";
const char humidity72[] PROGMEM = "11.24";
const char humidity73[] PROGMEM = "11.40";
const char humidity74[] PROGMEM = "11.56";
const char humidity75[] PROGMEM = "11.72";
const char humidity76[] PROGMEM = "11.88";
const char humidity77[] PROGMEM = "12.03";
const char humidity78[] PROGMEM = "12.19";
const char humidity79[] PROGMEM = "12.35";
const char humidity80[] PROGMEM = "12.51";
const char humidity81[] PROGMEM = "12.66";
const char humidity82[] PROGMEM = "12.82";
const char humidity83[] PROGMEM = "12.98";
const char humidity84[] PROGMEM = "13.14";
const char humidity85[] PROGMEM = "13.29";
const char humidity86[] PROGMEM = "13.45";
const char humidity87[] PROGMEM = "13.61";
const char humidity88[] PROGMEM = "13.77";
const char humidity89[] PROGMEM = "13.92";
const char humidity90[] PROGMEM = "14.08";
const char humidity91[] PROGMEM = "14.24";
const char humidity92[] PROGMEM = "14.40";
const char humidity93[] PROGMEM = "14.56";
const char humidity94[] PROGMEM = "14.71";
const char humidity95[] PROGMEM = "14.87";
const char humidity96[] PROGMEM = "15.03";
const char humidity97[] PROGMEM = "15.19";
const char humidity98[] PROGMEM = "15.34";
const char humidity99[] PROGMEM = "15.50";
const char humidity100[] PROGMEM = "15.66";
const char humidity101[] PROGMEM = "15.82";
const char humidity102[] PROGMEM = "15.97";
const char humidity103[] PROGMEM = "16.13";
const char humidity104[] PROGMEM = "16.29";
const char humidity105[] PROGMEM = "16.45";
const char humidity106[] PROGMEM = "16.61";
const char humidity107[] PROGMEM = "16.76";
const char humidity108[] PROGMEM = "16.92";
const char humidity109[] PROGMEM = "17.08";
const char humidity110[] PROGMEM = "17.24";
const char humidity111[] PROGMEM = "17.39";
const char humidity112[] PROGMEM = "17.55";
const char humidity113[] PROGMEM = "17.71";
const char humidity114[] PROGMEM = "17.87";
const char humidity115[] PROGMEM = "18.02";
const char humidity116[] PROGMEM = "18.18";
const char humidity117[] PROGMEM = "18.34";
const char humidity118[] PROGMEM = "18.50";
const char humidity119[] PROGMEM = "18.65";
const char humidity120[] PROGMEM = "18.81";
const char humidity121[] PROGMEM = "18.97";
const char humidity122[] PROGMEM = "19.13";
const char humidity123[] PROGMEM = "19.29";
const char humidity124[] PROGMEM = "19.44";
const char humidity125[] PROGMEM = "19.60";
const char humidity126[] PROGMEM = "19.76";
const char humidity127[] PROGMEM = "19.92";
const char humidity128[] PROGMEM = "20.07";
const char humidity129[] PROGMEM = "20.23";
const char humidity130[] PROGMEM = "20.39";
const char humidity131[] PROGMEM = "20.55";
const char humidity132[] PROGMEM = "20.70";
const char humidity133[] PROGMEM = "20.86";
const char humidity134[] PROGMEM = "21.02";
const char humidity135[] PROGMEM = "21.18";
const char humidity136[] PROGMEM = "21.34";
const char humidity137[] PROGMEM = "21.49";
const char humidity138[] PROGMEM = "21.65";
const char humidity139[] PROGMEM = "21.81";
const char humidity140[] PROGMEM = "21.97";
const char humidity141[] PROGMEM = "22.12";
const char humidity142[] PROGMEM = "22.28";
const char humidity143[] PROGMEM = "22.44";
const char humidity144[] PROGMEM = "22.60";
const char humidity145[] PROGMEM = "22.75";
const char humidity146[] PROGMEM = "22.91";
const char humidity147[] PROGMEM = "23.07";
const char humidity148[] PROGMEM = "23.23";
const char humidity149[] PROGMEM = "23.38";
const char humidity150[] PROGMEM = "23.54";
const char humidity151[] PROGMEM = "23.70";
const char humidity152[] PROGMEM = "23.86";
const char humidity153[] PROGMEM = "24.02";
const char humidity154[] PROGMEM = "24.17";
const char humidity155[] PROGMEM = "24.33";
const char humidity156[] PROGMEM = "24.49";
const char humidity157[] PROGMEM = "24.65";
const char humidity158[] PROGMEM = "24.80";
const char humidity159[] PROGMEM = "24.96";
const char humidity160[] PROGMEM = "25.12";
const char humidity161[] PROGMEM = "25.28";
const char humidity162[] PROGMEM = "25.43";
const char humidity163[] PROGMEM = "25.59";
const char humidity164[] PROGMEM = "25.75";
const char humidity165[] PROGMEM = "25.91";
const char humidity166[] PROGMEM = "26.07";
const char humidity167[] PROGMEM = "26.22";
const char humidity168[] PROGMEM = "26.38";
const char humidity169[] PROGMEM = "26.54";
const char humidity170[] PROGMEM = "26.70";
const char humidity171[] PROGMEM = "26.85";
const char humidity172[] PROGMEM = "27.01";
const char humidity173[] PROGMEM = "27.17";
const char humidity174[] PROGMEM = "27.33";
const char humidity175[] PROGMEM = "27.48";
const char humidity176[] PROGMEM = "27.64";
const char humidity177[] PROGMEM = "27.80";
const char humidity178[] PROGMEM = "27.96";
const char humidity179[] PROGMEM = "28.11";
const char humidity180[] PROGMEM = "28.27";
const char humidity181[] PROGMEM = "28.43";
const char humidity182[] PROGMEM = "28.59";
const char humidity183[] PROGMEM = "28.75";
const char humidity184[] PROGMEM = "28.90";
const char humidity185[] PROGMEM = "29.06";
const char humidity186[] PROGMEM = "29.22";
const char humidity187[] PROGMEM = "29.38";
const char humidity188[] PROGMEM = "29.53";
const char humidity189[] PROGMEM = "29.69";
const char humidity190[] PROGMEM = "29.85";
const char humidity191[] PROGMEM = "30.01";
const char humidity192[] PROGMEM = "30.16";
const char humidity193[] PROGMEM = "30.32";
const char humidity194[] PROGMEM = "30.48";
const char humidity195[] PROGMEM = "30.64";
const char humidity196[] PROGMEM = "30.79";
const char humidity197[] PROGMEM = "30.95";
const char humidity198[] PROGMEM = "31.11";
const char humidity199[] PROGMEM = "31.27";
const char humidity200[] PROGMEM = "31.43";
const char humidity201[] PROGMEM = "31.58";
const char humidity202[] PROGMEM = "31.74";
const char humidity203[] PROGMEM = "31.90";
const char humidity204[] PROGMEM = "32.06";
const char humidity205[] PROGMEM = "32.21";
const char humidity206[] PROGMEM = "32.37";
const char humidity207[] PROGMEM = "32.53";
const char humidity208[] PROGMEM = "32.69";
const char humidity209[] PROGMEM = "32.84";
const char humidity210[] PROGMEM = "33.00";
const char humidity211[] PROGMEM = "33.16";
const char humidity212[] PROGMEM = "33.32";
const char humidity213[] PROGMEM = "33.48";
const char humidity214[] PROGMEM = "33.63";
const char humidity215[] PROGMEM = "33.79";
const char humidity216[] PROGMEM = "33.95";
const char humidity217[] PROGMEM = "34.11";
const char humidity218[] PROGMEM = "34.26";
const char humidity219[] PROGMEM = "34.42";
const char humidity220[] PROGMEM = "34.58";
const char humidity221[] PROGMEM = "34.74";
const char humidity222[] PROGMEM = "34.89";
const char humidity223[] PROGMEM = "35.05";
const char humidity224[] PROGMEM = "35.21";
const char humidity225[] PROGMEM = "35.37";
const char humidity226[] PROGMEM = "35.52";
const char humidity227[] PROGMEM = "35.68";
const char humidity228[] PROGMEM = "35.84";
const char humidity229[] PROGMEM = "36.00";
const char humidity230[] PROGMEM = "36.16";
const char humidity231[] PROGMEM = "36.31";
const char humidity232[] PROGMEM = "36.47";
const char humidity233[] PROGMEM = "36.63";
const char humidity234[] PROGMEM = "36.79";
const char humidity235[] PROGMEM = "36.94";
const char humidity236[] PROGMEM = "37.10";
const char humidity237[] PROGMEM = "37.26";
const char humidity238[] PROGMEM = "37.42";
const char humidity239[] PROGMEM = "37.57";
const char humidity240[] PROGMEM = "37.73";
const char humidity241[] PROGMEM = "37.89";
const char humidity242[] PROGMEM = "38.05";
const char humidity243[] PROGMEM = "38.21";
const char humidity244[] PROGMEM = "38.36";
const char humidity245[] PROGMEM = "38.52";
const char humidity246[] PROGMEM = "38.68";
const char humidity247[] PROGMEM = "38.84";
const char humidity248[] PROGMEM = "38.99";
const char humidity249[] PROGMEM = "39.15";
const char humidity250[] PROGMEM = "39.31";
const char humidity251[] PROGMEM = "39.47";
const char humidity252[] PROGMEM = "39.62";
const char humidity253[] PROGMEM = "39.78";
const char humidity254[] PROGMEM = "39.94";
const char humidity255[] PROGMEM = "40.10";
const char humidity256[] PROGMEM = "40.25";
const char humidity257[] PROGMEM = "40.41";
const char humidity258[] PROGMEM = "40.57";
const char humidity259[] PROGMEM = "40.73";
const char humidity260[] PROGMEM = "40.89";
const char humidity261[] PROGMEM = "41.04";
const char humidity262[] PROGMEM = "41.20";
const char humidity263[] PROGMEM = "41.36";
const char humidity264[] PROGMEM = "41.52";
const char humidity265[] PROGMEM = "41.67";
const char humidity266[] PROGMEM = "41.83";
const char humidity267[] PROGMEM = "41.99";
const char humidity268[] PROGMEM = "42.15";
const char humidity269[] PROGMEM = "42.30";
const char humidity270[] PROGMEM = "42.46";
const char humidity271[] PROGMEM = "42.62";
const char humidity272[] PROGMEM = "42.78";
const char humidity273[] PROGMEM = "42.94";
const char humidity274[] PROGMEM = "43.09";
const char humidity275[] PROGMEM = "43.25";
const char humidity276[] PROGMEM = "43.41";
const char humidity277[] PROGMEM = "43.57";
const char humidity278[] PROGMEM = "43.72";
const char humidity279[] PROGMEM = "43.88";
const char humidity280[] PROGMEM = "44.04";
const char humidity281[] PROGMEM = "44.20";
const char humidity282[] PROGMEM = "44.35";
const char humidity283[] PROGMEM = "44.51";
const char humidity284[] PROGMEM = "44.67";
const char humidity285[] PROGMEM = "44.83";
const char humidity286[] PROGMEM = "44.98";
const char humidity287[] PROGMEM = "45.14";
const char humidity288[] PROGMEM = "45.30";
const char humidity289[] PROGMEM = "45.46";
const char humidity290[] PROGMEM = "45.62";
const char humidity291[] PROGMEM = "45.77";
const char humidity292[] PROGMEM = "45.93";
const char humidity293[] PROGMEM = "46.09";
const char humidity294[] PROGMEM = "46.25";
const char humidity295[] PROGMEM = "46.40";
const char humidity296[] PROGMEM = "46.56";
const char humidity297[] PROGMEM = "46.72";
const char humidity298[] PROGMEM = "46.88";
const char humidity299[] PROGMEM = "47.03";
const char humidity300[] PROGMEM = "47.19";
const char humidity301[] PROGMEM = "47.35";
const char humidity302[] PROGMEM = "47.51";
const char humidity303[] PROGMEM = "47.66";
const char humidity304[] PROGMEM = "47.82";
const char humidity305[] PROGMEM = "47.98";
const char humidity306[] PROGMEM = "48.14";
const char humidity307[] PROGMEM = "48.30";
const char humidity308[] PROGMEM = "48.45";
const char humidity309[] PROGMEM = "48.61";
const char humidity310[] PROGMEM = "48.77";
const char humidity311[] PROGMEM = "48.93";
const char humidity312[] PROGMEM = "49.08";
const char humidity313[] PROGMEM = "49.24";
const char humidity314[] PROGMEM = "49.40";
const char humidity315[] PROGMEM = "49.56";
const char humidity316[] PROGMEM = "49.71";
const char humidity317[] PROGMEM = "49.87";
const char humidity318[] PROGMEM = "50.03";
const char humidity319[] PROGMEM = "50.19";
const char humidity320[] PROGMEM = "50.35";
const char humidity321[] PROGMEM = "50.50";
const char humidity322[] PROGMEM = "50.66";
const char humidity323[] PROGMEM = "50.82";
const char humidity324[] PROGMEM = "50.98";
const char humidity325[] PROGMEM = "51.13";
const char humidity326[] PROGMEM = "51.29";
const char humidity327[] PROGMEM = "51.45";
const char humidity328[] PROGMEM = "51.61";
const char humidity329[] PROGMEM = "51.76";
const char humidity330[] PROGMEM = "51.92";
const char humidity331[] PROGMEM = "52.08";
const char humidity332[] PROGMEM = "52.24";
const char humidity333[] PROGMEM = "52.39";
const char humidity334[] PROGMEM = "52.55";
const char humidity335[] PROGMEM = "52.71";
const char humidity336[] PROGMEM = "52.87";
const char humidity337[] PROGMEM = "53.03";
const char humidity338[] PROGMEM = "53.18";
const char humidity339[] PROGMEM = "53.34";
const char humidity340[] PROGMEM = "53.50";
const char humidity341[] PROGMEM = "53.66";
const char humidity342[] PROGMEM = "53.81";
const char humidity343[] PROGMEM = "53.97";
const char humidity344[] PROGMEM = "54.13";
const char humidity345[] PROGMEM = "54.29";
const char humidity346[] PROGMEM = "54.44";
const char humidity347[] PROGMEM = "54.60";
const char humidity348[] PROGMEM = "54.76";
const char humidity349[] PROGMEM = "54.92";
const char humidity350[] PROGMEM = "55.08";
const char humidity351[] PROGMEM = "55.23";
const char humidity352[] PROGMEM = "55.39";
const char humidity353[] PROGMEM = "55.55";
const char humidity354[] PROGMEM = "55.71";
const char humidity355[] PROGMEM = "55.86";
const char humidity356[] PROGMEM = "56.02";
const char humidity357[] PROGMEM = "56.18";
const char humidity358[] PROGMEM = "56.34";
const char humidity359[] PROGMEM = "56.49";
const char humidity360[] PROGMEM = "56.65";
const char humidity361[] PROGMEM = "56.81";
const char humidity362[] PROGMEM = "56.97";
const char humidity363[] PROGMEM = "57.12";
const char humidity364[] PROGMEM = "57.28";
const char humidity365[] PROGMEM = "57.44";
const char humidity366[] PROGMEM = "57.60";
const char humidity367[] PROGMEM = "57.76";
const char humidity368[] PROGMEM = "57.91";
const char humidity369[] PROGMEM = "58.07";
const char humidity370[] PROGMEM = "58.23";
const char humidity371[] PROGMEM = "58.39";
const char humidity372[] PROGMEM = "58.54";
const char humidity373[] PROGMEM = "58.70";
const char humidity374[] PROGMEM = "58.86";
const char humidity375[] PROGMEM = "59.02";
const char humidity376[] PROGMEM = "59.17";
const char humidity377[] PROGMEM = "59.33";
const char humidity378[] PROGMEM = "59.49";
const char humidity379[] PROGMEM = "59.65";
const char humidity380[] PROGMEM = "59.81";
const char humidity381[] PROGMEM = "59.96";
const char humidity382[] PROGMEM = "60.12";
const char humidity383[] PROGMEM = "60.28";
const char humidity384[] PROGMEM = "60.44";
const char humidity385[] PROGMEM = "60.59";
const char humidity386[] PROGMEM = "60.75";
const char humidity387[] PROGMEM = "60.91";
const char humidity388[] PROGMEM = "61.07";
const char humidity389[] PROGMEM = "61.22";
const char humidity390[] PROGMEM = "61.38";
const char humidity391[] PROGMEM = "61.54";
const char humidity392[] PROGMEM = "61.70";
const char humidity393[] PROGMEM = "61.85";
const char humidity394[] PROGMEM = "62.01";
const char humidity395[] PROGMEM = "62.17";
const char humidity396[] PROGMEM = "62.33";
const char humidity397[] PROGMEM = "62.49";
const char humidity398[] PROGMEM = "62.64";
const char humidity399[] PROGMEM = "62.80";
const char humidity400[] PROGMEM = "62.96";
const char humidity401[] PROGMEM = "63.12";
const char humidity402[] PROGMEM = "63.27";
const char humidity403[] PROGMEM = "63.43";
const char humidity404[] PROGMEM = "63.59";
const char humidity405[] PROGMEM = "63.75";
const char humidity406[] PROGMEM = "63.90";
const char humidity407[] PROGMEM = "64.06";
const char humidity408[] PROGMEM = "64.22";
const char humidity409[] PROGMEM = "64.38";
const char humidity410[] PROGMEM = "64.54";
const char humidity411[] PROGMEM = "64.69";
const char humidity412[] PROGMEM = "64.85";
const char humidity413[] PROGMEM = "65.01";
const char humidity414[] PROGMEM = "65.17";
const char humidity415[] PROGMEM = "65.32";
const char humidity416[] PROGMEM = "65.48";
const char humidity417[] PROGMEM = "65.64";
const char humidity418[] PROGMEM = "65.80";
const char humidity419[] PROGMEM = "65.95";
const char humidity420[] PROGMEM = "66.11";
const char humidity421[] PROGMEM = "66.27";
const char humidity422[] PROGMEM = "66.43";
const char humidity423[] PROGMEM = "66.58";
const char humidity424[] PROGMEM = "66.74";
const char humidity425[] PROGMEM = "66.90";
const char humidity426[] PROGMEM = "67.06";
const char humidity427[] PROGMEM = "67.22";
const char humidity428[] PROGMEM = "67.37";
const char humidity429[] PROGMEM = "67.53";
const char humidity430[] PROGMEM = "67.69";
const char humidity431[] PROGMEM = "67.85";
const char humidity432[] PROGMEM = "68.00";
const char humidity433[] PROGMEM = "68.16";
const char humidity434[] PROGMEM = "68.32";
const char humidity435[] PROGMEM = "68.48";
const char humidity436[] PROGMEM = "68.63";
const char humidity437[] PROGMEM = "68.79";
const char humidity438[] PROGMEM = "68.95";
const char humidity439[] PROGMEM = "69.11";
const char humidity440[] PROGMEM = "69.26";
const char humidity441[] PROGMEM = "69.42";
const char humidity442[] PROGMEM = "69.58";
const char humidity443[] PROGMEM = "69.74";
const char humidity444[] PROGMEM = "69.90";
const char humidity445[] PROGMEM = "70.05";
const char humidity446[] PROGMEM = "70.21";
const char humidity447[] PROGMEM = "70.37";
const char humidity448[] PROGMEM = "70.53";
const char humidity449[] PROGMEM = "70.68";
const char humidity450[] PROGMEM = "70.84";
const char humidity451[] PROGMEM = "71.00";
const char humidity452[] PROGMEM = "71.16";
const char humidity453[] PROGMEM = "71.31";
const char humidity454[] PROGMEM = "71.47";
const char humidity455[] PROGMEM = "71.63";
const char humidity456[] PROGMEM = "71.79";
const char humidity457[] PROGMEM = "71.95";
const char humidity458[] PROGMEM = "72.10";
const char humidity459[] PROGMEM = "72.26";
const char humidity460[] PROGMEM = "72.42";
const char humidity461[] PROGMEM = "72.58";
const char humidity462[] PROGMEM = "72.73";
const char humidity463[] PROGMEM = "72.89";
const char humidity464[] PROGMEM = "73.05";
const char humidity465[] PROGMEM = "73.21";
const char humidity466[] PROGMEM = "73.36";
const char humidity467[] PROGMEM = "73.52";
const char humidity468[] PROGMEM = "73.68";
const char humidity469[] PROGMEM = "73.84";
const char humidity470[] PROGMEM = "73.99";
const char humidity471[] PROGMEM = "74.15";
const char humidity472[] PROGMEM = "74.31";
const char humidity473[] PROGMEM = "74.47";
const char humidity474[] PROGMEM = "74.63";
const char humidity475[] PROGMEM = "74.78";
const char humidity476[] PROGMEM = "74.94";
const char humidity477[] PROGMEM = "75.10";
const char humidity478[] PROGMEM = "75.26";
const char humidity479[] PROGMEM = "75.41";
const char humidity480[] PROGMEM = "75.57";
const char humidity481[] PROGMEM = "75.73";
const char humidity482[] PROGMEM = "75.89";
const char humidity483[] PROGMEM = "76.04";
const char humidity484[] PROGMEM = "76.20";
const char humidity485[] PROGMEM = "76.36";
const char humidity486[] PROGMEM = "76.52";
const char humidity487[] PROGMEM = "76.68";
const char humidity488[] PROGMEM = "76.83";
const char humidity489[] PROGMEM = "76.99";
const char humidity490[] PROGMEM = "77.15";
const char humidity491[] PROGMEM = "77.31";
const char humidity492[] PROGMEM = "77.46";
const char humidity493[] PROGMEM = "77.62";
const char humidity494[] PROGMEM = "77.78";
const char humidity495[] PROGMEM = "77.94";
const char humidity496[] PROGMEM = "78.09";
const char humidity497[] PROGMEM = "78.25";
const char humidity498[] PROGMEM = "78.41";
const char humidity499[] PROGMEM = "78.57";
const char humidity500[] PROGMEM = "78.72";
const char humidity501[] PROGMEM = "78.88";
const char humidity502[] PROGMEM = "79.04";
const char humidity503[] PROGMEM = "79.20";
const char humidity504[] PROGMEM = "79.36";
const char humidity505[] PROGMEM = "79.51";
const char humidity506[] PROGMEM = "79.67";
const char humidity507[] PROGMEM = "79.83";
const char humidity508[] PROGMEM = "79.99";
const char humidity509[] PROGMEM = "80.14";
const char humidity510[] PROGMEM = "80.30";
const char humidity511[] PROGMEM = "80.46";
const char humidity512[] PROGMEM = "80.62";
const char humidity513[] PROGMEM = "80.77";
const char humidity514[] PROGMEM = "80.93";
const char humidity515[] PROGMEM = "81.09";
const char humidity516[] PROGMEM = "81.25";
const char humidity517[] PROGMEM = "81.41";
const char humidity518[] PROGMEM = "81.56";
const char humidity519[] PROGMEM = "81.72";
const char humidity520[] PROGMEM = "81.88";
const char humidity521[] PROGMEM = "82.04";
const char humidity522[] PROGMEM = "82.19";
const char humidity523[] PROGMEM = "82.35";
const char humidity524[] PROGMEM = "82.51";
const char humidity525[] PROGMEM = "82.67";
const char humidity526[] PROGMEM = "82.82";
const char humidity527[] PROGMEM = "82.98";
const char humidity528[] PROGMEM = "83.14";
const char humidity529[] PROGMEM = "83.30";
const char humidity530[] PROGMEM = "83.45";
const char humidity531[] PROGMEM = "83.61";
const char humidity532[] PROGMEM = "83.77";
const char humidity533[] PROGMEM = "83.93";
const char humidity534[] PROGMEM = "84.09";
const char humidity535[] PROGMEM = "84.24";
const char humidity536[] PROGMEM = "84.40";
const char humidity537[] PROGMEM = "84.56";
const char humidity538[] PROGMEM = "84.72";
const char humidity539[] PROGMEM = "84.87";
const char humidity540[] PROGMEM = "85.03";
const char humidity541[] PROGMEM = "85.19";
const char humidity542[] PROGMEM = "85.35";
const char humidity543[] PROGMEM = "85.50";
const char humidity544[] PROGMEM = "85.66";
const char humidity545[] PROGMEM = "85.82";
const char humidity546[] PROGMEM = "85.98";
const char humidity547[] PROGMEM = "86.14";
const char humidity548[] PROGMEM = "86.29";
const char humidity549[] PROGMEM = "86.45";
const char humidity550[] PROGMEM = "86.61";
const char humidity551[] PROGMEM = "86.77";
const char humidity552[] PROGMEM = "86.92";
const char humidity553[] PROGMEM = "87.08";
const char humidity554[] PROGMEM = "87.24";
const char humidity555[] PROGMEM = "87.40";
const char humidity556[] PROGMEM = "87.55";
const char humidity557[] PROGMEM = "87.71";
const char humidity558[] PROGMEM = "87.87";
const char humidity559[] PROGMEM = "88.03";
const char humidity560[] PROGMEM = "88.18";
const char humidity561[] PROGMEM = "88.34";
const char humidity562[] PROGMEM = "88.50";
const char humidity563[] PROGMEM = "88.66";
const char humidity564[] PROGMEM = "88.82";
const char humidity565[] PROGMEM = "88.97";
const char humidity566[] PROGMEM = "89.13";
const char humidity567[] PROGMEM = "89.29";
const char humidity568[] PROGMEM = "89.45";
const char humidity569[] PROGMEM = "89.60";
const char humidity570[] PROGMEM = "89.76";
const char humidity571[] PROGMEM = "89.92";
const char humidity572[] PROGMEM = "90.08";
const char humidity573[] PROGMEM = "90.23";
const char humidity574[] PROGMEM = "90.39";
const char humidity575[] PROGMEM = "90.55";
const char humidity576[] PROGMEM = "90.71";
const char humidity577[] PROGMEM = "90.86";
const char humidity578[] PROGMEM = "91.02";
const char humidity579[] PROGMEM = "91.18";
const char humidity580[] PROGMEM = "91.34";
const char humidity581[] PROGMEM = "91.50";
const char humidity582[] PROGMEM = "91.65";
const char humidity583[] PROGMEM = "91.81";
const char humidity584[] PROGMEM = "91.97";
const char humidity585[] PROGMEM = "92.13";
const char humidity586[] PROGMEM = "92.28";
const char humidity587[] PROGMEM = "92.44";
const char humidity588[] PROGMEM = "92.60";
const char humidity589[] PROGMEM = "92.76";
const char humidity590[] PROGMEM = "92.91";
const char humidity591[] PROGMEM = "93.07";
const char humidity592[] PROGMEM = "93.23";
const char humidity593[] PROGMEM = "93.39";
const char humidity594[] PROGMEM = "93.55";
const char humidity595[] PROGMEM = "93.70";
const char humidity596[] PROGMEM = "93.86";
const char humidity597[] PROGMEM = "94.02";
const char humidity598[] PROGMEM = "94.18";
const char humidity599[] PROGMEM = "94.33";
const char humidity600[] PROGMEM = "94.49";
const char humidity601[] PROGMEM = "94.65";
const char humidity602[] PROGMEM = "94.81";
const char humidity603[] PROGMEM = "94.96";
const char humidity604[] PROGMEM = "95.12";
const char humidity605[] PROGMEM = "95.28";
const char humidity606[] PROGMEM = "95.44";
const char humidity607[] PROGMEM = "95.59";
const char humidity608[] PROGMEM = "95.75";
const char humidity609[] PROGMEM = "95.91";
const char humidity610[] PROGMEM = "96.07";
const char humidity611[] PROGMEM = "96.23";
const char humidity612[] PROGMEM = "96.38";
const char humidity613[] PROGMEM = "96.54";
const char humidity614[] PROGMEM = "96.70";
const char humidity615[] PROGMEM = "96.86";
const char humidity616[] PROGMEM = "97.01";
const char humidity617[] PROGMEM = "97.17";
const char humidity618[] PROGMEM = "97.33";
const char humidity619[] PROGMEM = "97.49";
const char humidity620[] PROGMEM = "97.64";
const char humidity621[] PROGMEM = "97.80";
const char humidity622[] PROGMEM = "97.96";
const char humidity623[] PROGMEM = "98.12";
const char humidity624[] PROGMEM = "98.28";
const char humidity625[] PROGMEM = "98.43";
const char humidity626[] PROGMEM = "98.59";
const char humidity627[] PROGMEM = "98.75";
const char humidity628[] PROGMEM = "98.91";
const char humidity629[] PROGMEM = "99.06";
const char humidity630[] PROGMEM = "99.22";
const char humidity631[] PROGMEM = "99.38";
const char humidity632[] PROGMEM = "99.54";
const char humidity633[] PROGMEM = "99.69";
const char humidity634[] PROGMEM = "99.85";
const char humidity635[] PROGMEM = "100.00";

static PGM_P const humidityLookup[HUMIDITY_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
humidity0,
humidity1,
humidity2,
humidity3,
humidity4,
humidity5,
humidity6,
humidity7,
humidity8,
humidity9,
humidity10,
humidity11,
humidity12,
humidity13,
humidity14,
humidity15,
humidity16,
humidity17,
humidity18,
humidity19,
humidity20,
humidity21,
humidity22,
humidity23,
humidity24,
humidity25,
humidity26,
humidity27,
humidity28,
humidity29,
humidity30,
humidity31,
humidity32,
humidity33,
humidity34,
humidity35,
humidity36,
humidity37,
humidity38,
humidity39,
humidity40,
humidity41,
humidity42,
humidity43,
humidity44,
humidity45,
humidity46,
humidity47,
humidity48,
humidity49,
humidity50,
humidity51,
humidity52,
humidity53,
humidity54,
humidity55,
humidity56,
humidity57,
humidity58,
humidity59,
humidity60,
humidity61,
humidity62,
humidity63,
humidity64,
humidity65,
humidity66,
humidity67,
humidity68,
humidity69,
humidity70,
humidity71,
humidity72,
humidity73,
humidity74,
humidity75,
humidity76,
humidity77,
humidity78,
humidity79,
humidity80,
humidity81,
humidity82,
humidity83,
humidity84,
humidity85,
humidity86,
humidity87,
humidity88,
humidity89,
humidity90,
humidity91,
humidity92,
humidity93,
humidity94,
humidity95,
humidity96,
humidity97,
humidity98,
humidity99,
humidity100,
humidity101,
humidity102,
humidity103,
humidity104,
humidity105,
humidity106,
humidity107,
humidity108,
humidity109,
humidity110,
humidity111,
humidity112,
humidity113,
humidity114,
humidity115,
humidity116,
humidity117,
humidity118,
humidity119,
humidity120,
humidity121,
humidity122,
humidity123,
humidity124,
humidity125,
humidity126,
humidity127,
humidity128,
humidity129,
humidity130,
humidity131,
humidity132,
humidity133,
humidity134,
humidity135,
humidity136,
humidity137,
humidity138,
humidity139,
humidity140,
humidity141,
humidity142,
humidity143,
humidity144,
humidity145,
humidity146,
humidity147,
humidity148,
humidity149,
humidity150,
humidity151,
humidity152,
humidity153,
humidity154,
humidity155,
humidity156,
humidity157,
humidity158,
humidity159,
humidity160,
humidity161,
humidity162,
humidity163,
humidity164,
humidity165,
humidity166,
humidity167,
humidity168,
humidity169,
humidity170,
humidity171,
humidity172,
humidity173,
humidity174,
humidity175,
humidity176,
humidity177,
humidity178,
humidity179,
humidity180,
humidity181,
humidity182,
humidity183,
humidity184,
humidity185,
humidity186,
humidity187,
humidity188,
humidity189,
humidity190,
humidity191,
humidity192,
humidity193,
humidity194,
humidity195,
humidity196,
humidity197,
humidity198,
humidity199,
humidity200,
humidity201,
humidity202,
humidity203,
humidity204,
humidity205,
humidity206,
humidity207,
humidity208,
humidity209,
humidity210,
humidity211,
humidity212,
humidity213,
humidity214,
humidity215,
humidity216,
humidity217,
humidity218,
humidity219,
humidity220,
humidity221,
humidity222,
humidity223,
humidity224,
humidity225,
humidity226,
humidity227,
humidity228,
humidity229,
humidity230,
humidity231,
humidity232,
humidity233,
humidity234,
humidity235,
humidity236,
humidity237,
humidity238,
humidity239,
humidity240,
humidity241,
humidity242,
humidity243,
humidity244,
humidity245,
humidity246,
humidity247,
humidity248,
humidity249,
humidity250,
humidity251,
humidity252,
humidity253,
humidity254,
humidity255,
humidity256,
humidity257,
humidity258,
humidity259,
humidity260,
humidity261,
humidity262,
humidity263,
humidity264,
humidity265,
humidity266,
humidity267,
humidity268,
humidity269,
humidity270,
humidity271,
humidity272,
humidity273,
humidity274,
humidity275,
humidity276,
humidity277,
humidity278,
humidity279,
humidity280,
humidity281,
humidity282,
humidity283,
humidity284,
humidity285,
humidity286,
humidity287,
humidity288,
humidity289,
humidity290,
humidity291,
humidity292,
humidity293,
humidity294,
humidity295,
humidity296,
humidity297,
humidity298,
humidity299,
humidity300,
humidity301,
humidity302,
humidity303,
humidity304,
humidity305,
humidity306,
humidity307,
humidity308,
humidity309,
humidity310,
humidity311,
humidity312,
humidity313,
humidity314,
humidity315,
humidity316,
humidity317,
humidity318,
humidity319,
humidity320,
humidity321,
humidity322,
humidity323,
humidity324,
humidity325,
humidity326,
humidity327,
humidity328,
humidity329,
humidity330,
humidity331,
humidity332,
humidity333,
humidity334,
humidity335,
humidity336,
humidity337,
humidity338,
humidity339,
humidity340,
humidity341,
humidity342,
humidity343,
humidity344,
humidity345,
humidity346,
humidity347,
humidity348,
humidity349,
humidity350,
humidity351,
humidity352,
humidity353,
humidity354,
humidity355,
humidity356,
humidity357,
humidity358,
humidity359,
humidity360,
humidity361,
humidity362,
humidity363,
humidity364,
humidity365,
humidity366,
humidity367,
humidity368,
humidity369,
humidity370,
humidity371,
humidity372,
humidity373,
humidity374,
humidity375,
humidity376,
humidity377,
humidity378,
humidity379,
humidity380,
humidity381,
humidity382,
humidity383,
humidity384,
humidity385,
humidity386,
humidity387,
humidity388,
humidity389,
humidity390,
humidity391,
humidity392,
humidity393,
humidity394,
humidity395,
humidity396,
humidity397,
humidity398,
humidity399,
humidity400,
humidity401,
humidity402,
humidity403,
humidity404,
humidity405,
humidity406,
humidity407,
humidity408,
humidity409,
humidity410,
humidity411,
humidity412,
humidity413,
humidity414,
humidity415,
humidity416,
humidity417,
humidity418,
humidity419,
humidity420,
humidity421,
humidity422,
humidity423,
humidity424,
humidity425,
humidity426,
humidity427,
humidity428,
humidity429,
humidity430,
humidity431,
humidity432,
humidity433,
humidity434,
humidity435,
humidity436,
humidity437,
humidity438,
humidity439,
humidity440,
humidity441,
humidity442,
humidity443,
humidity444,
humidity445,
humidity446,
humidity447,
humidity448,
humidity449,
humidity450,
humidity451,
humidity452,
humidity453,
humidity454,
humidity455,
humidity456,
humidity457,
humidity458,
humidity459,
humidity460,
humidity461,
humidity462,
humidity463,
humidity464,
humidity465,
humidity466,
humidity467,
humidity468,
humidity469,
humidity470,
humidity471,
humidity472,
humidity473,
humidity474,
humidity475,
humidity476,
humidity477,
humidity478,
humidity479,
humidity480,
humidity481,
humidity482,
humidity483,
humidity484,
humidity485,
humidity486,
humidity487,
humidity488,
humidity489,
humidity490,
humidity491,
humidity492,
humidity493,
humidity494,
humidity495,
humidity496,
humidity497,
humidity498,
humidity499,
humidity500,
humidity501,
humidity502,
humidity503,
humidity504,
humidity505,
humidity506,
humidity507,
humidity508,
humidity509,
humidity510,
humidity511,
humidity512,
humidity513,
humidity514,
humidity515,
humidity516,
humidity517,
humidity518,
humidity519,
humidity520,
humidity521,
humidity522,
humidity523,
humidity524,
humidity525,
humidity526,
humidity527,
humidity528,
humidity529,
humidity530,
humidity531,
humidity532,
humidity533,
humidity534,
humidity535,
humidity536,
humidity537,
humidity538,
humidity539,
humidity540,
humidity541,
humidity542,
humidity543,
humidity544,
humidity545,
humidity546,
humidity547,
humidity548,
humidity549,
humidity550,
humidity551,
humidity552,
humidity553,
humidity554,
humidity555,
humidity556,
humidity557,
humidity558,
humidity559,
humidity560,
humidity561,
humidity562,
humidity563,
humidity564,
humidity565,
humidity566,
humidity567,
humidity568,
humidity569,
humidity570,
humidity571,
humidity572,
humidity573,
humidity574,
humidity575,
humidity576,
humidity577,
humidity578,
humidity579,
humidity580,
humidity581,
humidity582,
humidity583,
humidity584,
humidity585,
humidity586,
humidity587,
humidity588,
humidity589,
humidity590,
humidity591,
humidity592,
humidity593,
humidity594,
humidity595,
humidity596,
humidity597,
humidity598,
humidity599,
humidity600,
humidity601,
humidity602,
humidity603,
humidity604,
humidity605,
humidity606,
humidity607,
humidity608,
humidity609,
humidity610,
humidity611,
humidity612,
humidity613,
humidity614,
humidity615,
humidity616,
humidity617,
humidity618,
humidity619,
humidity620,
humidity621,
humidity622,
humidity623,
humidity624,
humidity625,
humidity626,
humidity627,
humidity628,
humidity629,
humidity630,
humidity631,
humidity632,
humidity633,
humidity634,
humidity635
};

#endif
