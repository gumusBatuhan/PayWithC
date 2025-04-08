#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>


// PROGRAMDA KULLANILACAK TANIMLAMALARIN ALABÝLECEKLERÝ MAKSÝMUM DEÐERLER
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


// KULLANICIYA BAÐLI ÝÇ ÝÇE STRUCT YAPISI
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


// GLOBAL FONKSÝYON BÝLDÝRÝMLERÝ
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

// MAÝN FONKSÝYONU
int main()
{
    setlocale(LC_ALL, "Turkish");
    girisMenu();
    return 0;
}

// KART CVV DOÐRULAMA FONKSÝYONU
int dogrulaCVV(CVVdogrula* dogrula, const char* cvv) 
{
    for (int i = 0; i < dogrula->kisiSayac; i++) 
	{
        if (strcmp(dogrula->kisiler[i].kullanici.kart.KartCVV, cvv) == 0)
		{
            return 1; // CVV eþleþti
        }
    }
    return 0; // CVV eþleþmedi
}


// KULLANICILARI TXT DOSYASINA KAYDETME FONKSÝYONU
void kullaniciKaydet(struct kisi kisiler[], int kisiSayac)
{
    FILE *file = fopen("kisiler.txt", "w");
    if (!file)
    {
        perror("Dosya Açýlýrken Bir Hata Oluþtu...");
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


// KAYITLI KULLANICILARI TXT DOSYASINDAN OKUMA FONKSÝYONU
int kullaniciYukle(struct kisi kisiler[])
{
    FILE *file = fopen("kisiler.txt", "r");
    if (!file)
    {
        perror("Dosya Açýlýrken Bir Hata Oluþtu...");
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

// KAYITLI KULLANICILARIN BÝLGÝLERÝNÝ GÖRÜNTÜLEYEN SAYFA
void kullaniciGoruntule(struct kisi kisiler[], int kisiSayac)
{
	kullaniciStart:
    if (kisiSayac == 0)
    {
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                          ::");
        printf("\n\t\t\t                       ::   Kayýtlý Kullanýcý Bilgisi Bulunamadý   ::");
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
    	printf("\n\t\t\t                       ::     @     Kayýtlý Kullanýcýlar     @     ::");
    	printf("\n\t\t\t                       ::     @  Aþaðýda Görüntülenmektedir  @     ::");
    	printf("\n\t\t\t                       ::     @                              @     ::");
    	printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     ::");
    	printf("\n\t\t\t                       ::                                          ::");
    	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n");
        printf("\n\t\t\t			Kullanýcý Adý: %s", kisiler[i].kullaniciAdi);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Þifre: %s", kisiler[i].sifre);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Ýsim: %s", kisiler[i].kullanici.isim);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Soyisim: %s", kisiler[i].kullanici.soyisim);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Doðum Günü: %s/%s/%s", kisiler[i].kullanici.dogum.gun, kisiler[i].kullanici.dogum.ay, kisiler[i].kullanici.dogum.yil);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Kart Ýsmi: %s", kisiler[i].kullanici.kart.kartIsim);
        printf("\n\t\t\t			--------------------------------------------");
        printf("\n\t\t\t			Kart Numarasý: %s", kisiler[i].kullanici.kart.KartNo);
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
    printf("\n\t\t\t         ::   Geri Dönmek Ýçin 1'e Listeyi Tekrar Görüntülemek Ýçin 2'ye Basýnýz.   ::");
    printf("\n\t\t\t         ::                                                                         ::");
    printf("\n\t\t\t         :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
    printf("\n\t\t\t           SEÇÝMÝNÝZ :");
    int kullaniciSecim;
    scanf("\n\t\t\t%d", &kullaniciSecim);
    if (kullaniciSecim == 1)
    {
    	system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                       ::");
        printf("\n\t\t\t                       ::    Ana Menüye Yönlendiriliyorsunuz    ::");
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
        printf("\n\t\t\t                       ::    Listenin Baþýna Yönlendiriliyorsunuz    ::");
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
        printf("\n\t\t\t                       ::      Geçersiz Bir Ýþlem Yaptýnýz      ::");
        printf("\n\t\t\t                       ::    Ana Menüye Yönlendiriliyorsunuz    ::");
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
        printf("\n\t\t\t                       ::   Maksimum kullanýcý sayýsýna ulaþýldý   ::");
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
        printf("\n\t\t\t                       ::     @        LÜTFEN       @     ::");
        printf("\n\t\t\t                       ::     @       KAYDINIZI     @     ::");
        printf("\n\t\t\t                       ::     @        YAPINIZ      @     ::");
        printf("\n\t\t\t                       ::     @                     @     ::");
        printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
        printf("\n\t\t\t                       ::                                 ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       Ýsminizi Giriniz : ");
        scanf("%s", newUser.kullanici.isim);
        printf("\n\t\t\t                       Soyisminizi Giriniz : ");
        scanf("%s", newUser.kullanici.soyisim);
        system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       ::  Lütfen Doðum Günü BÝlgilerinizi Giriniz  ::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       Doðum Tarihinizin Gününü Giriniz : ");
        scanf("%s", newUser.kullanici.dogum.gun);
        printf("\n\t\t\t                       Doðum Tarihinizin Ayýný Giriniz : ");
        scanf("%s", newUser.kullanici.dogum.ay);
        printf("\n\t\t\t                       Doðum Tarihinizin Yýlýný Giriniz : ");
        scanf("%s", newUser.kullanici.dogum.yil);
        system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                     ::");
        printf("\n\t\t\t                       ::  Lütfen Kart Bilgilerinizi Giriniz  ::");
        printf("\n\t\t\t                       ::                                     ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       Kart Sahibinin Ýsmini Giriniz : ");
        scanf("%s", newUser.kullanici.kart.kartIsim);
        printf("\n\t\t\t                       Kart Numaranýzý Giriniz : ");
        scanf("%s", newUser.kullanici.kart.KartNo);
        printf("\n\t\t\t                       Kart Son Kullanma Tarihini Giriniz (MM/YY): ");
        scanf("%s", newUser.kullanici.kart.KartTarih);
        printf("\n\t\t\t                       Kartýnýzýn Arka Yüzündeki CVV Numarasýný Giriniz : ");
        scanf("%s", newUser.kullanici.kart.KartCVV);
    	sifreHata:
        system("cls");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       ::  Kullanýcý Adý ve Þifrenizi Belirleyiniz  ::");
        printf("\n\t\t\t                       ::                                           ::");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::\n\n");
        printf("\n\t\t\t                       Kullanýcý Adý Giriniz : ");
        scanf("%s", newUser.kullaniciAdi);
        printf("\n\t\t\t                       Þifrenizi Giriniz : ");
        scanf("%s", newUser.sifre);
        char sifreTekrar[MAX_SIFRE_LENGTH];
        printf("\n\t\t\t                       Þifrenizi Tekrar Giriniz : ");
        scanf("%s", sifreTekrar);
        if (strcmp(newUser.sifre, sifreTekrar) != 0) 
		{
			system("cls");
			printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::::::::");
        	printf("\n\t\t\t                       ::                                                 ::");
        	printf("\n\t\t\t                       ::  Þifreler eþleþmiyor, lütfen tekrar deneyiniz.  ::");
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
   		printf("\n\t\t\t                       ::  Kaydýnýz Baþarýyla Oluþturulmuþtur  ::");
   		printf("\n\t\t\t                       ::                                      ::");
   		printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::\n\n");
   		Sleep(2000);
    }
    system("cls");
    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
   	printf("\n\t\t\t                       ::     Giriþ Menüsü Ýçin 1'e Basýnýz    ::");
   	printf("\n\t\t\t                       ::  Ana Menüye Dönmek Ýçin 2'ye Basýnýz ::");
   	printf("\n\t\t\t                       ::     Çýkýþ Yapmak Ýçin 3'e Basýnýz    ::");
    printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::\n\n");
    printf("\n\t\t\t           SEÇÝMÝNÝZ :");
    scanf("\n\t\t\t%d", &kayitSecim);
    if (kayitSecim == 1)
	{
		system("cls");
		printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                           ::");
    	printf("\n\t\t\t                       ::    Giriþ Menüsüne Yönlendiriliyorsunuz    ::");
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
    	printf("\n\t\t\t                       ::    Ana Menüye Yönlendiriliyorsunuz    ::");
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
    	printf("\n\t\t\t                       ::   Üzgünüz Geçersiz Bir Ýþlem Yaptýnýz   ::");
    	printf("\n\t\t\t                       ::                                         ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::\n\n");
    	Sleep(3000);
    	goto kayitStart;
	}
    return kisiSayac;
}


// KULLANICI GÝRÝÞ YAPMA SAYFASI
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
    printf("\n\t\t\t                       ::     @        LÜTFEN       @     ::");
    printf("\n\t\t\t                       ::     @        GÝRÝÞ        @     ::");
    printf("\n\t\t\t                       ::     @        YAPIN        @     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::\n\n");
    printf("\n\t\t\t                       Kullanýcý Adýnýzý Giriniz : ");
    scanf("%s", kullaniciAdi);
    printf("\n\t\t\t                       Þifrenizi Giriniz : ");
    scanf("%s", sifre);
    for (int i = 0; i < kisiSayac; i++) 
	{
        if (strcmp(kisiler[i].kullaniciAdi, kullaniciAdi) == 0 && strcmp(kisiler[i].sifre, sifre) == 0) 
		{
			system("cls");
            printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                                      ::");
    		printf("\n\t\t\t                       ::       Giriþ Ýþleminiz Baþarýlý       ::");
    		printf("\n\t\t\t                       ::                                      ::");
    		printf("\n\t\t\t                       ::   Ana Menüye Yönlendiriliyorsunuz    ::");
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
   			printf("\n\t\t\t                       ::     Hatalý Kullanýcý Adý Veya Þifre     ::");
   			printf("\n\t\t\t                       ::                                         ::");
   			printf("\n\t\t\t                       ::   Giriþ Menüsüne Yönlendiriliyorsunuz   ::");
   			printf("\n\t\t\t                       ::                                         ::");
   			printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
   			Sleep(2000);
   			goto girisYap;	
            }
            return 1;
    }
    return 0;
}


// PROGRAM BAÞLANGIÇ SAYFASI
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
    printf("\n\t\t\t            *** Lütfen Aþaðýdan Yapmak Ýstediðiniz Ýþlemi Seçiniz ***\n\n");
    printf("\n\t\t\t           :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::     * 1-> Kayýt Olmak Ýçin 1'i Seçiniz.               ::\n");
    printf("\n\t\t\t           ::-------------------------------------------------------::\n");
    printf("\n\t\t\t           ::     * 2-> Giriþ Yapmak Ýçin 2'yi Seçiniz.             ::\n");
    printf("\n\t\t\t           ::-------------------------------------------------------::\n");
    printf("\n\t\t\t           ::     * 3-> Çýkýþ Yapmak Ýcin 3'i Seçiniz.              ::\n");
    printf("\n\t\t\t           :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");
    printf("\n\t\t\t           SEÇÝMÝNÝZ :");
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
    	printf("\n\t\t\t                       ::      Geçersiz Bir Ýþlem Yaptýnýz      ::");
    	printf("\n\t\t\t                       ::    Ana Menüye Yönlendiriliyorsunuz    ::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
		Sleep(3000);
        girisMenu();
        break;
    }
}


// ANA MENÜ SAYFASI
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
    printf("\n\t\t\t              *** Lütfen Aþaðýdan Yapmak Ýstediðiniz Ýþlemi Seçiniz ***\n\n");
    printf("\n\t\t\t          ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t          ::    * 1-> Bilgisayar Kiralama Ýþlemleri Ýçin 1'i Seçiniz.           ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 2-> Yiyecek Menüsünü Görmek Ýçin 2'yi Seçiniz.                ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 3-> VR Gözlük Kiralama Ýþlemi Ýçin 3'i Seçiniz.               ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 4-> Sayý Tahmin Etme Oyunu Ýçin 4'ü Seçiniz.                  ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 5-> Kayýtlý Kullanýcýlarý Görüntülemek Ýçin 5'i Seçiniz.      ::\n");
    printf("\n\t\t\t          ::--------------------------------------------------------------------::\n");
    printf("\n\t\t\t          ::    * 6-> Çýkýþ Yapmak Ýçin 6'yý Seçiniz.                           ::\n");
    printf("\n\t\t\t          ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");
    printf("\n\t\t\t           SEÇÝMÝNÝZ :");
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
    	printf("\n\t\t\t                       ::      Geçersiz Bir Ýþlem Yaptýnýz      ::");
    	printf("\n\t\t\t                       ::    Ana Menüye Yönlendiriliyorsunuz    ::");
    	printf("\n\t\t\t                       ::                                       ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::");
    	Sleep(3000);
        anaMenu();
        break;
    }
}


// SAYI TAHMÝN ETME OYUNU 
void sayiOyun()
{
    system("cls");
	system("color 3");
	int sayi, tahmin, donus;
  	srand ( time(NULL) );
  	sayi = rand() % 10 + 1;
  	int deneme = 0;
  	printf("\n\t\t\t           :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           :: ************ SAYI TAHMÝN ETME OYUNUNA HOÞGELDÝNÝZ *********** ::\n");
    printf("\n\t\t\t           ::---------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::           1 Ýle 10 Arasýnda Bir Sayýyý Doðru Tahmin           ::\n");
    printf("\n\t\t\t           ::---------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::       Ederseniz Bizden 1 Saatlik Bir Kupon Kazanacaksýnýz     ::\n");
    printf("\n\t\t\t           ::***************************************************************::\n");
    printf("\n\t\t\t           ::***************************************************************::\n");
    printf("\n\t\t\t           ::                Toplam 3 Hakkýnýz Bulunmaktadýr                ::\n");
    printf("\n\t\t\t           ::---------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::                       Ýyi Þanslar Dileriz                     ::\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");

  	for (deneme = 0; deneme < 3 ; deneme++) 
  	{
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                        ::");
   		printf("\n\t\t\t                       ::   1 Ýle 10 Arasýnda Bir Sayý Giriniz   ::");
    	printf("\n\t\t\t                       ::                                        ::");
    	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::\n\n");
    	printf("\n\t\t\t                       TAHMÝNÝNÝZ :");
        scanf("\n\t\t\t%d", &tahmin);

      if(tahmin == sayi)
	  	{
	  		start:
            system("cls");
        	printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                            ::");
   			printf("\n\t\t\t                       ::   Tebrikler! Kazandýnýz!   ::");
    		printf("\n\t\t\t                       ::                            ::");
    		printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::\n\n");
    		printf("\n\t\t\t        :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t        ::   Tekrar oynamak için 1'e Ana menüye Dönmek Ýçin 2'ye Basýnýz   ::");
            printf("\n\t\t\t        :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
    		printf("\n\t\t\t        SEÇÝMÝNÝZ :");
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
   				printf("\n\t\t\t                       ::   Geçersiz Bir Ýþlem Yaptýnýz   ::");
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
   			printf("\n\t\t\t                              ::   Tahmininiz Çok Yüksek   ::");
    		printf("\n\t\t\t                              ::                           ::");
    		printf("\n\t\t\t                              :::::::::::::::::::::::::::::::\n");
		}
        else if(tahmin < sayi)
		{
			system("cls");
			printf("\n\t\t\t                              ::::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                              ::                          ::");
   			printf("\n\t\t\t                              ::   Tahmininiz Çok Düþük   ::");
    		printf("\n\t\t\t                              ::                          ::");
    		printf("\n\t\t\t                              ::::::::::::::::::::::::::::::\n");
        }
  	}
  	        system("cls");
        	printf("\n\t\t\t                       :::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                         ::");
   			printf("\n\t\t\t                       ::   Üzgünüz Kaybettiniz   ::");
    		printf("\n\t\t\t                       ::                         ::");
    		printf("\n\t\t\t                       :::::::::::::::::::::::::::::\n\n");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::");
    		printf("\n\t\t\t                       ::                         ::");
   			printf("\n\t\t\t                       ::   Doðru Sayý : %d        ::",sayi);
    		printf("\n\t\t\t                       ::                         ::");
    		printf("\n\t\t\t                       :::::::::::::::::::::::::::::\n\n");
            Sleep(2000);
            anaMenu();
}


// VR GÖZLÜK TÝPLERÝNÝ GÖRÜNTÜLEME VE KÝRALAMA ÝÞLEMLERÝ MENÜSÜ  
void vrMenu()
{
   	system("cls");
	system("color 3");
	struct kisi kisiler[MAX_USERS];
    int kisiSayac = kullaniciYukle(kisiler);
    CVVdogrula dogrula = { kisiler, kisiSayac };
	int secim, vrSecim, sure;
	int htc=100, samsung=190, meta=170, hp=120, oculus=220, pico=150, total = 0;
	printf("\n\t\t\t                *** VR Gözlükler Aþaðýda Listelenmektedir ***\n\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::          NO          MARKA            FÝYAT          ::\n");
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
    printf("\n\t\t\t                       *** Ücretlerimiz Saatliktir ***            \n\n");
    printf("\n\t\t\t           Lütfen Kiralamak Ýstediðiniz VR Gözlüðü Seçiniz :");
    scanf("\n\t\t\t%d", &secim);
    if (secim > 6)
	{
        system("clear");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::::");
    	printf("\n\t\t\t                       ::                                             ::");
    	printf("\n\t\t\t                       ::   Üzgünüz Aradýðýnýz VR Gözlüðü Bulamadýk   ::");
    	printf("\n\t\t\t                       ::                                             ::");
    	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::::::");
        sleep(3);
        vrMenu();
    }
	else
	{
        printf("\n\t\t\t           VR Gözlüðü Kaç Saat Kiralamak Ýstiyorsunuz      :");
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
        printf("\n\t\t\t           Lütfen Kart CVV Numaranýzý Giriniz: ");
        char cvvInput[MAX_KARTCVV_LENGTH];
        scanf("%s", cvvInput);
        if (dogrulaCVV(&dogrula, cvvInput))
		{
            while (1)
			{
                system("cls");
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                printf("\n\t\t\t       ::   Seçtiðiniz VR Gözlük Ýçin Toplam Ödeyeceðiniz Ücret %d TL'dir  ::", total);
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
                printf("\n\t\t\t              ********************************************************");
                printf("\n\t\t\t              *   Onaylýyorsanýz 1'e Onaylamýyorsanýz 2'ye Basýnýz   *");
                printf("\n\t\t\t              ********************************************************\n\n");
                printf("\n\t\t\t       SEÇÝMÝNÝZ :");
                scanf("%d", &vrSecim);
                if (vrSecim == 1)
				{
                    system("cls");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::            Ýþleminiz Baþarýyla Gerçekleþmiþtir              ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::         Kalacaðýnýz Süre Boyunca Kafemizde Bulunan          ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::    Yiyecek Ve Ýçecek Menümüzede Bakmanýzý Tavsiye Ederiz    ::");
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
                    printf("\n\t\t\t                       ::     Ýþleminiz Ýptal Edilmiþtir...    ::");
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
                    printf("\n\t\t\t                       ::   Üzgünüz Geçersiz Bir Ýþlem Yaptýnýz   ::");
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
            printf("\n\t\t\t                       ::      Geçersiz CVV Numarasý      ::");
            printf("\n\t\t\t                       ::     Lütfen Tekrar Deneyiniz     ::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            sleep(3);
            vrMenu();
        }
    }
}


// YÝYECEK VE ÝÇECEK TÝPLERÝNÝ GÖRÜNTÜLEME VE SATIN AL ÝÞLEMLERÝ MENÜSÜ 
void yiyecekMenu()
{
    system("cls");
	system("color 3");
	struct kisi kisiler[MAX_USERS];
    int kisiSayac = kullaniciYukle(kisiler);
    CVVdogrula dogrula = { kisiler, kisiSayac };
	int total=0, hamburger= 75, patates=30, patso=25, soguk=60, sosisli=85, islak=55, su=20;
	int secim, yiyecekSecim, fiyat;
	printf("\n\t\t\t                    *** Yiyecek Menüleri Aþaðýda Listelenmektedir ***\n\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::          NO               MENÜLER               FÝYAT          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          1             Hamburger & Kola          75 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          2             Patates & Kola            30 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          3             Patso & Ayran             25 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          4             Soðuk Sandviç & Fanta     60 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          5             Sosisli Sandviç & Kola    85 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          6             Islak Hamburger & Kola    55 TL         ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------------------::\n");
    printf("\n\t\t\t           ::          7             Su                        20 TL         ::\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t                             *** Ücretlerimize KDV Dahildir ***              \n\n");
	printf("\n\t\t\t           Lütfen Satýn Almak Ýstediðiniz Menüyü Seçiniz :");
    scanf("\n\t\t\t%d", &secim);
    if (secim > 6)
	{
        system("clear");
        printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                         ::");
        printf("\n\t\t\t                       ::   Üzgünüz Aradýðýnýz Menüyü Bulamadýk   ::");
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
        printf("\n\t\t\t           Lütfen Kart CVV Numaranýzý Giriniz: ");
        char cvvInput[MAX_KARTCVV_LENGTH];
        scanf("%s", cvvInput);
        if (dogrulaCVV(&dogrula, cvvInput))
		{
            while (1)
			{
                 system("cls");
				printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    			printf("\n\t\t\t       ::   Seçtiðiniz Menü Ýçin Toplam Ödeyeceðiniz Ücret %d TL'dir   ::", total);
    			printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
    			printf("\n\t\t\t          ***********************************************************");
    			printf("\n\t\t\t          *   Onaylýyorsanýz 1'e Onaylamýyorsanýz 2'ye Basýnýz      *");
    			printf("\n\t\t\t          ***********************************************************\n\n");
    			printf("\n\t\t\t       SEÇÝMÝNÝZ :");
                scanf("%d", &yiyecekSecim);
                if (yiyecekSecim == 1)
				{
                    system("cls");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    				printf("\n\t\t\t             ::                                                             ::");
    				printf("\n\t\t\t             ::            Ýþleminiz Baþarýyla Gerçekleþmiþtir              ::");
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
                    printf("\n\t\t\t                       ::     Ýþleminiz Ýptal Edilmiþtir...    ::");
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
                    printf("\n\t\t\t                       ::   Üzgünüz Geçersiz Bir Ýþlem Yaptýnýz   ::");
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
            printf("\n\t\t\t                       ::      Geçersiz CVV Numarasý      ::");
            printf("\n\t\t\t                       ::     Lütfen Tekrar Deneyiniz     ::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            sleep(3);
        }
    }
}


// BÝLGÝSAYAR TÝPLERÝNÝ GÖRÜNTÜLEME VE KÝRALAMA ÝÞLEMLERÝ MENÜSÜ 
void pcTip()
{
	system("cls");
	system("color 3");
    struct kisi kisiler[MAX_USERS];
    int kisiSayac = kullaniciYukle(kisiler);
    CVVdogrula dogrula = { kisiler, kisiSayac };
    int secim, pcSecim, sure;
    int msi = 50, acer = 30, asus = 60, apple = 90, hp = 40, lenovo = 70, total = 0;
    printf("\n\t\t\t                *** Bilgisayarlar Aþaðýda Listelenmektedir ***\n\n");
    printf("\n\t\t\t           ::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n\t\t\t           ::          NO          MARKA          FÝYAT          ::\n");
    printf("\n\t\t\t           ::----------------------------------------------------::\n");
    printf("\n\t\t\t           ::          1            MSÝ           50 TL          ::\n");
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
    printf("\n\t\t\t                       *** Ücretlerimiz Saatliktir ***            \n\n");
    printf("\n\t\t\t           Lütfen Kiralamak Ýstediðiniz Bilgisayarý Seçiniz :");
    scanf("%d", &secim);
    if (secim > 6)
	{
        system("clear");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::::::");
        printf("\n\t\t\t                       ::                                              ::");
        printf("\n\t\t\t                       ::   Üzgünüz Aradýðýnýz Bilgisayarý Bulamadýk   ::");
        printf("\n\t\t\t                       ::                                              ::");
        printf("\n\t\t\t                       ::::::::::::::::::::::::::::::::::::::::::::::::::");
        sleep(3);
        pcTip();
    }
	else
	{
        printf("\n\t\t\t           Bilgisayarý Kaç Saat Kiralamak Ýstiyorsunuz      :");
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

        printf("\n\t\t\t           Lütfen Kart CVV Numaranýzý Giriniz: ");
        char cvvInput[MAX_KARTCVV_LENGTH];
        scanf("%s", cvvInput);
        if (dogrulaCVV(&dogrula, cvvInput))
		{
            while (1)
			{
                system("cls");
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                printf("\n\t\t\t       ::   Seçtiðiniz Bilgisayar Ýçin Toplam Ödeyeceðiniz Ücret %d TL'dir   ::", total);
                printf("\n\t\t\t       ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
                printf("\n\t\t\t             ***********************************************************");
                printf("\n\t\t\t             *   Onaylýyorsanýz 1'e Onaylamýyorsanýz 2'ye Basýnýz      *");
                printf("\n\t\t\t             ***********************************************************\n\n");
                printf("\n\t\t\t       SEÇÝMÝNÝZ :");
                scanf("%d", &pcSecim);
                if (pcSecim == 1)
				{
                    system("cls");
                    printf("\n\t\t\t             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::            Ýþleminiz Baþarýyla Gerçekleþmiþtir              ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::         Kalacaðýnýz Süre Boyunca Kafemizde Bulunan          ::");
                    printf("\n\t\t\t             ::                                                             ::");
                    printf("\n\t\t\t             ::    Yiyecek Ve Ýçecek Menümüzede Bakmanýzý Tavsiye Ederiz    ::");
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
                    printf("\n\t\t\t                       ::     Ýþleminiz Ýptal Edilmiþtir...    ::");
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
                    printf("\n\t\t\t                       ::   Üzgünüz Geçersiz Bir Ýþlem Yaptýnýz   ::");
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
            printf("\n\t\t\t                       ::      Geçersiz CVV Numarasý      ::");
            printf("\n\t\t\t                       ::     Lütfen Tekrar Deneyiniz     ::");
            printf("\n\t\t\t                       ::                                 ::");
            printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
            sleep(3);
            pcTip();
        }
    }
}


// ÇIKIÞ SAYFASI  
void cikisYap()
{
    system("cls");
	system("color 4");
	printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @         ÝYÝ         @     ::");
    printf("\n\t\t\t                       ::     @        GÜNLER       @     ::");
    printf("\n\t\t\t                       ::     @                     @     ::");
    printf("\n\t\t\t                       ::     @@@@@@@@@@@@@@@@@@@@@@@     ::");
    printf("\n\t\t\t                       ::                                 ::");
    printf("\n\t\t\t                       :::::::::::::::::::::::::::::::::::::\n\n");
    exit(0);
}
