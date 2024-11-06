카메라로부터 영상을 받아 그레이스케일영상과 이진영상으로변환 하여
원본영상,그레이영상,이진영상을 모두PC로 전송하여 출력, PC에서 3개의창이출력

반복문안의 모든 코드들의 실행시간을 측정하여 리눅스 셸에 출력 (시간 측정 부분)
#include <chrono>
// Start time measurement
        auto start = chrono::high_resolution_clock::now();
        // End time measurement
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        // Output elapsed time to shell
        cout << "Execution time: " << elapsed.count() << " ms" << endl;
