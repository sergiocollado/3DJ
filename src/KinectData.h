//
//  CKinectData.h
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 8/15/12.
//
//

#ifndef __openNI_3DJ__KinectData__
#define __openNI_3DJ__KinectData__

#include <iostream>
#include "ofxOpenNI.h"
#include "DataPool.h"
using namespace DataPool;

class CKinectData {
public:

    CKinectData();
    void setup();
	void update();
    void draw();
    void exit();

    bool m_isTracking, m_isCloud, m_isMasking, m_isFiltering;

    float				m_filterFactor;
    int                 m_numberOfUsersToTrack;

    CDataPool *m_dataPool;
    ofxOpenNI           m_openNIDevice;
};

#endif /* defined(__openNI_3DJ__KinectData__) */
