#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "detectCars.h"

using namespace cv;
using namespace std;

// Detects cars in a frame.
void detectCars(Mat& frame, CascadeClassifier& carCascade) {
	vector<Rect> cars;
	carCascade.detectMultiScale(frame, cars, 1.1, 3, 0, Size(30, 30));

	// Debug only.
	for (const auto& car : cars) {
		rectangle(frame, car, Scalar(0, 255, 0), 2);
	}
}