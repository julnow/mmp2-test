//zamienia odczytane pliki z macro do histogramu
#include "TMath.h"

// dlaczego co jakiś czas jest n_cząstek = 2 i nie ma tych cząstek w pliku tekstowym?
bool sign(int x, int y){ //sprawdza znak ladunku
	if (x>0 && y>0)
		return true;
	else if (x<0 && y<0)
		return true;
	else if (x==y&& y==0)
		return true;
	else
		return false;
}
void hist1(int pId, int pCharge){ //podajemy ID czastki i jej znak (dowolny int, byle mial dobry znak)

	double mean;
	double variance;
	double scaledvar;
	ifstream my_input;
  const char *filename = "mickop2.txt";
  const char *histname1 = "Histogram czastki o ID = ";
  const char *histname2 = to_string(pId).c_str();
	const char *histname3 = ", q = ";
	const char *histname4 = to_string(pCharge).c_str();
  char histname[100];
  strcpy(histname,histname1);
	strcat(histname,histname2);
	strcat(histname, histname3);
	strcat(histname, histname4);
  my_input.open(filename);   //otwieramy plik z danymi

  TH1I *pt_pbpb = new TH1I("Rozklad rodzaju czastek", histname, 100, 0.5, 12); //"czastka nr"+std::to_string(pId)


  long npart1, npart_1, npart101, npart_102;
  int npart, ipass, counter, charge; //l czastek, pass, counter, ladunek
  double pass;
  int id;  //w pliku przechowywane sa pedy poprzeczne
  //int val = 0;
  //while(my_input>>val){
  //while(!my_input.eof()){
  while(my_input.peek() != EOF){
    my_input>>npart>>ipass;
		counter = 0;
		if (npart != 2){ //dla 2 zderzen blad danych
	    my_input>>ipass;
	    for(int i=1; i<=npart; i=i+1){
	      my_input>>pass>>pass>>charge>>pass>>pass>>pass>>pass>>id;        //wczytujemy z pliku kolejne wartosci
	      if (id == pId && sign(charge, pCharge)){
				//	cout <<charge<<endl;
	        counter++;

	      }
	    }
		}
		pt_pbpb->Fill(counter);
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

	//zapis histogramu do pliku
	TFile *flog = new TFile("histogramy.root","recreate");
	flog->cd();
	pt_pbpb->Write();
	flog->Close();

  mean = pt_pbpb->GetMean();
  variance = pt_pbpb->GetStdDev() * pt_pbpb->GetStdDev();
  scaledvar = variance / mean;

	//obliczone dane
	const char *outputname1 = "Dla czastki o ID = ";
  char outputname[100];
	strcpy(outputname,outputname1);
	strcat(outputname,histname2);
	strcat(outputname, histname3);
	strcat(outputname, histname4);
	cout<<outputname<<endl;
  cout<<"srednie odchylenie: "<<mean<<endl;
  cout<<"wariancja: "<<variance<<endl;
  cout<<"wariancja skalowana: "<<scaledvar<<endl;

}
