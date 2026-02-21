#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
#include "distance_task.h"
#include "lid_control.h"

//declare task handlers
TaskHandle_t T1, T2, T3;
SemaphoreHandle_t xMutex;
QueueHandle_t xQopen, xQclose;


void setup() {
  Serial.begin(9600);
   //tasks , queues and semaphores initiation 
   xTaskCreate(distance_task,"distance using hc sensor",128,NULL,1,&T1);
   xTaskCreate(open_task,"open ",128,NULL,1,&T2);
   xTaskCreate(close_task,"close",128,NULL,1,&T3);  
   xMutex = xSemaphoreCreateMutex();   
   xQopen = xQueueCreate(1, sizeof(long));
   xQclose = xQueueCreate(1, sizeof(long));

}

void loop() {
}