# How to utilize this code for Tree-climbing Robot

## Project Summary
Our final term project entails the design of a tree-climbing robot which is able to ascend a tree, deploy a sensor in its canopy, and finally return home safely. There will be a total of 3 varied scenarios that our robot has to complete, all of which test the limits and capabilities of our robot design. Our solution aims to focus on both the mechatronics and electronics that govern the design of our robot and how in conjunction with each other allow for the successful utilisation of our tree-climbing robot.

## Mechatronics Design
Our robotic system is comprised of two grippers separated by a body which consists of three racks with a pinion respectively attached to the inside of the bottom gripper's body. Each gripper has 4 pairs of fingers with jagged teeth lining the inside face of it. This will later be lined with rubber and sandpaper to enable a high frictional contact between the gripper and tree ensuring its stability when attached to the tree. The top gripper has a gear head connected to the base of it allowing for rotation - opening and closing of the gripper. The gripper case is where the motor aiding in the rotation of the gripper will be placed. 

## Electronics Design
The electronics components we used consisted of an Arduino R3 board as a microcontroller with an L298P motor driver equipped. The grippers and backbone are actuated by two servo motors and three DC motors respectively. Two ultrasonic sensors are used for the distance measurement and obstacle detection on either side of the robot. The ‘obstacle’ here refers to the branches and rooftop in real cases. Our robot program is written in Arduino IDE.

![image](https://github.com/hx-cheng/tree-climbing-robot/assets/171290255/139030a2-35eb-4bd2-a698-4698e838b0cb)

The pins are assigned as shown in the figure above.
