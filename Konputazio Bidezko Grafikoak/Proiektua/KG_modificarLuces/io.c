#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define ARGIA_EZ 0
#define ARGIA_BAI 1

extern object3d * _first_object;
extern object3d * _selected_object;
extern object3d * _first_kamera;
extern object3d * _selected_kamera;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern char aldaketa_mota;
extern int LG;
//extern double traslazioa;
extern double biraketa_angelua;
extern double eskalaketa;
extern int obj_mota;
extern int nondik_ikusi;

argiak gl_argiak[8];

int argia_martxan = ARGIA_BAI;
int argi_mota=0; /*1: bonbilla, 2: eguzkia, 3: obj_argia, 4: kam_argia*/
int KAM_ARGIA_BAI=0; /* Kamerari atzikitzen diogun argia piztuta dago (1) ala ez (0)*/
int OBJ_ARGIA_BAI=0; /* Objektuari atzikitzen diogun argia piztuta dago (1) ala ez (0)*/
int EGUZKIA_BAI=0;   /* Eguzkiaren argia piztuta dago (1) ala ez (0)*/
int BONBILLA_BAI=0;  /* Bonbillaren argia piztuta dago (1) ala ez (0)*/
materialak *Turquoise;
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
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
    printf("\n\n");
}
// Objektu bat ezabatzean, memoria askatu baino lehen, honek dituen erakusleen memoriak (barne memoriak) askatzeko funtzioa
void obj_mem_askatu(object3d *optr)
{
    int i;
    mz *auxptr;
    for (i=0; i<optr->num_faces;i++)
    {
        free(optr->face_table[i].vertex_table);
    }
    free(optr->face_table);
    free(optr->vertex_table);
    /*TODO matrizeekin zer pasatzen da?*/
    for(auxptr=optr->mzptr; auxptr!=0; auxptr=optr->mzptr)
    {
        optr->mzptr=optr->mzptr->hptr;
        free(auxptr);
    }
    
}
/*aldaketak aplikatu*/
void aldaketak_aplikatu(double *mzptr) {
    mz *mlagptr;
    glMatrixMode(GL_MODELVIEW);
    switch(LG){
        case 0:/*lokala*/
            if (obj_mota == 0){ /*objektua bada*/
                glLoadMatrixd(_selected_object->mzptr->M);
                glMultMatrixd(&(mzptr[0]));
                mlagptr = (mz*)(malloc(sizeof(mz)));
                glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr -> M);
                mlagptr->hptr = _selected_object->mzptr;
                _selected_object->mzptr = mlagptr;
                glutPostRedisplay();

                break;
            }
            else if (obj_mota == 1){ /*kamera bada: hegaldia*/
                glLoadMatrixd(_selected_kamera->mzptr->M);
                glMultMatrixd(&(mzptr[0]));
                mlagptr = (mz*)(malloc(sizeof(mz)));
                glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr -> M);
                mlagptr->hptr = _selected_kamera->mzptr;
                _selected_kamera->mzptr = mlagptr;
                glutPostRedisplay();
                break;
            }
            break;

        case 1: /*globala*/
            if (obj_mota == 0){/*objektua bada*/
                glLoadMatrixd(&(mzptr[0]));
                glMultMatrixd(_selected_object->mzptr->M);
                mlagptr = (mz*)(malloc(sizeof(mz)));
                glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
                mlagptr->hptr = _selected_object->mzptr;
                _selected_object->mzptr = mlagptr;
                glutPostRedisplay();
                break;
            }
            else{ /*kamera bada: analisi modua*/
                glLoadMatrixd(&(mzptr[0]));
                glMultMatrixd(_selected_kamera->mzptr->M);
                mlagptr = (mz*)(malloc(sizeof(mz)));
                glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
                mlagptr->hptr = _selected_kamera->mzptr;
                _selected_kamera->mzptr = mlagptr;
                glutPostRedisplay();
                break;
                }
        }
}

 /* Traslazio matrizea sortu */
void lortu_traslazio_matrizea(double *mzptr, double x, double y, double z){
    /*traslazio matrizea*/
    mzptr[0]=1.0;
    mzptr[1]=0.0;
    mzptr[2]=0.0;
    mzptr[3]=0.0;
    mzptr[4]=0.0;
    mzptr[5]=1.0;
    mzptr[6]=0.0;
    mzptr[7]=0.0;
    mzptr[8]=0.0;
    mzptr[9]=0.0;
    mzptr[10]=1.0;
    mzptr[11]=0.0;
    mzptr[12]=x;
    mzptr[13]=y;
    mzptr[14]=z;
    mzptr[15]=1.0;
}

 /* Biraketa matrizea sortu */
void lortu_biraketa_matrizea(double *mzptr, double x, double y, double z){
    /*biraketa matrizea*/
    double alpha=x*biraketa_angelua;
    double beta=y*biraketa_angelua;
    double gamma=z*biraketa_angelua;
    mzptr[0] = cos(beta) * cos(gamma);   
    mzptr[1] = cos(beta) * sin(gamma);   
    mzptr[2] = -sin(beta);                                                                                
    mzptr[3] = 0.0;                                                                                                                                         
    mzptr[4] = sin(alpha) * sin(beta) * cos (gamma) - cos(alpha) * sin(gamma);
    mzptr[5] = sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma);
    mzptr[6] = sin(alpha) * cos(beta); 
    mzptr[7] = 0.0; 
    mzptr[8] = cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma);
    mzptr[9] = cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma); 
    mzptr[10] = cos(alpha) * cos(beta);            
    mzptr[11] = 0.0;
    mzptr[12] = 0.0;
    mzptr[13] = 0.0;
    mzptr[14] = 0.0;
    mzptr[15] = 1.0;
}

 /* Eskalaketa matrizea sortu */
void lortu_eskalaketa_matrizea(double *mzptr, double p, double q, double r){
    /*eskalaketa matrizea*/
    mzptr[0]=p;
    mzptr[1]=0.0;
    mzptr[2]=0.0;
    mzptr[3]=0.0;
    mzptr[4]=0.0;
    mzptr[5]=q;
    mzptr[6]=0.0;
    mzptr[7]=0.0;
    mzptr[8]=0.0;
    mzptr[9]=0.0;
    mzptr[10]=r;
    mzptr[11]=0.0;
    mzptr[12]=0.0;
    mzptr[13]=0.0;
    mzptr[14]=0.0;
    mzptr[15]=1.0;
}


/**
 * @brief Callback function to control the special keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */

/*Objektuekin lan egitean, aldaketa lortu teklen arabera*/
void transformazioa_lortu_obj(int tekla){
    double M_ald[16];
    if (_selected_object!=0){
        switch(tekla){
            case GLUT_KEY_LEFT:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),-1.0,0.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,-1.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0/eskalaketa,1.0,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;
            case GLUT_KEY_RIGHT:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),1.0,0.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,1.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0*eskalaketa,1.0,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;

                }
                break;
            case GLUT_KEY_UP:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,1.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),-1.0,0.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0*eskalaketa,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;
                    }
                break;

            case GLUT_KEY_DOWN:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,-1.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),1.0,0.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0/eskalaketa,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;

            case GLUT_KEY_PAGE_UP:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,0.0,-1.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,0.0,1.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0,1.0*eskalaketa); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;
            case GLUT_KEY_PAGE_DOWN:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,0.0,1.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,0.0,-1.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0,1.0/eskalaketa); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;
            }
            /*aldaketa burutzeko funtziora deitu*/
            aldaketak_aplikatu(&(M_ald[0]));
            /*Aldaketa berriak erakutsi*/
            glutPostRedisplay();
    }
    else{
        printf("KONTUZ! Ez dago objekturik. Mesedez objektu bat aukeratu.");

    }

}

void matrixAT(double * mat){
 mat[0]=1;       mat[4]=0;         mat[8]=0;         mat[12]=_selected_object->mzptr->M[12];
 mat[1]=0;       mat[5]=1;         mat[9]=0;         mat[13]=_selected_object->mzptr->M[13];
 mat[2]=0;       mat[6]=0;         mat[10]=1;        mat[14]=_selected_object->mzptr->M[14];
 mat[3]=0;       mat[7]=0;         mat[11]=0;        mat[15]=1;
         
             
 
}

void matrixATberria(double * bmat){
 bmat[0]=1;        bmat[4]=0;         bmat[8]=0;         bmat[12]=-_selected_object->mzptr->M[12];
 bmat[1]=0;        bmat[5]=1;         bmat[9]=0;         bmat[13]=-_selected_object->mzptr->M[13];
 bmat[2]=0;        bmat[6]=0;         bmat[10]=1;        bmat[14]=-_selected_object->mzptr->M[14];
 bmat[3]=0;        bmat[7]=0;         bmat[11]=0;        bmat[15]=1;   
}

/*Kamerarekin lan egitean, aldaketa lortu teklen arabera*/
void transformazioa_lortu_kam(int tekla){
    double M_ald[16];
    if(LG==0){ /*Hegaldi moduan egin beharreko aldaketak lortu*/
        if (_selected_object!=0){
        switch(tekla){
            case GLUT_KEY_LEFT:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),-1.0,0.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,-1.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0/eskalaketa,1.0,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;
            case GLUT_KEY_RIGHT:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),1.0,0.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,1.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0*eskalaketa,1.0,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;

                }
                break;
            case GLUT_KEY_UP:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,1.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),-1.0,0.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0*eskalaketa,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;
                    }
                break;

            case GLUT_KEY_DOWN:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,-1.0,0.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),1.0,0.0,0.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0/eskalaketa,1.0); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;

            case GLUT_KEY_PAGE_UP:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,0.0,-1.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,0.0,1.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0,1.0*eskalaketa); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;
            case GLUT_KEY_PAGE_DOWN:
                switch(aldaketa_mota){
                    case 't':
                        lortu_traslazio_matrizea(&(M_ald[0]),0.0,0.0,1.0); //T sakatzeak traslazioa (lekuz aldaketa) adierazten du.
                        break;
                    case 'r':
                        lortu_biraketa_matrizea(&(M_ald[0]),0.0,0.0,-1.0); //R sakatzeak biraketa adierazten du.
                        break;
                    case 'e':
                        lortu_eskalaketa_matrizea(&(M_ald[0]),1.0,1.0,1.0/eskalaketa); //E sakatzeak eskalaketa adierazten du.
                        break;
                }
                break;
            }
            /*aldaketa burutzeko funtziora deitu*/
            aldaketak_aplikatu(&(M_ald[0]));
        }
    } else{ /*LG=1; Analisi moduan egin beharreko aldaketak lortu*/
        if (tekla==GLUT_KEY_DOWN || tekla==GLUT_KEY_UP || tekla==GLUT_KEY_LEFT || tekla==GLUT_KEY_RIGHT){
            double Mtat[16];
            double MtNat[16];
            matrixAT(Mtat);
            matrixATberria(MtNat);  
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixd(Mtat);

            switch (tekla) {
            case GLUT_KEY_LEFT:
                glRotated(-KG_STEP_ROTATE,_selected_kamera->mzptr->M[4],_selected_kamera->mzptr->M[5],_selected_kamera->mzptr->M[6]);
                break;

            case GLUT_KEY_UP:
                glRotated(KG_STEP_ROTATE,_selected_kamera->mzptr->M[0],_selected_kamera->mzptr->M[1],_selected_kamera->mzptr->M[2]);
                break;

            case GLUT_KEY_RIGHT:
                glRotated(KG_STEP_ROTATE,_selected_kamera->mzptr->M[4],_selected_kamera->mzptr->M[5],_selected_kamera->mzptr->M[6]);
                break;

            case GLUT_KEY_DOWN:
                glRotated(-KG_STEP_ROTATE,_selected_kamera->mzptr->M[0],_selected_kamera->mzptr->M[1],_selected_kamera->mzptr->M[2]);
                break;
            }
            glMultMatrixd(MtNat);
            glMultMatrixd(_selected_kamera->mzptr->M);
            mz* mlagptr = (mz *)(malloc(sizeof(mz)));
            glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
            mlagptr->hptr = _selected_kamera->mzptr;
            _selected_kamera->mzptr = mlagptr;
           
        }  
    }
    glutPostRedisplay();
}


void matrize_biderketa_argia(int tekla){

switch(tekla){
    case GLUT_KEY_LEFT:
        glLoadIdentity;
        switch (aldaketa_mota){
        case 'r':
            if(argi_mota==1){
                glRotated(-KG_STEP_ROTATE,0,1,0);
            }
            else{
                break;
            }

            break;

        case 't':
            if(argi_mota==0){
               glTranslated(-KG_STEP_MOVE,0,0);
            }
            else{
                 break;
            }
            
            break;
        }
    break;

    case GLUT_KEY_UP:
        glLoadIdentity;
        switch (aldaketa_mota){
        case 'r':
            if(argi_mota==1){
                glRotated(-KG_STEP_ROTATE,1,0,0);
            }
            else{
                break;
            }
            
            break;
        case 'i':
            printf("aumentar intensidad luz\n");
            printf("esta funcion esta sin implementar\n");
            //glScaled(1,KG_STEP_SCALE,1);
            break;
        case 't':
            if(argi_mota==0){
                glTranslated(0,KG_STEP_MOVE,0);
            }
            else{
                break;
            }
            
            break;
        }
    break;

    case GLUT_KEY_RIGHT:
        switch (aldaketa_mota){
        case 'r':
            if(argi_mota==1){
                glRotated(KG_STEP_ROTATE,0,1,0);
            }
            else{
               break;
            }
            break;

        case 't':
            if(argi_mota==0){
                glTranslated(KG_STEP_MOVE,0,0);
            }
            else{
                break;
            }
            break;
        }
    break;

    case GLUT_KEY_DOWN:
        switch (aldaketa_mota){
        case 'r':
            if(argi_mota==1){
                glRotated(KG_STEP_ROTATE,1,0,0);   
            }
            else{
               break;
            }
            break;
        case 'i':
            printf("disminuir intensidad luz\n");
            printf("esta funcion esta sin implementar\n");
        
            break;
        case 't':
            if(argi_mota==0){
                glTranslated(0,-KG_STEP_MOVE,0);
            }
            else{
                break;
            }

            break;
        }
    break;

    case GLUT_KEY_PAGE_DOWN:
        switch (aldaketa_mota){
            case 'r':
            if(argi_mota==1){
                glRotated(KG_STEP_ROTATE,0,0,-1);   
            }
            else{
                 break;
            }
                break;
 
            case 't':
            if(argi_mota==0){
                glTranslated(0,0,-KG_STEP_MOVE);               
            }
            else{
                break;
            }
                break;
        }
        break;

    case GLUT_KEY_PAGE_UP:
        switch (aldaketa_mota){
            case 'r':
            if(argi_mota==1){
                glRotated(KG_STEP_ROTATE,0,0,1);
            }
            else{
                break;
            }

                break;

            case 't':
            if(argi_mota==0){
                glTranslated(0,0,KG_STEP_MOVE);
            }
            else{
                break;
            }
                break;
        }
        break;
    }
 
}

void transformazioa_lortu_argia(int tekla){
        double AUX[16];

        AUX[0]=1;   AUX[4]=0;   AUX[8]=gl_argiak[argi_mota].direkzioa[0];   AUX[12]=gl_argiak[argi_mota].a_posizioa[0];
        AUX[1]=0;   AUX[5]=1;   AUX[9]=gl_argiak[argi_mota].direkzioa[1];   AUX[13]=gl_argiak[argi_mota].a_posizioa[1];
        AUX[2]=0;   AUX[6]=0;   AUX[10]=gl_argiak[argi_mota].direkzioa[2];  AUX[14]=gl_argiak[argi_mota].a_posizioa[2];
        AUX[3]=0;   AUX[7]=0;   AUX[11]=0;                                  AUX[15]=1;

        glLoadIdentity();
        matrize_biderketa_argia(tekla);
        glMultMatrixd(AUX);
        glGetDoublev(GL_MODELVIEW_MATRIX, AUX);

        gl_argiak[argi_mota].direkzioa[0]=AUX[8];
        gl_argiak[argi_mota].direkzioa[1]=AUX[9];
        gl_argiak[argi_mota].direkzioa[2]=AUX[10];

        gl_argiak[argi_mota].a_posizioa[0]= AUX[12];
        gl_argiak[argi_mota].a_posizioa[1]=AUX[13];
        gl_argiak[argi_mota].a_posizioa[2]= AUX[14];
        gl_argiak[argi_mota].a_posizioa[3]=AUX[15];

        glutPostRedisplay();

         switch (tekla) {
            case GLUT_KEY_F1: 
                if(BONBILLA_BAI==0){
                    printf("Bonbilla piztu\n");
                    BONBILLA_BAI=1;
                    glEnable(GL_LIGHT0);
                }
                else{
                    BONBILLA_BAI=0;
                    printf("Bonbilla itzali\n");
                    glDisable(GL_LIGHT0); 
                }
                glutPostRedisplay();
                break;

            case GLUT_KEY_F2: 
                if(EGUZKIA_BAI==0){
                    printf("Eguzkia piztu\n");
                    EGUZKIA_BAI=1;
                    glEnable(GL_LIGHT1);
                }
                else{
                    EGUZKIA_BAI=0;
                    printf("Eguzkia itzali\n");
                    glDisable(GL_LIGHT1); 
                }
                glutPostRedisplay();
                break;

            case GLUT_KEY_F3: 
                if(OBJ_ARGIA_BAI==0){ 
                    gl_argiak[3].type = OBJ_ARGIA;
                    printf("Objektuaren argia piztu\n");
                    OBJ_ARGIA_BAI=1;
                    glEnable(GL_LIGHT2);
                }
                else{
                    OBJ_ARGIA_BAI=0;
                     printf("Objektuaren argia itzali\n");
                    glDisable(GL_LIGHT2); 
                }
                glutPostRedisplay();
                break;

            case GLUT_KEY_F4:
                
                if(KAM_ARGIA_BAI==0){
                    printf("Kameraren argia piztu\n");
                    KAM_ARGIA_BAI=1;
                    glEnable(GL_LIGHT3);
                }
                else{
                    KAM_ARGIA_BAI=0;
                    printf("Kameraren argia itzali\n");
                    glDisable(GL_LIGHT3); 
                }
                glutPostRedisplay();
                break;

            case GLUT_KEY_F9:
                if (argia_martxan == 0){
                    printf("Argia martxan.\n");
                    argia_martxan = 1;
                    if(BONBILLA_BAI==1){
                    glEnable(GL_LIGHT0);
                    }
                    if(EGUZKIA_BAI=1){
                    glEnable(GL_LIGHT1);
                    }
                    if(OBJ_ARGIA_BAI==1){
                    glDisable(GL_LIGHT2);
                    }
                    if(KAM_ARGIA_BAI==1){
                    glDisable(GL_LIGHT3);
                    }
                } else {
                    printf("Argirik ez.\n");
                    argia_martxan= 0;
                    glDisable(GL_LIGHT0);
                    glDisable(GL_LIGHT1);
                    glDisable(GL_LIGHT2);
                    glDisable(GL_LIGHT3);
                }
                glutPostRedisplay();
                break;

            case GLUT_KEY_F12: 
                if(_selected_object->fs==SMOOTH){
                    _selected_object->fs=FLAT;
                }
                else{
                    _selected_object->fs=SMOOTH;
                }
                glutPostRedisplay();
                break;
        }
        glutPostRedisplay();
 }



void tekla_berezien_arretarako_funtzioa(int tekla, int x, int y) {
     if (obj_mota == 0){ /*Objektua*/
        if (_selected_object!=0){
            transformazioa_lortu_obj(tekla);
        }   
    }
    else if (obj_mota == 1){ /*Kamera*/
        if (_selected_kamera != 0) {
            transformazioa_lortu_kam(tekla);
        }
    }
    else if (obj_mota==2){ /*Argia*/
        if (argi_mota != 0) {
            transformazioa_lortu_argia(tekla);
        }
    }
    
    glutPostRedisplay(); 
}


vector3 bektorea_lortu(point3 p1, point3 p2){
    vector3 b;

    b.x= p1.x - p2.x;
    b.y= p1.y - p2.y;
    b.z= p1.z - p2.z;

    return b;
}

void aurpegien_b_normal_kalkulatu(){
    vector3 vec1, vec2, b_normala;
    GLdouble modulua;                                                
    int ind1, ind2, ind0;
    int * erpinKopAurpegiko;

    for (int i=0; i<_selected_object->num_faces; i++){
        

        erpinKopAurpegiko=_selected_object->face_table[i].vertex_table;
        ind0= erpinKopAurpegiko[0];
        ind1= erpinKopAurpegiko[1];
        ind2= erpinKopAurpegiko[2];
     
        vec1= bektorea_lortu(_selected_object->vertex_table[ind1].coord, _selected_object->vertex_table[ind0].coord);
        vec2= bektorea_lortu(_selected_object->vertex_table[ind2].coord, _selected_object->vertex_table[ind0].coord);


        b_normala.x= (vec1.y * vec2.z)-(vec2.y * vec1.z);
        b_normala.y= -((vec1.x * vec2.z)-(vec2.x * vec1.z));
        b_normala.z= (vec1.x * vec2.y)-(vec2.x * vec1.y);

       
        modulua= sqrt(b_normala.x*b_normala.x+b_normala.y*b_normala.y+b_normala.z*b_normala.z);

        b_normala.x=  b_normala.x/modulua;
        b_normala.y=  b_normala.y/modulua; 
        b_normala.z=  b_normala.z/modulua;
  
        _selected_object->face_table[i].b_normala.x= b_normala.x;
        _selected_object->face_table[i].b_normala.y= b_normala.y;
        _selected_object->face_table[i].b_normala.z= b_normala.z;

    }
}

void argia_ezarri(int i){
    switch (i){
    case 0:

        glLightfv(GL_LIGHT0, GL_POSITION, gl_argiak[i].a_posizioa);
        glLightfv(GL_LIGHT0, GL_AMBIENT, gl_argiak[i].a_ingurunea); 
        glLightfv(GL_LIGHT0, GL_DIFFUSE, gl_argiak[i].a_difusioa); 
        glLightfv(GL_LIGHT0, GL_SPECULAR, gl_argiak[i].a_espekularra); 
        break;
    
    case 1:
        glLightfv(GL_LIGHT1, GL_AMBIENT, gl_argiak[i].a_ingurunea); 
        glLightfv(GL_LIGHT1, GL_DIFFUSE, gl_argiak[i].a_difusioa); 
        glLightfv(GL_LIGHT1, GL_SPECULAR, gl_argiak[i].a_espekularra); 
        glLightfv(GL_LIGHT1, GL_POSITION, gl_argiak[i].a_posizioa); 
        break;

    case 2:
        glLightfv(GL_LIGHT2, GL_AMBIENT, gl_argiak[i].a_ingurunea); 
        glLightfv(GL_LIGHT2, GL_DIFFUSE, gl_argiak[i].a_difusioa); 
        glLightfv(GL_LIGHT2, GL_SPECULAR, gl_argiak[i].a_espekularra);
        glLightfv(GL_LIGHT2, GL_POSITION, gl_argiak[i].a_posizioa); 
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, gl_argiak[i].direkzioa);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, gl_argiak[i].cut_off);
        break;

    case 3:
        glLightfv(GL_LIGHT3, GL_AMBIENT, gl_argiak[i].a_ingurunea); 
        glLightfv(GL_LIGHT3, GL_DIFFUSE, gl_argiak[i].a_difusioa); 
        glLightfv(GL_LIGHT3, GL_SPECULAR, gl_argiak[i].a_espekularra);
        glLightfv(GL_LIGHT3, GL_POSITION, gl_argiak[i].a_posizioa); 
        if (gl_argiak[i].type == 2){
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, gl_argiak[i].direkzioa);
            glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, gl_argiak[i].cut_off);
        }
        break;

    case 4:
        glLightfv(GL_LIGHT4, GL_AMBIENT, gl_argiak[i].a_ingurunea); 
        glLightfv(GL_LIGHT4, GL_DIFFUSE, gl_argiak[i].a_difusioa); 
        glLightfv(GL_LIGHT4, GL_SPECULAR, gl_argiak[i].a_espekularra);
        glLightfv(GL_LIGHT4, GL_POSITION, gl_argiak[i].a_posizioa); 

        if (gl_argiak[i].type == 3){
             glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, gl_argiak[i].direkzioa);
             glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, gl_argiak[i].cut_off);
        }
        break;

    

    default:
        break;
    }
}

void argia_hasieratu(){
    /*gl_argiak dituen parametroak hasieratu: eguzkia ez bada*/
    gl_argiak[0].a_posizioa[0] = 0.0;
    gl_argiak[0].a_posizioa[1] = 1.0;
    gl_argiak[0].a_posizioa[2] = 0.0;
    gl_argiak[0].a_posizioa[3] = 0.0;
    gl_argiak[0].a_ingurunea[0] = 1.2;
    gl_argiak[0].a_ingurunea[1] = 1.2;
    gl_argiak[0].a_ingurunea[2] = 1.2;
    gl_argiak[0].a_ingurunea[3] = 1.0;
    gl_argiak[0].a_difusioa[0] = 1.0;
    gl_argiak[0].a_difusioa[1] = 1.0;
    gl_argiak[0].a_difusioa[2] = 1.0;
    gl_argiak[0].a_difusioa[3] = 1.0;
    gl_argiak[0].a_espekularra[0] = 1.0;
    gl_argiak[0].a_espekularra[1] = 1.0;
    gl_argiak[0].a_espekularra[2] = 1.0;
    gl_argiak[0].a_espekularra[3] = 1.0;

    /*eragiketak egin*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    argia_ezarri(0);
    glGetFloatv(GL_MODELVIEW_MATRIX, gl_argiak[0].matrize_obj);

    /*gl_argiak dituen parametroak hasieratu: eguzkia bada*/
    gl_argiak[0].type = EGUZKIA;
    gl_argiak[0].is_on = 1;


    gl_argiak[1].a_posizioa[0] = 1.0;
    gl_argiak[1].a_posizioa[1] = 1.0f;
    gl_argiak[1].a_posizioa[2] = 0.0f;
    gl_argiak[1].a_posizioa[3] = 1.0f;
    gl_argiak[1].a_ingurunea[0] = 1.2f;
    gl_argiak[1].a_ingurunea[1] = 1.2f;
    gl_argiak[1].a_ingurunea[2] = 1.2f;
    gl_argiak[1].a_ingurunea[3] = 1.0f;
    gl_argiak[1].a_difusioa[0] = 1.0f;
    gl_argiak[1].a_difusioa[1] = 1.0f;
    gl_argiak[1].a_difusioa[2] = 1.0f;
    gl_argiak[1].a_difusioa[3] = 1.0f;
    gl_argiak[1].a_espekularra[0] = 1.0f;
    gl_argiak[1].a_espekularra[1] = 1.0f;
    gl_argiak[1].a_espekularra[2] = 1.0f;
    gl_argiak[1].a_espekularra[3] = 1.0f;
    

    //eragiketak
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    argia_ezarri(1);
    glGetFloatv(GL_MODELVIEW_MATRIX, gl_argiak[1].matrize_obj);
    gl_argiak[1].type = BONBILLA;
    gl_argiak[1].is_on = 0;
}


void fokuO_matrizea(){
    int i;
    for (i = 0; i < 16; i++){
        gl_argiak[2].matrize_obj[i] = _selected_object->matrizeen_lista->M[i];
        
    }
}
void foku_obj_matrizea(){
    gl_argiak[2].a_posizioa[0] = _selected_object->max.x / 2;
    gl_argiak[2].a_posizioa[1] = _selected_object->max.y / 2;
    gl_argiak[2].a_posizioa[2] = _selected_object->max.z;
    gl_argiak[2].a_posizioa[3] = 1;

    gl_argiak[2].a_ingurunea[0] = 1.5;
    gl_argiak[2].a_ingurunea[1] = 1.5;
    gl_argiak[2].a_ingurunea[2] = 1.5;
    gl_argiak[2].a_ingurunea[3] = 1.0;

    gl_argiak[2].a_difusioa[0] = 1.5;
    gl_argiak[2].a_difusioa[1] = 1.5;
    gl_argiak[2].a_difusioa[2] = 1.5;
    gl_argiak[2].a_difusioa[3] = 1.0;

    gl_argiak[2].a_espekularra[0] = 1.0;
    gl_argiak[2].a_espekularra[1] = 1.0;
    gl_argiak[2].a_espekularra[2] = 1.0;
    gl_argiak[2].a_espekularra[3] = 1.0;

    gl_argiak[2].cut_off = 45.0;

    gl_argiak[2].direkzioa[0] = 0.0;
    gl_argiak[2].direkzioa[1] = 0.0;
    gl_argiak[2].direkzioa[2] = 1.0;

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    argia_ezarri(2);
    _selected_object->matrizeen_lista = (matrizeen_lista*) malloc(sizeof(matrizeen_lista));
    fokuO_matrizea();
    gl_argiak[2].type = 2;
    gl_argiak[2].is_on = 0;
}




void fokuK_matrizea(){
    int i;
    for (i = 0; i < 16; i++){
        gl_argiak[2].matrize_obj[i] = _selected_kamera->matrizeen_lista->M[i];
        
    }
}


void foku_kam_matrizea(){
    gl_argiak[3].a_posizioa[0] = _selected_kamera->max.x / 2;
    gl_argiak[3].a_posizioa[1] = _selected_kamera->max.y / 2;
    gl_argiak[3].a_posizioa[2] = _selected_kamera->max.z;
    gl_argiak[3].a_posizioa[3] = 1;

    gl_argiak[3].a_ingurunea[0] = 1.5;
    gl_argiak[3].a_ingurunea[1] = 1.5;
    gl_argiak[3].a_ingurunea[2] = 1.5;
    gl_argiak[3].a_ingurunea[3] = 1.0;

    gl_argiak[3].a_difusioa[0] = 1.5;
    gl_argiak[3].a_difusioa[1] = 1.5;
    gl_argiak[3].a_difusioa[2] = 1.5;
    gl_argiak[3].a_difusioa[3] = 1.0;

    gl_argiak[3].a_espekularra[0] = 1.0;
    gl_argiak[3].a_espekularra[1] = 1.0;
    gl_argiak[3].a_espekularra[2] = 1.0;
    gl_argiak[3].a_espekularra[3] = 1.0;

    gl_argiak[3].cut_off = 45.0;

    gl_argiak[3].direkzioa[0] = 0.0;
    gl_argiak[3].direkzioa[1] = 0.0;
    gl_argiak[3].direkzioa[2] = 1.0;

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    argia_ezarri(3);
    _selected_kamera->matrizeen_lista = (matrizeen_lista*) malloc(sizeof(matrizeen_lista));
    fokuK_matrizea();
    gl_argiak[3].type = 3;
    gl_argiak[3].is_on = 0;

}
void materiala_hasieratu(){
    Turquoise = (materialak*) malloc(sizeof(materialak));
    Turquoise -> m_ingurunea[0]= 0.1; 
    Turquoise -> m_ingurunea[1]= 0.18725; 
    Turquoise -> m_ingurunea[2]= 0.1745; 
    Turquoise -> m_ingurunea[3]= 0.8; 
    Turquoise -> m_difusioa[0]= 0.396;
    Turquoise -> m_difusioa[1]= 0.74151;
    Turquoise -> m_difusioa[2]=  0.69102;
    Turquoise -> m_difusioa[3]= 0.8;
    Turquoise -> m_espekularra[0]= 0.297254;
    Turquoise -> m_espekularra[1]= 0.30829;
    Turquoise -> m_espekularra[2]= 0.306678;
    Turquoise -> m_espekularra[3]= 0.8;
    Turquoise -> argirik_ez[0]= 12.8;

}

void materiala_gehitu(){
    _selected_object->materialak = Turquoise;
}





void erpinen_b_normal_kalkulatu(){
    vector3 b0= {0,0,0};
    vertex * vertex1;
    for (int i=0; i<_selected_object->num_vertices; i++){
        _selected_object->vertex_table[i].b_normala=b0;
    }
        
    for (int j=0; j<_selected_object->num_faces; j++){
        for (int k=0; k<_selected_object->face_table[j].num_vertices; k++){
            vertex1= &(_selected_object->vertex_table[_selected_object->face_table[j].vertex_table[k]]);
            vertex1->b_normala.x= vertex1->b_normala.x - _selected_object->face_table[j].b_normala.x;
            vertex1->b_normala.y= vertex1->b_normala.y - _selected_object->face_table[j].b_normala.y;
            vertex1->b_normala.z= vertex1->b_normala.z - _selected_object->face_table[j].b_normala.z;
        } 
        
    }

    for (int i=0; i<_selected_object->num_vertices; i++){
        vertex1= &(_selected_object->vertex_table[i]);
    
        vertex1->b_normala.x= vertex1->b_normala.x / vertex1->num_faces;
        vertex1->b_normala.y= vertex1->b_normala.y / vertex1->num_faces;
        vertex1->b_normala.z= vertex1->b_normala.z / vertex1->num_faces;
        }
    }






/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */

void keyboard(unsigned char key, int x, int y) {
    int i;
    char fname[128]; /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *aux_obj = 0;
    GLdouble wd,he,midx,midy;

    switch (key) {
    case 'f':
    case 'F':
        /*Ask for file*/
        printf("%s", KG_MSSG_SELECT_FILE);
        scanf("%s", &(fname[0]));
        /*Allocate memory for the structure and read the file*/
        aux_obj = (object3d *) malloc(sizeof (object3d));
        read = read_wavefront(fname, aux_obj);
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
            aux_obj->mzptr = (mz*)malloc(sizeof(mz));
            aux_obj->mzptr->hptr= 0;
            for (i=1;i<16;i++)aux_obj->mzptr->M[i]=0.0;
            aux_obj->mzptr->M[0]=1.0;
            aux_obj->mzptr->M[5]=1.0;
            aux_obj->mzptr->M[10]=1.0;
            aux_obj->mzptr->M[15]=1.0;
            /*Insert the new object in the list*/
            aux_obj->next = _first_object;
            _first_object = aux_obj;
            _selected_object = _first_object;
            
            printf("%s\n",KG_MSSG_FILEREAD);
            aurpegien_b_normal_kalkulatu();
            erpinen_b_normal_kalkulatu(_selected_object);
            materiala_gehitu();
            _selected_object->fs=FLAT;
            foku_obj_matrizea();
            break;
        }
        break;

    case 9: /* <TAB> */
        if (_selected_object == 0)
        {
            printf("Ez dago objekturik, ezin da hurrengo objektua aukeratu\n");
        }
        else
        {
            _selected_object = _selected_object->next;
            /*The selection is circular, thus if we move out of the list we go back to the first element*/
            if (_selected_object == 0) _selected_object = _first_object;
             printf("Ez daude objektu gehiago\n");
        }
        break;

    case 127: /* <SUPR> */
        // TODO if there is not any object in the object list we should not try to free any memory!!!
        /*Erasing an object depends on whether it is the first one or not*/
        if(_selected_object==0)
        {
            printf("Ez dago objekturik ezabatzeko.\n");
            break;
        }
        if (_selected_object == _first_object)
        {
            /*To remove the first object we just set the first as the current's next*/
            _first_object = _first_object->next;
            /*Once updated the pointer to the first object it is save to free the memory*/
            // TODO free the auxiliar memory used inside the structure
            obj_mem_askatu(_selected_object);
            free(_selected_object);
            /*Finally, set the selected to the new first one*/
            _selected_object = _first_object;
        } else {
            /*In this case we need to get the previous element to the one we want to erase*/
            aux_obj = _first_object;
            while (aux_obj->next != _selected_object)
                aux_obj = aux_obj->next;
                /*Now we bypass the element to erase*/
                aux_obj->next = _selected_object->next;
                /*free the memory*/
                // TODO free the auxiliar memory used inside the structure
                obj_mem_askatu(_selected_object);
                free(_selected_object);
                /*and update the selection. It is the previous to the deleted one. */
                _selected_object = aux_obj;
        }
        break;

    case '-':   /* Decrease the projection plane; compute the new dimensions*/
        /*Objektua aukeratuta badago, txikitu*/
        double M_ald[16];
        if(obj_mota=0){ /*aldaketak objektu baten gainean egiteko.*/
            if (_selected_object){
                lortu_eskalaketa_matrizea(&(M_ald[0]),1.0/eskalaketa,1.0/eskalaketa,1.0/eskalaketa);
            }
            break;
        }
        else{
            if(obj_mota=1){/*aldaketak kamera baten gainean egiteko.*/
                wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            else{  /*argia aukeratuta badago, ez du ezer ez egiten*/           
                break;
            }
        }
        break;
        
    case '+':
        //INPLEMENTA EZAZU + FUNTZIOANLITATEA
        // TODO
        if(obj_mota=0){ /*aldaketak objektu baten gainean egiteko.*/
                    lortu_eskalaketa_matrizea(&(M_ald[0]),1.0*eskalaketa,1.0*eskalaketa,1.0*eskalaketa);
                    break;
        }
        else if(obj_mota=1){/*aldaketak kamera baten gainean egiteko.*/   
            wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        else{ /*aldaketak argiengan egiteko*/
           if(argi_mota==3 || argi_mota==2){
                gl_argiak[argi_mota].cut_off += KG_STEP_CAMERA_ANGLE;
                glutPostRedisplay();
            }
            else{
                 break;
            }        
        
        }
        break;
    

    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        exit(0);
        break;

    case 't': /*traslazioa*/
    case 'T':
        aldaketa_mota='t';
        break;
    case 'r': /*biraketa*/
    case 'R':
        aldaketa_mota='r';
        break;
    case 'e': /*eskalaketa*/
    case 'E':
        aldaketa_mota='e';
        break;

    case 'z':
    case 'Z':
        if(obj_mota==0){
            if (_selected_object != 0){
                mz *maux;
                if (_selected_object -> mzptr -> hptr !=0){
                printf("Aldaketa deseginda.\n");
                maux = _selected_object ->mzptr;
                _selected_object->mzptr = _selected_object ->mzptr->hptr;
                free(maux);
                }
                else{
                printf("Ezin da gehiago desegin. \n");
                }
            }
            else{
            printf("Ez dago objekturik kargatuta, orduan ezin da desegin. \n");
            }
        }
        else if(obj_mota==1){
            if (_selected_kamera != 0){
            mz *maux;
            if (_selected_kamera -> mzptr -> hptr !=0){
            printf("Aldaketa deseginda.\n");
            maux = _selected_kamera ->mzptr;
            _selected_kamera->mzptr = _selected_kamera ->mzptr->hptr;
            free(maux);
            }
            else{
            printf("Ezin da gehiago desegin. \n");
            }
        }
        else{
        printf("Ez dago kamerarik kargatuta, orduan ezin da desegin. \n");
        }
        }
        break;

    case 'g':
    case 'G':
        printf("globala\n");
        LG=1; /*Egoera aldagaia globala*/
        if(obj_mota==1){
            double AUX[16];
            double B[16];
            printf("Kamararen analisi modua\n");
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if(_selected_kamera->mzptr->M==_selected_object->mzptr->M){

            }
            if((_selected_kamera->mzptr->M[12]==_selected_object->mzptr->M[12])
            &&(_selected_kamera->mzptr->M[13]==_selected_object->mzptr->M[13])
            &&(_selected_kamera->mzptr->M[14]==_selected_object->mzptr->M[14])){
            _selected_kamera->mzptr->M[12]= _selected_kamera->mzptr->M[12]+ _selected_kamera->mzptr->M[8]*10;
            _selected_kamera->mzptr->M[13]= _selected_kamera->mzptr->M[13]+ _selected_kamera->mzptr->M[9]*10;
            _selected_kamera->mzptr->M[14]= _selected_kamera->mzptr->M[14]+ _selected_kamera->mzptr->M[10]*10;
            }
            gluLookAt(_selected_kamera->mzptr->M[12],_selected_kamera->mzptr->M[13],_selected_kamera->mzptr->M[14],
            _selected_object->mzptr->M[12], _selected_object->mzptr->M[13], _selected_object->mzptr->M[14],
            _selected_kamera->mzptr->M[4],_selected_kamera->mzptr->M[5],_selected_kamera->mzptr->M[6]);
            glGetDoublev(GL_MODELVIEW_MATRIX, AUX);
            

            B[0]=AUX[0];    B[4]=AUX[1];      B[8]=AUX[2];     B[12]=_selected_kamera->mzptr->M[12];
            B[1]=AUX[4];    B[5]=AUX[5];      B[9]=AUX[6];     B[13]=_selected_kamera->mzptr->M[13];
            B[2]=AUX[8];    B[6]=AUX[9];      B[10]=AUX[10];   B[14]=_selected_kamera->mzptr->M[14];
            B[3]= 0;      B[7]=0;         B[11]=0;       B[15]=1;       //Es el E que es el mismo
            
            glLoadMatrixd(B);
            glGetDoublev(GL_MODELVIEW_MATRIX, _selected_kamera->mzptr->M);
        }
        break;
    case 'l':
    case 'L':
        LG=0; /*Egoera aldagaia lokala*/
        break;

    case 'o':
    case 'O':
        obj_mota=0; /*Objektua*/
        break;
    case 'c':
    case 'C':
        obj_mota=1; /*Kamera*/
        break;
    case 'a':
    case 'A':
        printf("Argiak\n");
        obj_mota=2; /*Argiak*/
        break;
    case 'k':
    case 'K':
            if (nondik_ikusi==1){
                nondik_ikusi=0;//objektutik ikusita
                printf("obj-tik ikusi\n");
            }
            else{
                nondik_ikusi=1;//kanpotik ikusita
                printf("kanpotik ikusi\n");
            }
            break;
     case '1':
        printf("BONBILLA\n");
        argi_mota = 0;
        break;

    case '2':
        printf("EGUZKIA\n");
        argi_mota = 1;
        break;

    case '3':
        printf("OBJ_ARGIA\n");
        argi_mota = 2;
        break;

    case '4':
        printf("KAM_ARGIA\n");
        argi_mota = 3;
        break;

    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}


