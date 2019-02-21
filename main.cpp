
#include <cstdlib>

#include "ArenaApi.h"
#include "opencv2/opencv.hpp"
#include "libterraclear/src/stopwatch.hpp"

namespace tc = terraclear;

int main()
{
    bool is_error = false;

    try
    {
        // get cameras
        Arena::ISystem* pSystem = Arena::OpenSystem();
        pSystem->UpdateDevices(100);            
        std::vector<Arena::DeviceInfo> deviceInfos = pSystem->GetDevices();

        if (deviceInfos.size() == 0)
        {
                std::cout << "No camera found!" << std::endl;
                return -1;
        }

        //connect to camera 0
        Arena::IDevice* pDevice = pSystem->CreateDevice(deviceInfos[0]);

        //set acquisition mode.
        Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode", "Continuous");

        //required pixel format.
        std::string pixel_format = "BayerRG8"; //YUV411_8_UYYVYY

        //get ptr to pixel format node item
        GenICam::gcstring current_format = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "PixelFormat");
        std::cout << "PixelFormat is " << current_format.c_str() << std::endl;

        std::cout << "Setting PixelFormat mode to " << pixel_format << std::endl;

        //set format
        Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "PixelFormat", pixel_format.c_str()); 

        //set buffer mode newest only.
        Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetTLStreamNodeMap(), "StreamBufferHandlingMode", "NewestOnly");

        std::cout << "Starting stream" << std::endl;
        pDevice->StartStream();

        //Create OpenCV Window
        char window_name[] = "Lucid";
        cv::namedWindow(window_name, cv::WINDOW_NORMAL | cv::WINDOW_FREERATIO | cv::WINDOW_AUTOSIZE);

        //timer
        tc::stopwatch sw2;
        sw2.start();
        uint64_t total_ms = 0;
        uint32_t cam_fps = 0;
        uint32_t frame_cnt = 0;
        float avg_ms = 0.0f;

        for (;;)
        {
            sw2.reset();

            //Get Image from Camera
            uint32_t timeout = 2000; //sec
            Arena::IImage* pImage = pDevice->GetImage(timeout);
                        
            //convert to BGR8
            Arena::IImage* pConverted = Arena::ImageFactory::Convert(pImage, BGR8);


            size_t width = pConverted->GetWidth();
            size_t height = pConverted->GetHeight();

            //Construct CV Mat
            cv::Mat cam_img(height, width, CV_8UC3, (void*)pConverted->GetData());

            //construct & paint fps and ms delay text.
            std::stringstream fpsstr;
            fpsstr << "fps: " << std::fixed << std::setprecision(0) << cam_fps << ", acquire:" << sw2.get_elapsed_ms() << "ms";
            cv::putText(cam_img, fpsstr.str(), cv::Point(10,50), cv::FONT_HERSHEY_PLAIN, 4,  cv::Scalar(0x00, 0x00, 0xff), 4);   

            //update onscreen img.
            cv::imshow(window_name, cam_img);

            //wait for Key and quit on ESC button
            int x = cv::waitKey(1);
            if(x == 27) //ESC = 27
            {
                break;       
            }

            //flush & queue same buffer
            pDevice->RequeueBuffer(pImage);
            
            //calc avg fps over 100 frames..
            frame_cnt++;
            total_ms += sw2.get_elapsed_ms();
            if (frame_cnt >= 100)
            {
                avg_ms = (float)total_ms / (float)frame_cnt;
                cam_fps = 1000.0f / avg_ms;
                frame_cnt = 0;
                total_ms = 0;

                std::cout << "fps:" << cam_fps << std::endl;
            }
        }

        //stop streaming & cleanup
        pDevice->StopStream();
        pSystem->DestroyDevice(pDevice);
        Arena::CloseSystem(pSystem);
    }
    catch (GenICam::GenericException& ge)
    {
            std::cout << "GenICam error: " << ge.what() << std::endl;
            is_error = true;
    }
    catch (std::exception& ex)
    {
            std::cout << "Std Error: " << ex.what() << std::endl;
            is_error = true;
    }
    catch (...)
    {
            std::cout << "Unknown Error" << std::endl;
            is_error = true;
    }

    if (is_error)
            return -1;
    else
            return 0;
}

