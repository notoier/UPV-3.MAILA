#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

extern object3d *_first_object;
extern object3d *_selected_object;

extern kamera *_first_kamera;
extern kamera *_selected_kamera;

extern GLdouble _ortho_x_min, _ortho_x_max;
extern GLdouble _ortho_y_min, _ortho_y_max;
extern GLdouble _ortho_z_min, _ortho_z_max;

extern int LG; // 1 lokala, 2 globala

extern char aldaketa_mota; /*t = translation, r=rotation, e=escale, i=argi intetsitatea*/
extern double biraketa_angelua;
extern double lekuzaldaketa;
extern double eskalaketa;

int objektu_aktiboa = 0; // 0 aukeratutako objektua, 1 kamera, 2 argia
int argi_aktiboa = 0;    // 0 bonbila, 1 eguzkia, 2 kamera fokoa, 3 objektu fokoa
int bonbilla_piztuta = 0;
int eguzkia_piztuta = 0;
int obj_fokoa_piztuta = 0;
int kam_fokoa_piztuta = 0;
int orokorra_piztuta = 1;
int ikuspuntua = 0; // 0 -> objektuaren ikuspuntua, 1 -> kanpoko ikuspuntua
materiala *horia,*zilarra;

argia argi_globalak[4];
materiala materialak[2];

void poligonoen_v_normalak_kal();
void ertzen_vektore_normala_kalk();
void objektu_fokoa_hasieratu();
void argiak_hasieratu();
void materiala_aldatu();
void materiala_jarri();
void intentsitatea_aldatu();
void matrizI();

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help()
{
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
/**
 * * object3d egiturako barne memoria garbitzeko funtzioa
 * */
void egiturako_mem_askatu(object3d *optr)
{
    int i;
    MZ *auxptr;

    for (i = 0; i < optr->num_faces; i++)
    {
        free(optr->face_table[i].vertex_table);
    }
    free(optr->vertex_table);
    free(optr->face_table);
    for (auxptr = optr->MZptr; auxptr != 0; auxptr = optr->MZptr)
    {
        optr->MZptr = optr->MZptr->hptr;
        free(auxptr);
    }
    /*TODO matrizeekin zer pasatzen da? */
}

void lortu_traslazio_matrizea(double *MZptr, double x, double y, double z)
{
    MZptr[0] = 1.0;
    MZptr[1] = 0;
    MZptr[2] = 0;
    MZptr[3] = 0;
    MZptr[4] = 0;
    MZptr[5] = 1.0;
    MZptr[6] = 0;
    MZptr[7] = 0;
    MZptr[8] = 0;
    MZptr[9] = 0;
    MZptr[10] = 1.0;
    MZptr[11] = 0;
    MZptr[12] = x * lekuzaldaketa;
    MZptr[13] = y * lekuzaldaketa;
    MZptr[14] = z * lekuzaldaketa;
    MZptr[15] = 1.0;
}

void lortu_eskala_matrizea(double *MZptr, double p, double q, double r)
{
    MZptr[0] = p;
    MZptr[1] = 0;
    MZptr[2] = 0;
    MZptr[3] = 0;
    MZptr[4] = 0;
    MZptr[5] = q;
    MZptr[6] = 0;
    MZptr[7] = 0;
    MZptr[8] = 0;
    MZptr[9] = 0;
    MZptr[10] = r;
    MZptr[11] = 0;
    MZptr[12] = 0;
    MZptr[13] = 0;
    MZptr[14] = 0;
    MZptr[15] = 1.0;
}

void lortu_biraketa_matrizea(double *MZptr, double x, double y, double z)
{
    MZptr[0] = cos(biraketa_angelua * x) * cos(biraketa_angelua * y);
    MZptr[1] = sin(biraketa_angelua * x) * cos(biraketa_angelua * y);
    MZptr[2] = -sin(biraketa_angelua * y);
    MZptr[3] = 0;
    MZptr[4] = cos(biraketa_angelua * x) * sin(biraketa_angelua * y) * sin(biraketa_angelua * z) - sin(biraketa_angelua * x) * cos(biraketa_angelua * z);
    MZptr[5] = sin(biraketa_angelua * x) * sin(biraketa_angelua * y) * sin(biraketa_angelua * z) + cos(biraketa_angelua * x) * cos(biraketa_angelua * z);
    MZptr[6] = cos(biraketa_angelua * y) * sin(biraketa_angelua * z);
    MZptr[7] = 0;
    MZptr[8] = cos(biraketa_angelua * x) * sin(biraketa_angelua * y) * cos(biraketa_angelua * z) + sin(biraketa_angelua * x) * sin(biraketa_angelua * z);
    MZptr[9] = sin(biraketa_angelua * x) * sin(biraketa_angelua * y) * cos(biraketa_angelua * z) - cos(biraketa_angelua * x) * sin(biraketa_angelua * z);
    MZptr[10] = cos(biraketa_angelua * y) * cos(biraketa_angelua * z);
    MZptr[11] = 0;
    MZptr[12] = 0;
    MZptr[13] = 0;
    MZptr[14] = 0;
    MZptr[15] = 1.0;
}

void biderkatu_matrizeak(double *MZptr)
{
    MZ *mlagptr;

    glMatrixMode(GL_MODELVIEW);

    if (objektu_aktiboa == 0)
    {
        if (LG == 1)
        {
            glLoadMatrixd(_selected_object->MZptr->M);
            glMultMatrixd(&(MZptr[0]));
        }
        else
        {
            glLoadMatrixd(&(MZptr[0]));
            glMultMatrixd(_selected_object->MZptr->M);
        }
        mlagptr = (MZ *)(malloc(sizeof(MZ)));
        glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
        mlagptr->hptr = _selected_object->MZptr;
        _selected_object->MZptr = mlagptr;
    }
    else if (objektu_aktiboa == 1)
    {
        if (LG == 1)
        {
            glLoadMatrixd(_selected_kamera->MZptr->M);
            glMultMatrixd(&(MZptr[0]));
        }
        else
        {
            glLoadMatrixd(&(MZptr[0]));
            glMultMatrixd(_selected_kamera->MZptr->M);
        }
        mlagptr = (MZ *)(malloc(sizeof(MZ)));
        glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
        mlagptr->hptr = _selected_kamera->MZptr;
        _selected_kamera->MZptr = mlagptr;
    }
}

void esa_matrizea_lortu(double *Mobj, double *Mesa)
{
    Mesa[0] = Mobj[0];
    Mesa[4] = Mobj[1];
    Mesa[8] = Mobj[2];
    Mesa[1] = Mobj[4];
    Mesa[5] = Mobj[5];
    Mesa[9] = Mobj[6];
    Mesa[2] = Mobj[8];
    Mesa[6] = Mobj[9];
    Mesa[10] = Mobj[10];
    Mesa[3] = 0.0;
    Mesa[7] = 0.0;
    Mesa[11] = 0.0;
    Mesa[12] = (-1) * (Mobj[0] * Mobj[12] + Mobj[1] * Mobj[13] + Mobj[2] * Mobj[14]);
    Mesa[13] = (-1) * (Mobj[4] * Mobj[12] + Mobj[5] * Mobj[13] + Mobj[6] * Mobj[14]);
    Mesa[14] = (-1) * (Mobj[8] * Mobj[12] + Mobj[9] * Mobj[13] + Mobj[10] * Mobj[14]);
    Mesa[15] = 1.0;
}

void eraldatu_matrizea_objektu(int key)
{
    double M_ald[16];
    switch (key)
    {
    case GLUT_KEY_LEFT:
        switch (aldaketa_mota)
        {
        case 't':
            lortu_traslazio_matrizea(&(M_ald[0]), -1.0, 0.0, 0.0);
            break;
        case 'r':
            lortu_biraketa_matrizea(&(M_ald[0]), 0.0, -1.0, 0.0);
            break;

        case 'e':
            lortu_eskala_matrizea(&(M_ald[0]), 1.0 / eskalaketa, 1.0, 1.0);
            break;
        case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
        }
        biderkatu_matrizeak(M_ald);
        break;

    case GLUT_KEY_RIGHT:
        switch (aldaketa_mota)
        {
        case 't':
            lortu_traslazio_matrizea(&(M_ald[0]), 1.0, 0.0, 0.0);
            break;
        case 'r':
            lortu_biraketa_matrizea(&(M_ald[0]), 0.0, 1.0, 0.0);
            break;

        case 'e':
            lortu_eskala_matrizea(&(M_ald[0]), 1.0 * eskalaketa, 1.0, 1.0);
            break;
        case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
        }
        biderkatu_matrizeak(M_ald);
        break;

    case GLUT_KEY_UP:
        switch (aldaketa_mota)
        {
        case 't':
            lortu_traslazio_matrizea(&(M_ald[0]), 0.0, 1.0, 0.0);
            break;
        case 'r':
            lortu_biraketa_matrizea(&(M_ald[0]), -1.0, 0.0, 0.0);
            break;

        case 'e':
            lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0 * eskalaketa, 1.0);
            break;
        case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
        }
        biderkatu_matrizeak(M_ald);
        break;

    case GLUT_KEY_DOWN:
        switch (aldaketa_mota)
        {
        case 't':
            lortu_traslazio_matrizea(&(M_ald[0]), 0.0, -1.0, 0.0);
            break;
        case 'r':
            lortu_biraketa_matrizea(&(M_ald[0]), 1.0, 0.0, 0.0);
            break;

        case 'e':
            lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0 / eskalaketa, 1.0);
            break;
        case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
        }
        biderkatu_matrizeak(M_ald);
        break;

    case GLUT_KEY_PAGE_UP:
        switch (aldaketa_mota)
        {
        case 't':
            lortu_traslazio_matrizea(&(M_ald[0]), 0.0, 0.0, -1.0);
            break;
        case 'r':
            lortu_biraketa_matrizea(&(M_ald[0]), 0.0, 0.0, 1.0);
            break;

        case 'e':
            lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0, 1.0 * eskalaketa);
            break;
        case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
        }
        biderkatu_matrizeak(M_ald);
        break;

    case GLUT_KEY_PAGE_DOWN:
        switch (aldaketa_mota)
        {
        case 't':
            lortu_traslazio_matrizea(&(M_ald[0]), 0.0, 0.0, 1.0);
            break;
        case 'r':
            lortu_biraketa_matrizea(&(M_ald[0]), 0.0, 0.0, -1.0);
            break;

        case 'e':
            lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0, 1.0 / eskalaketa);
            break;
        case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
        }
        biderkatu_matrizeak(M_ald);
        break;
    }
}

void matrixAT(double *mat)
{
    mat[0] = 1;
    mat[4] = 0;
    mat[8] = 0;
    mat[12] = _selected_object->MZptr->M[12];
    mat[1] = 0;
    mat[5] = 1;
    mat[9] = 0;
    mat[13] = _selected_object->MZptr->M[13];
    mat[2] = 0;
    mat[6] = 0;
    mat[10] = 1;
    mat[14] = _selected_object->MZptr->M[14];
    mat[3] = 0;
    mat[7] = 0;
    mat[11] = 0;
    mat[15] = 1;
}

void matrixATberria(double *bmat)
{
    bmat[0] = 1;
    bmat[4] = 0;
    bmat[8] = 0;
    bmat[12] = -_selected_object->MZptr->M[12];
    bmat[1] = 0;
    bmat[5] = 1;
    bmat[9] = 0;
    bmat[13] = -_selected_object->MZptr->M[13];
    bmat[2] = 0;
    bmat[6] = 0;
    bmat[10] = 1;
    bmat[14] = -_selected_object->MZptr->M[14];
    bmat[3] = 0;
    bmat[7] = 0;
    bmat[11] = 0;
    bmat[15] = 1;
}

void matrizI(double *bmat)
{
    bmat[0] = 1;
    bmat[4] = 0;
    bmat[8] = 0;
    bmat[12] = 0;
    bmat[1] = 0;
    bmat[5] = 1;
    bmat[9] = 0;
    bmat[13] = 0;
    bmat[2] = 0;
    bmat[6] = 0;
    bmat[10] = 1;
    bmat[14] = 0;
    bmat[3] = 0;
    bmat[7] = 0;
    bmat[11] = 0;
    bmat[15] = 1;
}

void eraldatu_matrizea_kamera(int key)
{
    double M_ald[16];
    if (LG == 1)
    {
        switch (key)
        {
        case GLUT_KEY_LEFT:
            switch (aldaketa_mota)
            {
            case 't':
                lortu_traslazio_matrizea(&(M_ald[0]), -1.0, 0.0, 0.0);
                break;
            case 'r':
                lortu_biraketa_matrizea(&(M_ald[0]), 0.0, -1.0, 0.0);
                break;

            case 'e':
                lortu_eskala_matrizea(&(M_ald[0]), 1.0 / eskalaketa, 1.0, 1.0);
                break;
            case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
            }
            break;

        case GLUT_KEY_RIGHT:
            switch (aldaketa_mota)
            {
            case 't':
                lortu_traslazio_matrizea(&(M_ald[0]), 1.0, 0.0, 0.0);
                break;
            case 'r':
                lortu_biraketa_matrizea(&(M_ald[0]), 0.0, 1.0, 0.0);
                break;

            case 'e':
                lortu_eskala_matrizea(&(M_ald[0]), 1.0 * eskalaketa, 1.0, 1.0);
                break;
            case 'i':
            printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
            break;
            }
            break;

        case GLUT_KEY_UP:
            switch (aldaketa_mota)
            {
            case 't':
                lortu_traslazio_matrizea(&(M_ald[0]), 0.0, 1.0, 0.0);
                break;
            case 'r':
                lortu_biraketa_matrizea(&(M_ald[0]), -1.0, 0.0, 0.0);
                break;

            case 'e':
                lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0 * eskalaketa, 1.0);
                break;
            case 'i':
                printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
                break;
            }
            break;

        case GLUT_KEY_DOWN:
            switch (aldaketa_mota)
            {
            case 't':
                lortu_traslazio_matrizea(&(M_ald[0]), 0.0, -1.0, 0.0);
                break;
            case 'r':
                lortu_biraketa_matrizea(&(M_ald[0]), 1.0, 0.0, 0.0);
                break;

            case 'e':
                lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0 / eskalaketa, 1.0);
                break;
            case 'i':
                printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
                break;
            }
            break;

        case GLUT_KEY_PAGE_UP:
            switch (aldaketa_mota)
            {
            case 't':
                lortu_traslazio_matrizea(&(M_ald[0]), 0.0, 0.0, -1.0);
                break;
            case 'r':
                lortu_biraketa_matrizea(&(M_ald[0]), 0.0, 0.0, 1.0);
                break;

            case 'e':
                lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0, 1.0 * eskalaketa);
                break;
            case 'i':
                printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
                break;
            }
            break;

        case GLUT_KEY_PAGE_DOWN:
            switch (aldaketa_mota)
            {
            case 't':
                lortu_traslazio_matrizea(&(M_ald[0]), 0.0, 0.0, 1.0);
                break;
            case 'r':
                lortu_biraketa_matrizea(&(M_ald[0]), 0.0, 0.0, -1.0);
                break;

            case 'e':
                lortu_eskala_matrizea(&(M_ald[0]), 1.0, 1.0, 1.0 / eskalaketa);
                break;
            case 'i':
                printf("Modu hau bakarrik argiekin lan egiterakoan erabili ahal da.\n");
                matrizI(&(M_ald[0]));
                break;
            }
            break;
        }
        biderkatu_matrizeak(M_ald);
    }
    else
    {
        if (key >= 100 && key <= 103)
        {
            double Mtat[16];
            double MtNat[16];
            matrixAT(Mtat);
            matrixATberria(MtNat);

            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixd(Mtat);

            switch (key)
            {
            case 100:
                glRotated(-KG_STEP_ROTATE, _selected_kamera->MZptr->M[4], _selected_kamera->MZptr->M[5], _selected_kamera->MZptr->M[6]);
                break;

            case 101:
                glRotated(KG_STEP_ROTATE, _selected_kamera->MZptr->M[0], _selected_kamera->MZptr->M[1], _selected_kamera->MZptr->M[2]);
                break;

            case 102:
                glRotated(KG_STEP_ROTATE, _selected_kamera->MZptr->M[4], _selected_kamera->MZptr->M[5], _selected_kamera->MZptr->M[6]);
                break;

            case 103:
                glRotated(-KG_STEP_ROTATE, _selected_kamera->MZptr->M[0], _selected_kamera->MZptr->M[1], _selected_kamera->MZptr->M[2]);
                break;
            }
            glMultMatrixd(MtNat);
            glMultMatrixd(_selected_kamera->MZptr
                              ->M);
            MZ *mlagptr = (MZ *)(malloc(sizeof(MZ)));
            glGetDoublev(GL_MODELVIEW_MATRIX, mlagptr->M);
            mlagptr->hptr = _selected_kamera->MZptr;
            _selected_kamera->MZptr = mlagptr;
            glutPostRedisplay();
        }
    }
}

/**
 * @brief Callback function to control the special keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void tekla_berezien_arretarako_funtzioa(int key, int x, int y)
{
    if (objektu_aktiboa == 0)
    {
        if (_selected_object != 0)
        {
            eraldatu_matrizea_objektu(key);
            glutPostRedisplay();
        }
        else
        {
            printf("Ez dago objekturik kargatuta.\n");
        }
    }
    else if (objektu_aktiboa == 1)
    {
        if (_selected_kamera != 0)
        {
            eraldatu_matrizea_kamera(key);
            glutPostRedisplay();
        }
        else
        {
            printf("Ez dago kamararik aukeratuta.\n");
        }
    }
    else if (objektu_aktiboa == 2)
    {
        if (key == GLUT_KEY_F1)
        {
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
        }
        else if (key == GLUT_KEY_F2)
        {
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
        }
        else if (key == GLUT_KEY_F3)
        {
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
        }
        else if (key == GLUT_KEY_F4)
        {
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
        }
        else if (key == GLUT_KEY_F9)
        {
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
        }
        else if (key == GLUT_KEY_F12)
        {
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
        }

        else
        {
            double aux_mat[16];

            aux_mat[0] = 1;
            aux_mat[4] = 0;
            aux_mat[8] = argi_globalak[argi_aktiboa].spot_direction[0];
            aux_mat[12] = argi_globalak[argi_aktiboa].position[0];
            aux_mat[1] = 0;
            aux_mat[5] = 1;
            aux_mat[9] = argi_globalak[argi_aktiboa].spot_direction[1];
            aux_mat[13] = argi_globalak[argi_aktiboa].position[1];
            aux_mat[2] = 0;
            aux_mat[6] = 0;
            aux_mat[10] = argi_globalak[argi_aktiboa].spot_direction[2];
            aux_mat[14] = argi_globalak[argi_aktiboa].position[2];
            aux_mat[3] = 0;
            aux_mat[7] = 0;
            aux_mat[11] = 0;
            aux_mat[15] = 1;

            glLoadIdentity();
        
            switch (argi_aktiboa)
            {
                case 0:
                    if (aldaketa_mota == 't')
                    {
                        switch (key)
                        {
                            case GLUT_KEY_LEFT:
                                printf("entro\n");
                                glTranslated(-KG_STEP_MOVE, 0, 0);
                                break;
                            case GLUT_KEY_RIGHT:
                                glTranslated(KG_STEP_MOVE, 0, 0);
                                break;
                            case GLUT_KEY_UP:
                                glTranslated(0, KG_STEP_MOVE, 0);
                                break;
                            case GLUT_KEY_DOWN:
                                glTranslated(0, -KG_STEP_MOVE, 0);
                                break;
                            case GLUT_KEY_PAGE_DOWN:
                                glTranslated(0, 0, -KG_STEP_MOVE);
                                break;
                            case GLUT_KEY_PAGE_UP:
                                glTranslated(0, 0, KG_STEP_MOVE);
                                break;
                        }
                    }
                    else if(aldaketa_mota == 'i'){
                        switch (key){
                            case GLUT_KEY_UP:
                                intentsitatea_aldatu(1,0);
                                glLightfv(GL_LIGHT0, GL_AMBIENT, argi_globalak[0].ambient);
                                glLightfv(GL_LIGHT0, GL_DIFFUSE, argi_globalak[0].diffuse);
                                glLightfv(GL_LIGHT0, GL_SPECULAR, argi_globalak[0].specular);
                                break;
                            case GLUT_KEY_DOWN:
                                intentsitatea_aldatu(-1,0);
                                glLightfv(GL_LIGHT0, GL_AMBIENT, argi_globalak[0].ambient);
                                glLightfv(GL_LIGHT0, GL_DIFFUSE, argi_globalak[0].diffuse);
                                glLightfv(GL_LIGHT0, GL_SPECULAR, argi_globalak[0].specular);
                                break;
                        }
                    }
                    else
                    {
                        printf("Ezin da eraldaketa hori egin bonbillan.\n");
                    }
                    break;
                case 1:
                    if (aldaketa_mota == 'r')
                    {
                        switch (key)
                        {
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
                    }
                    else if(aldaketa_mota == 'i'){
                        switch (key){
                            case GLUT_KEY_UP:
                                intentsitatea_aldatu(1,1);
                                glLightfv(GL_LIGHT1, GL_AMBIENT, argi_globalak[1].ambient);
                                glLightfv(GL_LIGHT1, GL_DIFFUSE, argi_globalak[1].diffuse);
                                glLightfv(GL_LIGHT1, GL_SPECULAR, argi_globalak[1].specular);
                                break;
                            case GLUT_KEY_DOWN:
                                intentsitatea_aldatu(-1,1);
                                glLightfv(GL_LIGHT1, GL_AMBIENT, argi_globalak[1].ambient);
                                glLightfv(GL_LIGHT1, GL_DIFFUSE, argi_globalak[1].diffuse);
                                glLightfv(GL_LIGHT1, GL_SPECULAR, argi_globalak[1].specular);
                                break;
                        }
                    }
                    else
                    {
                        printf("Ezin da eraldaketa hori egin eguzkian.\n");
                    }
                    break;
                case 2:
                    if(aldaketa_mota == 'i'){
                        switch (key){
                            case GLUT_KEY_UP:
                                intentsitatea_aldatu(1,2);
                                glLightfv(GL_LIGHT2, GL_AMBIENT, argi_globalak[2].ambient);
                                glLightfv(GL_LIGHT2, GL_DIFFUSE, argi_globalak[2].diffuse);
                                glLightfv(GL_LIGHT2, GL_SPECULAR, argi_globalak[2].specular);
                                break;
                            case GLUT_KEY_DOWN:
                                intentsitatea_aldatu(-1,2);
                                glLightfv(GL_LIGHT2, GL_AMBIENT, argi_globalak[2].ambient);
                                glLightfv(GL_LIGHT2, GL_DIFFUSE, argi_globalak[2].diffuse);
                                glLightfv(GL_LIGHT2, GL_SPECULAR, argi_globalak[2].specular);
                                break;
                        }
                    }
                    else{
                    printf("Ezin da eraldaketa hori egin objektuaren fokoan.\n");
                    }
                    break;
                case 3:
                    if(aldaketa_mota == 'i'){
                        switch (key){
                            case GLUT_KEY_UP:
                                intentsitatea_aldatu(1,3);
                                glLightfv(GL_LIGHT3, GL_AMBIENT, argi_globalak[3].ambient);
                                glLightfv(GL_LIGHT3, GL_DIFFUSE, argi_globalak[3].diffuse);
                                glLightfv(GL_LIGHT3, GL_SPECULAR, argi_globalak[3].specular);
                                break;
                            case GLUT_KEY_DOWN:
                                intentsitatea_aldatu(-1,3);
                                glLightfv(GL_LIGHT3, GL_AMBIENT, argi_globalak[3].ambient);
                                glLightfv(GL_LIGHT3, GL_DIFFUSE, argi_globalak[3].diffuse);
                                glLightfv(GL_LIGHT3, GL_SPECULAR, argi_globalak[3].specular);
                                break;
                        }
                    }
                    else{
                    printf("Ezin da eraldaketa hori egin kamararen fokoan.\n");
                    }
                    break;
            }

            glMultMatrixd(aux_mat);
            glGetDoublev(GL_MODELVIEW_MATRIX, aux_mat);

            argi_globalak[argi_aktiboa].spot_direction[0] = aux_mat[8];
            argi_globalak[argi_aktiboa].spot_direction[1] = aux_mat[9];
            argi_globalak[argi_aktiboa].spot_direction[2] = aux_mat[10];

            argi_globalak[argi_aktiboa].position[0] = aux_mat[12];
            argi_globalak[argi_aktiboa].position[1] = aux_mat[13];
            argi_globalak[argi_aktiboa].position[2] = aux_mat[14];
            argi_globalak[argi_aktiboa].position[3] = aux_mat[15];
            glutPostRedisplay();
        }
    }
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y)
{
    int i;
    char fname[128]; /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd, he, midx, midy;
    double M_ald[16];

    switch (key)
    {
    case '1':
        argi_aktiboa = 0;
        break;
    case '2':
        argi_aktiboa = 1;
        break;
    case '3':
        argi_aktiboa = 2;
        break;
    case '4':
        argi_aktiboa = 3;
        break;
    case 'o':
    case 'O':
        objektu_aktiboa = 0;
        printf("Objektuekin lan egiten.\n");
        break;

    case 'k':
    case 'K':
        objektu_aktiboa = 1;
        printf("Kamerekin lan egiten.\n");
        break;

    case 'a':
    case 'A':
        objektu_aktiboa = 2;
        printf("Argiekin lan egiten.\n");
        break;

    case 'm':
    case 'M':
        materiala_aldatu();
        glutPostRedisplay();
        break;

    case 'f':
    case 'F':
        /*Ask for file*/
        printf("%s", KG_MSSG_SELECT_FILE);
        scanf("%s", &(fname[0]));
        /*Allocate memory for the structure and read the file*/
        auxiliar_object = (object3d *)malloc(sizeof(object3d));
        read = read_wavefront(fname, auxiliar_object);
        switch (read)
        {
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
            auxiliar_object->MZptr = (MZ *)malloc(sizeof(MZ));
            auxiliar_object->MZptr->hptr = 0;
            for (i = 1; i < 16; i++)
                auxiliar_object->MZptr->M[i] = 0, 0;
            auxiliar_object->MZptr->M[0] = 1.0;
            auxiliar_object->MZptr->M[5] = 1.0;
            auxiliar_object->MZptr->M[10] = 1.0;
            auxiliar_object->MZptr->M[15] = 1.0;
            /*Insert the new object in the list*/
            auxiliar_object->next = _first_object;
            _first_object = auxiliar_object;
            _selected_object = _first_object;

            poligonoen_v_normalak_kal();
            ertzen_vektore_normala_kalk();
            materiala_jarri();
            _selected_object->flat_smooth = 0;
            objektu_fokoa_hasieratu();
            printf("%s\n", KG_MSSG_FILEREAD);
            break;
        }
        break;

    case 9: /* <TAB> */
        if (_selected_object == 0)
        {
            printf("Ez dago bezte objekturik.\n");
        }
        else
        {
            _selected_object = _selected_object->next;
            /*The selection is circular, thus if we move out of the list we go back to the first element*/
            if (_selected_object == 0)
                _selected_object = _first_object;
        }
        break;

    case 'q':
    case 'Q':
        if (ikuspuntua == 0)
        {
            ikuspuntua = 1;
            printf("Objektu ikuspuntua\n");
        }
        else
        {
            ikuspuntua = 0;
            printf("Kanpoko ikuspuntua\n");
        }
        break;

    case 127: /* <SUPR> */
        // TODO if there is not any object in the object list we should not try to free any memory!!!
        if (_selected_object == 0)
        {
            printf("Ez dago objekturik ezabatzeko.\n");
        }
        else
        {
            /*Erasing an object depends on whether it is the first one or not*/
            if (_selected_object == _first_object)
            {
                /*To remove the first object we just set the first as the current's next*/
                _first_object = _first_object->next;
                /*Once updated the pointer to the first object it is save to free the memory*/
                // TODO free the auxiliar memory used inside the structure
                egiturako_mem_askatu(_selected_object);
                free(_selected_object);
                /*Finally, set the selected to the new first one*/
                _selected_object = _first_object;
            }
            else
            {
                /*In this case we need to get the previous element to the one we want to erase*/
                auxiliar_object = _first_object;
                while (auxiliar_object->next != _selected_object)
                    auxiliar_object = auxiliar_object->next;
                /*Now we bypass the element to erase*/
                auxiliar_object->next = _selected_object->next;
                /*free the memory*/
                // TODO free the auxiliar memory used inside the structure
                egiturako_mem_askatu(_selected_object);
                free(_selected_object);
                /*and update the selection. It is the previous to the deleted one. */
                _selected_object = auxiliar_object;
            }
        }
        break;

    case '-': /* Decrease the projection plane; compute the new dimensions*/
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
        {
            // with or without pressing CTRL key
        }

        wd = (_ortho_x_max - _ortho_x_min) * KG_STEP_ZOOM;
        he = (_ortho_y_max - _ortho_y_min) * KG_STEP_ZOOM;
        /*In order to avoid moving the center of the plane, we get its coordinates*/
        midx = (_ortho_x_max + _ortho_x_min) / 2;
        midy = (_ortho_y_max + _ortho_y_min) / 2;
        /*The the new limits are set, keeping the center of the plane*/
        _ortho_x_max = midx + wd / 2;
        _ortho_x_min = midx - wd / 2;
        _ortho_y_max = midy + he / 2;
        _ortho_y_min = midy - he / 2;

        if (_selected_object != 0)
        {
            lortu_eskala_matrizea(&(M_ald[0]), 1.0 / eskalaketa, 1.0 / eskalaketa, 1.0 / eskalaketa);
            biderkatu_matrizeak(M_ald);
        }

        break;

    case '+': /* Increase the projection plane; compute the new dimensions*/
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
        {
            // with or without pressing CTRL key
        }

        wd = (_ortho_x_max - _ortho_x_min) / KG_STEP_ZOOM;
        he = (_ortho_y_max - _ortho_y_min) / KG_STEP_ZOOM;
        /*In order to avoid moving the center of the plane, we get its coordinates*/
        midx = (_ortho_x_max + _ortho_x_min) / 2;
        midy = (_ortho_y_max + _ortho_y_min) / 2;
        /*The the new limits are set, keeping the center of the plane*/
        _ortho_x_max = midx + wd / 2;
        _ortho_x_min = midx - wd / 2;
        _ortho_y_max = midy + he / 2;
        _ortho_y_min = midy - he / 2;

        if (_selected_object != 0)
        {
            lortu_eskala_matrizea(&(M_ald[0]), 1.0 * eskalaketa, 1.0 * eskalaketa, 1.0 * eskalaketa);
            biderkatu_matrizeak(M_ald);
        }
        break;

    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        exit(0);
        break;

    case 't':
    case 'T':
        printf("Aldaketa mota: translazioa \n");
        aldaketa_mota = 't';
        break;

    case 'e':
    case 'E':
        printf("Aldaketa mota: eskalatu \n");
        aldaketa_mota = 'e';
        break;

    case 'r':
    case 'R':
        printf("Aldaketa mota: rotazioa \n");
        aldaketa_mota = 'r';
        break;
    
    case 'i':
    case 'I':
        printf("Aldaketa mota: argiaren intentsitatea \n");
        aldaketa_mota = 'i';
        break;

    case 'l':
    case 'L':
        printf("Aldaketa lokala \n");
        LG = 1;
        break;

    case 'g':
    case 'G':
        if (objektu_aktiboa == 1)
        { // camara
            double A[16];
            double B[16];
            printf("Kamararen analisi modua\n");
            LG = 2;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if ((_selected_kamera->MZptr->M[12] == _selected_object->MZptr->M[12]) && (_selected_kamera->MZptr->M[13] == _selected_object->MZptr->M[13]) && (_selected_kamera->MZptr->M[14] == _selected_object->MZptr->M[14]))
            {
                _selected_kamera->MZptr->M[12] = _selected_kamera->MZptr->M[12] + _selected_kamera->MZptr->M[8] * 10;
                _selected_kamera->MZptr->M[13] = _selected_kamera->MZptr->M[13] + _selected_kamera->MZptr->M[9] * 10;
                _selected_kamera->MZptr->M[14] = _selected_kamera->MZptr->M[14] + _selected_kamera->MZptr->M[10] * 10;
            }
            gluLookAt(_selected_kamera->MZptr->M[12], _selected_kamera->MZptr->M[13], _selected_kamera->MZptr->M[14],
                      _selected_object->MZptr->M[12], _selected_object->MZptr->M[13], _selected_object->MZptr->M[14],
                      _selected_kamera->MZptr->M[4], _selected_kamera->MZptr->M[5], _selected_kamera->MZptr->M[6]);
            glGetDoublev(GL_MODELVIEW_MATRIX, A);

            B[0] = A[0];
            B[4] = A[1];
            B[8] = A[2];
            B[12] = _selected_kamera->MZptr->M[12];
            B[1] = A[4];
            B[5] = A[5];
            B[9] = A[6];
            B[13] = _selected_kamera->MZptr->M[13];
            B[2] = A[8];
            B[6] = A[9];
            B[10] = A[10];
            B[14] = _selected_kamera->MZptr->M[14];
            B[3] = 0;
            B[7] = 0;
            B[11] = 0;
            B[15] = 1; // Es el E que es el mismo

            glLoadMatrixd(B);
            glGetDoublev(GL_MODELVIEW_MATRIX, _selected_kamera->MZptr->M);
        }
        else if (objektu_aktiboa == 0)
        { // obj
            LG = 2;
            printf("Munduko erreferentzia sistema\n");
        }

        break;

    case 'z':
        if (objektu_aktiboa == 0)
        {
            if (_selected_object != 0)
            {
                MZ *maux;
                if (_selected_object->MZptr->hptr != 0)
                {
                    printf("Desegin \n");
                    maux = _selected_object->MZptr;
                    _selected_object->MZptr = _selected_object->MZptr->hptr;
                    free(maux);
                }
                else
                {
                    printf("Ezin da gehiago desegin. \n");
                }
            }
            else
            {
                printf("Ez dago objekturik kargatuta, orduan ezin da desegin. \n");
            }
        }
        else if (objektu_aktiboa == 1)
        {
            if (_selected_kamera != 0)
            {
                MZ *maux;
                if (_selected_kamera->MZptr->hptr != 0)
                {
                    printf("Desegin \n");
                    maux = _selected_kamera->MZptr;
                    _selected_kamera->MZptr = _selected_kamera->MZptr->hptr;
                    free(maux);
                }
                else
                {
                    printf("Ezin da gehiago desegin. \n");
                }
            }
            else
            {
                printf("Ez dago kamerarik kargatuta, orduan ezin da desegin. \n");
            }
        }
        break;
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}

vector3 puntuen_kenketa(point3 p1, point3 p2)
{
    vector3 v;

    v.x = p1.x - p2.x;
    v.y = p1.y - p2.y;
    v.z = p1.z - p2.z;

    return v;
}

void poligonoen_v_normalak_kal()
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

        _selected_object->face_table[i].v_normala.x = vN.x;
        _selected_object->face_table[i].v_normala.y = vN.y;
        _selected_object->face_table[i].v_normala.z = vN.z;
    }
}

void fokoaren_matrizea()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        argi_globalak[2].m_obj[i] = _selected_object->MB->M[i];
    }
}

void kameraren_matrizea()
{
    int i;
    for (i = 0; i < 16; i++)
    {
        argi_globalak[2].m_obj[i] = _selected_kamera->MB->M[i];
    }
}

void put_light(GLint i)
{
    switch (i)
    {
    case 0:

        glLightfv(GL_LIGHT0, GL_POSITION, argi_globalak[i].position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, argi_globalak[i].ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, argi_globalak[i].diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, argi_globalak[i].specular);
        break;

    case 1:
        glLightfv(GL_LIGHT1, GL_AMBIENT, argi_globalak[i].ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, argi_globalak[i].diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, argi_globalak[i].specular);
        glLightfv(GL_LIGHT1, GL_POSITION, argi_globalak[i].position);
        break;

    case 2:
        glLightfv(GL_LIGHT2, GL_AMBIENT, argi_globalak[i].ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, argi_globalak[i].diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, argi_globalak[i].specular);
        glLightfv(GL_LIGHT2, GL_POSITION, argi_globalak[i].position);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, argi_globalak[i].spot_direction);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, argi_globalak[i].cut_off);
        break;

    case 3:
        glLightfv(GL_LIGHT3, GL_AMBIENT, argi_globalak[i].ambient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, argi_globalak[i].diffuse);
        glLightfv(GL_LIGHT3, GL_SPECULAR, argi_globalak[i].specular);
        glLightfv(GL_LIGHT3, GL_POSITION, argi_globalak[i].position);
        if (argi_globalak[i].type == 3)
        {
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, argi_globalak[i].spot_direction);
            glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, argi_globalak[i].cut_off);
        }
        break;

    case 4:
        glLightfv(GL_LIGHT4, GL_AMBIENT, argi_globalak[i].ambient);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, argi_globalak[i].diffuse);
        glLightfv(GL_LIGHT4, GL_SPECULAR, argi_globalak[i].specular);
        glLightfv(GL_LIGHT4, GL_POSITION, argi_globalak[i].position);

        if (argi_globalak[i].type == 4)
        {
            glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, argi_globalak[i].spot_direction);
            glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, argi_globalak[i].cut_off);
        }
        break;

    default:
        break;
    }
}

void argiak_hasieratu()
{

    argi_globalak[0].position[0] = 0.0f;
    argi_globalak[0].position[1] = 1.0f;
    argi_globalak[0].position[2] = 0.0f;
    argi_globalak[0].position[3] = 0.0f;
    argi_globalak[0].ambient[0] = 1.2f;
    argi_globalak[0].ambient[1] = 1.2f;
    argi_globalak[0].ambient[2] = 1.2f;
    argi_globalak[0].ambient[3] = 1.0f;
    argi_globalak[0].diffuse[0] = 1.0f;
    argi_globalak[0].diffuse[1] = 1.0f;
    argi_globalak[0].diffuse[2] = 1.0f;
    argi_globalak[0].diffuse[3] = 1.0f;
    argi_globalak[0].specular[0] = 1.0f;
    argi_globalak[0].specular[1] = 1.0f;
    argi_globalak[0].specular[2] = 1.0f;
    argi_globalak[0].specular[3] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(0);
    glGetFloatv(GL_MODELVIEW_MATRIX, argi_globalak[0].m_obj);
    argi_globalak[0].type = 0;
    argi_globalak[0].is_on = 1;

    argi_globalak[1].position[0] = 1.0f;
    argi_globalak[1].position[1] = 1.0f;
    argi_globalak[1].position[2] = 0.0f;
    argi_globalak[1].position[3] = 1.0f;
    argi_globalak[1].ambient[0] = 1.2f;
    argi_globalak[1].ambient[1] = 1.2f;
    argi_globalak[1].ambient[2] = 1.2f;
    argi_globalak[1].ambient[3] = 1.0f;
    argi_globalak[1].diffuse[0] = 1.0f;
    argi_globalak[1].diffuse[1] = 1.0f;
    argi_globalak[1].diffuse[2] = 1.0f;
    argi_globalak[1].diffuse[3] = 1.0f;
    argi_globalak[1].specular[0] = 1.0f;
    argi_globalak[1].specular[1] = 1.0f;
    argi_globalak[1].specular[2] = 1.0f;
    argi_globalak[1].specular[3] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(1);
    glGetFloatv(GL_MODELVIEW_MATRIX, argi_globalak[1].m_obj);
    argi_globalak[1].type = 1;
    argi_globalak[1].is_on = 0;
}

void objektu_fokoa_hasieratu()
{
    argi_globalak[2].position[0] = _selected_object->max.x / 2;
    argi_globalak[2].position[1] = _selected_object->max.y / 2;
    argi_globalak[2].position[2] = _selected_object->max.z;
    argi_globalak[2].position[3] = 1.0f;
    argi_globalak[2].ambient[0] = 1.5f;
    argi_globalak[2].ambient[1] = 1.5f;
    argi_globalak[2].ambient[2] = 1.5f;
    argi_globalak[2].ambient[3] = 1.0f;
    argi_globalak[2].diffuse[0] = 1.5f;
    argi_globalak[2].diffuse[1] = 1.5f;
    argi_globalak[2].diffuse[2] = 1.5f;
    argi_globalak[2].diffuse[3] = 1.0f;
    argi_globalak[2].specular[0] = 1.0f;
    argi_globalak[2].specular[1] = 1.0f;
    argi_globalak[2].specular[2] = 1.0f;
    argi_globalak[2].specular[3] = 1.0f;
    argi_globalak[2].cut_off = 45.0f;
    argi_globalak[2].spot_direction[0] = 0.0f;
    argi_globalak[2].spot_direction[1] = 0.0f;
    argi_globalak[2].spot_direction[2] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(2);
    _selected_object->MB = (MZ *)malloc(sizeof(MZ));
    fokoaren_matrizea();
    argi_globalak[2].type = 2;
    argi_globalak[2].is_on = 0;
}

void kamera_fokoa_hasieratu()
{
    argi_globalak[3].position[0] = _selected_kamera->max.x / 2;
    argi_globalak[3].position[1] = _selected_kamera->max.y / 2;
    argi_globalak[3].position[2] = _selected_kamera->max.z;
    argi_globalak[3].position[3] = 1.0f;
    argi_globalak[3].ambient[0] = 1.5f;
    argi_globalak[3].ambient[1] = 1.5f;
    argi_globalak[3].ambient[2] = 1.5f;
    argi_globalak[3].ambient[3] = 1.0f;
    argi_globalak[3].diffuse[0] = 1.5f;
    argi_globalak[3].diffuse[1] = 1.5f;
    argi_globalak[3].diffuse[2] = 1.5f;
    argi_globalak[3].diffuse[3] = 1.0f;
    argi_globalak[3].specular[0] = 1.0f;
    argi_globalak[3].specular[1] = 1.0f;
    argi_globalak[3].specular[2] = 1.0f;
    argi_globalak[3].specular[3] = 1.0f;
    argi_globalak[2].cut_off = 45.0f;
    argi_globalak[2].spot_direction[0] = 0.0f;
    argi_globalak[2].spot_direction[1] = 0.0f;
    argi_globalak[2].spot_direction[2] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    put_light(3);
    _selected_kamera->MB = (MZ *)malloc(sizeof(MZ));
    kameraren_matrizea();
    argi_globalak[3].type = 3;
    argi_globalak[3].is_on = 0;
}

void ertzen_vektore_normala_kalk()
{
    vector3 v0 = {0, 0, 0};
    vertex *v1;
    for (int i = 0; i < _selected_object->num_vertices; i++)
    {
        _selected_object->vertex_table[i].v_normala = v0;
    }

    for (int j = 0; j < _selected_object->num_faces; j++)
    {
        for (int k = 0; k < _selected_object->face_table[j].num_vertices; k++)
        {
            v1 = &(_selected_object->vertex_table[_selected_object->face_table[j].vertex_table[k]]);
            v1->v_normala.x = v1->v_normala.x - _selected_object->face_table[j].v_normala.x;
            v1->v_normala.y = v1->v_normala.y - _selected_object->face_table[j].v_normala.y;
            v1->v_normala.z = v1->v_normala.z - _selected_object->face_table[j].v_normala.z;
        }
    }

    for (int i = 0; i < _selected_object->num_vertices; i++)
    {
        v1 = &(_selected_object->vertex_table[i]);

        v1->v_normala.x = v1->v_normala.x / v1->num_faces;
        v1->v_normala.y = v1->v_normala.y / v1->num_faces;
        v1->v_normala.z = v1->v_normala.z / v1->num_faces;
    }
}

void materiala_jarri(){
    _selected_object -> materiala = horia;
}

void materialak_hasieratu(){
    horia = (materiala *)malloc(sizeof(materiala));
    zilarra = (materiala *)malloc(sizeof(materiala));

    horia->ambient[0] = 0.05f;
    horia->ambient[1] = 0.05f;
    horia->ambient[2] = 0.0f;
    horia->ambient[3] = 1.0f;
    horia->diffuse[0] = 0.5f;
    horia->diffuse[1] = 0.5f;
    horia->diffuse[2] = 0.4f;
    horia->diffuse[3] = 1.0f;
    horia->specular[0] = 0.7f;
    horia->specular[1] = 0.7f;
    horia->specular[2] = 0.04f;
    horia->specular[3] = 1.0f;
    horia->shininess[0] = 0.078125f;

    zilarra->ambient[0] = 0.23125f;
    zilarra->ambient[1] = 0.23125f;
    zilarra->ambient[2] = 0.23125f;
    zilarra->ambient[3] = 1.0f;
    zilarra->diffuse[0] = 0.2775f;
    zilarra->diffuse[1] = 0.2775f;
    zilarra->diffuse[2] = 0.2775f;
    zilarra->diffuse[3] = 1.0f;
    zilarra->specular[0] = 0.773911f;
    zilarra->specular[1] = 0.773911f;
    zilarra->specular[2] = 0.773911f;
    zilarra->specular[3] = 1.0f;
    zilarra->shininess[0] = 89.6f;

}



void materiala_aldatu(){
    if (_selected_object->materiala == horia)
    {
        _selected_object->materiala = zilarra;
    }
    else
    {
        _selected_object->materiala = horia;
    }
}

void intentsitatea_aldatu(int i, int argia_i){
    argi_globalak[argia_i].ambient[0] += i*2;
    argi_globalak[argia_i].ambient[1] += i*2;
    argi_globalak[argia_i].ambient[2] += i*2;
    argi_globalak[argia_i].ambient[3] += i*2;
    argi_globalak[argia_i].diffuse[0] += i*2;
    argi_globalak[argia_i].diffuse[1] += i*2;
    argi_globalak[argia_i].diffuse[2] += i*2;
    argi_globalak[argia_i].diffuse[3] += i*2;
    argi_globalak[argia_i].specular[0] += i*2;
    argi_globalak[argia_i].specular[1] += i*2;
    argi_globalak[argia_i].specular[2] += i*2;
    argi_globalak[argia_i].specular[3] += i*2;
}