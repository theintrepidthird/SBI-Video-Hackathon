#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#define N 4

using namespace cv;
using namespace std;

mutex incr;
int num = 0;
int type = 2;


string arr[4][10];
string arr1[4][5];



void compress(string fname);


string getopt(){
    return "--ctu"+arr[type][1]+"--b-adapt"+arr[type][2] + "--rc-lookahead" + arr[type][3] + "--lookahead-slices" + arr[type][4] + "--ref"+arr[type][5] + "--me"+arr[type][6] + "--subme"+arr[type][7] + "--max-merge"+arr[type][8] + "--rdoq-level"+arr[type][9] + arr1[type][1] + arr1[type][2] + arr1[type][3]+ arr1[type][4];

}

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



void compress(string fname){
    incr.lock();
    num++;
    incr.unlock();
    cout<<"Reached here"<<endl;
    string fn = fname.substr(0,fname.size()-4);
    string fn0 = fn+".tmp";
    popen(("ffmpeg -i "+fname+" "+fn+".yuv; echo Done > "+fn0).c_str(),"r");
    Wait(fn0);
    int stat = remove(fn0.c_str());
 //   cout<<"Reached here"<<endl;

    popen(("ffmpeg -i "+fname+" -vn -acodec pcm_s16le -ar 44100 -ac 2 "+fn+".wav; echo Done > "+fn0).c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());
 //   cout<<"Reached here"<<endl;
    popen(("ffmpeg -i "+fn+".wav -c:a aac -q:a 1 "+fn+".aac; echo Done > "+fn0).c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());
  //  cout<<"Reached here"<<endl;
    VideoCapture vid(fname);
    double fps = vid.get(CAP_PROP_FPS);
  //  cout<<"Reached here"<<endl;
    Mat im;
    vid >> im;

    int H = im.cols;
    int W = im.rows;
    
    string comman = "./x265 --input "+fn+".yuv --fps "+to_string(fps) + " --input-res "+to_string(W)+"x"+to_string(H)+" --output "+fn+".raw "+ getopt() + "echo Done > "+fn0;

    popen(comman.c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());
    
    comman = "python compress.py 0 "+ fn + ".raw " + fn + ".aac " + fn+".compressed;" + "echo Done > "+fn0;
    popen(comman.c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());


    comman = "python encrypt.py "+ fn + ".compressed " + fn + ".encrypted" + ";echo Done > "+fn0;
    popen(comman.c_str(),"r");
    Wait(fn0);
    stat = remove(fn0.c_str());
    stat = remove((fn+".yuv").c_str());
    stat = remove((fn+".wav").c_str());
    stat = remove((fn+".aac").c_str());
    stat = remove((fn+".compressed").c_str());
    stat = remove((fn+".raw").c_str());
    incr.lock();
    num--;
    incr.unlock();
}

int main(int argc, char* argv[]){
    arr[0][0] = " 3 ";
    arr[0][1] = " 32 ";
    arr[0][2] = " 0 ";
    arr[0][3] =  " 15 ";
    arr[0][4] =  " 8 ";
    arr[0][5] = " 2 ";
    arr[0][6] = " hex ";
    arr[0][7] = " 2 "; 
    arr[0][8] = " 2 ";
    arr[0][9] = " 0 ";
    
    arr[1][0] = " 4 ";
    arr[1][1] = " 64 ";
    arr[1][2] = " 0 ";
    arr[1][3] =  " 15 ";
    arr[1][4] =  " 8 ";
    arr[1][5] = " 3 ";
    arr[1][6] = " hex ";
    arr[1][7] = " 2 "; 
    arr[1][8] = " 2 ";
    arr[1][9] = " 0 ";

    arr[2][0] = " 5 ";
    arr[2][1] = " 64 ";
    arr[2][2] = " 2 ";
    arr[2][3] =  " 20 ";
    arr[2][4] =  " 8 ";
    arr[2][5] = " 3 ";
    arr[2][6] = " hex ";
    arr[2][7] = " 2 "; 
    arr[2][8] = " 2 ";
    arr[2][9] = " 0 ";

    arr[3][0] = " 6 ";
    arr[3][1] = " 64 ";
    arr[3][2] = " 2 ";
    arr[3][3] =  " 25 ";
    arr[3][4] =  " 4 ";
    arr[3][5] = " 4 ";
    arr[3][6] = " star ";
    arr[3][7] = " 3 "; 
    arr[3][8] = " 3 ";
    arr[3][9] = " 2 ";

    arr1[0][0] = "3";
    arr1[0][1] = "--no-rect ";
    arr1[0][2] = "--no-limit-modes ";
    arr1[0][3] = "--early-skip ";
    arr1[0][4] = "--fast-intra;";

    arr1[1][0] = "4";
    arr1[1][1] = "--no-rect ";
    arr1[1][2] = "--no-limit-modes ";
    arr1[1][3] = "--no-early-skip ";
    arr1[1][4] = "--fast-intra;";

    arr1[2][0] = "5";
    arr1[2][1] = "--no-rect ";
    arr1[2][2] = "--no-limit-modes ";
    arr1[2][3] = "--early-skip ";
    arr1[2][4] = "--no-fast-intra;";

    arr1[3][0] = "6";
    arr1[3][1] = "--rect ";
    arr1[3][2] = "--limit-modes ";
    arr1[3][3] = "--no-early-skip ";
    arr1[3][4] = "--no-fast-intra;";
   // cout<<"Reached here"<<endl;
    ifstream ifs;
   // cout<<"Reached here"<<endl;
    ifs.open(argv[1]);
   // cout<<"Reached here"<<endl;
    string s;
    vector<thread> ts;
    incr.unlock();
   while(ifs >> s){
        while(num > N){}
   //     cout<<"Reached here"<<s<<endl;
   //     ts.push_back(thread(compress,s));
        compress(s);
    }
}