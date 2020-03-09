
void printBuffer0(void){
  display.setLogBuffer(1, 15);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(20, 20, "Welcome to");
  
  display.display();
}
void printBuffer01(void){
  display.setLogBuffer(1, 15);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  
  display.drawString(16, 20, "ESP GPS MOD");
  display.display();
}

void printBuffer03(void){
  display.setLogBuffer(1, 15);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  
  display.drawString(10, 20, "Temperature over limit !!");
  display.display();
}