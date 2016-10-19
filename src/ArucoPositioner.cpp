//
// Created by matt on 19/10/16.
//

#include "../include/ArucoPositioner.h"

ArucoPositioner::ArucoPositioner(raspicam::RaspiCam_Cv *camera, aruco::CameraParameters *camParam) :
        camera(camera),
        camParam(camParam) {}

double ArucoPositioner::getPosX() {
    return posX;
}

double ArucoPositioner::getPosY() {
    return posY;
}

double ArucoPositioner::getPosZ() {
    return posZ;
}

bool ArucoPositioner::initialise() {
    cout << "Connecting to camera" << endl;
    if (!camera->open()) {
        cerr << "Error opening camera" << endl;
        return -1;
    }
    cout << "Connected to camera =" << camera->getId() << endl;

    // read camera parameters if specifed
    camParam->readFromXMLFile("../out_camera_calibration.yml");

    // read marker size if specified (default value -1)
    markerSize = 0.035;

    //Create the detector
    detector.setThresholdParams(7, 7);
    detector.setThresholdParamRange(2, 0);

    //Set the dictionary you want to work with, if you included option -d in command line
    //see dictionary.h for all types
    detector.setDictionary(
            "ARUCO_MIP_36h12");//cml("-d") return the string after -d in the command line "example: ./program video.avi -d ARUCO", then, returns the string "ARUCO"
}

bool ArucoPositioner::update() {
    if (captureFrame()) {
        if (detectMarkers()) {
            return calculatePosition();
        }
    }
    return false;
}

bool ArucoPositioner::captureFrame() {
    camera->grab();
    camera->retrieve(frame);
    return true;
}

bool ArucoPositioner::detectMarkers() {
    // Ok, let's detect
    //std::cout << "Attempting detect" << std::endl;



    *markers = detector.detect(frame, *camParam, markerSize);

    // for each marker, print out its data
    for (unsigned int i = 0; i < markers->size(); i++) {
        cout << "MARKER: " << (*markers)[i] << endl;
    }

    if (markers->size() != 0) {
        cv::imwrite("im.jpg", frame);
        return true;
    }

    return false;
}

bool ArucoPositioner::calculatePosition() {
    //So we have our vector of markers: markers

    return false;
}