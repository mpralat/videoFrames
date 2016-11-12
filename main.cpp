#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


int main() {
    std::cout << "Hello, World!" << std::endl;

    cv::Mat image;
    image = cv::imread("/home/marta/Inne/fajne_hehehe/1.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    cv::waitKey(0);

    return 0;
}