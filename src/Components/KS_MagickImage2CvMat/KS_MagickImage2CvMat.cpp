/*
 * KS_MagickImage2CvMat.cpp
 *
 *  Created on: 22-11-2010
 *      Author: szkudi
 */

#include "KS_MagickImage2CvMat.hpp"
#include "Logger.hpp"

namespace Processors{

namespace MI2CvMat {

KS_MagickImage2CvMat::KS_MagickImage2CvMat(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello KS_MagickImage2CvMat\n";
}

KS_MagickImage2CvMat::~KS_MagickImage2CvMat()
{
	LOG(LTRACE) << "Good bye KS_MagickImage2CvMat\n";
}

bool KS_MagickImage2CvMat::onInit()
{
	LOG(LTRACE) << "KS_MagickImage2CvMat::initialize\n";

	h_onNewImage.setup(this, &KS_MagickImage2CvMat::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	return true;
}

bool KS_MagickImage2CvMat::onFinish()
{
	LOG(LTRACE) << "KS_MagickImage2CvMat::finish\n";

	return true;
}

bool KS_MagickImage2CvMat::onStep()
{
	LOG(LTRACE) << "KS_MagickImage2CvMat::step\n";
	return true;
}

bool KS_MagickImage2CvMat::onStop()
{
	return true;
}

bool KS_MagickImage2CvMat::onStart()
{
	return true;
}

void KS_MagickImage2CvMat::onNewImage()
{
	LOG(LTRACE) << "KS_MagickImage2CvMat::onNewImage\n";
	try {
		Magick::Image img = in_img.read();

		cv::Size size;
		cv::Mat mimg;

		size.height = img.size().height();
		size.width = img.size().width();

		char *pixels;

		Magick::ColorspaceType ct = img.colorSpace();

		if(ct == Magick::RGBColorspace){
//			std::cout << "AFTER:: RGB channels" << std::endl;
//			pixels = (char*)malloc(sizeof(char) * 3 * size.height * size.width);
			pixels = new char[sizeof(char) * 3 * size.height * size.width];
			img.write(0, 0, size.width, size.height, "BGR", MagickCore::CharPixel, pixels);
			mimg = cv::Mat(size, CV_8UC3, pixels );
		}
		else if(ct == Magick::GRAYColorspace){
//			std::cout << "AFTER:: Single channel" << std::endl;
//			pixels = (char*)malloc(sizeof(char) * size.height * size.width);
			pixels = new char[sizeof(char) * size.height * size.width];
			img.write(0, 0, size.width, size.height, "G", MagickCore::CharPixel, pixels);
			mimg = cv::Mat(size, CV_8UC1, pixels );
		}

//		free(pixels);

		out_img.write(mimg);
		newImage->raise();

		delete[] pixels;

	} catch (...) {
		LOG(LERROR) << "KS_MagickImage2CvMat::onNewImage failed\n";
	}

}

}//: namespace IM2CvMat
}//: namespace Processors
