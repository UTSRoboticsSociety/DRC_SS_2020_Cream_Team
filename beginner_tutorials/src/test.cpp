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

#include <iostream>
#include <array>
#include <math.h>
#include <string.h>

	using namespace cv;
	using namespace std;

	#define DEBUG
	//#define PRINT_IMG
	//#define TEST_IMG
	#define DISPLAY_IMG
	#define testturning
	#define camangle

	#define turnscaling 40
	#define turnoffset 10
	

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

//vertices for perspective transformation
#define topLeft 45,255
#define topRight 595,255
#define bottomLeft 0,275
#define bottomRight 640,275

void transform(Point2f*src_vertices, Point2f*dst_vertices, Mat& src, Mat &dst)
{
	Mat M = getPerspectiveTransform(src_vertices, dst_vertices);
	warpPerspective(src, dst, M, dst.size(), INTER_LINEAR, BORDER_CONSTANT);
}



int main(int argc, char **argv)
{
	//setup variable containers
	std::vector<int> points;
	std::vector<int> blueMidPoints;
	std::vector<int> yellowMidPoints;

	//setting up image transform objects
	
	//select points from source image
	Point2f src_vertices[4];
	src_vertices[0] = Point(topLeft);
	src_vertices[1] = Point(topRight);
	src_vertices[2] = Point(bottomLeft);
	src_vertices[3] = Point(bottomRight);

	//map points into a 640,480 window
	Point2f dst_vertices[4];
	dst_vertices[0] = Point(0,0);
	dst_vertices[1] = Point(640,0);
	dst_vertices[2] = Point(0,480);
	dst_vertices[3] = Point(640,480);
		
	Mat M = getPerspectiveTransform(src_vertices, dst_vertices);
	Mat dst(480, 640, CV_8UC3);
	

	//ROS setup
	ros::init(argc, argv, "test");
	
	ros::NodeHandle m;
	ros::Publisher servo_pub = m.advertise<std_msgs::UInt16>("servo",500);

	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter",10);

	ros::NodeHandle s;
	ros::Publisher speed_pub = s.advertise<std_msgs::UInt16>("motorspeed",500);


	ros::Rate loop_rate(60);


	std_msgs::UInt16 angle;
	std_msgs::UInt16 speed;

	//Image Read
	cv::Mat image;
		

	#ifdef return
		return 1;
	#endif
#ifndef TEST_IMG
		//video camera setup
		VideoCapture cap(0);
		//test if cam found
		if(!cap.open(-1)){
        		return 0;
		}	
#endif
	//Loop image, and recipricating servo angle and print angle size
	while(ros::ok())
	{
	//grabs image from camera imports into image

	#ifndef TEST_IMG

		cap >> image;
	#endif
	#ifdef TEST_IMG
		image = cv::imread("./src/beginner_tutorials/src/img278.jpg" , cv::IMREAD_COLOR); 
	#endif  

	if(! image.data ) {
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}

		#ifdef PRINT_IMG
			std::cout << image << std::endl;
		#endif
	
		/*decode apply colour mask (exmaple of this done in matlab copy out simliar for and it statements*/
		//get sizes
		//setup variables
		
		int r;
		int c;
		int d = 3;
		
		//import data with opencv
		r = image.rows;
		c = image.cols;

		#ifdef DEBUG
		std::cout << "rows: " << r << std::endl;
		std::cout << "cols: " << c << std::endl;
		#endif

		//Set up referece img

		//Mat mask(r, c, CV_8UC3, Scalar(0, 0, 0));
		//r = image.rows;
		//c = image.cols;
#ifdef DISPLAY_IMG		
		cv::imshow("window", image);
		cv::waitKey(1);
		
		Mat OutputImage;
		inRange(image,Scalar(b_blower,b_glower,b_rlower),Scalar(b_bupper,b_gupper,b_rupper),OutputImage);

		//adding lines
		for(int i = 0; i < c; i++)
		{
			OutputImage.at<Vec3b>(250,i) = 255;
			OutputImage.at<Vec3b>(310,i) = 255;
			OutputImage.at<Vec3b>(370,i) = 255;
		}
			

		imshow("Blue Detection", OutputImage);
		waitKey(10);

		
		inRange(image,Scalar(y_blower,y_glower,y_rlower),Scalar(y_bupper,y_gupper,y_rupper),OutputImage);

		//adding lines
		for(int i = 0; i < c; i++)
		{
			OutputImage.at<Vec3b>(250,i) = 255;
			OutputImage.at<Vec3b>(310,i) = 255;
			OutputImage.at<Vec3b>(370,i) = 255;

		}
			

		imshow("Yellow Detection", OutputImage);
		waitKey(9);
		
		//Perspective Transform		
		warpPerspective(image, dst, M, dst.size(), INTER_LINEAR, BORDER_CONSTANT);
		imshow("dst", dst);

#endif

#ifdef USE_PERSPECTIVE
	image = dst;
#endif

		#ifdef DEFINE
		std::cout << "mask: \n" << mask << std::endl;
		std::cout << "rows: " << r << std::endl;
		std::cout << "cols: " << c << std::endl;
		#endif


		//search through the rows
		Vec3b pixelRGB;
		double RBG[3];
		double red, green, blue;
				
		
		//setup variable for mid point
		int midpoint;
	
		for(int k = 0; k < 3; k++)
		{
/**************************************************YELLOW********************************************************************/
			//hit iterator yellow

			points.clear();
			int row = (k * 60)+250;
			for (int i = 1; i <= r; i++)
			{
	
				//will scan across row 100
				pixelRGB = image.at<Vec3b>(row,i);
				red = pixelRGB.val[2];
				green = pixelRGB.val[1];
				blue = pixelRGB.val[0];
				#ifdef DEBUG
					//std::cout << "Red:"<<red<<" Green:"<<green<<" Blue:"<<blue<<" At"<<i<<","<<row<<std::endl;
				#endif
	
				//  tests of pixels are within value range (this tests for one color)
				if(red < y_rupper && red > y_rlower){
					if(green < y_gupper && green > y_glower){
						if(blue < y_bupper && blue > y_blower){
								
							//found target color
							points.push_back(i);		
							
						}
					}
				}			
			}


			//find and record mid point
			midpoint = points.size() / 2;
			if(midpoint == 0){
				midpoint = c/2.0;
				yellowMidPoints.push_back(midpoint);

				#ifdef DEBUG
					std::cout<<"no yellow found"<<std::endl;
				#endif
			}
			else if(points.at(midpoint) > c/2){
				midpoint = c;
				yellowMidPoints.push_back(midpoint);

				#ifdef DEBUG
					std::cout<<"   yellow found OVERSHOT"<<std::endl;
				#endif
			}
			else{
				yellowMidPoints.push_back(points.at(midpoint));
				#ifdef DEBUG
					std::cout<<"   yellow found"<<std::endl;
				#endif
			}
/*****************************************************************BLUE***************************************************************/
			//hit iterator blue

			points.clear();
			//int row = (k * 60)+250;
			for (int i = 1; i <= r; i++)
			{
	
				//will scan across row 100
				pixelRGB = image.at<Vec3b>(row,i);
				red = pixelRGB.val[2];
				green = pixelRGB.val[1];
				blue = pixelRGB.val[0];
				#ifdef DEBUG
					//std::cout << "Red:"<<red<<" Green:"<<green<<" Blue:"<<blue<<" At"<<i<<","<<row<<std::endl;
				#endif
	
				//  tests of pixels are within value range (this tests for one color)
				if(red < b_rupper && red > b_rlower){
					if(green < b_gupper && green > b_glower){
						if(blue < b_bupper && blue > b_blower){
								
							//found target color
							points.push_back(i);		
							
						}
					}
				}			
			}

			//find and record mid point
			midpoint = points.size() / 2;
			if(midpoint == 0){
				midpoint = c/2.0;
				blueMidPoints.push_back(midpoint);

				#ifdef DEBUG
					std::cout<<"no blue found"<<std::endl;
				#endif
			}
			else if(points.at(midpoint) < c/2){
				midpoint = c;
				blueMidPoints.push_back(midpoint);

				#ifdef DEBUG
					std::cout<<"   blue found OVERSHOT"<<std::endl;
				#endif
			}
			else{
				blueMidPoints.push_back(points.at(midpoint));
				#ifdef DEBUG
					std::cout<<"   blue found"<<std::endl;
				#endif
			}
			for(int i = 0; i < blueMidPoints.size(); i++)
			{
				std::cout<<"b mid point num"<<i<<" is:"<<blueMidPoints.at(i)<<std::endl;
			}

			for(int i = 0; i < yellowMidPoints.size(); i++)
			{
				std::cout<<"y mid point num"<<i<<" is:"<<yellowMidPoints.at(i)<<std::endl;
			}
	
		//end line for loop it here
		}
		//process the colours into an angle

#ifdef testturning
		int sendturn;
		double midPixel = c/2.0;

		double offsetavgBlue = 0;
		double offsetavgYellow = 0;
		int sum = 0;
//getting avg for blue
		for(std::vector<int>::iterator it = blueMidPoints.begin(); it != blueMidPoints.end(); ++it)
		{
			sum += *it;
		}
		offsetavgBlue = sum / blueMidPoints.size();
//getting avg for yellow
		for(std::vector<int>::iterator it = yellowMidPoints.begin(); it != yellowMidPoints.end(); ++it)
		{
			sum += *it;
		}
		//offsetavgYellow = sum / yellowMidPoints.size();

std::cout << "Offsetavg is: "<<offsetavgBlue<<std::endl;


		double ratioOffset = (double) offsetavgBlue / midPixel;
		std::cout<<"Ratio Offset is: "<<ratioOffset<<std::endl;

		//turning 
		sendturn = turnscaling * ratioOffset + turnoffset;
		std::cout<<"desired blue angle to send:"<<sendturn<<std::endl;



		
#endif

		//done processing clear midpoints
		blueMidPoints.clear();
		yellowMidPoints.clear();
		// send to ROS

		std_msgs::String msg;
		std::stringstream tt;
		int delay = 1;

		//Setting servo angle and motor speed

#ifdef camangle		
		//Sending angle data over ROS
		angle.data = sendturn;
		servo_pub.publish(angle);
		//ros::Duration(0.5).sleep();

		tt << "angle should be: "<<angle.data<<std::endl;
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);
		//ros::Duration(0.5).sleep();
		
#endif

		speed.data = 175;
		speed_pub.publish(speed);
		//ros::Duration(delay).sleep();

		tt << "Speed: "<<speed.data<<std::endl;
		msg.data = tt.str();
		ROS_INFO("%s",msg.data.c_str());
		chatter_pub.publish(msg);


//		ros::shutdown();
		ros::spinOnce();

	}

	return 0;
}
