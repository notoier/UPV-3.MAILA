#include <stdio.h>
#include <stdlib.h>

typedef struct elem
{
    int bal;
    struct elem *hptr;

} elem;

// TODO code to insert an element into the list in ascending order

void insert_in_ascendent_order(elem **kanptrptr, elem *bptr)
{
    while ((*kanptrptr != 0) && ((*kanptrptr)->bal < bptr->bal))
        kanptrptr = &((*kanptrptr)->hptr);
    
    bptr->hptr = *kanptrptr;
    *kanptrptr = bptr;
}


int main(int argc, char *arg[])
{
    int teklatukoa, kop;
    elem *leptr, *lptr;
    char kaka[80];

    leptr = 0;

    printf("Insert number\n  ");

    for ( 
            kop = scanf("%d",&teklatukoa);
            teklatukoa != 0;
            kop = scanf("%d",&teklatukoa) 
        )
            {
                if (kop >0)
                    {
                        printf("%d irakurri dut\n",teklatukoa);
                        // create elem with the value inserted from keyboard
                        lptr = (elem *) malloc(sizeof(elem));
                        lptr->bal = teklatukoa;
                        insert_in_ascendent_order(&leptr, lptr);
                    }
                else
                    {
                        printf("Only numbers!!!\n\n");
                        exit(0);
                    }
                printf("Insert number\n  ");
            }
    for (lptr = leptr; lptr != 0; lptr = lptr->hptr)
        printf( "Balioa = %d\n",lptr->bal);
}
