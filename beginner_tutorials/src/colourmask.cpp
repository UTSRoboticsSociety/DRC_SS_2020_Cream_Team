#include "ros/ros.h"
#include <opencv/cv.hpp>
#include "std_msgs/UInt16.h"

#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>

	using namespace cv;
	using namespace std;

//Upper and Lower values For BGR: Blue detection
 
#define b_blower 123
#define b_glower 54
#define b_rlower 14

#define b_bupper 183
#define b_gupper 134
#define b_rupper 94

//Upper and Lower values For BGR: Yellow detection
 
#define y_blower 134
#define y_glower 165
#define y_rlower 168

#define y_bupper 214
#define y_gupper 245
#define y_rupper 248

//ROS setup
class image_sub;
class ImageConverter
{
	ros::NodeHandle nh_;
	image_transport::ImageTransport it;
	image_transport::Subscriber image_sub;
	

public:
  	ImageConverter()
  	  : it(nh_)
  		{
		ros::NodeHandle mi;
		image_sub = it.subscribe("/usb_cam/image_raw", 1, &ImageConverter::masking, this);
		//transport vectors(actually set up for ints) out here?
		ros::Publisher mask = mi.advertise<std_msgs::UInt16>("/colourmask/output", 1);
		}
	
	void masking(const sensor_msgs::ImageConstPtr& msg)
{
	cv_bridge::CvImage image;
	try
    	{
//from example code    	  
//cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);


		//insert cv code in here

    	}
    	catch (cv_bridge::Exception& e)
    	{
    	  ROS_ERROR("cv_bridge exception: %s", e.what());
      	return;
    	}
	
}
};
//	ros::NodeHandle cm;
//	ros::Subscriber image = cm.subscribe("/usb_cam/output_video", 5, masking);



int main(int argc, char** argv)
{
  ros::init(argc, argv, "colourmasking");
  ImageConverter ic;
  ros::spin();
  return 0;
}





