#Maze Solving Autonomous Robot
                              
This report is all about autonomous robots that can solve simple problems like line following , maze solving etc. I am using 5 ir sensor array which are pid tuned to follow line. Late algorithms like left hand rule(for non looping maze) and flood fill or Dijkstra’s (for looping) are being applied for maze solving.
Materials used:-
1.)5 ir sensors (or array)\n
2.)2 motors\n
3.)L298n motor driver
4.)Optical encoders
Line following:-
5 ir sensors are used for line following in which the center sensor tracks the black line.there are 2 sensors both to the right and the left of the sensors that calculates the error which is further used for pid tuning.
Link of video:-
https://drive.google.com/open?id=13HVMbEWZWij5F5munRUTgB-mRIS1p54w

Non-looping maze solver:-
The bot is allowed to traverse the maze using left hand rule. The whole path is recorded in an array and then the shortest path is found out by optimizing the array of path by substitutions like:-
LBR=B
RBL=B
SBS=B
LBS=R
SBL=R
LBL=S
Working video:-
https://drive.google.com/open?id=1qiwLSot62w9NewPzBtvALf4EIzPNIMNy

Looping maze:-
Firstly the robot traverse the whole maze and map its coordinates with the help of encoders. Later I am trying to apply flood fill algorithm to solve the maze.
Presently, I am trying to get the bot to properly map the maze so that the shortest path could be found accurately.  
