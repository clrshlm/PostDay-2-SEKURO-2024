#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

vector<float> hx, hy;
float x = 0, y = 0;
int pos = -1;

void load()
{
    ifstream myf("simpan.txt");
    if (myf.is_open())
    {
        myf>>x>>y;
    }else{
        cout<<"file tidak bisa disimpan"<<endl;
    }
}
void save()
{
    ofstream myf("simpan.txt");
    if (myf.is_open())
    {
        myf<<x<<" "<<y;
    }else{
        cout<<"file tidak bisa disimpan"<<endl;
    }
    myf.close();
}
void lokasi()
{
    cout<<setprecision(2)<<fixed<<"--> Lokasi : [ x = "<<x <<" ] [ y = " << y << " ]" <<endl;
}

void gerak(float xx, float yy)
{
    x += xx; y += yy;
    float tx = round(x * 100);
    float ty = round(y * 100);
    int itx = tx, ity = ty;
    x = (float)itx * 0.01;
    y = (float)ity * 0.01;
    pos++;
    if (pos >= hx.size())
    {
        hx.push_back(x);
        hy.push_back(y);
    }else{
        hx[pos] = x;
        hy[pos] = y;
    }
    lokasi();
}

void gerak_2(float v, float t, float theta)
{
    float phi = M_PI;
    float gx = (v*t) * cos(theta * phi/180);
    float gy = (v*t) * sin(theta * phi/180);
    x += gx;
    y += gy;
    pos++;
    if (pos >= hx.size())
    {
        hx.push_back(x);
        hy.push_back(y);
    }else{
        hx[pos] = x;
        hy[pos] = y;
    }
    lokasi();
}

void undo()
{
    if (pos == -1){
        cout<<"Tidak dapat undo !"<<endl;
    }else{
        pos--;
        x = hx[pos];
        y = hy[pos];
        cout<<"Undo berhasil"<<endl;
    }
    lokasi();
}

void redo()
{
    if (pos + 1 >= hx.size()){
        cout<<"Tidak dapat redo !"<<endl;
    }else{
        pos++;
        x = hx[pos];
        y = hy[pos];
        cout<<"Redo berhasil"<<endl;
    }
    lokasi();
}
int main()
{
    string cmd="";
    cout<<"Help Command : "<<endl;
    cout<<"gerak x y => gerak 8.32931 12.2482"<<endl;
    cout<<"gerak2 v t sudut => gerak2 10 10 30"<<endl;
    cout<<"exit => program selesai"<<endl;

    float p1,p2,p3;
    load();
    lokasi();
    while (cmd!="exit") {
        cout<<"cmd > ";
        cin>>cmd;
        if (cmd == "gerak"){
            cin>>p1>>p2;
            gerak(p1,p2);
        }
        else if (cmd == "gerak2"){
            cin>>p1>>p2>>p3;
            gerak_2(p1,p2,p3);
        }
        else if (cmd == "undo"){
            undo();
        }
        else if (cmd == "redo"){
            redo();
        }
    }
    save();
}
