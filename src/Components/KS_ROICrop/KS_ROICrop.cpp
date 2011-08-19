/*
 * KS_MagickImage2CvMat.cpp
 *
 *  Created on: 22-11-2010
 *      Author: szkudi
 */

#include "KS_ROICrop.hpp"
#include "Logger.hpp"
#include <vector>

using namespace Types;

namespace Processors{

namespace ROIC {

KS_ROICrop::KS_ROICrop(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello KS_ROICrop\n";
}

KS_ROICrop::~KS_ROICrop()
{
	LOG(LTRACE) << "Good bye KS_ROICrop\n";
}

bool KS_ROICrop::onInit()
{
	LOG(LTRACE) << "KS_ROICrop::initialize\n";

	h_onNewImage.setup(this, &KS_ROICrop::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	h_onNewDrawable.setup(this, &KS_ROICrop::onNewDrawable);
	registerHandler("onNewDrawable", &h_onNewDrawable);

	registerStream("in_container", &in_container);


	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	newDrawable = registerEvent("newDrawable");

	registerStream("out_drawable", &out_drawable);

	img_ready = false;
	container_ready = false;

	return true;
}

bool KS_ROICrop::onFinish()
{
	LOG(LTRACE) << "KS_ROICrop::finish\n";

	return true;
}

bool KS_ROICrop::onStep(){
	LOG(LTRACE) << "KS_ROICrop::step\n";

	cv::Point* p1;
	cv::Point* p2;
	Rectangle* it, *second;
	DrawableContainer ret;
	vector<Rectangle*> rects, tmp;
	bool added = false;

	int width, heigth;

	try{
		img_ready = false;
		container_ready = false;

		for(unsigned int i = 0; i < container.getSize(); ++i){
			it = (Rectangle*)container.get(i);
			p1 = it->get(0);
			p2 = it->get(1);

			width = abs(p2->x - p1->x);
			heigth = abs(p2->y - p2->y);

			p1->x -= 0.5 * width;
			p2->x += 0.5 * width;

			p1->y += 0.5 * heigth;
			p2->y -= 0.5 * heigth;

			normalizePoint(p1, img.size());
			normalizePoint(p2, img.size());

			tmp.push_back(it);

		}

//		for(unsigned int i = 0; i < container.getSize(); i++){
////			cout << "wszedlem w fora" << endl;
//			it = (Rectangle*)container.get(i);
//			vector<Rectangle*>::iterator iter;
//			for( iter = rects.begin(); iter != rects.end(); ){
//				second = (*iter);
//				if(intersection(it, second)){
////					cout << "Intersection" << endl;
//					rects.push_back(makeOneRect(it, second));
////					cout << "New inserted" << endl;
////					iter = rects.erase(iter);
//					if(iter != rects.end())
//						iter++;
////					added = true;
//					break;
//				}else
//					iter++;
////				cout << "wyszedlem z ifa intersekcji || jest ich: "	<< rects.size() << endl;
//			}
//			if(iter == rects.end()){
////			if(!added){
//				rects.push_back(it);
////				cout << "dodalem element do rectsow || jest ich: "	<< rects.size() << endl;
//			}
//		}


//		for(unsigned int i = 0; i < rects.size(); ++i)
//			ret.add(rects[i]);

		out_drawable.write(container);
		newDrawable->raise();

		for(unsigned int i = 0; i < container.getSize(); ++i){
			it = (Rectangle*)container.get(i);
			p1 = it->get(0);
			p2 = it->get(1);

//			cv::Mat tmp(img, cv::Rect(p1, p2));

			out_img.write(cv::Mat(img, cv::Rect(*p1, *p2)).clone());
			newImage->raise();

		}
	}catch(...){
		LOG(LERROR) << "KS_ROICrop::step\n";
	}

	return true;
}

void KS_ROICrop::normalizePoint(cv::Point* p, cv::Size size){
	if(p->x < 0)
		p->x = 0;
	else if(p->x >= size.width)
		p->x = size.width - 1;

	if(p->y < 0)
		p->y = 0;
	else if(p->y >= size.height)
		p->y = size.height - 1;
}

//bool KS_ROICrop::checkIntersecions(vector<Rectangle>::pointer first, vector<Rectangle>::pointer second){
//	bool ret_val = false;
//
//	for(unsigned int i = 0; i < container.getSize(); i++){
//		cout << "wszedlem w fora" << endl;
//		it = (Rectangle*)container.get(i);
//		vector<Rectangle*>::iterator iter;
//		for( iter = rects.begin(); iter != rects.end(); ++iter){
//			second = (*iter);
//			if(intersection(it, second)){
//				cout << "Intersection" << endl;
//				rects.push_back(makeOneRect(it, second));
////					iter = rects.erase(iter);
//				ret_val = true;
//				break;
//			}
//			cout << "wyszedlem z ifa intersekcji || jest ich: "	<< rects.size() << endl;
//		}
//		if(iter == rects.end()){
////			if(!added){
//			rects.push_back(it);
//			cout << "dodalem element do rectsow || jest ich: "	<< rects.size() << endl;
//		}
//	}
//
//	return ret_val;
//}

bool KS_ROICrop::intersection(Rectangle* r1, Rectangle* r2){
	cv::Point* r1_p1 = r1->get(0);
	cv::Point* r1_p2 = r1->get(1);

	cv::Point* r2_p1 = r2->get(0);
	cv::Point* r2_p2 = r2->get(1);

//	if(r2_p2->x < r1_p1->x ||
//	   r2_p2->y > r1_p1->y ||
//	   r2_p1->x > r1_p2->x ||
//	   r2_p1->y < r1_p2->y)
//		return false;
//
//	return true;

	if(r2_p2->x < r1_p1->x ||
	   r2_p2->y < r1_p1->y ||
	   r2_p1->x > r1_p2->x ||
	   r2_p1->y > r1_p2->y)
		return false;

	return true;

}

Rectangle* KS_ROICrop::makeOneRect(Rectangle* r1, Rectangle* r2){
	int x1, y1;
	int x2, y2;

	cv::Point* r1_p1 = r1->get(0);
	cv::Point* r1_p2 = r1->get(1);

	cv::Point* r2_p1 = r2->get(0);
	cv::Point* r2_p2 = r2->get(1);

	x1 = min(r1_p1->x, r2_p1->x);
	y1 = min(r1_p1->y, r2_p1->y);

	x2 = max(r1_p2->x, r2_p2->x);
	y2 = max(r1_p2->y, r2_p2->y);

	return new Rectangle(x1, y1, x2 - x1, y2 - y1);
}

bool KS_ROICrop::onStop()
{
	return true;
}

bool KS_ROICrop::onStart()
{
	return true;
}

void KS_ROICrop::onNewImage()
{
	LOG(LTRACE) << "KS_ROICrop::onNewImage\n";
	try {
		img = in_img.read();
		img_ready = true;
		if(img_ready && container_ready)
			onStep();
	} catch (...) {
		LOG(LERROR) << "KS_ROICrop::onNewImage failed\n";
	}

}

void KS_ROICrop::onNewDrawable(){
	LOG(LTRACE) << "KS_ROICrop::onNewDrawable\n";
	try{
		container = in_container.read();
//		std::cout << "Data read " << container.getSize() <<"\n" << std::endl;
		container_ready = true;
		if(img_ready && container_ready)
			onStep();
	}catch(...){
		LOG(LERROR) << "KS_ROICrop::onNewDrawable\n";
	}
}

}//: namespace ROIC
}//: namespace Processors
