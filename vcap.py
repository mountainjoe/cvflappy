#! /usr/local/bin/python

import cv2
import datetime
import sys

filename = sys.argv[1]
frames = []

cap = cv2.VideoCapture(0)

lastSecond = 0

while (True):
    ret, frame = cap.read()

    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    #cv2.imshow('frame', gray)
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break

    thisSecond = datetime.datetime.now().second
    if thisSecond != lastSecond:
        print "appending frame!"
        frames.append(frame)
        lastSecond = thisSecond


cap.release()
cv2.destroyAllWindows()


for (index,frame) in enumerate(frames):
    cv2.imwrite("flappy-%s-%d.png" % (filename,index), frame)

