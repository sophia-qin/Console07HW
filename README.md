# MechHWConsole07

Welcome to console 7 aka the best console! 

To Do:
There is a bug between the TCT game and Poolshot in the UI, but we believe that it could 
be a hardware issue. The Poolshot mechanism needs to be redesigned again as the ball lifter gets stuck frequently as well as the TCT. 
The TCT game lifts up sideways and the cup gets placed weird. Just run it on debug and you will see. 
You should also ask to get another ball stop installed because we are currently using one sensor to control 2 games. 
Additionally, the Friction cars need to be installed. We wrote code for it and most of it should work but needs to be worked on. 
When that is all done, you can begin working on two player mode unless there a new vision ;). 

When you upload code, upload MechHWConsole07_old because we reverted back to old code at Maker Faire and it didn't work so the "old" 
is actually the new, working code. Feel free to rename it so you know which code to upload. 

The Pachinko game is super sensitive. If the user hits the slider before the ball stops moving then it will break the game. 
The TCT game is also super sensitive. Be careful when you run it because the CAM shaft is fragile as well as the paddle. 
The servo motor was breaking a lot so be careful when reinstalling. Run the code without the silver brackets that attach to the paddle.
This way, you can see where to put the silver brackets and thus not break the servo. 

Console 07 
Games include: Pachinko, TCT Game, Variable Friction, and Poolshot
 
# Pachinko
####
User controls an electromagnet on the top to drop a ball into the score buckets. Every time the user the user fails a ball should be pumped up by calling the playAgain() method in the scene. User can also choose level of difficulty between easy, medium and hard, varying the number of changes you get to score. Successfully implemented the Pachinko UI with the Hardware, as well as solved the issue with the LED blinking and double scoring by using specific delayed. 

# TCT (Table Cloth Trick)
####
Game is the rendition of the Table Cloth Trick, which demonstrates the laws of Inertia - an object in motion remains in motion unless a force acts upon it. User is able to click the start button to begin the demonstration - the cup is place on the yellow arm, starts moving and then is dropped into the second cup on the machine with the applied force of the arm. 

# Poolshot
###
User controls the yellow pump at the bottom to shoot a metal ball into the score buckets. Within the UI, the user is able to control the angle and direction of the pump with releaseBall() method, as well as being shown the amount of lives lost/remaining in the form of heart images. Also displayed on the screen is a live score. 

# Variable Friction
###
Based off of laws of physics, separate metal cubes race against different materials in order to demonstrate the varying forces of friction. Game is in progress as of 2017.  
