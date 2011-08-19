/*!
 * \file CvFilter2D_Processor.hpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#ifndef KS_BCREADER_HPP_
#define KS_BCREADER_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"
#include "Props.hpp"

#include <Types/stream_OpenCV.hpp>

#include <cv.h>
#include <highgui.h>

#include <sstream>

/**
  */

namespace Processors {
namespace BCReader {

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

/*!
 * \class KS_CvMat2MagicImage_Processor
 * \brief Convolves an image with the kernel
 */
class KS_BCReader: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	KS_BCReader(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~KS_BCReader();

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
	Base::EventHandler <KS_BCReader> h_onNewImage;

	/// Input data stream
	Base::DataStreamIn <Mat> in_img;

	/// Threshold properties
	Props props;
};

}//: namespace CvFilter2D
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("KS_BCReader", Processors::BCReader::KS_BCReader, Common::Panel_Empty)

#endif /* CVFILTER2D_PROCESSOR_HPP_ */

