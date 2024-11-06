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

//#include <sys/time.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sys/time.h>

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
    struct timeval start, end;

    while (true) {
        gettimeofday(&start, NULL); // 시작 시간 저장

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

        gettimeofday(&end, NULL); // 종료 시간 저장

        // 실행 시간 계산 (초 단위)
        double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        
        // 실행 시간 출력 (밀리초 단위)
        cout << "Execution time: " << elapsedTime * 1000 << " ms" << endl;

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
