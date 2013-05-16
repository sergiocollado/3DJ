//
//  CMenuViewController.cpp
//  3DJ
//
//  Created by Sam Ruberti on 9/2/12.
//

#include "CMenuViewController.h"
#include "CWorld.h"

CMenuViewController::CMenuViewController(int red, int green, int blue, int alpha )
{
    m_datapool = &CDataPool::getInstance();
    m_r = red;
    m_g = green;
    m_b = blue;
    m_a = alpha;
    m_exitMenu = false;

    initViews();
    setupDelegates(); //adds ofAddListener for each ofxUICanvas in views
    hideAllViews(); //hide all views at start
    m_loopEditor->showCanvases(true); //show loop editor window at start
    showMenuView(true); //Start with menu
    
    m_bg.loadImage("textures/scratch_tile.png");
}

CMenuViewController::~CMenuViewController()
{
    delete m_menu;
    delete m_loopEditor;
    delete m_calibrationEditor;
    delete m_datapool;
}

void CMenuViewController::initViews()
{
    m_menu = new CMenuView;
    m_loopEditor = new CLoopEditorView();
    m_calibrationEditor = new CalibrationView();

}

void CMenuViewController::menuEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();

    //Main Menu
    if(name == "START SESSION"){
        static string val = "testThread"; // for testing the datapool communicating between threads
        CDataPool::getInstance().createRef("testDataPool", &val);
        m_exitMenu = true;
        hideAllViews();
        g_currentState = ST_BOX_STATE;
    }else if(name == "SETS"){
        m_loopEditor->showCanvases(true);
        m_calibrationEditor->m_canvas1->setVisible(false);
    }else if(name == "GET SOUNDS"){
        m_loopEditor->showCanvases(false);
        m_calibrationEditor->m_canvas1->setVisible(false);
    }else if(name == "HELP"){
        m_loopEditor->showCanvases(false);
        m_calibrationEditor->m_canvas1->setVisible(false);
    }else if(name == "SAVE SETUP"){
        string saveFileName = "config.3dj";
        CDataPool::getInstance().saveToFile( saveFileName );
    }
}

void CMenuViewController::loopEditorEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();

    //=============================== Radio Buttons  File Load
    if(name == "A1"){
        saveRadioButtonInfo(name);
    }else if(name == "A2"){
        saveRadioButtonInfo(name);
    }else if(name == "A3"){
        saveRadioButtonInfo(name);
    }else if(name == "A4"){
        saveRadioButtonInfo(name);
    }else if(name == "B1"){
        saveRadioButtonInfo(name);
    }else if(name == "B2"){
        saveRadioButtonInfo(name);
    }else if(name == "B3"){
        saveRadioButtonInfo(name);
    }else if(name == "B4"){
        saveRadioButtonInfo(name);
    }else if(name == "C1"){
        saveRadioButtonInfo(name);
    }else if(name == "C2"){
        saveRadioButtonInfo(name);
    }else if(name == "C3"){
        saveRadioButtonInfo(name);
    }else if(name == "C4"){
        saveRadioButtonInfo(name);
    }
    //=============================== Matrix Sound Player

    else if(name == "Matrix A"){
        ofxUIToggleMatrix *mat = (ofxUIToggleMatrix *) e.widget;
        //Get toggles() ???
        //Loop sample
    }
    
}

void CMenuViewController::visualEditorEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();

    if(name == "") {

    }else if(name == ""){

    }
}

void CMenuViewController::setupDelegates()
{
    ofAddListener(m_loopEditor->m_canvas2->newGUIEvent, this, &CMenuViewController::loopEditorEvent);
    ofAddListener(m_menu->m_canvas1->newGUIEvent, this, &CMenuViewController::menuEvent);
    ofAddListener(m_loopEditor->m_canvas1->newGUIEvent, this, &CMenuViewController::loopEditorEvent);

}

void CMenuViewController::showMenuView(bool _showMenuView)
{
    if(_showMenuView){
        m_menu->m_canvas1->setVisible(_showMenuView);
    }else {
        //hideallViews();
    }
}

void CMenuViewController::hideAllViews()
{
    m_menu->m_canvas1->setVisible(false);
    m_loopEditor->m_canvas1->setVisible(false);
    m_loopEditor->m_canvas2->setVisible(false);
    m_calibrationEditor->m_canvas1->setVisible(false);
}

bool CMenuViewController::draw()
{
    int h = m_bg.height;
    int w = m_bg.width;
    for (int x = 0; x < ofGetScreenWidth(); x += w) {
        for (int y = 0; y < ofGetScreenHeight(); y += h ) {
            m_bg.draw(x,y);
        }
        
    }
    showMenuView(true);
    return true;
}

void CMenuViewController::saveRadioButtonInfo(string boxID) {

    //Open the Open File Dialog
    ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a wav or mp3 audio file");

    //Check if the user opened a file
    if (openFileResult.bSuccess){

        ofLogVerbose("User selected a file");

        //We have a file, check it and process it
        processOpenFileSelection(openFileResult,boxID);

    }else {
        ofLogVerbose("User hit cancel");
    }    
}

void CMenuViewController::processOpenFileSelection(ofFileDialogResult openFileResult, string boxID){

	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());

	ofFile file (openFileResult.getPath());

	if (file.exists()){

		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		//Only WAV or MP3 Files
		if (fileExtension == "WAV" || fileExtension == "MP3") {

            //====================================================================
            //Load sound files into Datapool XML File
            //====================================================================
            //string fileName = "sounds/" + file.getFileName();
            string key;
            key.resize(boxID.size());
            transform(boxID.begin(), boxID.end(), key.begin(), ::tolower);
            key = key + "Button";

            //reload sound file.
            void *val;
            if ( m_datapool->getRefByName("boxButtons", val) ) {
                vector<CBoxButton*> *vecBoxes = (vector<CBoxButton*> *)val;
                for ( vector<CBoxButton*>::iterator iter = vecBoxes->begin(); iter!=vecBoxes->end(); iter ++){
                    if ( (*iter)->getBoxName() == boxID ){
                        cout<<"reload sound:"<<file.getAbsolutePath();
                        (*iter)->reloadSound(file.getAbsolutePath());
                        m_datapool->setValue( boxID, file.getAbsolutePath(), true );
                        break;
                    }
                }                                
            }else{
                ofLogVerbose("cannot get the reference of box vector");
            }
		}
	}

    file.close();
}


