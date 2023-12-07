#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>




// kullan�c� men�s� tan�mlama
int baslama() {
	int secim;
	do {
		printf("1 -> Oyuna Basla");
		printf("\n2 -> Nasil Oynanir"); // FILE pointer ile ekrana text dosyasini yazdir.
		printf("\n3 -> Cikis\n");
		printf("\nSeciminizi giriniz : ");
		scanf("%d",&secim);
	}while(secim>3 || secim<1);
	
	return secim;
	
}


// may�nlar� rastgele yerle�tirme
void mayinYerlestir(int matris[8][8]){
	//10 tane mayin yerlestir.
	srand(time(NULL));
	int sayac=0;
	while(sayac<10){
		
		int i = rand() % 8;
		int j = rand() % 8;
			
		if(matris[i][j]!=-1) {
			matris[i][j]=-1;
			sayac++;	
		}else{
			i = rand() % 8;
			j = rand() % 8;
		}
		
	}
}


//secilen karenin kom�usunu kontrol etme - may�n yoksa kulln�c�ya g�sterir, 
int cevredeMayinVarMi (int matris[8][8],char arayuzMatris[8][8],int satir, int sutun) {
	// cevredeki 8 kareyi kontrol eden for
	if(matris[satir-1][sutun-1]==-1){
		//program� sonland�r
		printf("Mayini actiniz...");
		return -1;
	}else{
		
		int mayinSayisi = 0;
        for (int i = satir - 1; i <= satir + 1; i++) {
            for (int j = sutun - 1; j <= sutun + 1; j++) {
                if (i >= 0 && i < 8 && j >= 0 && j < 8 && matris[i][j] == -1) {
                	
                    mayinSayisi++;
                }
            }
        }
        
        
        if (mayinSayisi == 0) {
            arayuzMatris[satir - 1][sutun - 1] = '0';

            for (int a = satir - 1; a <= satir + 1; a++) {
                for (int b = sutun - 1; b <= sutun + 1; b++) {
                    if (a >= 0 && a < 8 && b >= 0 && b < 8 && matris[a - 1][b - 1] != -1 && arayuzMatris[a - 1][b - 1] == '#') {
                        cevredeMayinVarMi(matris, arayuzMatris, a, b);
                    }
                }
            }
        } else {
            arayuzMatris[satir - 1][sutun - 1] = mayinSayisi + '0';
        }
	

        return 0;
        
	}
	
	
}




int main() {
	int secim=baslama();
	
	if(secim==1){
		printf("Oyun Basladi ...\n\n");
		// aray�z tasar�m� 8x8
		int matris[8][8] = {0}; //kullan�c� bunu g�rmeyecek, as�l matris
		char arayuzMatris[8][8];
	    for (int i = 0; i < 8; i++) {
	        for (int j = 0; j < 8; j++) {
	            arayuzMatris[i][j] = '#';
	        }
	    }	
		mayinYerlestir(matris);
		printf("     1   2   3   4   5   6   7   8\n\n");
		for(int i=0;i<8;i++){
			printf("%d  ",i+1);
			
			for(int j=0;j<8;j++){
				
				printf("| %c ",arayuzMatris[i][j]);
				
			}
			printf("|\n\n");
			
		}
		int satir,sutun;
		printf("Lutfen belirtilen formatta bir yer seciniz. (satir,sutun) :\n");
		scanf("%d,%d",&satir,&sutun);
		
		while(cevredeMayinVarMi(matris,arayuzMatris,satir,sutun) != -1){
			if (satir < 1 || satir > 8 || sutun < 1 || sutun > 8) {
       			printf("Ge�ersiz giris! Lutfen tekrar deneyin.\n");
    		}else{
    			printf("     1   2   3   4   5   6   7   8\n\n");
				for(int i=0;i<8;i++){
					printf("%d  ",i+1);
				
					for(int j=0;j<8;j++){
					
						printf("| %c ",arayuzMatris[i][j]);
					
					}
					printf("|\n\n");
				
				}	
    			
    			
			}
    		
    				
			printf("L�tfen belirtilen formatta bir yer se�iniz. (satir,sutun) :\n");
			scanf("%d,%d",&satir,&sutun);			
				
		}
		printf("Oyun bitti.\n");		
		
		//oyunu baslat
	}else if(secim==2){
		printf("\n");
		// F�LE ile dosya g�ster
		// geri basg�ca donme butonu
		FILE *fp;
		char c;
		fp = fopen("nasiloynanir.txt","r");
		if(fp==NULL){
			printf("\nDosya acilamadi...");
			return 1;
		}
		
		fseek(fp, 0, SEEK_SET); // Dosyan�n ba��na git
		c=fgetc(fp);
		while(c!=EOF){
			printf("%c",c);
			c=fgetc(fp);
		}
		
		fclose(fp);
		baslama();
	}else {
		// program� sonland�r
		printf("\nOyundan cikiliyor...");
		getch();
	}
		
	return 0;
}
