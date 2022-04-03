#include<bits/stdc++.h>
#include<chrono>

using namespace std;
using namespace std::chrono;
std::random_device r;
std::seed_seq seed{r(), r(), r()};

//auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);

double alpha=0; //growth rate
int N_i = 0;
int t1 =0;
int E=0;
double gap=0;
int filenum =0;



vector<double>particles;
vector<double>interval;
vector<long double>count_t1;

vector<double>mid_size;



string C_vs_x_1;

void static_initialization()
{


    for(double i=0; i<=1.5*N_i; i+=gap)
    {
        interval.push_back(i);
        mid_size.push_back(i+0.5*gap);
        count_t1.push_back(0);

    }







}

void process()
{
     for(int i=0; i<N_i; i++)
  {
      particles.push_back(1);
  }

    int time = 0;

    long double L = (long double) N_i;
    int N = N_i;


    //uniform_int_distribution<int> dist(0,particles.size()-1);

     while (particles.size()!=1)
     {
         int it = particles.size() -1;
         uniform_int_distribution<int> dist(0,it);


         time++;
          int a1 = dist(gen);


     label:
        int a2 = dist(gen);

        if (a1==a2)
        {
            goto label;
        }

         double b1 = particles[a1];
         double b2 = particles[a2];

         double b1_increment = alpha * b1;
         double b2_increment = alpha * b2;

         double b1_total = b1 + b1_increment;
         double b2_total = b2 + b2_increment;

         double b = b1_total + b2_total;
         particles[a1] = b;
         particles[a2] = b;

         int r = particles.size();
         swap(particles[a2], particles[r-1]);
         particles.pop_back();


         if(time==t1)
            {
                for(int i=0;i<particles.size();i++)
                {
                    double p_s = particles[i];
                    for(int j=0;j<interval.size();j++)
                    {
                        if(p_s>interval[j] && p_s<= interval[j+1])
                        {
                            count_t1[j]+=0.00001;
                            break;
                        }
                    }
                }
            }









            L= L- b1-b2 +b;




     }


}


void data_collection()
{

    ofstream f_C1 (C_vs_x_1);





    static_initialization();

    for(int i=0; i<E; i++)
    {

        process();
        vector<double>().swap(particles);

        cout<<"ENSEMBLE "<<i<<" DONE"<<endl;
    }

    for(int i=0; i<interval.size(); i++)
    {
        //if(count_t1[i]!=0){
        f_C1<<mid_size[i]<<"     "<<setprecision(20)<<count_t1[i]*100000.0/(long double)(E*gap)<<endl;




    }







    f_C1.close();


    vector<double>().swap(interval);
    vector<long double>().swap(count_t1);


    vector<double>().swap(mid_size);


}

int main(int argc,char* argv[])
{
    N_i= atoi(argv[1]);
     alpha = atof(argv[2]);
     string alp = (argv[2]);
    t1 = atoi(argv[3]);
    gap = atof(argv[4]);
    E= atoi(argv[5]);
    filenum = atoi(argv[6]);





    C_vs_x_1 = "Sizedist_N" + to_string(N_i) + "_a" + alp + "_t" + to_string(t1) + "_E" + to_string(E) + "_n" + to_string(filenum)+ ".dat";

    data_collection();
    return 0;
}




