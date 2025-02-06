#pragma once

#define LGFX_USE_V1

#include <LovyanGFX.hpp>

// ESP32C3��LovyanGFX��Ǝ��ݒ�ŗ��p����ꍇ�̐ݒ��

/*
���̃t�@�C���𕡐����A�V�������O��t���āA���ɍ��킹�Đݒ���e��ύX���Ă��������B
�쐬�����t�@�C�������[�U�[�v���O��������include���邱�Ƃŗ��p�\�ɂȂ�܂��B

���������t�@�C���̓��C�u������lgfx_user�t�H���_�ɒu���ė��p���Ă��\���܂��񂪁A
���̏ꍇ�̓��C�u�����̃A�b�v�f�[�g���ɍ폜�����\��������̂ł����ӂ��������B

���S�ɉ^�p�������ꍇ�̓o�b�N�A�b�v���쐬���Ă������A���[�U�[�v���W�F�N�g�̃t�H���_�ɒu���Ă��������B
//*/


/// �Ǝ��̐ݒ���s���N���X���ALGFX_Device����h�����č쐬���܂��B
class LGFX : public lgfx::LGFX_Device
{
/*
 �N���X����"LGFX"����ʂ̖��O�ɕύX���Ă��\���܂���B
 AUTODETECT�ƕ��p����ꍇ��"LGFX"�͎g�p����Ă��邽�߁ALGFX�ȊO�̖��O�ɕύX���Ă��������B
 �܂��A�������̃p�l���𓯎��g�p����ꍇ�����ꂼ��ɈقȂ閼�O��t���Ă��������B
 �� �N���X����ύX����ꍇ�̓R���X�g���N�^�̖��O�������ē������O�ɕύX���K�v�ł��B

 ���O�̕t�����͎��R�Ɍ��߂č\���܂��񂪁A�ݒ肪�������ꍇ��z�肵�A
 �Ⴆ��ESP32 DevKit-C��SPI�ڑ���ILI9341�̐ݒ���s�����ꍇ�A
  LGFX_DevKitC_SPI_ILI9341
 �̂悤�Ȗ��O�ɂ��A�t�@�C�����ƃN���X������v�����Ă������ƂŁA���p���ɖ����ɂ����Ȃ�܂��B
//*/


// �ڑ�����p�l���̌^�ɂ������C���X�^���X��p�ӂ��܂��B
//lgfx::Panel_GC9A01      _panel_instance;
//lgfx::Panel_GDEW0154M09 _panel_instance;
//lgfx::Panel_HX8357B     _panel_instance;
//lgfx::Panel_HX8357D     _panel_instance;
//lgfx::Panel_ILI9163     _panel_instance;
//lgfx::Panel_ILI9341     _panel_instance;
//lgfx::Panel_ILI9342     _panel_instance;
//lgfx::Panel_ILI9481     _panel_instance;
//lgfx::Panel_ILI9486     _panel_instance;
//lgfx::Panel_ILI9488     _panel_instance;
//lgfx::Panel_IT8951      _panel_instance;
//lgfx::Panel_SH110x      _panel_instance; // SH1106, SH1107
//lgfx::Panel_SSD1306     _panel_instance;
//lgfx::Panel_SSD1327     _panel_instance;
//lgfx::Panel_SSD1331     _panel_instance;
//lgfx::Panel_SSD1351     _panel_instance; // SSD1351, SSD1357
//lgfx::Panel_SSD1963     _panel_instance;
//lgfx::Panel_ST7735      _panel_instance;
//lgfx::Panel_ST7735S     _panel_instance;
  lgfx::Panel_ST7789      _panel_instance;
//lgfx::Panel_ST7796      _panel_instance;


// �p�l����ڑ�����o�X�̎�ނɂ������C���X�^���X��p�ӂ��܂��B
  lgfx::Bus_SPI       _bus_instance;   // SPI�o�X�̃C���X�^���X
//lgfx::Bus_I2C       _bus_instance;   // I2C�o�X�̃C���X�^���X (ESP32�̂�)
//lgfx::Bus_Parallel8 _bus_instance;   // 8�r�b�g�p�������o�X�̃C���X�^���X (ESP32�̂�)

// �o�b�N���C�g���䂪�\�ȏꍇ�̓C���X�^���X��p�ӂ��܂��B(�K�v�Ȃ���΍폜)
  lgfx::Light_PWM     _light_instance;

// �^�b�`�X�N���[���̌^�ɂ������C���X�^���X��p�ӂ��܂��B(�K�v�Ȃ���΍폜)
//lgfx::Touch_FT5x06      _touch_instance; // FT5206, FT5306, FT5406, FT6206, FT6236, FT6336, FT6436
//lgfx::Touch_GT911       _touch_instance;
//lgfx::Touch_STMPE610    _touch_instance;
//lgfx::Touch_XPT2046     _touch_instance;

public:

  // �R���X�g���N�^���쐬���A�����Ŋe��ݒ���s���܂��B
  // �N���X����ύX�����ꍇ�̓R���X�g���N�^���������O���w�肵�Ă��������B
  LGFX(void)
  {
    { // �o�X����̐ݒ���s���܂��B
      auto cfg = _bus_instance.config();    // �o�X�ݒ�p�̍\���̂��擾���܂��B

// SPI�o�X�̐ݒ�
      cfg.spi_host = SPI2_HOST;     // �g�p����SPI��I��  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // �� ESP-IDF�o�[�W�����A�b�v�ɔ����AVSPI_HOST , HSPI_HOST�̋L�q�͔񐄏��ɂȂ邽�߁A�G���[���o��ꍇ�͑����SPI2_HOST , SPI3_HOST���g�p���Ă��������B
      cfg.spi_mode = 0;             // SPI�ʐM���[�h��ݒ� (0 ~ 3)
      cfg.freq_write = 40000000;    // ���M����SPI�N���b�N (�ő�80MHz, 80MHz�𐮐��Ŋ������l�Ɋۂ߂��܂�)
      cfg.freq_read  = 16000000;    // ��M����SPI�N���b�N
      cfg.spi_3wire  = true;        // ��M��MOSI�s���ōs���ꍇ��true��ݒ�
      cfg.use_lock   = true;        // �g�����U�N�V�������b�N���g�p����ꍇ��true��ݒ�
      cfg.dma_channel = SPI_DMA_CH_AUTO; // �g�p����DMA�`�����l����ݒ� (0=DMA�s�g�p / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=�����ݒ�)
      // �� ESP-IDF�o�[�W�����A�b�v�ɔ����ADMA�`�����l����SPI_DMA_CH_AUTO(�����ݒ�)�������ɂȂ�܂����B1ch,2ch�̎w��͔񐄏��ɂȂ�܂��B
      cfg.pin_sclk = 18;            // SPI��SCLK�s���ԍ���ݒ�
      cfg.pin_mosi = 19;            // SPI��MOSI�s���ԍ���ݒ�
      cfg.pin_miso = -1;            // SPI��MISO�s���ԍ���ݒ� (-1 = disable)
      cfg.pin_dc   = 16;            // SPI��D/C�s���ԍ���ݒ�  (-1 = disable)
     // SD�J�[�h�Ƌ��ʂ�SPI�o�X���g���ꍇ�AMISO�͏ȗ������K���ݒ肵�Ă��������B
//*/

      _bus_instance.config(cfg);    // �ݒ�l���o�X�ɔ��f���܂��B
      _panel_instance.setBus(&_bus_instance);      // �o�X���p�l���ɃZ�b�g���܂��B
    }

    { // �\���p�l������̐ݒ���s���܂��B
      auto cfg = _panel_instance.config();    // �\���p�l���ݒ�p�̍\���̂��擾���܂��B

      cfg.pin_cs           =     5;  // CS���ڑ�����Ă���s���ԍ�   (-1 = disable)
      cfg.pin_rst          =    23;  // RST���ڑ�����Ă���s���ԍ�  (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSY���ڑ�����Ă���s���ԍ� (-1 = disable)

      // �� �ȉ��̐ݒ�l�̓p�l�����Ɉ�ʓI�ȏ����l���ݒ肳��Ă��܂��̂ŁA�s���ȍ��ڂ̓R�����g�A�E�g���Ď����Ă݂Ă��������B

      //cfg.memory_width     =   135;  // �h���C�oIC���T�|�[�g���Ă���ő�̕�
      //cfg.memory_height    =   240;  // �h���C�oIC���T�|�[�g���Ă���ő�̍���
      cfg.panel_width      =   135;  // ���ۂɕ\���\�ȕ�
      cfg.panel_height     =   240;  // ���ۂɕ\���\�ȍ���
      cfg.offset_x         =    52;  // �p�l����X�����I�t�Z�b�g��
      cfg.offset_y         =    40;  // �p�l����Y�����I�t�Z�b�g��
      cfg.offset_rotation  =     0;  // ��]�����̒l�̃I�t�Z�b�g 0~7 (4~7�͏㉺���])
      cfg.dummy_read_pixel =     8;  // �s�N�Z���Ǐo���O�̃_�~�[���[�h�̃r�b�g��
      cfg.dummy_read_bits  =     1;  // �s�N�Z���ȊO�̃f�[�^�Ǐo���O�̃_�~�[���[�h�̃r�b�g��
      cfg.readable         =  true;  // �f�[�^�Ǐo�����\�ȏꍇ true�ɐݒ�
      cfg.invert           =  true;  // �p�l���̖��Â����]���Ă��܂��ꍇ true�ɐݒ�
      cfg.rgb_order        = false;  // �p�l���̐ԂƐ�����ւ���Ă��܂��ꍇ true�ɐݒ�
      cfg.dlen_16bit       = false;  // �f�[�^����16bit�P�ʂő��M����p�l���̏ꍇ true�ɐݒ�
      cfg.bus_shared       =  true;  // SD�J�[�h�ƃo�X�����L���Ă���ꍇ true�ɐݒ�(drawJpgFile���Ńo�X������s���܂�)

      _panel_instance.config(cfg);
    }

//*
    { // �o�b�N���C�g����̐ݒ���s���܂��B�i�K�v�Ȃ���΍폜�j
      auto cfg = _light_instance.config();    // �o�b�N���C�g�ݒ�p�̍\���̂��擾���܂��B

      cfg.pin_bl =  4;              // �o�b�N���C�g���ڑ�����Ă���s���ԍ�
      cfg.invert = false;           // �o�b�N���C�g�̋P�x�𔽓]������ꍇ true
      cfg.freq   = 44100;           // �o�b�N���C�g��PWM���g��
      cfg.pwm_channel = 7;          // �g�p����PWM�̃`�����l���ԍ�

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);  // �o�b�N���C�g���p�l���ɃZ�b�g���܂��B
    }
//*/

    setPanel(&_panel_instance); // �g�p����p�l�����Z�b�g���܂��B
  }
};