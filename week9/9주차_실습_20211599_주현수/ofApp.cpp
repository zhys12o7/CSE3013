#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    
    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5);

    //keypressed함수에서 draw_flag가 set된 경우
    if( draw_flag ){
        int i;

        //줄 그리기
        for (i = 0; i < num_of_line; i++) {
            ofDrawLine(linearr[i].x1, linearr[i].y1, linearr[i].x2, linearr[i].y2);
        }
  
        //점 그리기
        for (i = 0; i < num_of_dot; i++) {
            
            ofSetColor(0);

            if (dotarr[i].color == 0) {
                ofSetColor(0);
            }
            if (dotarr[i].color == 1) {
                ofSetColor(255, 0, 0);
            }
            ofDrawCircle(dotarr[i].x1, dotarr[i].y1, 10);

        }
        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */

        
        
        // 2nd week portion.
        ofSetLineWidth(2);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){
        // Reset flags
        draw_flag = 0;
        
        // Free the dynamically allocated memory exits.
        
        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return;
        draw_flag = 1;
        
        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
    }
    if (key == 's'){
        // 2nd week portion.
    }
    if (key == 'e'){
        // 2nd week portion.
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 'l'){
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");
        
        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            
            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }
    
    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */

    //맨 처음 점에서 시작하기 떄문에 color를 빨간색으로 설정
    dotarr[now].color = 1;
    if (key == OF_KEY_RIGHT){
        
        //현재 점의 위치 now
    
        //움직이기 전 점 색깔 검은색
        dotarr[now].color = 0; 
        //움직이는 중
        now++;
        now = now % num_of_dot;
        //움직인 후 점 색깔 빨간색
        dotarr[now].color = 1;

        cout << "Selcted Dot Coordinate is (" << dotarr[now].x1 << ", " << dotarr[now].y1 << ")" << endl;
    }
    if (key == OF_KEY_LEFT){
        
        //현재 점의 위치 now
      
        //움직이기 전 점 색깔 검은색
        dotarr[now].color = 0;
        //움직이는 중
        now--;
        now = (now+num_of_dot) % num_of_dot;
        //움직인 후 점 색깔 빨간색
        dotarr[now].color = 1;

        cout << "Selcted Dot Coordinate is (" << dotarr[now].x1 << ", " << dotarr[now].y1 << ")" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    
    ofBuffer buffer(file);
    
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;
    int k = 0;
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
    
    
    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
        //선분의 수와 점의 수를 받을 경우
        if( words.size() == 1){
            
            
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
                
                //줄의 갯수 만큼 동적할당받기
                linearr = new Data[num_of_line];

            }
            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;

                //점의 갯수만큼 동적할당받기
                dotarr = new Data[num_of_dot];
            }
        }

        //선분이나 줄의 정보를 받을 때
        else if (words.size() >= 2){
            int x1,y1,x2,y2;

            //줄
            if( input_type == 0){ // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());

                //좌표가 screen을 넘어갈 경우 오류메시지
                if (x1 < 0 || x1>1024 || x2 < 0 || x2>1024 || y1 <= 0 || y1>768 || y2 <= 0 || y2>768)
                {
                    cout << "error" << endl;
                }
                //멀쩡하게 받은 경우 전역변수로 선언된 배열에 할당
                else {
                    linearr[k].x1 = x1;
                    linearr[k].x2 = x2;
                    linearr[k].y1 = y1;
                    linearr[k].y2 = y2;
                    k++;
                    //받은 배열의 개수가 line수랑 같으면 점을 받을 준비를 한다.
                    if (k == num_of_line) {
                        input_type = 1;
                        k = 0;
                    }
                }
            }

            


            //점
            else{ // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());

                //좌표가 screen을 넘어갈 때
                if (x1 < 0 || x1>1024 || y1 <= 0 || y1>768 )
                {
                    cout << "error" << endl;
                }
                //멀쩡하게 받은 경우, 전역변수로 선언된 배열에 할당
                else {
                    dotarr[k].x1 = x1;
                    dotarr[k].y1 = y1;
                    k++;
                }
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
    
    //initializeWaterLines();
}

void ofApp::initializeWaterLines() {
    ;
}


