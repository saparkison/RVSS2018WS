#!usr/bin/python
import time
import math
import cv2
import numpy as np
#import sys
import pygame

import PiBot as PB


pb = PB.PiBot('10.0.0.20')
global_tick = pb.getMotorTicks()
image = pb.getImageFromCamera()
cv2.imshow("current_view" , image)
cv2.waitKey(500)
print "left and right tickes " , global_tick
print image.shape
pb.setMotorSpeeds(0,0)

filename = "image0.png"
cv2.imwrite(filename,image )


global_odometry = np.array([[0,0]])
global_imagecount = 1

# Open a file
f1 = open('data_log/data_out.txt','w+')



pygame.init()
pygame.display.set_mode((10,10))

try:
    print("TELEOP")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                print event.type
                if event.key == pygame.K_UP:
                    print("FORWARD")
                    pb.setMotorSpeeds(30,-1*30)
                if event.key == pygame.K_DOWN:
                    print("BACKWARD")
                    pb.setMotorSpeeds(-1*30,30)
                if event.key == pygame.K_LEFT:
                    print "LEFT"
                    pb.setMotorSpeeds(-1*30,-1*30)
                if event.key == pygame.K_RIGHT:
                    print "RIGHT"
                    pb.setMotorSpeeds(30,30)

            if event.type == pygame.KEYUP:
                print "Done"
                pb.setMotorSpeeds(0,0)

        # Determine Ticks Moved
        tick_count = pb.getMotorTicks()
        tick_diff = [0, 0]
        tick_diff[0] = 1*(global_tick[0] - tick_count[0])
        tick_diff[1] = 1*(global_tick[1] - tick_count[1])

        # Change Ticks moved to mm moved
        movement = [0, 0]
        movement[0] = tick_diff[0]*0.5607
        movement[1] = tick_diff[1]*0.6065

        # Determine Distance
        distance = (movement[0] + movement[1])/2
        between_wheels = 145 # mm
        theta = (movement[0] - movement[1])/between_wheels * 180/3.14159

        if (abs(distance) > 5) or (abs(theta) > 15):

            global_tick = tick_count
            filename = "%04d.png" % global_imagecount

            new_array = [[distance, theta]]
            global_odometry = np.append(global_odometry, new_array,axis=0)

            sWrite = filename + " " + "%f" % distance + " "+ "%f" % theta +"\n"
            f1.write(sWrite)
            # Get Image and Save It
            image = pb.getImageFromCamera()
            cv2.imshow("current_view" , image)
            cv2.imwrite("data_log/" + filename,image )

            global_imagecount = global_imagecount + 1


except KeyboardInterrupt:
    pb.stop()
    f1.close()
    #np.savetxt("odometry_out.txt", global_odometry, delimiter=",")
