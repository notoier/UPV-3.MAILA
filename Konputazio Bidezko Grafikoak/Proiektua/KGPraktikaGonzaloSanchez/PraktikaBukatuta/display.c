#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "io.h"
/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;
extern object3d *_selected_kamera;
extern object3d *_first_kamera;
extern int ikuspuntua;
extern argia argi_globalak[];
extern materiala materialak[];

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(1,0,0);
    glVertex3d(0,0,0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,1,0);
    glVertex3d(0,0,0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,0,1);
    glVertex3d(0,0,0);
    glEnd();
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    // we will use a rectangular viewport allways
    if (width > height)
        glViewport(0, 0, height, height);
      else 
        glViewport(0, 0, width, width);
    //  old code
    //  glViewport(0, 0, width, height);
    //  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
    //  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}

void argienPosizioakEzarri(){
    if(_selected_object==0){
        printf("\n");
    }
    else{
        GLfloat sop[4] = {_selected_object->MZptr->M[12], _selected_object->MZptr->M[13], (_selected_object->max.z) + _selected_object->MZptr->M[14], 1};
        GLfloat sod[3] = {_selected_object->MZptr->M[8], _selected_object->MZptr->M[9], _selected_object->MZptr->M[10]};
        glLightfv(GL_LIGHT2, GL_POSITION, sop);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, sod);
    }
    GLfloat scp[4]={_selected_kamera->MZptr->M[12], _selected_kamera->MZptr->M[13], _selected_kamera->MZptr->M[14], 1}; 
    GLfloat scd[3]={-_selected_kamera->MZptr->M[8], -_selected_kamera->MZptr->M[9], -_selected_kamera->MZptr->M[10]};
    glLightfv(GL_LIGHT3, GL_POSITION, scp);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 180);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, scd);
   
}

void M_partikularra_lortu(double *M, double *n_M)
{
    n_M[0]=M[0];   n_M[4]=M[1];   n_M[8]=M[2];     n_M[12]=-(M[0]*M[12]+M[1]*M[13]+M[2]*M[14]);
    n_M[1]=M[4];   n_M[5]=M[5];   n_M[9]=M[6];     n_M[13]=-(M[4]*M[12]+M[5]*M[13]+M[6]*M[14]);
    n_M[2]=M[8];   n_M[6]=M[9];   n_M[10]=M[10];   n_M[14]=-(M[8]*M[12]+M[9]*M[13]+M[10]*M[14]);
    n_M[3]=0;      n_M[7]=0;      n_M[11]=0;       n_M[15]=1;
}

int aurpegiaKoloreztatu(object3d *obj, face * aurpegia){
    double A[16];
    double MCSRobj[16];
    double EcObj[16];
    
    double a;
    vector3 v;
    vector3 e_obj;
    M_partikularra_lortu(obj->MZptr->M,&(MCSRobj[0]));
    e_obj.x = MCSRobj[0]*_selected_kamera->MZptr->M[12] + MCSRobj[4]*_selected_kamera->MZptr->M[13] +MCSRobj[8]*_selected_kamera->MZptr->M[14] +MCSRobj[12]*_selected_kamera->MZptr->M[15];
    e_obj.y = MCSRobj[1]*_selected_kamera->MZptr->M[12] + MCSRobj[5]*_selected_kamera->MZptr->M[13] +MCSRobj[9]*_selected_kamera->MZptr->M[14] +MCSRobj[13]*_selected_kamera->MZptr->M[15];
    e_obj.z = MCSRobj[2]*_selected_kamera->MZptr->M[12] + MCSRobj[6]*_selected_kamera->MZptr->M[13] +MCSRobj[10]*_selected_kamera->MZptr->M[14] +MCSRobj[14]*_selected_kamera->MZptr->M[15];

    v.x=e_obj.x - _selected_object->vertex_table[aurpegia->vertex_table[0]].coord.x;
    v.y=e_obj.y  - _selected_object->vertex_table[aurpegia->vertex_table[0]].coord.y;
    v.z=e_obj.z  - _selected_object->vertex_table[aurpegia->vertex_table[0]].coord.z;

    a=v.x * aurpegia->v_normala.x + v.y * aurpegia->v_normala.y +v.z * aurpegia->v_normala.z;
    return (a>0);
}



/**
 * @brief Callback display function
 */
void display(void) {
    double n_M[16];
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*When the window is wider than our original projection plane we extend the plane in the X axis*/
    if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
        /* New width */
        GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;
        /* Midpoint in the X axis */
        GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
        /*Definition of the projection*/
        glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
    } else {/* In the opposite situation we extend the Y axis * /
        /* New height */
        GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
        /* Midpoint in the Y axis */
        GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
        /*Definition of the projection*/
        glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
    }

    
    
    if((ikuspuntua==1) && (_selected_object!=0)){
        M_partikularra_lortu(_selected_object->MZptr->M, n_M);
    }else{
        M_partikularra_lortu(_selected_kamera->MZptr->M, n_M);
    }


    glOrtho(_ortho_x_min, _ortho_x_max, _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
    
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 200.0);


    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glLoadMatrixd(n_M);
    glEnable(GL_LIGHTING);

    for (int i = 0; i < 8; i++){
            glPushMatrix();
            glMultMatrixf(argi_globalak[i].m_obj);
            put_light(i);
            glPopMatrix();
    }
    glLoadMatrixd(n_M);
    argienPosizioakEzarri();


    aux_obj = _first_object;

    /*First, we draw the axes*/
    //draw_axes();
    
    /*Now each of the objects in the list*/
    while (aux_obj != 0) {

        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }
        

        glMaterialfv(GL_FRONT, GL_AMBIENT, aux_obj ->materiala->ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, aux_obj ->materiala->diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, aux_obj ->materiala->specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, aux_obj ->materiala->shininess);

        
        /* Draw the object; for each face create a new polygon with the corresponding vertices */
        glLoadMatrixd(n_M);
        glMultMatrixd(aux_obj->MZptr->M);
        for (f = 0; f < aux_obj->num_faces; f++) {
            glNormal3d(aux_obj->face_table[f].v_normala.x, aux_obj->face_table[f].v_normala.y, aux_obj->face_table[f].v_normala.z);
            glBegin(GL_POLYGON);
            if(aurpegiaKoloreztatu(aux_obj, &(aux_obj->face_table[f]))){
                for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                    v_index = aux_obj->face_table[f].vertex_table[v];
                    glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                            aux_obj->vertex_table[v_index].coord.y,
                            aux_obj->vertex_table[v_index].coord.z);

                }
            }
            glEnd();
        }
                
        aux_obj = aux_obj->next;
    }
    
    /*Do the actual drawing*/
    glFlush();
    glutSwapBuffers();
    
}
