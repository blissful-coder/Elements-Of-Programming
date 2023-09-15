#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct wrapperString
{
    unsigned char *str;
    int len;
} wrapString;

typedef struct wrapperMat
{
    unsigned char **mat;
    int row;
    int col;
} wrapMat;

wrapString give_me_buffer();
wrapMat gridStr(unsigned char* str, int len);
void showMat(wrapMat);
wrapMat encrypt(wrapMat x);
wrapMat decrypt(wrapMat x);

int main(void)
{
    wrapString wstr;
    wrapMat wmat;
    wstr = give_me_buffer();
    wmat = gridStr(wstr.str,wstr.len);
    // printf("\nMy String:\n[%s]\n", wstr.str);
    // showMat(wmat);
    // printf("\nLength of String: %d\n", wstr.len);
    // printf("\nMatrix row: %d, col: %d, product: %d\n",wmat.row,wmat.col, wmat.row * wmat.col);
    wrapMat encrypted = encrypt(wmat);
    printf("\nEncrypted:\n");
    showMat(encrypted);
    wrapMat decrypted = decrypt(encrypted);
    printf("\nDecrypted:\n");
    showMat(decrypted);
    return 0;
}

wrapString give_me_buffer()
{
    int c;
    int i;
    int size = 10;
    unsigned char *str = malloc(size * sizeof(char));
    for (i = 0; (c = getchar()) != '\0' && c != EOF; ++i)
    {
        if (i == size)
        {
            size = 2 * size;
            str = realloc(str, size * sizeof(char));
            if (str == NULL)
            {
                printf("Error Unable to Grow String! :(");
                exit(-1);
            }
        }
        str[i] = c;
    }
    if (i == size)
    {
        str = realloc(str, (size + 1) * sizeof(char));
        if (str == NULL)
        {
            printf("Error Unable to Grow String! :(");
            exit(-1);
        }
    }
    str[i] = '\0';
    wrapString obj;
    obj.str = str;
    obj.len = i;
    return obj;
}

wrapMat gridStr(unsigned char* str, int len)
{
    int l = len;
    int k = 0, row, column;
    row = floor(sqrt(l));
    column = ceil(sqrt(l));

    if (row * column < l)
        row = column;
 
    unsigned char **s = malloc(row*sizeof(char*));
    for (int i=0; i<row; i++){
        s[i] = malloc(column*sizeof(char));
    }
    // convert the string into grid
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            s[i][j] = str[k];
            k++;
        }
    }
    wrapMat obj;
    obj.mat = s;
    obj.row = row;
    obj.col = column;
    return obj;
}

void showMat (wrapMat showMe){
 // Printing the grid
    for (int i = 0; i < showMe.row; i++) {
        for (int j = 0; j < showMe.col; j++) {
            if (showMe.mat[i][j] == '\0')
                break;
            printf("%c",showMe.mat[i][j]);
        }
        printf("\n");
    }
}

wrapMat encrypt (wrapMat x){
 // Printing the grid
    wrapMat enc = x;
    for (int i = 0; i < enc.row; i++) {
        for (int j = 0; j < enc.col; j++) {
            if (enc.mat[i][j] == '\0')
                break;
            enc.mat[i][j] = enc.mat[i][j] + 1;
        }
    }
    return enc;
}

wrapMat decrypt (wrapMat x){
 // Printing the grid
    wrapMat enc = x;
    for (int i = 0; i < enc.row; i++) {
        for (int j = 0; j < enc.col; j++) {
            if (enc.mat[i][j] == '\0')
                break;
           enc.mat[i][j] = enc.mat[i][j] - 1;
        }
    }
    return enc;
}