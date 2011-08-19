/*!
 * \file CvFilter2D_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>
#include <iostream>

#include "KS_CvMat2MagickImage.hpp"
#include "Logger.hpp"

#include <vector>

namespace Processors {
namespace CvMat2MI {

KS_CvMat2MagickImage::KS_CvMat2MagickImage(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello KS_CvMat2MagickImage\n";

}

KS_CvMat2MagickImage::~KS_CvMat2MagickImage()
{
	LOG(LTRACE) << "Good bye KS_CvMat2MagickImage\n";
}

bool KS_CvMat2MagickImage::onInit()
{
	LOG(LTRACE) << "KS_CvMat2MagickImage::initialize\n";

	h_onNewImage.setup(this, &KS_CvMat2MagickImage::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	return true;
}

bool KS_CvMat2MagickImage::onFinish()
{
	LOG(LTRACE) << "KS_CvMat2MagickImage::finish\n";

	return true;
}

bool KS_CvMat2MagickImage::onStep()
{
	LOG(LTRACE) << "KS_CvMat2MagickImage::step\n";
	return true;
}

bool KS_CvMat2MagickImage::onStop()
{
	return true;
}

bool KS_CvMat2MagickImage::onStart()
{
	return true;
}

void KS_CvMat2MagickImage::onNewImage()
{
	LOG(LTRACE) << "KS_CvMat2MagickImage::onNewImage\n";
	try {
		cv::Mat img = in_img.read();

		Magick::Image mimg;

		cv::Size size = img.size();

		if(img.channels() == 1){
//			std::cout << "BEFORE: Single channel" << std::endl;
			mimg.read(size.width, size.height, "I", MagickCore::CharPixel, img.datastart);
		}
		else if(img.channels() == 3){
//			std::cout << "BEFORE: RGB channels" << std::endl;
			mimg.read(size.width, size.height, "BGR", MagickCore::CharPixel, img.datastart);
		}

		out_img.write(mimg);

		newImage->raise();
	} catch (...) {
		LOG(LERROR) << "KS_CvMat2MagickImage::onNewImage failed\n";
	}

}

}//: namespace CvMat2IM
}//: namespace Processors
