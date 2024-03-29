/* 
 * Button Example for Rosserial
 */

#include <ros.h>
#include <std_msgs/Bool.h>


ros::NodeHandle nh;

std_msgs::Bool pushed_msg;
ros::Publisher pub_button("local_taster", &pushed_msg);

const int button_pin = 7;
const int led_pin = 13;

bool last_reading;
long last_debounce_time=0;
long debounce_delay=1000;

void setup()
{
  nh.initNode();
  nh.advertise(pub_button);
  
  //initialize an LED output pin 
  //and a input pin for our push button
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  
  //Enable the pullup resistor on the button
  digitalWrite(button_pin, HIGH);
  
  //The button is a normally button
  last_reading = ! digitalRead(button_pin);
 
}

void loop()
{
  
  bool reading = ! digitalRead(button_pin);
  
  //if the button value has not changed during the debounce delay
  // we know it is stable
  if ( (millis() - last_debounce_time)  >= debounce_delay) {
    last_debounce_time += debounce_delay;
    digitalWrite(led_pin, reading);
    pushed_msg.data = reading;
    pub_button.publish(&pushed_msg);
  }

  last_reading = reading;
  
  nh.spinOnce();
}
