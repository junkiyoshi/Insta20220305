#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetBackgroundAuto(false);

	// 配色デザイン ペールオレンジ P052
	this->color_palette.push_back(ofColor(245, 226, 197));
	this->color_palette.push_back(ofColor(249, 235, 199));
	this->color_palette.push_back(ofColor(235, 216, 183));
	this->color_palette.push_back(ofColor(242, 216, 194));
	this->color_palette.push_back(ofColor(208, 175, 131));
	this->color_palette.push_back(ofColor(220, 230, 233));
	this->color_palette.push_back(ofColor(199, 213, 188));
	this->color_palette.push_back(ofColor(253, 247, 225));
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < 2; i++) {

		this->palette_shuffle(this->color_palette);

		auto location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.035), 0, 1, 50, 670), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.035), 0, 1, 50, 670));
		auto scale = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.05), 0, 1, 1, 10);

		ofPushMatrix();
		ofTranslate(location);
		ofRotate(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.05), 0, 1, -360, 360));

		ofSetColor(color_palette[0]);
		ofFill();
		ofBeginShape();
		for (auto deg = 0; deg < 360; deg += 1) {

			ofVertex(this->make_point(deg * DEG_TO_RAD) * scale);
		}
		ofEndShape(true);

		ofSetColor(255);
		ofNoFill();
		ofBeginShape();
		for (auto deg = 0; deg < 360; deg += 1) {

			ofVertex(this->make_point(deg * DEG_TO_RAD) * scale);
		}
		ofEndShape(true);

		ofPopMatrix();
	}

	ofSetColor(0);
	ofFill();
	ofBeginShape();
	ofVertex(0, 0);
	ofVertex(ofGetWidth(), 0);
	ofVertex(ofGetWidth(), ofGetHeight());
	ofVertex(0, ofGetHeight());
	ofNextContour(true);
	ofVertex(50, 50);
	ofVertex(ofGetWidth() - 50, 50);
	ofVertex(ofGetWidth() - 50, ofGetHeight() - 50);
	ofVertex(50, ofGetHeight() - 50);
	ofEndShape(true);
}

//--------------------------------------------------------------
//Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
void ofApp::palette_shuffle(vector<ofColor>& color_palette) {

	for (int i = 0; i < color_palette.size(); i++) {

		int k = ofRandom(i, color_palette.size());
		ofColor tmp = color_palette[i];
		color_palette[i] = color_palette[k];
		color_palette[k] = tmp;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}