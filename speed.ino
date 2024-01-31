#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int pin = 2;
unsigned int counter = 0; // счетчик смены положений
unsigned int counter1 = 0;//подсчет количества закрытий датчика
unsigned long per = 0;//время закрытия датчика
float counter2 = 0;// переменная для подсчета скорости вращения крыльчатки
unsigned long summa_per = 0; // суммарное время закрытия датчика
void period(){ // функция для расчета периода вращения
  per = pulseIn(pin,LOW); //возвращает время закрытия датчика в микросекундах
  summa_per=summa_per+per; //суммарное время закрытия датчика
  if(per!=0){
    counter1++;
    }
  lcd.print(per);
  lcd.setCursor(0,1);
  lcd.print(summa_per);
  lcd.clear(); 
}
  void ustirovka(){// функция для подсчета скорости вращения крыльчатки
  counter2 = counter1/(summa_per*0.000001);
  lcd.setCursor(5,1);
  lcd.print(counter2);
  delay(100);
  lcd.clear();
    
}
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  pinMode(pin,INPUT);
}
void loop() {
  period();
 if(pulseIn(pin,LOW,10)||pulseIn(pin,HIGH,10)==0){//должна запуститься после того, как в течение 10 сеунд не происходит смены сигнала с 1 на 0 или с 0 на 1 но почему-то функция работает непрерывно
  ustirovka();
 }
 else{
  period();
 }

}
