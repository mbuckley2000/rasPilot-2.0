//
// Created by matt on 17/10/16.
//

#include "../include/PiCam.h"
#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <string>
#include "aruco/aruco.h"
#include "aruco/cvdrawingutils.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace aruco;
using namespace std;

PiCam::PiCam() {}
/*
int PiCam::capture() {
    raspicam::RaspiCam_Cv Camera;
    cv::Mat frame;
    //set camera params
    Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
    //Open camera
    cout<<"Opening Camera..."<<endl;
    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
    //Start capture
    cout<<"Capturing"<<endl;
    //while (true) {
        Camera.grab();
        Camera.retrieve (frame);
        cout << "Retrieved frame" << endl;
    //}
    cout<<"Stop camera..."<<endl;
    Camera.release();
    //save image
    //cv::imwrite("raspicam_cv_image.jpg",image);
    //cout<<"Image saved at raspicam_cv_image.jpg"<<endl;
}


int arucoCap() {
    try {
        CmdLineParser cml(argc,argv);
        if (argc <4 || cml["-h"] ){
            cerr << "Usage: video.avi  cameraParams.yml  markerSize [-d <dicionary>:ARUCO default] " << endl;
            cerr<<"\tDictionaries: "; for(auto dict:aruco::Dictionary::getDicTypes())    cerr<<dict<<" ";cerr<<endl;
            cout<<"Example to work with apriltags dictionary : video.avi -d TAG36h11"<<endl<<endl;
            return 0;
        }


        aruco::CameraParameters CamParam;

        // read the input image
        cv::Mat InImage;
        // Open input and read image
        VideoCapture vreader(argv[1]);
        if (vreader.isOpened()) vreader>>InImage;
        else{cerr<<"Could not open input"<<endl;return -1;}
        // read camera parameters if specifed
        CamParam.readFromXMLFile(argv[2]);
        CamParam.resize(InImage.size());
        // read marker size if specified (default value -1)
        float MarkerSize = std::stof(argv[3]);
        //Create the detector
        MarkerDetector MDetector;
        MDetector.setThresholdParams(7, 7);
        MDetector.setThresholdParamRange(2, 0);
        std::map<uint32_t,MarkerPoseTracker> MTracker;//use a map so that for each id, we use a different pose tracker
        //Set the dictionary you want to work with, if you included option -d in command line
        //see dictionary.h for all types
        if (cml["-d"])  MDetector.setDictionary( cml("-d"),0.f);

        do{
            vreader.retrieve(InImage);
            // Ok, let's detect
            vector< Marker >  Markers=MDetector.detect(InImage);
            for(auto & marker:Markers)//for each marker
                MTracker[marker.id].estimatePose(marker,CamParam,MarkerSize);//call its tracker and estimate the pose

            // for each marker, draw info and its boundaries in the image
            for (unsigned int i = 0; i < Markers.size(); i++) {
                cout << Markers[i] << endl;
                Markers[i].draw(InImage, Scalar(0, 0, 255), 2);
            }
            // draw a 3d cube in each marker if there is 3d info
            if (CamParam.isValid() && MarkerSize != -1){
                for (unsigned int i = 0; i < Markers.size(); i++) {
                    CvDrawingUtils::draw3dCube(InImage, Markers[i], CamParam);
                    CvDrawingUtils::draw3dAxis(InImage, Markers[i], CamParam);
                }
            }
            // show input with augmented information
            cv::namedWindow("in", 1);
            cv::imshow("in", InImage);
        } while( char(cv::waitKey(0))!=27 && vreader.grab()); // wait for esc to be pressed


        if (cml["-o"]) cv::imwrite(cml("-o"), InImage);
    } catch (std::exception &ex)

    {
        cout << "Exception :" << ex.what() << endl;
    }
}
 */
