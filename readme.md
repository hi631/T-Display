<br>Includes examples of software that works with T-Display

![td_sample.jpg](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/159764/01543d65-a31b-b36e-0513-877fa368785c.jpeg)

For Arduino_GFX
Specify the pin number during initial setup.
◇AnimatedGIF_GIFDEC GIF animation of a rotating globe
◇Clock A simple clock
LovyanGFX
Register the hardware configuration in the library.
LGFX_ESP32C3-TTGO_T-Display.hpp must be stored in Arduino\libraries\LovyanGFX\src\lgfx_user beforehand.
*Some parts have become uncompileable due to library updates.
◇ClockSample Analog/digital clock
◇DrawLineThickness Some kind of pattern; they probably mean that the drawing is fast.
◇Graph Multiple scrolling graphs
◇MovingCircles (cannot be compiled)  Circles move at high speed.
◇MovingIcons (cannot be compiled) Icons move at high speed.
◇RotatedZoomSample Rotates and condenses.
TFT_eSPI
Works with the default settings.
◇boing_ball A round ball bounces.
◇Flash_Jpg_DMA An image (panda) is displayed.
◇SpriteRotatingCube A white cube bounces around.
◇SPIFFS_Jpg A landscape image is displayed.

[ More information ]( https://qiita.com/hi631/items/beba226886ce9b4cd086 )


T-Displayで動作するソフトウェアの例

Arduino_GFXの場合
　初期設定時にピン番号を指定する。
　◇AnimatedGIF_GIFDEC
　　地球が回るGIFアニメーション
　◇Clock
　　シンプルなクロック

LovyanGFXの場合
　ハード構成をライブラリに登録する。
　LGFX_ESP32C3-TTGO_T-Display.hppを、Arduino\libraries\LovyanGFX\src\lgfx_userに予め格納が必要。
　　※一部はライブラリアップデートでコンパイル不可になってしまった。
　◇ClockSample
　　アナログ・デジタル両様時計
　◇DrawLineThickness
　　なんだかわからない模様、描画が早いと言いたいのだろう。
　◇Graph
　　スクロールする複数本のグラフ
　◇MovingCircles(コンパイル不可)
　　輪が高速で動く。
　◇MovingIcons(コンパイル不可)
　　アイコンが高速で動く。
　◇RotatedZoomSample
　　ぐるぐる回って凝縮される。

TFT_eSPI
　ディフォルト設定の決め打ちで動作する。
　◇boing_ball
　　丸いボールが跳ねる。
　◇Flash_Jpg_DMA
　　画像（パンダ）が表示される。
　◇SpriteRotatingCube
　　白いキューブが跳ね回る。
　◇SPIFFS_Jpg
　　風景画像が表示される。

[ 詳しくは ]( https://qiita.com/hi631/items/beba226886ce9b4cd086 )
