#include <stdio.h>
#include "adtlib.h"
#include "utillib.h"

int main()
{
    printLogo();
    printMenu();
    FILE* file = fopen("src/data/config.cfg", "r");
    if (file != NULL)
    {
        printf(">> ");
        Word word = getWordInputStream(stdin);

        if (isWordEQ(word, "1"))
        {
            printf("NEW GAME!\n");
            int row = getIntInputStream(file);
            int col = getIntInputStream(file);
            printf("row : %d, col : %d\n", row, col);
            char b;
            int x,y;
            LOKASI P;
            MAP M1;
            DaftarLokasi DL;
            int i,j;
            PLAYER P1;
            x = getIntInputStream(file);
            y = getIntInputStream(file);
            P = MakeLOKASI('8',x,y,'h');
            int jmlBangunan = getIntInputStream(file);
            CreateDaftarLokasi(&DL, jmlBangunan+1);
            insertLast(&DL,P);
            createPlayer(&P1,ELMTLD(DL,0));
            printf("%d,%d\n",Absis(pLoc(P1)),Ordinat(pLoc(P1)));
            for(i=0;i<jmlBangunan;i++){
                b = getCharInputStream(file);
                x = getIntInputStream(file);
                y = getIntInputStream(file);
                P = MakeLOKASI(b,x,y,'b');
                insertLast(&DL,P);
            }
            alokasiMAP(&M1,row,col,DL);
            mapBuilding(&M1);
            getAdjacent(&M1,file);
            updateStatus(&M1,P1);
            displayMAP(M1);
            printf("\n");
            displayReachable(M1);
            printf("\n\n");
            movePlayer(M1,&P1,2);
            displayMAP(M1);
            displayReachable(M1);
            
        }
        else if (isWordEQ(word, "2"))
        {
            printf("LOAD GAME!\n");
        }
        else
        {
            fclose(file);
            printf("SAMPAI JUMPA LAGI!\n");
        }
    }
    
    
    

    // printf("hasil get word stdin: ");
    // wordOutputStream(stdout, word, true);

    // char c = getCharSTDIN();
    // printf("hasil get char: %c\n", c);

    

    return 0;
}
