# XIAO ESP32C3 Examples

Some examples done for the XIAO ESP32C3 board. They are inspired from other examples, but enhanced a bit to match a certain purpose.

## WiFi REST

This example shows a basic way how to make a REST API with a WiFi connected XIAO ESP32C3 board. [Check it out!](WiFi_REST/WiFi_REST.ino)

## WiFi REST Lib

REST example with a library. [Get it!](WiFi_REST_Lib/WiFi_REST_Lib.ino) You need to install the following libraries using the Library Manager (Tools > Manage Libraries).

- AsyncTCP
- ESPAsyncTCP
- ESPAsyncWebSrv

> **WARNING!** There is a bug in the ESPAsyncWebSrv library. Follow steps below to fix it.

1. Navigate to your Arduino libraries folder, usually something like `Documents/Arduino/libraries`. Ask internet if can't find.
2. The `ESPAsyncWebSrv` folder should be there. Go in there and find file `AsyncWebSocket.cpp`.
3. Change the line 832 from `return IPAddress(0U);` to `return IPAddress(static_cast<uint32_t>(0U));`.
4. Save the file and proceed with your Arduino project.

## jQuery Boostrap REST Demo

This example contains a HTML page that uses [jQuery](https://jquery.com/) and [Bootstrap](https://getbootstrap.com/) libraries to interact with the REST API covered in WiFi REST Lib example. 

### License

- [jQuery MIT License](https://github.com/jquery/jquery/blob/main/LICENSE.txt)
- [Bootstrap MIT License](https://github.com/twbs/bootstrap/blob/main/LICENSE)

