%LocalAppData%\Arduino15\packages\esp32\tools\mkspiffs\0.2.3\mkspiffs.exe ^
  -c .\data ^
  -s 0x160000 ^
  SPIFFS.bin

%LocalAppData%\Arduino15\packages\esp32\tools\esptool_py\4.6\esptool.exe ^
  -p COM6 ^
  -b 921600 ^
  write_flash ^
  -ff 80m ^
  -fm dio ^
  0x290000 ^
  SPIFFS.bin

timeout 3
exit

éQè∆
http://www.neko.ne.jp/~freewing/hardware/espressif_esp32_upload_spiffs_command_line/

default.csvÇÃê›íË
# Name,   Type, SubType, Offset,  Size, Flags
nvs,      data, nvs,     0x9000,  0x5000,
otadata,  data, ota,     0xe000,  0x2000,
app0,     app,  ota_0,   0x10000, 0x140000,
app1,     app,  ota_1,   0x150000,0x140000,
spiffs,   data, spiffs,  0x290000,0x160000,    <----
coredump, data, coredump,0x3F0000,0x10000,
