/*
 * KS_MagickImage2CvMat.hpp
 *
 *  Created on: 22-11-2010
 *      Author: szkudi
 */

#ifndef KS_MAGICKIMAGE2CVMAT_HPP_
#define KS_MAGICKIMAGE2CVMAT_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"
#include "Props.hpp"

#include <Types/stream_OpenCV.hpp>

#include <cv.h>
#include <highgui.h>

#include <ImageMagick/Magick++.h>
//#ifndef MagickPlusPlus_Header
//#include <ImageMagick/Magick++/Include.h>
//#include <ImageMagick/Magick++/Image.h>
//#include <ImageMagick/Magick++/Pixels.h>
//#include <ImageMagick/Magick++/STL.h>
//#define MagickPlusPlus_Header
//#endif // MagickPlusPlus_Header

namespace Processors{

namespace MI2CvMat {

using namespace cv;

/*!
 * \brief Properties
 */
struct Props: public Base::Props
{
	/*!
	 * \copydoc Base::Props::load
	 */
	void load(const ptree & pt)
	{
	}

	/*!
	 * \copydoc Base::Props::save
	 */
	void save(ptree & pt)
	{

	}

};

class KS_MagickImage2CvMat: public Base::Component {
public:
	/*!
	 * Constructor
	 */
	KS_MagickImage2CvMat(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~KS_MagickImage2CvMat();

	/*!
	 * Return window properties
	 */
	Base::Props * getProperties()
	{
		return &props;
	}

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Retrieves data from device.
	 */
	bool onStep();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	/*!
	 * Event handler function.
	 */
	void onNewImage();

	/// Event handler.
	Base::EventHandler <KS_MagickImage2CvMat> h_onNewImage;

	/// Input data stream
	Base::DataStreamIn <Magick::Image, Base::DataStreamBuffer::Newest> in_img;

	/// Event raised, when image is processed
	Base::Event * newImage;

	/// Output data stream - processed image
	Base::DataStreamOut <Mat> out_img;

	/// Threshold properties
	Props props;
};
}

}

/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("KS_MagickImage2CvMat", Processors::MI2CvMat::KS_MagickImage2CvMat, Common::Panel_Empty)


#endif /* KS_MAGICKIMAGE2CVMAT_HPP_ */
