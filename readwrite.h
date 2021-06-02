#ifndef READWRITE_H
#define READWRITE_H
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

vector<uint8_t> readpgm(int &height, int &width, string &filename)
{

    stringstream ss;
    ifstream infile(filename);

    string inputLine = "";

    getline(infile, inputLine); // read the first line : P5

    if (inputLine.compare("P5") != 0)
        cerr << "Version error" << endl;

    ss << infile.rdbuf(); //read the third line : width and height
    ss >> width >> height;

    int max_val; //maximum intensity value : 255
    ss >> max_val;

    unsigned char pixel;

    vector<uint8_t> PixelArray;

    for (int x = 0; x < width * height; x++)
    {
        ss.read((char *)&pixel, 1);
        PixelArray.push_back(pixel);
    }

    infile.close();

    return PixelArray;
}

void writepgm(vector<uint8_t> newimg, int width, int height,string writtenfile)
{
    ofstream out(writtenfile); //Creating newimg
    out << "P5" << endl<< width << " " << height << endl<< 255 << endl; // headers
    for (int i = 0; i < newimg.size(); i++)
    {
        char ch = (char)newimg[i];
        out.put(ch);
    }
    out.close();
}
#endif // READWRITE_H
