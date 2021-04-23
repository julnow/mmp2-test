//C++
#include<iostream>
#include<string>
#include<cmath>
#include<fstream>

#include <cstdlib>
#include <ctime>


using namespace std;



int main(int argc, char* argv[])
{

srand(time(0));
double counterM=0;
double A1=1; //p
double A2=1; //p
double parts=0.0;
double system=A1+A2;   //liczba masowa obu jader


	ifstream fin;
	fin.open(argv[1]);
	//cout << argv[1] << endl;
       //ofstream *out = new ofstream;
       //out->open("input_to_MMP_1.txt");


//total number of events
int NOE=0;
int NOE_FULL=0;

// Define my own variables (number of charged part.)
        int plus;
        int minus;
        int all;
        double plus_pt;
        double minus_pt;
        double plus_ptkw;
        double minus_ptkw;
        double all_pt;
        double all_ptkw;
	int counter1=0;

while(!fin.eof())
{

string linia;
   for(int i=0; i<17; i++) {  //sprawdzic czy 17
   getline(fin,linia);
	//cout << linia << endl;
	if(i==3){
		string STRING2=linia.substr(38,43);
                const char * ble=STRING2.c_str();
                parts=atof(ble);
		//*out << parts << endl;
   	}
   }




NOE=NOE+1;

   int npart, time;
   fin >>npart>>time;

	cout << npart << "\t" << time << endl;

   int a1, a2, a3, a4, a5, a6, a7, a8;
   fin >>a1>>a2>>a3>>a4>>a5>>a6>>a7>>a8;

//a1 -number of collisions; reject events with a1==0

   NOE_FULL=NOE_FULL+1;

   double t, rx, ry, rz, E, px, py, pz, m;
   int id, i3, charge, idlast, colln, hist;

		if(a1!=0 && a3!=0 && npart!=system)
		{
   		cout<<npart<<endl;
		counterM++;

		}


      for(int k=0; k<npart; k++)
      {
      fin >>t>>rx>>ry>>rz>>E>>px>>py>>pz>>m>>id>>i3>>charge>>idlast>>colln>>hist;

	if(a1!=0 && a3!=0 && npart!=system)   //modified 22.08.2010
	{

	cout << charge << "\t" << id << endl;


	}  //if a1!=0, a3, npart
      }  //loop over particles
char c;
fin>>c;



}  //loop over events

return(0);
}  //main
