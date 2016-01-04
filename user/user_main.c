/*
The MIT License (MIT)

Copyright (c) 2015 Pedro Minatel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "osapi.h"
#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"
#include "driver/uart.h"

// Contains ssid and password
//#include "user_config.h"

const char wifi_ssid[32] = "ssid";
const char wifi_pass[64] = "wifipassword";

// Data structure for the configuration of your wireless network.
// Will contain ssid and password for your network.
struct station_config stationConf;

void ICACHE_FLASH_ATTR wifiInit() {
  // Copy the ssid and the password into the data structure for later call.
  os_memcpy(&stationConf.ssid, wifi_ssid, 32);
  os_memcpy(&stationConf.password, wifi_pass, 64);

  // Set the wifi mode.  Can be STATION_MODE, SOFTAP_MODE or STATIONAP_MODE.
  // In this caswe we just want to connect as a client on the wireless network
  // so we use station  mode.
  wifi_set_opmode( STATION_MODE );
  // Set the ssid and password of the network you want to connect to.
  wifi_station_set_config(&stationConf);

  // wifi_station_connect isn't needed as when wifi_station_set_config is called as
  // the esp8266 will connect to the router automatically.
  //wifi_station_connect();
}

void user_init(void) {
  // Configure the UART0 and UART1 (TX only) to 115200
  uart_init(BIT_RATE_115200,BIT_RATE_115200);

#ifdef DEBUG_OVER_SERIAL
  system_set_os_print(ON);
  os_printf("\nStarting...\n");
  os_printf("HEAP: %ld\n",system_get_free_heap_size());
  os_printf("CHIP ID: %ld\n",system_get_chip_id());
  os_printf("FLASH SIZE: %ld\n",system_get_flash_size_map());
  os_printf("VERSION: %c\n",system_get_sdk_version());
#else
  system_set_os_print(OFF);
#endif

  // Print a message that we are starting user_init on debug uart
  wifi_station_disconnect();
  wifi_softap_set_config()

  // Setup the wifi
  //wifiInit();

  // Print a message that we have completed user_init on debug uart
  //os_printf("Ready...\n");
}
