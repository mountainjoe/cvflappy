#!/usr/bin/env python

import cv2
import numpy
#import pylab

def display_and_wait(img):
    cv2.imshow("display",img)
    cv2.waitKey()

img = cv2.imread("flappy-try2-10.png")
display_and_wait(img)
#img = cv2.imread("flappy-try2-13.png")
#img = cv2.imread("flappy-try2-110.png")

bird_area = ( 175,525, 400,1700 )

hue = cv2.cvtColor(img,cv2.cv.CV_BGR2HSV)[...,0]
display_and_wait(hue)

thr = cv2.threshold(hue,25,255,cv2.cv.CV_THRESH_BINARY)[1]
display_and_wait(thr)

erd = cv2.erode(thr,numpy.ones((9,9)))
display_and_wait(erd)

dil = cv2.dilate(erd,numpy.ones((15,15)))
display_and_wait(dil)

crp = dil[bird_area[0]:bird_area[1],bird_area[2]:bird_area[3]]
display_and_wait(crp)

SBD = cv2.SimpleBlobDetector()

SBD.setBool('filterByCircularity',False)
SBD.setBool('filterByColor',False)
SBD.setBool('filterByConvexity',False)
SBD.setBool('filterByInertia',False)

SBD.setBool('filterByArea',True)
SBD.setInt('minArea',750)
SBD.setInt('maxArea',7500)

keypoints = SBD.detect(crp)
print keypoints

display = img.copy()
for k in keypoints:
  print k.pt,k.size
  cv2.circle(display,tuple(numpy.round(k.pt).astype(int)+(bird_area[2],bird_area[0])),numpy.round(k.size).astype(int),(0,0,255),5)

display_and_wait(display)
