import numpy as np
import cv2
import math
import sys
sys.path.append('thirdparties/gtsam/build/cython')
import gtsam
import re

import visual_odometry
import slam


f = open('data_log/data_out.txt')
line = f.readline()
gtWheelPoses = []
globalWheelPoses = []
globalPose = gtsam.Pose2(0,0,0)
globalWheelPoses.append(globalPose)
print globalPose.matrix()
while line:
    wheelO = re.findall('[+-]?\d+\.\d+',line)
    line = f.readline()

    pose = gtsam.Pose2(float(wheelO[0]), 0, np.deg2rad(float(wheelO[1])))
    gtWheelPoses.append(pose)

    globalPose = globalPose.compose(pose);
    print pose.matrix()
    print globalPose.matrix()
    globalWheelPoses.append(globalPose)

gtVOposes = [];
globalPose = gtsam.Pose2(0,0,0)
gtVOposes.append(globalPose)
globalVOposes = [];
globalVOposes.append(globalPose)

for i in range(19, 274):
    pose = visual_odometry.visual_odometry(i,i+1)
    print pose

    if pose[0] == 0:
        gtsamPose = gtVOposes[i-19]
    else:
        gtsamPose = gtsam.Pose2(pose[0],pose[1],  np.deg2rad(pose[2]))

    gtVOposes.append(gtsamPose);

    globalPose = globalPose.compose(gtsamPose);
    print globalPose.matrix()
    globalVOposes.append(globalPose)



print len(gtVOposes)
print len(globalVOposes)
print len(gtWheelPoses)
print len(globalWheelPoses)

s = slam.Slam(globalWheelPoses,gtWheelPoses,globalVOposes,gtVOposes)

r = s.estimate_global()

fout = open('out.txt', 'w+')
for pose in r:
    for d in np.nditer(pose.matrix()):
        fout.write("%f " % d)
    fout.write("\n")

fout.close()
