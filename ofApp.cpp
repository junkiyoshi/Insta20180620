#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 15);
	
	this->cap.open("D:\\video\\image2.mp4");
	this->cap_size = cv::Size(1280, 720);
	this->cap_image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
	this->cap_frame = cv::Mat(this->cap_image.getHeight(), this->cap_image.getWidth(), CV_MAKETYPE(CV_8UC3, this->cap_image.getPixels().getNumChannels()), this->cap_image.getPixels().getData(), 0);
}

//--------------------------------------------------------------
void ofApp::update() {

	cv::Mat origin;
	this->cap >> origin;
	if (origin.empty()) {

		this->cap.set(CV_CAP_PROP_POS_FRAMES, 1);
		return;
	}

	cv::resize(origin, this->cap_frame, this->cap_size);
	cv::cvtColor(this->cap_frame, this->cap_frame, CV_BGR2RGB);
	
	this->cap_image.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<string> word = { "A", "B", "C", "D", "E", "F","G", "H", "I", "J", "K", "L","M", "N", "O", "P", "Q", "R", "S", "T","U", "V", "W", "X", "Y", "Z" };

	for (int x = 0; x < this->cap_frame.cols; x += 15) {

		for (int y = 0; y < this->cap_frame.rows; y += 15) {

			ofColor color(this->cap_frame.at<cv::Vec3b>(y, x)[0], this->cap_frame.at<cv::Vec3b>(y, x)[1], this->cap_frame.at<cv::Vec3b>(y, x)[2]);
			ofSetColor(color);

			int moji_index = ofMap(color.getHue(), 0, 255, 0, word.size());
			this->font.drawString(word[moji_index], x, y);
		}
	}

	//this->cap_image.draw(0, 0);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}