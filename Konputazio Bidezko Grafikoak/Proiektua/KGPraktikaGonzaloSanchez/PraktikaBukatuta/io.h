#ifndef IO_H
#define IO_H
#include "definitions.h"

void keyboard(unsigned char key, int x, int y);
void print_help();
void argiak_hasieratu();
void put_light(GLint i);
void fokoaren_matrizea();
void kameraren_matrizea();
void objektu_fokoa_hasieratu();
void kamera_fokoa_hasieratu();
void materiala_jarri(int i, object3d *aux_obj);
void materiala_aldatu();


#endif // IO_H
