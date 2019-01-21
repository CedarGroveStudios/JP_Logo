/* ATtiny85_jp_2018-12-13_v00
   For back-lighted PCB
     ATtiny85-10 (low voltage)
     to conserve power, burn bootloader for 1MHz internal clock
*/
  #include <avr/power.h>

  // define PWM output pins
  int
    red_led =  4,        // green LED analog OUT pin #4
    grn_led_1 =  1,        // green LED analog OUT pin #1
    grn_led_2 =  0;        // red LED analog OUT pin #0
    
  // define constants
  int
    red_low       =    0, // minimum red LED brightness
    red_glow      =  20, // maximum red LED brightness
    red_hot_rate  =   80, // step rate to maximum brightness in ms
    red_cold_rate =   120, // step rate to minimum brightness in ms
    grn_glow      =  24, // maximum green LED brightness
    grn_on_flick  =    2, // number of on flickers
    grn_on_time   =   10, // flicker time on in ms
    grn_off_time   =  60; // time between flickers in ms
  
  // define variables
  int
    count =             0; // general counter
    
void setup() {
  analogWrite(red_led, red_low);
  analogWrite(grn_led_1, 0);
  analogWrite(grn_led_2, 0);
  delay(1000);
}

void loop() {  
  grn_on_flick = random(1,5);
  
  for (count=0; count<=grn_on_flick; count++) {
    analogWrite(grn_led_1, 0);
    analogWrite(grn_led_2, 0);
    delay(grn_off_time);
    analogWrite(grn_led_1, grn_glow);
    analogWrite(grn_led_2, grn_glow);
    delay(grn_on_time);
  }

  delay(5);
  
  for (count=red_low; count<=red_glow; count++) { 
    delay(red_hot_rate);
    analogWrite(red_led, count);
  } 

  delay(random(3000,6000));
  analogWrite(grn_led_1, 0);
  analogWrite(grn_led_2, 0);
  delay(grn_off_time);
  analogWrite(grn_led_1, grn_glow);
  analogWrite(grn_led_2, grn_glow);
  delay(grn_on_time);
  analogWrite(grn_led_1, 0);
  analogWrite(grn_led_2, 0);
  
  for (count=red_glow; count>=red_low; count--) { 
    delay (red_cold_rate);
    analogWrite(red_led, count);
  }

  delay(random(5000,10000));
}


