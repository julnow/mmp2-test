//zamienia odczytane pliki z macro do histogramu
#include "TMath.h"
int nmb = 9999983; //liczba zderzeń
int sample_size = (int)nmb/30; //rozmiar próbki

bool sign(int x, int y){ //sprawdza znak ladunku
	if (x>0 && y>0)
		return true;
	else if (x<0 && y<0)
		return true;
	else if (x!=0&& y==0) //dla 0 suma wszystkich ladunkow niezerowych
		return true;
	else
		return false;
}
void hist2(int pCharge){ //podajemy ID czastki i jej znak (dowolny int, byle mial dobry znak)

	double mean;
	double variance, uvariance;
	double scaledvar, uscaledvar;
	ifstream my_input;
  const char *filename = "julnow1.txt";
  const char *histname1 = "Histogram czastki o q = ";
	const char *histname4 = to_string(pCharge).c_str();
  char histname[100];
  strcpy(histname,histname1);
	strcat(histname, histname4);
  my_input.open(filename);   //otwieramy plik z danymi

  TH1I *pt_pbpb = new TH1I("Rozklad rodzaju czastek", histname, 100, -0.5, 11.5); //"czastka nr"+std::to_string(pId)
	TH1D *war_skal = new TH1D("Rozklad wariancji skal", "wariancja skal", 100, 0, 3); //histogram wariancji skalowanej

	int npart, ipass, counter, charge; //l czastek, pass, counter, ladunek
	double pass;
	int id;  //w pliku przechowywane sa pedy poprzeczne

	while(my_input.peek() != EOF){
		TH1I *tmp = new TH1I("Rozklad do wariancji skal", "war skal", 100, -0.5, 11.5); //tymczasowy histogram do obliczenia wariancji skalowanej próbki
			for (int i=0; i<sample_size;++i){
				my_input>>npart>>ipass;
				counter = 0;
				if (npart != 2){ //dla 2 zderzen blad danych
					my_input>>ipass;
					for(int i=1; i<=npart; i=i+1){
						my_input>>charge>>id;        //wczytujemy z pliku kolejne wartosci
						if (sign(charge, pCharge)){
							counter++;
					}
				}
			}
			pt_pbpb->Fill(counter);
			tmp->Fill(counter);
		}//teraz liczymy dla tymczasowego histogramu (sampling) war skalowaną
		double tmp_mean = tmp->GetMean();
		double tmp_variance = tmp->GetStdDev() * tmp->GetStdDev();
		double tmp_scaledvar = tmp_variance / tmp_mean;
		war_skal->Fill(tmp_scaledvar);
		//cout<<"war skalowana dla tego subsampla "<<tmp_scaledvar<<endl;
	}
	my_input.close();

  //po wczytaniu wszystkich danych histogram jest gotowy
  //mozna go narysowac:
	auto canvas = new TCanvas("c","Panel");
  canvas->SetWindowSize(1200, 800);
	canvas->SetLogy(); //skala log
  pt_pbpb->SetFillColor(4);
  pt_pbpb->SetBarWidth(5.0);
  pt_pbpb->SetBarOffset(-2.0);
  pt_pbpb->Draw("BAR3");

	//zapis histogramu do png
	char histfile[100] = "";
	const char *png = ".png";
	const char *histfile1 = "_";
	strcat(histfile, histfile1);
	strcat(histfile, histname4);
	strcat(histfile, png);
	//cout <<histfile<<endl;
	canvas->Print(histfile);

	//statystki zderzenia
	mean = pt_pbpb->GetMean();
	variance = pt_pbpb->GetStdDev() * pt_pbpb->GetStdDev();
	uvariance = 2*variance * pt_pbpb->GetStdDevError();
	scaledvar = variance / mean;
	uscaledvar = war_skal->GetStdDev();

	//obliczone dane

  char outputname[100];
	const char *outputname1 = "Dla czastek o q = ";
	strcpy(outputname,outputname1);
	strcat(outputname, histname4);
	cout<<outputname<<endl;
  cout<<"srednie odchylenie: "<<mean<<endl;
  cout<<"wariancja: "<<variance<<endl;
  cout<<"wariancja skalowana: "<<scaledvar<<endl;
	cout<<"niepewność wariancji skalowanej :"<<uscaledvar<<endl;

}
