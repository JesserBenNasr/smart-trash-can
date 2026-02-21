#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "distance_task.h"
#include <queue.h>


const byte TRIGGER_PIN = 22; // Broche TRIGGER
const byte ECHO_PIN = 24;    // Broche ECHO

// External queues from main
extern QueueHandle_t xQopen;
extern QueueHandle_t xQclose;

void distance_task(void *pvParameters)
{
  //hc 04 initiation 
    pinMode(TRIGGER_PIN, OUTPUT);
    digitalWrite(TRIGGER_PIN, LOW); 
    pinMode(ECHO_PIN, INPUT);
    for(;;)
     {
       digitalWrite(TRIGGER_PIN, LOW);
       delayMicroseconds(2);
       digitalWrite(TRIGGER_PIN, HIGH);
       delayMicroseconds(10);
       digitalWrite(TRIGGER_PIN, LOW);
       // Read the echo time
        long duration = pulseIn(ECHO_PIN, HIGH);
         
       // Calculate the distance in cm
        long distance = duration * 0.034 / 2;
         Serial.println(distance);
        if ( distance <30 ) 
        {
          Serial.println("open");
          xQueueSendToBack(xQopen, &distance, portMAX_DELAY);  
        }
        else 
        {
          Serial.println("close");
          xQueueSendToBack(xQclose, &distance, portMAX_DELAY);  
        }
     
      vTaskDelay(1500/ portTICK_PERIOD_MS);
     }
}