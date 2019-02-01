#include "../Parameter/MatrixVariable.h"

//DeviceInfo
extern u8 device_id = 203; //0~255 0 for off
extern Modes mode = Normal;
extern u8 app_id = -1;

//LED setting
extern u8 brightness = 64;
extern u8 brightness_level[5] = {32,64,96,128,160};

extern u32 palette[3][128] =     //WRGB Colour Palette
{{            //MatrixColorPalette
  0x00000000, //0
  0x00050505, //1
  0x00101010, //2
  0x00242424, //3
  0x004E4E4E, //4
  0x00727272, //5
  0x00AFAFAF, //6
  0x00FFFFFF, //7
  0x00130000, //8
  0x00270000, //9
  0x005D0000, //10
  0x00A20000, //11
  0x00FF0000, //12
  0x00FF0C0C, //13
  0x00FF1F1F, //14
  0x00FF3F3F, //15
  0x00130500, //16
  0x00270A00, //17
  0x005D1700, //18
  0x00A22900, //19
  0x00FF4000, //20
  0x00FF490C, //21
  0x00FF571F, //22
  0x00FF6F3F, //23
  0x00130A00, //24
  0x00271400, //25
  0x005D2F00, //26
  0x00A25100, //27
  0x00FF8000, //28
  0x00FF860C, //29
  0x00FF8F1F, //30
  0x00FF9F3F, //31
  0x00130E00, //32
  0x00271D00, //33
  0x005D4600, //34
  0x00A27A00, //35
  0x00FFBF00, //36
  0x00FFC20C, //37
  0x00FFC71F, //38
  0x00FFCF3F, //39
  0x00131300, //40
  0x00272700, //41
  0x005D5D00, //42
  0x00A2A200, //43
  0x00FFFF00, //44
  0x00FFFF0C, //45
  0x00FFFF1F, //46
  0x00FFFF3F, //47
  0x000A1300, //48
  0x00142700, //49
  0x002F5D00, //50
  0x0051A200, //51
  0x0080FF00, //52
  0x0086FF0C, //53
  0x008FFF1F, //54
  0x009FFF3F, //55
  0x00001300, //56
  0x00002700, //57
  0x00005D00, //58
  0x0000A200, //59
  0x0000FF00, //60
  0x000CFF0C, //61
  0x001FFF1F, //62
  0x003FFF3F, //63
  0x0000130D, //64
  0x0000271A, //65
  0x00005D3E, //66
  0x0000A26C, //67
  0x0000FFAA, //68
  0x000CFFAE, //69
  0x001FFFB4, //70
  0x003FFFBF, //71
  0x00001113, //72
  0x00002727, //73
  0x00005D5D, //74
  0x0000A2A2, //75
  0x0000FFFF, //76
  0x000CFFFF, //77
  0x001FFFFF, //78
  0x003FFFFF, //79
  0x00000A13, //80
  0x00001427, //81
  0x00002F5D, //82
  0x000051A2, //83
  0x000080FF, //84
  0x000C86FF, //85
  0x001F8FFF, //86
  0x003F9FFF, //87
  0x00000013, //88
  0x00000027, //89
  0x0000005D, //90
  0x000000A2, //91
  0x000000FF, //92
  0x000C0CFF, //93
  0x001F1FFF, //94
  0x003F3FFF, //95
  0x000A0013, //96
  0x00140027, //97
  0x002F005D, //98
  0x005100A2, //99
  0x008000FF, //100
  0x00860CFF, //101
  0x008F1FFF, //102
  0x009F3FFF, //103
  0x00130013, //104
  0x00270027, //105
  0x005D005D, //106
  0x00A200A2, //107
  0x00FF00FF, //108
  0x00FF0CFF, //109
  0x00FF1FFF, //110
  0x00FF3F9F, //111
  0x0013000A, //112
  0x00270014, //113
  0x005D002F, //114
  0x00A20051, //115
  0x00FF0080, //116
  0x00FF0C86, //117
  0x00FF1F8F, //118
  0x00FF3F9F, //119
  0x00130005, //120
  0x0027000A, //121
  0x005D0017, //122
  0x00A20029, //123
  0x00FF0040, //124
  0x00FF0C49, //125
  0x00FF1F57, //126
  0x00FF3F6F //127
},{           //LaunchpadColorPalette
  0x00000000, //0
  0x001E1E1E, //1
  0x007F7F7F, //2
  0x004C4C4C, //3
  0x00FFFFFF, //4
  0x00FF0000, //5
  0x00590000, //6
  0x00190000, //7
  0x00FFBD6C, //8
  0x00FF5400, //9
  0x00591D00, //10
  0x00271B00, //11
  0x00FFFF4C, //12
  0x00FFFF00, //13
  0x00595900, //14
  0x00191900, //15
  0x0088FF4C, //16
  0x0054FF00, //17
  0x001D5900, //18
  0x00142B00, //19
  0x004CFF4C, //20
  0x0000FF00, //21
  0x00005900, //22
  0x00001900, //23
  0x004CFF5E, //24
  0x0000FF19, //25
  0x0000590D, //26
  0x00001902, //27
  0x004CFF88, //28
  0x0000FF55, //29
  0x0000591D, //30
  0x00001F12, //31
  0x004CFFB7, //32
  0x0000FF99, //33
  0x00005935, //34
  0x00001912, //35
  0x004CC3FF, //36
  0x0000A9FF, //37
  0x00004152, //38
  0x00001019, //39
  0x004C88FF, //40
  0x000055FF, //41
  0x00001D59, //42
  0x00000819, //43
  0x004C4CFF, //44
  0x000000FF, //45
  0x00000059, //46
  0x00000019, //47
  0x00874CFF, //48
  0x005400FF, //49
  0x00190064, //50
  0x000F0030, //51
  0x00FF4CFF, //52
  0x00FF00FF, //53
  0x00590059, //54
  0x00190019, //55
  0x00FF4C87, //56
  0x00FF0054, //57
  0x0059001D, //58
  0x00220013, //59
  0x00FF1500, //60
  0x00993500, //61
  0x00795100, //62
  0x00436400, //63
  0x00033900, //64
  0x00005735, //65
  0x0000547F, //66
  0x000000FF, //67
  0x0000454F, //68
  0x002500CC, //69
  0x007F7F7F, //70
  0x00202020, //71
  0x00FF0000, //72
  0x00BDFF2D, //73
  0x00AFED06, //74
  0x0064FF09, //75
  0x00108B00, //76
  0x0000FF87, //77
  0x0000A9FF, //78
  0x00002AFF, //79
  0x003F00FF, //80
  0x007A00FF, //81
  0x00B21A7D, //82
  0x00402100, //83
  0x00FF4A00, //84
  0x0088E106, //85
  0x0072FF15, //86
  0x0000FF00, //87
  0x003BFF26, //88
  0x0059FF71, //89
  0x0038FFCC, //90
  0x005B8AFF, //91
  0x003151C6, //92
  0x00877FE9, //93
  0x00D31DFF, //94
  0x00FF005D, //95
  0x00FF7F00, //96
  0x00B9B000, //97
  0x0090FF00, //98
  0x00835D07, //99
  0x00392B00, //100
  0x00144C10, //101
  0x000D5038, //102
  0x0015152A, //103
  0x0016205A, //104
  0x00693C1C, //105
  0x00A8000A, //106
  0x00DE513D, //107
  0x00D86A1C, //108
  0x00FFE126, //109
  0x009EE12F, //110
  0x0067B50F, //111
  0x001E1E30, //112
  0x00DCFF6B, //113
  0x0080FFBD, //114
  0x009A99FF, //115
  0x008E66FF, //116
  0x00404040, //117
  0x00757575, //118
  0x00E0FFFF, //119
  0x00A00000, //120
  0x00350000, //121
  0x001AD000, //122
  0x00074200, //123
  0x00B9B000, //124
  0x003F3100, //125
  0x00B35F00, //126
  0x004B1502  //127,
},{           //Custom Colour palette default use 203 palette
  0x00000000, //0
  0x00050505, //1
  0x00101010, //2
  0x00242424, //3
  0x004E4E4E, //4
  0x00727272, //5
  0x00AFAFAF, //6
  0x00FFFFFF, //7
  0x00130000, //8
  0x00270000, //9
  0x005D0000, //10
  0x00A20000, //11
  0x00FF0000, //12
  0x00FF0C0C, //13
  0x00FF1F1F, //14
  0x00FF3F3F, //15
  0x00130500, //16
  0x00270A00, //17
  0x005D1700, //18
  0x00A22900, //19
  0x00FF4000, //20
  0x00FF490C, //21
  0x00FF571F, //22
  0x00FF6F3F, //23
  0x00130A00, //24
  0x00271400, //25
  0x005D2F00, //26
  0x00A25100, //27
  0x00FF8000, //28
  0x00FF860C, //29
  0x00FF8F1F, //30
  0x00FF9F3F, //31
  0x00130E00, //32
  0x00271D00, //33
  0x005D4600, //34
  0x00A27A00, //35
  0x00FFBF00, //36
  0x00FFC20C, //37
  0x00FFC71F, //38
  0x00FFCF3F, //39
  0x00131300, //40
  0x00272700, //41
  0x005D5D00, //42
  0x00A2A200, //43
  0x00FFFF00, //44
  0x00FFFF0C, //45
  0x00FFFF1F, //46
  0x00FFFF3F, //47
  0x000A1300, //48
  0x00142700, //49
  0x002F5D00, //50
  0x0051A200, //51
  0x0080FF00, //52
  0x0086FF0C, //53
  0x008FFF1F, //54
  0x009FFF3F, //55
  0x00001300, //56
  0x00002700, //57
  0x00005D00, //58
  0x0000A200, //59
  0x0000FF00, //60
  0x000CFF0C, //61
  0x001FFF1F, //62
  0x003FFF3F, //63
  0x0000130D, //64
  0x0000271A, //65
  0x00005D3E, //66
  0x0000A26C, //67
  0x0000FFAA, //68
  0x000CFFAE, //69
  0x001FFFB4, //70
  0x003FFFBF, //71
  0x00001113, //72
  0x00002727, //73
  0x00005D5D, //74
  0x0000A2A2, //75
  0x0000FFFF, //76
  0x000CFFFF, //77
  0x001FFFFF, //78
  0x003FFFFF, //79
  0x00000A13, //80
  0x00001427, //81
  0x00002F5D, //82
  0x000051A2, //83
  0x000080FF, //84
  0x000C86FF, //85
  0x001F8FFF, //86
  0x003F9FFF, //87
  0x00000013, //88
  0x00000027, //89
  0x0000005D, //90
  0x000000A2, //91
  0x000000FF, //92
  0x000C0CFF, //93
  0x001F1FFF, //94
  0x003F3FFF, //95
  0x000A0013, //96
  0x00140027, //97
  0x002F005D, //98
  0x005100A2, //99
  0x008000FF, //100
  0x00860CFF, //101
  0x008F1FFF, //102
  0x009F3FFF, //103
  0x00130013, //104
  0x00270027, //105
  0x005D005D, //106
  0x00A200A2, //107
  0x00FF00FF, //108
  0x00FF0CFF, //109
  0x00FF1FFF, //110
  0x00FF3F9F, //111
  0x0013000A, //112
  0x00270014, //113
  0x005D002F, //114
  0x00A20051, //115
  0x00FF0080, //116
  0x00FF0C86, //117
  0x00FF1F8F, //118
  0x00FF3F9F, //119
  0x00130005, //120
  0x0027000A, //121
  0x005D0017, //122
  0x00A20029, //123
  0x00FF0040, //124
  0x00FF0C49, //125
  0x00FF1F57, //126
  0x00FF3F6F //127
}};

extern u8 led_gamma[256] =
{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

extern u8 bottomLEDmap [NUM_BOTTOM_LEDS] =
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};

//KeyPad
extern u8 keymap [YSIZE][XSIZE] =
{{64, 65, 66, 67, 96, 97, 98, 99},
{60, 61, 62, 63, 92, 93, 94, 95},
{56, 57, 58, 59, 88, 89, 90, 91},
{52, 53, 54, 55, 84, 85, 86, 87},
{48, 49, 50, 51, 80, 81, 82, 83},
{44, 45, 46, 47, 76, 77, 78, 79},
{40, 41, 42, 43, 72, 73, 74, 75},
{36, 37, 38, 39, 68, 69, 70, 71}};

//TouchBar
extern u8 touch_sensitive = 0;

//Sysex
extern u8 rotation = 0;
extern u8 midi_channel = 0;
extern bool gamma_enable = false; //Wont effect colour palette
extern bool midi_enable = true;
extern bool m2p_enable = false;
extern bool powercord_enable = false;
extern bool massage_return = false;

extern u8 font[96][6] = {
	{4, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // 32 = Space
	{1, 0b11111011}, // 33 = !
	{3, 0b11100000, 0b00000000, 0b11100000}, // 34 = "
	{5, 0b00101000, 0b11111110, 0b00101000, 0b11111110, 0b00101000}, // 35 = #
	{5, 0b00100100, 0b01010100, 0b11111110, 0b01010100, 0b01001000}, // 36 = $
	{5, 0b11000100, 0b11001000, 0b00010000, 0b00100110, 0b01000110}, // 37 = %
	{5, 0b01101100, 0b10010010, 0b10010010, 0b01101100, 0b00001010}, // 38 = &
	{2, 0b00100000, 0b11000000}, // 39 = '
	{2, 0b01111100, 0b10000010}, // 40 = (
	{2, 0b10000010, 0b01111100}, // 41 = )
	{5, 0b00101000, 0b00111000, 0b01111100, 0b00111000, 0b00101000}, // 42 = *
	{5, 0b00010000, 0b00010000, 0b01111100, 0b00010000, 0b00010000}, // 43 = +
	{4, 0b00000000, 0b00000101, 0b00000110, 0b00000000}, // 44 = ,
	{4, 0b00010000, 0b00010000, 0b00010000, 0b00010000}, // 45 = -
	{4, 0b00000000, 0b00000110, 0b00000110, 0b00000000}, // 46 = .
	{5, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000}, // 47 = /
	{5, 0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01111100}, // 48 = 0
	{3, 0b01000010, 0b11111110, 0b00000010}, // 49 = 1
	{5, 0b01001110, 0b10010010, 0b10010010, 0b10010010, 0b01100010}, // 50 = 2
	{5, 0b01000100, 0b10000010, 0b10010010, 0b10010010, 0b01101100}, // 51 = 3
	{5, 0b00011000, 0b00101000, 0b01001000, 0b11111110, 0b00001000}, // 52 = 4
	{5, 0b11100100, 0b10100010, 0b10100010, 0b10100010, 0b10011100}, // 53 = 5
	{5, 0b01111100, 0b10010010, 0b10010010, 0b10010010, 0b01001100}, // 54 = 6
	{5, 0b10000000, 0b10000110, 0b10011000, 0b10100000, 0b11000000}, // 55 = 7
	{5, 0b01101100, 0b10010010, 0b10010010, 0b10010010, 0b01101100}, // 56 = 8
	{5, 0b01100100, 0b10010010, 0b10010010, 0b10010010, 0b01111100}, // 57 = 9
	{4, 0b00000000, 0b00110110, 0b00110110, 0b00000000}, // 58 = :
	{4, 0b00000000, 0b00110101, 0b00110110, 0b00000000}, // 59 = ;
	{4, 0b00010000, 0b00101000, 0b01000100, 0b10000010}, // 60 = <
	{4, 0b00101000, 0b00101000, 0b00101000, 0b00101000}, // 61 = =
	{4, 0b10000010, 0b01000100, 0b00101000, 0b00010000}, // 62 = >
	{5, 0b01000000, 0b10000000, 0b10001010, 0b10010000, 0b01100000}, // 63 = ?
	{5, 0b01111100, 0b10000010, 0b10010010, 0b10101010, 0b01111000}, // 64 = @
	{5, 0b00000110, 0b00111000, 0b11001000, 0b00111000, 0b00000110}, // 65 = A
	{5, 0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b01101100}, // 66 = B
	{5, 0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01000100}, // 67 = C
	{5, 0b11111110, 0b10000010, 0b10000010, 0b01000100, 0b00111000}, // 68 = D
	{5, 0b11111110, 0b10010010, 0b10010010, 0b10010010, 0b10000010}, // 69 = E
	{5, 0b11111110, 0b10010000, 0b10010000, 0b10010000, 0b10000000}, // 70 = F
	{5, 0b01111100, 0b10000010, 0b10000010, 0b10010010, 0b10011110}, // 71 = G
	{5, 0b11111110, 0b00010000, 0b00010000, 0b00010000, 0b11111110}, // 72 = H
	{3, 0b10000010, 0b11111110, 0b10000010}, // 73 = I
	{4, 0b00000100, 0b00000010, 0b10000010, 0b11111100}, // 74 = J
	{5, 0b11111110, 0b00010000, 0b00101000, 0b01000100, 0b10000010}, // 75 = K
	{5, 0b11111110, 0b00000010, 0b00000010, 0b00000010, 0b00000010}, // 76 = L
	{5, 0b11111110, 0b01000000, 0b00110000, 0b01000000, 0b11111110}, // 77 = M
	{5, 0b11111110, 0b01100000, 0b00010000, 0b00001100, 0b11111110}, // 78 = N
	{5, 0b01111100, 0b10000010, 0b10000010, 0b10000010, 0b01111100}, // 79 = O
	{5, 0b11111110, 0b10010000, 0b10010000, 0b10010000, 0b01100000}, // 80 = P
	{5, 0b01111100, 0b10000010, 0b10001010, 0b10000100, 0b01111010}, // 81 = Q
	{5, 0b11111110, 0b10010000, 0b10011000, 0b10010100, 0b01100010}, // 82 = R
	{5, 0b01100100, 0b10110010, 0b10010010, 0b10010010, 0b01001100}, // 83 = S
	{5, 0b10000000, 0b10000000, 0b11111110, 0b10000000, 0b10000000}, // 84 = T
	{5, 0b11111100, 0b00000010, 0b00000010, 0b00000010, 0b11111100}, // 85 = U
	{5, 0b11100000, 0b00011000, 0b00000110, 0b00011000, 0b11100000}, // 86 = V
	{5, 0b11110000, 0b00001110, 0b00110000, 0b00001110, 0b11110000}, // 87 = W
	{5, 0b11000110, 0b00101000, 0b00010000, 0b00101000, 0b11000110}, // 88 = X
	{5, 0b11000000, 0b00100000, 0b00011110, 0b00100000, 0b11000000}, // 89 = Y
	{5, 0b10000110, 0b10001010, 0b10010010, 0b10100010, 0b11000010}, // 90 = Z
	{3, 0b11111110, 0b10000010, 0b10000010}, // 91 = [
	{5, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100}, // 92 = Backslash
	{3, 0b10000010, 0b10000010, 0b11111110}, // 93 = ]
	{5, 0b00100000, 0b01000000, 0b10000000, 0b01000000, 0b00100000}, // 94 = ^
	{5, 0b00000010, 0b00000010, 0b00000010, 0b00000010, 0b00000010}, // 95 = _
	{2, 0b11000000, 0b00100000}, // 96 = `
	{5, 0b00000100, 0b00101010, 0b00101010, 0b00101010, 0b00011110}, // 97 = a
	{5, 0b11111110, 0b00100010, 0b00100010, 0b00100010, 0b00011100}, // 98 = b
	{5, 0b00011100, 0b00100010, 0b00100010, 0b00100010, 0b00100010}, // 99 = c
	{5, 0b00011100, 0b00100010, 0b00100010, 0b00100010, 0b11111110}, // 100 = d
	{5, 0b00011100, 0b00101010, 0b00101010, 0b00101010, 0b00011010}, // 101 = e
	{4, 0b00010000, 0b01111110, 0b10010000, 0b10010000}, // 102 = f
	{5, 0b00011000, 0b00100101, 0b00100101, 0b00100101, 0b00111110}, // 103 = g
	{5, 0b11111110, 0b00100000, 0b00100000, 0b00100000, 0b00011110}, // 104 = h
	{2, 0b10111100, 0b00000010}, // 105 = i
	{3, 0b00000010, 0b00000001, 0b10111110}, // 106 = j
	{4, 0b11111110, 0b00001000, 0b00010100, 0b00100010}, // 107 = k
	{2, 0b11111100, 0b00000010}, // 108 = l
	{5, 0b00111110, 0b00100000, 0b00011110, 0b00100000, 0b00011110}, // 109 = m
	{5, 0b00111110, 0b00100000, 0b00100000, 0b00100000, 0b00011110}, // 110 = n
	{5, 0b00011100, 0b00100010, 0b00100010, 0b00100010, 0b00011100}, // 111 = o
	{5, 0b00111111, 0b00100100, 0b00100100, 0b00100100, 0b00011000}, // 112 = p
	{5, 0b00011100, 0b00100010, 0b00100010, 0b00100100, 0b00111111}, // 113 = q
	{4, 0b00111110, 0b00010000, 0b00100000, 0b00100000}, // 114 = r
	{5, 0b00010010, 0b00101010, 0b00101010, 0b00101010, 0b00100100}, // 115 = s
	{3, 0b00100000, 0b01111100, 0b00100010}, // 116 = t
	{5, 0b00111100, 0b00000010, 0b00000010, 0b00000100, 0b00111110}, // 117 = u
	{5, 0b00110000, 0b00001100, 0b00000010, 0b00001100, 0b00110000}, // 118 = v
	{5, 0b00111000, 0b00000110, 0b00111000, 0b00000110, 0b00111000}, // 119 = w
	{5, 0b00100010, 0b00010100, 0b00001000, 0b00010100, 0b00100010}, // 120 = x
	{5, 0b00111000, 0b00000101, 0b00000101, 0b00000101, 0b00111110}, // 121 = y
	{5, 0b00100010, 0b00100110, 0b00101010, 0b00110010, 0b00100010}, // 122 = z
	{3, 0b00010000, 0b01101100, 0b10000010}, // 123 = {
	{1, 0b11111111}, // 124 = |
	{3, 0b10000010, 0b01101100, 0b00010000}, // 125 = }
	{4, 0b01000000, 0b10000000, 0b01000000, 0b10000000, }, // 126 = ~
	{5, 0b00111000, 0b00101000, 0b01101100, 0b00101000, 0b00010000} // 127 = DEL
};

extern u8 half_height_num_font[10][3] = {
  {B1111, B1001, B1111},  //0
  {B0000, B0000, B1111},  //1
  {B0000, B1011, B1101},  //2
  {B1001, B1101, B1111},  //3
  {B1110, B0010, B0111},  //4
  {B0000, B1101, B1011},  //5
  {B0000, B1111, B0011},  //6
  {B0000, B1000, B1111},  //7
  {B1111, B1101, B1111},  //8
  {B0000, B1100, B1111},  //9
  //{B0000, B0000, B0000},  //space
};
