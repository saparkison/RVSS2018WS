import numpy as np
import cv2
import math

def visual_odometry( start_num, end_num )

#start_num = 19
#end_num = 274

    # params for ShiTomasi corner detection
    feature_params = dict( maxCorners = 100,
                           qualityLevel = 0.05,
                           minDistance = 10,
                           blockSize = 15,
                           useHarrisDetector=True )

    # Parameters for lucas kanade optical flow
    lk_params = dict( winSize  = (15,15),
                      maxLevel = 15,
                      criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 20, 0.001))

    # Create some random colors
    color = np.random.randint(0,255,(100,3))

    # Open the file with read only permit
    folder = 'data_log/'
    f = open(folder+'data_out.txt')

    #H = np.array([[  1.12375325e-01,  -4.86001720e-01,   8.77712777e+02],
    #             [  -2.36834933e+00,   4.49234588e+00,   6.64034708e+02],
    #             [   4.01039286e-04,   1.59276405e-02,   1.00000000e+00]],float)

    H = np.array([[ 1.22265638e+00, -9.02305713e-01, -3.24612144e+03],
                 [  1.27021068e+01, -2.43531947e+01, -1.38074249e+03],
                 [  4.74107545e-03, -8.12562362e-02,  1.00000000e+00]],float)

    # Read the first line
    line = f.readline()

    # Load an color image in grayscale
    img1 = cv2.imread(folder+line[0:8],0)
    # Warp source image to destination based on homography
    #img1 = cv2.warpPerspective(img1, H, (600,600))

    # Create a mask image for drawing purposes
    mask = np.zeros_like(img1)

    ## If the file is not empty keep reading line one at a time
    ## till the file is empty
    for x in range(start_num, end_num): #start image, end image
        # Get corners
        p0 = cv2.goodFeaturesToTrack(img1, mask = None, **feature_params)

        # Load an color image in grayscale
        line = f.readline()
        img2 = cv2.imread(folder+line[0:8],0)

        # Warp source image to destination based on homography
        #img2 = cv2.warpPerspective(img2, H, (600,600))

        # Track corners
        print "Name: %s" % (folder+line[0:8])
        p1, st, err = cv2.calcOpticalFlowPyrLK(img1, img2, p0, None, **lk_params)

        # Select good points
        st = st.reshape(st.shape[0])
        good_old = p0[st==1]
        good_new = p1[st==1]

        # Prespective Transformation
        p0 = cv2.perspectiveTransform(good_old, H)
        p1 = cv2.perspectiveTransform(good_new, H)
        #p0 = good_old;
        #p1 = good_new;

        # Transformation
        M = cv2.estimateRigidTransform(p0, p1, False)
        if M is not None:
           print(M)
           print(M[0][2])
           print(M[1][2])
           a = M[1][0]/M[0][0]
           #print(M[1][0])
           #print(M[0][0])
           print(math.atan(a)*180/3.14)

        # Copy the second image
        img1 = img2.copy()

        # draw the tracks
        frame = img2.copy()
        for i,(new,old) in enumerate(zip(good_new,good_old)):
            a,b = new.ravel()
            c,d = old.ravel()
            mask = cv2.line(mask, (a,b),(c,d), color[i].tolist(), 2)
            frame = cv2.circle(frame,(a,b),5,color[i].tolist(),-1)
        img = cv2.add(frame,mask)
        cv2.imshow('frame',img)
        cv2.waitKey(0) & 0xFF
        mask = np.zeros_like(img1)

        #print "I am here."

    cv2.destroyAllWindows()
    f.close()

    #print "Now I am here!"
return 
