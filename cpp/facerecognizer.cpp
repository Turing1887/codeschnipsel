// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.


    This example is essentially just a version of the face_landmark_detection_ex.cpp
    example modified to use OpenCV's VideoCapture object to read from a camera instead
    of files.


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.
*/

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

#include <qDebug>

#include <cmath>

// include class header file
#include "facerecognizer.h"
#include "midiinput.h"

using namespace dlib;
using namespace std;

FaceRecognizer::FaceRecognizer()
    : emotion(0)
{
}


std::vector<image_window::overlay_line> FaceRecognizer::calculateOverlay(std::vector<full_object_detection> shapes) {

    std::vector<image_window::overlay_line> lines;

    for (unsigned long i = 0; i < shapes.size(); ++i)
    {
        DLIB_CASSERT(shapes[i].num_parts() == 68,
            "\t std::vector<image_window::overlay_line> render_face_detections()"
            << "\n\t Invalid inputs were given to this function. "
            << "\n\t shapes["<<i<<"].num_parts():  " << shapes[i].num_parts()
        );

        const full_object_detection& d = shapes[i];

        // lips outer part
        for (int i = 49; i < 59; ++i) {
            lines.push_back(dlib::image_window::overlay_line(d.part(i), d.part(i - 1), rgb_pixel(0,100,255)));
        }

        lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(59), rgb_pixel(255,0,125)));
        // end Lips outer Part

        // Lips inside part
        for (int i = 61; i <= 67; ++i) {
           lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), rgb_pixel(120,120,255)));
        }

        lines.push_back(dlib::image_window::overlay_line(d.part(60), d.part(67), rgb_pixel(255,0,0)));
        // end Lips inside Part

        // left eye
        for (int i = 37; i < 42; ++i) {
            lines.push_back(dlib::image_window::overlay_line(d.part(i), d.part(i - 1), rgb_pixel(0,100,255)));
        }

        lines.push_back(dlib::image_window::overlay_line(d.part(36), d.part(41), rgb_pixel(255,0,125)));
        // end left eye

        // right eye
        for (int i = 43; i <= 47; ++i) {
           lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), rgb_pixel(120,120,255)));
        }

        lines.push_back(dlib::image_window::overlay_line(d.part(42), d.part(47), rgb_pixel(255,0,0)));
        // end right eye

        // right eyeline
        for (int i = 23; i < 26; ++i) {
            lines.push_back(dlib::image_window::overlay_line(d.part(i), d.part(i - 1), rgb_pixel(0,100,255)));
        }

        // left eyeline
        for (int i = 19; i <= 21; ++i) {
           lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), rgb_pixel(120,120,255)));
        }

        lines.push_back(dlib::image_window::overlay_line(d.part(21), d.part(22), rgb_pixel(255,0,0)));
        // end left eyeline

         lines.push_back(dlib::image_window::overlay_line(d.part(27), d.part(27), rgb_pixel(0,0,0)));

        // read left and right point, WARUM 0,500???
        point upper = point(0,0);
        point lower = point(0,500);

        for(int i = 48; i < 68; i++) {
            if (d.part(i).y() < lower.y()){
                lower = d.part(i);
            }
            if (d.part(i).y() > upper.y()){
                upper = d.part(i);
            }
        }

         lines.push_back(dlib::image_window::overlay_line(d.part(21), d.part(27), rgb_pixel(0,0,0)));
         lines.push_back(dlib::image_window::overlay_line(d.part(22), d.part(27), rgb_pixel(0,0,0)));

         MIDIOutput midiOutput;
         // open output connection
         midiOutput.open("Microsoft GS Wavetable Synth");

         int channel = 0;
        //  int note = 60;
         int velocity = 127;
         


        //Mundhöhe
        // Vincent:
        // Neutral = 38 - 43
        // Zusammengezogen = 22 - 39
        // Hochgezogen = 140 - 150
        long mh = (upper-lower).length();
        //qDebug() << "Mundhöhe:";
        //qDebug() << mh;

        //Distanz Nasenmitte - Augenbrauen (l + r)
        // Vincent:
        // Neutral = 33 - 36
        // Zusammengezogen = 27 - 28
        // Hochgezogen = 54 - 56
        long nely = d.part(27).y() - d.part(21).y();
        long nery = d.part(27).y() - d.part(22).y();
        long nelx = d.part(27).x() - d.part(21).x();
        long nerx = d.part(27).x() - d.part(22).x();
        long distance_nel = sqrt(pow(nely, 2) + pow(nelx, 2));
        long distance_ner = sqrt(pow(nery, 2) + pow(nerx, 2));


        //qDebug() << "Nel:";
        //qDebug() << nely;
        //qDebug() << nelx;
        //qDebug() << distance_nel;
        //qDebug() << "Ner:";
        //qDebug() << distance_ner;

        //rechte Augenbraue - Höhe:
        long augr = d.part(25).y() - d.part(22).y();
        lines.push_back(dlib::image_window::overlay_line(d.part(22), d.part(25), rgb_pixel(0,0,0)));

        //linke Augenbraue - Höhe
        long augl = d.part(18).y() - d.part(21).y();
        lines.push_back(dlib::image_window::overlay_line(d.part(18), d.part(21), rgb_pixel(0,0,0)));


        //Midioutput of Eyebrows
        midiOutput.sendNoteOn(channel, augr%128, velocity);
        qDebug() << "Augl:";
        qDebug() << augr;
        qDebug() << "Augr:";
        qDebug() << augl;

        //Lippenhöhe
        //long lipheight = max(upper.y() - d.part(48).y(), upper.y() - d.part(54).y());

        //qDebug() << lipheight;

        /*
        if(mh/2 >= lipheight) {

            // neutral / traurig
            emotion = lipheight;
            lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(255,255,255)));
        } else {

            // glücklich
            emotion = 1;
            lines.push_back(dlib::image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(0,0,255)));
        }

        */
        //point secondPoint = point(100,100);
        //point firstPoint = d.part(50);
    }

    return lines;
}

int FaceRecognizer::getEmotion(){
    return emotion;
}
