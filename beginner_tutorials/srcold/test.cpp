#include "ros/ros.h"
#include "std_msgs/UInt16.h"

#include "std_msgs/String.h"
#include <sstream>

#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

    #include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{

   ros::init(argc, argv, "test");

   ros::NodeHandle m;
   ros::Publisher servo_pub = m.advertise<std_msgs::UInt16>("servo",500);

   ros::NodeHandle n;
   ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter",10);


   ros::Rate loop_rate(10);


   std_msgs::UInt16 angle;
   
  cv::Mat image;
  image = cv::imread("./src/beginner_tutorials/src/testcolour.png" , cv::IMREAD_COLOR);
  
  if(! image.data ) {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }


  namedWindow( "Display window", WINDOW_AUTOSIZE );
  imshow( "Display window", image );
  std::cout << image << std::endl;

   while(ros::ok())
      {
	namedWindow( "Display window", WINDOW_AUTOSIZE );
	imshow( "Display window", image );
		std_msgs::String msg;
		std::stringstream tt;


   	angle.data = 60;
	servo_pub.publish(angle);
	ros::Duration(1).sleep();


		tt << "angle should be 60";
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);

	
	angle.data = 120;
	servo_pub.publish(angle);
	ros::Duration(1).sleep();

		tt << "angle should be 120";
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);

	ros::spinOnce();

      }

   return 0;
}
