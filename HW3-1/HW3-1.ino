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
  rainbow(3);   
}


void rainbow(uint8_t wait) {
  for (int i = 0; i < 256; i++) {        
    setColorHSV(i, 255, 255);
    delay(wait);
  }
  for (int i = 0; i < 256; i++) {         
    setColorHSV(255 - i, 255, 255);
    delay(wait);
  }
  for (int i = 0; i < 256; i++) {        
    setColorHSV(i + 170, 255, 255);      
    delay(wait);
  }
}


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