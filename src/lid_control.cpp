#include "lid_control.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <Servo.h>
extern SemaphoreHandle_t xMutex;
extern QueueHandle_t xQopen;
extern QueueHandle_t xQclose;

const byte Led = 26;
//servo motor initiation 
Servo lidServo;  
void open_task(void *pvParameters)
{  
pinMode (Led, OUTPUT);
    digitalWrite(Led,LOW);
   
   //servo motor config 
   lidServo.attach(10);

  long d ; 
  for(;;)
     {
     if( xQueueReceive(xQopen, &d, portMAX_DELAY)== pdTRUE)
     {
     if( xSemaphoreTake(xMutex, portMAX_DELAY)==pdTRUE)
     {
      digitalWrite(Led,HIGH);
      lidServo.write(180);
      vTaskDelay(100/ portTICK_PERIOD_MS);
      xSemaphoreGive(xMutex);
     }
      vTaskDelay(1000/ portTICK_PERIOD_MS);      
     }
     }
}

void close_task(void *pvParameters)
{  
  long d ; 
  for(;;)
     {
      if( xQueueReceive(xQclose, &d, portMAX_DELAY)==pdTRUE)
      {
      if (xSemaphoreTake(xMutex, portMAX_DELAY)==pdTRUE )
      {
      lidServo.write(0);
      vTaskDelay(100/ portTICK_PERIOD_MS);
      digitalWrite(Led,LOW);
      xSemaphoreGive(xMutex);
      }
      vTaskDelay(1000/ portTICK_PERIOD_MS);
      
      }
     }
}