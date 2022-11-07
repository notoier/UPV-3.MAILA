#include <stdio.h>
#include <stdlib.h>

typedef struct elem
{
int bal;
struct elem *hptr;
} elem;

// TODO code to insert an element into the list in ascending order
/*
void insert_in_ascendent_order(...)
{
}
*/

int main(int argc, char *arg[])
{
int teklatukoa,kop;
elem *leptr,*lptr;
char kaka[80];

leptr = 0;
printf("insert number\n  ");
for ( kop = scanf("%d",&teklatukoa);
      teklatukoa != 0;
      kop = scanf("%d",&teklatukoa) )
    {
    if (kop >0)
        {
        printf("%d irakurri dut\n",teklatukoa);
        // create elem with the value inserted from keyboard
        lptr = (elem *) malloc(sizeof(elem));
        lptr->bal= teklatukoa;
        // this code inserts the element into the list pointed by leptr as the first element of the list (LIFO).
        lptr->hptr = leptr;
        leptr = lptr;
        // TODO Change the code to insert the element in ascendent order: erase the two lines above and use a function 
        // void insert_in_ascendent_order(...) with two parameters, one for the list and the second for the element. How should be passed the parameters?
        // insert_in_ascendent_order( , );
        }
      else
        {
        printf("only numbers!!!\n\n");
        exit(0);
        }
      printf("insert number\n  ");
    }
for (lptr = leptr; lptr != 0; lptr = lptr->hptr)
    printf( "balioa = %d\n",lptr->bal);
}