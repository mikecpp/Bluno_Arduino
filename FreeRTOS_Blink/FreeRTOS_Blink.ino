#include <Arduino_FreeRTOS.h>

void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

void setup() 
{ 
    Serial.begin(115200);
  
    while (!Serial) {
    }

    xTaskCreate(
        TaskBlink
        ,  (const portCHAR *)"Blink"   // A name just for humans
        ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
        ,  NULL
        ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        ,  NULL );

    xTaskCreate(
        TaskAnalogRead
        ,  (const portCHAR *) "AnalogRead"
        ,  128  // Stack size
        ,  NULL
        ,  1  // Priority
        ,  NULL );
}

void loop()
{

}

void TaskBlink(void *pvParameters) 
{
    (void) pvParameters;

     pinMode(LED_BUILTIN, OUTPUT);

    while(1) {
        digitalWrite(LED_BUILTIN, HIGH);   
        vTaskDelay( 1000 / portTICK_PERIOD_MS ); 
        digitalWrite(LED_BUILTIN, LOW);    
        vTaskDelay( 1000 / portTICK_PERIOD_MS ); 
    }
}

void TaskAnalogRead(void *pvParameters)  
{
    (void) pvParameters;
  
    while(1) {
        int sensorValue = analogRead(A0);
        Serial.println(sensorValue);
        vTaskDelay(1);  
    }
}

