#include <SPIFFS.h>
#include <ESP32_JPEG_Library.h>

#include <Arduino_GFX_Library.h>
Arduino_DataBus *bus = new Arduino_ESP32SPI(16 /* DC */, 5 /* CS */, 18 /* SCK */, 19 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *gfx = new Arduino_ST7789(bus, 23 /* TFT_RST */, 0 /* rotation */, true /* IPS */, 135 /* width */, 240 /* height */, 52 /* col offset 1 */, 40 /* row offset 1 */, 53 /* col offset 2 */, 40 /* row offset 2 */);

#define ROOT "/root"
#define JPEG_FILENAME ROOT "/img_test_320_240.jpg"
#define JPEG_FILENAME ROOT "/img_test_135_240.jpg"
#define JPEG_FILENAMEZ ROOT "/img_test_135_240z.jpg"
uint8_t *image_jpeg = NULL;
uint8_t *image_rgb = NULL;
size_t image_size = 0;
size_t image_jpeg_size = 0;

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){ Serial.println("Failed to open directory"); return; }
    if(!root.isDirectory()){ Serial.println("Not a directory"); return; }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : "); Serial.print (file.name());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);
            if(levels){ listDir(fs, file.path(), levels -1); }
        } else {
            Serial.print("  FILE: "); Serial.print(file.name());
            Serial.print("  SIZE: "); Serial.print(file.size());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);
        }
        file = root.openNextFile();
    }
}

static jpeg_error_t esp_jpeg_decoder(const char *path)
{

  listDir(SPIFFS, "/", 0);

  Serial.printf("Reading file: %s\r\n", path);

  FILE *f = fopen(path, "r");
  if (!f)
  {
    Serial.println("- failed to open file for reading");
    return JPEG_ERR_MEM;
  }

  size_t len = fread(image_jpeg, 1, image_size, f);
  fclose(f);
  Serial.printf("Read file done len: %d\n", len);


  jpeg_error_t ret = JPEG_ERR_OK;
  int inbuf_consumed = 0;

  // Generate default configuration
  jpeg_dec_config_t config = {
      .output_type = JPEG_RAW_TYPE_RGB565_BE,
      .rotate = JPEG_ROTATE_0D,
  };

  // Empty handle to jpeg_decoder
  jpeg_dec_handle_t *jpeg_dec = NULL;

  // Create jpeg_dec
  jpeg_dec = jpeg_dec_open(&config);

  // Create io_callback handle
  jpeg_dec_io_t *jpeg_io = (jpeg_dec_io_t *)calloc(1, sizeof(jpeg_dec_io_t));
  if (jpeg_io == NULL)
  {
    return JPEG_ERR_MEM;
  }

  // Create out_info handle
  jpeg_dec_header_info_t *out_info = (jpeg_dec_header_info_t *)calloc(1, sizeof(jpeg_dec_header_info_t));
  if (out_info == NULL)
  {
    return JPEG_ERR_MEM;
  }
  // Set input buffer and buffer len to io_callback
  jpeg_io->inbuf = image_jpeg;
  jpeg_io->inbuf_len = len;

  // Parse jpeg picture header and get picture for user and decoder
  ret = jpeg_dec_parse_header(jpeg_dec, jpeg_io, out_info);
  if (ret < 0)
  {
    Serial.println("JPEG decode parse failed");
    goto _exit;
  }

  jpeg_io->outbuf = image_rgb;
  inbuf_consumed = jpeg_io->inbuf_len - jpeg_io->inbuf_remain;
  jpeg_io->inbuf = image_jpeg + inbuf_consumed;
  jpeg_io->inbuf_len = jpeg_io->inbuf_remain;

  // Start decode jpeg raw data
  ret = jpeg_dec_process(jpeg_dec, jpeg_io);
  if (ret < 0)
  {
    Serial.println("JPEG decode process failed");
    goto _exit;
  }

_exit:
  // Decoder deinitialize
  jpeg_dec_close(jpeg_dec);
  free(out_info);
  free(jpeg_io);
  return ret;
}

void setup()
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Arduino_GFX ESP32 SIMD JPEG Image Viewer example");

#ifdef GFX_EXTRA_PRE_INIT
  GFX_EXTRA_PRE_INIT();
#endif

  // Init Display
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BLACK);

//#ifdef GFX_BL
  pinMode(4, OUTPUT);  digitalWrite(4, HIGH); // ?
//#endif

   if (!SPIFFS.begin(false, ROOT))
  {
    Serial.println(F("ERROR: File System Mount Failed!"));
    gfx->println(F("ERROR: File System Mount Failed!"));
  }
  else
  {
    image_size = gfx->width() * gfx->height() * 2;
    image_jpeg_size = image_size / 7;
    image_rgb = (uint8_t *)aligned_alloc(16, image_size);
    image_jpeg = (uint8_t *)aligned_alloc(16, image_jpeg_size);
  }
}

int fsel = 0;
void loop()
{
  unsigned long start = millis();

  gfx->fillScreen(BLUE);
  jpeg_error_t ret = JPEG_ERR_OK;
  //uint32_t t = millis();
  
  //ret = esp_jpeg_decoder(JPEG_FILENAME);
  if((fsel & 1)==0) ret = esp_jpeg_decoder(JPEG_FILENAME);
  else              ret = esp_jpeg_decoder(JPEG_FILENAMEZ);
  fsel++;

  if (ret != JPEG_ERR_OK)
  {
    Serial.printf("JPEG decode failed - %d\n", (int)ret);
  }
  else
  {
    gfx->draw16bitBeRGBBitmap(0, 0, (uint16_t *)image_rgb, gfx->width(), gfx->height());
  }

  Serial.printf("Time used: %lu\n", millis() - start);

  delay(1000);
}
