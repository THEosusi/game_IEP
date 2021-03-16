#include <IRremote.h>
int red_light_pin = 9; //
int green_light_pin = 13;
int blue_light_pin = 10;
int LED_red = 2;
int LED_green = 3;
long randNumber;
char Answer[30];
char MyAnswer[30];
int level = 0;
int i = 0;
bool clear = false;
int stage = 0;
int edit = 0;
/*For IRremote*/
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(0));
    pinMode(red_light_pin, OUTPUT);
    pinMode(green_light_pin, OUTPUT);
    pinMode(blue_light_pin, OUTPUT);
    pinMode(LED_red, OUTPUT);
    pinMode(LED_green, OUTPUT);
    irrecv.enableIRIn(); // Start the receiver
}
void loop()
{
    /*RGB_color(255, 0, 0); // Red
    delay(1000);
    RGB_color(0, 255, 0); // Green
    delay(1000);
    RGB_color(0, 0, 255); // Blue
    delay(1000);
    RGB_color(0, 255, 255); // Cyan
    delay(1000);
    RGB_color(255, 255, 0); // Yellow
    delay(1000);*/
    if (level == 0)
    {
        randNumber = random(255);
        RGB_color(255, 0, 0);
        delay(1000);
        if (irrecv.decode(&results))
        {
            Serial.println(results.value, HEX);
            irrecv.resume(); // Receive the next valu

            if (results.value == 0xFDA05F)
            {
                level = 1;
            }
        }
        delay(500);
    }

    /*------------------- level 1 --------------------*/
    if (level == 1)
    {
        /* ******Stage 0 ****** */
        if (stage == 0)
        {
            RGB_color(0, 0, 0); // clear
            delay(1500);
            RGB_color(255, 0, 0); // Red
            delay(1000);
            RGB_color(0, 255, 0); // Green
            delay(1000);
            RGB_color(0, 0, 255); // Blue
            delay(1000);
            RGB_color(0, 0, 0); // 
            delay(1500);
            /*This command line for explain the player what color number is */
            for (i = 0; i <= 3; i++)
            { //how many select;
                randNumber = random(255);              
                if (randNumber % 3 == 0)
                {
                    RGB_color(255, 0, 0); // Red
                    delay(400);
                    RGB_color(0, 0, 0); // clear
                    delay(400);
                    Answer[i] = '1';
                }
                else if (randNumber % 3 == 1)
                {
                    RGB_color(0, 255, 0); // Green
                    delay(400);
                    RGB_color(0, 0, 0); // clear
                    delay(400);
                    Answer[i] = '2';
                }
                else if (randNumber % 3 == 2)
                {
                    RGB_color(0, 0, 255); // Blue
                    delay(400);
                    RGB_color(0, 0, 0); // clear
                    delay(400);
                    Answer[i] = '3';
                }
                Serial.println(Answer[i]); /*Real Answer*/
            }
        }
        stage = 1;

        /* ******Next Stage 1****** */
        if (stage == 1)
        {

            //it is finish;
            if (irrecv.decode(&results))
            {
                Serial.println(results.value, HEX);
                if (results.value == 0xFD08F7)
                {
                    MyAnswer[edit] = '1'; /*red*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                else if (results.value == 0xFD8877)
                {
                    MyAnswer[edit] = '2'; /*green*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                else if (results.value == 0xFD48B7)
                {
                    MyAnswer[edit] = '3'; /*blue*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                if (edit == 4)
                {
                    stage = 2;
                }
            }
        }
        /* ******Stage 2****** */
        if (stage == 2)
        {
            for (i = 0; i <= 3; i++)
            {

                if (Answer[i] != MyAnswer[i])
                {
                    clear = false;
                    break;
                }
                if (i == 3)
                {
                    clear = true;
                }
            }
            if (clear && stage == 2)
            {
                level = 2;
                stage = 0;
                edit = 0;
                Serial.print("right");
                digitalWrite(LED_green, HIGH); // turn the LED on 
                delay(500);                    
                digitalWrite(LED_green, LOW);  // turn the LED off 
                delay(500);                     // wait for a second
            }
            else if (clear == false && stage == 2)
            {
                level = 1;
                stage = 0;
                edit = 0;
                Serial.print("false");
                digitalWrite(LED_red, HIGH); // turn the LED on
                delay(500);                  
                digitalWrite(LED_red, LOW);  // turn the LED off
                delay(500);                  
            }
        }
    }

    /*------------------- level 2 --------------------*/
    if (level == 2)
    {
        /* ******Stage 0 ****** */
        if (stage == 0)
        {
            RGB_color(0, 0, 0); // clear
            delay(1500);
            RGB_color(255, 0, 0); // Red
            delay(800);
            RGB_color(0, 255, 0); // Green
            delay(800);
            RGB_color(0, 0, 255); // Blue
            delay(800);
            RGB_color(0, 0, 0); // clear
            delay(1500);
            /*This command line for explain the player what color number is */
            for (i = 0; i <= 4; i++)
            { //how many select;
                randNumber = random(255);              
                if (randNumber % 3 == 0)
                {
                    RGB_color(255, 0, 0); // Red
                    delay(350);
                    RGB_color(0, 0, 0); // clear
                    delay(350);
                    Answer[i] = '1';
                }
                else if (randNumber % 3 == 1)
                {
                    RGB_color(0, 255, 0); // Green
                    delay(350);
                    RGB_color(0, 0, 0); // clear
                    delay(350);
                    Answer[i] = '2';
                }
                else if (randNumber % 3 == 2)
                {
                    RGB_color(0, 0, 255); // Blue
                    delay(350);
                    RGB_color(0, 0, 0); // clear
                    delay(350);
                    Answer[i] = '3';
                }
                Serial.println(Answer[i]); /*Real Answer*/
            }
        }
        stage = 1;

        /* ******Next Stage 1****** */
        if (stage == 1)
        {

            //it is finish;
            if (irrecv.decode(&results))
            {
                Serial.println(results.value, HEX);
                if (results.value == 0xFD08F7)
                {
                    MyAnswer[edit] = '1'; /*red*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                else if (results.value == 0xFD8877)
                {
                    MyAnswer[edit] = '2'; /*green*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                else if (results.value == 0xFD48B7)
                {
                    MyAnswer[edit] = '3'; /*blue*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                if (edit == 5)
                {
                    stage = 2;
                }
            }
        }
        /* ******Stage 2****** */
        if (stage == 2)
        {
            for (i = 0; i <= 4; i++)
            {

                if (Answer[i] != MyAnswer[i])
                {
                    clear = false;
                    break;
                }
                if (i == 4)
                {
                    clear = true;
                }
            }
            if (clear && stage == 2)
            {
                level = 3;
                stage = 0;
                edit = 0;
                Serial.print("right");
                digitalWrite(LED_green, HIGH); // turn the LED on 
                delay(500);                    
                digitalWrite(LED_green, LOW);  // turn the LED off 
                delay(500);                     // wait for a second
            }
            else if (clear == false && stage == 2)
            {
                level = 2;
                stage = 0;
                edit = 0;
                Serial.print("false");
                digitalWrite(LED_red, HIGH); // turn the LED on
                delay(500);                  
                digitalWrite(LED_red, LOW);  // turn the LED off
                delay(500);                  
            }
        }
    }
    /*------------------- level 3 --------------------*/
    if (level == 3)
    {
        /* ******Stage 0 ****** */
        if (stage == 0)
        {
            RGB_color(0, 0, 0); // clear
            delay(1000);
            RGB_color(255, 0, 0); // Red
            delay(700);
            RGB_color(0, 255, 0); // Green
            delay(700);
            RGB_color(0, 0, 255); // Blue
            delay(700);
            RGB_color(255, 255, 0); // Yellow
            delay(700);
            RGB_color(0, 0, 0); // 
            delay(1000);
            /*This command line for explain the player what color number is */
            for (i = 0; i <= 5; i++)
            { //how many select;
                randNumber = random(255);              
                if (randNumber % 4 == 0)
                {
                    RGB_color(255, 0, 0); // Red
                    delay(300);
                    RGB_color(0, 0, 0); // clear
                    delay(300);
                    Answer[i] = '1';
                }
                else if (randNumber % 4 == 1)
                {
                    RGB_color(0, 255, 0); // Green
                    delay(300);
                    RGB_color(0, 0, 0); // clear
                    delay(300);
                    Answer[i] = '2';
                }
                else if (randNumber % 4 == 2)
                {
                    RGB_color(0, 0, 255); // Blue
                    delay(300);
                    RGB_color(0, 0, 0); // clear
                    delay(300);
                    Answer[i] = '3';
                }
                else if (randNumber % 4 == 3)
                {
                    RGB_color(255, 255, 0); // yellow
                    delay(300);
                    RGB_color(0, 0, 0); // clear
                    delay(300);
                    Answer[i] = '4';
                }
                Serial.println(Answer[i]); /*Real Answer*/
            }
        }
        stage = 1;

        /* ******Next Stage 1****** */
        if (stage == 1)
        {

            //it is finish;
            if (irrecv.decode(&results))
            {
                Serial.println(results.value, HEX);
                if (results.value == 0xFD08F7)
                {
                    MyAnswer[edit] = '1'; /*red*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                else if (results.value == 0xFD8877)
                {
                    MyAnswer[edit] = '2'; /*green*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                else if (results.value == 0xFD48B7)
                {
                    MyAnswer[edit] = '3'; /*blue*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
              else if (results.value == 0xFD28D7)
                {
                    MyAnswer[edit] = '4'; /*yellow*/
                    Serial.println(edit);
                    edit++;
                    irrecv.resume(); // Receive the next value
                }
                if (edit == 6)
                {
                    stage = 2;
                }
            }
        }
        /* ******Stage 2****** */
        if (stage == 2)
        {
            for (i = 0; i <= 5; i++)
            {

                if (Answer[i] != MyAnswer[i])
                {
                    clear = false;
                    break;
                }
                if (i == 5)
                {
                    clear = true;
                }
            }
            if (clear && stage == 2)
            {
                Serial.print("right");
                for(i = 0; i <= 5; i++)
                {
                digitalWrite(LED_green, HIGH); // turn the LED on 
                digitalWrite(LED_red, HIGH); // turn the LED on
                RGB_color(0, 0, 255); // Blue
                delay(250);                    
                digitalWrite(LED_green, LOW);  // turn the LED off 
                digitalWrite(LED_red, LOW);  // turn the LED off
                RGB_color(255, 255, 0); // yellow
                delay(250);                     // wait for a second
                }
                level = 0;
                stage = 0;
                edit = 0;

            }
            else if (clear == false && stage == 2)
            {
                level = 3;
                stage = 0;
                edit = 0;
                Serial.print("false");
                digitalWrite(LED_red, HIGH); // turn the LED on
                delay(500);                  
                digitalWrite(LED_red, LOW);  // turn the LED off
                delay(500);                  
            }
        }
    }    
}




/* ---------------------RGB Function------------------- */
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
    analogWrite(red_light_pin, red_light_value);
    analogWrite(green_light_pin, green_light_value);
    analogWrite(blue_light_pin, blue_light_value);
}