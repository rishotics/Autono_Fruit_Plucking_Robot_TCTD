from detector import ObjectDetector
import numpy as np
import cv2
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("-d","--detector",required=True,help="path to trained detector to load...")
#ap.add_argument("-i","--image",required=True,help="path to an image for object detection...")
ap.add_argument("-a","--annotate",default=None,help="text to annotate...")
args = vars(ap.parse_args())

detector = ObjectDetector(loadPath=args["detector"])

cap=cv2.VideoCapture("naspati.webm")
grabbed, image = cap.read()
while True:

	grabbed,image=cap.read()
	
	x,y,xb,yb=detector.detect(image,annotate=args["annotate"])

	#detector.detect(image,annotate=args["annotate"])
	center=[[(x/2+xb/2)/2],[(y+yb)/3]]	

	key = cv2.waitKey(1) & 0xFF

	# if the 'q' key is pressed, stop the loop
	if key == ord("q"):
		break

# cleanup the camera and close any open windows
cap.release()
cv2.destroyAllWindows()