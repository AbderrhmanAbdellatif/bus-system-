// perjesi2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
enum  Cinsiyet {K,E};
enum gun{ Pazartesi, Sali, carsamba, Persembe, Cuma, Cumartesi, Pazar };
typedef  struct M {
	char isim [20];
	char soyisim[20];
	int TcNo;
	enum  Cinsiyet cinsiyet;
}Musteri;
typedef struct k {
	int no;
	char DoluYadeBos;
	Musteri musteri;
	enum gun Gun;
}Koltuk;
typedef struct bus{
	char Plaka[20];
	char Marka[20];
	int model;
	Koltuk koltuk[10][4];
}otobus;
Koltuk otobusKoltuk[40];//cunku 40 tane koltugum var otubuste
Koltuk YeniKoltuk;// yeni koltuk alanlari icin 
Musteri YeniMusteri;// yeni musteri icin  yani gelen musterini bilgini almak  icin 
otobus bus;// struct otubus 
void Otobuokutma(FILE *fp);
Koltuk KoltukDoldur(int N,char D,Musteri M,enum gun g);
Musteri MusterDoldur(char isim[],char soyisim[],int Tc,enum Cinsiyet C);
void Koltuksatis(FILE *fp);
int KisiArama();
//void Karbarcik(Koltuk D[], int N);//bu sirlama kodu yaptim ki cunku  dosyasya sirlama bir sekilde dosya yazdirmek isitiyorum
int main()
{
	puts(" GidereGider Turizm");
	int secim;
	char Durm;
	char temp;
	int degisken=0;
	do{
		FILE *dosya = fopen("C:\\Users\\Aizen\\Desktop\\otobus.txt", "r");
		puts("1-  Otubus durumu goster  ");
		puts("2-  Koltuk satis");
		puts("3-  kisi arama ");
		puts("4-  cikis ");
		scanf("%d",&secim);
		if (secim == 1) {
			Otobuokutma(dosya);
		}
		if (secim == 2) {
			puts("KOLTUK SATIS ");
			puts("Yeni koltuk  satisi yapmak ister misiniz ? y/n ");
			printf(" Durum secin :");
			while (1) {//dongu yaptim ki  bir sonraki islem gelmek icin 
				scanf("%c", &Durm);// gelen durum icin
				if (Durm == 'y')Koltuksatis(dosya);//koltuk satis icin 
				if (Durm == 'n') break;// eger n istir ise dongun cikacak baska komutlara gidecek 
			}
		}if (secim==3){
				puts("KISI ARAMA");
				printf("yeni kisi arama yapmak ister misiniz? y/n \n");	
				fflush(stdout);
				printf(" Durum secin :");
				while (1)
				{
					getchar();
					scanf("%c", &temp);// gelen durum icin
					if (temp == 'y') degisken=KisiArama();//kisi arama icin 
					if (temp == 'n') break;// eger n istir ise dongun cikacak baska komutlara gidecek 
					if (degisken == -1) break;//burda otobus dolu mu bos mu  kontur ediyorum 
					if (degisken == 1)puts("Boyle bir kisi Yok !!");
				}
			}
		     if (secim == 4) {
		    	break;
		}
		puts(" ");
	} while (1);
	system("pause");
       return 0;
}
void Otobuokutma(FILE *fp) {
	int dizi[10][4];
	int T = 0;//toplam  icin 
	char p[20],M[20],Mol[20];//dizi tutmak icin 
	int mod = 0;// sayilari tutmak icin 
	int f=0, d=0, v=0; // dizini souna kadar gelmek icin kullandi m
	int sayi=0,k=0;//sayi dizini bouyuntu yapmak icin 
	char c = getc(fp);// karkter karkter okusun diye 
	while (c != EOF) {// dosya sonua kadar okusun diye 
		if (c == '/') {// "/ " gorudugu zaman  yeni satir insin diye 
			printf("\n");
			sayi = 0;// sayi yeni bir dize girmek icin sifiriyorum 
			k++;
		}
		else {
			if (k==0) {
				 p[sayi] = c;// burada plaka dolduyorum
				 bus.Plaka[sayi]= p[sayi];//dizi doldurdum 
				 sayi++;// sayi atiyoum 
				 f++;//son sayi bulmak istiyorum 
			}
			else if (k==1){
			   	M[sayi] = c;//burda marka dolduruoyrum
			 	 bus.Marka[sayi]= M[sayi] ;
				 sayi++;
				 d++;
			}
			else{
				Mol[sayi] = c;
				bus.model = atoi(Mol);//atoi founkstion  kullandim ki sayi cevresin 
				sayi++;
				if (sayi==3){
					Mol[sayi] = '\0';
				}
			}
			
		}
		if (c == '\n') {
			break;
		}
		c = getc(fp);
	}
	bus.Plaka[f] = '\0';//sonua \0 ekliyorum cunku  bitme nokta gibi 
	bus.Marka[d] = '\0';//sonua \0 ekliyorum cunku  bitme nokta gibi 
	printf("       %s\n", bus.Plaka);
	printf("       %s\n", bus.Marka);
	printf("       %d\n", bus.model);
	char karkter = getc(fp);
	int KisiDurum=7, z=0, KisiKontrulu=0,s=0; 
	char rakem[2], Durum, kisiAdi[100], Gunler[2], kisiSoyadi[100], TcK[50], kisiler[2];
	char personelAdi[20], personelSoyadi[20];
	d = 0, v = 0;
    int n = 0,m=0,H=0;
	int i, j;//matrix icin kullandim 
	int kimlik=0, Rakemlar=0;
	int YolcullukGun;
	int pl, a, q,t;//for icin kulladim 
	int doldurma = 0;//bir dizini boytunu doldurmak icin kullaniyorum 
	int koltukleri;//koltuk sayisi yapmak icin 
	while (karkter!=EOF){
		if (karkter == '\n') {
			n = 0;//dizini sonuna bilmek icin  kullandim 
			m = 0;
			v = 0;
			d = 0;
			KisiKontrulu = 0;//kisi konturlu  sifirliyorum
			s = 0;//dizini index sifirliyorum
			Rakemlar = 0;//rakem sifirliyorum
			kimlik = 0;//tc kimlik sifirliyorum
			H = 0;//burada 
			Durum = '\0';
			for (pl = 0;  pl< 2; pl++){
				rakem[pl]=' ';
			}//burada dizleri sifirlamak icin kullandim 
			for ( a = 0; a < 20; a++){
				kisiAdi[a] = ' ';
			}
			for ( q = 0; q <50; q++){
				kisiSoyadi[q] = ' ';
			}
			for ( t = 0; t < 50; t++){
				TcK[t] = ' ';
			}
		}
		if (karkter == '/') {
			KisiKontrulu++;//dolmak icin konturlu
			s = 0;
		}
		else {
			if (KisiKontrulu == 0 && karkter != '\n') {//kisi konturlu 0 oldugu zaman ve ayine zaman gelen charin '\n' olmasi 
				rakem[s] = karkter;//koltuk sandalsasi icin 
				Rakemlar = atoi(rakem);
				s++;
				d++;
			}
			else if (KisiKontrulu == 1) {
				Durum = karkter;//kisinin  durum yapmak icin 
			}else if (KisiKontrulu==2) {
				Gunler[s] = karkter;
				YolcullukGun = atoi(Gunler);//burada gunleri hesapliyorum
				s++;
			}
			else if (KisiKontrulu == 3) {
				kisiAdi[s] = karkter;
				s++;
				v++;
			}
			else if (KisiKontrulu == 4) {
				kisiSoyadi[s] = karkter;//kisi sayAdi doldurmak icin  
				s++;
				n++;
			}
			else if (KisiKontrulu == 5) {
				TcK[s] = karkter;
				kimlik = atoi(TcK);//Tc  kimlik icin 
				s++;
			}
			else if(KisiKontrulu==6){
				kisiler[s]= karkter;//erkek mi kadin mi oldugunu yapmak icin 
				H = atoi(kisiler);
				KisiKontrulu++;
			}
		}
		if (KisiDurum==KisiKontrulu){//eger estir  ise o zaman girecek
			kisiAdi[v] = '\0';//dizini souna bitis nokta koymak isiyorum 
			kisiSoyadi[n] = '\0';//dizini sonua bitis nokta koymak istiyorum 
			strcpy(personelAdi,kisiAdi);//burada dosyadan gelen Adiyla dolduyorum 
			strcpy(personelSoyadi,kisiSoyadi);//burada dosyadan gelen Adiyla dolduyorum 
			if (H==1)YeniMusteri = MusterDoldur(personelAdi, personelSoyadi, kimlik, E);
			else YeniMusteri = MusterDoldur(personelAdi, personelSoyadi, kimlik, K);
			//Pazartesi, Sali, carsamba, Persembe, Cuma, Cumartesi, Pazar switch kullanarak dolduuyorum
			switch (YolcullukGun){//Gunleri sabit oldugun icin bu case kullandim
			case 1:
				YeniKoltuk = KoltukDoldur(Rakemlar,Durum,YeniMusteri,Pazartesi);
				break;
			case 2:
				YeniKoltuk = KoltukDoldur(Rakemlar, Durum, YeniMusteri, Sali);
				break;
			case 3:
				YeniKoltuk = KoltukDoldur(Rakemlar, Durum, YeniMusteri, carsamba);
				break;
			case 4:
				YeniKoltuk = KoltukDoldur(Rakemlar, Durum, YeniMusteri, Persembe);
				break;
			case 5:
				YeniKoltuk = KoltukDoldur(Rakemlar, Durum, YeniMusteri, Cuma);
				break;
			case 6:
				YeniKoltuk = KoltukDoldur(Rakemlar, Durum, YeniMusteri, Cumartesi);
				break;
			case 7:
				YeniKoltuk = KoltukDoldur(Rakemlar, Durum, YeniMusteri, Pazar);
				break;

			}
			for ( koltukleri = 0; koltukleri<40; koltukleri++){
				if (koltukleri==YeniKoltuk.no){
					otobusKoltuk[koltukleri] = YeniKoltuk;
				}
			}
		}
		karkter = getc(fp);
	}
	int y = 0;//cunku bir sayi yapmak istiyorum ki daha bulmak icin 
	for (i = 0; i<10; i++) {
		for (j = 0; j <4; j++) {
			dizi[i][j] = doldurma++;
		}
	}
	printf("     S|   0   1   2   3 \n");
	printf("          -   -   -   - \n");
	for (i = 0; i <10; i++) {
		printf("   %d |", i);
		for (j = 0; j <4; j++) {
			if (dizi[i][j] == otobusKoltuk[y].no) {//hangi koltuk dololdugunu kontur ediyorum
				if (otobusKoltuk[y].musteri.cinsiyet == K) {// eger kadin ise calisacak
					printf("   O");
				}
				else {//eger erkek ise 
					printf("   X");
				}
			}
			else printf("   %d", dizi[i][j]);
			y++;
		}
		printf("\n ");
	}
	puts("........................(40");
	puts("SATIR");
}
Koltuk KoltukDoldur(int N, char D, Musteri M, enum gun g) {
	Koltuk K;
	K.DoluYadeBos = D;
	K.Gun = g;
	K.musteri = M;
	K.no = N;
	return K;
};
Musteri MusterDoldur(char s[], char soy[], int Tc, enum Cinsiyet C) {
	Musteri M;
	strcpy(M.isim,s);
	strcpy(M.soyisim,soy);
	M.TcNo = Tc;
	M.cinsiyet = C;
	return M;
}
void Koltuksatis(FILE *fp) {
	puts("bilgileri giriniz ");
	FILE *FILEP = fopen("C:\\Users\\Aizen\\Desktop\\bus.txt", "w");;
	fprintf(FILEP, "%s", bus.Plaka);
	fprintf(FILEP, "\n%s", bus.Marka);
	fprintf(FILEP, "\n%d \n ", bus.model);
	int yerileri;
	//Koltuk KoltukDoldur(int N, char D, Musteri M, enum gun g)
	//Musteri MusterDoldur(char s[], char soy[], int Tc, enum Cinsiyet C)
	char AdiKisiler[100], SoyadKisiler[100];
	int Tckisiler, KoltukNo;
	char  gunicin = '\0';
	enum Cinsiyet Cinsiyetkisi;
	enum   gun Gunlerkisi;
	Musteri gelenMusteri;
	Koltuk VarKoltuk;
	char harf;
	puts("Musteri >");
	printf("Ad: ");
	scanf("%s", AdiKisiler);
	strcpy(gelenMusteri.isim, AdiKisiler);//Mustersini Adi
	printf("Soyad :");
	scanf("%s", SoyadKisiler);
	strcpy(gelenMusteri.soyisim, SoyadKisiler);//Musterini Soyadi
	printf("Tc:");
	scanf("%d", &Tckisiler);
	gelenMusteri.TcNo = Tckisiler;//Musternini Tckimlik
	printf("cinsiyet E/K :");
	scanf("%c", &harf);
	char j = getchar();//chardaki sikiniti ciktigim icin boyle yaptim
	if (j == 'K') { Cinsiyetkisi = K; }//kendin ise 
	else { Cinsiyetkisi = E; }//erkek ise 
	gelenMusteri.cinsiyet = Cinsiyetkisi;
	YeniMusteri = gelenMusteri;
	printf("\n");
	puts("Koltuk >");
	printf("No:");
	scanf("%d", &KoltukNo);
	VarKoltuk.no = KoltukNo;//koltuk numarasi yapiyorum
	VarKoltuk.DoluYadeBos = 'D';//dol yapiyorum 
	VarKoltuk.musteri = YeniMusteri;//yeni gelen musteri ekliyorum 
	//----------------gunleri yapiyorum
	printf("Gun : ");
	char gelenGunleri[10];
	scanf("%s", gelenGunleri);
	if (strcmp(gelenGunleri, "Pazartesi") == 0)VarKoltuk.Gun = Pazartesi;
	if (strcmp(gelenGunleri, "Sali") == 0) VarKoltuk.Gun = Sali;
	if (strcmp(gelenGunleri, "carsamba") == 0) VarKoltuk.Gun = carsamba;
	if (strcmp(gelenGunleri, "Persembe") == 0) VarKoltuk.Gun = Persembe;
	if (strcmp(gelenGunleri, "Cuma") == 0) VarKoltuk.Gun = Cuma;
	if (strcmp(gelenGunleri, "Cumartesi") == 0) VarKoltuk.Gun = Cumartesi;
	if (strcmp(gelenGunleri, "Pazar") == 0) VarKoltuk.Gun = Pazar;
	int degilicin, olmasiicin;
	for (yerileri = 0; yerileri < 40; yerileri++) {
		if (otobusKoltuk[yerileri].no == VarKoltuk.no) {
			puts("Koltuk Bos Degildir !!");
			puts("Koltuk > ");
			scanf("%d", &degilicin);
			VarKoltuk.no = degilicin;
		}
		else if (VarKoltuk.no > 39 || VarKoltuk.no < 0) {
			puts("Koltuk no 0-39 arasi olmali");
			puts("Koltuk > ");
			scanf("%d", &olmasiicin);
			VarKoltuk.no = olmasiicin;
		}
		else {
			if (yerileri == VarKoltuk.no) {//koltuk sayisi aliyorum 
				otobusKoltuk[yerileri] = VarKoltuk;
				puts("islem Tamaalanmistir . ");
			}
		}

	
}
	int yerleriKoltuk = 0;
	//Karbarcik(otobusKoltuk,41); sirlama algrotime
	for (yerleriKoltuk = 0; yerleriKoltuk < 41; yerleriKoltuk++) {
		if (otobusKoltuk[yerleriKoltuk].no != 0) {
			FILEP = fopen("C:\\Users\\Aizen\\Desktop\\bus.txt", "a");
			fprintf(FILEP, "\n %d/%c/%d/%s/%s/%d/%d", otobusKoltuk[yerleriKoltuk].no, otobusKoltuk[yerleriKoltuk].DoluYadeBos,
				otobusKoltuk[yerleriKoltuk].Gun, otobusKoltuk[yerleriKoltuk].musteri.isim, otobusKoltuk[yerleriKoltuk].musteri.soyisim,
				otobusKoltuk[yerleriKoltuk].musteri.TcNo, otobusKoltuk[yerleriKoltuk].musteri.cinsiyet);
		}
	}
	fclose(FILEP);
	puts("Yeni koltuk  satisi yapmak ister misiniz ? y/n");
}
	
int KisiArama() {
	int degistirilenDrurumu = 0;
	int l;
	int size=0;
	for( l = 1; l <=40; l++){
		if (otobusKoltuk[l].no==l){//bu kontur ediyorum cunku bilmek istoyrum ki bu orubeste kisileri var mi yok mu diye 
			size = 1;
		}
	}

	if (size!=1){
		puts("Lutfen otobuse kisileri doldurunuz !!!");
		return -1;
	}
	else {
		int tckimlik, koltukleryeri;
		printf("TC giriniz :");
		scanf("%d", &tckimlik);
		for (koltukleryeri = 0; koltukleryeri < 40; koltukleryeri++) {
			if (otobusKoltuk[koltukleryeri].musteri.TcNo == tckimlik) {
				puts("Musteri > ");
				printf("\n");
				printf("        Ad: %s\n", otobusKoltuk[koltukleryeri].musteri.isim);
				printf("\n");
				printf("        Soyad:%s \n", otobusKoltuk[koltukleryeri].musteri.soyisim);
				printf("\n");
				printf("        Tc:%d\n", otobusKoltuk[koltukleryeri].musteri.TcNo);
				if (otobusKoltuk[koltukleryeri].musteri.cinsiyet == K) {
					printf("\n");
					printf("    Cinsiyet : K \n");
				}
				else
				{
					printf("\n");
					printf("        Cinsiyet : E \n");
				}
				puts("Koltuk > ");
				printf("\n");
				printf("         No :%d\n", otobusKoltuk[koltukleryeri].no);

				switch (otobusKoltuk[koltukleryeri].Gun) {//Gunleri sabit oldugun icin bu case kullandim
				case 0:
					printf("        Gun : Pazartesi \n ");
					break;
				case 1:
					printf("         Gun : Sali \n ");
					break;
				case 2:
					printf("         Gun : carsamba \n ");
					break;
				case 3:
					printf("         Gun : Persembe \n ");
					break;
				case 4:
					printf("         Gun : Cuma \n ");
					break;
				case 5:
					printf("         Gun :Cumartesi \n ");
					break;
				case 6:
					printf("         Gun : Pazar \n ");
					break;
				}
				degistirilenDrurumu = 0;
				break;
			}else{
				degistirilenDrurumu = 1;
			}
		}
	}
	if (degistirilenDrurumu == 1) {
		return 1;
	}
	printf("\n");
	printf("yeni kisi arama yapmak ister misiniz? y/n");
}
//void Karbarcik(Koltuk D[], int N) {
//	Koltuk gecici;
//    int p, hareket;
//	for (hareket = 0; hareket < N - 1; hareket++) {
//		for (p = 0; p < N - 1 - hareket; p++) {
//			if (D[p].no > D[p + 1].no) {
//				gecici = D[p];
//				D[p] = D[p + 1];
//				D[p + 1] = gecici;
//			}
//		}
//	}
//}
