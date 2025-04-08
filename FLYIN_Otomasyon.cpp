#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>


// PROGRAMDA KULLANILACAK TANIMLAMALARIN ALAB�LECEKLER� MAKS�MUM DE�ERLER
#define MAX_USERS 50
#define MAX_KULLANICIADI_LENGTH 50
#define MAX_SIFRE_LENGTH 50
#define MAX_ISIM_LENGTH 50
#define MAX_SOYISIM_LENGTH 50
#define MAX_GUN_LENGTH 3
#define MAX_AY_LENGTH 3
#define MAX_YIL_LENGTH 5
#define MAX_KARTISIM_LENGTH 50
#define MAX_KARTNO_LENGTH 20
#define MAX_KARTTARIH_LENGTH 10
#define MAX_KARTCVV_LENGTH 5


// KULLANICIYA BA�LI �� ��E STRUCT YAPISI
struct KartBilgileri 
{
    char kartIsim[MAX_KARTISIM_LENGTH];
    char KartNo[MAX_KARTNO_LENGTH];
    char KartTarih[MAX_KARTTARIH_LENGTH];
    char KartCVV[MAX_KARTCVV_LENGTH];
};

struct Dogumgunu 
{
    char gun[MAX_GUN_LENGTH];
    char ay[MAX_AY_LENGTH];
    char yil[MAX_YIL_LENGTH];
};

struct KullaniciBilgileri
{
    char isim[MAX_ISIM_LENGTH];
    char soyisim[MAX_SOYISIM_LENGTH];
    struct Dogumgunu dogum;
    struct KartBilgileri kart;
};


// KULLANICI STRUCT YAPISI
struct kisi
{
    char kullaniciAdi[MAX_KULLANICIADI_LENGTH];
    char sifre[MAX_SIFRE_LENGTH];
    struct KullaniciBilgileri kullanici;
};

typedef struct CVV
{
    struct kisi* kisiler;
    int kisiSayac;
} CVVdogrula;


// GLOBAL FONKS�YON B�LD�R�MLER�
void kullaniciKaydet(struct kisi kisiler[], int kisiSayac);
int kullaniciYukle(struct kisi kisiler[]);
int kayitOl(struct kisi kisiler[], int kisiSayac);
int girisYap(struct kisi kisiler[], int kisiSayac);
int dogrulaCVV(CVVdogrula* dogrula, const char* cvv);
void kullaniciGoruntule(struct kisi kisiler[], int kisiSayac);
void girisMenu();
void cikisYap();
void anaMenu();
void sayiOyun();
void vrMenu();
void yiyecekMenu();
void pcTip();

// MA�N FONKS�YONU
int main()
{
    setlocale(LC_ALL, "Turkish");
    girisMenu();
    return 0;
}

// KART CVV DO�RULAMA FONKS�YONU
int dogrulaCVV(CVVdogrula* dogrula, const char* cvv) 
{
    for (int i = 0; i < dogrula->kisiSayac; i++) 
	{
        if (strcmp(dogrula->kisiler[i].kullanici.kart.KartCVV, cvv) == 0)
		{
            return 1; // CVV e�le�ti
        }
    }
    return 0; // CVV e�le�medi
}


// KULLANICILARI TXT DOSYASINA KAYDETME FONKS�YONU
void kullaniciKaydet(struct kisi kisiler[], int kisiSayac)
{
    FILE *file = fopen("kisiler.txt", "w");
    if (!file)
    {
        perror("Dosya A��l�rken Bir Hata Olu�tu...");
        return;
    }
    for (int i = 0; i < kisiSayac; i++)
    {
        fprintf(file, "%s %s %s %s %s %s %s %s %s %s %s\n",
            kisiler[i].kullaniciAdi,
            kisiler[i].sifre,
            kisiler[i].kullanici.isim,
            kisiler[i].kullanici.soyisim,
            kisiler[i].kullanici.dogum.gun,
            kisiler[i].kullanici.dogum.ay,
            kisiler[i].kullanici.dogum.yil,
            kisiler[i].kullanici.kart.kartIsim,
            kisiler[i].kullanici.kart.KartNo,
            kisiler[i].kullanici.kart.KartTarih,
            kisiler[i].kullanici.kart.KartCVV);
    }
    fclose(file);
}


// KAYITLI KULLANICILARI TXT DOSYASINDAN OKUMA FONKS�YONU
int kullaniciYukle(struct kisi kisiler[])
{
    FILE *file = fopen("kisiler.txt", "r");
    if (!file)
    {
        perror("Dosya A��l�rken Bir Hata Olu�tu...");
        return 0;
    }
    int kisiSayac = 0;
    while (fscanf(file, "%s %s %s %s %s %s %s %s %s %s %s",
        kisiler[kisiSayac].kullaniciAdi,
        kisiler[kisiSayac].sifre,
        kisiler[kisiSayac].kullanici.isim,
        kisiler[kisiSayac].kullanici.soyisim,
        kisiler[kisiSayac].kullanici.dogum.gun,
        kisiler[kisiSayac].kullanici.dogum.ay,
        kisiler[kisiSayac].kullanici.dogum.yil,
        kisiler[kisiSayac].kullanici.kart.kartIsim,
        kisiler[kisiSayac].kullanici.kart.KartNo,
        kisiler[kisiSayac].kullanici.kart.KartTarih,
        kisiler[kisiSayac].kullanici.kart.KartCVV) == 11)
    {
        kisiSayac++;
        if (kisiSayac >= MAX_USERS) break;
    }
    fclose(file);
    return kisiSayac;
}

// KAYITLI KULLANICILARIN B�LG�LER�N� G�R�NT�LEYEN SAYFA
void kullaniciGoruntule(struct kisi kisiler[], int kisiSayac)
{
	kullaniciStart:
    if (kisiSayac == 0)
    {
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                          ::");
        printf("\n\t\t\t                       ::   Kay�tl� Kullan�c� Bilgisi Bulunamad�   ::");
        printf("\n\t\t\t                       ::                                          ::");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::\n\n");
        return;
    }

    for (int i = 0; i < kisiSayac; i++)
    {
    	system("color 3");
    	system("cls");
    	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                          ::");
    	printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     ::");
    	printf("\n\t\t\t                       ::     @                              @     ::");
    	printf("\n\t\t\t                       ::     @     Kay�tl� Kullan�c�lar     @     ::");
    	printf("\n\t\t\t                       ::     @  A�a��da G�r�nt�lenmektedir  @     ::");
    	printf("\n\t\t\t                       ::     @                              @     ::");
    	printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     ::");
    	printf("\n\t\t\t                       ::                                          ::");
    	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n");
        printf("\n\t\t\t			Kullan�c� Ad�: %s", kisiler[i].kullaniciAdi);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			�ifre: %s", kisiler[i].sifre);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			�sim: %s", kisiler[i].kullanici.isim);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Soyisim: %s", kisiler[i].kullanici.soyisim);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Do�um G�n�: %s/%s/%s", kisiler[i].kullanici.dogum.gun, kisiler[i].kullanici.dogum.ay, kisiler[i].kullanici.dogum.yil);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Kart �smi: %s", kisiler[i].kullanici.kart.kartIsim);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Kart Numaras�: %s", kisiler[i].kullanici.kart.KartNo);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Kart Tarihi: %s", kisiler[i].kullanici.kart.KartTarih);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Kart CVV: %s", kisiler[i].kullanici.kart.KartCVV);
        printf("\n");
        printf("\n\t\t\t                        ********************************************\n");
        printf("\n");
    }
    
    printf("\n\t\t\t         :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    printf("\n\t\t\t         ::                                                                         ::");
    printf("\n\t\t\t         ::   Geri D�nmek ��in 1'e Listeyi Tekrar G�r�nt�lemek ��in 2'ye Bas�n�z.   ::");
    printf("\n\t\t\t         ::                                                                         ::");
    printf("\n\t\t\t         :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
    printf("\n\t\t\t           SE��M�N�Z :");
    int kullaniciSecim;
    scanf("\n\t\t\t%d", &kullaniciSecim);
    if (kullaniciSecim == 1)
    {
    	system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                       ::");
        printf("\n\t\t\t                       ::    Ana Men�ye Y�nlendiriliyorsunuz    ::");
        printf("\n\t\t\t                       ::                                       ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
        Sleep(2000);
        anaMenu();
    }
    else if (kullaniciSecim == 2)
    {
    	system("cls");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                            ::");
        printf("\n\t\t\t                       ::    Listenin Ba��na Y�nlendiriliyorsunuz    ::");
        printf("\n\t\t\t                       ::                                            ::");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::::");
        Sleep(2000);
        goto kullaniciStart;
    }
    else
    {
        system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                       ::");
        printf("\n\t\t\t                       ::      Ge�ersiz Bir ��lem Yapt�n�z      ::");
        printf("\n\t\t\t                       ::    Ana Men�ye Y�nlendiriliyorsunuz    ::");
        printf("\n\t\t\t                       ::                                       ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
        Sleep(3000);
        goto kullaniciStart;
    }
}


// KULLANICI KAYIT OLMA SAYFASI
int kayitOl(struct kisi kisiler[], int kisiSayac)
{
    int kayitSecim;
    if (kisiSayac >= MAX_USERS)
	{
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                          ::");
        printf("\n\t\t\t                       ::   Maksimum kullan�c� say�s�na ula��ld�   ::");
        printf("\n\t\t\t                       ::                                          ::");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::\n\n");
        return kisiSayac;
    } 
	else 
	{
        struct kisi newUser;
        system("cls");
        system("color 3");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                 ::");
        printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
        printf("\n\t\t\t                       ::     @                     @     ::");
        printf("\n\t\t\t                       ::     @        L�TFEN       @     ::");
        printf("\n\t\t\t                       ::     @       KAYDINIZI     @     ::");
        printf("\n\t\t\t                       ::     @        YAPINIZ      @     ::");
        printf("\n\t\t\t                       ::     @                     @     ::");
        printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
        printf("\n\t\t\t                       ::                                 ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       �sminizi Giriniz : ");
        scanf("%s", newUser.kullanici.isim);
        printf("\n\t\t\t                       Soyisminizi Giriniz : ");
        scanf("%s", newUser.kullanici.soyisim);
        system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       ::  L�tfen Do�um G�n� B�lgilerinizi Giriniz  ::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       Do�um Tarihinizin G�n�n� Giriniz : ");
        scanf("%s", newUser.kullanici.dogum.gun);
        printf("\n\t\t\t                       Do�um Tarihinizin Ay�n� Giriniz : ");
        scanf("%s", newUser.kullanici.dogum.ay);
        printf("\n\t\t\t                       Do�um Tarihinizin Y�l�n� Giriniz : ");
        scanf("%s", newUser.kullanici.dogum.yil);
        system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                     ::");
        printf("\n\t\t\t                       ::  L�tfen Kart Bilgilerinizi Giriniz  ::");
        printf("\n\t\t\t                       ::                                     ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       Kart Sahibinin �smini Giriniz : ");
        scanf("%s", newUser.kullanici.kart.kartIsim);
        printf("\n\t\t\t                       Kart Numaran�z� Giriniz : ");
        scanf("%s", newUser.kullanici.kart.KartNo);
        printf("\n\t\t\t                       Kart Son Kullanma Tarihini Giriniz (MM/YY): ");
        scanf("%s", newUser.kullanici.kart.KartTarih);
        printf("\n\t\t\t                       Kart�n�z�n Arka Y�z�ndeki CVV Numaras�n� Giriniz : ");
        scanf("%s", newUser.kullanici.kart.KartCVV);
    	sifreHata:
        system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       ::  Kullan�c� Ad� ve �ifrenizi Belirleyiniz  ::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       Kullan�c� Ad� Giriniz : ");
        scanf("%s", newUser.kullaniciAdi);
        printf("\n\t\t\t                       �ifrenizi Giriniz : ");
        scanf("%s", newUser.sifre);
        char sifreTekrar[MAX_SIFRE_LENGTH];
        printf("\n\t\t\t                       �ifrenizi Tekrar Giriniz : ");
        scanf("%s", sifreTekrar);
        if (strcmp(newUser.sifre, sifreTekrar) != 0) 
		{
			system("cls");
			printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::::::::");
        	printf("\n\t\t\t                       ::                                                 ::");
        	printf("\n\t\t\t                       ::  �ifreler e�le�miyor, l�tfen tekrar deneyiniz.  ::");
        	printf("\n\t\t\t                       ::                                                 ::");
        	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
        	Sleep(2000);
            goto sifreHata;
        }
        kisiler[kisiSayac++] = newUser;
        kullaniciKaydet(kisiler, kisiSayac);
        kayitStart:
        system("cls");
    	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
   		printf("\n\t\t\t                       ::                                      ::");
   		printf("\n\t\t\t                       ::  Kayd�n�z Ba�ar�yla Olu�turulmu�tur  ::");
   		printf("\n\t\t\t                       ::                                      ::");
   		printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::\n\n");
   		Sleep(2000);
    }
    system("cls");
    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
   	printf("\n\t\t\t                       ::     Giri� Men�s� ��in 1'e Bas�n�z    ::");
   	printf("\n\t\t\t                       ::  Ana Men�ye D�nmek ��in 2'ye Bas�n�z ::");
   	printf("\n\t\t\t                       ::     ��k�� Yapmak ��in 3'e Bas�n�z    ::");
    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::\n\n");
    printf("\n\t\t\t           SE��M�N�Z :");
    scanf("\n\t\t\t%d", &kayitSecim);
    if (kayitSecim == 1)
	{
		system("cls");
		printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                           ::");
    	printf("\n\t\t\t                       ::    Giri� Men�s�ne Y�nlendiriliyorsunuz    ::");
    	printf("\n\t\t\t                       ::                                           ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::");
    	Sleep(2000);
        girisYap(kisiler, kisiSayac);
    } 
	else if (kayitSecim == 2)
	{
		system("cls");
		printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       ::    Ana Men�ye Y�nlendiriliyorsunuz    ::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
    	Sleep(2000);
        girisMenu();
    }
    else if (kayitSecim == 3)
	{
		cikisYap();
	}
	else
	{
		system("cls");
		printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                         ::");
    	printf("\n\t\t\t                       ::   �zg�n�z Ge�ersiz Bir ��lem Yapt�n�z   ::");
    	printf("\n\t\t\t                       ::                                         ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::\n\n");
    	Sleep(3000);
    	goto kayitStart;
	}
    return kisiSayac;
}


// KULLANICI G�R�� YAPMA SAYFASI
int girisYap(struct kisi kisiler[], int kisiSayac) 
{
	girisYap:
    char kullaniciAdi[MAX_KULLANICIADI_LENGTH];
    char sifre[MAX_SIFRE_LENGTH];
    int loginSecim;
    system("color 3");
    system("cls");
    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @        L�TFEN       @     ::");
    printf("\n\t\t\t                       ::     @        G�R��        @     ::");
    printf("\n\t\t\t                       ::     @        YAPIN        @     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::\n\n");
    printf("\n\t\t\t                       Kullan�c� Ad�n�z� Giriniz : ");
    scanf("%s", kullaniciAdi);
    printf("\n\t\t\t                       �ifrenizi Giriniz : ");
    scanf("%s", sifre);
    for (int i = 0; i < kisiSayac; i++) 
	{
        if (strcmp(kisiler[i].kullaniciAdi, kullaniciAdi) == 0 && strcmp(kisiler[i].sifre, sifre) == 0) 
		{
			system("cls");
            printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                                      ::");
    		printf("\n\t\t\t                       ::       Giri� ��leminiz Ba�ar�l�       ::");
    		printf("\n\t\t\t                       ::                                      ::");
    		printf("\n\t\t\t                       ::   Ana Men�ye Y�nlendiriliyorsunuz    ::");
    		printf("\n\t\t\t                       ::                                      ::");
    		printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
    		Sleep(2000);
            anaMenu();
        }
		else
			{
            system("cls");
   			printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
   			printf("\n\t\t\t                       ::                                         ::");
   			printf("\n\t\t\t                       ::     Hatal� Kullan�c� Ad� Veya �ifre     ::");
   			printf("\n\t\t\t                       ::                                         ::");
   			printf("\n\t\t\t                       ::   Giri� Men�s�ne Y�nlendiriliyorsunuz   ::");
   			printf("\n\t\t\t                       ::                                         ::");
   			printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
   			Sleep(2000);
   			goto girisYap;	
            }
            return 1;
    }
    return 0;
}


// PROGRAM BA�LANGI� SAYFASI
void girisMenu() 
{
    int kisiSayac = 0;
    struct kisi kisiler[MAX_USERS];
    kisiSayac = kullaniciYukle(kisiler);
    int secim;
    system("color 3");
    system("cls");
    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @        FLYIN        @     ::");
    printf("\n\t\t\t                       ::     @  INTERNET KAFESINE  @     ::");
    printf("\n\t\t\t                       ::     @     HOSGELDINIZ     @     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
    printf("\n");
    printf("\n\t\t\t            *** L�tfen A�a��dan Yapmak �stedi�iniz ��lemi Se�iniz ***\n\n");
    printf("\n\t\t\t           :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::     * 1-> Kay�t Olmak ��in 1'i Se�iniz.               ::\n");
    printf("\n\t\t\t           ::-------------------------------------------------------::\n");
    printf("\n\t\t\t           ::     * 2-> Giri� Yapmak ��in 2'yi Se�iniz.             ::\n");
    printf("\n\t\t\t           ::-------------------------------------------------------::\n");
    printf("\n\t\t\t           ::     * 3-> ��k�� Yapmak �cin 3'i Se�iniz.              ::\n");
    printf("\n\t\t\t           :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");
    printf("\n\t\t\t           SE��M�N�Z :");
    scanf("\n\t\t\t%d", &secim);
    switch (secim) 
	{
    case 1:
        kisiSayac = kayitOl(kisiler, kisiSayac);
        break;
    case 2:
    	girisYap(kisiler, kisiSayac);
        break;
    case 3:
        cikisYap();
        break;
    default:
        system("cls");
		printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       ::      Ge�ersiz Bir ��lem Yapt�n�z      ::");
    	printf("\n\t\t\t                       ::    Ana Men�ye Y�nlendiriliyorsunuz    ::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
		Sleep(3000);
        girisMenu();
        break;
    }
}


// ANA MEN� SAYFASI
void anaMenu()
{
	struct kisi kisiler[MAX_USERS];
    int kisiSayac = kullaniciYukle(kisiler);
    int menuSecim;
    system("cls");
	system("color 3");
    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::");
    printf("\n\t\t\t                       ::                                  ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::     @                      @     ::");
    printf("\n\t\t\t                       ::     @         FLYIN        @     ::");
    printf("\n\t\t\t                       ::     @   INTERNET KAFESINE  @     ::");
    printf("\n\t\t\t                       ::     @      HOSGELDINIZ     @     ::");
    printf("\n\t\t\t                       ::     @                      @     ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::                                  ::");
    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::\n\n");
    printf("\n\t\t\t              *** L�tfen A�a��dan Yapmak �stedi�iniz ��lemi Se�iniz ***\n\n");
    printf("\n\t\t\t          ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t          ::    * 1-> Bilgisayar Kiralama ��lemleri ��in 1'i Se�iniz.           ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 2-> Yiyecek Men�s�n� G�rmek ��in 2'yi Se�iniz.                ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 3-> VR G�zl�k Kiralama ��lemi ��in 3'i Se�iniz.               ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 4-> Say� Tahmin Etme Oyunu ��in 4'� Se�iniz.                  ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 5-> Kay�tl� Kullan�c�lar� G�r�nt�lemek ��in 5'i Se�iniz.      ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 6-> ��k�� Yapmak ��in 6'y� Se�iniz.                           ::\n");
    printf("\n\t\t\t          ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");
    printf("\n\t\t\t           SE��M�N�Z :");
    scanf("%d", &menuSecim);
    switch (menuSecim)
	{
    case 1:
        pcTip();
        break;
    case 2:
    	yiyecekMenu();
        break;
    case 3:
        vrMenu();
        break;
    case 4:
    	sayiOyun();
        break;
    case 5:
    	kullaniciGoruntule(kisiler, kisiSayac);
        break;
    case 6:
       	cikisYap();
       	break;
    default:
        system("cls");
		printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       ::      Ge�ersiz Bir ��lem Yapt�n�z      ::");
    	printf("\n\t\t\t                       ::    Ana Men�ye Y�nlendiriliyorsunuz    ::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
    	Sleep(3000);
        anaMenu();
        break;
    }
}


// SAYI TAHM�N ETME OYUNU 
void sayiOyun()
{
    system("cls");
	system("color 3");
	int sayi, tahmin, donus;
  	srand ( time(NULL) );
  	sayi = rand() % 10 + 1;
  	int deneme = 0;
  	printf("\n\t\t\t           :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           :: ************ SAYI TAHM�N ETME OYUNUNA HO�GELD�N�Z *********** ::\n");
    printf("\n\t\t\t           ::---------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::           1 �le 10 Aras�nda Bir Say�y� Do�ru Tahmin           ::\n");
    printf("\n\t\t\t           ::---------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::       Ederseniz Bizden 1 Saatlik Bir Kupon Kazanacaks�n�z     ::\n");
    printf("\n\t\t\t           ::***************************************************************::\n");
    printf("\n\t\t\t           ::***************************************************************::\n");
    printf("\n\t\t\t           ::                Toplam 3 Hakk�n�z Bulunmaktad�r                ::\n");
    printf("\n\t\t\t           ::---------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::                       �yi �anslar Dileriz                     ::\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");

  	for (deneme = 0; deneme < 3 ; deneme++) 
  	{
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                        ::");
   		printf("\n\t\t\t                       ::   1 �le 10 Aras�nda Bir Say� Giriniz   ::");
    	printf("\n\t\t\t                       ::                                        ::");
    	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::\n\n");
    	printf("\n\t\t\t                       TAHM�N�N�Z :");
        scanf("\n\t\t\t%d", &tahmin);

      if(tahmin == sayi)
	  	{
	  		start:
            system("cls");
        	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                            ::");
   			printf("\n\t\t\t                       ::   Tebrikler! Kazand�n�z!   ::");
    		printf("\n\t\t\t                       ::                            ::");
    		printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::\n\n");
    		printf("\n\t\t\t        :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t        ::   Tekrar oynamak i�in 1'e Ana men�ye D�nmek ��in 2'ye Bas�n�z   ::");
            printf("\n\t\t\t        :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
    		printf("\n\t\t\t        SE��M�N�Z :");
    		scanf("\n\t\t\t%d", &donus);
    		if(donus==1)
			{
				sayiOyun();
			}
			else if(donus==2)
			{
				anaMenu();
			}
			else
			{
				system("cls");
				printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
    			printf("\n\t\t\t                       ::                                 ::");
   				printf("\n\t\t\t                       ::   Ge�ersiz Bir ��lem Yapt�n�z   ::");
    			printf("\n\t\t\t                       ::                                 ::");
    			printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
    			Sleep(2000);
    			goto start;
			}
      	}
      	else if(tahmin > sayi)
	  	{
	  		system("cls");
        	printf("\n\t\t\t                              :::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                              ::                           ::");
   			printf("\n\t\t\t                              ::   Tahmininiz �ok Y�ksek   ::");
    		printf("\n\t\t\t                              ::                           ::");
    		printf("\n\t\t\t                              :::::::::::::::::::::::::::::::\n");
		}
        else if(tahmin < sayi)
		{
			system("cls");
			printf("\n\t\t\t                              ::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                              ::                          ::");
   			printf("\n\t\t\t                              ::   Tahmininiz �ok D���k   ::");
    		printf("\n\t\t\t                              ::                          ::");
    		printf("\n\t\t\t                              ::::::::::::::::::::::::::::::\n");
        }
  	}
  	        system("cls");
        	printf("\n\t\t\t                       :::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                         ::");
   			printf("\n\t\t\t                       ::   �zg�n�z Kaybettiniz   ::");
    		printf("\n\t\t\t                       ::                         ::");
    		printf("\n\t\t\t                       :::::::::::::::::::::::::::::\n\n");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                         ::");
   			printf("\n\t\t\t                       ::   Do�ru Say� : %d        ::",sayi);
    		printf("\n\t\t\t                       ::                         ::");
    		printf("\n\t\t\t                       :::::::::::::::::::::::::::::\n\n");
            Sleep(2000);
            anaMenu();
}


// VR G�ZL�K T�PLER�N� G�R�NT�LEME VE K�RALAMA ��LEMLER� MEN�S�  
void vrMenu()
{
   	system("cls");
	system("color 3");
	struct kisi kisiler[MAX_USERS];
    int kisiSayac = kullaniciYukle(kisiler);
    CVVdogrula dogrula = { kisiler, kisiSayac };
	int secim, vrSecim, sure;
	int htc=100, samsung=190, meta=170, hp=120, oculus=220, pico=150, total = 0;
	printf("\n\t\t\t                *** VR G�zl�kler A�a��da Listelenmektedir ***\n\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::          NO          MARKA            F�YAT          ::\n");
    printf("\n\t\t\t           ::------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          1       HTC Vive Cosmos      100 TL         ::\n");
    printf("\n\t\t\t           ::------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          2       Samsung Gear VR      190 TL         ::\n");
    printf("\n\t\t\t           ::------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          3       Meta Quest 2         170 TL         ::\n");
    printf("\n\t\t\t           ::------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          4       HP Reverb G2         120 TL         ::\n");
    printf("\n\t\t\t           ::------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          5       OCULUS Meta          220 TL         ::\n");
    printf("\n\t\t\t           ::------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          6       Pico G3 3DoF         150 TL         ::\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t                       *** �cretlerimiz Saatliktir ***            \n\n");
    printf("\n\t\t\t           L�tfen Kiralamak �stedi�iniz VR G�zl��� Se�iniz :");
    scanf("\n\t\t\t%d", &secim);
    if (secim > 6)
	{
        system("clear");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                             ::");
    	printf("\n\t\t\t                       ::   �zg�n�z Arad���n�z VR G�zl��� Bulamad�k   ::");
    	printf("\n\t\t\t                       ::                                             ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::::");
        sleep(3);
        vrMenu();
    }
	else
	{
        printf("\n\t\t\t           VR G�zl��� Ka� Saat Kiralamak �stiyorsunuz      :");
        scanf("%d", &sure);
        switch (secim)
		{
            case 1: total = htc * sure; break;
            case 2: total = samsung * sure; break;
            case 3: total = meta * sure; break;
            case 4: total = hp * sure; break;
            case 5: total = oculus * sure; break;
            case 6: total = pico * sure; break;
        }
        printf("\n\t\t\t           L�tfen Kart CVV Numaran�z� Giriniz: ");
        char cvvInput[MAX_KARTCVV_LENGTH];
        scanf("%s", cvvInput);
        if (dogrulaCVV(&dogrula, cvvInput))
		{
            while (1)
			{
                system("cls");
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                printf("\n\t\t\t       ::   Se�ti�iniz VR G�zl�k ��in Toplam �deyece�iniz �cret %d TL'dir  ::", total);
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
                printf("\n\t\t\t              ********************************************************");
                printf("\n\t\t\t              *   Onayl�yorsan�z 1'e Onaylam�yorsan�z 2'ye Bas�n�z   *");
                printf("\n\t\t\t              ********************************************************\n\n");
                printf("\n\t\t\t       SE��M�N�Z :");
                scanf("%d", &vrSecim);
                if (vrSecim == 1)
				{
                    system("cls");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::            ��leminiz Ba�ar�yla Ger�ekle�mi�tir              ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::         Kalaca��n�z S�re Boyunca Kafemizde Bulunan          ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::    Yiyecek Ve ��ecek Men�m�zede Bakman�z� Tavsiye Ederiz    ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    sleep(4);
                    anaMenu();
                    break;
                } 
				else if (vrSecim == 2)
				{
                    system("cls");
                    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t                       ::                                      ::");
                    printf("\n\t\t\t                       ::     ��leminiz �ptal Edilmi�tir...    ::");
                    printf("\n\t\t\t                       ::                                      ::");
                    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
                    sleep(3);
                    anaMenu();
                    break;
                }
				else
				{
                    system("cls");
                    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t                       ::                                         ::");
                    printf("\n\t\t\t                       ::   �zg�n�z Ge�ersiz Bir ��lem Yapt�n�z   ::");
                    printf("\n\t\t\t                       ::                                         ::");
                    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
                    sleep(3);
                    vrMenu();
                }
            }
        }
		else
		{
            system("cls");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       ::      Ge�ersiz CVV Numaras�      ::");
            printf("\n\t\t\t                       ::     L�tfen Tekrar Deneyiniz     ::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            sleep(3);
            vrMenu();
        }
    }
}


// Y�YECEK VE ��ECEK T�PLER�N� G�R�NT�LEME VE SATIN AL ��LEMLER� MEN�S� 
void yiyecekMenu()
{
    system("cls");
	system("color 3");
	struct kisi kisiler[MAX_USERS];
    int kisiSayac = kullaniciYukle(kisiler);
    CVVdogrula dogrula = { kisiler, kisiSayac };
	int total=0, hamburger= 75, patates=30, patso=25, soguk=60, sosisli=85, islak=55, su=20;
	int secim, yiyecekSecim, fiyat;
	printf("\n\t\t\t                    *** Yiyecek Men�leri A�a��da Listelenmektedir ***\n\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::          NO               MEN�LER               F�YAT          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          1             Hamburger & Kola          75 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          2             Patates & Kola            30 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          3             Patso & Ayran             25 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          4             So�uk Sandvi� & Fanta     60 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          5             Sosisli Sandvi� & Kola    85 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          6             Islak Hamburger & Kola    55 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          7             Su                        20 TL         ::\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t                             *** �cretlerimize KDV Dahildir ***              \n\n");
	printf("\n\t\t\t           L�tfen Sat�n Almak �stedi�iniz Men�y� Se�iniz :");
    scanf("\n\t\t\t%d", &secim);
    if (secim > 6)
	{
        system("clear");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                         ::");
        printf("\n\t\t\t                       ::   �zg�n�z Arad���n�z Men�y� Bulamad�k   ::");
        printf("\n\t\t\t                       ::                                         ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
        sleep(3);
        pcTip();
    }
	else
	{
        switch (secim)
		{
            case 1: total = hamburger; break;
            case 2: total = patates; break;
            case 3: total = patso; break;
            case 4: total = soguk; break;
            case 5: total = sosisli; break;
            case 6: total = islak;
            case 7: total = su; break;
        }
        printf("\n\t\t\t           L�tfen Kart CVV Numaran�z� Giriniz: ");
        char cvvInput[MAX_KARTCVV_LENGTH];
        scanf("%s", cvvInput);
        if (dogrulaCVV(&dogrula, cvvInput))
		{
            while (1)
			{
                 system("cls");
				printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    			printf("\n\t\t\t       ::   Se�ti�iniz Men� ��in Toplam �deyece�iniz �cret %d TL'dir   ::", total);
    			printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
    			printf("\n\t\t\t          ***********************************************************");
    			printf("\n\t\t\t          *   Onayl�yorsan�z 1'e Onaylam�yorsan�z 2'ye Bas�n�z      *");
    			printf("\n\t\t\t          ***********************************************************\n\n");
    			printf("\n\t\t\t       SE��M�N�Z :");
                scanf("%d", &yiyecekSecim);
                if (yiyecekSecim == 1)
				{
                    system("cls");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    				printf("\n\t\t\t             ::                                                             ::");
    				printf("\n\t\t\t             ::            ��leminiz Ba�ar�yla Ger�ekle�mi�tir              ::");
    				printf("\n\t\t\t             ::                                                             ::");
    				printf("\n\t\t\t             ::                       Afiyet Olsun                          ::");
    				printf("\n\t\t\t             ::                                                             ::");
    				printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    sleep(4);
                    anaMenu();
                    break;
                } 
				else if (yiyecekSecim == 2)
				{
                    system("cls");
                    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t                       ::                                      ::");
                    printf("\n\t\t\t                       ::     ��leminiz �ptal Edilmi�tir...    ::");
                    printf("\n\t\t\t                       ::                                      ::");
                    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
                    sleep(3);
                    anaMenu();
                    break;
                }
				else
				{
                    system("cls");
                    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t                       ::                                         ::");
                    printf("\n\t\t\t                       ::   �zg�n�z Ge�ersiz Bir ��lem Yapt�n�z   ::");
                    printf("\n\t\t\t                       ::                                         ::");
                    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
                    sleep(3);
                    yiyecekMenu();
                }
            }
        }
		else
		{
            system("cls");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       ::      Ge�ersiz CVV Numaras�      ::");
            printf("\n\t\t\t                       ::     L�tfen Tekrar Deneyiniz     ::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            sleep(3);
        }
    }
}


// B�LG�SAYAR T�PLER�N� G�R�NT�LEME VE K�RALAMA ��LEMLER� MEN�S� 
void pcTip()
{
	system("cls");
	system("color 3");
    struct kisi kisiler[MAX_USERS];
    int kisiSayac = kullaniciYukle(kisiler);
    CVVdogrula dogrula = { kisiler, kisiSayac };
    int secim, pcSecim, sure;
    int msi = 50, acer = 30, asus = 60, apple = 90, hp = 40, lenovo = 70, total = 0;
    printf("\n\t\t\t                *** Bilgisayarlar A�a��da Listelenmektedir ***\n\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::          NO          MARKA          F�YAT          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------::\n");
    printf("\n\t\t\t           ::          1            MS�           50 TL          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------::\n");
    printf("\n\t\t\t           ::          2            ACER          30 TL          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------::\n");
    printf("\n\t\t\t           ::          3            ASUS          60 TL          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------::\n");
    printf("\n\t\t\t           ::          4            APPLE         90 TL          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------::\n");
    printf("\n\t\t\t           ::          5            HP            40 TL          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------::\n");
    printf("\n\t\t\t           ::          6            LENOVO        70 TL          ::\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t                       *** �cretlerimiz Saatliktir ***            \n\n");
    printf("\n\t\t\t           L�tfen Kiralamak �stedi�iniz Bilgisayar� Se�iniz :");
    scanf("%d", &secim);
    if (secim > 6)
	{
        system("clear");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                              ::");
        printf("\n\t\t\t                       ::   �zg�n�z Arad���n�z Bilgisayar� Bulamad�k   ::");
        printf("\n\t\t\t                       ::                                              ::");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::::::");
        sleep(3);
        pcTip();
    }
	else
	{
        printf("\n\t\t\t           Bilgisayar� Ka� Saat Kiralamak �stiyorsunuz      :");
        scanf("%d", &sure);
        switch (secim)
		{
            case 1: total = msi * sure; break;
            case 2: total = acer * sure; break;
            case 3: total = asus * sure; break;
            case 4: total = apple * sure; break;
            case 5: total = hp * sure; break;
            case 6: total = lenovo * sure; break;
        }

        printf("\n\t\t\t           L�tfen Kart CVV Numaran�z� Giriniz: ");
        char cvvInput[MAX_KARTCVV_LENGTH];
        scanf("%s", cvvInput);
        if (dogrulaCVV(&dogrula, cvvInput))
		{
            while (1)
			{
                system("cls");
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                printf("\n\t\t\t       ::   Se�ti�iniz Bilgisayar ��in Toplam �deyece�iniz �cret %d TL'dir   ::", total);
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
                printf("\n\t\t\t             ***********************************************************");
                printf("\n\t\t\t             *   Onayl�yorsan�z 1'e Onaylam�yorsan�z 2'ye Bas�n�z      *");
                printf("\n\t\t\t             ***********************************************************\n\n");
                printf("\n\t\t\t       SE��M�N�Z :");
                scanf("%d", &pcSecim);
                if (pcSecim == 1)
				{
                    system("cls");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::            ��leminiz Ba�ar�yla Ger�ekle�mi�tir              ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::         Kalaca��n�z S�re Boyunca Kafemizde Bulunan          ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::    Yiyecek Ve ��ecek Men�m�zede Bakman�z� Tavsiye Ederiz    ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    sleep(4);
                    anaMenu();
                    break;
                } 
				else if (pcSecim == 2)
				{
                    system("cls");
                    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t                       ::                                      ::");
                    printf("\n\t\t\t                       ::     ��leminiz �ptal Edilmi�tir...    ::");
                    printf("\n\t\t\t                       ::                                      ::");
                    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
                    sleep(3);
                    anaMenu();
                    break;
                }
				else
				{
                    system("cls");
                    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t                       ::                                         ::");
                    printf("\n\t\t\t                       ::   �zg�n�z Ge�ersiz Bir ��lem Yapt�n�z   ::");
                    printf("\n\t\t\t                       ::                                         ::");
                    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
                    sleep(3);
                    pcTip();
                }
            }
        }
		else
		{
            system("cls");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       ::      Ge�ersiz CVV Numaras�      ::");
            printf("\n\t\t\t                       ::     L�tfen Tekrar Deneyiniz     ::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            sleep(3);
            pcTip();
        }
    }
}


// �IKI� SAYFASI  
void cikisYap()
{
    system("cls");
	system("color 4");
	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @         �Y�         @     ::");
    printf("\n\t\t\t                       ::     @        G�NLER       @     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::\n\n");
    exit(0);
}
