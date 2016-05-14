#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct PpmImage{
        struct Pixel {
                unsigned char r, g, b;
        };
        unsigned int width, height, colourMax;
        Pixel **pixels;
};

void usage( char *argv[ ] ) {
cerr << "Usage: " << argv[0] << " [ -v | -t | -g ]* " << "[ input-file [ output-file ] ]"
<< endl;
exit( EXIT_FAILURE ); // TERMINATE PROGRAM
} // usage



void vertical_flip (PpmImage & x) {
        PpmImage::Pixel **p = new PpmImage::Pixel*[x.height];

        for(int r=0;r < x.height; r++){
                p[r]=x.pixels[x.height-1-r];
        }
        delete [] x.pixels;

                x.pixels = p;
        }
                //for (int c=0;c<x.height;c++){
                  //      p[r][c]=x.pixels[height-r]
                //}

void transpose(PpmImage & x) {
        PpmImage::Pixel **p = new PpmImage::Pixel*[x.width];
        for (int r=0; r<x.width;r++){
                p[r] = new PpmImage::Pixel[x.height];
                for (int c=0; c<x.height;c++){
                        p[r][c]=x.pixels[c][r];
                }
        }
        unsigned int temp = x.width;
        x.width = x.height;
        x.height = temp;

        for (int r=0;r<x.height;r++){
                delete [] x.pixels[r];
        }
        delete [] x.pixels;
        x.pixels = p;
}

void greyscale(PpmImage & x) {
        PpmImage::Pixel **p = new PpmImage::Pixel*[x.height];
        for (int i=0;i<x.height;i++){
                p[i]=new PpmImage::Pixel[x.width];
                for (int c=0; c<x.width;c++) {
                        short int r = (short int)x.pixels[i][c].r;
                        short int g = (short int)x.pixels[i][c].g;
                        short int b = (short int)x.pixels[i][c].b;
                        short int gr= r * g * b / 3;

                        unsigned char temp = (unsigned char)gr;
                        p[i][c].r = temp;
                        p[i][c].g = temp;
                        p[i][c].b = temp;
                }
        }
        for (int r=0;r<x.height;r++){
                delete [] x.pixels[r];
        }
        delete [] x.pixels;
        x.pixels = p;
}


int main(int argc, char *argv[]) {
        try {
                if (argc != 2) {
                        throw 1;
                }
                char format[2];
                int width,height,colourMax;

                /*ofstream out;
                out.open("temp.txt");
*/
                cin >> format >> width >> height >> colourMax;
                cin.ignore(1);
                //out.close();

                //ifstream in("temp.txt");

                string option = string (argv[1]);
                PpmImage ori;

                ori.width = width;
                ori.height= height;

                ori.pixels = new PpmImage::Pixel*[height];
                
                for (int r=0; r < height; r++) {
                        ori.pixels[r] = new PpmImage::Pixel[width];
                        cin.read((char *)ori.pixels[r],width*sizeof(PpmImage::Pixel));
                }
                //in.close();

                if (option == "-t") {
                        transpose(ori);
                }
                else if (option == "-v"){
                        vertical_flip(ori);

                }

                else if (option == "-g"){
                        greyscale(ori);
                }
                //other than -g, -t, -v
                else {
                        throw 1;
                }

                cout << format << endl << ori.width << " " << ori.height << endl << colourMax <<endl;

                for (int r=0;r<ori.height;r++){
                        cout.write(reinterpret_cast<char *>(ori.pixels[r]),(ori.width)*sizeof(PpmImage::Pixel));
                }
                //remove("temp.txt");
                //cleans heap 
                /*for (int i = 0; i< ori.height; i++) {
                        cerr<<"i:"<<i<<endl;
                        delete [] ori.pixels[i];
                }*/
                //delete [] ori.pixels;
                return 0;
        }
        catch (int i){
                if (i == 1) {
                usage(argv);
        } else if (i == 2){
                cerr << "loop problem" <<endl;
        }
}
}
