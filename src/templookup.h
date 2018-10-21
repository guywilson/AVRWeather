#include <avr/pgmspace.h>

#ifndef _INCL_TEMPLOOKUP
#define _INCL_TEMPLOOKUP

#define TEMP_LOOKUP_BUFFER_SIZE			1024
#define TEMP_INDEX_OFFSET				 409

/******************************************************************************
**
** From ADC inputs linked to a Texas Instruments LM35CAZ temperature sensor
** with a range of -40C to 110C. The +ve and -ve ranges from the sensor go
** to seperate analogue inputs. The sensor output is -400mV to +1100mV but we
** are only interested in the range -40C to 60C (The highest temperate ever 
** recorded on earth is 56.7C in Death Valley, California) so that yields a
** voltage range of -400mv to +600mV, e.g. a range of 1V. We use an 
** implementation amplifier on each of the +ve and -ve inputs with a gain of 
** 5 to yield an input voltage range of -2V to +3V, this equates to an ADC
** value range of -409 to + 614 (a spread of 1023).
**
** We calculate the array offset by subtracting the -ve input from the +ve
** input and adding the offset 409 to give a range of 0 - 1023", e.g.
**
** index = (ADC(+ve) - AD(-ve)) + 409
**
** As the sensor output is linear, the temperature is calculated using the 
** equation of the straight line output graph:
**
** T = ((100 / 1023) * -409) + 0
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
const char temp0[] PROGMEM = "-39.98";
const char temp1[] PROGMEM = "-39.88";
const char temp2[] PROGMEM = "-39.78";
const char temp3[] PROGMEM = "-39.69";
const char temp4[] PROGMEM = "-39.59";
const char temp5[] PROGMEM = "-39.49";
const char temp6[] PROGMEM = "-39.39";
const char temp7[] PROGMEM = "-39.30";
const char temp8[] PROGMEM = "-39.20";
const char temp9[] PROGMEM = "-39.10";
const char temp10[] PROGMEM = "-39.00";
const char temp11[] PROGMEM = "-38.91";
const char temp12[] PROGMEM = "-38.81";
const char temp13[] PROGMEM = "-38.71";
const char temp14[] PROGMEM = "-38.61";
const char temp15[] PROGMEM = "-38.51";
const char temp16[] PROGMEM = "-38.42";
const char temp17[] PROGMEM = "-38.32";
const char temp18[] PROGMEM = "-38.22";
const char temp19[] PROGMEM = "-38.12";
const char temp20[] PROGMEM = "-38.03";
const char temp21[] PROGMEM = "-37.93";
const char temp22[] PROGMEM = "-37.83";
const char temp23[] PROGMEM = "-37.73";
const char temp24[] PROGMEM = "-37.63";
const char temp25[] PROGMEM = "-37.54";
const char temp26[] PROGMEM = "-37.44";
const char temp27[] PROGMEM = "-37.34";
const char temp28[] PROGMEM = "-37.24";
const char temp29[] PROGMEM = "-37.15";
const char temp30[] PROGMEM = "-37.05";
const char temp31[] PROGMEM = "-36.95";
const char temp32[] PROGMEM = "-36.85";
const char temp33[] PROGMEM = "-36.75";
const char temp34[] PROGMEM = "-36.66";
const char temp35[] PROGMEM = "-36.56";
const char temp36[] PROGMEM = "-36.46";
const char temp37[] PROGMEM = "-36.36";
const char temp38[] PROGMEM = "-36.27";
const char temp39[] PROGMEM = "-36.17";
const char temp40[] PROGMEM = "-36.07";
const char temp41[] PROGMEM = "-35.97";
const char temp42[] PROGMEM = "-35.87";
const char temp43[] PROGMEM = "-35.78";
const char temp44[] PROGMEM = "-35.68";
const char temp45[] PROGMEM = "-35.58";
const char temp46[] PROGMEM = "-35.48";
const char temp47[] PROGMEM = "-35.39";
const char temp48[] PROGMEM = "-35.29";
const char temp49[] PROGMEM = "-35.19";
const char temp50[] PROGMEM = "-35.09";
const char temp51[] PROGMEM = "-35.00";
const char temp52[] PROGMEM = "-34.90";
const char temp53[] PROGMEM = "-34.80";
const char temp54[] PROGMEM = "-34.70";
const char temp55[] PROGMEM = "-34.60";
const char temp56[] PROGMEM = "-34.51";
const char temp57[] PROGMEM = "-34.41";
const char temp58[] PROGMEM = "-34.31";
const char temp59[] PROGMEM = "-34.21";
const char temp60[] PROGMEM = "-34.12";
const char temp61[] PROGMEM = "-34.02";
const char temp62[] PROGMEM = "-33.92";
const char temp63[] PROGMEM = "-33.82";
const char temp64[] PROGMEM = "-33.72";
const char temp65[] PROGMEM = "-33.63";
const char temp66[] PROGMEM = "-33.53";
const char temp67[] PROGMEM = "-33.43";
const char temp68[] PROGMEM = "-33.33";
const char temp69[] PROGMEM = "-33.24";
const char temp70[] PROGMEM = "-33.14";
const char temp71[] PROGMEM = "-33.04";
const char temp72[] PROGMEM = "-32.94";
const char temp73[] PROGMEM = "-32.84";
const char temp74[] PROGMEM = "-32.75";
const char temp75[] PROGMEM = "-32.65";
const char temp76[] PROGMEM = "-32.55";
const char temp77[] PROGMEM = "-32.45";
const char temp78[] PROGMEM = "-32.36";
const char temp79[] PROGMEM = "-32.26";
const char temp80[] PROGMEM = "-32.16";
const char temp81[] PROGMEM = "-32.06";
const char temp82[] PROGMEM = "-31.96";
const char temp83[] PROGMEM = "-31.87";
const char temp84[] PROGMEM = "-31.77";
const char temp85[] PROGMEM = "-31.67";
const char temp86[] PROGMEM = "-31.57";
const char temp87[] PROGMEM = "-31.48";
const char temp88[] PROGMEM = "-31.38";
const char temp89[] PROGMEM = "-31.28";
const char temp90[] PROGMEM = "-31.18";
const char temp91[] PROGMEM = "-31.09";
const char temp92[] PROGMEM = "-30.99";
const char temp93[] PROGMEM = "-30.89";
const char temp94[] PROGMEM = "-30.79";
const char temp95[] PROGMEM = "-30.69";
const char temp96[] PROGMEM = "-30.60";
const char temp97[] PROGMEM = "-30.50";
const char temp98[] PROGMEM = "-30.40";
const char temp99[] PROGMEM = "-30.30";
const char temp100[] PROGMEM = "-30.21";
const char temp101[] PROGMEM = "-30.11";
const char temp102[] PROGMEM = "-30.01";
const char temp103[] PROGMEM = "-29.91";
const char temp104[] PROGMEM = "-29.81";
const char temp105[] PROGMEM = "-29.72";
const char temp106[] PROGMEM = "-29.62";
const char temp107[] PROGMEM = "-29.52";
const char temp108[] PROGMEM = "-29.42";
const char temp109[] PROGMEM = "-29.33";
const char temp110[] PROGMEM = "-29.23";
const char temp111[] PROGMEM = "-29.13";
const char temp112[] PROGMEM = "-29.03";
const char temp113[] PROGMEM = "-28.93";
const char temp114[] PROGMEM = "-28.84";
const char temp115[] PROGMEM = "-28.74";
const char temp116[] PROGMEM = "-28.64";
const char temp117[] PROGMEM = "-28.54";
const char temp118[] PROGMEM = "-28.45";
const char temp119[] PROGMEM = "-28.35";
const char temp120[] PROGMEM = "-28.25";
const char temp121[] PROGMEM = "-28.15";
const char temp122[] PROGMEM = "-28.05";
const char temp123[] PROGMEM = "-27.96";
const char temp124[] PROGMEM = "-27.86";
const char temp125[] PROGMEM = "-27.76";
const char temp126[] PROGMEM = "-27.66";
const char temp127[] PROGMEM = "-27.57";
const char temp128[] PROGMEM = "-27.47";
const char temp129[] PROGMEM = "-27.37";
const char temp130[] PROGMEM = "-27.27";
const char temp131[] PROGMEM = "-27.17";
const char temp132[] PROGMEM = "-27.08";
const char temp133[] PROGMEM = "-26.98";
const char temp134[] PROGMEM = "-26.88";
const char temp135[] PROGMEM = "-26.78";
const char temp136[] PROGMEM = "-26.69";
const char temp137[] PROGMEM = "-26.59";
const char temp138[] PROGMEM = "-26.49";
const char temp139[] PROGMEM = "-26.39";
const char temp140[] PROGMEM = "-26.30";
const char temp141[] PROGMEM = "-26.20";
const char temp142[] PROGMEM = "-26.10";
const char temp143[] PROGMEM = "-26.00";
const char temp144[] PROGMEM = "-25.90";
const char temp145[] PROGMEM = "-25.81";
const char temp146[] PROGMEM = "-25.71";
const char temp147[] PROGMEM = "-25.61";
const char temp148[] PROGMEM = "-25.51";
const char temp149[] PROGMEM = "-25.42";
const char temp150[] PROGMEM = "-25.32";
const char temp151[] PROGMEM = "-25.22";
const char temp152[] PROGMEM = "-25.12";
const char temp153[] PROGMEM = "-25.02";
const char temp154[] PROGMEM = "-24.93";
const char temp155[] PROGMEM = "-24.83";
const char temp156[] PROGMEM = "-24.73";
const char temp157[] PROGMEM = "-24.63";
const char temp158[] PROGMEM = "-24.54";
const char temp159[] PROGMEM = "-24.44";
const char temp160[] PROGMEM = "-24.34";
const char temp161[] PROGMEM = "-24.24";
const char temp162[] PROGMEM = "-24.14";
const char temp163[] PROGMEM = "-24.05";
const char temp164[] PROGMEM = "-23.95";
const char temp165[] PROGMEM = "-23.85";
const char temp166[] PROGMEM = "-23.75";
const char temp167[] PROGMEM = "-23.66";
const char temp168[] PROGMEM = "-23.56";
const char temp169[] PROGMEM = "-23.46";
const char temp170[] PROGMEM = "-23.36";
const char temp171[] PROGMEM = "-23.26";
const char temp172[] PROGMEM = "-23.17";
const char temp173[] PROGMEM = "-23.07";
const char temp174[] PROGMEM = "-22.97";
const char temp175[] PROGMEM = "-22.87";
const char temp176[] PROGMEM = "-22.78";
const char temp177[] PROGMEM = "-22.68";
const char temp178[] PROGMEM = "-22.58";
const char temp179[] PROGMEM = "-22.48";
const char temp180[] PROGMEM = "-22.39";
const char temp181[] PROGMEM = "-22.29";
const char temp182[] PROGMEM = "-22.19";
const char temp183[] PROGMEM = "-22.09";
const char temp184[] PROGMEM = "-21.99";
const char temp185[] PROGMEM = "-21.90";
const char temp186[] PROGMEM = "-21.80";
const char temp187[] PROGMEM = "-21.70";
const char temp188[] PROGMEM = "-21.60";
const char temp189[] PROGMEM = "-21.51";
const char temp190[] PROGMEM = "-21.41";
const char temp191[] PROGMEM = "-21.31";
const char temp192[] PROGMEM = "-21.21";
const char temp193[] PROGMEM = "-21.11";
const char temp194[] PROGMEM = "-21.02";
const char temp195[] PROGMEM = "-20.92";
const char temp196[] PROGMEM = "-20.82";
const char temp197[] PROGMEM = "-20.72";
const char temp198[] PROGMEM = "-20.63";
const char temp199[] PROGMEM = "-20.53";
const char temp200[] PROGMEM = "-20.43";
const char temp201[] PROGMEM = "-20.33";
const char temp202[] PROGMEM = "-20.23";
const char temp203[] PROGMEM = "-20.14";
const char temp204[] PROGMEM = "-20.04";
const char temp205[] PROGMEM = "-19.94";
const char temp206[] PROGMEM = "-19.84";
const char temp207[] PROGMEM = "-19.75";
const char temp208[] PROGMEM = "-19.65";
const char temp209[] PROGMEM = "-19.55";
const char temp210[] PROGMEM = "-19.45";
const char temp211[] PROGMEM = "-19.35";
const char temp212[] PROGMEM = "-19.26";
const char temp213[] PROGMEM = "-19.16";
const char temp214[] PROGMEM = "-19.06";
const char temp215[] PROGMEM = "-18.96";
const char temp216[] PROGMEM = "-18.87";
const char temp217[] PROGMEM = "-18.77";
const char temp218[] PROGMEM = "-18.67";
const char temp219[] PROGMEM = "-18.57";
const char temp220[] PROGMEM = "-18.48";
const char temp221[] PROGMEM = "-18.38";
const char temp222[] PROGMEM = "-18.28";
const char temp223[] PROGMEM = "-18.18";
const char temp224[] PROGMEM = "-18.08";
const char temp225[] PROGMEM = "-17.99";
const char temp226[] PROGMEM = "-17.89";
const char temp227[] PROGMEM = "-17.79";
const char temp228[] PROGMEM = "-17.69";
const char temp229[] PROGMEM = "-17.60";
const char temp230[] PROGMEM = "-17.50";
const char temp231[] PROGMEM = "-17.40";
const char temp232[] PROGMEM = "-17.30";
const char temp233[] PROGMEM = "-17.20";
const char temp234[] PROGMEM = "-17.11";
const char temp235[] PROGMEM = "-17.01";
const char temp236[] PROGMEM = "-16.91";
const char temp237[] PROGMEM = "-16.81";
const char temp238[] PROGMEM = "-16.72";
const char temp239[] PROGMEM = "-16.62";
const char temp240[] PROGMEM = "-16.52";
const char temp241[] PROGMEM = "-16.42";
const char temp242[] PROGMEM = "-16.32";
const char temp243[] PROGMEM = "-16.23";
const char temp244[] PROGMEM = "-16.13";
const char temp245[] PROGMEM = "-16.03";
const char temp246[] PROGMEM = "-15.93";
const char temp247[] PROGMEM = "-15.84";
const char temp248[] PROGMEM = "-15.74";
const char temp249[] PROGMEM = "-15.64";
const char temp250[] PROGMEM = "-15.54";
const char temp251[] PROGMEM = "-15.44";
const char temp252[] PROGMEM = "-15.35";
const char temp253[] PROGMEM = "-15.25";
const char temp254[] PROGMEM = "-15.15";
const char temp255[] PROGMEM = "-15.05";
const char temp256[] PROGMEM = "-14.96";
const char temp257[] PROGMEM = "-14.86";
const char temp258[] PROGMEM = "-14.76";
const char temp259[] PROGMEM = "-14.66";
const char temp260[] PROGMEM = "-14.57";
const char temp261[] PROGMEM = "-14.47";
const char temp262[] PROGMEM = "-14.37";
const char temp263[] PROGMEM = "-14.27";
const char temp264[] PROGMEM = "-14.17";
const char temp265[] PROGMEM = "-14.08";
const char temp266[] PROGMEM = "-13.98";
const char temp267[] PROGMEM = "-13.88";
const char temp268[] PROGMEM = "-13.78";
const char temp269[] PROGMEM = "-13.69";
const char temp270[] PROGMEM = "-13.59";
const char temp271[] PROGMEM = "-13.49";
const char temp272[] PROGMEM = "-13.39";
const char temp273[] PROGMEM = "-13.29";
const char temp274[] PROGMEM = "-13.20";
const char temp275[] PROGMEM = "-13.10";
const char temp276[] PROGMEM = "-13.00";
const char temp277[] PROGMEM = "-12.90";
const char temp278[] PROGMEM = "-12.81";
const char temp279[] PROGMEM = "-12.71";
const char temp280[] PROGMEM = "-12.61";
const char temp281[] PROGMEM = "-12.51";
const char temp282[] PROGMEM = "-12.41";
const char temp283[] PROGMEM = "-12.32";
const char temp284[] PROGMEM = "-12.22";
const char temp285[] PROGMEM = "-12.12";
const char temp286[] PROGMEM = "-12.02";
const char temp287[] PROGMEM = "-11.93";
const char temp288[] PROGMEM = "-11.83";
const char temp289[] PROGMEM = "-11.73";
const char temp290[] PROGMEM = "-11.63";
const char temp291[] PROGMEM = "-11.53";
const char temp292[] PROGMEM = "-11.44";
const char temp293[] PROGMEM = "-11.34";
const char temp294[] PROGMEM = "-11.24";
const char temp295[] PROGMEM = "-11.14";
const char temp296[] PROGMEM = "-11.05";
const char temp297[] PROGMEM = "-10.95";
const char temp298[] PROGMEM = "-10.85";
const char temp299[] PROGMEM = "-10.75";
const char temp300[] PROGMEM = "-10.65";
const char temp301[] PROGMEM = "-10.56";
const char temp302[] PROGMEM = "-10.46";
const char temp303[] PROGMEM = "-10.36";
const char temp304[] PROGMEM = "-10.26";
const char temp305[] PROGMEM = "-10.17";
const char temp306[] PROGMEM = "-10.07";
const char temp307[] PROGMEM = "-9.97";
const char temp308[] PROGMEM = "-9.87";
const char temp309[] PROGMEM = "-9.78";
const char temp310[] PROGMEM = "-9.68";
const char temp311[] PROGMEM = "-9.58";
const char temp312[] PROGMEM = "-9.48";
const char temp313[] PROGMEM = "-9.38";
const char temp314[] PROGMEM = "-9.29";
const char temp315[] PROGMEM = "-9.19";
const char temp316[] PROGMEM = "-9.09";
const char temp317[] PROGMEM = "-8.99";
const char temp318[] PROGMEM = "-8.90";
const char temp319[] PROGMEM = "-8.80";
const char temp320[] PROGMEM = "-8.70";
const char temp321[] PROGMEM = "-8.60";
const char temp322[] PROGMEM = "-8.50";
const char temp323[] PROGMEM = "-8.41";
const char temp324[] PROGMEM = "-8.31";
const char temp325[] PROGMEM = "-8.21";
const char temp326[] PROGMEM = "-8.11";
const char temp327[] PROGMEM = "-8.02";
const char temp328[] PROGMEM = "-7.92";
const char temp329[] PROGMEM = "-7.82";
const char temp330[] PROGMEM = "-7.72";
const char temp331[] PROGMEM = "-7.62";
const char temp332[] PROGMEM = "-7.53";
const char temp333[] PROGMEM = "-7.43";
const char temp334[] PROGMEM = "-7.33";
const char temp335[] PROGMEM = "-7.23";
const char temp336[] PROGMEM = "-7.14";
const char temp337[] PROGMEM = "-7.04";
const char temp338[] PROGMEM = "-6.94";
const char temp339[] PROGMEM = "-6.84";
const char temp340[] PROGMEM = "-6.74";
const char temp341[] PROGMEM = "-6.65";
const char temp342[] PROGMEM = "-6.55";
const char temp343[] PROGMEM = "-6.45";
const char temp344[] PROGMEM = "-6.35";
const char temp345[] PROGMEM = "-6.26";
const char temp346[] PROGMEM = "-6.16";
const char temp347[] PROGMEM = "-6.06";
const char temp348[] PROGMEM = "-5.96";
const char temp349[] PROGMEM = "-5.87";
const char temp350[] PROGMEM = "-5.77";
const char temp351[] PROGMEM = "-5.67";
const char temp352[] PROGMEM = "-5.57";
const char temp353[] PROGMEM = "-5.47";
const char temp354[] PROGMEM = "-5.38";
const char temp355[] PROGMEM = "-5.28";
const char temp356[] PROGMEM = "-5.18";
const char temp357[] PROGMEM = "-5.08";
const char temp358[] PROGMEM = "-4.99";
const char temp359[] PROGMEM = "-4.89";
const char temp360[] PROGMEM = "-4.79";
const char temp361[] PROGMEM = "-4.69";
const char temp362[] PROGMEM = "-4.59";
const char temp363[] PROGMEM = "-4.50";
const char temp364[] PROGMEM = "-4.40";
const char temp365[] PROGMEM = "-4.30";
const char temp366[] PROGMEM = "-4.20";
const char temp367[] PROGMEM = "-4.11";
const char temp368[] PROGMEM = "-4.01";
const char temp369[] PROGMEM = "-3.91";
const char temp370[] PROGMEM = "-3.81";
const char temp371[] PROGMEM = "-3.71";
const char temp372[] PROGMEM = "-3.62";
const char temp373[] PROGMEM = "-3.52";
const char temp374[] PROGMEM = "-3.42";
const char temp375[] PROGMEM = "-3.32";
const char temp376[] PROGMEM = "-3.23";
const char temp377[] PROGMEM = "-3.13";
const char temp378[] PROGMEM = "-3.03";
const char temp379[] PROGMEM = "-2.93";
const char temp380[] PROGMEM = "-2.83";
const char temp381[] PROGMEM = "-2.74";
const char temp382[] PROGMEM = "-2.64";
const char temp383[] PROGMEM = "-2.54";
const char temp384[] PROGMEM = "-2.44";
const char temp385[] PROGMEM = "-2.35";
const char temp386[] PROGMEM = "-2.25";
const char temp387[] PROGMEM = "-2.15";
const char temp388[] PROGMEM = "-2.05";
const char temp389[] PROGMEM = "-1.96";
const char temp390[] PROGMEM = "-1.86";
const char temp391[] PROGMEM = "-1.76";
const char temp392[] PROGMEM = "-1.66";
const char temp393[] PROGMEM = "-1.56";
const char temp394[] PROGMEM = "-1.47";
const char temp395[] PROGMEM = "-1.37";
const char temp396[] PROGMEM = "-1.27";
const char temp397[] PROGMEM = "-1.17";
const char temp398[] PROGMEM = "-1.08";
const char temp399[] PROGMEM = "-0.98";
const char temp400[] PROGMEM = "-0.88";
const char temp401[] PROGMEM = "-0.78";
const char temp402[] PROGMEM = "-0.68";
const char temp403[] PROGMEM = "-0.59";
const char temp404[] PROGMEM = "-0.49";
const char temp405[] PROGMEM = "-0.39";
const char temp406[] PROGMEM = "-0.29";
const char temp407[] PROGMEM = "-0.20";
const char temp408[] PROGMEM = "-0.10";
const char temp409[] PROGMEM = "0.00";
const char temp410[] PROGMEM = "0.10";
const char temp411[] PROGMEM = "0.20";
const char temp412[] PROGMEM = "0.29";
const char temp413[] PROGMEM = "0.39";
const char temp414[] PROGMEM = "0.49";
const char temp415[] PROGMEM = "0.59";
const char temp416[] PROGMEM = "0.68";
const char temp417[] PROGMEM = "0.78";
const char temp418[] PROGMEM = "0.88";
const char temp419[] PROGMEM = "0.98";
const char temp420[] PROGMEM = "1.08";
const char temp421[] PROGMEM = "1.17";
const char temp422[] PROGMEM = "1.27";
const char temp423[] PROGMEM = "1.37";
const char temp424[] PROGMEM = "1.47";
const char temp425[] PROGMEM = "1.56";
const char temp426[] PROGMEM = "1.66";
const char temp427[] PROGMEM = "1.76";
const char temp428[] PROGMEM = "1.86";
const char temp429[] PROGMEM = "1.96";
const char temp430[] PROGMEM = "2.05";
const char temp431[] PROGMEM = "2.15";
const char temp432[] PROGMEM = "2.25";
const char temp433[] PROGMEM = "2.35";
const char temp434[] PROGMEM = "2.44";
const char temp435[] PROGMEM = "2.54";
const char temp436[] PROGMEM = "2.64";
const char temp437[] PROGMEM = "2.74";
const char temp438[] PROGMEM = "2.83";
const char temp439[] PROGMEM = "2.93";
const char temp440[] PROGMEM = "3.03";
const char temp441[] PROGMEM = "3.13";
const char temp442[] PROGMEM = "3.23";
const char temp443[] PROGMEM = "3.32";
const char temp444[] PROGMEM = "3.42";
const char temp445[] PROGMEM = "3.52";
const char temp446[] PROGMEM = "3.62";
const char temp447[] PROGMEM = "3.71";
const char temp448[] PROGMEM = "3.81";
const char temp449[] PROGMEM = "3.91";
const char temp450[] PROGMEM = "4.01";
const char temp451[] PROGMEM = "4.11";
const char temp452[] PROGMEM = "4.20";
const char temp453[] PROGMEM = "4.30";
const char temp454[] PROGMEM = "4.40";
const char temp455[] PROGMEM = "4.50";
const char temp456[] PROGMEM = "4.59";
const char temp457[] PROGMEM = "4.69";
const char temp458[] PROGMEM = "4.79";
const char temp459[] PROGMEM = "4.89";
const char temp460[] PROGMEM = "4.99";
const char temp461[] PROGMEM = "5.08";
const char temp462[] PROGMEM = "5.18";
const char temp463[] PROGMEM = "5.28";
const char temp464[] PROGMEM = "5.38";
const char temp465[] PROGMEM = "5.47";
const char temp466[] PROGMEM = "5.57";
const char temp467[] PROGMEM = "5.67";
const char temp468[] PROGMEM = "5.77";
const char temp469[] PROGMEM = "5.87";
const char temp470[] PROGMEM = "5.96";
const char temp471[] PROGMEM = "6.06";
const char temp472[] PROGMEM = "6.16";
const char temp473[] PROGMEM = "6.26";
const char temp474[] PROGMEM = "6.35";
const char temp475[] PROGMEM = "6.45";
const char temp476[] PROGMEM = "6.55";
const char temp477[] PROGMEM = "6.65";
const char temp478[] PROGMEM = "6.74";
const char temp479[] PROGMEM = "6.84";
const char temp480[] PROGMEM = "6.94";
const char temp481[] PROGMEM = "7.04";
const char temp482[] PROGMEM = "7.14";
const char temp483[] PROGMEM = "7.23";
const char temp484[] PROGMEM = "7.33";
const char temp485[] PROGMEM = "7.43";
const char temp486[] PROGMEM = "7.53";
const char temp487[] PROGMEM = "7.62";
const char temp488[] PROGMEM = "7.72";
const char temp489[] PROGMEM = "7.82";
const char temp490[] PROGMEM = "7.92";
const char temp491[] PROGMEM = "8.02";
const char temp492[] PROGMEM = "8.11";
const char temp493[] PROGMEM = "8.21";
const char temp494[] PROGMEM = "8.31";
const char temp495[] PROGMEM = "8.41";
const char temp496[] PROGMEM = "8.50";
const char temp497[] PROGMEM = "8.60";
const char temp498[] PROGMEM = "8.70";
const char temp499[] PROGMEM = "8.80";
const char temp500[] PROGMEM = "8.90";
const char temp501[] PROGMEM = "8.99";
const char temp502[] PROGMEM = "9.09";
const char temp503[] PROGMEM = "9.19";
const char temp504[] PROGMEM = "9.29";
const char temp505[] PROGMEM = "9.38";
const char temp506[] PROGMEM = "9.48";
const char temp507[] PROGMEM = "9.58";
const char temp508[] PROGMEM = "9.68";
const char temp509[] PROGMEM = "9.78";
const char temp510[] PROGMEM = "9.87";
const char temp511[] PROGMEM = "9.97";
const char temp512[] PROGMEM = "10.07";
const char temp513[] PROGMEM = "10.17";
const char temp514[] PROGMEM = "10.26";
const char temp515[] PROGMEM = "10.36";
const char temp516[] PROGMEM = "10.46";
const char temp517[] PROGMEM = "10.56";
const char temp518[] PROGMEM = "10.65";
const char temp519[] PROGMEM = "10.75";
const char temp520[] PROGMEM = "10.85";
const char temp521[] PROGMEM = "10.95";
const char temp522[] PROGMEM = "11.05";
const char temp523[] PROGMEM = "11.14";
const char temp524[] PROGMEM = "11.24";
const char temp525[] PROGMEM = "11.34";
const char temp526[] PROGMEM = "11.44";
const char temp527[] PROGMEM = "11.53";
const char temp528[] PROGMEM = "11.63";
const char temp529[] PROGMEM = "11.73";
const char temp530[] PROGMEM = "11.83";
const char temp531[] PROGMEM = "11.93";
const char temp532[] PROGMEM = "12.02";
const char temp533[] PROGMEM = "12.12";
const char temp534[] PROGMEM = "12.22";
const char temp535[] PROGMEM = "12.32";
const char temp536[] PROGMEM = "12.41";
const char temp537[] PROGMEM = "12.51";
const char temp538[] PROGMEM = "12.61";
const char temp539[] PROGMEM = "12.71";
const char temp540[] PROGMEM = "12.81";
const char temp541[] PROGMEM = "12.90";
const char temp542[] PROGMEM = "13.00";
const char temp543[] PROGMEM = "13.10";
const char temp544[] PROGMEM = "13.20";
const char temp545[] PROGMEM = "13.29";
const char temp546[] PROGMEM = "13.39";
const char temp547[] PROGMEM = "13.49";
const char temp548[] PROGMEM = "13.59";
const char temp549[] PROGMEM = "13.69";
const char temp550[] PROGMEM = "13.78";
const char temp551[] PROGMEM = "13.88";
const char temp552[] PROGMEM = "13.98";
const char temp553[] PROGMEM = "14.08";
const char temp554[] PROGMEM = "14.17";
const char temp555[] PROGMEM = "14.27";
const char temp556[] PROGMEM = "14.37";
const char temp557[] PROGMEM = "14.47";
const char temp558[] PROGMEM = "14.57";
const char temp559[] PROGMEM = "14.66";
const char temp560[] PROGMEM = "14.76";
const char temp561[] PROGMEM = "14.86";
const char temp562[] PROGMEM = "14.96";
const char temp563[] PROGMEM = "15.05";
const char temp564[] PROGMEM = "15.15";
const char temp565[] PROGMEM = "15.25";
const char temp566[] PROGMEM = "15.35";
const char temp567[] PROGMEM = "15.44";
const char temp568[] PROGMEM = "15.54";
const char temp569[] PROGMEM = "15.64";
const char temp570[] PROGMEM = "15.74";
const char temp571[] PROGMEM = "15.84";
const char temp572[] PROGMEM = "15.93";
const char temp573[] PROGMEM = "16.03";
const char temp574[] PROGMEM = "16.13";
const char temp575[] PROGMEM = "16.23";
const char temp576[] PROGMEM = "16.32";
const char temp577[] PROGMEM = "16.42";
const char temp578[] PROGMEM = "16.52";
const char temp579[] PROGMEM = "16.62";
const char temp580[] PROGMEM = "16.72";
const char temp581[] PROGMEM = "16.81";
const char temp582[] PROGMEM = "16.91";
const char temp583[] PROGMEM = "17.01";
const char temp584[] PROGMEM = "17.11";
const char temp585[] PROGMEM = "17.20";
const char temp586[] PROGMEM = "17.30";
const char temp587[] PROGMEM = "17.40";
const char temp588[] PROGMEM = "17.50";
const char temp589[] PROGMEM = "17.60";
const char temp590[] PROGMEM = "17.69";
const char temp591[] PROGMEM = "17.79";
const char temp592[] PROGMEM = "17.89";
const char temp593[] PROGMEM = "17.99";
const char temp594[] PROGMEM = "18.08";
const char temp595[] PROGMEM = "18.18";
const char temp596[] PROGMEM = "18.28";
const char temp597[] PROGMEM = "18.38";
const char temp598[] PROGMEM = "18.48";
const char temp599[] PROGMEM = "18.57";
const char temp600[] PROGMEM = "18.67";
const char temp601[] PROGMEM = "18.77";
const char temp602[] PROGMEM = "18.87";
const char temp603[] PROGMEM = "18.96";
const char temp604[] PROGMEM = "19.06";
const char temp605[] PROGMEM = "19.16";
const char temp606[] PROGMEM = "19.26";
const char temp607[] PROGMEM = "19.35";
const char temp608[] PROGMEM = "19.45";
const char temp609[] PROGMEM = "19.55";
const char temp610[] PROGMEM = "19.65";
const char temp611[] PROGMEM = "19.75";
const char temp612[] PROGMEM = "19.84";
const char temp613[] PROGMEM = "19.94";
const char temp614[] PROGMEM = "20.04";
const char temp615[] PROGMEM = "20.14";
const char temp616[] PROGMEM = "20.23";
const char temp617[] PROGMEM = "20.33";
const char temp618[] PROGMEM = "20.43";
const char temp619[] PROGMEM = "20.53";
const char temp620[] PROGMEM = "20.63";
const char temp621[] PROGMEM = "20.72";
const char temp622[] PROGMEM = "20.82";
const char temp623[] PROGMEM = "20.92";
const char temp624[] PROGMEM = "21.02";
const char temp625[] PROGMEM = "21.11";
const char temp626[] PROGMEM = "21.21";
const char temp627[] PROGMEM = "21.31";
const char temp628[] PROGMEM = "21.41";
const char temp629[] PROGMEM = "21.51";
const char temp630[] PROGMEM = "21.60";
const char temp631[] PROGMEM = "21.70";
const char temp632[] PROGMEM = "21.80";
const char temp633[] PROGMEM = "21.90";
const char temp634[] PROGMEM = "21.99";
const char temp635[] PROGMEM = "22.09";
const char temp636[] PROGMEM = "22.19";
const char temp637[] PROGMEM = "22.29";
const char temp638[] PROGMEM = "22.39";
const char temp639[] PROGMEM = "22.48";
const char temp640[] PROGMEM = "22.58";
const char temp641[] PROGMEM = "22.68";
const char temp642[] PROGMEM = "22.78";
const char temp643[] PROGMEM = "22.87";
const char temp644[] PROGMEM = "22.97";
const char temp645[] PROGMEM = "23.07";
const char temp646[] PROGMEM = "23.17";
const char temp647[] PROGMEM = "23.26";
const char temp648[] PROGMEM = "23.36";
const char temp649[] PROGMEM = "23.46";
const char temp650[] PROGMEM = "23.56";
const char temp651[] PROGMEM = "23.66";
const char temp652[] PROGMEM = "23.75";
const char temp653[] PROGMEM = "23.85";
const char temp654[] PROGMEM = "23.95";
const char temp655[] PROGMEM = "24.05";
const char temp656[] PROGMEM = "24.14";
const char temp657[] PROGMEM = "24.24";
const char temp658[] PROGMEM = "24.34";
const char temp659[] PROGMEM = "24.44";
const char temp660[] PROGMEM = "24.54";
const char temp661[] PROGMEM = "24.63";
const char temp662[] PROGMEM = "24.73";
const char temp663[] PROGMEM = "24.83";
const char temp664[] PROGMEM = "24.93";
const char temp665[] PROGMEM = "25.02";
const char temp666[] PROGMEM = "25.12";
const char temp667[] PROGMEM = "25.22";
const char temp668[] PROGMEM = "25.32";
const char temp669[] PROGMEM = "25.42";
const char temp670[] PROGMEM = "25.51";
const char temp671[] PROGMEM = "25.61";
const char temp672[] PROGMEM = "25.71";
const char temp673[] PROGMEM = "25.81";
const char temp674[] PROGMEM = "25.90";
const char temp675[] PROGMEM = "26.00";
const char temp676[] PROGMEM = "26.10";
const char temp677[] PROGMEM = "26.20";
const char temp678[] PROGMEM = "26.30";
const char temp679[] PROGMEM = "26.39";
const char temp680[] PROGMEM = "26.49";
const char temp681[] PROGMEM = "26.59";
const char temp682[] PROGMEM = "26.69";
const char temp683[] PROGMEM = "26.78";
const char temp684[] PROGMEM = "26.88";
const char temp685[] PROGMEM = "26.98";
const char temp686[] PROGMEM = "27.08";
const char temp687[] PROGMEM = "27.17";
const char temp688[] PROGMEM = "27.27";
const char temp689[] PROGMEM = "27.37";
const char temp690[] PROGMEM = "27.47";
const char temp691[] PROGMEM = "27.57";
const char temp692[] PROGMEM = "27.66";
const char temp693[] PROGMEM = "27.76";
const char temp694[] PROGMEM = "27.86";
const char temp695[] PROGMEM = "27.96";
const char temp696[] PROGMEM = "28.05";
const char temp697[] PROGMEM = "28.15";
const char temp698[] PROGMEM = "28.25";
const char temp699[] PROGMEM = "28.35";
const char temp700[] PROGMEM = "28.45";
const char temp701[] PROGMEM = "28.54";
const char temp702[] PROGMEM = "28.64";
const char temp703[] PROGMEM = "28.74";
const char temp704[] PROGMEM = "28.84";
const char temp705[] PROGMEM = "28.93";
const char temp706[] PROGMEM = "29.03";
const char temp707[] PROGMEM = "29.13";
const char temp708[] PROGMEM = "29.23";
const char temp709[] PROGMEM = "29.33";
const char temp710[] PROGMEM = "29.42";
const char temp711[] PROGMEM = "29.52";
const char temp712[] PROGMEM = "29.62";
const char temp713[] PROGMEM = "29.72";
const char temp714[] PROGMEM = "29.81";
const char temp715[] PROGMEM = "29.91";
const char temp716[] PROGMEM = "30.01";
const char temp717[] PROGMEM = "30.11";
const char temp718[] PROGMEM = "30.21";
const char temp719[] PROGMEM = "30.30";
const char temp720[] PROGMEM = "30.40";
const char temp721[] PROGMEM = "30.50";
const char temp722[] PROGMEM = "30.60";
const char temp723[] PROGMEM = "30.69";
const char temp724[] PROGMEM = "30.79";
const char temp725[] PROGMEM = "30.89";
const char temp726[] PROGMEM = "30.99";
const char temp727[] PROGMEM = "31.09";
const char temp728[] PROGMEM = "31.18";
const char temp729[] PROGMEM = "31.28";
const char temp730[] PROGMEM = "31.38";
const char temp731[] PROGMEM = "31.48";
const char temp732[] PROGMEM = "31.57";
const char temp733[] PROGMEM = "31.67";
const char temp734[] PROGMEM = "31.77";
const char temp735[] PROGMEM = "31.87";
const char temp736[] PROGMEM = "31.96";
const char temp737[] PROGMEM = "32.06";
const char temp738[] PROGMEM = "32.16";
const char temp739[] PROGMEM = "32.26";
const char temp740[] PROGMEM = "32.36";
const char temp741[] PROGMEM = "32.45";
const char temp742[] PROGMEM = "32.55";
const char temp743[] PROGMEM = "32.65";
const char temp744[] PROGMEM = "32.75";
const char temp745[] PROGMEM = "32.84";
const char temp746[] PROGMEM = "32.94";
const char temp747[] PROGMEM = "33.04";
const char temp748[] PROGMEM = "33.14";
const char temp749[] PROGMEM = "33.24";
const char temp750[] PROGMEM = "33.33";
const char temp751[] PROGMEM = "33.43";
const char temp752[] PROGMEM = "33.53";
const char temp753[] PROGMEM = "33.63";
const char temp754[] PROGMEM = "33.72";
const char temp755[] PROGMEM = "33.82";
const char temp756[] PROGMEM = "33.92";
const char temp757[] PROGMEM = "34.02";
const char temp758[] PROGMEM = "34.12";
const char temp759[] PROGMEM = "34.21";
const char temp760[] PROGMEM = "34.31";
const char temp761[] PROGMEM = "34.41";
const char temp762[] PROGMEM = "34.51";
const char temp763[] PROGMEM = "34.60";
const char temp764[] PROGMEM = "34.70";
const char temp765[] PROGMEM = "34.80";
const char temp766[] PROGMEM = "34.90";
const char temp767[] PROGMEM = "35.00";
const char temp768[] PROGMEM = "35.09";
const char temp769[] PROGMEM = "35.19";
const char temp770[] PROGMEM = "35.29";
const char temp771[] PROGMEM = "35.39";
const char temp772[] PROGMEM = "35.48";
const char temp773[] PROGMEM = "35.58";
const char temp774[] PROGMEM = "35.68";
const char temp775[] PROGMEM = "35.78";
const char temp776[] PROGMEM = "35.87";
const char temp777[] PROGMEM = "35.97";
const char temp778[] PROGMEM = "36.07";
const char temp779[] PROGMEM = "36.17";
const char temp780[] PROGMEM = "36.27";
const char temp781[] PROGMEM = "36.36";
const char temp782[] PROGMEM = "36.46";
const char temp783[] PROGMEM = "36.56";
const char temp784[] PROGMEM = "36.66";
const char temp785[] PROGMEM = "36.75";
const char temp786[] PROGMEM = "36.85";
const char temp787[] PROGMEM = "36.95";
const char temp788[] PROGMEM = "37.05";
const char temp789[] PROGMEM = "37.15";
const char temp790[] PROGMEM = "37.24";
const char temp791[] PROGMEM = "37.34";
const char temp792[] PROGMEM = "37.44";
const char temp793[] PROGMEM = "37.54";
const char temp794[] PROGMEM = "37.63";
const char temp795[] PROGMEM = "37.73";
const char temp796[] PROGMEM = "37.83";
const char temp797[] PROGMEM = "37.93";
const char temp798[] PROGMEM = "38.03";
const char temp799[] PROGMEM = "38.12";
const char temp800[] PROGMEM = "38.22";
const char temp801[] PROGMEM = "38.32";
const char temp802[] PROGMEM = "38.42";
const char temp803[] PROGMEM = "38.51";
const char temp804[] PROGMEM = "38.61";
const char temp805[] PROGMEM = "38.71";
const char temp806[] PROGMEM = "38.81";
const char temp807[] PROGMEM = "38.91";
const char temp808[] PROGMEM = "39.00";
const char temp809[] PROGMEM = "39.10";
const char temp810[] PROGMEM = "39.20";
const char temp811[] PROGMEM = "39.30";
const char temp812[] PROGMEM = "39.39";
const char temp813[] PROGMEM = "39.49";
const char temp814[] PROGMEM = "39.59";
const char temp815[] PROGMEM = "39.69";
const char temp816[] PROGMEM = "39.78";
const char temp817[] PROGMEM = "39.88";
const char temp818[] PROGMEM = "39.98";
const char temp819[] PROGMEM = "40.08";
const char temp820[] PROGMEM = "40.18";
const char temp821[] PROGMEM = "40.27";
const char temp822[] PROGMEM = "40.37";
const char temp823[] PROGMEM = "40.47";
const char temp824[] PROGMEM = "40.57";
const char temp825[] PROGMEM = "40.66";
const char temp826[] PROGMEM = "40.76";
const char temp827[] PROGMEM = "40.86";
const char temp828[] PROGMEM = "40.96";
const char temp829[] PROGMEM = "41.06";
const char temp830[] PROGMEM = "41.15";
const char temp831[] PROGMEM = "41.25";
const char temp832[] PROGMEM = "41.35";
const char temp833[] PROGMEM = "41.45";
const char temp834[] PROGMEM = "41.54";
const char temp835[] PROGMEM = "41.64";
const char temp836[] PROGMEM = "41.74";
const char temp837[] PROGMEM = "41.84";
const char temp838[] PROGMEM = "41.94";
const char temp839[] PROGMEM = "42.03";
const char temp840[] PROGMEM = "42.13";
const char temp841[] PROGMEM = "42.23";
const char temp842[] PROGMEM = "42.33";
const char temp843[] PROGMEM = "42.42";
const char temp844[] PROGMEM = "42.52";
const char temp845[] PROGMEM = "42.62";
const char temp846[] PROGMEM = "42.72";
const char temp847[] PROGMEM = "42.82";
const char temp848[] PROGMEM = "42.91";
const char temp849[] PROGMEM = "43.01";
const char temp850[] PROGMEM = "43.11";
const char temp851[] PROGMEM = "43.21";
const char temp852[] PROGMEM = "43.30";
const char temp853[] PROGMEM = "43.40";
const char temp854[] PROGMEM = "43.50";
const char temp855[] PROGMEM = "43.60";
const char temp856[] PROGMEM = "43.70";
const char temp857[] PROGMEM = "43.79";
const char temp858[] PROGMEM = "43.89";
const char temp859[] PROGMEM = "43.99";
const char temp860[] PROGMEM = "44.09";
const char temp861[] PROGMEM = "44.18";
const char temp862[] PROGMEM = "44.28";
const char temp863[] PROGMEM = "44.38";
const char temp864[] PROGMEM = "44.48";
const char temp865[] PROGMEM = "44.57";
const char temp866[] PROGMEM = "44.67";
const char temp867[] PROGMEM = "44.77";
const char temp868[] PROGMEM = "44.87";
const char temp869[] PROGMEM = "44.97";
const char temp870[] PROGMEM = "45.06";
const char temp871[] PROGMEM = "45.16";
const char temp872[] PROGMEM = "45.26";
const char temp873[] PROGMEM = "45.36";
const char temp874[] PROGMEM = "45.45";
const char temp875[] PROGMEM = "45.55";
const char temp876[] PROGMEM = "45.65";
const char temp877[] PROGMEM = "45.75";
const char temp878[] PROGMEM = "45.85";
const char temp879[] PROGMEM = "45.94";
const char temp880[] PROGMEM = "46.04";
const char temp881[] PROGMEM = "46.14";
const char temp882[] PROGMEM = "46.24";
const char temp883[] PROGMEM = "46.33";
const char temp884[] PROGMEM = "46.43";
const char temp885[] PROGMEM = "46.53";
const char temp886[] PROGMEM = "46.63";
const char temp887[] PROGMEM = "46.73";
const char temp888[] PROGMEM = "46.82";
const char temp889[] PROGMEM = "46.92";
const char temp890[] PROGMEM = "47.02";
const char temp891[] PROGMEM = "47.12";
const char temp892[] PROGMEM = "47.21";
const char temp893[] PROGMEM = "47.31";
const char temp894[] PROGMEM = "47.41";
const char temp895[] PROGMEM = "47.51";
const char temp896[] PROGMEM = "47.61";
const char temp897[] PROGMEM = "47.70";
const char temp898[] PROGMEM = "47.80";
const char temp899[] PROGMEM = "47.90";
const char temp900[] PROGMEM = "48.00";
const char temp901[] PROGMEM = "48.09";
const char temp902[] PROGMEM = "48.19";
const char temp903[] PROGMEM = "48.29";
const char temp904[] PROGMEM = "48.39";
const char temp905[] PROGMEM = "48.48";
const char temp906[] PROGMEM = "48.58";
const char temp907[] PROGMEM = "48.68";
const char temp908[] PROGMEM = "48.78";
const char temp909[] PROGMEM = "48.88";
const char temp910[] PROGMEM = "48.97";
const char temp911[] PROGMEM = "49.07";
const char temp912[] PROGMEM = "49.17";
const char temp913[] PROGMEM = "49.27";
const char temp914[] PROGMEM = "49.36";
const char temp915[] PROGMEM = "49.46";
const char temp916[] PROGMEM = "49.56";
const char temp917[] PROGMEM = "49.66";
const char temp918[] PROGMEM = "49.76";
const char temp919[] PROGMEM = "49.85";
const char temp920[] PROGMEM = "49.95";
const char temp921[] PROGMEM = "50.05";
const char temp922[] PROGMEM = "50.15";
const char temp923[] PROGMEM = "50.24";
const char temp924[] PROGMEM = "50.34";
const char temp925[] PROGMEM = "50.44";
const char temp926[] PROGMEM = "50.54";
const char temp927[] PROGMEM = "50.64";
const char temp928[] PROGMEM = "50.73";
const char temp929[] PROGMEM = "50.83";
const char temp930[] PROGMEM = "50.93";
const char temp931[] PROGMEM = "51.03";
const char temp932[] PROGMEM = "51.12";
const char temp933[] PROGMEM = "51.22";
const char temp934[] PROGMEM = "51.32";
const char temp935[] PROGMEM = "51.42";
const char temp936[] PROGMEM = "51.52";
const char temp937[] PROGMEM = "51.61";
const char temp938[] PROGMEM = "51.71";
const char temp939[] PROGMEM = "51.81";
const char temp940[] PROGMEM = "51.91";
const char temp941[] PROGMEM = "52.00";
const char temp942[] PROGMEM = "52.10";
const char temp943[] PROGMEM = "52.20";
const char temp944[] PROGMEM = "52.30";
const char temp945[] PROGMEM = "52.39";
const char temp946[] PROGMEM = "52.49";
const char temp947[] PROGMEM = "52.59";
const char temp948[] PROGMEM = "52.69";
const char temp949[] PROGMEM = "52.79";
const char temp950[] PROGMEM = "52.88";
const char temp951[] PROGMEM = "52.98";
const char temp952[] PROGMEM = "53.08";
const char temp953[] PROGMEM = "53.18";
const char temp954[] PROGMEM = "53.27";
const char temp955[] PROGMEM = "53.37";
const char temp956[] PROGMEM = "53.47";
const char temp957[] PROGMEM = "53.57";
const char temp958[] PROGMEM = "53.67";
const char temp959[] PROGMEM = "53.76";
const char temp960[] PROGMEM = "53.86";
const char temp961[] PROGMEM = "53.96";
const char temp962[] PROGMEM = "54.06";
const char temp963[] PROGMEM = "54.15";
const char temp964[] PROGMEM = "54.25";
const char temp965[] PROGMEM = "54.35";
const char temp966[] PROGMEM = "54.45";
const char temp967[] PROGMEM = "54.55";
const char temp968[] PROGMEM = "54.64";
const char temp969[] PROGMEM = "54.74";
const char temp970[] PROGMEM = "54.84";
const char temp971[] PROGMEM = "54.94";
const char temp972[] PROGMEM = "55.03";
const char temp973[] PROGMEM = "55.13";
const char temp974[] PROGMEM = "55.23";
const char temp975[] PROGMEM = "55.33";
const char temp976[] PROGMEM = "55.43";
const char temp977[] PROGMEM = "55.52";
const char temp978[] PROGMEM = "55.62";
const char temp979[] PROGMEM = "55.72";
const char temp980[] PROGMEM = "55.82";
const char temp981[] PROGMEM = "55.91";
const char temp982[] PROGMEM = "56.01";
const char temp983[] PROGMEM = "56.11";
const char temp984[] PROGMEM = "56.21";
const char temp985[] PROGMEM = "56.30";
const char temp986[] PROGMEM = "56.40";
const char temp987[] PROGMEM = "56.50";
const char temp988[] PROGMEM = "56.60";
const char temp989[] PROGMEM = "56.70";
const char temp990[] PROGMEM = "56.79";
const char temp991[] PROGMEM = "56.89";
const char temp992[] PROGMEM = "56.99";
const char temp993[] PROGMEM = "57.09";
const char temp994[] PROGMEM = "57.18";
const char temp995[] PROGMEM = "57.28";
const char temp996[] PROGMEM = "57.38";
const char temp997[] PROGMEM = "57.48";
const char temp998[] PROGMEM = "57.58";
const char temp999[] PROGMEM = "57.67";
const char temp1000[] PROGMEM = "57.77";
const char temp1001[] PROGMEM = "57.87";
const char temp1002[] PROGMEM = "57.97";
const char temp1003[] PROGMEM = "58.06";
const char temp1004[] PROGMEM = "58.16";
const char temp1005[] PROGMEM = "58.26";
const char temp1006[] PROGMEM = "58.36";
const char temp1007[] PROGMEM = "58.46";
const char temp1008[] PROGMEM = "58.55";
const char temp1009[] PROGMEM = "58.65";
const char temp1010[] PROGMEM = "58.75";
const char temp1011[] PROGMEM = "58.85";
const char temp1012[] PROGMEM = "58.94";
const char temp1013[] PROGMEM = "59.04";
const char temp1014[] PROGMEM = "59.14";
const char temp1015[] PROGMEM = "59.24";
const char temp1016[] PROGMEM = "59.34";
const char temp1017[] PROGMEM = "59.43";
const char temp1018[] PROGMEM = "59.53";
const char temp1019[] PROGMEM = "59.63";
const char temp1020[] PROGMEM = "59.73";
const char temp1021[] PROGMEM = "59.82";
const char temp1022[] PROGMEM = "59.92";
const char temp1023[] PROGMEM = "60.02";

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
temp531,
temp532,
temp533,
temp534,
temp535,
temp536,
temp537,
temp538,
temp539,
temp540,
temp541,
temp542,
temp543,
temp544,
temp545,
temp546,
temp547,
temp548,
temp549,
temp550,
temp551,
temp552,
temp553,
temp554,
temp555,
temp556,
temp557,
temp558,
temp559,
temp560,
temp561,
temp562,
temp563,
temp564,
temp565,
temp566,
temp567,
temp568,
temp569,
temp570,
temp571,
temp572,
temp573,
temp574,
temp575,
temp576,
temp577,
temp578,
temp579,
temp580,
temp581,
temp582,
temp583,
temp584,
temp585,
temp586,
temp587,
temp588,
temp589,
temp590,
temp591,
temp592,
temp593,
temp594,
temp595,
temp596,
temp597,
temp598,
temp599,
temp600,
temp601,
temp602,
temp603,
temp604,
temp605,
temp606,
temp607,
temp608,
temp609,
temp610,
temp611,
temp612,
temp613,
temp614,
temp615,
temp616,
temp617,
temp618,
temp619,
temp620,
temp621,
temp622,
temp623,
temp624,
temp625,
temp626,
temp627,
temp628,
temp629,
temp630,
temp631,
temp632,
temp633,
temp634,
temp635,
temp636,
temp637,
temp638,
temp639,
temp640,
temp641,
temp642,
temp643,
temp644,
temp645,
temp646,
temp647,
temp648,
temp649,
temp650,
temp651,
temp652,
temp653,
temp654,
temp655,
temp656,
temp657,
temp658,
temp659,
temp660,
temp661,
temp662,
temp663,
temp664,
temp665,
temp666,
temp667,
temp668,
temp669,
temp670,
temp671,
temp672,
temp673,
temp674,
temp675,
temp676,
temp677,
temp678,
temp679,
temp680,
temp681,
temp682,
temp683,
temp684,
temp685,
temp686,
temp687,
temp688,
temp689,
temp690,
temp691,
temp692,
temp693,
temp694,
temp695,
temp696,
temp697,
temp698,
temp699,
temp700,
temp701,
temp702,
temp703,
temp704,
temp705,
temp706,
temp707,
temp708,
temp709,
temp710,
temp711,
temp712,
temp713,
temp714,
temp715,
temp716,
temp717,
temp718,
temp719,
temp720,
temp721,
temp722,
temp723,
temp724,
temp725,
temp726,
temp727,
temp728,
temp729,
temp730,
temp731,
temp732,
temp733,
temp734,
temp735,
temp736,
temp737,
temp738,
temp739,
temp740,
temp741,
temp742,
temp743,
temp744,
temp745,
temp746,
temp747,
temp748,
temp749,
temp750,
temp751,
temp752,
temp753,
temp754,
temp755,
temp756,
temp757,
temp758,
temp759,
temp760,
temp761,
temp762,
temp763,
temp764,
temp765,
temp766,
temp767,
temp768,
temp769,
temp770,
temp771,
temp772,
temp773,
temp774,
temp775,
temp776,
temp777,
temp778,
temp779,
temp780,
temp781,
temp782,
temp783,
temp784,
temp785,
temp786,
temp787,
temp788,
temp789,
temp790,
temp791,
temp792,
temp793,
temp794,
temp795,
temp796,
temp797,
temp798,
temp799,
temp800,
temp801,
temp802,
temp803,
temp804,
temp805,
temp806,
temp807,
temp808,
temp809,
temp810,
temp811,
temp812,
temp813,
temp814,
temp815,
temp816,
temp817,
temp818,
temp819,
temp820,
temp821,
temp822,
temp823,
temp824,
temp825,
temp826,
temp827,
temp828,
temp829,
temp830,
temp831,
temp832,
temp833,
temp834,
temp835,
temp836,
temp837,
temp838,
temp839,
temp840,
temp841,
temp842,
temp843,
temp844,
temp845,
temp846,
temp847,
temp848,
temp849,
temp850,
temp851,
temp852,
temp853,
temp854,
temp855,
temp856,
temp857,
temp858,
temp859,
temp860,
temp861,
temp862,
temp863,
temp864,
temp865,
temp866,
temp867,
temp868,
temp869,
temp870,
temp871,
temp872,
temp873,
temp874,
temp875,
temp876,
temp877,
temp878,
temp879,
temp880,
temp881,
temp882,
temp883,
temp884,
temp885,
temp886,
temp887,
temp888,
temp889,
temp890,
temp891,
temp892,
temp893,
temp894,
temp895,
temp896,
temp897,
temp898,
temp899,
temp900,
temp901,
temp902,
temp903,
temp904,
temp905,
temp906,
temp907,
temp908,
temp909,
temp910,
temp911,
temp912,
temp913,
temp914,
temp915,
temp916,
temp917,
temp918,
temp919,
temp920,
temp921,
temp922,
temp923,
temp924,
temp925,
temp926,
temp927,
temp928,
temp929,
temp930,
temp931,
temp932,
temp933,
temp934,
temp935,
temp936,
temp937,
temp938,
temp939,
temp940,
temp941,
temp942,
temp943,
temp944,
temp945,
temp946,
temp947,
temp948,
temp949,
temp950,
temp951,
temp952,
temp953,
temp954,
temp955,
temp956,
temp957,
temp958,
temp959,
temp960,
temp961,
temp962,
temp963,
temp964,
temp965,
temp966,
temp967,
temp968,
temp969,
temp970,
temp971,
temp972,
temp973,
temp974,
temp975,
temp976,
temp977,
temp978,
temp979,
temp980,
temp981,
temp982,
temp983,
temp984,
temp985,
temp986,
temp987,
temp988,
temp989,
temp990,
temp991,
temp992,
temp993,
temp994,
temp995,
temp996,
temp997,
temp998,
temp999,
temp1000,
temp1001,
temp1002,
temp1003,
temp1004,
temp1005,
temp1006,
temp1007,
temp1008,
temp1009,
temp1010,
temp1011,
temp1012,
temp1013,
temp1014,
temp1015,
temp1016,
temp1017,
temp1018,
temp1019,
temp1020,
temp1021,
temp1022,
temp1023
};

#endif