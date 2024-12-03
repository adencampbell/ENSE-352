

**Simon Game: A User Guide**  
**ENSE 352 Lab \- Final Project Report**  
**Fall 2024**  
**Name: Aden Campbell**  
**Student ID\#: 200482525**

### **Simon Game:** 

### **A Simple Short-Term Memory Testing Game**

#### **Introduction:**

Welcome to Simon, a short-term memory testing game designed to challenge your recall abilities. The game operates on a STM F103RB microcontroller with 4 buttons, 4 Red LEDs (corresponding to each other based on position), and a USB-A to micro USB power cable. The goal is to remember and repeat increasingly complex sequences of flashing lights. Let's dive into how to get started and the game mechanics\!\!\!

#### **Getting Started:**

1. **Powering the Game:**

   * Connect the STM F103RB microcontroller to a USB power source using the USB-A to Micro USB cable.  
2. **Reset the Microcontroller:**

   * Once the microcontroller is powered, press the **Black “Reset” button** on the microcontroller to start the game.  
3. **You’re Ready to Play\!**

   * After pressing the reset button, the game will be in a ready state, and you can begin by following the next sequence.

#### **Welcome Sequence:**

The game begins with a **"Knight Rider" light sequence**, where the 4 red LEDs light up in the following pattern:

* The lights will start from the left-most LED and move right to the right-most LED, then reverse direction to the left-most LED again.  
* This sequence will repeat until you press **any one of the 4 buttons**. Once a button is pressed, the game will start\!

#### **Round 1:**

* The game will flash one random LED for a short period.  
* You will have **5 seconds** to press the corresponding button for the flashed LED.  
* If you press the correct button within the time limit, you’ll proceed to Round 2\.

#### **Round 2-10:**

* After each round is successfully completed, a new random LED will be added to the sequence.  
* For example, in Round 2, the first LED from Round 1 will repeat, and the second one will be randomly chosen.  
* Each time a light is flashed, you have **5 seconds** to press the corresponding button. The timer will reset after each successful button press, giving you more time to complete the sequence.  
* Continue repeating the growing sequence until you reach Round 10\.

#### **Winning the Game:**

* If you successfully complete Round 10 by repeating a 10-light sequence correctly, the game will indicate a win:  
  * All 4 LEDs will rapidly blink at the same time 4 times.  
  * The game will then display the 4-bit binary pattern of the round you achieved. For example, completing round 10 will display 0101 in binary.  
  * **Press any button to restart the game.**

#### **Losing the Game:**

* If you fail to repeat the correct sequence or if you do not press any button within the 5-second window at any point, you lose:  
  * The lights will flash in a failure sequence 4 times:  
    * First, the outer two LEDs will flash, then 3 delays will occur.  
    * After that, the inner two LEDs will flash.  
  * The game will display the 4-bit binary pattern for the round you reached. For example, if you lost in Round 7, it will show 1110 in binary.  
  * **Press any button to restart the game.**

Good luck, and enjoy playing Simon\!

