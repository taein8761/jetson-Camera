#include "opencv2/opencv.hpp"
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;

int main() {
    string src = "nvarguscamerasrc sensor-id=0 ! "
                 "video/x-raw(memory:NVMM), width=(int)640, height=(int)360, "
                 "format=(string)NV12, framerate=(fraction)30/1 ! "
                 "nvvidconv flip-method=0 ! video/x-raw, "
                 "width=(int)640, height=(int)360, format=(string)BGRx ! "
                 "videoconvert ! video/x-raw, format=(string)BGR ! appsink";

    VideoCapture source(src, CAP_GSTREAMER);
    if (!source.isOpened()) {
        cout << "Camera error" << endl;
        return -1;
    }

    string dst1 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! "
                  "nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! "
                  "h264parse ! rtph264pay pt=96 ! "
                  "udpsink host=203.234.58.156 port=8001 sync=false";

    VideoWriter writer1(dst1, CAP_GSTREAMER, 0, 30, Size(640, 360), true);
    if (!writer1.isOpened()) {
        cerr << "Writer1 open failed!" << endl;
        return -1;
    }

    string dst2 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! "
                  "nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! "
                  "h264parse ! rtph264pay pt=96 ! "
                  "udpsink host=203.234.58.156 port=8002 sync=false";

    VideoWriter writer2(dst2, CAP_GSTREAMER, 0, 30, Size(640, 360), false);
    if (!writer2.isOpened()) {
        cerr << "Writer2 open failed!" << endl;
        return -1;
    }

    string dst3 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! "
                  "nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! "
                  "h264parse ! rtph264pay pt=96 ! "
                  "udpsink host=203.234.58.156 port=8003 sync=false";

    VideoWriter writer3(dst3, CAP_GSTREAMER, 0, 30, Size(640, 360), false);
    if (!writer3.isOpened()) {
        cerr << "Writer3 open failed!" << endl;
        return -1;
    }

    Mat frame, gray, binary;
    while (true) {
        // Start time measurement
        auto start = chrono::high_resolution_clock::now();
        
        source >> frame;
        if (frame.empty()) {
            cerr << "Frame empty!" << endl;
            break;
        }
        
        // Convert to grayscale
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // Apply binary thresholding
        threshold(gray, binary, 128, 255, THRESH_BINARY);

        // Write original frame to writer1
        writer1.write(frame);
        
        // Write binary frame to writer2
        writer2.write(binary);
        
        // Write grayscale frame to writer3
        writer3.write(gray);
        
        // End time measurement
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        
        // Output elapsed time to shell
        cout << "Execution time: " << elapsed.count() << " ms" << endl;

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
