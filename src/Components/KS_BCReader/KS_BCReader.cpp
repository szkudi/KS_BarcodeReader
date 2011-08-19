/*!
 * \file CvFilter2D_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>
#include <iostream>

#include "KS_BCReader.hpp"
#include "Logger.hpp"

#include <vector>

namespace Processors {
namespace BCReader {

KS_BCReader::KS_BCReader(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello KS_BCReader\n";

}

KS_BCReader::~KS_BCReader()
{
	LOG(LTRACE) << "Good bye KS_BCReader\n";
}

bool KS_BCReader::onInit()
{
	LOG(LTRACE) << "KS_BCReader::initialize\n";

	h_onNewImage.setup(this, &KS_BCReader::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	return true;
}

bool KS_BCReader::onFinish()
{
	LOG(LTRACE) << "KS_BCReader::finish\n";

	return true;
}

bool KS_BCReader::onStep()
{
	LOG(LTRACE) << "KS_BCReader::step\n";
	return true;
}

bool KS_BCReader::onStop()
{
	return true;
}

bool KS_BCReader::onStart()
{
	return true;
}

void KS_BCReader::onNewImage()
{
	LOG(LTRACE) << "KS_BCReader::onNewImage\n";
	try {
		cv::Mat img = in_img.read();

		cv::Size size = img.size();

		cv::Mat line = img.row(size.height/2);
		line.convertTo(line, CV_8UC3);

		double lum[size.width];
		memset(lum, 0, sizeof(double) * size.width);

		for(int i = 0; i < size.width; ++i){
			lum[i] = line.data[3*i] * 0.114 + line.data[3*i + 1] * 0.587 + line.data[3*i + 2] * 0.299;
		}

		for(int i = 1; i < size.width - 1; ++i){
			if(abs(lum[i] - lum[i - 1]) > 0.01 &&
			   abs(lum[i] - lum[i + 1]) > 0.01	){
//				if(lum[i] > lum[i - 1] && lum[i] > lum[i + 1])

			}
		}


	} catch (...) {
		LOG(LERROR) << "KS_BCReader::onNewImage failed\n";
	}

}

}//: namespace BCReader
}//: namespace Processors
