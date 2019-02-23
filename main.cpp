
#include <unistd.h>
#include <iostream>
#include <sstream> 

//opencv
#include "opencv2/opencv.hpp"

//libterraclear
#include "libterraclear/src/stopwatch.hpp"

#ifndef TC_USE_TRITON
    #define TC_USE_TRITON
#endif
#include "libterraclear/src/camera_lucid_triton.hpp"

namespace tc = terraclear;

int main()
{
  
    char window_name[] = "LUCID";
    tc::camera_lucid_triton poe_cam;
    
    //Create OpenCV Window & set frame ref
    cv::namedWindow(window_name, cv::WINDOW_NORMAL | cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);
    cv::Mat cam_img = poe_cam.getRGBFrame();

    uint32_t retry_count = 0;
    while (true)
    {
        if (retry_count > 10)
            return -1;
        
        poe_cam.update_frames();
        cam_img = poe_cam.getRGBFrame();
        if ((cam_img.rows > 0) && (cam_img.cols > 0))
        {
            break;
        }
        else
        {
            retry_count ++;
            usleep(250000);
        }
        std::cout << "." << std::flush;
    }
    std::cout << std::endl;

    //timer
    tc::stopwatch sw2;
    sw2.start();
    uint64_t total_ms = 0;
    uint32_t cam_fps = 0;
    uint32_t frame_cnt = 0;
    float avg_ms = 0.0f;

    //camera loop..
    for ( ;; )
    {
        //grab image from FLIR stack..
        sw2.reset();
        poe_cam.update_frames();

        //construct & paint fps and ms delay text.
        std::stringstream fpsstr;
        fpsstr << "fps: " << std::fixed << std::setprecision(0) << cam_fps << ", frame lag:" << avg_ms << "ms";
        cv::putText(cam_img, fpsstr.str(), cv::Point(10,50), cv::FONT_HERSHEY_PLAIN, 4,  cv::Scalar(0x00, 0x00, 0xff), 4);   

        //update onscreen img.
        cv::imshow(window_name, cam_img);

        //wait for Key and quit on ESC button
        int x = cv::waitKey(1);
        if(x == 27) //ESC = 27
        {
            break;       
        }        
        
        //calc avg fps over 100 frames..
         frame_cnt++;
         total_ms += sw2.get_elapsed_ms();            
         if (frame_cnt >= 60)
         {
             avg_ms = (float)total_ms / (float)frame_cnt;
             cam_fps = 1000.0f / avg_ms;
             frame_cnt = 0;
             total_ms = 0;

             std::cout << "fps:" << cam_fps << std::endl;
         }

    }    
    
    return 0;
}

