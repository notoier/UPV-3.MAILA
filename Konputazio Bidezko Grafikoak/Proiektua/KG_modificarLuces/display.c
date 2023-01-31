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
extern object3d * _first_kamera;
extern object3d * _selected_kamera;
extern int obj_mota;
extern int kamera_mota;
double near = 0.8; 
double far = 100000;
extern int nondik_ikusi;

extern argiak gl_argiak[8];
extern GLint fs;
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
    // _window_ratio = (GLdouble) width / (GLdouble) height;
}

/*erreferentzia sistema aldatzeko matrizea lortu*/
void lortu_ESAM(double * M, double * ESAM){
    ESAM[0]=M[0];   ESAM[4]=M[1];   ESAM[8]=M[2];     ESAM[12]=-(M[0]*M[12]+M[1]*M[13]+M[2]*M[14]);
    ESAM[1]=M[4];   ESAM[5]=M[5];   ESAM[9]=M[6];     ESAM[13]=-(M[4]*M[12]+M[5]*M[13]+M[6]*M[14]);
    ESAM[2]=M[8];   ESAM[6]=M[9];   ESAM[10]=M[10];   ESAM[14]=-(M[8]*M[12]+M[9]*M[13]+M[10]*M[14]);
    ESAM[3]=0;      ESAM[7]=0;      ESAM[11]=0;       ESAM[15]=1;
}

void argienPosizioaEzarri(){
    if(_selected_object!=0){
    
        GLfloat s_obj_pos[4] = {_selected_object->mzptr->M[12], _selected_object->mzptr->M[13], (_selected_object->max.z) + _selected_object->mzptr->M[14], 1};
        GLfloat s_obj_dir[3] = {_selected_object->mzptr->M[8], _selected_object->mzptr->M[9], _selected_object->mzptr->M[10]};
        glLightfv(GL_LIGHT2, GL_POSITION, s_obj_pos);
        //glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180); //NO SÉ SI ES NECESARIO!! PROBAR.
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, s_obj_dir);
    }
    else{
        printf("Ez dago objekturik\n");
    }
    if(_selected_kamera!=0){
    GLfloat s_kam_pos[4]={_selected_kamera->mzptr->M[12], _selected_kamera->mzptr->M[13], _selected_kamera->mzptr->M[14], 1}; 
    GLfloat s_kam_dir[3]={-_selected_kamera->mzptr->M[8], -_selected_kamera->mzptr->M[9], -_selected_kamera->mzptr->M[10]};
    glLightfv(GL_LIGHT3, GL_POSITION,  s_kam_pos);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 180);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, s_kam_dir);
    }
    else{
        printf("Ez dago kamerarik\n");
    }
}

int aurpegiakLortu(object3d *obj, face * aurpegi){
    double ESAM_obj[16];
    double a;
    vector3 vec;
    vector3 e;
    lortu_ESAM(obj->mzptr->M,&(ESAM_obj[0]));
    e.x = ESAM_obj[0]*_selected_kamera->mzptr->M[12] + ESAM_obj[4]*_selected_kamera->mzptr->M[13] +ESAM_obj[8]*_selected_kamera->mzptr->M[14] +ESAM_obj[12]*_selected_kamera->mzptr->M[15];
    e.y = ESAM_obj[1]*_selected_kamera->mzptr->M[12] + ESAM_obj[5]*_selected_kamera->mzptr->M[13] +ESAM_obj[9]*_selected_kamera->mzptr->M[14] +ESAM_obj[13]*_selected_kamera->mzptr->M[15];
    e.z = ESAM_obj[2]*_selected_kamera->mzptr->M[12] + ESAM_obj[6]*_selected_kamera->mzptr->M[13] +ESAM_obj[10]*_selected_kamera->mzptr->M[14] +ESAM_obj[14]*_selected_kamera->mzptr->M[15];

    vec.x=e.x - _selected_object->vertex_table[aurpegi->vertex_table[0]].coord.x;
    vec.y=e.y  - _selected_object->vertex_table[aurpegi->vertex_table[0]].coord.y;
    vec.z=e.z  - _selected_object->vertex_table[aurpegi->vertex_table[0]].coord.z;

    a=vec.x * aurpegi->b_normala.x + vec.y * aurpegi->b_normala.y +vec.z * aurpegi->b_normala.z;
    return (a>0);
}



/**
 * @brief Callback display function
 */
void display(void) {
    double ESAM[16];
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT);

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
    
    if((nondik_ikusi==0) && (_selected_object!=0)){
        /*objektuaren erreferentzia sistemara aldatu*/
        lortu_ESAM(_selected_object->mzptr->M, ESAM);
    }else{
        /*kameraren erreferentzia sistemara aldatu*/
        lortu_ESAM(_selected_kamera->mzptr->M, ESAM);
    }

    glOrtho(_ortho_x_min, _ortho_x_max, _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);

    
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 200.0);
    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glLoadMatrixd(ESAM);
    
    glEnable(GL_LIGHTING);
    for (int i = 0; i < 8; i++){
            glPushMatrix();
            glMultMatrixf(gl_argiak[i].matrize_obj);
            argia_ezarri(i);
            glPopMatrix();
    }
    glLoadMatrixd(ESAM);
    argienPosizioaEzarri();



    /*First, we draw the axes*/
    //draw_axes();

    /*Now each of the objects in the list*/
    //obj dauden bitartean, objk marraztu
    while (aux_obj != 0) {

        /* Select the color, depending on whether the current object is the selected one or not */
        //Kolorea erabaki
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }

        glMaterialfv(GL_FRONT, GL_AMBIENT, aux_obj->materialak->m_ingurunea);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, aux_obj->materialak->m_difusioa);
        glMaterialfv(GL_FRONT, GL_SPECULAR, aux_obj->materialak->m_espekularra);
        glMaterialfv(GL_FRONT, GL_SHININESS, aux_obj->materialak->argirik_ez);

        /* Draw the object; for each face create a new polygon with the corresponding vertices */
        //Obj marraztu: poligono guztiak marraztuz
        glLoadMatrixd(ESAM);
        glMultMatrixd(aux_obj->mzptr->M);

        for (f = 0; f < aux_obj->num_faces; f++) {
            glNormal3d(aux_obj->face_table[f].b_normala.x, aux_obj->face_table[f].b_normala.y, aux_obj->face_table[f].b_normala.z);
            glBegin(GL_POLYGON);

            if(aurpegiakLortu(aux_obj, &(aux_obj->face_table[f]))){
                for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                    v_index = aux_obj->face_table[f].vertex_table[v];
                    glVertex3d(aux_obj->vertex_table[v_index].coord.x, aux_obj->vertex_table[v_index].coord.y, aux_obj->vertex_table[v_index].coord.z);  
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
