/*
 * KS_MagickImage2CvMat.hpp
 *
 *  Created on: 22-11-2010
 *      Author: szkudi
 */

#ifndef KS_ROICROP_HPP_
#define KS_ROICROP_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"
#include "Props.hpp"
#include "Types/DrawableContainer.hpp"
#include "Types/Rectangle.hpp"

#include <Types/stream_OpenCV.hpp>

#include <cv.h>
#include <highgui.h>

namespace Processors{

namespace ROIC {

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

class KS_ROICrop: public Base::Component {
public:
	/*!
	 * Constructor
	 */
	KS_ROICrop(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~KS_ROICrop();

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
	Base::EventHandler <KS_ROICrop> h_onNewImage;

	void onNewDrawable();

	Base::EventHandler <KS_ROICrop> h_onNewDrawable;

	/// Input data stream
	Base::DataStreamIn < Types::DrawableContainer, Base::DataStreamBuffer::Newest > in_container;
	Base::DataStreamIn < cv::Mat, Base::DataStreamBuffer::Newest>	in_img;

	/// Event raised, when image is processed
	Base::Event * newImage;

	/// Output data stream - processed image
	Base::DataStreamOut <cv::Mat> out_img;

	Base::Event* newDrawable;

	Base::DataStreamOut<Types::DrawableContainer> out_drawable;

	/// Threshold properties
	Props props;

private:
	void normalizePoint(cv::Point* p, cv::Size size);
	bool intersection(Types::Rectangle* r1, Types::Rectangle* r2);
	Types::Rectangle* makeOneRect(Types::Rectangle* r1, Types::Rectangle* r2);

	Types::DrawableContainer container;
	cv::Mat img;
	bool img_ready, container_ready;
};
}

}

/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("KS_ROICrop", Processors::ROIC::KS_ROICrop, Common::Panel_Empty)


#endif /* KS_MAGICKIMAGE2CVMAT_HPP_ */
