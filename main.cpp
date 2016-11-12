#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <boost/algorithm/string.hpp>
#include <glob.h>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <boost/filesystem.hpp>

#undef BOOST_NO_CXX11_SCOPED_ENUMS


namespace fs = boost::filesystem;

std::string checkDirectory(std::string output_dir) {
    std::vector<std::string> strings;
    boost::split(strings, output_dir, boost::is_any_of("/"));
    if (fs::create_directory(fs::path(output_dir)))
        std::cerr << "Directory created! " << output_dir << std::endl;
    std::cout << strings[strings.size() - 3] << std::endl;
    return strings[strings.size() - 3];
}

void saveFrames(std::string fileName, std::string outputDir) {

    cv::Mat frame;
    cv::VideoCapture capture(fileName);
    if (!capture.isOpened())
        _exit(-1);

    std::string mainName = checkDirectory(outputDir);
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
        cv::imwrite(outputDir + mainName + "_" + fileName + "_" + std::to_string(i) + ".jpg", frame);
        frame.release();
    }
    capture.release();
}

int main(int argc, char *argv[]) {
    std::string main_directory;
    if (argc > 1)
        main_directory = argv[1];
    else {
        std::cout << "Please provide an input folder with avi files." << std::endl;
        _exit(-1);
    }

    fs::path input(main_directory);
//    Iterating through directories.
    for (auto i = fs::directory_iterator(input); i != fs::directory_iterator(); i++) {
        if (is_directory(i->path())) {
            fs::current_path(i->path());
            glob_t globbuf;
//            Getting all avi files from the dir.
            int err = glob("*.avi", 0, NULL, &globbuf);
            if (err == 0)
                for (size_t j = 0; j < globbuf.gl_pathc; j++) {
                    std::cout << globbuf.gl_pathv[j] << std::endl;
                    std::string outputDir = i->path().string() + "/frames/";
                    saveFrames(globbuf.gl_pathv[j], outputDir);
                }

            globfree(&globbuf);

        } else
            continue;
    }

    return 0;
}