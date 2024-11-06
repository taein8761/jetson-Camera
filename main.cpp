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

    VideoWriter wr작
        auto start = chrono::high_resolution_clock::now();
        
        source >> frame;
        if (frame.empty()) {
            cerr << "Frame empty!" << endl;
            break;
        }
        
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        // 이진화
        threshold(gray, binary, 128, 255, THRESH_BINARY);
        
        writer1.write(frame);
        
        writer2.write(binary);
        
        writer3.write(gray);
        
        // 시간 측정 종료
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        
        // 측정한 시간 표시
        cout << "Execution time: " << elapsed.count() << " ms" << endl;

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
