#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// USE https://github.com/Yuelong-Yu/ERFNet-Caffe FOR DATASETS

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

// TEMP
Mat postProcess(const cv::Mat& output) {
	// Thresholding to create a binary mask
	cv::Mat mask;
	cv::threshold(output, mask, 0.5, 255, cv::THRESH_BINARY);

	// Clean up the mask using morphological operations
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
	cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

	return mask;
}

// Function for side walk detection
void detectSidewalk(Mat& frame, dnn::Net semanticSegmentationModel) {
	Mat blob = dnn::blobFromImage(frame, 1.0, Size(1024, 512), Scalar(0, 0, 0), false, false);
	semanticSegmentationModel.setInput(blob);

	Mat output = semanticSegmentationModel.forward();

	// Post-processing for sidewalk detection
	Mat sidewalkMask = postProcess(output);

	// Overlay the sidewalk mask on the original frame
	Mat sidewalkDetection;
	frame.copyTo(sidewalkDetection, sidewalkMask);
}

int main(int, char**)
{
	// Load the pre-trained Haar Cascade classifier for car detection.
	CascadeClassifier carCascade;
	carCascade.load("C:/Users/lando/source/repos/robot-ai/quado/cars.xml");

	// Load a pre-trained model (ENet) for semantic segmentation
	dnn::Net semanticSegmentationModel = dnn::readNet("C:/Users/lando/source/repos/robot-ai/quado/erfnet_cityscapes.prototxt",
	"C:/Users/lando/source/repos/robot-ai/quado/erfnet_cityscapes.caffemodel");

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

		detectCars(frame, carCascade);
		detectSidewalk(frame, semanticSegmentationModel);

		// DEBUG: Shows the results of the masks and 
		imshow("Live", frame);

		if (waitKey(5) >= 0)
			break;
	}

	capture.release();
	destroyAllWindows();
	return 0;
}