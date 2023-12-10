#include <stdio.h>
#include <stdlib.h>
#include <time.h>




// kullanýcý menüsü tanýmlama
int baslama() {
	int secim;
	do {
		printf("\n1 -> Oyuna Basla");
		printf("\n2 -> Nasil Oynanir"); // FILE pointer ile ekrana text dosyasini yazdir.
		printf("\n3 -> Cikis\n");
		printf("\nSeciminizi giriniz : ");
		scanf("%d",&secim);
	}while(secim>3 || secim<1);
	
	return secim;
	
}

// mayýnlarý rastgele yerleþtirme
void mayinYerlestir(int matris[8][8]){
	//10 tane mayin yerlestir.
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

int oyunBitti(int matris[8][8],char arayuzMatris[8][8]) {
	int sayac=0;
	
	for(int i=0;i<8;i++){
		for(int j=0; j<8;j++){
			if(arayuzMatris[i][j]=='#'){
				if(matris[i][j]==-1){
					sayac ++;
				}
				
			}
		}
	}
	if (sayac==8){
		return 0;   //oyun bitti 
	}else{
		return 1; //devam 
	}
}


//secilen karenin komþusunu kontrol etme - mayýn yoksa kullnýcýya gösterir, 
int cevredeMayinVarMi (int matris[8][8],char arayuzMatris[8][8],int satir, int sutun) {
	
	if(oyunBitti(matris,arayuzMatris)==1){ // karelerin bulundugu indislerde sadece -1 varsa oyun biter aksi halde burasý çalýþýr
	
		if(matris[satir-1][sutun-1]==-1){
			//programý sonlandýr
			printf("Mayini actiniz...");
			baslama();
		}else{
			
			int mayinSayisi = 0;
	        for (int i = satir - 2; i <= satir; i++) {
	            for (int j = sutun - 2; j <= sutun ; j++) {
	                if (i >= 0 && i < 8 && j >= 0 && j < 8 && matris[i][j] == -1) {
	                	
	                    mayinSayisi++;
	                }
	            }
	        }
	        
	        
	        if (mayinSayisi == 0) {
	            arayuzMatris[satir - 1][sutun - 1] = '0';
	
	            for (int a = satir - 2; a <= satir ; a++) {
	                for (int b = sutun - 2; b <= sutun; b++) {
	                    if (a >= 0 && a < 8 && b >= 0 && b < 8 && matris[a - 1][b - 1] != -1 && arayuzMatris[a - 1][b - 1] == '#') { //girilen yerde mayýn yoksa ve açýlmamiþsa
	                        cevredeMayinVarMi(matris, arayuzMatris, a, b);
	                    }
	                }
	            }
	        } else {
	            arayuzMatris[satir - 1][sutun - 1] = mayinSayisi + '0';
	        }
		
	
	        return 0;
	        
		}
		
	}else{
		printf("\n Tebrikler oyun bitti!");
	}
}




int main() {
	int secim=baslama();
	srand(time(NULL));
	
	if(secim==1){
		printf("Oyun Basladi ...\n\n");
		// arayüz tasarýmý 8x8
		int matris[8][8] = {0}; //kullanýcý bunu görmeyecek, asýl matris
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
       			printf("Geçersiz giris! Lutfen tekrar deneyin.\n");
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
    		
    				
			printf("Lütfen belirtilen formatta bir yer seçiniz. (satir,sutun) :\n");
			scanf("%d,%d",&satir,&sutun);			
				
		}
		printf("Oyun bitti.\n");		
		
		//oyunu baslat
	}else if(secim==2){
		printf("\n");
		// FÝLE ile dosya göster
		// geri basgýca donme butonu
		FILE *fp;
		char c;
		fp = fopen("nasiloynanir.txt","r");
		if(fp==NULL){
			printf("\nDosya acilamadi...");
			return 1;
		}
		
		fseek(fp, 0, SEEK_SET); // Dosyanýn baþýna git
		c=fgetc(fp);
		while(c!=EOF){
			printf("%c",c);
			c=fgetc(fp);
		}
		
		fclose(fp);
		baslama();
	}else {
		// programý sonlandýr
		printf("\nOyundan cikiliyor...");
	}
		
	return 0;
}
