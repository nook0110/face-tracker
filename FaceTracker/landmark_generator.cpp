#include "app.h"

void App::RecognizeLandmarks() {

    // Get frame
    cv::Mat frame;
    capture_.read(frame);
    cv::resize(frame, frame, cv::Size(frameWidth_, frameHeight_));
    // Inference
    cv::Mat all_faces;
    face_detector_->detect(frame, all_faces);
    cv::Mat face = BiggestFace(all_faces);
    std::vector<std::vector<cv::Point2f>> landmarks;
    cv::Mat grey;
    cvtColor(frame, grey, cv::COLOR_BGR2GRAY);

    landmark_detector_->fit(grey, face.at<cv::Mat>(0), landmarks);
    facial_points_.push(landmarks[0]);

}


//This func finds biggest face of all in the frame
cv::Mat BiggestFace(cv::Mat faces) {
    int right_face = 0;
    int max_height = 0;
    for (int face = 0; face < faces.rows; face++) {
        int height = int(faces.at<float>(face, 0)) - int(faces.at<float>(face, 2));
        if (height > max_height) {
            right_face = face;
            max_height = height;
        }
    }
    return faces.at<cv::Mat>(right_face);
}
