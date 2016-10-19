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
    camParam->readFromXMLFile("filename");

    // read marker size if specified (default value -1)
    markerSize = -1;

    //Create the detector
    detector.setThresholdParams(7, 7);
    detector.setThresholdParamRange(2, 0);

    //Set the dictionary you want to work with, if you included option -d in command line
    //see dictionary.h for all types
    detector.setDictionary(
            "dictionaryName");//cml("-d") return the string after -d in the command line "example: ./program video.avi -d ARUCO", then, returns the string "ARUCO"
}

bool ArucoPositioner::update() {
    if (captureFrame()) {
        detectPosition();
        return true;
    }
    return false;
}

bool ArucoPositioner::captureFrame() {
    camera->grab();
    camera->retrieve(frame);
    return true;
}

bool ArucoPositioner::detectPosition() {
    // Ok, let's detect
    vector<aruco::Marker> markers = detector.detect(frame, *camParam, markerSize);

    // for each marker, print out its data
    for (unsigned int i = 0; i < markers.size(); i++) {
        cout << markers[i] << endl;
    }
}