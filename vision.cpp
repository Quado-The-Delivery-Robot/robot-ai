#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "vision.h"
#include "detectCars.h"

using namespace cv;
using namespace std;

void runVision()
{
	// Load the pre-trained Haar Cascade classifier for car detection.
	CascadeClassifier carCascade;
	carCascade.load("cars.xml");

	//--- INITIALIZE VIDEOCAPTURE
	VideoCapture capture;

	// open the default camera using default API
	// cap.open(0);
	// OR advance usage: select any API backend
	int deviceID = 0; // 0 = open default camera
	int apiID = CAP_ANY; // 0 = autodetect default API

	// open selected camera using selected API
	capture.open(deviceID, apiID);

	// Confirm that the default camera was opened.
	if (!capture.isOpened()) {
		return;
	}

	Mat frame;

	for (;;)
	{
		capture.read(frame);

		// Confirm that the frame is not empty.
		if (frame.empty()) {
			break;
		}

		detectCars(frame, carCascade);

		// DEBUG: Shows the results of the masks and 
		imshow("Live", frame);

		if (waitKey(5) >= 0)
			break;
	}

	capture.release();
	destroyAllWindows();
}