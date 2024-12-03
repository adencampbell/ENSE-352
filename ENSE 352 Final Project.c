//Name: Aden Campbell.
//Student ID: 200482525.
//ENSE 352 Fall 2024 Final Project.

//Import packages as needed.
#include <stm32f10x.h>
#include <stdint.h>
//I enjoy boolean logic from c++ so I used a header
#include <stdbool.h>
#include <stdlib.h>
#define NUMBER_OF_LEDS 4

void setupOutputPins();
void setupInputPins();
void enablePortClocks();
void startup();
void delay(uint32_t);
void turnOnLED1();
void turnOffLED1();
void turnOnLED2();
void turnOffLED2();
void turnOnLED3();
void turnOffLED3();
void turnOnLED4();
void turnOffLED4();
int isButton1Pressed();
int isButton2Pressed();
int isButton3Pressed();
int isButton4Pressed();
void loss(int round);
void winner();
void game();
void indicateRound(int round);
int randomNumberTo4();
//dleay length
uint32_t length = 0xFFFFF;


int main(){
	//standard startup procedures
	enablePortClocks();
	setupOutputPins();
	setupInputPins();
	//this begins the game, acts essentially as a state machine after
	startup();
	return 0;	
}

void enablePortClocks(){
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN);
}  

void setupOutputPins(){
	GPIOA->CRL |= GPIO_CRL_MODE5;
	GPIOA->CRL |= GPIO_CRL_MODE0;
	GPIOA->CRL |= GPIO_CRL_MODE4;
	GPIOA->CRL |= GPIO_CRL_MODE1;
	GPIOB->CRL |= GPIO_CRL_MODE0;
	
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	GPIOA->CRL &= ~GPIO_CRL_CNF4;
	GPIOA->CRL &= ~GPIO_CRL_CNF1;
	GPIOB->CRL &= ~GPIO_CRL_CNF0;
}

void setupInputPins(){
	GPIOC->CRH &= ~GPIO_CRH_MODE13;
	GPIOB->CRH &= ~GPIO_CRH_MODE8;
	GPIOB->CRH &= ~GPIO_CRH_MODE9;
	GPIOB->CRL &= ~GPIO_CRL_MODE4;
	GPIOB->CRL &= ~GPIO_CRL_MODE6;
	GPIOC->CRH &= ~GPIO_CRH_CNF13_0;
	GPIOC->CRH |= GPIO_CRH_CNF13_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF8_0;
	GPIOB->CRH |= GPIO_CRH_CNF8_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF9_0;
	GPIOB->CRH |= GPIO_CRH_CNF9_1;
	GPIOB->CRL &= ~GPIO_CRL_CNF4_0;
	GPIOB->CRL |= GPIO_CRL_CNF4_1;
	GPIOB->CRL &= ~GPIO_CRL_CNF6_0;
	GPIOB->CRL |= GPIO_CRL_CNF6_1;
	GPIOC->ODR |= GPIO_ODR_ODR13;
	GPIOB->ODR |= GPIO_ODR_ODR4;
	GPIOB->ODR |= GPIO_ODR_ODR6;
	GPIOB->ODR |= GPIO_ODR_ODR8;
	GPIOB->ODR |= GPIO_ODR_ODR9;
}

//used trevors github code to generate random sequences/
int randomNumberTo4(){
    int limit;
    int r;
    limit = RAND_MAX - (RAND_MAX % NUMBER_OF_LEDS);
    while((r = rand()) >= limit);
    return r % NUMBER_OF_LEDS;
}

//check if any of the four buttons return true, if so return true.
//delay is also added in this function utilizing for loop
bool anyButtonsPressed()
{
	bool buttonPressed = false;
	for(int i = 150000; i > 0; i--){
		if (isButton1Pressed()){
			buttonPressed = true;
		} 
		else if (isButton2Pressed()){
			buttonPressed = true;
		} 
		else if (isButton3Pressed()){
			buttonPressed = true;
		} 
		else if (isButton4Pressed()) {
			buttonPressed = true;
		}
	}
	return buttonPressed;
}

//this does the starting light sequence from right to left, while a button is not pressed. I check a lot, and use checking as my delays.
void startup() 
{
    bool buttonPressed = false;
    while (!buttonPressed) {
        turnOnLED1();
				buttonPressed = anyButtonsPressed();
        turnOffLED1();
			
        turnOnLED2();
				buttonPressed = anyButtonsPressed();
        turnOffLED2();
			
        turnOnLED3();
				buttonPressed = anyButtonsPressed();
        turnOffLED3();
			
        turnOnLED4();
        buttonPressed = anyButtonsPressed();
        turnOffLED4();
        
        turnOnLED3();
				buttonPressed = anyButtonsPressed();
        turnOffLED3();
			
        turnOnLED2();
				buttonPressed = anyButtonsPressed();
        turnOffLED2();
    }
		//once a button is pressed go to the game
    game();
}

//being game
void game(){
		//start round at 0
    int round = 0;
		//lost is essentially guaranteed false, unless otherwise sepcified by code later.
    bool lost = false;
		//sequence of lights will be an array of length 10, each element will be generated randonly in the below for loop.
    int lightNums[10];
		for (int i = 0; i < 10; i++){
			lightNums[i] = randomNumberTo4();
		}
		//while loop while lost is false
    while (!lost){
				delay(length);
				delay(length);
				//for loop with amount of iterations corresponding to the round you're on
        for (int i = 0; i <= round; i++){
						delay(length);
						delay(length);
						//check which light number is in the sequence at that element, display the led accordingly
            if (lightNums[i] == 0) {
                turnOnLED1();
                delay(length);
								delay(length);
                turnOffLED1();
            } 
						else if (lightNums[i] == 1){
                turnOnLED2();
                delay(length);
								delay(length);
                turnOffLED2();
            }
						else if (lightNums[i] == 2){
                turnOnLED3();
                delay(length);
								delay(length);
                turnOffLED3();
            }
						else if (lightNums[i] == 3){
                turnOnLED4();
                delay(length);
								delay(length);
                turnOffLED4();
            }
        }
				//same loop, this time not for turning on LED's, but instead for checking button sequence
        for (int i = 0; i <= round; i++){
						//wait for a button press
            bool buttonPressed = false; 
						delay(length);
						int time = 0;
            while (!buttonPressed){
								//incrementing time as the 5 second timer
								time++;
								//find out whic button is pressed. Then check that that button corresponds to the correct led in the seqeunce, then exit the loop.
                if (isButton1Pressed()){
                    turnOnLED1();
                    delay(length);
                    turnOffLED1();
                    if (lightNums[i] != 0){
                        lost = true; 
                    }
                    buttonPressed = true;
								time++;
                } 
								else if (isButton2Pressed()){
                    turnOnLED2();
                    delay(length);
                    turnOffLED2();
                    if (lightNums[i] != 1){
                        lost = true;
                    }
                    buttonPressed = true;
								time++;
                } 
								else if (isButton3Pressed()){
                    turnOnLED3();
                    delay(length);
                    turnOffLED3();
                    if (lightNums[i] != 2){
                        lost = true;
                    }
                    buttonPressed = true;
								time++;
                }
								else if (isButton4Pressed()){
                    turnOnLED4();
                    delay(length);
                    turnOffLED4();
                    if (lightNums[i] != 3){
                        lost = true; 
                    }
                    buttonPressed = true;
                }
								time++;
								//experimentally found this to be roughly 5 seconds
								//user loses if they time out.
								if (time > 4000000){
									lost = true;
									buttonPressed = true;
									loss(round+1);
								}
            }
        }
				//if the sequence was correct
        if (lost == false){
					//if round is 9, they won, send to winner function
					if (round == 9){
						winner();
					}
					//otherwise they havent won yet, but advance a round
					round++;
        }
				//if the sequence was not coorect, they lost
				else{
					loss(round+1);
				}
    }
}

//if the user loses.
void loss(int round){
	//this is the pattern i chose to  edisplayed 4 times.
	for (int i = 0; i < 4; i++){
		turnOnLED1();
		turnOnLED4();
		delay(length);
		delay(length);
		delay(length);
		turnOnLED2();
		turnOnLED3();
		turnOffLED1();
		turnOffLED4();
		delay(length);
		turnOnLED1();
		turnOnLED4();
		turnOffLED2();
		turnOffLED3();
		delay(length);
		delay(length);
		delay(length);
		turnOffLED1();
		turnOffLED4();
		
	}
	//send to indicate binary rounds function, pass hich round they were in
	indicateRound(round);	
}

void indicateRound(int round){
	//check if bit 4 is set
	if ((round & 0x8) == 0x8){
		turnOnLED4();
	}
	//check if bit 3 is set
	if ((round & 0x4) == 0x4){
		turnOnLED3();
	}
	//check if bit 2 is set
	if ((round & 0x2) == 0x2){
		turnOnLED2();
	}
	//check if bit 1 is set
	if ((round & 0x1) == 0x1){
		turnOnLED1();
	}
	bool buttonPressed = false;
	//once the user presses a button, undisplay the binary pattern, go back to startup
  while (!buttonPressed){
		if (isButton1Pressed()){
          buttonPressed = true;
    } 
		else if (isButton2Pressed()){
          buttonPressed = true;
    }
		else if (isButton3Pressed()){
          buttonPressed = true;
    }
		else if (isButton4Pressed()){
					buttonPressed = true;
    }
	}
	//same procedure but for turning off the binary pattern.
	if ((round & 0x8) == 0x8){
		turnOffLED4();
	}
	if ((round & 0x4) == 0x4){
		turnOffLED3();
	}
	if ((round & 0x2) == 0x2){
		turnOffLED2();
	}
	if ((round & 0x1) == 0x1){
		turnOffLED1();
	}
	delay(length);
	delay(length);
	startup();
}

//if the user has won the game
void winner(){
	//the winner pattern of lights
	for (int i = 0; i < 4; i++){
		turnOnLED1();
		turnOnLED2();
		turnOnLED3();
		turnOnLED4();
		delay(length);
		turnOffLED1();
		turnOffLED2();
		turnOffLED3();
		turnOffLED4 ();
		delay(length);
	}
	//indicate round 10 in 4 bit binary pattern, so 1010
	indicateRound(10);
}

//delay function
void delay(uint32_t len)
{
	while(len > 0)
	{
		len -= 1;
	}
}

//all these below functions simplify turning off/on LED,s and checking buttons states instead of manually writing out weird GPIO syntax repeatedly.
void turnOnLED1()
{
    GPIOA->ODR |= (1 << 0); 
}

void turnOffLED1()
{
    GPIOA->ODR &= ~(1 << 0); 
}

void turnOnLED2()
{
    GPIOA->ODR |= (1 << 1); 
}

void turnOffLED2()
{
    GPIOA->ODR &= ~(1 << 1); 
}

void turnOnLED3()
{
    GPIOA->ODR |= (1 << 4);  
}

void turnOffLED3()
{
    GPIOA->ODR &= ~(1 << 4); 
}

void turnOnLED4()
{
    GPIOB->ODR |= (1 << 0);
}

void turnOffLED4()
{
    GPIOB->ODR &= ~(1 << 0); 
}

int isButton1Pressed()
{
    return (GPIOB->IDR & GPIO_IDR_IDR4) == 0;  
}

int isButton2Pressed()
{
    return (GPIOB->IDR & GPIO_IDR_IDR6) == 0; 
}

int isButton3Pressed()
{
    return (GPIOB->IDR & GPIO_IDR_IDR8) == 0;  
}

int isButton4Pressed()
{
    return (GPIOB->IDR & GPIO_IDR_IDR9) == 0;
}



