#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void crypt(char *input, char *key, int size) {
    for(int i =  0; i < size; i++) {
	input[i] = input[i] ^ key[i % strlen(key)];
    }
}

int main(int argc, char ** argv){
    
    /* WRITING
     */
    char head[] = "CS2060";
    char name[] = "Alex Howard";
    char message1[] = "I really like programming. C is one of my favorite languages.";
    char message2[] = "I think I should get an A.";
    char ky[] = "dZ*bZ+w[$Sx[@";
    uint32_t nameSize = strlen(name);
    uint32_t m1Size = strlen(message1);
    uint32_t m2Size = strlen(message2);
    uint32_t keySize = strlen(ky);
    uint32_t index;
    
    FILE * ofh;
    ofh = fopen("outfile.dat", "wb");
    
    fwrite(head, 6, 1, ofh);
    
    fwrite(&index, sizeof(uint32_t), 1, ofh);
    
    fwrite(&nameSize, sizeof(uint32_t), 1, ofh);
    fwrite(name, nameSize, 1, ofh);
    
    fwrite(&m1Size, sizeof(uint32_t), 1, ofh);
    fwrite(message1, m1Size, 1, ofh);
    
    crypt(message2, ky, m2Size);
    fwrite(&m2Size, sizeof(uint32_t), 1, ofh);
    fwrite(message2, m2Size, 1, ofh);
    
    index = ftell(ofh);
    
    fwrite(&keySize, sizeof(uint32_t), 1, ofh);
    fwrite(ky, keySize, 1, ofh);
    
    fseek(ofh, 6, SEEK_SET);
    fwrite(&index, sizeof(uint32_t), 1, ofh);
    
    fclose(ofh);
    
    
    
    /* READING
     */
    FILE * fh;
    char header[7] ={'\0'};
    uint32_t fileIdx,sm1,sm2,sm3,sk,scm;
    char * m1,* m2, * m3, * key, *cm, * ptr;
    uint32_t checker;
    
    
    if(argc > 2){
	return 1;
    }else if (argc == 2){
	fh = fopen(argv[1],"rb");
    }else{
	fh = fopen("outfile.dat","rb");
    }
    
    fread(header,6,1,fh);
    fread(&fileIdx,sizeof(uint32_t),1,fh);
    
    fread(&sm1,sizeof(uint32_t),1,fh);
    m1 = (char *)malloc(sm1);
    fread(m1,sm1,1,fh);
    
    //	printf("%s",m1);
    
    fread(&sm2,sizeof(uint32_t),1,fh);
    m2 = (char *)malloc(sm2);
    fread(m2,sm2,1,fh);
    
    //	printf("%s",m2);
    
    fread(&sm3,sizeof(uint32_t),1,fh);
    m3 = (char *)malloc(sm3);
    fread(m3,sm3,1,fh);
    checker = ftell(fh);
    fread(&sk,sizeof(uint32_t),1,fh);
    key = (char *)malloc(sk);
    fread(key,sk,1,fh);
    
    //	printf("%s",m3);
    
    //     fread(&scm,sizeof(uint32_t),1,fh);
    //     cm = (char *)malloc(scm);
    //     fread(cm,scm,1,fh);
    
    printf("%s\n",header);
    printf("File Index is %d\n",(int)fileIdx);
    printf("%s\n",m1);
    printf("%s\n",m2);
    printf("%s\n",m3);
    printf("%s\n",key);
 
    
//     ptr = m3;
//     
//     for(int i = 0;;ptr++,i++){
// 	*ptr = *ptr ^ key[i % strlen(key)];
// 	if (!(*ptr)){
// 	    break;
// 	}
//     }
//     printf("%s\n", m3);
    
        crypt(m3, key, sm3);
	printf("%s\n", m3);
    
    if(checker == fileIdx){
	printf("Your index is correct\n");
    }else{
	printf("Your index is NOT correct\n");
    }
    
}