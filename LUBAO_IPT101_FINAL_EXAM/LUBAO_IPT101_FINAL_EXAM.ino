//API USED: https://covid-api.mmediagroup.fr/v1/cases?country=Japan



#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// Replace with your network credentials
const char* ssid = "lubao";
const char* password = "thirteen";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int LEDPin = 13;
void setup(void) {
  //parsing json
  const size_t capacity = 49 * JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(13) + JSON_OBJECT_SIZE(50) + 6060;
  DynamicJsonBuffer jsonBuffer(capacity);

  const char* json = "{\"All\":{\"confirmed\":201087,\"recovered\":167357,\"deaths\":2833,\"country\":\"Japan\",\"population\":127484450,\"sq_km_area\":377829,\"life_expectancy\":\"80.7\",\"elevation_in_meters\":438,\"continent\":\"Asia\",\"abbreviation\":\"JP\",\"location\":\"Eastern Asia\",\"iso\":392,\"capital_city\":\"Tokyo\"},\"Aichi\":{\"lat\":\"35.035551\",\"long\":\"137.211621\",\"confirmed\":14236,\"recovered\":11581,\"deaths\":151,\"updated\":\"2020/12/22 06:22:55+00\"},\"Akita\":{\"lat\":\"39.748679\",\"long\":\"140.408228\",\"confirmed\":95,\"recovered\":90,\"deaths\":1,\"updated\":\"2020/12/22 06:22:55+00\"},\"Aomori\":{\"lat\":\"40.781541\",\"long\":\"140.828896\",\"confirmed\":395,\"recovered\":345,\"deaths\":6,\"updated\":\"2020/12/22 06:22:55+00\"},\"Chiba\":{\"lat\":\"35.510141\",\"long\":\"140.198917\",\"confirmed\":9177,\"recovered\":7721,\"deaths\":104,\"updated\":\"2020/12/22 06:22:55+00\"},\"Ehime\":{\"lat\":\"33.624835\",\"long\":\"132.856842\",\"confirmed\":375,\"recovered\":319,\"deaths\":11,\"updated\":\"2020/12/22 06:22:55+00\"},\"Fukui\":{\"lat\":\"35.846614\",\"long\":\"136.224654\",\"confirmed\":337,\"recovered\":313,\"deaths\":11,\"updated\":\"2020/12/22 06:22:55+00\"},\"Fukuoka\":{\"lat\":\"33.526032\",\"long\":\"130.666949\",\"confirmed\":7458,\"recovered\":6210,\"deaths\":113,\"updated\":\"2020/12/22 06:22:55+00\"},\"Fukushima\":{\"lat\":\"37.378867\",\"long\":\"140.223295\",\"confirmed\":758,\"recovered\":552,\"deaths\":12,\"updated\":\"2020/12/22 06:22:55+00\"},\"Gifu\":{\"lat\":\"35.778671\",\"long\":\"137.055925\",\"confirmed\":1748,\"recovered\":1360,\"deaths\":24,\"updated\":\"2020/12/22 06:22:55+00\"},\"Gunma\":{\"lat\":\"36.504479\",\"long\":\"138.985605\",\"confirmed\":1950,\"recovered\":1471,\"deaths\":31,\"updated\":\"2020/12/22 06:22:55+00\"},\"Hiroshima\":{\"lat\":\"34.605309\",\"long\":\"132.788719\",\"confirmed\":2378,\"recovered\":1157,\"deaths\":14,\"updated\":\"2020/12/22 06:22:55+00\"},\"Hokkaido\":{\"lat\":\"43.385711\",\"long\":\"142.552318\",\"confirmed\":12296,\"recovered\":9930,\"deaths\":381,\"updated\":\"2020/12/22 06:22:55+00\"},\"Hyogo\":{\"lat\":\"35.039913\",\"long\":\"134.828057\",\"confirmed\":8270,\"recovered\":7115,\"deaths\":131,\"updated\":\"2020/12/22 06:22:55+00\"},\"Ibaraki\":{\"lat\":\"36.303588\",\"long\":\"140.319591\",\"confirmed\":2149,\"recovered\":1844,\"deaths\":35,\"updated\":\"2020/12/22 06:22:55+00\"},\"Ishikawa\":{\"lat\":\"36.769464\",\"long\":\"136.771027\",\"confirmed\":967,\"recovered\":835,\"deaths\":51,\"updated\":\"2020/12/22 06:22:55+00\"},\"Iwate\":{\"lat\":\"39.593287\",\"long\":\"141.361777\",\"confirmed\":336,\"recovered\":204,\"deaths\":18,\"updated\":\"2020/12/22 06:22:55+00\"},\"Kagawa\":{\"lat\":\"34.217292\",\"long\":\"133.969047\",\"confirmed\":211,\"recovered\":181,\"deaths\":3,\"updated\":\"2020/12/22 06:22:55+00\"},\"Kagoshima\":{\"lat\":\"31.009484\",\"long\":\"130.430665\",\"confirmed\":881,\"recovered\":739,\"deaths\":15,\"updated\":\"2020/12/22 06:22:55+00\"},\"Kanagawa\":{\"lat\":\"35.415312\",\"long\":\"139.338983\",\"confirmed\":17071,\"recovered\":14735,\"deaths\":236,\"updated\":\"2020/12/22 06:22:55+00\"},\"Kochi\":{\"lat\":\"33.422519\",\"long\":\"133.367307\",\"confirmed\":518,\"recovered\":323,\"deaths\":5,\"updated\":\"2020/12/22 06:22:55+00\"},\"Kumamoto\":{\"lat\":\"32.608154\",\"long\":\"130.745231\",\"confirmed\":1472,\"recovered\":1128,\"deaths\":15,\"updated\":\"2020/12/22 06:22:55+00\"},\"Kyoto\":{\"lat\":\"35.253815\",\"long\":\"135.443341\",\"confirmed\":3829,\"recovered\":2922,\"deaths\":42,\"updated\":\"2020/12/22 06:22:55+00\"},\"Mie\":{\"lat\":\"34.508018\",\"long\":\"136.376013\",\"confirmed\":1150,\"recovered\":946,\"deaths\":14,\"updated\":\"2020/12/22 06:22:55+00\"},\"Miyagi\":{\"lat\":\"38.446859\",\"long\":\"140.927086\",\"confirmed\":1782,\"recovered\":1381,\"deaths\":11,\"updated\":\"2020/12/22 06:22:55+00\"},\"Miyazaki\":{\"lat\":\"32.193204\",\"long\":\"131.299374\",\"confirmed\":668,\"recovered\":582,\"deaths\":6,\"updated\":\"2020/12/22 06:22:55+00\"},\"Nagano\":{\"lat\":\"36.132134\",\"long\":\"138.045528\",\"confirmed\":1052,\"recovered\":861,\"deaths\":10,\"updated\":\"2020/12/22 06:22:55+00\"},\"Nagasaki\":{\"lat\":\"33.235712\",\"long\":\"129.608033\",\"confirmed\":419,\"recovered\":277,\"deaths\":3,\"updated\":\"2020/12/22 06:22:55+00\"},\"Nara\":{\"lat\":\"34.317451\",\"long\":\"135.871644\",\"confirmed\":1659,\"recovered\":1390,\"deaths\":20,\"updated\":\"2020/12/22 06:22:55+00\"},\"Niigata\":{\"lat\":\"37.521819\",\"long\":\"138.918647\",\"confirmed\":445,\"recovered\":372,\"deaths\":3,\"updated\":\"2020/12/22 06:22:55+00\"},\"Oita\":{\"lat\":\"33.200697\",\"long\":\"131.43324\",\"confirmed\":576,\"recovered\":469,\"deaths\":5,\"updated\":\"2020/12/22 06:22:55+00\"},\"Okayama\":{\"lat\":\"34.89246\",\"long\":\"133.826252\",\"confirmed\":1124,\"recovered\":642,\"deaths\":13,\"updated\":\"2020/12/22 06:22:55+00\"},\"Okinawa\":{\"lat\":\"25.768923\",\"long\":\"126.668016\",\"confirmed\":4999,\"recovered\":4602,\"deaths\":82,\"updated\":\"2020/12/22 06:22:55+00\"},\"Osaka\":{\"lat\":\"34.620965\",\"long\":\"135.507481\",\"confirmed\":27218,\"recovered\":22846,\"deaths\":432,\"updated\":\"2020/12/22 06:22:55+00\"},\"Port Quarantine\":{\"lat\":\"\",\"long\":\"\",\"confirmed\":1786,\"recovered\":1625,\"deaths\":1,\"updated\":\"2020/12/22 06:22:55+00\"},\"Saga\":{\"lat\":\"33.286977\",\"long\":\"130.115738\",\"confirmed\":409,\"recovered\":369,\"deaths\":3,\"updated\":\"2020/12/22 06:22:55+00\"},\"Saitama\":{\"lat\":\"35.997101\",\"long\":\"139.347635\",\"confirmed\":11810,\"recovered\":9408,\"deaths\":177,\"updated\":\"2020/12/22 06:22:55+00\"},\"Shiga\":{\"lat\":\"35.215827\",\"long\":\"136.138064\",\"confirmed\":944,\"recovered\":836,\"deaths\":11,\"updated\":\"2020/12/22 06:22:55+00\"},\"Shimane\":{\"lat\":\"35.07076\",\"long\":\"132.554064\",\"confirmed\":181,\"recovered\":163,\"deaths\":0,\"updated\":\"2020/12/22 06:22:55+00\"},\"Shizuoka\":{\"lat\":\"34.916975\",\"long\":\"138.407784\",\"confirmed\":2383,\"recovered\":1725,\"deaths\":28,\"updated\":\"2020/12/22 06:22:55+00\"},\"Tochigi\":{\"lat\":\"36.689912\",\"long\":\"139.819213\",\"confirmed\":1039,\"recovered\":755,\"deaths\":5,\"updated\":\"2020/12/22 06:22:55+00\"},\"Tokushima\":{\"lat\":\"33.919178\",\"long\":\"134.242091\",\"confirmed\":195,\"recovered\":178,\"deaths\":10,\"updated\":\"2020/12/22 06:22:55+00\"},\"Tokyo\":{\"lat\":\"35.711343\",\"long\":\"139.446921\",\"confirmed\":51887,\"recovered\":44802,\"deaths\":542,\"updated\":\"2020/12/22 06:22:55+00\"},\"Tottori\":{\"lat\":\"35.359069\",\"long\":\"133.863619\",\"confirmed\":70,\"recovered\":61,\"deaths\":0,\"updated\":\"2020/12/22 06:22:55+00\"},\"Toyama\":{\"lat\":\"36.637464\",\"long\":\"137.269346\",\"confirmed\":504,\"recovered\":440,\"deaths\":26,\"updated\":\"2020/12/22 06:22:55+00\"},\"Unknown\":{\"lat\":\"\",\"long\":\"\",\"confirmed\":8,\"recovered\":8,\"deaths\":0,\"updated\":\"2020/12/22 06:22:55+00\"},\"Wakayama\":{\"lat\":\"33.911879\",\"long\":\"135.505446\",\"confirmed\":582,\"recovered\":528,\"deaths\":7,\"updated\":\"2020/12/22 06:22:55+00\"},\"Yamagata\":{\"lat\":\"38.448396\",\"long\":\"140.102154\",\"confirmed\":330,\"recovered\":192,\"deaths\":3,\"updated\":\"2020/12/22 06:22:55+00\"},\"Yamaguchi\":{\"lat\":\"34.20119\",\"long\":\"131.573293\",\"confirmed\":472,\"recovered\":402,\"deaths\":2,\"updated\":\"2020/12/22 06:22:55+00\"},\"Yamanashi\":{\"lat\":\"35.612364\",\"long\":\"138.611489\",\"confirmed\":488,\"recovered\":422,\"deaths\":9,\"updated\":\"2020/12/22 06:22:55+00\"}}";

  JsonObject& root = jsonBuffer.parseObject(json);

  JsonObject& All = root["All"];
  long All_confirmed = All["confirmed"]; // 201087
  long All_recovered = All["recovered"]; // 167357
  int All_deaths = All["deaths"]; // 2833
  const char* All_country = All["country"]; // "Japan"
  long All_population = All["population"]; // 127484450
  long All_sq_km_area = All["sq_km_area"]; // 377829
  const char* All_life_expectancy = All["life_expectancy"]; // "80.7"
  int All_elevation_in_meters = All["elevation_in_meters"]; // 438
  const char* All_continent = All["continent"]; // "Asia"
  const char* All_abbreviation = All["abbreviation"]; // "JP"
  const char* All_location = All["location"]; // "Eastern Asia"
  int All_iso = All["iso"]; // 392
  const char* All_capital_city = All["capital_city"]; // "Tokyo"

  JsonObject& Aichi = root["Aichi"];
  const char* Aichi_lat = Aichi["lat"]; // "35.035551"
  const char* Aichi_long = Aichi["long"]; // "137.211621"
  int Aichi_confirmed = Aichi["confirmed"]; // 14236
  int Aichi_recovered = Aichi["recovered"]; // 11581
  int Aichi_deaths = Aichi["deaths"]; // 151
  const char* Aichi_updated = Aichi["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Akita = root["Akita"];
  const char* Akita_lat = Akita["lat"]; // "39.748679"
  const char* Akita_long = Akita["long"]; // "140.408228"
  int Akita_confirmed = Akita["confirmed"]; // 95
  int Akita_recovered = Akita["recovered"]; // 90
  int Akita_deaths = Akita["deaths"]; // 1
  const char* Akita_updated = Akita["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Aomori = root["Aomori"];
  const char* Aomori_lat = Aomori["lat"]; // "40.781541"
  const char* Aomori_long = Aomori["long"]; // "140.828896"
  int Aomori_confirmed = Aomori["confirmed"]; // 395
  int Aomori_recovered = Aomori["recovered"]; // 345
  int Aomori_deaths = Aomori["deaths"]; // 6
  const char* Aomori_updated = Aomori["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Chiba = root["Chiba"];
  const char* Chiba_lat = Chiba["lat"]; // "35.510141"
  const char* Chiba_long = Chiba["long"]; // "140.198917"
  int Chiba_confirmed = Chiba["confirmed"]; // 9177
  int Chiba_recovered = Chiba["recovered"]; // 7721
  int Chiba_deaths = Chiba["deaths"]; // 104
  const char* Chiba_updated = Chiba["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Ehime = root["Ehime"];
  const char* Ehime_lat = Ehime["lat"]; // "33.624835"
  const char* Ehime_long = Ehime["long"]; // "132.856842"
  int Ehime_confirmed = Ehime["confirmed"]; // 375
  int Ehime_recovered = Ehime["recovered"]; // 319
  int Ehime_deaths = Ehime["deaths"]; // 11
  const char* Ehime_updated = Ehime["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Fukui = root["Fukui"];
  const char* Fukui_lat = Fukui["lat"]; // "35.846614"
  const char* Fukui_long = Fukui["long"]; // "136.224654"
  int Fukui_confirmed = Fukui["confirmed"]; // 337
  int Fukui_recovered = Fukui["recovered"]; // 313
  int Fukui_deaths = Fukui["deaths"]; // 11
  const char* Fukui_updated = Fukui["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Fukuoka = root["Fukuoka"];
  const char* Fukuoka_lat = Fukuoka["lat"]; // "33.526032"
  const char* Fukuoka_long = Fukuoka["long"]; // "130.666949"
  int Fukuoka_confirmed = Fukuoka["confirmed"]; // 7458
  int Fukuoka_recovered = Fukuoka["recovered"]; // 6210
  int Fukuoka_deaths = Fukuoka["deaths"]; // 113
  const char* Fukuoka_updated = Fukuoka["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Fukushima = root["Fukushima"];
  const char* Fukushima_lat = Fukushima["lat"]; // "37.378867"
  const char* Fukushima_long = Fukushima["long"]; // "140.223295"
  int Fukushima_confirmed = Fukushima["confirmed"]; // 758
  int Fukushima_recovered = Fukushima["recovered"]; // 552
  int Fukushima_deaths = Fukushima["deaths"]; // 12
  const char* Fukushima_updated = Fukushima["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Gifu = root["Gifu"];
  const char* Gifu_lat = Gifu["lat"]; // "35.778671"
  const char* Gifu_long = Gifu["long"]; // "137.055925"
  int Gifu_confirmed = Gifu["confirmed"]; // 1748
  int Gifu_recovered = Gifu["recovered"]; // 1360
  int Gifu_deaths = Gifu["deaths"]; // 24
  const char* Gifu_updated = Gifu["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Gunma = root["Gunma"];
  const char* Gunma_lat = Gunma["lat"]; // "36.504479"
  const char* Gunma_long = Gunma["long"]; // "138.985605"
  int Gunma_confirmed = Gunma["confirmed"]; // 1950
  int Gunma_recovered = Gunma["recovered"]; // 1471
  int Gunma_deaths = Gunma["deaths"]; // 31
  const char* Gunma_updated = Gunma["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Hiroshima = root["Hiroshima"];
  const char* Hiroshima_lat = Hiroshima["lat"]; // "34.605309"
  const char* Hiroshima_long = Hiroshima["long"]; // "132.788719"
  int Hiroshima_confirmed = Hiroshima["confirmed"]; // 2378
  int Hiroshima_recovered = Hiroshima["recovered"]; // 1157
  int Hiroshima_deaths = Hiroshima["deaths"]; // 14
  const char* Hiroshima_updated = Hiroshima["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Hokkaido = root["Hokkaido"];
  const char* Hokkaido_lat = Hokkaido["lat"]; // "43.385711"
  const char* Hokkaido_long = Hokkaido["long"]; // "142.552318"
  int Hokkaido_confirmed = Hokkaido["confirmed"]; // 12296
  int Hokkaido_recovered = Hokkaido["recovered"]; // 9930
  int Hokkaido_deaths = Hokkaido["deaths"]; // 381
  const char* Hokkaido_updated = Hokkaido["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Hyogo = root["Hyogo"];
  const char* Hyogo_lat = Hyogo["lat"]; // "35.039913"
  const char* Hyogo_long = Hyogo["long"]; // "134.828057"
  int Hyogo_confirmed = Hyogo["confirmed"]; // 8270
  int Hyogo_recovered = Hyogo["recovered"]; // 7115
  int Hyogo_deaths = Hyogo["deaths"]; // 131
  const char* Hyogo_updated = Hyogo["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Ibaraki = root["Ibaraki"];
  const char* Ibaraki_lat = Ibaraki["lat"]; // "36.303588"
  const char* Ibaraki_long = Ibaraki["long"]; // "140.319591"
  int Ibaraki_confirmed = Ibaraki["confirmed"]; // 2149
  int Ibaraki_recovered = Ibaraki["recovered"]; // 1844
  int Ibaraki_deaths = Ibaraki["deaths"]; // 35
  const char* Ibaraki_updated = Ibaraki["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Ishikawa = root["Ishikawa"];
  const char* Ishikawa_lat = Ishikawa["lat"]; // "36.769464"
  const char* Ishikawa_long = Ishikawa["long"]; // "136.771027"
  int Ishikawa_confirmed = Ishikawa["confirmed"]; // 967
  int Ishikawa_recovered = Ishikawa["recovered"]; // 835
  int Ishikawa_deaths = Ishikawa["deaths"]; // 51
  const char* Ishikawa_updated = Ishikawa["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Iwate = root["Iwate"];
  const char* Iwate_lat = Iwate["lat"]; // "39.593287"
  const char* Iwate_long = Iwate["long"]; // "141.361777"
  int Iwate_confirmed = Iwate["confirmed"]; // 336
  int Iwate_recovered = Iwate["recovered"]; // 204
  int Iwate_deaths = Iwate["deaths"]; // 18
  const char* Iwate_updated = Iwate["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Kagawa = root["Kagawa"];
  const char* Kagawa_lat = Kagawa["lat"]; // "34.217292"
  const char* Kagawa_long = Kagawa["long"]; // "133.969047"
  int Kagawa_confirmed = Kagawa["confirmed"]; // 211
  int Kagawa_recovered = Kagawa["recovered"]; // 181
  int Kagawa_deaths = Kagawa["deaths"]; // 3
  const char* Kagawa_updated = Kagawa["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Kagoshima = root["Kagoshima"];
  const char* Kagoshima_lat = Kagoshima["lat"]; // "31.009484"
  const char* Kagoshima_long = Kagoshima["long"]; // "130.430665"
  int Kagoshima_confirmed = Kagoshima["confirmed"]; // 881
  int Kagoshima_recovered = Kagoshima["recovered"]; // 739
  int Kagoshima_deaths = Kagoshima["deaths"]; // 15
  const char* Kagoshima_updated = Kagoshima["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Kanagawa = root["Kanagawa"];
  const char* Kanagawa_lat = Kanagawa["lat"]; // "35.415312"
  const char* Kanagawa_long = Kanagawa["long"]; // "139.338983"
  int Kanagawa_confirmed = Kanagawa["confirmed"]; // 17071
  int Kanagawa_recovered = Kanagawa["recovered"]; // 14735
  int Kanagawa_deaths = Kanagawa["deaths"]; // 236
  const char* Kanagawa_updated = Kanagawa["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Kochi = root["Kochi"];
  const char* Kochi_lat = Kochi["lat"]; // "33.422519"
  const char* Kochi_long = Kochi["long"]; // "133.367307"
  int Kochi_confirmed = Kochi["confirmed"]; // 518
  int Kochi_recovered = Kochi["recovered"]; // 323
  int Kochi_deaths = Kochi["deaths"]; // 5
  const char* Kochi_updated = Kochi["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Kumamoto = root["Kumamoto"];
  const char* Kumamoto_lat = Kumamoto["lat"]; // "32.608154"
  const char* Kumamoto_long = Kumamoto["long"]; // "130.745231"
  int Kumamoto_confirmed = Kumamoto["confirmed"]; // 1472
  int Kumamoto_recovered = Kumamoto["recovered"]; // 1128
  int Kumamoto_deaths = Kumamoto["deaths"]; // 15
  const char* Kumamoto_updated = Kumamoto["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Kyoto = root["Kyoto"];
  const char* Kyoto_lat = Kyoto["lat"]; // "35.253815"
  const char* Kyoto_long = Kyoto["long"]; // "135.443341"
  int Kyoto_confirmed = Kyoto["confirmed"]; // 3829
  int Kyoto_recovered = Kyoto["recovered"]; // 2922
  int Kyoto_deaths = Kyoto["deaths"]; // 42
  const char* Kyoto_updated = Kyoto["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Mie = root["Mie"];
  const char* Mie_lat = Mie["lat"]; // "34.508018"
  const char* Mie_long = Mie["long"]; // "136.376013"
  int Mie_confirmed = Mie["confirmed"]; // 1150
  int Mie_recovered = Mie["recovered"]; // 946
  int Mie_deaths = Mie["deaths"]; // 14
  const char* Mie_updated = Mie["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Miyagi = root["Miyagi"];
  const char* Miyagi_lat = Miyagi["lat"]; // "38.446859"
  const char* Miyagi_long = Miyagi["long"]; // "140.927086"
  int Miyagi_confirmed = Miyagi["confirmed"]; // 1782
  int Miyagi_recovered = Miyagi["recovered"]; // 1381
  int Miyagi_deaths = Miyagi["deaths"]; // 11
  const char* Miyagi_updated = Miyagi["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Miyazaki = root["Miyazaki"];
  const char* Miyazaki_lat = Miyazaki["lat"]; // "32.193204"
  const char* Miyazaki_long = Miyazaki["long"]; // "131.299374"
  int Miyazaki_confirmed = Miyazaki["confirmed"]; // 668
  int Miyazaki_recovered = Miyazaki["recovered"]; // 582
  int Miyazaki_deaths = Miyazaki["deaths"]; // 6
  const char* Miyazaki_updated = Miyazaki["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Nagano = root["Nagano"];
  const char* Nagano_lat = Nagano["lat"]; // "36.132134"
  const char* Nagano_long = Nagano["long"]; // "138.045528"
  int Nagano_confirmed = Nagano["confirmed"]; // 1052
  int Nagano_recovered = Nagano["recovered"]; // 861
  int Nagano_deaths = Nagano["deaths"]; // 10
  const char* Nagano_updated = Nagano["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Nagasaki = root["Nagasaki"];
  const char* Nagasaki_lat = Nagasaki["lat"]; // "33.235712"
  const char* Nagasaki_long = Nagasaki["long"]; // "129.608033"
  int Nagasaki_confirmed = Nagasaki["confirmed"]; // 419
  int Nagasaki_recovered = Nagasaki["recovered"]; // 277
  int Nagasaki_deaths = Nagasaki["deaths"]; // 3
  const char* Nagasaki_updated = Nagasaki["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Nara = root["Nara"];
  const char* Nara_lat = Nara["lat"]; // "34.317451"
  const char* Nara_long = Nara["long"]; // "135.871644"
  int Nara_confirmed = Nara["confirmed"]; // 1659
  int Nara_recovered = Nara["recovered"]; // 1390
  int Nara_deaths = Nara["deaths"]; // 20
  const char* Nara_updated = Nara["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Niigata = root["Niigata"];
  const char* Niigata_lat = Niigata["lat"]; // "37.521819"
  const char* Niigata_long = Niigata["long"]; // "138.918647"
  int Niigata_confirmed = Niigata["confirmed"]; // 445
  int Niigata_recovered = Niigata["recovered"]; // 372
  int Niigata_deaths = Niigata["deaths"]; // 3
  const char* Niigata_updated = Niigata["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Oita = root["Oita"];
  const char* Oita_lat = Oita["lat"]; // "33.200697"
  const char* Oita_long = Oita["long"]; // "131.43324"
  int Oita_confirmed = Oita["confirmed"]; // 576
  int Oita_recovered = Oita["recovered"]; // 469
  int Oita_deaths = Oita["deaths"]; // 5
  const char* Oita_updated = Oita["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Okayama = root["Okayama"];
  const char* Okayama_lat = Okayama["lat"]; // "34.89246"
  const char* Okayama_long = Okayama["long"]; // "133.826252"
  int Okayama_confirmed = Okayama["confirmed"]; // 1124
  int Okayama_recovered = Okayama["recovered"]; // 642
  int Okayama_deaths = Okayama["deaths"]; // 13
  const char* Okayama_updated = Okayama["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Okinawa = root["Okinawa"];
  const char* Okinawa_lat = Okinawa["lat"]; // "25.768923"
  const char* Okinawa_long = Okinawa["long"]; // "126.668016"
  int Okinawa_confirmed = Okinawa["confirmed"]; // 4999
  int Okinawa_recovered = Okinawa["recovered"]; // 4602
  int Okinawa_deaths = Okinawa["deaths"]; // 82
  const char* Okinawa_updated = Okinawa["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Osaka = root["Osaka"];
  const char* Osaka_lat = Osaka["lat"]; // "34.620965"
  const char* Osaka_long = Osaka["long"]; // "135.507481"
  int Osaka_confirmed = Osaka["confirmed"]; // 27218
  int Osaka_recovered = Osaka["recovered"]; // 22846
  int Osaka_deaths = Osaka["deaths"]; // 432
  const char* Osaka_updated = Osaka["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Port_Quarantine = root["Port Quarantine"];
  const char* Port_Quarantine_lat = Port_Quarantine["lat"]; // ""
  const char* Port_Quarantine_long = Port_Quarantine["long"]; // ""
  int Port_Quarantine_confirmed = Port_Quarantine["confirmed"]; // 1786
  int Port_Quarantine_recovered = Port_Quarantine["recovered"]; // 1625
  int Port_Quarantine_deaths = Port_Quarantine["deaths"]; // 1
  const char* Port_Quarantine_updated = Port_Quarantine["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Saga = root["Saga"];
  const char* Saga_lat = Saga["lat"]; // "33.286977"
  const char* Saga_long = Saga["long"]; // "130.115738"
  int Saga_confirmed = Saga["confirmed"]; // 409
  int Saga_recovered = Saga["recovered"]; // 369
  int Saga_deaths = Saga["deaths"]; // 3
  const char* Saga_updated = Saga["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Saitama = root["Saitama"];
  const char* Saitama_lat = Saitama["lat"]; // "35.997101"
  const char* Saitama_long = Saitama["long"]; // "139.347635"
  int Saitama_confirmed = Saitama["confirmed"]; // 11810
  int Saitama_recovered = Saitama["recovered"]; // 9408
  int Saitama_deaths = Saitama["deaths"]; // 177
  const char* Saitama_updated = Saitama["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Shiga = root["Shiga"];
  const char* Shiga_lat = Shiga["lat"]; // "35.215827"
  const char* Shiga_long = Shiga["long"]; // "136.138064"
  int Shiga_confirmed = Shiga["confirmed"]; // 944
  int Shiga_recovered = Shiga["recovered"]; // 836
  int Shiga_deaths = Shiga["deaths"]; // 11
  const char* Shiga_updated = Shiga["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Shimane = root["Shimane"];
  const char* Shimane_lat = Shimane["lat"]; // "35.07076"
  const char* Shimane_long = Shimane["long"]; // "132.554064"
  int Shimane_confirmed = Shimane["confirmed"]; // 181
  int Shimane_recovered = Shimane["recovered"]; // 163
  int Shimane_deaths = Shimane["deaths"]; // 0
  const char* Shimane_updated = Shimane["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Shizuoka = root["Shizuoka"];
  const char* Shizuoka_lat = Shizuoka["lat"]; // "34.916975"
  const char* Shizuoka_long = Shizuoka["long"]; // "138.407784"
  int Shizuoka_confirmed = Shizuoka["confirmed"]; // 2383
  int Shizuoka_recovered = Shizuoka["recovered"]; // 1725
  int Shizuoka_deaths = Shizuoka["deaths"]; // 28
  const char* Shizuoka_updated = Shizuoka["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Tochigi = root["Tochigi"];
  const char* Tochigi_lat = Tochigi["lat"]; // "36.689912"
  const char* Tochigi_long = Tochigi["long"]; // "139.819213"
  int Tochigi_confirmed = Tochigi["confirmed"]; // 1039
  int Tochigi_recovered = Tochigi["recovered"]; // 755
  int Tochigi_deaths = Tochigi["deaths"]; // 5
  const char* Tochigi_updated = Tochigi["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Tokushima = root["Tokushima"];
  const char* Tokushima_lat = Tokushima["lat"]; // "33.919178"
  const char* Tokushima_long = Tokushima["long"]; // "134.242091"
  int Tokushima_confirmed = Tokushima["confirmed"]; // 195
  int Tokushima_recovered = Tokushima["recovered"]; // 178
  int Tokushima_deaths = Tokushima["deaths"]; // 10
  const char* Tokushima_updated = Tokushima["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Tokyo = root["Tokyo"];
  const char* Tokyo_lat = Tokyo["lat"]; // "35.711343"
  const char* Tokyo_long = Tokyo["long"]; // "139.446921"
  long Tokyo_confirmed = Tokyo["confirmed"]; // 51887
  long Tokyo_recovered = Tokyo["recovered"]; // 44802
  int Tokyo_deaths = Tokyo["deaths"]; // 542
  const char* Tokyo_updated = Tokyo["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Tottori = root["Tottori"];
  const char* Tottori_lat = Tottori["lat"]; // "35.359069"
  const char* Tottori_long = Tottori["long"]; // "133.863619"
  int Tottori_confirmed = Tottori["confirmed"]; // 70
  int Tottori_recovered = Tottori["recovered"]; // 61
  int Tottori_deaths = Tottori["deaths"]; // 0
  const char* Tottori_updated = Tottori["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Toyama = root["Toyama"];
  const char* Toyama_lat = Toyama["lat"]; // "36.637464"
  const char* Toyama_long = Toyama["long"]; // "137.269346"
  int Toyama_confirmed = Toyama["confirmed"]; // 504
  int Toyama_recovered = Toyama["recovered"]; // 440
  int Toyama_deaths = Toyama["deaths"]; // 26
  const char* Toyama_updated = Toyama["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Unknown = root["Unknown"];
  const char* Unknown_lat = Unknown["lat"]; // ""
  const char* Unknown_long = Unknown["long"]; // ""
  int Unknown_confirmed = Unknown["confirmed"]; // 8
  int Unknown_recovered = Unknown["recovered"]; // 8
  int Unknown_deaths = Unknown["deaths"]; // 0
  const char* Unknown_updated = Unknown["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Wakayama = root["Wakayama"];
  const char* Wakayama_lat = Wakayama["lat"]; // "33.911879"
  const char* Wakayama_long = Wakayama["long"]; // "135.505446"
  int Wakayama_confirmed = Wakayama["confirmed"]; // 582
  int Wakayama_recovered = Wakayama["recovered"]; // 528
  int Wakayama_deaths = Wakayama["deaths"]; // 7
  const char* Wakayama_updated = Wakayama["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Yamagata = root["Yamagata"];
  const char* Yamagata_lat = Yamagata["lat"]; // "38.448396"
  const char* Yamagata_long = Yamagata["long"]; // "140.102154"
  int Yamagata_confirmed = Yamagata["confirmed"]; // 330
  int Yamagata_recovered = Yamagata["recovered"]; // 192
  int Yamagata_deaths = Yamagata["deaths"]; // 3
  const char* Yamagata_updated = Yamagata["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Yamaguchi = root["Yamaguchi"];
  const char* Yamaguchi_lat = Yamaguchi["lat"]; // "34.20119"
  const char* Yamaguchi_long = Yamaguchi["long"]; // "131.573293"
  int Yamaguchi_confirmed = Yamaguchi["confirmed"]; // 472
  int Yamaguchi_recovered = Yamaguchi["recovered"]; // 402
  int Yamaguchi_deaths = Yamaguchi["deaths"]; // 2
  const char* Yamaguchi_updated = Yamaguchi["updated"]; // "2020/12/22 06:22:55+00"

  JsonObject& Yamanashi = root["Yamanashi"];
  const char* Yamanashi_lat = Yamanashi["lat"]; // "35.612364"
  const char* Yamanashi_long = Yamanashi["long"]; // "138.611489"
  int Yamanashi_confirmed = Yamanashi["confirmed"]; // 488
  int Yamanashi_recovered = Yamanashi["recovered"]; // 422
  int Yamanashi_deaths = Yamanashi["deaths"]; // 9
  const char* Yamanashi_updated = Yamanashi["updated"]; // "2020/12/22 06:22:55+00"







  //the HTML of the web page
  page = "<!DOCTYPE html>"
         "<html lang=""en"">"
         "<head>"
         "<meta charset=""UTF-8"">"
         "<meta name=""viewport"" content=""width=device-width, initial-scale=1.0"">"
         "<title>NodeMCU Web Server</title>"
         "<!-- WEBSITE ICON -->"
         "<link rel=""icon"" href=""https://img2.pngio.com/debo-jt-esp8266-developer-boards-nodemcu-esp8266-wi-fi-module-nodemcu-png-999_738.png"" type=""image/icon type"">"
         "<!-- <link rel=""stylesheet"" href=""css/style.css""> -->"
         "<script src=""script.js""></script>"
         "<style>"
         "body {"
         "background-color: #2c2c2c;"
         "font-family: ""Roboto"", sans-serif;"
         "border: 1px solid;"
         "border-color: gray;"
         "border-radius: 20px;"
         "margin-left: 25%;"
         "margin-right: 35%;"
         "width: 750px;"
         "height: 50%;"
         "padding: 20px;"
         "}"
         "div.txtBox {"
         "background-color: #ffffff;"
         "font-family: ""Roboto"", sans-serif;"
         "border: 1px solid;"
         "border-color: gray;"
         "border-radius: 20px;"
         "margin-left: auto;"
         "margin-right: auto;"
         "width: 700px;"
         "height: auto;"
         "padding: 10px;"
         "}"
         "#paragraphdescription {"
         "text-indent: 10px;"
         "}"
         "#id {"
         "font-size: medium;"
         "}"
         "img {"
         "border: 2px solid #555;"
         "}"
         "</style>"
         "</head>"
         "<body>"
         "<div class=""txtBox"">"
         "<center>"
         "<h1>ESP8266 Web Server with parsed JSON data</h1>"
         "<img src=""https://upload.wikimedia.org/wikipedia/en/9/9e/Flag_of_Japan.svg"" alt=""Flag_of_Japan"" width=""auto"" height=""180px"">"
         "<img id=""COVID"" src=""https://www.fda.gov/files/covid19-1600x900.jpg"" alt=""COVID19"" width=""auto"" height=""180px"">"
         "<!-- <img src=""https://www.fda.gov/files/covid19-1600x900.jpg"" alt=""COVID19"" width=""auto"" height=""180px""> -->"
         "</center>"
         "<p align=""justify"" id=""paragraphdescription"">"
         "This webpage displays the parsed JSON data coming from "
         "<a href=""https://covid-api.mmediagroup.fr/v1/cases?country=Japan"" target=""_blank"">this site</a>."
         "Which is a data coming from a COVID19 API that gets the current number of confirmed cases, recoveries,"
         " and deaths in any Country."
         "<br><br>"
         "</p>"
         "<h1>Country: " +(String) All_country+"</h1>"
         "<h2>Confirmed Cases: " +(String) All_confirmed+"</h2>"
         "<h2>Total Recovered: " +(String) All_recovered+"</h2>"
         "<h2>Total Deaths: " +(String) All_deaths+"</h2>"
         "</div>"
         "</body>"
         "</html>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);

  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", []() {
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000);
  });
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  server.handleClient();
}
