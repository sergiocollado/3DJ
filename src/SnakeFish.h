//
//  SnakeFish.h
//  openNI-3DJ
//
//  Created by Samuel Ruberti on 10/12/12.
//
//

#ifndef __openNI_3DJ__SnakeFish__
#define __openNI_3DJ__SnakeFish__
#include "Entity.h"

class SnakeFish : public CreatureEntity{

public:
    SnakeFish();
    ~SnakeFish();
    
    void render();
    void update(double time_since_last_update);
    void applyTransforms();
    void move();
    void kill();
    void preRender();
    void postRender();

    //member vars
    bool m_active;
    
    float m_x, m_y, m_z; 
    float m_r, m_g, m_b, m_a; 
    float m_total_time; 
    EntityType m_type;
    
    float m_maxSpeed;
    float m_birth;
    float m_energy, m_power;
    ofPoint m_position, m_projectedPos, m_rotation, m_scale;
    
    float m_sF, m_oS, m_oX, m_oY;
    float m_rYA, m_rXA, m_rXF, m_rYF;
    
    vector<ofPoint *> m_queue;
    

};
#endif /* defined(__openNI_3DJ__SnakeFish__) */
