#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <boost/algorithm/string.hpp>
#include <glob.h>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <boost/filesystem.hpp>

#undef BOOST_NO_CXX11_SCOPED_ENUMS


namespace fs = boost::filesystem;

void checkDirectory(std::string output_dir) {
    if (fs::create_directory(fs::path(output_dir)))
        std::cerr << "Directory created! " << output_dir << std::endl;
}

void saveFrames(std::string fileName, std::string outputDir) {

    cv::Mat frame;
    cv::VideoCapture capture(fileName);
    if (!capture.isOpened())
        _exit(-1);

    checkDirectory(outputDir);
//    Getting a frame each two seconds (it's roughly 24fps).
    double frames = capture.get(CV_CAP_PROP_FRAME_COUNT);
    for (int i = 48; i < frames - 48; i += 240) {
//        Setting the frame pointer to each 240th frame, starting with the first one.
        capture.set(CV_CAP_PROP_POS_FRAMES, i);
        bool success = capture.read(frame);
        if (!success) {
            std::cout << "A wild problem with reading the frame appeared!" << std::endl;
            break;
        }
        cv::imwrite(outputDir + fileName + "_" + std::to_string(i) + ".jpg", frame);
        frame.release();
    }
    capture.release();
}

int main(int argc, char *argv[]) {
    std::string main_directory = "/home/marta/Inne/videos/";
    if (argc > 1)
        main_directory = argv[1];
    else {
        std::cout << "Please provide an input folder with avi files." << std::endl;
        _exit(-1);
    }

    fs::path input(main_directory);
    std::string outputDir = main_directory + "frames/";
//    Iterating through directories.
    for (auto i = fs::directory_iterator(input); i != fs::directory_iterator(); i++) {
        if (is_directory(i->path())) {
            fs::current_path(i->path());
            glob_t globbuf;
            std::vector<const char *> extensions = {"*.avi", "*.mp4"};
            for (auto ext : extensions){
                int err = glob(ext, 0, NULL, &globbuf);
                if (err == 0)
                    for (size_t j = 0; j < globbuf.gl_pathc; j++) {
                        std::cout << globbuf.gl_pathv[j] << std::endl;
                        saveFrames(globbuf.gl_pathv[j], outputDir);
                    }
            }

            globfree(&globbuf);

        } else
            continue;
    }

    return 0;
}