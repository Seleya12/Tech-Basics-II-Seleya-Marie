# Process Documentation – Two-Player Arduino Reaction Game

## 1. Project Idea
Our project is a two-player reaction and memory game built with an Arduino Uno.  
The goal of the project was to create a simple but competitive physical game that focuses on
reaction time, pattern recognition, and user interaction.  
Two players compete against each other using individual controllers with buttons and LEDs,
while the system measures reaction speed and determines a winner visually.
We used this as a refrence: https://www.instructables.com/Reaction-Time-Game-With-Arduino-Uno/?utm

---

## 2. Hardware Setup
The hardware setup consists of an Arduino Uno connected to three separate breadboards, one
for each player, and one to start the game.

Each player controller includes:
- Three buttons
- Three LEDs (green, yellow, red)
- 220 Ω resistors for each LED

### Pin Assignments

**Player 1**
- Button 1 (Green): Pin 3  
- Button 2 (Yellow): Pin 5  
- Button 3 (Red): Pin 7  
- Green LED: Pin 8  
- Yellow LED: Pin 11  
- Red LED: Pin 12  

**Player 2**
- Button 1 (Green): Pin A5  
- Button 2 (Yellow): Pin A4  
- Button 3 (Red): Pin A3  
- Green LED: Pin A2  
- Yellow LED: Pin A1  
- Red LED: Pin A0  

**Shared Components**
- Start Button: Pin 13   
- All components share a common ground connection with the Arduino.

---

## 3. Software / Code Structure
The Arduino code controls three different game modes.  
In Level 1, players react as quickly as possible to a randomly activated LED by pressing the
corresponding button.  
Levels 2 and 3 introduce a memory component, where players must correctly repeat an LED
sequence of increasing length.  
The start button is used to select the desired level by pressing it multiple times.  
Reaction times are measured, and the winner is visually indicated using LEDs.

---

## 4. Development Process
The project was developed iteratively, starting with a simplified prototype.
For the initial prototype and presentation, we first recreated a provided example to familiarize ourselves with the hardware setup and programming environment. The example implemented a simple reaction game (Game 1). Rebuilding this version allowed us to understand the basic interaction logic and ensure that the core components worked before developing our own extended version of the project.
![IMG_5579](https://github.com/user-attachments/assets/32db5b87-a3a7-46bb-9ae8-a1b09379cda8)

After successfully presenting and testing the prototype, the project was further developed. At a later stage, Seleya extended the hardware setup by adding a third button and LED per controller and replacing the longer cables with shorter ones to make the wiring more organized and easier to manage.
At that time, Marie was already in Hong Kong, which made the collaboration slightly more challenging. Seleya documented and shared the pin configuration and hardware setup so that Marie could adapt the code accordingly. The code was then tested and adjusted multiple times, requiring several iterations and exchanges until the final version of the game functioned reliably.
![IMG_6131](https://github.com/user-attachments/assets/1123c229-b12d-40a9-868a-aa17417ab544)


---

## 5. Challenges & Solutions
During the development of the project, several technical and practical challenges occurred. In addition, collaboration became more complex because Marie was already in Hong Kong during part of the development phase, which meant that communication and testing had to take place remotely.

One issue concerned the LEDs, which initially did not behave as expected. This was caused by incorrect LED polarity during wiring. After identifying the problem, we corrected the orientation of the LEDs and verified the connections using a simple LED test program.

Another challenge was identifying a suitable power source for the system. While alternative power options were considered, the project is currently powered via a USB connection to a computer. This solution was chosen because the powerbank did not work reliably.

Additionally, space limitations on the breadboards made the hardware setup more difficult than expected. The available space was limited, which led to cable congestion during the early stages of the build. To solve this issue, we reorganized the layout and replaced some cables with shorter jumper wires. This resulted in a cleaner setup and reduced the risk of loose or incorrect connections.

---

## 6. Final Result
The final result is a fully functional two-player Arduino reaction and memory game with
multiple difficulty levels.

The system reliably detects button inputs, activates LEDs,  and
determines a winner between the two players. The different levels add variety to the
gameplay, starting with a simple reaction challenge and gradually introducing memory-based
sequences that make the game more challenging.

Overall, during the project we mainly focused on two core elements: LEDs and buttons. Rather
than adding many different components, we tried to specialize in these two and really
understand how they work. 

A demo video shows two players competing against each other and demonstrates the full gameplay process, including level selection, LED signals, and the final result of each round.
