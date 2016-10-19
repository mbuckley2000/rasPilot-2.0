//
// Created by matt on 19/10/16.
//

#ifndef RASPILOT_2_0_ARUCOPOSITIONER_H
#define RASPILOT_2_0_ARUCOPOSITIONER_H

#include <raspicam/raspicam_cv.h>
#include <aruco/aruco.h>
#include <vector>


class ArucoPositioner {

public:
    ArucoPositioner(raspicam::RaspiCam_Cv *camera, aruco::CameraParameters *camParam);

    double getPosX();

    double getPosY();

    double getPosZ();

    bool initialise();

    bool update();

private:
    raspicam::RaspiCam_Cv *camera;
    aruco::CameraParameters *camParam;
    aruco::MarkerDetector detector;
    cv::Mat frame;
    vector<aruco::Marker> *markers;

    double posX, posY, posZ;
    float markerSize;

    bool captureFrame();

    bool detectMarkers();

    bool calculatePosition();
};

#endif //RASPILOT_2_0_ARUCOPOSITIONER_H