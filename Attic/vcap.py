#! /usr/local/bin/python

import cv2
import datetime
import sys



def frame_capture(filename_base):
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

        if filename_base != "":
            #thisSecond = datetime.datetime.now().second
            #if thisSecond != lastSecond:
            #    print "appending frame!"
                frames.append(frame)
            #    lastSecond = thisSecond

    cap.release()
    cv2.destroyAllWindows()

    for (index,frame) in enumerate(frames):
        cv2.imwrite("%s-%05d.png" % (filename_base,index), frame)


def video_capture(filename):
    print "trying video capture!"
    cap = cv2.VideoCapture(0)

    #fourcc = cv2.cv.CV_FOURCC('A','V','C','1')
    #fourcc = cv2.cv.CV_FOURCC('M','J','P','G')
    fourcc = cv2.cv.CV_FOURCC('m','p','4','v')
    writ = cv2.VideoWriter(filename, fourcc, 60, (1440,1080))

    while True:
        ret, frame = cap.read()

        writ.write(frame)

        cv2.imshow('frame',frame)
        if cv2.waitKey(1) & 0xff == ord('q'):
            break

    cap.release()
    writ.release()
    cv2.destroyAllWindows()




if __name__ == "__main__":
    video_capture(sys.argv[1])
    #frame_capture(sys.argv[1])
