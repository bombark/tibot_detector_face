/*
 * Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Modified by Felipe Gustavo Bombardelli <felipebombardelli@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http://www.opensource.org/licenses/bsd-license>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*====================================== HEADER =======================================*/

#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <tiobj.hpp>

using namespace cv;
using namespace std;

/*-------------------------------------------------------------------------------------*/



/*======================================  UTIL  =======================================*/

/*static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}*/

/*-------------------------------------------------------------------------------------*/



/*======================================  MAIN  =======================================*/

int main(int argc, const char *argv[]) {
	string fn_haar = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";

	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);

	char buf[64];
	Mat frame, _frame, face_resized;
	_frame.create( 480, 640, CV_8UC3 );
	while( scanf("%s", buf) ){
		FILE* fd = fopen("image", "r");
		fread( _frame.data, 1, 640*480*3, fd );
		fclose(fd);
		cvtColor( _frame, frame, CV_BGR2GRAY );

		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(frame, faces);


		//for(int i = 0; i < faces.size(); i++) {
		if ( faces.size() > 0 ){
			Rect face_i = faces[0];
			Mat face = frame(face_i);
			cv::resize(face, face_resized, Size(64, 64), 1.0, 1.0, INTER_CUBIC);
			//rectangle(_frame, face_i, CV_RGB(0, 255,0), 1);
			
			FILE* fd = fopen("face","w");
			fwrite( face_resized.data, 1, 64*64, fd);
			fclose(fd);
			
			TiObj info;
			info.set("x",faces[0].x);
			info.set("y",faces[0].y);
			info.set("cols",faces[0].width);
			info.set("rows",faces[0].height);
			info.saveFile("info");
		}

	}
	return 0;
}

/*-------------------------------------------------------------------------------------*/
