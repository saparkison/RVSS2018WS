import numpy as np
import cv2
import math
import re

temp = 1

start_num = 19
end_num = 274

H = np.matrix([[ 1.22265638e+00, -9.02305713e-01, -3.24612144e+03],
             [  1.27021068e+01, -2.43531947e+01, -1.38074249e+03],
             [  4.74107545e-03, -8.12562362e-02,  1.00000000e+00]],float)

# Define the empty occupancy grid
occupancy_grid = np.zeros((48,64), float) # 5 pixels per grid

# Bring in the transformation matrix
f = open('out.txt')

# Transform the images
for x in range(start_num, end_num): #start image, end image

    # Read in the array
    line = f.readline()
    # Extract data from first line. Cast values to integers from strings.
    # info = (int(val) for val in line.split())

    info = re.findall('[+-]?\d+\.\d+',line)

    print info

    print x

    y = x+1

    trans = np.matrix([[info[0], info[3], info[6]],
                     [ info[1], info[4], info[7]],
                     [ info[2], info[5], info[8]]], float)

    # Bring in the images
    folder = 'data_log/'
    img1 = cv2.imread(folder+"%04d.png" % x,0)
    cv2.imshow("IMG1", img1)
    #img1 = cv2.cvtColor(img1,cv2.COLOR_RGB2GRAY)
    img2 = cv2.imread(folder+"%04d.png" % y,0)
    #img2 = cv2.cvtColor(img2,cv2.COLOR_RGB2GRAY)
    # Warp using the H matrix

    # II  = np.zeros((600,1200),"uint8")
    # II[:,:600] = I1w
    # II[:,600:] = I2w
    # # Read in the motions
    # tx = -25.28   # mm
    # ty = 2.2      # mm
    # yaw = 2.37    # degrees
    # # Set up the M matrix
    # c = np.cos(np.deg2rad(yaw))
    # s = np.sin(np.deg2rad(yaw))
    # M = np.array([[c, -s, tx],[s,c,ty]],float)
    # # Alignn the images using M
    # (cols,rows) = I1w.shape
    # dst = cv2.warpAffine(I1w,M,(cols,rows))
    # dst = cv2.addWeighted(dst,0.5,I2w,0.5,0)
    # # Align based on the correct center of rotation
    # cr = np.array([[0.0],[266]])
    # R  = M[:2,:2]
    # tc = R.dot(cr) - cr
    # M[0,2] -= tc[0]
    # M[1,2] -= tc[1]
    # There may be a scale effect - it was 0.98 in the sample
    # M[:2,:2] *= 0.98
    # dst = cv2.warpAffine(I1w,M,(cols,rows))
    # dst = cv2.addWeighted(dst,0.5,I2w,0.5,0)
    # Show the transformed images
    # cv2.imshow("The two views",dst)


    # Determine where the pixels are black
    # I think the images are 240x320 pixels
    # Assume high number is black, low number is white
    # Let break down pixels into the grid
    # Then put them into the global map based on the global pose

    # Discritize into grid
    local_occupancy = np.zeros((48,64), float)

    global_position = np.zeros((2,240,320),float)
    pixel_map = np.zeros((240,320),float)

    for i in range(1, 240):
        for j in range(1,320):
            # Posion Vector
            local_pos = np.matrix([[i-1],[j-1],[1]],float)
            #print('local pos initial: ')
            #print local_pos

            local_pos = H * local_pos

            #print('local pos after H: ')
            #print local_pos

            local_pos[0,0] = local_pos[0,0]/local_pos[2,0]
            local_pos[1,0] = local_pos[1,0]/local_pos[2,0]
            local_pos[2,0] = 1

            #print local_pos

            global_pos = trans * local_pos;

            #print global_pos

            global_pos[0,0] = global_pos[0,0]/global_pos[2,0]
            global_pos[1,0] = global_pos[1,0]/global_pos[2,0]
            global_pos[2,0] = 1

            global_position[0,i,j] = global_pos[0,0]
            global_position[1,i,j] = global_pos[1,0]

            # Determine if cell is occipied
            threshold = 0.7
            if img1[i-1,j-1] < threshold:
                pixel_map[i-1,j-1] = -1
            else:
                pixel_map[i-1,j-1] = 1
                

    # This should create a local occupancy grid of 0s and 1s
