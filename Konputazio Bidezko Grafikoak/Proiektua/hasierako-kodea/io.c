#include "definitions.h"
#include "load_obj.h"
#include "display.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

extern object3d * _first_object;
extern object3d * _selected_object;

extern camera * _first_camera;
extern camera * _selected_camera;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern char _change_type; /*Variable used to define the type of change to be done to a selected object*/
extern char _change_scope; /*Defines the types of changes (global or local)*/
extern char _change_mode; /*Variable used to define the thing to change (camera, object...)*/
extern char _camera_mode; /*Variable to control the type of cameras (Flying mode, analasis mode)*/

int viewpoint = 0;

int argi_aktiboa = 0;    // 0 bonbila, 1 eguzkia, 2 kamera fokoa, 3 objektu fokoa
int bonbilla_piztuta = 0;
int eguzkia_piztuta = 0;
int obj_fokoa_piztuta = 0;
int kam_fokoa_piztuta = 0;
int orokorra_piztuta = 1;

light global_lighting[4];
material materials[2];
material *yellow, *silver;
/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<I>\t\t Objektuari dagokion informazioa pantailaratu\n");
    printf("<Q,q>\t\t Ikuspuntua aldatu\n");
    printf("<Z,z>\t\t Objektuari egindako aldaketa desegin\n");
    printf("<T,t>\t\t Translazioa aktibatu\n");
    printf("<R,r>\t\t Rotazioak aktibatu\n");
    printf("<S,s>\t\t Escalak aktibatu\n");

    printf("<G,g>\t\t Aldaketa global aktibatu\n");
    printf("<L,l>\t\t Aldaketa lokalak aktibatu\n");

    printf("<GEZIAK / AVPAG / REPAG>\t\t Aldaketak egin\n");

    printf("<O,o>\t\t Aldaketak objektuei egin\n");
    printf("<C,c>\t\t Aldaketak camerari egin\n");   
    printf("<A,a>\t\t Aldaketak argiari egin\n");
    
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
    printf("\n\n");
}
/**
 * @brief Free all memory allocated to an object 
 * @param object Object to free
 */
void freeall(object3d *object){
    GLint i;
    MZ *auxptr;

    for (i = 0; i < object->num_faces; ++i){
        free(object->face_table[i].vertex_table);
    }
    free(object->vertex_table);
    free(object->face_table);
    for (auxptr = object->MZptr; auxptr != 0; auxptr = object->MZptr)
    {
        object->MZptr = object->MZptr->hptr;
        free(auxptr);
    }
}

void multiply_matrixes(double *mptr){

    MZ *mlagptr;
    glMatrixMode(GL_MODELVIEW);
    //If we are make changes to an object:
    if (_change_mode == 'o'){
        //Changes depend on wether the change's scope is set in global or local
        switch(_change_scope){
            case 'l':
                glLoadMatrixd(_selected_object->MZptr->M);
                glMultMatrixd(&(mptr[0]));
                break;

            case 'g':
                glLoadMatrixd(&(mptr[0]));
                glMultMatrixd(_selected_object->MZptr->M);
                break;
        }

        mlagptr = (MZ*)malloc(sizeof(MZ));
        glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr -> M);
        mlagptr->hptr = _selected_object->MZptr;
        _selected_object->MZptr = mlagptr;
    
    //Else, if we are changing a camera
    } else if (_change_mode == 'c'){
        //Changes still depend on wether the change's scope is set in global or local
        switch (_camera_mode)
        {
            case 'f':
                glLoadMatrixd(_selected_camera->MZptr->M);
                glMultMatrixd(&(mptr[0]));
                break;
            
            case 'a':
                glLoadMatrixd(&(mptr[0]));
                glMultMatrixd(_selected_camera->MZptr->M);
                break;
        }

        mlagptr = (MZ *)(malloc(sizeof(MZ)));
        glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
        mlagptr->hptr = _selected_camera->MZptr;
        _selected_camera->MZptr = mlagptr;
    }
}

/**
  * @brief Get the translation matrix object
  * 
  * @param mptr Object's translation matrix
  * @param x X coordinate
  * @param y Y coordinate
  * @param z Z coordinate
  */
void translation_matrix(double x, double y, double z){
    double mptr[16];
    MZ* mlagptr;
    // AZ* alagptr;

    mptr[0] = 1.0; mptr[4] = 0.0; mptr[8]  = 0.0; mptr[12] = x*KG_TRAN_STEP;
    mptr[1] = 0.0; mptr[5] = 1.0; mptr[9]  = 0.0; mptr[13] = y*KG_TRAN_STEP;
    mptr[2] = 0.0; mptr[6] = 0.0; mptr[10] = 1.0; mptr[14] = z*KG_TRAN_STEP;
    mptr[3] = 0.0; mptr[7] = 0.0; mptr[11] = 0.0; mptr[15] = 1.0;

    multiply_matrixes(mptr);

    if (_change_mode == 'o')
        printf("Object moved in:  X: %f, Y: %f, Z: %f. \n", x,y,z );
    else
        printf("Camera moved in:  X: %f, Y: %f, Z: %f. \n", x,y,z );    
}

/**
  * @brief Get the rotation matrix object
  * 
  * @param mptr Object's rotation matrix (Rodriges' formula)
  * @param x X coordinate
  * @param y Y coordinate
  * @param z Z coordinate
  */
void rotation_matrix(double x, double y, double z){

    double mptr[16];
    MZ* mlagptr;
    // AZ* alagptr;
/* 
    mptr[0] = cos(KG_ROT_ANGLE) + pow(x, 2)*(1-cos(KG_ROT_ANGLE));   mptr[4] = x*y*(1-cos(KG_ROT_ANGLE)) - z*sin(KG_ROT_ANGLE);       mptr[8]  = x*z*(1-cos(KG_ROT_ANGLE)) + y*sin(KG_ROT_ANGLE);       mptr[12] = 0.0;
    mptr[1] = y*x*(1-cos(KG_ROT_ANGLE)) + z*sin(KG_ROT_ANGLE);       mptr[5] = cos(KG_ROT_ANGLE) + pow(y, 2)*(1-cos(KG_ROT_ANGLE));   mptr[9]  = y*z*(1-cos(KG_ROT_ANGLE)) - x*sin(KG_ROT_ANGLE);       mptr[13] = 0.0;
    mptr[2] = z*x*(1-cos(KG_ROT_ANGLE) - y*sin(KG_ROT_ANGLE));       mptr[6] = z*y*(1-cos(KG_ROT_ANGLE) + x*sin(KG_ROT_ANGLE));       mptr[10] = cos(KG_ROT_ANGLE) + pow(z, 2)*(1-cos(KG_ROT_ANGLE));   mptr[14] = 0.0;
    mptr[3] = 0.0;                                                   mptr[7] = 0.0;                                                   mptr[11] = 0.0;                                                   mptr[15] = 1.0;
*/
    double alpha = x * KG_ROT_ANGLE;
    double beta = y * KG_ROT_ANGLE;
    double gamma = z * KG_ROT_ANGLE;

    mptr[0] = cos(beta) * cos(gamma); mptr[4] = sin(alpha) * sin(beta) * cos (gamma) - cos(alpha) * sin(gamma); mptr[8] = cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma); mptr[12] = 0.0;
    mptr[1] = cos(beta) * sin(gamma); mptr[5] = sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma);  mptr[9] = cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma); mptr[13] = 0.0;
    mptr[2] = -sin(beta);             mptr[6] = sin(alpha) * cos(beta);                                         mptr[10] = cos(alpha) * cos(beta);                                       mptr[14] = 0.0;
    mptr[3] = 0.0;                    mptr[7] = 0.0;                                                            mptr[11] = 0.0;                                                          mptr[15] = 1.0;

    multiply_matrixes(mptr);

    if (_change_mode  == 'o')
        printf("Object rotated %fº in:  X: %f, Y: %f, Z: %f. \n", KG_ROT_ANGLE*180/M_PI, x*KG_ROT_ANGLE*180/M_PI, y*KG_ROT_ANGLE*180/M_PI, z*KG_ROT_ANGLE*180/M_PI);
    else
        printf("Camera rotated %fº in:  X: %f, Y: %f, Z: %f. \n", KG_ROT_ANGLE*180/M_PI, x*KG_ROT_ANGLE*180/M_PI, y*KG_ROT_ANGLE*180/M_PI, z*KG_ROT_ANGLE*180/M_PI);
    
}
/**
  * @brief Get scale matrix object
  * 
  * @param mptr Object's scale matrix
  * @param x X coordinate
  * @param y Y coordinate
  * @param z Z coordinate
  */
void scaling_matrix(double x, double y, double z){

    double mptr[16];
    MZ* mlagptr;
    // AZ* alagptr;

    mptr[0] = x;                mptr[4] = 0.0;              mptr[8]  = 0.0;             mptr[12] = 0.0;
    mptr[1] = 0.0;              mptr[5] = y;                mptr[9]  = 0.0;             mptr[13] = 0.0;
    mptr[2] = 0.0;              mptr[6] = 0.0;              mptr[10] = z;               mptr[14] = 0.0;
    mptr[3] = 0.0;              mptr[7] = 0.0;              mptr[11] = 0.0;             mptr[15] = 1.0;

    multiply_matrixes(mptr);
    
    if (_change_mode == 'o')
        printf("Object's size changed in:  X: %f, Y: %f, Z: %f. \n", x,y,z);
    else
        printf("Cameras's size changed in:  X: %f, Y: %f, Z: %f. \n", x,y,z);
}

/**
 * @brief  
 * 
 * @param matrix 
 */
void at_matrix(double * matrix){
    matrix[0]=1;       matrix[4]=0;         matrix[8]=0;         matrix[12]=_selected_object->MZptr->M[12];
    matrix[1]=0;       matrix[5]=1;         matrix[9]=0;         matrix[13]=_selected_object->MZptr->M[13];
    matrix[2]=0;       matrix[6]=0;         matrix[10]=1;        matrix[14]=_selected_object->MZptr->M[14];
    matrix[3]=0;       matrix[7]=0;         matrix[11]=0;        matrix[15]=1;
         
}
/**
 * @brief 
 * 
 * @param bmatrix 
 */
void new_at_matrix(double * bmatrix){
    bmatrix[0]=1;        bmatrix[4]=0;         bmatrix[8]=0;         bmatrix[12]=-_selected_object->MZptr->M[12];
    bmatrix[1]=0;        bmatrix[5]=1;         bmatrix[9]=0;         bmatrix[13]=-_selected_object->MZptr->M[13];
    bmatrix[2]=0;        bmatrix[6]=0;         bmatrix[10]=1;        bmatrix[14]=-_selected_object->MZptr->M[14];
    bmatrix[3]=0;        bmatrix[7]=0;         bmatrix[11]=0;        bmatrix[15]=1;   
}
/**
 * @brief Undo the last change done to an object
 * 
 */
void undo(){
    if (_selected_object != 0){
        if (_selected_object->MZptr != 0){
            if(_selected_object->MZptr->hptr != 0){        
                
                printf("Last change reversed \n");

                MZ *auxptr;
                
                auxptr = _selected_object->MZptr;
                _selected_object->MZptr =_selected_object->MZptr->hptr;
                free(auxptr);
            }
        }
    } else {
        printf("No object loaded, therefore, there's nothing to undo \n");
    }  
}

vector3 puntuen_kenketa(point3 p1, point3 p2)
{
    vector3 v;

    v.x = p1.x - p2.x;
    v.y = p1.y - p2.y;
    v.z = p1.z - p2.z;

    return v;
}

void poligonoen_v_normk_kal()
{
    vector3 v1, v2, vN;
    GLdouble modulua;
    int i1, i2, i0;
    int *AurpegienErtzenIndizeak;

    for (int i = 0; i < _selected_object->num_faces; i++)
    {

        AurpegienErtzenIndizeak = _selected_object->face_table[i].vertex_table;
        i0 = AurpegienErtzenIndizeak[0];
        i1 = AurpegienErtzenIndizeak[1];
        i2 = AurpegienErtzenIndizeak[2];

        v1 = puntuen_kenketa(_selected_object->vertex_table[i1].coord, _selected_object->vertex_table[i0].coord);
        v2 = puntuen_kenketa(_selected_object->vertex_table[i2].coord, _selected_object->vertex_table[i0].coord);

        vN.x = (v1.y * v2.z) - (v2.y * v1.z);
        vN.y = -((v1.x * v2.z) - (v2.x * v1.z));
        vN.z = (v1.x * v2.y) - (v2.x * v1.y);

        modulua = sqrt(vN.x * vN.x + vN.y * vN.y + vN.z * vN.z);

        vN.x = vN.x / modulua;
        vN.y = vN.y / modulua;
        vN.z = vN.z / modulua;

        _selected_object->face_table[i].v_norm.x = vN.x;
        _selected_object->face_table[i].v_norm.y = vN.y;
        _selected_object->face_table[i].v_norm.z = vN.z;
    }
}


void fokoaren_matrizea()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        global_lighting[2].m_obj[i] = _selected_object->MB->M[i];
    }
}

void kameraren_matrizea()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        global_lighting[2].m_obj[i] = _selected_camera->MB->M[i];
    }
}

void put_light(GLint i)
{
    switch (i)
    {
    case 0:

        glLightfv(GL_LIGHT0, GL_POSITION, global_lighting[i].position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, global_lighting[i].ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, global_lighting[i].diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, global_lighting[i].specular);
        break;

    case 1:
        glLightfv(GL_LIGHT1, GL_AMBIENT, global_lighting[i].ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, global_lighting[i].diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, global_lighting[i].specular);
        glLightfv(GL_LIGHT1, GL_POSITION, global_lighting[i].position);
        break;

    case 2:
        glLightfv(GL_LIGHT2, GL_AMBIENT, global_lighting[i].ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, global_lighting[i].diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, global_lighting[i].specular);
        glLightfv(GL_LIGHT2, GL_POSITION, global_lighting[i].position);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, global_lighting[i].spot_direction);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, global_lighting[i].cut_off);
        break;

    case 3:
        glLightfv(GL_LIGHT3, GL_AMBIENT, global_lighting[i].ambient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, global_lighting[i].diffuse);
        glLightfv(GL_LIGHT3, GL_SPECULAR, global_lighting[i].specular);
        glLightfv(GL_LIGHT3, GL_POSITION, global_lighting[i].position);
        if (global_lighting[i].type == 3)
        {
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, global_lighting[i].spot_direction);
            glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, global_lighting[i].cut_off);
        }
        break;

    case 4:
        glLightfv(GL_LIGHT4, GL_AMBIENT, global_lighting[i].ambient);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, global_lighting[i].diffuse);
        glLightfv(GL_LIGHT4, GL_SPECULAR, global_lighting[i].specular);
        glLightfv(GL_LIGHT4, GL_POSITION, global_lighting[i].position);

        if (global_lighting[i].type == 4)
        {
            glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, global_lighting[i].spot_direction);
            glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, global_lighting[i].cut_off);
        }
        break;

    default:
        break;
    }
}

void lighting_init()
{

    global_lighting[0].position[0] = 0.0f;
    global_lighting[0].position[1] = 1.0f;
    global_lighting[0].position[2] = 0.0f;
    global_lighting[0].position[3] = 0.0f;
    global_lighting[0].ambient[0] = 1.2f;
    global_lighting[0].ambient[1] = 1.2f;
    global_lighting[0].ambient[2] = 1.2f;
    global_lighting[0].ambient[3] = 1.0f;
    global_lighting[0].diffuse[0] = 1.0f;
    global_lighting[0].diffuse[1] = 1.0f;
    global_lighting[0].diffuse[2] = 1.0f;
    global_lighting[0].diffuse[3] = 1.0f;
    global_lighting[0].specular[0] = 1.0f;
    global_lighting[0].specular[1] = 1.0f;
    global_lighting[0].specular[2] = 1.0f;
    global_lighting[0].specular[3] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(0);
    glGetFloatv(GL_MODELVIEW_MATRIX, global_lighting[0].m_obj);
    global_lighting[0].type = 0;
    global_lighting[0].is_on = 1;

    global_lighting[1].position[0] = 1.0f;
    global_lighting[1].position[1] = 1.0f;
    global_lighting[1].position[2] = 0.0f;
    global_lighting[1].position[3] = 1.0f;
    global_lighting[1].ambient[0] = 1.2f;
    global_lighting[1].ambient[1] = 1.2f;
    global_lighting[1].ambient[2] = 1.2f;
    global_lighting[1].ambient[3] = 1.0f;
    global_lighting[1].diffuse[0] = 1.0f;
    global_lighting[1].diffuse[1] = 1.0f;
    global_lighting[1].diffuse[2] = 1.0f;
    global_lighting[1].diffuse[3] = 1.0f;
    global_lighting[1].specular[0] = 1.0f;
    global_lighting[1].specular[1] = 1.0f;
    global_lighting[1].specular[2] = 1.0f;
    global_lighting[1].specular[3] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(1);
    glGetFloatv(GL_MODELVIEW_MATRIX, global_lighting[1].m_obj);
    global_lighting[1].type = 1;
    global_lighting[1].is_on = 0;
}

void objektu_fokoa_hasieratu()
{
    global_lighting[2].position[0] = _selected_object->max.x / 2;
    global_lighting[2].position[1] = _selected_object->max.y / 2;
    global_lighting[2].position[2] = _selected_object->max.z;
    global_lighting[2].position[3] = 1.0f;
    global_lighting[2].ambient[0] = 1.5f;
    global_lighting[2].ambient[1] = 1.5f;
    global_lighting[2].ambient[2] = 1.5f;
    global_lighting[2].ambient[3] = 1.0f;
    global_lighting[2].diffuse[0] = 1.5f;
    global_lighting[2].diffuse[1] = 1.5f;
    global_lighting[2].diffuse[2] = 1.5f;
    global_lighting[2].diffuse[3] = 1.0f;
    global_lighting[2].specular[0] = 1.0f;
    global_lighting[2].specular[1] = 1.0f;
    global_lighting[2].specular[2] = 1.0f;
    global_lighting[2].specular[3] = 1.0f;
    global_lighting[2].cut_off = 45.0f;
    global_lighting[2].spot_direction[0] = 0.0f;
    global_lighting[2].spot_direction[1] = 0.0f;
    global_lighting[2].spot_direction[2] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(2);
    _selected_object->MB = (MZ *)malloc(sizeof(MZ));
    fokoaren_matrizea();
    global_lighting[2].type = 2;
    global_lighting[2].is_on = 0;
}

void camera_focus_init()
{
    global_lighting[3].position[0] = _selected_camera->max.x / 2;
    global_lighting[3].position[1] = _selected_camera->max.y / 2;
    global_lighting[3].position[2] = _selected_camera->max.z;
    global_lighting[3].position[3] = 1.0f;
    global_lighting[3].ambient[0] = 1.5f;
    global_lighting[3].ambient[1] = 1.5f;
    global_lighting[3].ambient[2] = 1.5f;
    global_lighting[3].ambient[3] = 1.0f;
    global_lighting[3].diffuse[0] = 1.5f;
    global_lighting[3].diffuse[1] = 1.5f;
    global_lighting[3].diffuse[2] = 1.5f;
    global_lighting[3].diffuse[3] = 1.0f;
    global_lighting[3].specular[0] = 1.0f;
    global_lighting[3].specular[1] = 1.0f;
    global_lighting[3].specular[2] = 1.0f;
    global_lighting[3].specular[3] = 1.0f;
    global_lighting[2].cut_off = 45.0f;
    global_lighting[2].spot_direction[0] = 0.0f;
    global_lighting[2].spot_direction[1] = 0.0f;
    global_lighting[2].spot_direction[2] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(3);
    _selected_camera->MB = (MZ *)malloc(sizeof(MZ));
    kameraren_matrizea();
    global_lighting[3].type = 3;
    global_lighting[3].is_on = 0;
}

void ertzen_vektore_normala_kalk()
{
    vector3 v0 = {0, 0, 0};
    vertex *v1;
    for (int i = 0; i < _selected_object->num_vertices; i++)
    {
        _selected_object->vertex_table[i].v_norm = v0;
    }

    for (int j = 0; j < _selected_object->num_faces; j++)
    {
        for (int k = 0; k < _selected_object->face_table[j].num_vertices; k++)
        {
            v1 = &(_selected_object->vertex_table[_selected_object->face_table[j].vertex_table[k]]);
            v1->v_norm.x = v1->v_norm.x - _selected_object->face_table[j].v_norm.x;
            v1->v_norm.y = v1->v_norm.y - _selected_object->face_table[j].v_norm.y;
            v1->v_norm.z = v1->v_norm.z - _selected_object->face_table[j].v_norm.z;
        }
    }

    for (int i = 0; i < _selected_object->num_vertices; i++)
    {
        v1 = &(_selected_object->vertex_table[i]);

        v1->v_norm.x = v1->v_norm.x / v1->num_faces;
        v1->v_norm.y = v1->v_norm.y / v1->num_faces;
        v1->v_norm.z = v1->v_norm.z / v1->num_faces;
    }
}

void materiala_jarri(){
    _selected_object -> material = yellow;
}

void material_init(){
    yellow = (material *)malloc(sizeof(material));
    silver = (material *)malloc(sizeof(material));

    yellow->ambient[0] = 0.05f;
    yellow->ambient[1] = 0.05f;
    yellow->ambient[2] = 0.0f;
    yellow->ambient[3] = 1.0f;
    yellow->diffuse[0] = 0.5f;
    yellow->diffuse[1] = 0.5f;
    yellow->diffuse[2] = 0.4f;
    yellow->diffuse[3] = 1.0f;
    yellow->specular[0] = 0.7f;
    yellow->specular[1] = 0.7f;
    yellow->specular[2] = 0.04f;
    yellow->specular[3] = 1.0f;
    yellow->shininess[0] = 0.078125f;

    silver->ambient[0] = 0.23125f;
    silver->ambient[1] = 0.23125f;
    silver->ambient[2] = 0.23125f;
    silver->ambient[3] = 1.0f;
    silver->diffuse[0] = 0.2775f;
    silver->diffuse[1] = 0.2775f;
    silver->diffuse[2] = 0.2775f;
    silver->diffuse[3] = 1.0f;
    silver->specular[0] = 0.773911f;
    silver->specular[1] = 0.773911f;
    silver->specular[2] = 0.773911f;
    silver->specular[3] = 1.0f;
    silver->shininess[0] = 89.6f;

}

void change_material(){
    if (_selected_object->material == yellow)
    {
        _selected_object->material = silver;
    }
    else
    {
        _selected_object->material = yellow;
    }
}

void intentsitatea_aldatu(int i, int argia_i){
    global_lighting[argia_i].ambient[0] += i*2;
    global_lighting[argia_i].ambient[1] += i*2;
    global_lighting[argia_i].ambient[2] += i*2;
    global_lighting[argia_i].ambient[3] += i*2;
    global_lighting[argia_i].diffuse[0] += i*2;
    global_lighting[argia_i].diffuse[1] += i*2;
    global_lighting[argia_i].diffuse[2] += i*2;
    global_lighting[argia_i].diffuse[3] += i*2;
    global_lighting[argia_i].specular[0] += i*2;
    global_lighting[argia_i].specular[1] += i*2;
    global_lighting[argia_i].specular[2] += i*2;
    global_lighting[argia_i].specular[3] += i*2;
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {

    char fname[128]; /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    int lighting_enabled = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;

    switch (key) {
        // Load an object
        case 'f':
        case 'F':
            /*Ask for file*/
            printf("%s", KG_MSSG_SELECT_FILE);
            scanf("%s", &(fname[0]));
            /*Allocate memory for the structure and read the file*/
            auxiliar_object = (object3d *) malloc(sizeof (object3d));
            read = read_wavefront(fname, auxiliar_object);
            switch (read) {
            /*Errors in the reading*/
            case 1:
                printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
                break;
            case 2:
                printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
                break;
            case 3:
                printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
                break;
            /*Read OK*/
            case 0:
                int i;
                auxiliar_object->MZptr = (MZ*)malloc(sizeof(MZ));
                for (i = 0; i < 16; i++){
                    if (i % 5 == 0){
                        auxiliar_object->MZptr->M[i] = 1.0;
                    } else {
                        auxiliar_object->MZptr->M[i] = 0.0;
                    }
                }
                
                //Insert the new object in the list
            
                auxiliar_object->next = _first_object;
                _first_object = auxiliar_object;
                _selected_object = _first_object;
                printf("%s\n",KG_MSSG_FILEREAD);
                break;
            }
            break;
        
        //Print object's information (TO BE FIXED)
  /*    case 'i':
        case 'I': //Print object's information on window
            //Check if there's an object selected
            if(_selected_object == 0){
                break;
            } 
            GLchar n_faces = _selected_object->num_faces;
            GLchar n_vertices = _selected_object->num_vertices;
            char* string1 = ("Faces: " + n_faces);
            char* string2 = "Vertices: " + n_vertices;
            output(2, 3, 0.2, 0.89, 0.89, GLUT_BITMAP_HELVETICA_10, "OBJECT INFORMATION");
            output(1, 2, 0.2, 0.89, 0.89, GLUT_BITMAP_HELVETICA_10, string1);
            output(2, 2.5, 0.2, 0.89, 0.89, GLUT_BITMAP_HELVETICA_10, string2);
            return;
  */
        //Enable translation mode
        case 't':
        case 'T':
            _change_type = 't'; //Translate
            printf("Translation mode enabled\n");
            break;
        
        //Enable rotation mode
        case 'r':
        case 'R':
            _change_type = 'r'; //Rotate
            printf("Rotation mode enabled\n");
            break;

        //Enable scaling mode
        case 'e':
        case 'E':
            _change_type = 'e'; //Scale 
            printf("Scaling mode enabled\n");
            break;

        case 'i':
        case 'I':
            printf("Intensity mode enabled \n");
            _change_type = 'i';
            break;

        //Set changes to affect locally
        case 'l':
        case 'L':
            if (_change_mode != 'c'){
                _change_scope = 'l'; //Local change
                printf("Changes set to: Local\n");
                break;
            }else{
                //CAMARA ALDAKETAK
                _camera_mode = 'f';
                printf("Flying camera is active \n");
                break;
            }
        //Set changes to affect globaly
        case 'g':
        case 'G':
            if (_change_mode != 'c'){
                _change_scope = 'g'; //Global change
                printf("Changes set to: Global\n");
                break;
                
            }else if (_selected_object != 0){
                //LOCK CAMERA TO OBJECT
                _camera_mode = 'a';

                double auxiliar_matrix[16];
                double matrix[16];
                
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                
                if(_selected_camera->MZptr->M==_selected_object->MZptr->M){

                }
                if(
                    (_selected_camera->MZptr->M[12] == _selected_object->MZptr->M[12]) && 
                    (_selected_camera->MZptr->M[13] == _selected_object->MZptr->M[13]) && 
                    (_selected_camera->MZptr->M[14] == _selected_object->MZptr->M[14])
                  ){
                        _selected_camera->MZptr->M[12] = _selected_camera->MZptr->M[12] + _selected_camera->MZptr->M[8]  *10;
                        _selected_camera->MZptr->M[13] = _selected_camera->MZptr->M[13] + _selected_camera->MZptr->M[9]  *10;
                        _selected_camera->MZptr->M[14] = _selected_camera->MZptr->M[14] + _selected_camera->MZptr->M[10] *10;
                    }

                gluLookAt(_selected_camera->MZptr->M[12], _selected_camera->MZptr->M[13], _selected_camera->MZptr->M[14],
                          _selected_object->MZptr->M[12], _selected_object->MZptr->M[13], _selected_object->MZptr->M[14],
                          _selected_camera->MZptr->M[4],  _selected_camera->MZptr->M[5],  _selected_camera->MZptr->M[6]
                          );

                glGetDoublev(GL_MODELVIEW_MATRIX, auxiliar_matrix);
                

                matrix[0] = auxiliar_matrix[0];    matrix[4] = auxiliar_matrix[1];      matrix[8]  = auxiliar_matrix[2];     matrix[12] = _selected_camera->MZptr->M[12];
                matrix[1] = auxiliar_matrix[4];    matrix[5] = auxiliar_matrix[5];      matrix[9]  = auxiliar_matrix[6];     matrix[13] = _selected_camera->MZptr->M[13];
                matrix[2] = auxiliar_matrix[8];    matrix[6] = auxiliar_matrix[9];      matrix[10] = auxiliar_matrix[10];    matrix[14] = _selected_camera->MZptr->M[14];
                matrix[3] = 0;                     matrix[7] = 0;                       matrix[11] = 0;                      matrix[15] = 1; 

                glLoadMatrixd(matrix);
                glGetDoublev(GL_MODELVIEW_MATRIX, _selected_camera->MZptr->M);

                printf("Camera set in analisis mode \n");
                break;
            }
        //Set changes to affect only to objects
        case 'o':
        case 'O':
            _change_mode = 'o'; //Sets changes to affect the objects
            printf("Changes now affect only to: Objects\n");
            break;
        
        //Set changes to affect only to the camera
        case 'c':
        case 'C':
            _change_mode = 'c'; //Sets changes to affect the camera
            printf("Changes now affect only to: Camera\n");
            break;

        //Set changes to affect only to lights    
        case 'a':
        case 'A':
            _change_mode = 'a'; //Sets changes to affect the light
            printf("Changes now affect only to: Light\n");
            break;

        case 'm':
        case 'M': 
            printf("Object's material changed \n");
            change_material();
            glutPostRedisplay();
            break;
        
        case 'k':
        case 'K':
            if(lighting_enabled == 0){
                printf("Calculation of the effect of lights enabled\n");
                glEnable(GL_LIGHTING);
                lighting_enabled = 1;
            }else{
                printf("Calculation of the effect of lights diabled\n");
                glDisable(GL_LIGHTING);
                lighting_enabled = 0;
                }
            break;
        //Undo the last change done to an object
        case 'z':
        case 'Z':
            undo();
            break;
          
        case 'v':
        case 'V':
            if (viewpoint == 0)
            {
                viewpoint = 1;
                printf("Object's viewpoint\n");
            }
            else
            {
                viewpoint = 0;
                printf("Outsider's viewpoint\n");
            }
            break;
        //Change between loaded objects
        case 9: /* <TAB> */
            //Check if there's any object selected
            if (_selected_object == 0){
                _selected_object = _first_object;
            } else {
                //If there is, pass to the next object
                _selected_object = _selected_object->next;
                if (_selected_object == 0)
                {
                    _selected_object = _first_object;
                }
            }
            break;

        //Delete the current selected object
        case 127: /* <SUPR> */
            //No memory will be freed if there's no object loaded
            if (_selected_object != 0){
                /*Erasing an object depends on whether it is the first one or not*/
                if (_selected_object == _first_object)
                {
                    /*To remove the first object we just set the first as the current's next*/
                    _first_object = _first_object->next;
                    /*Once updated the pointer to the first object it is save to free the memory*/
                    freeall(_selected_object);
                    free(_selected_object);
                    /*Finally, set the selected to the new first one*/
                    _selected_object = _first_object;

                } else {
                    /*In this case we need to get the previous element to the one we want to erase*/
                    auxiliar_object = _first_object;
                    while (auxiliar_object->next != _selected_object)
                        auxiliar_object = auxiliar_object->next;
                    /*Now we bypass the element to erase*/
                    auxiliar_object->next = _selected_object->next;
                    /*free the memory*/
                    freeall(_selected_object);
                    free(_selected_object);
                    /*and update the selection. It is the previous to the deleted one. */
                    _selected_object = auxiliar_object;
                }
            }
            break;
        
        //ZOOM IN
        case '-': //ZOOM   
            /* Decrease the projection plane; compute the new dimensions*/
            switch (_change_mode)
            {
            case 'c':
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL){ 
                    // with or without pressing CTRL key 
                    }
                    
                    wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
                    he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
                    /*In order to avoid moving the center of the plane, we get its coordinates*/
                    midx = (_ortho_x_max+_ortho_x_min)/2;
                    midy = (_ortho_y_max+_ortho_y_min)/2;
                    /*The new limits are set, keeping the center of the plane*/
                    _ortho_x_max = midx + wd/2;
                    _ortho_x_min = midx - wd/2;
                    _ortho_y_max = midy + he/2;
                    _ortho_y_min = midy - he/2;
                
                break;
            
            case 'o':
                if (_selected_object!=0)
                    scaling_matrix(1.0/KG_SCALE_NUM, 1.0/KG_SCALE_NUM, 1.0/KG_SCALE_NUM);
                break;
            }

            break;
        //ZOOM_OUT
        case '+':
            switch (_change_mode)
            {
            case 'c':
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL){ 
                // with or without pressing CTRL key 
                }
                
                wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                //The new limits are set, keeping the center of the plane//
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;            
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;

                break;

            case 'o':
                if (_selected_object!=0)
                    scaling_matrix(1.0*KG_SCALE_NUM, 1.0*KG_SCALE_NUM, 1.0*KG_SCALE_NUM);
                break;
            }
            break;

        //Prints the program functionalities
        case '?':
            print_help();
            break;

        //Close the program
        case 27: /* <ESC> */
            exit(0);
            break;

        //Prints the pressed key if it has no functionality
        default:
            printf("Default \n");
            /*In the default case we just print the code of the key. This is usefull to define new cases*/
            printf("%d %c\n", key, key);
        }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}

/**
 * @brief Callback function to control de special keyboard keys
 * 
 * @param key key that has been pressed 
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y y coordinate of the mouse pointer when key was pressed
 */
void keyboard_func(int key, int x, int y){
    if (_change_mode = 'o')
        {
            if (_selected_object != 0) //We'll make changes only if there's an object selected
            {
                switch(key){
                    //UP ARROW
                    case GLUT_KEY_UP:
                        switch(_change_type){
                            case 't':
                                translation_matrix(0.0, 1.0, 0.0);
                                break;
                            case 'r':
                                rotation_matrix(1.0, 0.0, 0.0);
                                break;
                            case 'e':
                                scaling_matrix(1.0, 1.0*KG_SCALE_NUM, 1.0);
                                break;
                        }
                        break;
                    
                    //DOWN ARROW
                    case GLUT_KEY_DOWN:
                        switch(_change_type){
                            case 't':
                                translation_matrix(0.0, -1.0, 0.0);
                                break;
                            case 'r':
                                rotation_matrix(-1.0, 0.0, 0.0);
                                break;
                            case 'e':
                                scaling_matrix(1.0, 1.0/KG_SCALE_NUM, 1.0);
                                break;
                        }
                        break;

                    //LEFT ARROW
                    case GLUT_KEY_LEFT:
                        switch(_change_type){
                            case 't':
                                translation_matrix(-1.0, 0.0, 0.0);
                                break;
                            case 'r':
                                rotation_matrix(0.0, -1.0, 0.0);
                                break;
                            case 'e':
                                scaling_matrix(1.0/KG_SCALE_NUM, 1.0, 1.0);
                                break;
                        }
                        break;

                    //RIGHT ARROW
                    case GLUT_KEY_RIGHT: 
                        switch(_change_type){
                            case 't':
                                translation_matrix(1.0, 0.0, 0.0);
                                break;
                            case 'r':
                                rotation_matrix(0.0, 1.0, 0.0);
                                break;
                            case 'e':
                                scaling_matrix(1.0*KG_SCALE_NUM, 1.0, 1.0);
                                break;
                        }
                        break;

                    //AVPAG KEY
                    case GLUT_KEY_PAGE_UP:
                        switch(_change_type){
                            case 't':
                                translation_matrix(0.0, 0.0, 1.0);
                                break;
                            case 'r':
                                rotation_matrix(0.0, 0.0, 1.0);
                                break;
                            case 'e':
                                scaling_matrix(1.0, 1.0, 1.0*KG_SCALE_NUM);
                                break;
                        }
                        break;

                    //REPAG KEY
                    case GLUT_KEY_PAGE_DOWN:
                        switch(_change_type){
                            case 't':
                                translation_matrix(0.0, 0.0, -1.0);
                                break;
                            case 'r':
                                rotation_matrix(0.0, 0.0, -1.0);
                                break;
                            case 'e':
                                scaling_matrix(1.0, 1.0, 1.0/KG_SCALE_NUM);
                                break;
                        }
                        break;
                }
            }
            glutPostRedisplay();
        
        } else if (_change_mode == 'c'){
            if (_selected_camera != 0){
                if (_camera_mode == 'a'){

                    //CAMERA MOVEMENT WHEN SET IN ANALISIS MODE

                    double at_mat[16];
                    double new_at_mat[16];
                    
                    at_matrix(at_mat);
                    new_at_matrix(new_at_mat);  
                    
                    glMatrixMode(GL_MODELVIEW); 
                    glLoadMatrixd(at_mat);

                    switch (key) 
                    {
                        case GLUT_KEY_LEFT: /* izquierda */
                            glRotated(-KG_STEP_ROTATE, _selected_camera->MZptr->M[4],_selected_camera->MZptr->M[5],_selected_camera->MZptr->M[6]);
                            break;

                        case GLUT_KEY_UP: /* arriba */
                            glRotated(KG_STEP_ROTATE, _selected_camera->MZptr->M[0],_selected_camera->MZptr->M[1],_selected_camera->MZptr->M[2]);
                            break;

                        case GLUT_KEY_RIGHT: /* derecha */
                            glRotated(KG_STEP_ROTATE, _selected_camera->MZptr->M[4],_selected_camera->MZptr->M[5],_selected_camera->MZptr->M[6]);
                            break;

                        case GLUT_KEY_DOWN: /* abajo */
                            glRotated(-KG_STEP_ROTATE, _selected_camera->MZptr->M[0],_selected_camera->MZptr->M[1],_selected_camera->MZptr->M[2]);
                            break;
                    }
                    
                    glMultMatrixd(new_at_mat);
                    glMultMatrixd(_selected_camera->MZptr->M);
                    
                    MZ* mlagptr = (MZ *)(malloc(sizeof(MZ)));
                    
                    glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
                    
                    mlagptr->hptr = _selected_camera->MZptr;
                    _selected_camera->MZptr = mlagptr;
                    glutPostRedisplay();
        
                }else{
                    switch(key){
                        //UP ARROW
                        case GLUT_KEY_UP:
                            switch(_change_type){
                                case 't':
                                    translation_matrix(0.0, 1.0, 0.0);
                                    break;
                                case 'r':
                                    rotation_matrix(1.0, 0.0, 0.0);
                                    break;
                                case 'e':
                                    scaling_matrix(1.0, 1.0*KG_SCALE_NUM, 1.0);
                                    break;
                            }
                            break;
                        
                        //DOWN ARROW
                        case GLUT_KEY_DOWN:
                            switch(_change_type){
                                case 't':
                                    translation_matrix(0.0, -1.0, 0.0);
                                    break;
                                case 'r':
                                    rotation_matrix(-1.0, 0.0, 0.0);
                                    break;
                                case 'e':
                                    scaling_matrix(1.0, 1.0/KG_SCALE_NUM, 1.0);
                                    break;
                            }
                            break;

                        //LEFT ARROW
                        case GLUT_KEY_LEFT:
                            switch(_change_type){
                                case 't':
                                    translation_matrix(-1.0, 0.0, 0.0);
                                    break;
                                case 'r':
                                    rotation_matrix(0.0, -1.0, 0.0);
                                    break;
                                case 'e':
                                    scaling_matrix(1.0/KG_SCALE_NUM, 1.0, 1.0);
                                    break;
                            }
                            break;

                        //RIGHT ARROW
                        case GLUT_KEY_RIGHT: 
                            switch(_change_type){
                                case 't':
                                    translation_matrix(1.0, 0.0, 0.0);
                                    break;
                                case 'r':
                                    rotation_matrix(0.0, 1.0, 0.0);
                                    break;
                                case 'e':
                                    scaling_matrix(1.0*KG_SCALE_NUM, 1.0, 1.0);
                                    break;
                            }
                            break;

                        //AVPAG KEY
                        case GLUT_KEY_PAGE_UP:
                            switch(_change_type){
                                case 't':
                                    translation_matrix(0.0, 0.0, 1.0);
                                    break;
                                case 'r':
                                    rotation_matrix(0.0, 0.0, 1.0);
                                    break;
                                case 'e':
                                    scaling_matrix(1.0, 1.0, 1.0*KG_SCALE_NUM);
                                    break;
                            }
                            break;

                        //REPAG KEY
                        case GLUT_KEY_PAGE_DOWN:
                            switch(_change_type){
                                case 't':
                                    translation_matrix(0.0, 0.0, -1.0);
                                    break;
                                case 'r':
                                    rotation_matrix(0.0, 0.0, -1.0);
                                    break;
                                case 'e':
                                    scaling_matrix(1.0, 1.0, 1.0/KG_SCALE_NUM);
                                    break;
                            }
                            break;
                    }  
                    glutPostRedisplay();
                } 
            }
        } else {
            switch (key){
                case GLUT_KEY_F1:
                    argi_aktiboa = 0;
                    if (bonbilla_piztuta == 0)
                    {
                        bonbilla_piztuta = 1;
                        printf("Bonbilla aktibatuta\n");
                        glEnable(GL_LIGHT0);
                    }
                    else
                    {
                        printf("Bonbilla itzalita\n");
                        bonbilla_piztuta = 0;
                        glDisable(GL_LIGHT0);
                    }
                    glutPostRedisplay();
                    break;
                
                case GLUT_KEY_F2:
                    argi_aktiboa = 1;
                    if (eguzkia_piztuta == 0)
                    {
                        eguzkia_piztuta = 1;
                        printf("Eguzkia aktibatuta\n");
                        glEnable(GL_LIGHT1);
                    }
                    else
                    {
                        printf("Eguzkia itzalita\n");
                        eguzkia_piztuta = 0;
                        glDisable(GL_LIGHT1);
                    }
                    glutPostRedisplay();
                    break;
                
                case GLUT_KEY_F3:
                    argi_aktiboa = 2;
                    if (obj_fokoa_piztuta == 0)
                    {
                        obj_fokoa_piztuta = 1;
                        printf("Objektu fokoa aktibatuta\n");
                        glEnable(GL_LIGHT2);
                    }
                    else
                    {
                        printf("Objektu fokoa itzalita\n");
                        obj_fokoa_piztuta = 0;
                        glDisable(GL_LIGHT2);
                    }
                    glutPostRedisplay();
                    break;

                case GLUT_KEY_F4:
                    argi_aktiboa = 3;
                    if (kam_fokoa_piztuta == 0)
                    {
                        kam_fokoa_piztuta = 1;
                        printf("Kamera fokoa aktibatuta\n");
                        glEnable(GL_LIGHT3);
                    }
                    else
                    {
                        kam_fokoa_piztuta = 0;
                        printf("Kamera fokoa itzalita\n");
                        glDisable(GL_LIGHT3);
                    }
                    glutPostRedisplay();
                    break;

                case GLUT_KEY_F9:
                    if (orokorra_piztuta == 1)
                    {
                        orokorra_piztuta = 0;
                        glDisable(GL_LIGHT0);
                        glDisable(GL_LIGHT1);
                        glDisable(GL_LIGHT2);
                        glDisable(GL_LIGHT3);
                    }
                    else
                    {
                        orokorra_piztuta = 1;
                        if (bonbilla_piztuta == 1)
                        {
                            glEnable(GL_LIGHT0);
                        }
                        if (eguzkia_piztuta == 1)
                        {
                            glEnable(GL_LIGHT1);
                        }
                        if (obj_fokoa_piztuta == 1)
                        {
                            glEnable(GL_LIGHT2);
                        }
                        if (kam_fokoa_piztuta == 1)
                        {
                            glEnable(GL_LIGHT3);
                        }
                    }
                    glutPostRedisplay();
                    break;
                
                case GLUT_KEY_F12:
                    if (_selected_object->flat_smooth == 1)
                    {
                        _selected_object->flat_smooth = 0;
                        printf("FLAT aktibatuta\n");
                    }
                    else
                    {
                        _selected_object->flat_smooth = 1;
                        printf("SMOOTH aktibatuta\n");
                    }
                    glutPostRedisplay();
                    break;

                default:  

                    double aux_mat[16];

                    aux_mat[0] = 1;
                    aux_mat[4] = 0;
                    aux_mat[8] = global_lighting[argi_aktiboa].spot_direction[0];
                    aux_mat[12] = global_lighting[argi_aktiboa].position[0];
                    aux_mat[1] = 0;
                    aux_mat[5] = 1;
                    aux_mat[9] = global_lighting[argi_aktiboa].spot_direction[1];
                    aux_mat[13] = global_lighting[argi_aktiboa].position[1];
                    aux_mat[2] = 0;
                    aux_mat[6] = 0;
                    aux_mat[10] = global_lighting[argi_aktiboa].spot_direction[2];
                    aux_mat[14] = global_lighting[argi_aktiboa].position[2];
                    aux_mat[3] = 0;
                    aux_mat[7] = 0;
                    aux_mat[11] = 0;
                    aux_mat[15] = 1;

                    glLoadIdentity();

                    switch(argi_aktiboa){
                        case 0:
                            switch (_change_type){
                                case 't':
                                    switch (key){
                                        case GLUT_KEY_LEFT:
                                            printf("entro\n");
                                            glTranslated(-KG_TRAN_STEP, 0, 0);
                                            break;
                                        case GLUT_KEY_RIGHT:
                                            glTranslated(KG_TRAN_STEP, 0, 0);
                                            break;
                                        case GLUT_KEY_UP:
                                            glTranslated(0, KG_TRAN_STEP, 0);
                                            break;
                                        case GLUT_KEY_DOWN:
                                            glTranslated(0, -KG_TRAN_STEP, 0);
                                            break;
                                        case GLUT_KEY_PAGE_DOWN:
                                            glTranslated(0, 0, -KG_TRAN_STEP);
                                            break;
                                        case GLUT_KEY_PAGE_UP:
                                            glTranslated(0, 0, KG_TRAN_STEP);
                                            break;
                                            
                                        }
                                        break;

                                    case 'i':
                                        switch (key){
                                            case GLUT_KEY_UP:
                                                intentsitatea_aldatu(1,0);
                                                glLightfv(GL_LIGHT0, GL_AMBIENT, global_lighting[0].ambient);
                                                glLightfv(GL_LIGHT0, GL_DIFFUSE, global_lighting[0].diffuse);
                                                glLightfv(GL_LIGHT0, GL_SPECULAR, global_lighting[0].specular);
                                                break;
                                            case GLUT_KEY_DOWN:
                                                intentsitatea_aldatu(-1,0);
                                                glLightfv(GL_LIGHT0, GL_AMBIENT, global_lighting[0].ambient);
                                                glLightfv(GL_LIGHT0, GL_DIFFUSE, global_lighting[0].diffuse);
                                                glLightfv(GL_LIGHT0, GL_SPECULAR, global_lighting[0].specular);
                                                break;
                                        }
                                        break;
                                    }
                                    break;
                                
                        case 1:
                            switch (_change_type){
                                case 'r':
                                    switch (key){
                                        case GLUT_KEY_LEFT:
                                            glRotated(-KG_STEP_ROTATE, 0, 1, 0);
                                            break;
                                        case GLUT_KEY_RIGHT:
                                            glRotated(KG_STEP_ROTATE, 0, 1, 0);
                                            break;
                                        case GLUT_KEY_UP:
                                            glRotated(-KG_STEP_ROTATE, 1, 0, 0);
                                            break;
                                        case GLUT_KEY_DOWN:
                                            glRotated(KG_STEP_ROTATE, 1, 0, 0);
                                            break;
                                        case GLUT_KEY_PAGE_DOWN:
                                            glRotated(KG_STEP_ROTATE, 0, 0, -1);
                                            break;
                                        case GLUT_KEY_PAGE_UP:
                                            glRotated(KG_STEP_ROTATE, 0, 0, 1);
                                            break;
                                    }
                                break;

                                case 'i':
                                    switch (key){
                                        case GLUT_KEY_UP:
                                            intentsitatea_aldatu(1,1);
                                            glLightfv(GL_LIGHT1, GL_AMBIENT, global_lighting[1].ambient);
                                            glLightfv(GL_LIGHT1, GL_DIFFUSE, global_lighting[1].diffuse);
                                            glLightfv(GL_LIGHT1, GL_SPECULAR, global_lighting[1].specular);
                                            break;
                                        case GLUT_KEY_DOWN:
                                            intentsitatea_aldatu(-1,1);
                                            glLightfv(GL_LIGHT1, GL_AMBIENT, global_lighting[1].ambient);
                                            glLightfv(GL_LIGHT1, GL_DIFFUSE, global_lighting[1].diffuse);
                                            glLightfv(GL_LIGHT1, GL_SPECULAR, global_lighting[1].specular);
                                            break;
                                    }
                                    break;

                            }
                            break;
                        case 2:
                            if (_change_type == 'i'){
                                switch (key){
                                    case GLUT_KEY_UP:
                                        intentsitatea_aldatu(1,2);
                                        glLightfv(GL_LIGHT2, GL_AMBIENT, global_lighting[2].ambient);
                                        glLightfv(GL_LIGHT2, GL_DIFFUSE, global_lighting[2].diffuse);
                                        glLightfv(GL_LIGHT2, GL_SPECULAR, global_lighting[2].specular);
                                        break;
                                    case GLUT_KEY_DOWN:
                                        intentsitatea_aldatu(-1,2);
                                        glLightfv(GL_LIGHT2, GL_AMBIENT, global_lighting[2].ambient);
                                        glLightfv(GL_LIGHT2, GL_DIFFUSE, global_lighting[2].diffuse);
                                        glLightfv(GL_LIGHT2, GL_SPECULAR, global_lighting[2].specular);
                                        break;
                                }
                            }else{
                                printf("Ezin da eraldaketa hori egin objektuaren fokoan.\n");
                            }
                            break;
                        
                        case 3:
                            if (_change_type == 'i'){

                            switch (key){
                                case GLUT_KEY_UP:
                                    intentsitatea_aldatu(1,3);
                                    glLightfv(GL_LIGHT3, GL_AMBIENT, global_lighting[3].ambient);
                                    glLightfv(GL_LIGHT3, GL_DIFFUSE, global_lighting[3].diffuse);
                                    glLightfv(GL_LIGHT3, GL_SPECULAR, global_lighting[3].specular);
                                    break;
                                case GLUT_KEY_DOWN:
                                    intentsitatea_aldatu(-1,3);
                                    glLightfv(GL_LIGHT3, GL_AMBIENT, global_lighting[3].ambient);
                                    glLightfv(GL_LIGHT3, GL_DIFFUSE, global_lighting[3].diffuse);
                                    glLightfv(GL_LIGHT3, GL_SPECULAR, global_lighting[3].specular);
                                    break;
                                }
                            }else{
                                printf("Ezin da eraldaketa hori egin kamararen fokoan.\n");
                            }
                            break;
                        }
                        glMultMatrixd(aux_mat);
                        glGetDoublev(GL_MODELVIEW_MATRIX, aux_mat);

                        global_lighting[argi_aktiboa].spot_direction[0] = aux_mat[8];
                        global_lighting[argi_aktiboa].spot_direction[1] = aux_mat[9];
                        global_lighting[argi_aktiboa].spot_direction[2] = aux_mat[10];

                        global_lighting[argi_aktiboa].position[0] = aux_mat[12];
                        global_lighting[argi_aktiboa].position[1] = aux_mat[13];
                        global_lighting[argi_aktiboa].position[2] = aux_mat[14];
                        global_lighting[argi_aktiboa].position[3] = aux_mat[15];
                        glutPostRedisplay();
                        break;
                }
        }
        glutPostRedisplay();
}

