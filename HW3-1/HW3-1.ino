// =============== 純粹彩虹快閃（超炫交作業加分用）===============
// RGB LED 共陽極接法（最常見）
// R → D3,   G → D5,   B → D6   （都有PWM）

const int Rpin = 3;
const int Gpin = 5;
const int Bpin = 6;

void setup() {
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
}

void loop() {
  rainbow(8);   // 數字越小越快，建議 5~15 最好看
}

// 超級簡單彩虹函式
void rainbow(uint8_t wait) {
  for (int i = 0; i < 256; i++) {         // 紅→綠
    setColorHSV(i, 255, 255);
    delay(wait);
  }
  for (int i = 0; i < 256; i++) {         // 綠→藍
    setColorHSV(255 - i, 255, 255);
    delay(wait);
  }
  for (int i = 0; i < 256; i++) {         // 藍→紅（完成一個循環）
    setColorHSV(i + 170, 255, 255);       // 170 是藍到紅的偏移
    delay(wait);
  }
}

// 把 HSV 的 H（0-360）轉成 RGB（超簡化版，夠用又漂亮）
void setColorHSV(int h, int s, int v) {
  h = h % 360;
  float c = v * s / 255.0;
  float x = c * (1 - abs((h / 60.0) - 2 * (h / 60 / 2) - 1));
  float m = v - c;

  float r, g, b;

  if (h < 60)      { r = c; g = x; b = 0; }
  else if (h < 120) { r = x; g = c; b = 0; }
  else if (h < 180) { r = 0; g = c; b = x; }
  else if (h < 240) { r = 0; g = x; b = c; }
  else if (h < 300) { r = x; g = 0; b = c; }
  else             { r = c; g = 0; b = x; }

  // 共陽極：要反向輸出
  analogWrite(Rpin, 255 - (int)((r + m) * 255 / 255));
  analogWrite(Gpin, 255 - (int)((g + m) * 255 / 255));
  analogWrite(Bpin, 255 - (int)((b + m) * 255 / 255));
}