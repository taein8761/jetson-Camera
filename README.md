카메라로부터 영상을 받아 그레이스케일영상과 이진영상으로변환 하여
원본영상,그레이영상,이진영상을 모두PC로 전송하여 출력, PC에서 3개의창이출력
PS C:\Users\Admin> gst-launch-1.0 -v udpsrc port=8001 ! ‘application/x-rtp,encoding-name=(string)H264,payload=(int)96’ ! rtph264depay ! queue ! avdec_h264 ! videoconvert! autovideosink
(포트를 8001,8002,8003 으로 창을 열어서 영상 3개 수신)

반복문안의 모든 코드들의 실행시간을 측정하여 리눅스 셸에 출력 (시간 측정 부분)
#include <chrono>
// Start time measurement
        auto start = chrono::high_resolution_clock::now();
        // End time measurement
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        // Output elapsed time to shell
        cout << "Execution time: " << elapsed.count() << " ms" << endl;
![image](https://github.com/user-attachments/assets/075fe785-da7e-456d-952c-0558a12024c0)
