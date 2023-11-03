#pragma once

#ifndef HEADER_VISION_DETECTCARS
#define HEADER_VISION_DETECTCARS

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void detectCars(Mat&, CascadeClassifier&);

#endif