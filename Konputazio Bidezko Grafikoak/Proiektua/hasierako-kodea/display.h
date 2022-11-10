#ifndef DISPLAY_H
#define DISPLAY_H

void display(void);
void reshape(int width, int height);
void output(int x, int y, float r, float g, float b, void* font, char *str);

#endif // DISPLAY_H
