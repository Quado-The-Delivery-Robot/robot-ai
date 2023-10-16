
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Function for car detection
void detectCars(Mat& frame, CascadeClassifier& carCascade) {
	// Detect cars in the frame
	vector<Rect> cars;
	carCascade.detectMultiScale(frame, cars, 1.1, 3, 0, Size(30, 30));

	// Draw rectangles around detected cars
	for (const auto& car : cars) {
		rectangle(frame, car, Scalar(0, 255, 0), 2);
	}
}

int main(int, char**)
{
	// Load the pre-trained Haar Cascade classifier for car detection.
	CascadeClassifier carCascade;
	carCascade.load("C:/Users/lando/Documents/quado/cars.xml");

	//--- INITIALIZE VIDEOCAPTURE
	VideoCapture capture;

	// open the default camera using default API
	// cap.open(0);
	// OR advance usage: select any API backend
	int deviceID = 0; // 0 = open default camera
	int apiID = cv::CAP_ANY; // 0 = autodetect default API

	// open selected camera using selected API
	capture.open(deviceID, apiID);

	// Confirm that the default camera was opened.
	if (!capture.isOpened()) {
		return -1;
	}

	Mat frame;

	for (;;)
	{
		capture.read(frame);

		// Confirm that the frame is not empty.
		if (frame.empty()) {
			break;
		}

		// Detect cars
		detectCars(frame, carCascade);

		// DEBUG: Shows the results of the masks and 
		imshow("Live", frame);

		if (waitKey(5) >= 0)
			break;
	}

	capture.release();
	destroyAllWindows();
	return 0;
}