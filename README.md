# Rat-in-a-Maze-Puzzle
Proteus Project using Keil uVision4

### Resources Required :
1) LPC2148 Microcontroller 
2) Switch
3) Simple DC motor
4) Driver
5) Keypad
6) LCD 
7) Buzzer

### Softwares Used : 
1) Proteus
2) Keil uVision4
3) Tinker cad

# Abstract: 
Since lockdown, all of us have experienced boredom. So, we thought of making a puzzle by electronic means which will entertain us and help us to explore knowledge as well. This made us focus on various already existing algorithms. Out of these, we have implemented “Rat in a Maze puzzle”. In this algorithm, a rat has to travel through a 3x3 grid where pieces of paneer are placed randomly. A rat has to travel in such a way that it could eat a maximum amount of paneer by following the shortest path coming out of the grid. This puzzle seems to be quite easy, unless some tricky rules are imposed.                                            
Rule 1 – A rat can traverse the 3x3 grid only in horizontal and vertical directions. 
Rule 2 – It cannot go back to the block which is visited once. Simply, retracing the path is not allowed.
Rule 3 – The User has to press 0 to end the game.
Now, it seems to be interesting!
Let’s have a brief demonstration.
A 3x3 grid split into nine blocks of equal size can be considered as a maze. Let’s just assume that a rat is going to travel through the entire maze. A Switch and a DC Motor is placed in each block. Switches in few blocks are closed which indicates the presence of a piece of paneer in those particular blocks, which can be altered anytime. As soon as the user enters the path or block number to travel through the keypad, the status of switch in that block is checked. If the switch is closed, the DC motor starts rotating and the buzzer beeps which indicates that the rat has consumed the piece of paneer in that block. After pressing ‘0’ through the keypad, the game will end, then the path followed by the rat and number of pieces of paneer collected will be displayed on the LCD screen.
To understand the implementation of algorithm, let’s consider a case.
Suppose, pieces of paneer have been placed in the first, fifth and sixth block. Two players are playing the game. Player 1 enters the path 1-2-3-6-5-4-7-8-9 and collects 3 pieces of paneer. Player 2 enters the path 1-2-5-6-9 and also collects 3 pieces of paneer. In this case, both the players have collected the same amount of paneer but player 2 will win the game as the path followed in this case is shorter as compared to the path followed by player 1.   

## Circuit Diagram :
![Circuit Diagram](https://user-images.githubusercontent.com/59772587/121689377-29583b80-cae2-11eb-8761-f6254e4016ec.jpg)

## Output :

![Steps](https://user-images.githubusercontent.com/59772587/121692808-19daf180-cae6-11eb-9c3f-2dd612fb1606.jpg)
