#include <opencv2/highgui.hpp>
#include <iostream>
#include <iostream>

using namespace cv;
using namespace std;
 
int main( int argc, char** argv ) {
  
  Mat image;
  image = imread("testcolour.png" , CV_LOAD_IMAGE_COLOR);
  
  if(! image.data ) {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }
  
  cout << ("hekki world\n") <<endl;

  Point P1 = Point(2,2);
cout << P1 << endl;

Vec3b tense = image.at<Vec3b>(2,2);
double lol[3] = {tense.val[0], tense.val[1], tense.val[2]};
  cout << lol[0]<< lol[1]<< lol[2] << endl;
double a = 0.2223234;

cout << a << endl;

  namedWindow( "Display window", WINDOW_AUTOSIZE );
  imshow( "Display window", image );
  
  waitKey(0);
  return 0;
}
