#include <Arduino.h>
#include <Ticker.h>

Ticker tk, tk1;

int timer_flag = 0;
int count = 0;

void timer_coming_once_cb(void)
{
  Serial.println("time coming only once.");
  tk1.detach();
}

void time_coming_cicyle_cb(void)
{
  timer_flag = 1;
  count++;
}

void setup() {
  Serial.begin(9600);
  tk1.once(6, timer_coming_once_cb);
  // call time_coming_cicyle_cb every 3s
  tk.attach(3, time_coming_cicyle_cb);
}

void loop() {
  if (1 == timer_flag)
  {
    Serial.println("time coming......");
    Serial.println(count);
    timer_flag = 0;

    if (10 == count)
    {
      Serial.println("stop timer");
      tk.detach();
    }
  }
}
