#include <stdio.h>
#include <stdlib.h>


void turnTable(unsigned char **A, unsigned char **B, int width, int height) {
    for (int j = 0; j < width; j++) {
        for (int i = height - 1; i >= 0; i--) {
            B[width - 1 - j][i * 3] = A[i][j * 3];        // blue
            B[width - 1 - j][i * 3 + 1] = A[i][j * 3 + 1];// Green
            B[width - 1 - j][i * 3 + 2] = A[i][j * 3 + 2];// red
        }
    }
}

int main() {
    int width, height, depth;  
     // δέσμευση μνήμης για τον πίνακα που αποθηκεύουμε τα στοιχεία του header
    unsigned char  *header= malloc(54*sizeof(unsigned char));
    if (!header){
        return 1;         //malloc failed
    }

    FILE *rotated = stdout;

    //έλεγχος στοιχείων header
    int headerbytes =fread(header, sizeof(unsigned char), 54, stdin);
  
    if(header[0]!='B' || header[1]!='M'){
        printf("not a bmp file");             //έλεγχος αν είναι οντως bmp file
        return 1;
    }

    int offset= *(int *)&header[10];
    if (headerbytes<54){
        printf("1\n");
        return 1;                                // δεν τηρεί τις τεχνικές προδιαγραφές
    }
    if (offset>54){
        header=realloc(header, (offset)* sizeof(unsigned char));            // δεσμεύει κιαλλη μνήμη αφού τελικά δεν ήταν 54 bytes μόνο το header
        if(!header){
            return 1;                       //realloc failed
        }
        headerbytes= fread(header+54, sizeof(unsigned char), offset-54, stdin);    //για να διαβάσει τα υπόλοιπα στοιχεία του header
    }
    

    width = *(int *)&header[18];                //διαβάουμε το ύψος και πλάτος της εικόνας
    height = *(int *)&header[22];
    

    int padding = (4 - (3 * width % 4)) % 4;
    if ((3*width + padding)%4 != 0){
        printf("2\n");
        return 1;                              //λάθος πλάτος ή padding
    }

    int imageSize= *(int *)&header[34];            //μέγεθος της εικόνας 
    if ((width*3+padding)*height != imageSize){
        printf("3\n");
        return 1;                               // λάθος image size στο header
    }
    
    int fileSize= *(int *)&header[2];          // μέγεθος αρχείου
    if((imageSize + offset)!= fileSize ){
        printf("4\n");
        return 1;                               // λάθος μέγεθος αρχείου στο header
    }

     
    depth= *(int *)&header[28];
    if(depth!=24){
        printf("4\n");
        return 1;                             //μη έγκυρο color-depth
    }

     //δέσμευση μνήμης για τον δισδιάστατο πίνακα-την εικόνα
    
    unsigned char **bmp = malloc(height * sizeof(unsigned char *));
    if (!bmp) {
        
        return 1;             // malloc failed
    }
    
    for (int i = 0; i < height; i++) {
        bmp[i] = (unsigned char *)malloc(width * 3 * sizeof(unsigned char));
        if (!bmp[i]) {
            return 1;           // malloc failed
        }
    }

    // διαβάζουμε την εικόνα
    int bytesRead=0;
    
    for (int i = 0; i < height; i++) {
       bytesRead= fread(bmp[i], sizeof(unsigned char), 3 * width, stdin);     //3*width (κάθε πιξελ αποτελείται από 3 bytes RGB)
        for (int j = 0; j < padding; j++) {
            fgetc(stdin);
        }
    }
    if(bytesRead!= 3*width){
        return 1;
    }
    
    // δεσμεύω μνήμη για τον νέο πίνακα- rotated εικόνα
    unsigned char **bmpnew = (unsigned char **)malloc(width * sizeof(unsigned char *));
    if (!bmpnew) {
        return 1;
    }
    for (int i = 0; i < width; i++) {
        bmpnew[i] = (unsigned char *)malloc(height * 3 * sizeof(unsigned char));
        if (!bmpnew[i]) {
            return 1;
        }
    }

    turnTable(bmp, bmpnew, width, height);
    
    // φτιάχνω το header του νέου αρχείου εικόνας
    unsigned char headernew[offset];
    for (int i = 0; i < offset; i++) {
        headernew[i] = header[i];
    }
    *(int *)&headernew[18] = height;
    *(int *)&headernew[22] = width;
    int paddingnew = (4 - (3 * height % 4)) % 4;
    *(int *)&headernew[34] = width*height*3 + width*paddingnew ;
    *(int *)&headernew[2] = width*height*3 + width*paddingnew + offset;
    fwrite(headernew, sizeof(unsigned char), offset, rotated);
    
    // "φτιάχνουμε" την εικόνα σε ένα άλλο αρχείο 
   
    for (int i = 0; i < width; i++) {
        fwrite(bmpnew[i], sizeof(unsigned char), 3 * height, rotated);
        for (int j = 0; j < paddingnew; j++) {
            fputc(0, rotated);
        }
    }
    
    // ελευθερώνουμε την μνήμη που δεσμέυσαμε
    for (int i = 0; i < height; i++) {
        free(bmp[i]);
    }
    free(bmp);
    for (int i = 0; i < width; i++) {
        free(bmpnew[i]);
    }
    free(bmpnew);
    free(header);

    return 0;
}