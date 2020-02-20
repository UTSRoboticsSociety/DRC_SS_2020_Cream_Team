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

	//#define DEBUG

//define colours
#define redupper 100
#define redlower 50
#define greenupper 150
#define greenlower 100
#define blueupper 250
#define bluelower 150

	int main(int argc, char **argv)
	{
		//ROS setup
		ros::init(argc, argv, "test");
	
		ros::NodeHandle m;
		ros::Publisher servo_pub = m.advertise<std_msgs::UInt16>("servo",500);

		ros::NodeHandle n;
		ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter",10);

		ros::NodeHandle s;
		ros::Publisher speed_pub = s.advertise<std_msgs::UInt16>("motorspeed",500);


		ros::Rate loop_rate(10);


		std_msgs::UInt16 angle;
		std_msgs::UInt16 speed;

		//Image Read
		//video camera setup
		VideoCapture cap(0);
		//test if cam found
		if(!cap.open(-1)){
        		return 0;
	}

	//grabs image from camera imports into image
	cv::Mat image;
	cap >> image;

	//  image = cv::imread("./src/beginner_tutorials/src/testcolour.png" , cv::IMREAD_COLOR);
  
	if(! image.data ) {
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}



#ifdef return
return 1;
#endif

	//Loop image, and recipricating servo angle and print angle size
	while(ros::ok())
	{
		//import images
//		cap >> image;

		#ifdef DEBUG
			std::cout << image << std::endl;
		#endif
	
		/*decode apply colour mask (exmaple of this done in matlab copy out simliar for and it statements*/
		//get sizes
		//setup variables
		
		int r;
		int c;
		int d = 3;
		
		//import data with opencv
//		r = image.rows;
//		c = image.cols;

		#ifdef DEBUG
		std::cout << "rows: " << r << std::endl;
		std::cout << "cols: " << c << std::endl;
		#endif

		//Set up referece img
		/*Mat mask(r, c, CV_8UC3, Scalar(0, 0, 0));
		r = image.rows;
		c = image.cols;
		
		#ifdef DEBUG
		std::cout << "mask: \n" << mask << std::endl;
		std::cout << "rows: " << r << std::endl;
		std::cout << "cols: " << c << std::endl;
		#endif


		//search through the rows
		Vec3b pixelRGB;
		double RBG[3];
		double red, green, blue;
		int i, j;		
		for (i = 0; i <= r; i++){
		//search through the col
			for (j = 0; j<= 20; j++){
				pixelRGB = image.at<Vec3b>(i,j);
//				RBG[3] = {pixelRGB.val[0], pixelRGB.val[1], pixelRGB.val[2]};
				red = pixelRGB.val[0];
				green = pixelRGB.val[1];
				blue = pixelRGB.val[2];

		/*		if(red < redupper && red > redlower){
					if(green < greenupper && green > greenlower){
						if(blue < blueupper && blue > bluelower){
							
							}
							
						}
					}
				}
			}
		}
		
				j = 0;
				//for (i = 0; i <= c; i++){
					//if (mask(201,i,1)>1){
						j = j + 1;
				
					//}
				//}
			}
		}



				
	*/

		//process the colours into an angle
		
		
		// send to ROS

		std_msgs::String msg;
		std::stringstream tt;

		//Setting servo angle and motor speed

   		angle.data = 0;
		servo_pub.publish(angle);
		ros::Duration(2).sleep();

		tt << "angle should be 0";
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);

		speed.data = 50;
		speed_pub.publish(speed);
		ros::Duration(2).sleep();

		tt << "speed set to 80";
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);

		angle.data = 90;
		servo_pub.publish(angle);
		ros::Duration(2).sleep();

		tt << "angle should be 90";
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);

		speed.data = 100;
		speed_pub.publish(speed);
		ros::Duration(2).sleep();

		tt << "speed set to 150";
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);

		/*
		angle.data = 60;
		servo_pub.publish(angle);
		ros::Duration(2).sleep();

		tt << "angle should be 120";
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);
		*/

//		ros::shutdown();
ros::spinOnce();

	}

	return 0;
}
