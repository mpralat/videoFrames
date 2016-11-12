#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <boost/algorithm/string.hpp>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS

std::string output_dir = "/home/marta/Inne/Sponge/frames/";

using namespace boost::filesystem;

void saveFrames(cv::VideoCapture capture, std::string mainName) {
    cv::Mat frame;
    double frames = capture.get(CV_CAP_PROP_FRAME_COUNT);
    for (int i = 24; i < frames - 48; i += 240) {
        std::cout << i << std::endl;
//        Setting the frame pointer to each 240th frame, starting with the first one.
        capture.set(CV_CAP_PROP_POS_FRAMES, i);
        bool success = capture.read(frame);
        if (!success) {
            std::cout << "A wild problem with reading the frame appeared!" << std::endl;
            break;
        }
        std::cout << "nothing wrong, proceeding" << std::endl;
        cv::imwrite(output_dir + mainName + "_" + std::to_string(i) + ".jpg", frame);
    }
}

std::string checkDirectory(std::string output_dir) {
    std::vector<std::string> strings;
    boost::split(strings, output_dir, boost::is_any_of("/"));
    if (create_directory(path(output_dir)))
        std::cerr << "Directory created! " << output_dir << std::endl;
    return strings[strings.size() - 3];
}


int main() {
    std::string videoName = "/home/marta/Inne/Sponge/ep1_C.avi";

    cv::VideoCapture capture(videoName);
    if (!capture.isOpened())
        return -1;
    std::cout << "No errors!" << std::endl;

    saveFrames(capture, checkDirectory(output_dir));

    return 0;
}