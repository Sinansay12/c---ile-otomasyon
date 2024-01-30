#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Durak
{
    char ad[80];
    float enlem;
    float boylam;
};

void DurakEkle();
void DurakListeleme();
void DurakArama();
void DurakSil();
void DurakDuzenle();

int main()
{
    char anamenu;
    do
    {
        system("cls");

        cout << "|-------Hosgeldiniz------|" << endl;
        cout << "|      Secim Yapiniz     |" << endl;
        cout << "|   1- Durak Ekleme      |" << endl;
        cout << "|   2- Durak Listeleme   |" << endl;
        cout << "|   3- Durak Arama       |" << endl;
        cout << "|   4- Durak Sil         |" << endl;
        cout << "|   5- Durak Duzenle     |" << endl;
        cout << "|------------------------|" << endl;
        char secim;
        cin >> secim;

        switch (secim)
        {
        case '1':
        {
            DurakEkle();
            break;
        }
        case '2':
        {
            DurakListeleme();
            break;
        }
        case '3':
        {
            DurakArama();
            break;
        }
        case '4':
        {
            DurakSil();
            break;
        }
        case '5':
        {
            DurakDuzenle();
            break;
        }
        }

        cout << "Anamenuye Donmek icin: a basin cikmak icin: c" << endl;
        anamenu = getchar(); // Daha güvenilir bir giriþ alma yöntemi kullanýlabilir.
        anamenu = getchar(); // Ýki kez alýyoruz çünkü biri önceki satýrýn newline karakterini alacak.

    } while (anamenu == 'a');

    return 0;
}

Durak durak;

void DurakEkle()
{
    ofstream yaz("duraklar.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do
    {
        cout << "Durak Adini Giriniz: " << endl;
        cin >> durak.ad;
        cout << "Durak Enlem Giriniz: " << endl;
        cin >> durak.enlem;
        cout << "Durak Boylam Giriniz: " << endl;
        cin >> durak.boylam;
        yaz.write((char *)&durak, sizeof(durak));
        adet++;
        cout << "Baska Durak Eklemek Ister misiniz? (E/H)" << endl;
        cin >> secim;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet Durak eklendi." << endl;

    yaz.close();
}

void DurakListeleme()
{
    ifstream oku("duraklar.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(durak);
    cout << "Toplam Durak Sayisi:" << kayits << endl;

    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(durak));
            oku.read((char *)&durak, sizeof(durak));

            cout << i + 1 << ". Duragin Bilgileri" << endl;
            cout << "Durak Adi: " << durak.ad << endl;
            cout << "Durak Enlemi: " << durak.enlem << endl;
            cout << "Durak Boylami: " << durak.boylam << endl;
        }
    }
    else
        cout << "Kayit Bulunamadi..." << endl;

    oku.close();
}


void DurakArama()
{
    ifstream oku("duraklar.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(durak);

    cout << "Aranacak Durak Adini Giriniz: " << endl;
    char arananAd[80];
    cin >> arananAd;

    bool bulundu = false;
    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(durak));
            oku.read((char *)&durak, sizeof(durak));

            if (strcmp(durak.ad, arananAd) == 0)
            {
                bulundu = true;
                cout << "Bulunan Duragin Bilgileri" << endl;
                cout << "Durak Adi: " << durak.ad << endl;
                cout << "Durak Enlemi: " << durak.enlem << endl;
                cout << "Durak Boylami: " << durak.boylam << endl;
            }
        }
    }

    if (!bulundu)
        cout << "Durak Bulunamadi..." << endl;

    oku.close();
}

void DurakSil()
{
    char silinecekAd[80];
    bool var = false;

    ifstream oku("duraklar.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(durak);

    cout << "Silinecek Durak Adini Giriniz: ";
    cin >> silinecekAd;

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(durak));
        oku.read((char *)&durak, sizeof(durak));

        if (strcmp(durak.ad, silinecekAd) == 0)
        {
            var = true;
            cout << "Silinen Durak: " << endl;
            cout << "Durak Adi: " << durak.ad << endl;
            cout << "Durak Enlemi: " << durak.enlem << endl;
            cout << "Durak Boylami: " << durak.boylam << endl;
            break;
        }
    }

    oku.close();

    if (!var)
    {
        cout << "Durak Bulunamadi..." << endl;
        return;
    }

    ifstream oku2("duraklar.dat", ios::binary | ios::app);
    ofstream yaz("gecici.dat", ios::binary | ios::app);

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku2.seekg(i * sizeof(durak));
        oku2.read((char *)&durak, sizeof(durak));

        if (strcmp(durak.ad, silinecekAd) != 0)
        {
            yaz.write((char *)&durak, sizeof(durak));
        }
    }

    oku2.close();
    yaz.close();

    remove("duraklar.dat");
    rename("gecici.dat", "duraklar.dat");

    cout << "Durak Silindi." << endl;
}

void DurakDuzenle()
{
    char duzenlenecekAd[80];
    bool var = false;

    ifstream oku("duraklar.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(durak);

    cout << "Duzenlenecek Durak Adini Giriniz: ";
    cin >> duzenlenecekAd;

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(durak));
        oku.read((char *)&durak, sizeof(durak));

        if (strcmp(durak.ad, duzenlenecekAd) == 0)
        {
            var = true;
            cout << "Durak Adi: " << durak.ad << endl;
            cout << "Durak Enlemi: " << durak.enlem << endl;
            cout << "Durak Boylami: " << durak.boylam << endl;

            cout << "Yeni Durak Adi: ";
            cin >> durak.ad;
            cout << "Yeni Durak Enlemi: ";
            cin >> durak.enlem;
            cout << "Yeni Durak Boylami: ";
            cin >> durak.boylam;

            break;
        }
    }

    oku.close();

    if (!var)
    {
        cout << "Durak Bulunamadi..." << endl;
        return;
    }

    ofstream yaz("duraklar.dat", ios::binary | ios::app);

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(durak));
        oku.read((char *)&durak, sizeof(durak));
        yaz.write((char *)&durak, sizeof(durak));
    }

    yaz.close();

    cout << "Durak Duzenlendi." << endl;
}

