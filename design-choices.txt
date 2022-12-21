Design Choices

While creating the project, we placed an emphasis on usability by repeatedly checking to confirm that our games were effective, motivating, and fulfilling.


——————————

Interface & Hardware

Our commitment to usability was in part what led us to opt for two different forms of input (buttons and photoresistors), as we found that relying solely on buttons, for example, could become tiring, thereby reducing a user’s desire to continue the game. Elaborating upon this, we opted to have 5 of each type of transducer (LEDs, buttons, photoresistors) so that they could precisely align with, and therefore correspond to, each other. This in turn made it easier for the user to develop an intuitive understanding of where the game’s elements were in relation to one another, thus reducing the risk of confusion around how to interact with the game. 


——————————

Interactive Design Principles

We also employed the use of different signifiers so as to encourage the user’s rapid learning of the game’s flow. By playing the same celebratory Tetris theme song sequence each time a user performs well, and by flashing / lighting up the correct LED each time the user accurately hits it, the game provides vital feedback to communicate to the user that their behavior is appropriate. Conversely, there also exists a brief [and vaguely unpleasant] musical sequence that is played whenever a user makes a mistake, prompting them to realize that they have participated unsuccessfully. Each of these forms of feedback are delivered immediately and consistently, which enables the user to piece together the pattern without much external assistance.

We then took design constraints into consideration by writing the code in such a way that the inputs not presently in use physically could not be read. This meant that the photoresistors were nonfunctional during the Lightspeed game, while the buttons were nonfunctional during the DJ Memory game. Through this method, the user could very quickly recognize the items with which they were meant to interact.

Further design constraints included the choice to have users proceed to the next game (or otherwise begin all games anew) by pressing any of the 5 buttons. But this was not always our intention. Initially, we had planned to hold the black button responsible for processing all movement between games, as we felt that black was a neutral and obvious color. Yet we realized that if only 1 button were responsive, then we would need to effectively communicate this fact to the user, which would result in a greater chance of error and confusion. When all 5 of the differently-colored buttons are serviceable, however, any barriers to comprehension dissolve, as it becomes intuitive, in moments of uncertainty, to simply press whichever button is in front, thus granting the user the allowance of pressing whichever one they please. Here it is important to note that this particular design principle would only apply to users who had elected to play the game interactively, that is to say, without the serial monitor. Players who had selected the serial monitor could enjoy a more direct written approach.
