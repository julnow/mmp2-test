//zamienia odczytane pliki z macro do histogramu
#include "TMath.h"

// dlaczego co jakiś czas jest n_cząstek = 2 i nie ma tych cząstek w pliku tekstowym?

void hist1(int pId){

	double mean;
	double variance;
	double scaledvar;
	ifstream my_input;
  const char *filename = "test1.txt";
  const char *histname1 = "Histogram czastki o ID = ";
  const char *histname2 = to_string(pId).c_str();
  char histname[100];
  strcpy(histname,histname1);
	strcat(histname,histname2);
  my_input.open(filename);   //otwieramy plik z danymi

  TH1I *pt_pbpb = new TH1I("Rozklad rodzaju czastek", histname, 100, 0.5, 15); //"czastka nr"+std::to_string(pId)


  long npart1, npart_1, npart101, npart_102;
  int npart, ipass, counter;
  double pass;
  int id;  //w pliku przechowywane sa pedy poprzeczne
  //int val = 0;
  //while(my_input>>val){
  //while(!my_input.eof()){
  while(my_input.peek() != EOF){
    my_input>>npart>>ipass;
		if (npart != 2){ //dla 2 zderzen blad danych
	    my_input>>ipass;
	    counter = 0;
	    for(int i=1; i<=npart; i=i+1){
	      my_input>>pass>>pass>>pass>>pass>>pass>>pass>>pass>>id;        //wczytujemy z pliku kolejne wartosci
	      if (id == pId){
	        counter++;
	      }
	      pt_pbpb->Fill(counter);
	    }
	}
  }
  my_input.close();

  //po wczytaniu wszystkich danych histogram jest gotowy
  //mozna go narysowac:
	auto canvas = new TCanvas("c","Panel");
  canvas->SetWindowSize(1200, 800);
  pt_pbpb->SetFillColor(4);
  pt_pbpb->SetBarWidth(5.0);
  pt_pbpb->SetBarOffset(-2.0);
  pt_pbpb->Draw("BAR3");

  mean = pt_pbpb->GetMean();
  variance = pt_pbpb->GetStdDev() * pt_pbpb->GetStdDev();
  scaledvar = variance / mean;

  cout<<mean<<endl;
  cout<<variance<<endl;
  cout<<scaledvar<<endl;

}
