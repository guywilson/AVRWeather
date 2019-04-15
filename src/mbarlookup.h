#include <avr/pgmspace.h>

#ifndef _INCL_MBARLOOKUP
#define _INCL_MBARLOOKUP

#define MBAR_LOOKUP_BUFFER_SIZE					 728

/******************************************************************************
**
** From an ADC input linked to an NXP MPX4115A barometric pressure sensor
** with a range of 150mbar to 1150mbar. This range yields an output voltage
** range of 200mv to 4.7v. However, we are only interested in atmospheric
** pressure in the range 330mbar to 1100mb (the air pressure at the summit of
** Everest is ~330mbar, at sea level, the lowest recorded air pressure is
** 870mbar, the highest is 1083.8mbar).
**
** The transfer function of the sensor is (pressure in kPa):
**     Vout = Vs * ((0.009 * P) - 0.095)
**
**     e.g. with a pressure of 870mbar:
**     Vout = 5 * ((0.009 * 87) - 0.095) = 3.44v
**
** Given that the ADC input range is 0v - 5v equating to 0 - 1023 (10-bit)
** then re-arranging to get P in mbar from the ADC value, we use:
**     P = (((ADC / 1023) + 0.095) / 0.009) * 10
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
const char pressure0[] PROGMEM = "320.61";
const char pressure1[] PROGMEM = "321.70";
const char pressure2[] PROGMEM = "322.78";
const char pressure3[] PROGMEM = "323.87";
const char pressure4[] PROGMEM = "324.95";
const char pressure5[] PROGMEM = "326.04";
const char pressure6[] PROGMEM = "327.13";
const char pressure7[] PROGMEM = "328.21";
const char pressure8[] PROGMEM = "329.30";
const char pressure9[] PROGMEM = "330.38";
const char pressure10[] PROGMEM = "331.47";
const char pressure11[] PROGMEM = "332.56";
const char pressure12[] PROGMEM = "333.64";
const char pressure13[] PROGMEM = "334.73";
const char pressure14[] PROGMEM = "335.82";
const char pressure15[] PROGMEM = "336.90";
const char pressure16[] PROGMEM = "337.99";
const char pressure17[] PROGMEM = "339.07";
const char pressure18[] PROGMEM = "340.16";
const char pressure19[] PROGMEM = "341.25";
const char pressure20[] PROGMEM = "342.33";
const char pressure21[] PROGMEM = "343.42";
const char pressure22[] PROGMEM = "344.50";
const char pressure23[] PROGMEM = "345.59";
const char pressure24[] PROGMEM = "346.68";
const char pressure25[] PROGMEM = "347.76";
const char pressure26[] PROGMEM = "348.85";
const char pressure27[] PROGMEM = "349.93";
const char pressure28[] PROGMEM = "351.02";
const char pressure29[] PROGMEM = "352.11";
const char pressure30[] PROGMEM = "353.19";
const char pressure31[] PROGMEM = "354.28";
const char pressure32[] PROGMEM = "355.37";
const char pressure33[] PROGMEM = "356.45";
const char pressure34[] PROGMEM = "357.54";
const char pressure35[] PROGMEM = "358.62";
const char pressure36[] PROGMEM = "359.71";
const char pressure37[] PROGMEM = "360.80";
const char pressure38[] PROGMEM = "361.88";
const char pressure39[] PROGMEM = "362.97";
const char pressure40[] PROGMEM = "364.05";
const char pressure41[] PROGMEM = "365.14";
const char pressure42[] PROGMEM = "366.23";
const char pressure43[] PROGMEM = "367.31";
const char pressure44[] PROGMEM = "368.40";
const char pressure45[] PROGMEM = "369.49";
const char pressure46[] PROGMEM = "370.57";
const char pressure47[] PROGMEM = "371.66";
const char pressure48[] PROGMEM = "372.74";
const char pressure49[] PROGMEM = "373.83";
const char pressure50[] PROGMEM = "374.92";
const char pressure51[] PROGMEM = "376.00";
const char pressure52[] PROGMEM = "377.09";
const char pressure53[] PROGMEM = "378.17";
const char pressure54[] PROGMEM = "379.26";
const char pressure55[] PROGMEM = "380.35";
const char pressure56[] PROGMEM = "381.43";
const char pressure57[] PROGMEM = "382.52";
const char pressure58[] PROGMEM = "383.60";
const char pressure59[] PROGMEM = "384.69";
const char pressure60[] PROGMEM = "385.78";
const char pressure61[] PROGMEM = "386.86";
const char pressure62[] PROGMEM = "387.95";
const char pressure63[] PROGMEM = "389.04";
const char pressure64[] PROGMEM = "390.12";
const char pressure65[] PROGMEM = "391.21";
const char pressure66[] PROGMEM = "392.29";
const char pressure67[] PROGMEM = "393.38";
const char pressure68[] PROGMEM = "394.47";
const char pressure69[] PROGMEM = "395.55";
const char pressure70[] PROGMEM = "396.64";
const char pressure71[] PROGMEM = "397.72";
const char pressure72[] PROGMEM = "398.81";
const char pressure73[] PROGMEM = "399.90";
const char pressure74[] PROGMEM = "400.98";
const char pressure75[] PROGMEM = "402.07";
const char pressure76[] PROGMEM = "403.16";
const char pressure77[] PROGMEM = "404.24";
const char pressure78[] PROGMEM = "405.33";
const char pressure79[] PROGMEM = "406.41";
const char pressure80[] PROGMEM = "407.50";
const char pressure81[] PROGMEM = "408.59";
const char pressure82[] PROGMEM = "409.67";
const char pressure83[] PROGMEM = "410.76";
const char pressure84[] PROGMEM = "411.84";
const char pressure85[] PROGMEM = "412.93";
const char pressure86[] PROGMEM = "414.02";
const char pressure87[] PROGMEM = "415.10";
const char pressure88[] PROGMEM = "416.19";
const char pressure89[] PROGMEM = "417.27";
const char pressure90[] PROGMEM = "418.36";
const char pressure91[] PROGMEM = "419.45";
const char pressure92[] PROGMEM = "420.53";
const char pressure93[] PROGMEM = "421.62";
const char pressure94[] PROGMEM = "422.71";
const char pressure95[] PROGMEM = "423.79";
const char pressure96[] PROGMEM = "424.88";
const char pressure97[] PROGMEM = "425.96";
const char pressure98[] PROGMEM = "427.05";
const char pressure99[] PROGMEM = "428.14";
const char pressure100[] PROGMEM = "429.22";
const char pressure101[] PROGMEM = "430.31";
const char pressure102[] PROGMEM = "431.39";
const char pressure103[] PROGMEM = "432.48";
const char pressure104[] PROGMEM = "433.57";
const char pressure105[] PROGMEM = "434.65";
const char pressure106[] PROGMEM = "435.74";
const char pressure107[] PROGMEM = "436.83";
const char pressure108[] PROGMEM = "437.91";
const char pressure109[] PROGMEM = "439.00";
const char pressure110[] PROGMEM = "440.08";
const char pressure111[] PROGMEM = "441.17";
const char pressure112[] PROGMEM = "442.26";
const char pressure113[] PROGMEM = "443.34";
const char pressure114[] PROGMEM = "444.43";
const char pressure115[] PROGMEM = "445.51";
const char pressure116[] PROGMEM = "446.60";
const char pressure117[] PROGMEM = "447.69";
const char pressure118[] PROGMEM = "448.77";
const char pressure119[] PROGMEM = "449.86";
const char pressure120[] PROGMEM = "450.94";
const char pressure121[] PROGMEM = "452.03";
const char pressure122[] PROGMEM = "453.12";
const char pressure123[] PROGMEM = "454.20";
const char pressure124[] PROGMEM = "455.29";
const char pressure125[] PROGMEM = "456.38";
const char pressure126[] PROGMEM = "457.46";
const char pressure127[] PROGMEM = "458.55";
const char pressure128[] PROGMEM = "459.63";
const char pressure129[] PROGMEM = "460.72";
const char pressure130[] PROGMEM = "461.81";
const char pressure131[] PROGMEM = "462.89";
const char pressure132[] PROGMEM = "463.98";
const char pressure133[] PROGMEM = "465.06";
const char pressure134[] PROGMEM = "466.15";
const char pressure135[] PROGMEM = "467.24";
const char pressure136[] PROGMEM = "468.32";
const char pressure137[] PROGMEM = "469.41";
const char pressure138[] PROGMEM = "470.50";
const char pressure139[] PROGMEM = "471.58";
const char pressure140[] PROGMEM = "472.67";
const char pressure141[] PROGMEM = "473.75";
const char pressure142[] PROGMEM = "474.84";
const char pressure143[] PROGMEM = "475.93";
const char pressure144[] PROGMEM = "477.01";
const char pressure145[] PROGMEM = "478.10";
const char pressure146[] PROGMEM = "479.18";
const char pressure147[] PROGMEM = "480.27";
const char pressure148[] PROGMEM = "481.36";
const char pressure149[] PROGMEM = "482.44";
const char pressure150[] PROGMEM = "483.53";
const char pressure151[] PROGMEM = "484.61";
const char pressure152[] PROGMEM = "485.70";
const char pressure153[] PROGMEM = "486.79";
const char pressure154[] PROGMEM = "487.87";
const char pressure155[] PROGMEM = "488.96";
const char pressure156[] PROGMEM = "490.05";
const char pressure157[] PROGMEM = "491.13";
const char pressure158[] PROGMEM = "492.22";
const char pressure159[] PROGMEM = "493.30";
const char pressure160[] PROGMEM = "494.39";
const char pressure161[] PROGMEM = "495.48";
const char pressure162[] PROGMEM = "496.56";
const char pressure163[] PROGMEM = "497.65";
const char pressure164[] PROGMEM = "498.73";
const char pressure165[] PROGMEM = "499.82";
const char pressure166[] PROGMEM = "500.91";
const char pressure167[] PROGMEM = "501.99";
const char pressure168[] PROGMEM = "503.08";
const char pressure169[] PROGMEM = "504.17";
const char pressure170[] PROGMEM = "505.25";
const char pressure171[] PROGMEM = "506.34";
const char pressure172[] PROGMEM = "507.42";
const char pressure173[] PROGMEM = "508.51";
const char pressure174[] PROGMEM = "509.60";
const char pressure175[] PROGMEM = "510.68";
const char pressure176[] PROGMEM = "511.77";
const char pressure177[] PROGMEM = "512.85";
const char pressure178[] PROGMEM = "513.94";
const char pressure179[] PROGMEM = "515.03";
const char pressure180[] PROGMEM = "516.11";
const char pressure181[] PROGMEM = "517.20";
const char pressure182[] PROGMEM = "518.29";
const char pressure183[] PROGMEM = "519.37";
const char pressure184[] PROGMEM = "520.46";
const char pressure185[] PROGMEM = "521.54";
const char pressure186[] PROGMEM = "522.63";
const char pressure187[] PROGMEM = "523.72";
const char pressure188[] PROGMEM = "524.80";
const char pressure189[] PROGMEM = "525.89";
const char pressure190[] PROGMEM = "526.97";
const char pressure191[] PROGMEM = "528.06";
const char pressure192[] PROGMEM = "529.15";
const char pressure193[] PROGMEM = "530.23";
const char pressure194[] PROGMEM = "531.32";
const char pressure195[] PROGMEM = "532.40";
const char pressure196[] PROGMEM = "533.49";
const char pressure197[] PROGMEM = "534.58";
const char pressure198[] PROGMEM = "535.66";
const char pressure199[] PROGMEM = "536.75";
const char pressure200[] PROGMEM = "537.84";
const char pressure201[] PROGMEM = "538.92";
const char pressure202[] PROGMEM = "540.01";
const char pressure203[] PROGMEM = "541.09";
const char pressure204[] PROGMEM = "542.18";
const char pressure205[] PROGMEM = "543.27";
const char pressure206[] PROGMEM = "544.35";
const char pressure207[] PROGMEM = "545.44";
const char pressure208[] PROGMEM = "546.52";
const char pressure209[] PROGMEM = "547.61";
const char pressure210[] PROGMEM = "548.70";
const char pressure211[] PROGMEM = "549.78";
const char pressure212[] PROGMEM = "550.87";
const char pressure213[] PROGMEM = "551.96";
const char pressure214[] PROGMEM = "553.04";
const char pressure215[] PROGMEM = "554.13";
const char pressure216[] PROGMEM = "555.21";
const char pressure217[] PROGMEM = "556.30";
const char pressure218[] PROGMEM = "557.39";
const char pressure219[] PROGMEM = "558.47";
const char pressure220[] PROGMEM = "559.56";
const char pressure221[] PROGMEM = "560.64";
const char pressure222[] PROGMEM = "561.73";
const char pressure223[] PROGMEM = "562.82";
const char pressure224[] PROGMEM = "563.90";
const char pressure225[] PROGMEM = "564.99";
const char pressure226[] PROGMEM = "566.07";
const char pressure227[] PROGMEM = "567.16";
const char pressure228[] PROGMEM = "568.25";
const char pressure229[] PROGMEM = "569.33";
const char pressure230[] PROGMEM = "570.42";
const char pressure231[] PROGMEM = "571.51";
const char pressure232[] PROGMEM = "572.59";
const char pressure233[] PROGMEM = "573.68";
const char pressure234[] PROGMEM = "574.76";
const char pressure235[] PROGMEM = "575.85";
const char pressure236[] PROGMEM = "576.94";
const char pressure237[] PROGMEM = "578.02";
const char pressure238[] PROGMEM = "579.11";
const char pressure239[] PROGMEM = "580.19";
const char pressure240[] PROGMEM = "581.28";
const char pressure241[] PROGMEM = "582.37";
const char pressure242[] PROGMEM = "583.45";
const char pressure243[] PROGMEM = "584.54";
const char pressure244[] PROGMEM = "585.63";
const char pressure245[] PROGMEM = "586.71";
const char pressure246[] PROGMEM = "587.80";
const char pressure247[] PROGMEM = "588.88";
const char pressure248[] PROGMEM = "589.97";
const char pressure249[] PROGMEM = "591.06";
const char pressure250[] PROGMEM = "592.14";
const char pressure251[] PROGMEM = "593.23";
const char pressure252[] PROGMEM = "594.31";
const char pressure253[] PROGMEM = "595.40";
const char pressure254[] PROGMEM = "596.49";
const char pressure255[] PROGMEM = "597.57";
const char pressure256[] PROGMEM = "598.66";
const char pressure257[] PROGMEM = "599.74";
const char pressure258[] PROGMEM = "600.83";
const char pressure259[] PROGMEM = "601.92";
const char pressure260[] PROGMEM = "603.00";
const char pressure261[] PROGMEM = "604.09";
const char pressure262[] PROGMEM = "605.18";
const char pressure263[] PROGMEM = "606.26";
const char pressure264[] PROGMEM = "607.35";
const char pressure265[] PROGMEM = "608.43";
const char pressure266[] PROGMEM = "609.52";
const char pressure267[] PROGMEM = "610.61";
const char pressure268[] PROGMEM = "611.69";
const char pressure269[] PROGMEM = "612.78";
const char pressure270[] PROGMEM = "613.86";
const char pressure271[] PROGMEM = "614.95";
const char pressure272[] PROGMEM = "616.04";
const char pressure273[] PROGMEM = "617.12";
const char pressure274[] PROGMEM = "618.21";
const char pressure275[] PROGMEM = "619.30";
const char pressure276[] PROGMEM = "620.38";
const char pressure277[] PROGMEM = "621.47";
const char pressure278[] PROGMEM = "622.55";
const char pressure279[] PROGMEM = "623.64";
const char pressure280[] PROGMEM = "624.73";
const char pressure281[] PROGMEM = "625.81";
const char pressure282[] PROGMEM = "626.90";
const char pressure283[] PROGMEM = "627.98";
const char pressure284[] PROGMEM = "629.07";
const char pressure285[] PROGMEM = "630.16";
const char pressure286[] PROGMEM = "631.24";
const char pressure287[] PROGMEM = "632.33";
const char pressure288[] PROGMEM = "633.41";
const char pressure289[] PROGMEM = "634.50";
const char pressure290[] PROGMEM = "635.59";
const char pressure291[] PROGMEM = "636.67";
const char pressure292[] PROGMEM = "637.76";
const char pressure293[] PROGMEM = "638.85";
const char pressure294[] PROGMEM = "639.93";
const char pressure295[] PROGMEM = "641.02";
const char pressure296[] PROGMEM = "642.10";
const char pressure297[] PROGMEM = "643.19";
const char pressure298[] PROGMEM = "644.28";
const char pressure299[] PROGMEM = "645.36";
const char pressure300[] PROGMEM = "646.45";
const char pressure301[] PROGMEM = "647.53";
const char pressure302[] PROGMEM = "648.62";
const char pressure303[] PROGMEM = "649.71";
const char pressure304[] PROGMEM = "650.79";
const char pressure305[] PROGMEM = "651.88";
const char pressure306[] PROGMEM = "652.97";
const char pressure307[] PROGMEM = "654.05";
const char pressure308[] PROGMEM = "655.14";
const char pressure309[] PROGMEM = "656.22";
const char pressure310[] PROGMEM = "657.31";
const char pressure311[] PROGMEM = "658.40";
const char pressure312[] PROGMEM = "659.48";
const char pressure313[] PROGMEM = "660.57";
const char pressure314[] PROGMEM = "661.65";
const char pressure315[] PROGMEM = "662.74";
const char pressure316[] PROGMEM = "663.83";
const char pressure317[] PROGMEM = "664.91";
const char pressure318[] PROGMEM = "666.00";
const char pressure319[] PROGMEM = "667.08";
const char pressure320[] PROGMEM = "668.17";
const char pressure321[] PROGMEM = "669.26";
const char pressure322[] PROGMEM = "670.34";
const char pressure323[] PROGMEM = "671.43";
const char pressure324[] PROGMEM = "672.52";
const char pressure325[] PROGMEM = "673.60";
const char pressure326[] PROGMEM = "674.69";
const char pressure327[] PROGMEM = "675.77";
const char pressure328[] PROGMEM = "676.86";
const char pressure329[] PROGMEM = "677.95";
const char pressure330[] PROGMEM = "679.03";
const char pressure331[] PROGMEM = "680.12";
const char pressure332[] PROGMEM = "681.20";
const char pressure333[] PROGMEM = "682.29";
const char pressure334[] PROGMEM = "683.38";
const char pressure335[] PROGMEM = "684.46";
const char pressure336[] PROGMEM = "685.55";
const char pressure337[] PROGMEM = "686.64";
const char pressure338[] PROGMEM = "687.72";
const char pressure339[] PROGMEM = "688.81";
const char pressure340[] PROGMEM = "689.89";
const char pressure341[] PROGMEM = "690.98";
const char pressure342[] PROGMEM = "692.07";
const char pressure343[] PROGMEM = "693.15";
const char pressure344[] PROGMEM = "694.24";
const char pressure345[] PROGMEM = "695.32";
const char pressure346[] PROGMEM = "696.41";
const char pressure347[] PROGMEM = "697.50";
const char pressure348[] PROGMEM = "698.58";
const char pressure349[] PROGMEM = "699.67";
const char pressure350[] PROGMEM = "700.75";
const char pressure351[] PROGMEM = "701.84";
const char pressure352[] PROGMEM = "702.93";
const char pressure353[] PROGMEM = "704.01";
const char pressure354[] PROGMEM = "705.10";
const char pressure355[] PROGMEM = "706.19";
const char pressure356[] PROGMEM = "707.27";
const char pressure357[] PROGMEM = "708.36";
const char pressure358[] PROGMEM = "709.44";
const char pressure359[] PROGMEM = "710.53";
const char pressure360[] PROGMEM = "711.62";
const char pressure361[] PROGMEM = "712.70";
const char pressure362[] PROGMEM = "713.79";
const char pressure363[] PROGMEM = "714.87";
const char pressure364[] PROGMEM = "715.96";
const char pressure365[] PROGMEM = "717.05";
const char pressure366[] PROGMEM = "718.13";
const char pressure367[] PROGMEM = "719.22";
const char pressure368[] PROGMEM = "720.31";
const char pressure369[] PROGMEM = "721.39";
const char pressure370[] PROGMEM = "722.48";
const char pressure371[] PROGMEM = "723.56";
const char pressure372[] PROGMEM = "724.65";
const char pressure373[] PROGMEM = "725.74";
const char pressure374[] PROGMEM = "726.82";
const char pressure375[] PROGMEM = "727.91";
const char pressure376[] PROGMEM = "728.99";
const char pressure377[] PROGMEM = "730.08";
const char pressure378[] PROGMEM = "731.17";
const char pressure379[] PROGMEM = "732.25";
const char pressure380[] PROGMEM = "733.34";
const char pressure381[] PROGMEM = "734.42";
const char pressure382[] PROGMEM = "735.51";
const char pressure383[] PROGMEM = "736.60";
const char pressure384[] PROGMEM = "737.68";
const char pressure385[] PROGMEM = "738.77";
const char pressure386[] PROGMEM = "739.86";
const char pressure387[] PROGMEM = "740.94";
const char pressure388[] PROGMEM = "742.03";
const char pressure389[] PROGMEM = "743.11";
const char pressure390[] PROGMEM = "744.20";
const char pressure391[] PROGMEM = "745.29";
const char pressure392[] PROGMEM = "746.37";
const char pressure393[] PROGMEM = "747.46";
const char pressure394[] PROGMEM = "748.54";
const char pressure395[] PROGMEM = "749.63";
const char pressure396[] PROGMEM = "750.72";
const char pressure397[] PROGMEM = "751.80";
const char pressure398[] PROGMEM = "752.89";
const char pressure399[] PROGMEM = "753.98";
const char pressure400[] PROGMEM = "755.06";
const char pressure401[] PROGMEM = "756.15";
const char pressure402[] PROGMEM = "757.23";
const char pressure403[] PROGMEM = "758.32";
const char pressure404[] PROGMEM = "759.41";
const char pressure405[] PROGMEM = "760.49";
const char pressure406[] PROGMEM = "761.58";
const char pressure407[] PROGMEM = "762.66";
const char pressure408[] PROGMEM = "763.75";
const char pressure409[] PROGMEM = "764.84";
const char pressure410[] PROGMEM = "765.92";
const char pressure411[] PROGMEM = "767.01";
const char pressure412[] PROGMEM = "768.09";
const char pressure413[] PROGMEM = "769.18";
const char pressure414[] PROGMEM = "770.27";
const char pressure415[] PROGMEM = "771.35";
const char pressure416[] PROGMEM = "772.44";
const char pressure417[] PROGMEM = "773.53";
const char pressure418[] PROGMEM = "774.61";
const char pressure419[] PROGMEM = "775.70";
const char pressure420[] PROGMEM = "776.78";
const char pressure421[] PROGMEM = "777.87";
const char pressure422[] PROGMEM = "778.96";
const char pressure423[] PROGMEM = "780.04";
const char pressure424[] PROGMEM = "781.13";
const char pressure425[] PROGMEM = "782.21";
const char pressure426[] PROGMEM = "783.30";
const char pressure427[] PROGMEM = "784.39";
const char pressure428[] PROGMEM = "785.47";
const char pressure429[] PROGMEM = "786.56";
const char pressure430[] PROGMEM = "787.65";
const char pressure431[] PROGMEM = "788.73";
const char pressure432[] PROGMEM = "789.82";
const char pressure433[] PROGMEM = "790.90";
const char pressure434[] PROGMEM = "791.99";
const char pressure435[] PROGMEM = "793.08";
const char pressure436[] PROGMEM = "794.16";
const char pressure437[] PROGMEM = "795.25";
const char pressure438[] PROGMEM = "796.33";
const char pressure439[] PROGMEM = "797.42";
const char pressure440[] PROGMEM = "798.51";
const char pressure441[] PROGMEM = "799.59";
const char pressure442[] PROGMEM = "800.68";
const char pressure443[] PROGMEM = "801.76";
const char pressure444[] PROGMEM = "802.85";
const char pressure445[] PROGMEM = "803.94";
const char pressure446[] PROGMEM = "805.02";
const char pressure447[] PROGMEM = "806.11";
const char pressure448[] PROGMEM = "807.20";
const char pressure449[] PROGMEM = "808.28";
const char pressure450[] PROGMEM = "809.37";
const char pressure451[] PROGMEM = "810.45";
const char pressure452[] PROGMEM = "811.54";
const char pressure453[] PROGMEM = "812.63";
const char pressure454[] PROGMEM = "813.71";
const char pressure455[] PROGMEM = "814.80";
const char pressure456[] PROGMEM = "815.88";
const char pressure457[] PROGMEM = "816.97";
const char pressure458[] PROGMEM = "818.06";
const char pressure459[] PROGMEM = "819.14";
const char pressure460[] PROGMEM = "820.23";
const char pressure461[] PROGMEM = "821.32";
const char pressure462[] PROGMEM = "822.40";
const char pressure463[] PROGMEM = "823.49";
const char pressure464[] PROGMEM = "824.57";
const char pressure465[] PROGMEM = "825.66";
const char pressure466[] PROGMEM = "826.75";
const char pressure467[] PROGMEM = "827.83";
const char pressure468[] PROGMEM = "828.92";
const char pressure469[] PROGMEM = "830.00";
const char pressure470[] PROGMEM = "831.09";
const char pressure471[] PROGMEM = "832.18";
const char pressure472[] PROGMEM = "833.26";
const char pressure473[] PROGMEM = "834.35";
const char pressure474[] PROGMEM = "835.43";
const char pressure475[] PROGMEM = "836.52";
const char pressure476[] PROGMEM = "837.61";
const char pressure477[] PROGMEM = "838.69";
const char pressure478[] PROGMEM = "839.78";
const char pressure479[] PROGMEM = "840.87";
const char pressure480[] PROGMEM = "841.95";
const char pressure481[] PROGMEM = "843.04";
const char pressure482[] PROGMEM = "844.12";
const char pressure483[] PROGMEM = "845.21";
const char pressure484[] PROGMEM = "846.30";
const char pressure485[] PROGMEM = "847.38";
const char pressure486[] PROGMEM = "848.47";
const char pressure487[] PROGMEM = "849.55";
const char pressure488[] PROGMEM = "850.64";
const char pressure489[] PROGMEM = "851.73";
const char pressure490[] PROGMEM = "852.81";
const char pressure491[] PROGMEM = "853.90";
const char pressure492[] PROGMEM = "854.99";
const char pressure493[] PROGMEM = "856.07";
const char pressure494[] PROGMEM = "857.16";
const char pressure495[] PROGMEM = "858.24";
const char pressure496[] PROGMEM = "859.33";
const char pressure497[] PROGMEM = "860.42";
const char pressure498[] PROGMEM = "861.50";
const char pressure499[] PROGMEM = "862.59";
const char pressure500[] PROGMEM = "863.67";
const char pressure501[] PROGMEM = "864.76";
const char pressure502[] PROGMEM = "865.85";
const char pressure503[] PROGMEM = "866.93";
const char pressure504[] PROGMEM = "868.02";
const char pressure505[] PROGMEM = "869.11";
const char pressure506[] PROGMEM = "870.19";
const char pressure507[] PROGMEM = "871.28";
const char pressure508[] PROGMEM = "872.36";
const char pressure509[] PROGMEM = "873.45";
const char pressure510[] PROGMEM = "874.54";
const char pressure511[] PROGMEM = "875.62";
const char pressure512[] PROGMEM = "876.71";
const char pressure513[] PROGMEM = "877.79";
const char pressure514[] PROGMEM = "878.88";
const char pressure515[] PROGMEM = "879.97";
const char pressure516[] PROGMEM = "881.05";
const char pressure517[] PROGMEM = "882.14";
const char pressure518[] PROGMEM = "883.22";
const char pressure519[] PROGMEM = "884.31";
const char pressure520[] PROGMEM = "885.40";
const char pressure521[] PROGMEM = "886.48";
const char pressure522[] PROGMEM = "887.57";
const char pressure523[] PROGMEM = "888.66";
const char pressure524[] PROGMEM = "889.74";
const char pressure525[] PROGMEM = "890.83";
const char pressure526[] PROGMEM = "891.91";
const char pressure527[] PROGMEM = "893.00";
const char pressure528[] PROGMEM = "894.09";
const char pressure529[] PROGMEM = "895.17";
const char pressure530[] PROGMEM = "896.26";
const char pressure531[] PROGMEM = "897.34";
const char pressure532[] PROGMEM = "898.43";
const char pressure533[] PROGMEM = "899.52";
const char pressure534[] PROGMEM = "900.60";
const char pressure535[] PROGMEM = "901.69";
const char pressure536[] PROGMEM = "902.78";
const char pressure537[] PROGMEM = "903.86";
const char pressure538[] PROGMEM = "904.95";
const char pressure539[] PROGMEM = "906.03";
const char pressure540[] PROGMEM = "907.12";
const char pressure541[] PROGMEM = "908.21";
const char pressure542[] PROGMEM = "909.29";
const char pressure543[] PROGMEM = "910.38";
const char pressure544[] PROGMEM = "911.46";
const char pressure545[] PROGMEM = "912.55";
const char pressure546[] PROGMEM = "913.64";
const char pressure547[] PROGMEM = "914.72";
const char pressure548[] PROGMEM = "915.81";
const char pressure549[] PROGMEM = "916.89";
const char pressure550[] PROGMEM = "917.98";
const char pressure551[] PROGMEM = "919.07";
const char pressure552[] PROGMEM = "920.15";
const char pressure553[] PROGMEM = "921.24";
const char pressure554[] PROGMEM = "922.33";
const char pressure555[] PROGMEM = "923.41";
const char pressure556[] PROGMEM = "924.50";
const char pressure557[] PROGMEM = "925.58";
const char pressure558[] PROGMEM = "926.67";
const char pressure559[] PROGMEM = "927.76";
const char pressure560[] PROGMEM = "928.84";
const char pressure561[] PROGMEM = "929.93";
const char pressure562[] PROGMEM = "931.01";
const char pressure563[] PROGMEM = "932.10";
const char pressure564[] PROGMEM = "933.19";
const char pressure565[] PROGMEM = "934.27";
const char pressure566[] PROGMEM = "935.36";
const char pressure567[] PROGMEM = "936.45";
const char pressure568[] PROGMEM = "937.53";
const char pressure569[] PROGMEM = "938.62";
const char pressure570[] PROGMEM = "939.70";
const char pressure571[] PROGMEM = "940.79";
const char pressure572[] PROGMEM = "941.88";
const char pressure573[] PROGMEM = "942.96";
const char pressure574[] PROGMEM = "944.05";
const char pressure575[] PROGMEM = "945.13";
const char pressure576[] PROGMEM = "946.22";
const char pressure577[] PROGMEM = "947.31";
const char pressure578[] PROGMEM = "948.39";
const char pressure579[] PROGMEM = "949.48";
const char pressure580[] PROGMEM = "950.56";
const char pressure581[] PROGMEM = "951.65";
const char pressure582[] PROGMEM = "952.74";
const char pressure583[] PROGMEM = "953.82";
const char pressure584[] PROGMEM = "954.91";
const char pressure585[] PROGMEM = "956.00";
const char pressure586[] PROGMEM = "957.08";
const char pressure587[] PROGMEM = "958.17";
const char pressure588[] PROGMEM = "959.25";
const char pressure589[] PROGMEM = "960.34";
const char pressure590[] PROGMEM = "961.43";
const char pressure591[] PROGMEM = "962.51";
const char pressure592[] PROGMEM = "963.60";
const char pressure593[] PROGMEM = "964.68";
const char pressure594[] PROGMEM = "965.77";
const char pressure595[] PROGMEM = "966.86";
const char pressure596[] PROGMEM = "967.94";
const char pressure597[] PROGMEM = "969.03";
const char pressure598[] PROGMEM = "970.12";
const char pressure599[] PROGMEM = "971.20";
const char pressure600[] PROGMEM = "972.29";
const char pressure601[] PROGMEM = "973.37";
const char pressure602[] PROGMEM = "974.46";
const char pressure603[] PROGMEM = "975.55";
const char pressure604[] PROGMEM = "976.63";
const char pressure605[] PROGMEM = "977.72";
const char pressure606[] PROGMEM = "978.80";
const char pressure607[] PROGMEM = "979.89";
const char pressure608[] PROGMEM = "980.98";
const char pressure609[] PROGMEM = "982.06";
const char pressure610[] PROGMEM = "983.15";
const char pressure611[] PROGMEM = "984.23";
const char pressure612[] PROGMEM = "985.32";
const char pressure613[] PROGMEM = "986.41";
const char pressure614[] PROGMEM = "987.49";
const char pressure615[] PROGMEM = "988.58";
const char pressure616[] PROGMEM = "989.67";
const char pressure617[] PROGMEM = "990.75";
const char pressure618[] PROGMEM = "991.84";
const char pressure619[] PROGMEM = "992.92";
const char pressure620[] PROGMEM = "994.01";
const char pressure621[] PROGMEM = "995.10";
const char pressure622[] PROGMEM = "996.18";
const char pressure623[] PROGMEM = "997.27";
const char pressure624[] PROGMEM = "998.35";
const char pressure625[] PROGMEM = "999.44";
const char pressure626[] PROGMEM = "1000.53";
const char pressure627[] PROGMEM = "1001.61";
const char pressure628[] PROGMEM = "1002.70";
const char pressure629[] PROGMEM = "1003.79";
const char pressure630[] PROGMEM = "1004.87";
const char pressure631[] PROGMEM = "1005.96";
const char pressure632[] PROGMEM = "1007.04";
const char pressure633[] PROGMEM = "1008.13";
const char pressure634[] PROGMEM = "1009.22";
const char pressure635[] PROGMEM = "1010.30";
const char pressure636[] PROGMEM = "1011.39";
const char pressure637[] PROGMEM = "1012.47";
const char pressure638[] PROGMEM = "1013.56";
const char pressure639[] PROGMEM = "1014.65";
const char pressure640[] PROGMEM = "1015.73";
const char pressure641[] PROGMEM = "1016.82";
const char pressure642[] PROGMEM = "1017.90";
const char pressure643[] PROGMEM = "1018.99";
const char pressure644[] PROGMEM = "1020.08";
const char pressure645[] PROGMEM = "1021.16";
const char pressure646[] PROGMEM = "1022.25";
const char pressure647[] PROGMEM = "1023.34";
const char pressure648[] PROGMEM = "1024.42";
const char pressure649[] PROGMEM = "1025.51";
const char pressure650[] PROGMEM = "1026.59";
const char pressure651[] PROGMEM = "1027.68";
const char pressure652[] PROGMEM = "1028.77";
const char pressure653[] PROGMEM = "1029.85";
const char pressure654[] PROGMEM = "1030.94";
const char pressure655[] PROGMEM = "1032.02";
const char pressure656[] PROGMEM = "1033.11";
const char pressure657[] PROGMEM = "1034.20";
const char pressure658[] PROGMEM = "1035.28";
const char pressure659[] PROGMEM = "1036.37";
const char pressure660[] PROGMEM = "1037.46";
const char pressure661[] PROGMEM = "1038.54";
const char pressure662[] PROGMEM = "1039.63";
const char pressure663[] PROGMEM = "1040.71";
const char pressure664[] PROGMEM = "1041.80";
const char pressure665[] PROGMEM = "1042.89";
const char pressure666[] PROGMEM = "1043.97";
const char pressure667[] PROGMEM = "1045.06";
const char pressure668[] PROGMEM = "1046.14";
const char pressure669[] PROGMEM = "1047.23";
const char pressure670[] PROGMEM = "1048.32";
const char pressure671[] PROGMEM = "1049.40";
const char pressure672[] PROGMEM = "1050.49";
const char pressure673[] PROGMEM = "1051.57";
const char pressure674[] PROGMEM = "1052.66";
const char pressure675[] PROGMEM = "1053.75";
const char pressure676[] PROGMEM = "1054.83";
const char pressure677[] PROGMEM = "1055.92";
const char pressure678[] PROGMEM = "1057.01";
const char pressure679[] PROGMEM = "1058.09";
const char pressure680[] PROGMEM = "1059.18";
const char pressure681[] PROGMEM = "1060.26";
const char pressure682[] PROGMEM = "1061.35";
const char pressure683[] PROGMEM = "1062.44";
const char pressure684[] PROGMEM = "1063.52";
const char pressure685[] PROGMEM = "1064.61";
const char pressure686[] PROGMEM = "1065.69";
const char pressure687[] PROGMEM = "1066.78";
const char pressure688[] PROGMEM = "1067.87";
const char pressure689[] PROGMEM = "1068.95";
const char pressure690[] PROGMEM = "1070.04";
const char pressure691[] PROGMEM = "1071.13";
const char pressure692[] PROGMEM = "1072.21";
const char pressure693[] PROGMEM = "1073.30";
const char pressure694[] PROGMEM = "1074.38";
const char pressure695[] PROGMEM = "1075.47";
const char pressure696[] PROGMEM = "1076.56";
const char pressure697[] PROGMEM = "1077.64";
const char pressure698[] PROGMEM = "1078.73";
const char pressure699[] PROGMEM = "1079.81";
const char pressure700[] PROGMEM = "1080.90";
const char pressure701[] PROGMEM = "1081.99";
const char pressure702[] PROGMEM = "1083.07";
const char pressure703[] PROGMEM = "1084.16";
const char pressure704[] PROGMEM = "1085.24";
const char pressure705[] PROGMEM = "1086.33";
const char pressure706[] PROGMEM = "1087.42";
const char pressure707[] PROGMEM = "1088.50";
const char pressure708[] PROGMEM = "1089.59";
const char pressure709[] PROGMEM = "1090.68";
const char pressure710[] PROGMEM = "1091.76";
const char pressure711[] PROGMEM = "1092.85";
const char pressure712[] PROGMEM = "1093.93";
const char pressure713[] PROGMEM = "1095.02";
const char pressure714[] PROGMEM = "1096.11";
const char pressure715[] PROGMEM = "1097.19";
const char pressure716[] PROGMEM = "1098.28";
const char pressure717[] PROGMEM = "1099.36";
const char pressure718[] PROGMEM = "1100.45";
const char pressure719[] PROGMEM = "1101.54";
const char pressure720[] PROGMEM = "1102.62";
const char pressure721[] PROGMEM = "1103.71";
const char pressure722[] PROGMEM = "1104.80";
const char pressure723[] PROGMEM = "1105.88";
const char pressure724[] PROGMEM = "1106.97";
const char pressure725[] PROGMEM = "1108.05";
const char pressure726[] PROGMEM = "1109.14";
const char pressure727[] PROGMEM = "1110.23";

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
pressure275,
pressure276,
pressure277,
pressure278,
pressure279,
pressure280,
pressure281,
pressure282,
pressure283,
pressure284,
pressure285,
pressure286,
pressure287,
pressure288,
pressure289,
pressure290,
pressure291,
pressure292,
pressure293,
pressure294,
pressure295,
pressure296,
pressure297,
pressure298,
pressure299,
pressure300,
pressure301,
pressure302,
pressure303,
pressure304,
pressure305,
pressure306,
pressure307,
pressure308,
pressure309,
pressure310,
pressure311,
pressure312,
pressure313,
pressure314,
pressure315,
pressure316,
pressure317,
pressure318,
pressure319,
pressure320,
pressure321,
pressure322,
pressure323,
pressure324,
pressure325,
pressure326,
pressure327,
pressure328,
pressure329,
pressure330,
pressure331,
pressure332,
pressure333,
pressure334,
pressure335,
pressure336,
pressure337,
pressure338,
pressure339,
pressure340,
pressure341,
pressure342,
pressure343,
pressure344,
pressure345,
pressure346,
pressure347,
pressure348,
pressure349,
pressure350,
pressure351,
pressure352,
pressure353,
pressure354,
pressure355,
pressure356,
pressure357,
pressure358,
pressure359,
pressure360,
pressure361,
pressure362,
pressure363,
pressure364,
pressure365,
pressure366,
pressure367,
pressure368,
pressure369,
pressure370,
pressure371,
pressure372,
pressure373,
pressure374,
pressure375,
pressure376,
pressure377,
pressure378,
pressure379,
pressure380,
pressure381,
pressure382,
pressure383,
pressure384,
pressure385,
pressure386,
pressure387,
pressure388,
pressure389,
pressure390,
pressure391,
pressure392,
pressure393,
pressure394,
pressure395,
pressure396,
pressure397,
pressure398,
pressure399,
pressure400,
pressure401,
pressure402,
pressure403,
pressure404,
pressure405,
pressure406,
pressure407,
pressure408,
pressure409,
pressure410,
pressure411,
pressure412,
pressure413,
pressure414,
pressure415,
pressure416,
pressure417,
pressure418,
pressure419,
pressure420,
pressure421,
pressure422,
pressure423,
pressure424,
pressure425,
pressure426,
pressure427,
pressure428,
pressure429,
pressure430,
pressure431,
pressure432,
pressure433,
pressure434,
pressure435,
pressure436,
pressure437,
pressure438,
pressure439,
pressure440,
pressure441,
pressure442,
pressure443,
pressure444,
pressure445,
pressure446,
pressure447,
pressure448,
pressure449,
pressure450,
pressure451,
pressure452,
pressure453,
pressure454,
pressure455,
pressure456,
pressure457,
pressure458,
pressure459,
pressure460,
pressure461,
pressure462,
pressure463,
pressure464,
pressure465,
pressure466,
pressure467,
pressure468,
pressure469,
pressure470,
pressure471,
pressure472,
pressure473,
pressure474,
pressure475,
pressure476,
pressure477,
pressure478,
pressure479,
pressure480,
pressure481,
pressure482,
pressure483,
pressure484,
pressure485,
pressure486,
pressure487,
pressure488,
pressure489,
pressure490,
pressure491,
pressure492,
pressure493,
pressure494,
pressure495,
pressure496,
pressure497,
pressure498,
pressure499,
pressure500,
pressure501,
pressure502,
pressure503,
pressure504,
pressure505,
pressure506,
pressure507,
pressure508,
pressure509,
pressure510,
pressure511,
pressure512,
pressure513,
pressure514,
pressure515,
pressure516,
pressure517,
pressure518,
pressure519,
pressure520,
pressure521,
pressure522,
pressure523,
pressure524,
pressure525,
pressure526,
pressure527,
pressure528,
pressure529,
pressure530,
pressure531,
pressure532,
pressure533,
pressure534,
pressure535,
pressure536,
pressure537,
pressure538,
pressure539,
pressure540,
pressure541,
pressure542,
pressure543,
pressure544,
pressure545,
pressure546,
pressure547,
pressure548,
pressure549,
pressure550,
pressure551,
pressure552,
pressure553,
pressure554,
pressure555,
pressure556,
pressure557,
pressure558,
pressure559,
pressure560,
pressure561,
pressure562,
pressure563,
pressure564,
pressure565,
pressure566,
pressure567,
pressure568,
pressure569,
pressure570,
pressure571,
pressure572,
pressure573,
pressure574,
pressure575,
pressure576,
pressure577,
pressure578,
pressure579,
pressure580,
pressure581,
pressure582,
pressure583,
pressure584,
pressure585,
pressure586,
pressure587,
pressure588,
pressure589,
pressure590,
pressure591,
pressure592,
pressure593,
pressure594,
pressure595,
pressure596,
pressure597,
pressure598,
pressure599,
pressure600,
pressure601,
pressure602,
pressure603,
pressure604,
pressure605,
pressure606,
pressure607,
pressure608,
pressure609,
pressure610,
pressure611,
pressure612,
pressure613,
pressure614,
pressure615,
pressure616,
pressure617,
pressure618,
pressure619,
pressure620,
pressure621,
pressure622,
pressure623,
pressure624,
pressure625,
pressure626,
pressure627,
pressure628,
pressure629,
pressure630,
pressure631,
pressure632,
pressure633,
pressure634,
pressure635,
pressure636,
pressure637,
pressure638,
pressure639,
pressure640,
pressure641,
pressure642,
pressure643,
pressure644,
pressure645,
pressure646,
pressure647,
pressure648,
pressure649,
pressure650,
pressure651,
pressure652,
pressure653,
pressure654,
pressure655,
pressure656,
pressure657,
pressure658,
pressure659,
pressure660,
pressure661,
pressure662,
pressure663,
pressure664,
pressure665,
pressure666,
pressure667,
pressure668,
pressure669,
pressure670,
pressure671,
pressure672,
pressure673,
pressure674,
pressure675,
pressure676,
pressure677,
pressure678,
pressure679,
pressure680,
pressure681,
pressure682,
pressure683,
pressure684,
pressure685,
pressure686,
pressure687,
pressure688,
pressure689,
pressure690,
pressure691,
pressure692,
pressure693,
pressure694,
pressure695,
pressure696,
pressure697,
pressure698,
pressure699,
pressure700,
pressure701,
pressure702,
pressure703,
pressure704,
pressure705,
pressure706,
pressure707,
pressure708,
pressure709,
pressure710,
pressure711,
pressure712,
pressure713,
pressure714,
pressure715,
pressure716,
pressure717,
pressure718,
pressure719,
pressure720,
pressure721,
pressure722,
pressure723,
pressure724,
pressure725,
pressure726,
pressure727
};

#endif
