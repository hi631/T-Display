#define LGFX_USE_V1
#include <LovyanGFX.hpp>

//#define LGFX_AUTODETECT
//#include <LGFX_AUTODETECT.hpp>  // クラス"LGFX"を準備します
// #include <lgfx_user/LGFX_ESP32_sample.hpp> // またはユーザ自身が用意したLGFXクラスを準備します
 #include <lgfx_user/LGFX_ESP32C3-TTGO_T-Display.hpp> // またはユーザ自身が用意したLGFXクラスを準備します

static LGFX lcd;

static uint32_t sec, psec;
static uint32_t fps = 0, frame_count = 0;
static int32_t lcd_width ;
static int32_t lcd_height;

struct obj_info_t {
  int32_t x;
  int32_t y;
  int32_t r;
  int32_t dx;
  int32_t dy;
  uint32_t color;

  void move()
  {
    x += dx;
    y += dy;
    if (x < 0) {
      x = 0;
      if (dx < 0) dx = - dx;
    } else if (x >= lcd_width) {
      x = lcd_width -1;
      if (dx > 0) dx = - dx;
    }
    if (y < 0) {
      y = 0;
      if (dy < 0) dy = - dy;
    } else if (y >= lcd_height) {
      y = lcd_height - 1;
      if (dy > 0) dy = - dy;
    }
  }
};

static constexpr uint32_t obj_count = 200;
static obj_info_t objects[obj_count];

static LGFX_Sprite sprites[2];
static int_fast16_t sprite_height;

void setup(void)
{
  lcd.init();

  if (lcd.width() < lcd.height())
  {
    lcd.setRotation(lcd.getRotation() ^ 1);
  }
  lcd_width = lcd.width();
  lcd_height = lcd.height();
  obj_info_t *a;
  for (uint32_t i = 0; i < obj_count; ++i) {
    a = &objects[i];
    a->color = (uint32_t)rand() | 0x808080U;
    a->x = rand() % lcd_width;
    a->y = rand() % lcd_height;
    a->dx = ((rand() & 3) + 1) * (i & 1 ? 1 : -1);
    a->dy = ((rand() & 3) + 1) * (i & 2 ? 1 : -1);
    a->r = 8 + (i & 0x07);
  }

  uint32_t div = 2;
  for (;;) {
    sprite_height = (lcd_height + div - 1) / div;
    bool fail = false;
    for (uint32_t i = 0; !fail && i < 2; ++i)
    {
      sprites[i].setColorDepth(lcd.getColorDepth());
      sprites[i].setFont(&fonts::Font2);
      fail = !sprites[i].createSprite(lcd_width, sprite_height);
    }
    if (!fail) break;
    for (uint32_t i = 0; i < 2; ++i)
    {
      sprites[i].deleteSprite();
    }
    ++div;
  }
  lcd.startWrite();
}

void loop(void)
{
  static uint_fast8_t flip = 0;

  obj_info_t *a;
  for (uint32_t i = 0; i != obj_count; i++) {
    objects[i].move();
  }
  for (int32_t y = 0; y < lcd_height; y += sprite_height) {
    flip = flip ? 0 : 1;
    sprites[flip].clear();
    for (uint32_t i = 0; i != obj_count; i++) {
      a = &objects[i];
      if (( a->y + a->r >= y ) && ( a->y - a->r <= y + sprite_height ))
        sprites[flip].drawCircle(a->x, a->y - y, a->r, a->color);
    }

    if (y == 0) {
      sprites[flip].setCursor(1,1);
      sprites[flip].setTextColor(TFT_BLACK);
      sprites[flip].printf("obj:%d fps:%d", obj_count, fps);
      sprites[flip].setCursor(0,0);
      sprites[flip].setTextColor(TFT_WHITE);
      sprites[flip].printf("obj:%d fps:%d", obj_count, fps);
    }
    sprites[flip].pushSprite(&lcd, 0, y);
  }
  lcd.display();

  ++frame_count;
  sec = lgfx::millis() / 1000;
  if (psec != sec) {
    psec = sec;
    fps = frame_count;
    frame_count = 0;
  }
}
