Introduction to the Project

In designing the project, we chose to engage the user with two different tests, each of which would enable a distinct measurement of cognitive processing. We equipped users with the option to move between the games either via the serial monitor, or otherwise via the buttons utilized in the game. 


——————————

Game 1: Lightspeed

The first test, called “Lightspeed”, operates by first selecting a random LED among the 5 present. This LED flashes briefly to signal to the user that it has been chosen, then the Knight Rider sequence begins. We have equipped the user with 5 differently-colored buttons, each of which aligns precisely with its corresponding LED.

The aim of Lightspeed is to press the correct corresponding button at precisely the moment in which Knight Rider passes over the chosen LED. If Knight Rider has hit upon the chosen LED, but the user presses the wrong button, then a short musical sequence is emitted from the piezo to signal the failed attempt, and the Knight Rider continues. If the user presses the correct button, but the Knight Rider has hit upon one of the other 4 LEDs, then the user has missed, and the sequence continues.

But when the correct button aligns with the Knight Rider’s landing upon the correct LED, victory can be claimed! The chosen LED will flash to indicate success, and delightful playing of the Tetris theme song will put the user in a good mood following their triumph. 

Throughout the course of Lightspeed, any mistakes made by the user will be tracked, and these mistakes will be reflected in the score displayed by the LED lights showcased at the end. The number of incorrect attempts will be subtracted from 5, the total amount of LEDs, to yield the user’s acquired level. If at any point during the game the user accumulates 5 mistakes, then the game will end prematurely. Skilled players who win the game on their first attempt (with no mistakes) will be rewarded not only with 5 shining LED lights, but also with a celebratory round of the Tetris theme song!

With Lightspeed completed, the user will then need to move to DJ Memory. If, at the start of the program, they had elected to work via the serial monitor, then the serial monitor will prompt them to provide a written indication of their desire to continue to the next game. If instead they had elected to work via the buttons, then the program will wait attentively for any of the 5 colorful buttons to be pressed, at which point DJ Memory will begin.


——————————

Game 2: DJ Memory

Then comes the second test, “DJ Memory”. Here again, we see the LEDs providing feedback, but this time their activity links to 5 photoresistors. Each of these 5 photoresistors [and their LEDs] correspond to a musical note. Initiating the game with a randomly-selected note, the piezo invites the user to copy the sequence. This is because, when this first note is played, the LED associated with that note lights up. And by waving their hand over the photoresistor aligned with that particular LED, the user can delightedly discover that they are playing that same note back!

A correct mimicry of the current sequence is rewarded with the same triumphant Tetris song we saw during the Lightspeed game, but now the stakes are higher; each time a user accurately replicates the game’s chosen sequence, the sequence gets longer, and there are more notes of which to keep track.

Do you have what it takes to work your way up to a 5-note sequence? Be advised: even those boasting the strongest memory may slip up! Mistakes are met with the same short musical sequence seen in Lightspeed, but worry not, you can always restart the games and try again. Whether you are looking to sharpen your focus or perhaps kickstart your career as an Arduino DJ, our game will get you working!

Once the user has finished testing their memory recall as a DJ, the 5 LED lights will display their score in accordance with the level that they have reached. Given that the user will have earned a point for each sequence that they succeed to mimic, our LEDs will reflect the longest sequence that the user has been able to recall. With the longest sequence consisting of 5 notes, truly skilled players will, as is the case in Lightspeed, be met not just with the glow of 5 cheerful LEDs, but also with a fun round of piezo’s finest and most triumphant Tetris music!


——————————

With DJ Memory completed, and the full gamut of activities having come to a close, the user is then given the choice to restart all of the games anew. If, at the start of the program, they had elected to work via the serial monitor, then the serial monitor will prompt them to provide a written indication of their desire to begin the games afresh. If instead they had elected to work via the buttons, then the program will wait attentively for any of the 5 colorful buttons to be pressed, at which point the program will reset all settings, loop back to the start, and delve into Lightspeed.


————————————————————

To recreate this project, the following tools and supplies are needed:


- 1 Arduino circuit board

- 1 large breadboard

- 5 larger (preferably colorful) buttons

- 5 LED lights

- 5 photoresistors

- 1 piezo

- Several wires… we ended up using:
  - 39 regular wires
  - 20 long wires

- Several resistors… we ended up using:
  - 10 brown-black-orange (10000 ohms) resistors
  - 5 green-blue-brown (560 ohms) resistors

- Soldering iron, solder metal alloy, etc.

- Sufficiently-sized cardboard box

- Sharp object (scissors, exacto knife) that slices cardboard

- Decorations of choice


————————————————————

*** Credit for all songs utilized in code (thank you, Rob!): 
          [robsoncouto](https://github.com/robsoncouto/arduino-songs) 


————————————————————

Explore further [project details here](https://cio727131088.wordpress.com/2021/12/12/group-14-reaction-time/)

