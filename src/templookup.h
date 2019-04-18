#include <avr/pgmspace.h>

#ifndef _INCL_TEMPLOOKUP
#define _INCL_TEMPLOOKUP

#define TEMP_LOOKUP_BUFFER_SIZE			 532

#define ADC_TEMP_OFFSET					 51

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
const char temp0[] PROGMEM = "-50.25";
const char temp1[] PROGMEM = "-50.03";
const char temp2[] PROGMEM = "-49.82";
const char temp3[] PROGMEM = "-49.60";
const char temp4[] PROGMEM = "-49.38";
const char temp5[] PROGMEM = "-49.16";
const char temp6[] PROGMEM = "-48.95";
const char temp7[] PROGMEM = "-48.73";
const char temp8[] PROGMEM = "-48.51";
const char temp9[] PROGMEM = "-48.29";
const char temp10[] PROGMEM = "-48.08";
const char temp11[] PROGMEM = "-47.86";
const char temp12[] PROGMEM = "-47.64";
const char temp13[] PROGMEM = "-47.43";
const char temp14[] PROGMEM = "-47.21";
const char temp15[] PROGMEM = "-46.99";
const char temp16[] PROGMEM = "-46.77";
const char temp17[] PROGMEM = "-46.56";
const char temp18[] PROGMEM = "-46.34";
const char temp19[] PROGMEM = "-46.12";
const char temp20[] PROGMEM = "-45.91";
const char temp21[] PROGMEM = "-45.69";
const char temp22[] PROGMEM = "-45.47";
const char temp23[] PROGMEM = "-45.25";
const char temp24[] PROGMEM = "-45.04";
const char temp25[] PROGMEM = "-44.82";
const char temp26[] PROGMEM = "-44.60";
const char temp27[] PROGMEM = "-44.38";
const char temp28[] PROGMEM = "-44.17";
const char temp29[] PROGMEM = "-43.95";
const char temp30[] PROGMEM = "-43.73";
const char temp31[] PROGMEM = "-43.52";
const char temp32[] PROGMEM = "-43.30";
const char temp33[] PROGMEM = "-43.08";
const char temp34[] PROGMEM = "-42.86";
const char temp35[] PROGMEM = "-42.65";
const char temp36[] PROGMEM = "-42.43";
const char temp37[] PROGMEM = "-42.21";
const char temp38[] PROGMEM = "-42.00";
const char temp39[] PROGMEM = "-41.78";
const char temp40[] PROGMEM = "-41.56";
const char temp41[] PROGMEM = "-41.34";
const char temp42[] PROGMEM = "-41.13";
const char temp43[] PROGMEM = "-40.91";
const char temp44[] PROGMEM = "-40.69";
const char temp45[] PROGMEM = "-40.47";
const char temp46[] PROGMEM = "-40.26";
const char temp47[] PROGMEM = "-40.04";
const char temp48[] PROGMEM = "-39.82";
const char temp49[] PROGMEM = "-39.61";
const char temp50[] PROGMEM = "-39.39";
const char temp51[] PROGMEM = "-39.17";
const char temp52[] PROGMEM = "-38.95";
const char temp53[] PROGMEM = "-38.74";
const char temp54[] PROGMEM = "-38.52";
const char temp55[] PROGMEM = "-38.30";
const char temp56[] PROGMEM = "-38.09";
const char temp57[] PROGMEM = "-37.87";
const char temp58[] PROGMEM = "-37.65";
const char temp59[] PROGMEM = "-37.43";
const char temp60[] PROGMEM = "-37.22";
const char temp61[] PROGMEM = "-37.00";
const char temp62[] PROGMEM = "-36.78";
const char temp63[] PROGMEM = "-36.56";
const char temp64[] PROGMEM = "-36.35";
const char temp65[] PROGMEM = "-36.13";
const char temp66[] PROGMEM = "-35.91";
const char temp67[] PROGMEM = "-35.70";
const char temp68[] PROGMEM = "-35.48";
const char temp69[] PROGMEM = "-35.26";
const char temp70[] PROGMEM = "-35.04";
const char temp71[] PROGMEM = "-34.83";
const char temp72[] PROGMEM = "-34.61";
const char temp73[] PROGMEM = "-34.39";
const char temp74[] PROGMEM = "-34.18";
const char temp75[] PROGMEM = "-33.96";
const char temp76[] PROGMEM = "-33.74";
const char temp77[] PROGMEM = "-33.52";
const char temp78[] PROGMEM = "-33.31";
const char temp79[] PROGMEM = "-33.09";
const char temp80[] PROGMEM = "-32.87";
const char temp81[] PROGMEM = "-32.65";
const char temp82[] PROGMEM = "-32.44";
const char temp83[] PROGMEM = "-32.22";
const char temp84[] PROGMEM = "-32.00";
const char temp85[] PROGMEM = "-31.79";
const char temp86[] PROGMEM = "-31.57";
const char temp87[] PROGMEM = "-31.35";
const char temp88[] PROGMEM = "-31.13";
const char temp89[] PROGMEM = "-30.92";
const char temp90[] PROGMEM = "-30.70";
const char temp91[] PROGMEM = "-30.48";
const char temp92[] PROGMEM = "-30.27";
const char temp93[] PROGMEM = "-30.05";
const char temp94[] PROGMEM = "-29.83";
const char temp95[] PROGMEM = "-29.61";
const char temp96[] PROGMEM = "-29.40";
const char temp97[] PROGMEM = "-29.18";
const char temp98[] PROGMEM = "-28.96";
const char temp99[] PROGMEM = "-28.74";
const char temp100[] PROGMEM = "-28.53";
const char temp101[] PROGMEM = "-28.31";
const char temp102[] PROGMEM = "-28.09";
const char temp103[] PROGMEM = "-27.88";
const char temp104[] PROGMEM = "-27.66";
const char temp105[] PROGMEM = "-27.44";
const char temp106[] PROGMEM = "-27.22";
const char temp107[] PROGMEM = "-27.01";
const char temp108[] PROGMEM = "-26.79";
const char temp109[] PROGMEM = "-26.57";
const char temp110[] PROGMEM = "-26.35";
const char temp111[] PROGMEM = "-26.14";
const char temp112[] PROGMEM = "-25.92";
const char temp113[] PROGMEM = "-25.70";
const char temp114[] PROGMEM = "-25.49";
const char temp115[] PROGMEM = "-25.27";
const char temp116[] PROGMEM = "-25.05";
const char temp117[] PROGMEM = "-24.83";
const char temp118[] PROGMEM = "-24.62";
const char temp119[] PROGMEM = "-24.40";
const char temp120[] PROGMEM = "-24.18";
const char temp121[] PROGMEM = "-23.97";
const char temp122[] PROGMEM = "-23.75";
const char temp123[] PROGMEM = "-23.53";
const char temp124[] PROGMEM = "-23.31";
const char temp125[] PROGMEM = "-23.10";
const char temp126[] PROGMEM = "-22.88";
const char temp127[] PROGMEM = "-22.66";
const char temp128[] PROGMEM = "-22.44";
const char temp129[] PROGMEM = "-22.23";
const char temp130[] PROGMEM = "-22.01";
const char temp131[] PROGMEM = "-21.79";
const char temp132[] PROGMEM = "-21.58";
const char temp133[] PROGMEM = "-21.36";
const char temp134[] PROGMEM = "-21.14";
const char temp135[] PROGMEM = "-20.92";
const char temp136[] PROGMEM = "-20.71";
const char temp137[] PROGMEM = "-20.49";
const char temp138[] PROGMEM = "-20.27";
const char temp139[] PROGMEM = "-20.06";
const char temp140[] PROGMEM = "-19.84";
const char temp141[] PROGMEM = "-19.62";
const char temp142[] PROGMEM = "-19.40";
const char temp143[] PROGMEM = "-19.19";
const char temp144[] PROGMEM = "-18.97";
const char temp145[] PROGMEM = "-18.75";
const char temp146[] PROGMEM = "-18.53";
const char temp147[] PROGMEM = "-18.32";
const char temp148[] PROGMEM = "-18.10";
const char temp149[] PROGMEM = "-17.88";
const char temp150[] PROGMEM = "-17.67";
const char temp151[] PROGMEM = "-17.45";
const char temp152[] PROGMEM = "-17.23";
const char temp153[] PROGMEM = "-17.01";
const char temp154[] PROGMEM = "-16.80";
const char temp155[] PROGMEM = "-16.58";
const char temp156[] PROGMEM = "-16.36";
const char temp157[] PROGMEM = "-16.15";
const char temp158[] PROGMEM = "-15.93";
const char temp159[] PROGMEM = "-15.71";
const char temp160[] PROGMEM = "-15.49";
const char temp161[] PROGMEM = "-15.28";
const char temp162[] PROGMEM = "-15.06";
const char temp163[] PROGMEM = "-14.84";
const char temp164[] PROGMEM = "-14.62";
const char temp165[] PROGMEM = "-14.41";
const char temp166[] PROGMEM = "-14.19";
const char temp167[] PROGMEM = "-13.97";
const char temp168[] PROGMEM = "-13.76";
const char temp169[] PROGMEM = "-13.54";
const char temp170[] PROGMEM = "-13.32";
const char temp171[] PROGMEM = "-13.10";
const char temp172[] PROGMEM = "-12.89";
const char temp173[] PROGMEM = "-12.67";
const char temp174[] PROGMEM = "-12.45";
const char temp175[] PROGMEM = "-12.24";
const char temp176[] PROGMEM = "-12.02";
const char temp177[] PROGMEM = "-11.80";
const char temp178[] PROGMEM = "-11.58";
const char temp179[] PROGMEM = "-11.37";
const char temp180[] PROGMEM = "-11.15";
const char temp181[] PROGMEM = "-10.93";
const char temp182[] PROGMEM = "-10.71";
const char temp183[] PROGMEM = "-10.50";
const char temp184[] PROGMEM = "-10.28";
const char temp185[] PROGMEM = "-10.06";
const char temp186[] PROGMEM = "-9.85";
const char temp187[] PROGMEM = "-9.63";
const char temp188[] PROGMEM = "-9.41";
const char temp189[] PROGMEM = "-9.19";
const char temp190[] PROGMEM = "-8.98";
const char temp191[] PROGMEM = "-8.76";
const char temp192[] PROGMEM = "-8.54";
const char temp193[] PROGMEM = "-8.33";
const char temp194[] PROGMEM = "-8.11";
const char temp195[] PROGMEM = "-7.89";
const char temp196[] PROGMEM = "-7.67";
const char temp197[] PROGMEM = "-7.46";
const char temp198[] PROGMEM = "-7.24";
const char temp199[] PROGMEM = "-7.02";
const char temp200[] PROGMEM = "-6.80";
const char temp201[] PROGMEM = "-6.59";
const char temp202[] PROGMEM = "-6.37";
const char temp203[] PROGMEM = "-6.15";
const char temp204[] PROGMEM = "-5.94";
const char temp205[] PROGMEM = "-5.72";
const char temp206[] PROGMEM = "-5.50";
const char temp207[] PROGMEM = "-5.28";
const char temp208[] PROGMEM = "-5.07";
const char temp209[] PROGMEM = "-4.85";
const char temp210[] PROGMEM = "-4.63";
const char temp211[] PROGMEM = "-4.42";
const char temp212[] PROGMEM = "-4.20";
const char temp213[] PROGMEM = "-3.98";
const char temp214[] PROGMEM = "-3.76";
const char temp215[] PROGMEM = "-3.55";
const char temp216[] PROGMEM = "-3.33";
const char temp217[] PROGMEM = "-3.11";
const char temp218[] PROGMEM = "-2.89";
const char temp219[] PROGMEM = "-2.68";
const char temp220[] PROGMEM = "-2.46";
const char temp221[] PROGMEM = "-2.24";
const char temp222[] PROGMEM = "-2.03";
const char temp223[] PROGMEM = "-1.81";
const char temp224[] PROGMEM = "-1.59";
const char temp225[] PROGMEM = "-1.37";
const char temp226[] PROGMEM = "-1.16";
const char temp227[] PROGMEM = "-0.94";
const char temp228[] PROGMEM = "-0.72";
const char temp229[] PROGMEM = "-0.51";
const char temp230[] PROGMEM = "-0.29";
const char temp231[] PROGMEM = "-0.07";
const char temp232[] PROGMEM = "0.15";
const char temp233[] PROGMEM = "0.36";
const char temp234[] PROGMEM = "0.58";
const char temp235[] PROGMEM = "0.80";
const char temp236[] PROGMEM = "1.02";
const char temp237[] PROGMEM = "1.23";
const char temp238[] PROGMEM = "1.45";
const char temp239[] PROGMEM = "1.67";
const char temp240[] PROGMEM = "1.88";
const char temp241[] PROGMEM = "2.10";
const char temp242[] PROGMEM = "2.32";
const char temp243[] PROGMEM = "2.54";
const char temp244[] PROGMEM = "2.75";
const char temp245[] PROGMEM = "2.97";
const char temp246[] PROGMEM = "3.19";
const char temp247[] PROGMEM = "3.41";
const char temp248[] PROGMEM = "3.62";
const char temp249[] PROGMEM = "3.84";
const char temp250[] PROGMEM = "4.06";
const char temp251[] PROGMEM = "4.27";
const char temp252[] PROGMEM = "4.49";
const char temp253[] PROGMEM = "4.71";
const char temp254[] PROGMEM = "4.93";
const char temp255[] PROGMEM = "5.14";
const char temp256[] PROGMEM = "5.36";
const char temp257[] PROGMEM = "5.58";
const char temp258[] PROGMEM = "5.79";
const char temp259[] PROGMEM = "6.01";
const char temp260[] PROGMEM = "6.23";
const char temp261[] PROGMEM = "6.45";
const char temp262[] PROGMEM = "6.66";
const char temp263[] PROGMEM = "6.88";
const char temp264[] PROGMEM = "7.10";
const char temp265[] PROGMEM = "7.32";
const char temp266[] PROGMEM = "7.53";
const char temp267[] PROGMEM = "7.75";
const char temp268[] PROGMEM = "7.97";
const char temp269[] PROGMEM = "8.18";
const char temp270[] PROGMEM = "8.40";
const char temp271[] PROGMEM = "8.62";
const char temp272[] PROGMEM = "8.84";
const char temp273[] PROGMEM = "9.05";
const char temp274[] PROGMEM = "9.27";
const char temp275[] PROGMEM = "9.49";
const char temp276[] PROGMEM = "9.70";
const char temp277[] PROGMEM = "9.92";
const char temp278[] PROGMEM = "10.14";
const char temp279[] PROGMEM = "10.36";
const char temp280[] PROGMEM = "10.57";
const char temp281[] PROGMEM = "10.79";
const char temp282[] PROGMEM = "11.01";
const char temp283[] PROGMEM = "11.23";
const char temp284[] PROGMEM = "11.44";
const char temp285[] PROGMEM = "11.66";
const char temp286[] PROGMEM = "11.88";
const char temp287[] PROGMEM = "12.09";
const char temp288[] PROGMEM = "12.31";
const char temp289[] PROGMEM = "12.53";
const char temp290[] PROGMEM = "12.75";
const char temp291[] PROGMEM = "12.96";
const char temp292[] PROGMEM = "13.18";
const char temp293[] PROGMEM = "13.40";
const char temp294[] PROGMEM = "13.61";
const char temp295[] PROGMEM = "13.83";
const char temp296[] PROGMEM = "14.05";
const char temp297[] PROGMEM = "14.27";
const char temp298[] PROGMEM = "14.48";
const char temp299[] PROGMEM = "14.70";
const char temp300[] PROGMEM = "14.92";
const char temp301[] PROGMEM = "15.14";
const char temp302[] PROGMEM = "15.35";
const char temp303[] PROGMEM = "15.57";
const char temp304[] PROGMEM = "15.79";
const char temp305[] PROGMEM = "16.00";
const char temp306[] PROGMEM = "16.22";
const char temp307[] PROGMEM = "16.44";
const char temp308[] PROGMEM = "16.66";
const char temp309[] PROGMEM = "16.87";
const char temp310[] PROGMEM = "17.09";
const char temp311[] PROGMEM = "17.31";
const char temp312[] PROGMEM = "17.52";
const char temp313[] PROGMEM = "17.74";
const char temp314[] PROGMEM = "17.96";
const char temp315[] PROGMEM = "18.18";
const char temp316[] PROGMEM = "18.39";
const char temp317[] PROGMEM = "18.61";
const char temp318[] PROGMEM = "18.83";
const char temp319[] PROGMEM = "19.05";
const char temp320[] PROGMEM = "19.26";
const char temp321[] PROGMEM = "19.48";
const char temp322[] PROGMEM = "19.70";
const char temp323[] PROGMEM = "19.91";
const char temp324[] PROGMEM = "20.13";
const char temp325[] PROGMEM = "20.35";
const char temp326[] PROGMEM = "20.57";
const char temp327[] PROGMEM = "20.78";
const char temp328[] PROGMEM = "21.00";
const char temp329[] PROGMEM = "21.22";
const char temp330[] PROGMEM = "21.43";
const char temp331[] PROGMEM = "21.65";
const char temp332[] PROGMEM = "21.87";
const char temp333[] PROGMEM = "22.09";
const char temp334[] PROGMEM = "22.30";
const char temp335[] PROGMEM = "22.52";
const char temp336[] PROGMEM = "22.74";
const char temp337[] PROGMEM = "22.96";
const char temp338[] PROGMEM = "23.17";
const char temp339[] PROGMEM = "23.39";
const char temp340[] PROGMEM = "23.61";
const char temp341[] PROGMEM = "23.82";
const char temp342[] PROGMEM = "24.04";
const char temp343[] PROGMEM = "24.26";
const char temp344[] PROGMEM = "24.48";
const char temp345[] PROGMEM = "24.69";
const char temp346[] PROGMEM = "24.91";
const char temp347[] PROGMEM = "25.13";
const char temp348[] PROGMEM = "25.34";
const char temp349[] PROGMEM = "25.56";
const char temp350[] PROGMEM = "25.78";
const char temp351[] PROGMEM = "26.00";
const char temp352[] PROGMEM = "26.21";
const char temp353[] PROGMEM = "26.43";
const char temp354[] PROGMEM = "26.65";
const char temp355[] PROGMEM = "26.87";
const char temp356[] PROGMEM = "27.08";
const char temp357[] PROGMEM = "27.30";
const char temp358[] PROGMEM = "27.52";
const char temp359[] PROGMEM = "27.73";
const char temp360[] PROGMEM = "27.95";
const char temp361[] PROGMEM = "28.17";
const char temp362[] PROGMEM = "28.39";
const char temp363[] PROGMEM = "28.60";
const char temp364[] PROGMEM = "28.82";
const char temp365[] PROGMEM = "29.04";
const char temp366[] PROGMEM = "29.25";
const char temp367[] PROGMEM = "29.47";
const char temp368[] PROGMEM = "29.69";
const char temp369[] PROGMEM = "29.91";
const char temp370[] PROGMEM = "30.12";
const char temp371[] PROGMEM = "30.34";
const char temp372[] PROGMEM = "30.56";
const char temp373[] PROGMEM = "30.78";
const char temp374[] PROGMEM = "30.99";
const char temp375[] PROGMEM = "31.21";
const char temp376[] PROGMEM = "31.43";
const char temp377[] PROGMEM = "31.64";
const char temp378[] PROGMEM = "31.86";
const char temp379[] PROGMEM = "32.08";
const char temp380[] PROGMEM = "32.30";
const char temp381[] PROGMEM = "32.51";
const char temp382[] PROGMEM = "32.73";
const char temp383[] PROGMEM = "32.95";
const char temp384[] PROGMEM = "33.16";
const char temp385[] PROGMEM = "33.38";
const char temp386[] PROGMEM = "33.60";
const char temp387[] PROGMEM = "33.82";
const char temp388[] PROGMEM = "34.03";
const char temp389[] PROGMEM = "34.25";
const char temp390[] PROGMEM = "34.47";
const char temp391[] PROGMEM = "34.69";
const char temp392[] PROGMEM = "34.90";
const char temp393[] PROGMEM = "35.12";
const char temp394[] PROGMEM = "35.34";
const char temp395[] PROGMEM = "35.55";
const char temp396[] PROGMEM = "35.77";
const char temp397[] PROGMEM = "35.99";
const char temp398[] PROGMEM = "36.21";
const char temp399[] PROGMEM = "36.42";
const char temp400[] PROGMEM = "36.64";
const char temp401[] PROGMEM = "36.86";
const char temp402[] PROGMEM = "37.08";
const char temp403[] PROGMEM = "37.29";
const char temp404[] PROGMEM = "37.51";
const char temp405[] PROGMEM = "37.73";
const char temp406[] PROGMEM = "37.94";
const char temp407[] PROGMEM = "38.16";
const char temp408[] PROGMEM = "38.38";
const char temp409[] PROGMEM = "38.60";
const char temp410[] PROGMEM = "38.81";
const char temp411[] PROGMEM = "39.03";
const char temp412[] PROGMEM = "39.25";
const char temp413[] PROGMEM = "39.46";
const char temp414[] PROGMEM = "39.68";
const char temp415[] PROGMEM = "39.90";
const char temp416[] PROGMEM = "40.12";
const char temp417[] PROGMEM = "40.33";
const char temp418[] PROGMEM = "40.55";
const char temp419[] PROGMEM = "40.77";
const char temp420[] PROGMEM = "40.99";
const char temp421[] PROGMEM = "41.20";
const char temp422[] PROGMEM = "41.42";
const char temp423[] PROGMEM = "41.64";
const char temp424[] PROGMEM = "41.85";
const char temp425[] PROGMEM = "42.07";
const char temp426[] PROGMEM = "42.29";
const char temp427[] PROGMEM = "42.51";
const char temp428[] PROGMEM = "42.72";
const char temp429[] PROGMEM = "42.94";
const char temp430[] PROGMEM = "43.16";
const char temp431[] PROGMEM = "43.37";
const char temp432[] PROGMEM = "43.59";
const char temp433[] PROGMEM = "43.81";
const char temp434[] PROGMEM = "44.03";
const char temp435[] PROGMEM = "44.24";
const char temp436[] PROGMEM = "44.46";
const char temp437[] PROGMEM = "44.68";
const char temp438[] PROGMEM = "44.90";
const char temp439[] PROGMEM = "45.11";
const char temp440[] PROGMEM = "45.33";
const char temp441[] PROGMEM = "45.55";
const char temp442[] PROGMEM = "45.76";
const char temp443[] PROGMEM = "45.98";
const char temp444[] PROGMEM = "46.20";
const char temp445[] PROGMEM = "46.42";
const char temp446[] PROGMEM = "46.63";
const char temp447[] PROGMEM = "46.85";
const char temp448[] PROGMEM = "47.07";
const char temp449[] PROGMEM = "47.28";
const char temp450[] PROGMEM = "47.50";
const char temp451[] PROGMEM = "47.72";
const char temp452[] PROGMEM = "47.94";
const char temp453[] PROGMEM = "48.15";
const char temp454[] PROGMEM = "48.37";
const char temp455[] PROGMEM = "48.59";
const char temp456[] PROGMEM = "48.81";
const char temp457[] PROGMEM = "49.02";
const char temp458[] PROGMEM = "49.24";
const char temp459[] PROGMEM = "49.46";
const char temp460[] PROGMEM = "49.67";
const char temp461[] PROGMEM = "49.89";
const char temp462[] PROGMEM = "50.11";
const char temp463[] PROGMEM = "50.33";
const char temp464[] PROGMEM = "50.54";
const char temp465[] PROGMEM = "50.76";
const char temp466[] PROGMEM = "50.98";
const char temp467[] PROGMEM = "51.19";
const char temp468[] PROGMEM = "51.41";
const char temp469[] PROGMEM = "51.63";
const char temp470[] PROGMEM = "51.85";
const char temp471[] PROGMEM = "52.06";
const char temp472[] PROGMEM = "52.28";
const char temp473[] PROGMEM = "52.50";
const char temp474[] PROGMEM = "52.72";
const char temp475[] PROGMEM = "52.93";
const char temp476[] PROGMEM = "53.15";
const char temp477[] PROGMEM = "53.37";
const char temp478[] PROGMEM = "53.58";
const char temp479[] PROGMEM = "53.80";
const char temp480[] PROGMEM = "54.02";
const char temp481[] PROGMEM = "54.24";
const char temp482[] PROGMEM = "54.45";
const char temp483[] PROGMEM = "54.67";
const char temp484[] PROGMEM = "54.89";
const char temp485[] PROGMEM = "55.10";
const char temp486[] PROGMEM = "55.32";
const char temp487[] PROGMEM = "55.54";
const char temp488[] PROGMEM = "55.76";
const char temp489[] PROGMEM = "55.97";
const char temp490[] PROGMEM = "56.19";
const char temp491[] PROGMEM = "56.41";
const char temp492[] PROGMEM = "56.63";
const char temp493[] PROGMEM = "56.84";
const char temp494[] PROGMEM = "57.06";
const char temp495[] PROGMEM = "57.28";
const char temp496[] PROGMEM = "57.49";
const char temp497[] PROGMEM = "57.71";
const char temp498[] PROGMEM = "57.93";
const char temp499[] PROGMEM = "58.15";
const char temp500[] PROGMEM = "58.36";
const char temp501[] PROGMEM = "58.58";
const char temp502[] PROGMEM = "58.80";
const char temp503[] PROGMEM = "59.01";
const char temp504[] PROGMEM = "59.23";
const char temp505[] PROGMEM = "59.45";
const char temp506[] PROGMEM = "59.67";
const char temp507[] PROGMEM = "59.88";
const char temp508[] PROGMEM = "60.10";
const char temp509[] PROGMEM = "60.32";
const char temp510[] PROGMEM = "60.54";
const char temp511[] PROGMEM = "60.75";
const char temp512[] PROGMEM = "60.97";
const char temp513[] PROGMEM = "61.19";
const char temp514[] PROGMEM = "61.40";
const char temp515[] PROGMEM = "61.62";
const char temp516[] PROGMEM = "61.84";
const char temp517[] PROGMEM = "62.06";
const char temp518[] PROGMEM = "62.27";
const char temp519[] PROGMEM = "62.49";
const char temp520[] PROGMEM = "62.71";
const char temp521[] PROGMEM = "62.92";
const char temp522[] PROGMEM = "63.14";
const char temp523[] PROGMEM = "63.36";
const char temp524[] PROGMEM = "63.58";
const char temp525[] PROGMEM = "63.79";
const char temp526[] PROGMEM = "64.01";
const char temp527[] PROGMEM = "64.23";
const char temp528[] PROGMEM = "64.45";
const char temp529[] PROGMEM = "64.66";
const char temp530[] PROGMEM = "64.88";
const char temp531[] PROGMEM = "65.10";

static PGM_P const tempLookup[TEMP_LOOKUP_BUFFER_SIZE] PROGMEM = 
{
temp0,
temp1,
temp2,
temp3,
temp4,
temp5,
temp6,
temp7,
temp8,
temp9,
temp10,
temp11,
temp12,
temp13,
temp14,
temp15,
temp16,
temp17,
temp18,
temp19,
temp20,
temp21,
temp22,
temp23,
temp24,
temp25,
temp26,
temp27,
temp28,
temp29,
temp30,
temp31,
temp32,
temp33,
temp34,
temp35,
temp36,
temp37,
temp38,
temp39,
temp40,
temp41,
temp42,
temp43,
temp44,
temp45,
temp46,
temp47,
temp48,
temp49,
temp50,
temp51,
temp52,
temp53,
temp54,
temp55,
temp56,
temp57,
temp58,
temp59,
temp60,
temp61,
temp62,
temp63,
temp64,
temp65,
temp66,
temp67,
temp68,
temp69,
temp70,
temp71,
temp72,
temp73,
temp74,
temp75,
temp76,
temp77,
temp78,
temp79,
temp80,
temp81,
temp82,
temp83,
temp84,
temp85,
temp86,
temp87,
temp88,
temp89,
temp90,
temp91,
temp92,
temp93,
temp94,
temp95,
temp96,
temp97,
temp98,
temp99,
temp100,
temp101,
temp102,
temp103,
temp104,
temp105,
temp106,
temp107,
temp108,
temp109,
temp110,
temp111,
temp112,
temp113,
temp114,
temp115,
temp116,
temp117,
temp118,
temp119,
temp120,
temp121,
temp122,
temp123,
temp124,
temp125,
temp126,
temp127,
temp128,
temp129,
temp130,
temp131,
temp132,
temp133,
temp134,
temp135,
temp136,
temp137,
temp138,
temp139,
temp140,
temp141,
temp142,
temp143,
temp144,
temp145,
temp146,
temp147,
temp148,
temp149,
temp150,
temp151,
temp152,
temp153,
temp154,
temp155,
temp156,
temp157,
temp158,
temp159,
temp160,
temp161,
temp162,
temp163,
temp164,
temp165,
temp166,
temp167,
temp168,
temp169,
temp170,
temp171,
temp172,
temp173,
temp174,
temp175,
temp176,
temp177,
temp178,
temp179,
temp180,
temp181,
temp182,
temp183,
temp184,
temp185,
temp186,
temp187,
temp188,
temp189,
temp190,
temp191,
temp192,
temp193,
temp194,
temp195,
temp196,
temp197,
temp198,
temp199,
temp200,
temp201,
temp202,
temp203,
temp204,
temp205,
temp206,
temp207,
temp208,
temp209,
temp210,
temp211,
temp212,
temp213,
temp214,
temp215,
temp216,
temp217,
temp218,
temp219,
temp220,
temp221,
temp222,
temp223,
temp224,
temp225,
temp226,
temp227,
temp228,
temp229,
temp230,
temp231,
temp232,
temp233,
temp234,
temp235,
temp236,
temp237,
temp238,
temp239,
temp240,
temp241,
temp242,
temp243,
temp244,
temp245,
temp246,
temp247,
temp248,
temp249,
temp250,
temp251,
temp252,
temp253,
temp254,
temp255,
temp256,
temp257,
temp258,
temp259,
temp260,
temp261,
temp262,
temp263,
temp264,
temp265,
temp266,
temp267,
temp268,
temp269,
temp270,
temp271,
temp272,
temp273,
temp274,
temp275,
temp276,
temp277,
temp278,
temp279,
temp280,
temp281,
temp282,
temp283,
temp284,
temp285,
temp286,
temp287,
temp288,
temp289,
temp290,
temp291,
temp292,
temp293,
temp294,
temp295,
temp296,
temp297,
temp298,
temp299,
temp300,
temp301,
temp302,
temp303,
temp304,
temp305,
temp306,
temp307,
temp308,
temp309,
temp310,
temp311,
temp312,
temp313,
temp314,
temp315,
temp316,
temp317,
temp318,
temp319,
temp320,
temp321,
temp322,
temp323,
temp324,
temp325,
temp326,
temp327,
temp328,
temp329,
temp330,
temp331,
temp332,
temp333,
temp334,
temp335,
temp336,
temp337,
temp338,
temp339,
temp340,
temp341,
temp342,
temp343,
temp344,
temp345,
temp346,
temp347,
temp348,
temp349,
temp350,
temp351,
temp352,
temp353,
temp354,
temp355,
temp356,
temp357,
temp358,
temp359,
temp360,
temp361,
temp362,
temp363,
temp364,
temp365,
temp366,
temp367,
temp368,
temp369,
temp370,
temp371,
temp372,
temp373,
temp374,
temp375,
temp376,
temp377,
temp378,
temp379,
temp380,
temp381,
temp382,
temp383,
temp384,
temp385,
temp386,
temp387,
temp388,
temp389,
temp390,
temp391,
temp392,
temp393,
temp394,
temp395,
temp396,
temp397,
temp398,
temp399,
temp400,
temp401,
temp402,
temp403,
temp404,
temp405,
temp406,
temp407,
temp408,
temp409,
temp410,
temp411,
temp412,
temp413,
temp414,
temp415,
temp416,
temp417,
temp418,
temp419,
temp420,
temp421,
temp422,
temp423,
temp424,
temp425,
temp426,
temp427,
temp428,
temp429,
temp430,
temp431,
temp432,
temp433,
temp434,
temp435,
temp436,
temp437,
temp438,
temp439,
temp440,
temp441,
temp442,
temp443,
temp444,
temp445,
temp446,
temp447,
temp448,
temp449,
temp450,
temp451,
temp452,
temp453,
temp454,
temp455,
temp456,
temp457,
temp458,
temp459,
temp460,
temp461,
temp462,
temp463,
temp464,
temp465,
temp466,
temp467,
temp468,
temp469,
temp470,
temp471,
temp472,
temp473,
temp474,
temp475,
temp476,
temp477,
temp478,
temp479,
temp480,
temp481,
temp482,
temp483,
temp484,
temp485,
temp486,
temp487,
temp488,
temp489,
temp490,
temp491,
temp492,
temp493,
temp494,
temp495,
temp496,
temp497,
temp498,
temp499,
temp500,
temp501,
temp502,
temp503,
temp504,
temp505,
temp506,
temp507,
temp508,
temp509,
temp510,
temp511,
temp512,
temp513,
temp514,
temp515,
temp516,
temp517,
temp518,
temp519,
temp520,
temp521,
temp522,
temp523,
temp524,
temp525,
temp526,
temp527,
temp528,
temp529,
temp530,
temp531
};

#endif
