#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


int main(int argc, char ** argv){
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
	
	fread(&scm,sizeof(uint32_t),1,fh);
	cm = (char *)malloc(scm);
	fread(cm,scm,1,fh);
		
	printf("%s\n",header);
	printf("File Index is %d\n",(int)fileIdx);
	printf("%s\n",m1);
	printf("%s\n",m2);
	printf("%s\n",m3);
	printf("%s\n",key);

	
	ptr = cm;
	
	for(int i = 0;;ptr++,i++){
		
		*ptr = *ptr ^ key[i % strlen(key)];
		if (!(*ptr)){
			break;
		}	
	}
	printf("%s\n",cm);
	
	if(checker == fileIdx){
		printf("your index is correct\n");
	}else{
		printf("your index is NOT correct\n");
	}

}