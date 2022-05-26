#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#define N 4

using namespace cv;
using namespace std;

mutex incr;
int num = 0;

void decompress(string fname);



void Wait(string f){
    ifstream g;
    while(true){
        g.open(f);
        if(g){
            g.close();
            break;
        }
        g.close();
    }
}



void decompress(string fname){
    incr.lock();
    num++;
    incr.unlock();
    cout<<"Reached here!"<<endl;
    string fn = fname.substr(0,fname.size()-10);
    string fn0 = fn+".tmp";
    popen(("python decrypt.py "+fname+" "+fn+".compressed; echo Done > "+fn0).c_str(),"r");
    Wait(fn0);
    int stat = remove(fn0.c_str());
    

    popen(("python compress.py 1 "+fn+".compressed "+fn+".h265 "+fn+".aac; echo Done > "+fn0).c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());

    popen(("ffmpeg -i " + fn+ ".h265 -c:v libx265 -an -x265-params crf=25 " + fn + "tmp.mp4; echo Done > "+fn0).c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());

   // ffmpeg -i input.mp4 -i input.mp3 -c copy -map 0:v:0 -map 1:a:0 output.mp4
    
    popen(("ffmpeg -i " + fn+ "tmp.mp4 -i "+fn+".aac -c copy -map 0:v:0 -map 1:a:0 " + fn + ".mp4; echo Done > "+fn0).c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());

    stat = remove((fn+".compressed").c_str());
    stat = remove((fn+".h265").c_str());
    stat = remove((fn+".aac").c_str());
    stat = remove((fn+"tmp.mp4").c_str());
    incr.lock();
    num--;
    incr.unlock();
}

int main(int argc, char* argv[]){
    
    ifstream ifs;
    ifs.open(argv[1]);
    string s;
    vector<thread> ts;
   while(ifs >> s){
        while(num > N){}
       // ts.push_back(thread(decompress,s));
       decompress(s);
    }
}