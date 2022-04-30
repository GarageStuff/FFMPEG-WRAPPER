#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
    //Strings needed
    string outputResolution = "1920x1080";
    string minBitRate = "7000k";
    string maxBitRate = "12000k";
    //string encoder = "hevc_nvenc";
    string encoder = "h264_nvenc";
    string decoder = "cuda";

    string ffmpegPath = R"(c:\subsonic\transcode\ffmpeg_orig.exe -hwaccel cuda )";
    stringstream argstring;
    string str2;
    ofstream myfile;
    string blank = " ";
    string commands = "";
    //iterate over passed-in arguments and add to command string 
    int counter;
    for (counter = 1; counter < argc; counter++)
        {
            //clear the argstring for each iteration
            argstring.str("");
            //replace strings to override command
            if (counter == 4)
               {
                argstring << quoted(outputResolution);
               }
            else if (counter == 10)
                {
                argstring << quoted(minBitRate);
                }
            else if (counter == 12)
            {
                argstring << (maxBitRate);
            }
            else if (counter == 23 || counter == 24)
                {
                argstring << "";
                }
            else if (counter == 6)
            {
                argstring << quoted(encoder);
            }
            else {
                argstring << quoted(('"\%s"', argv[counter]));
            }
            
            commands.append(argstring.str() + blank);
            myfile.open("wrapperlog.txt");
            myfile << quoted(commands);
            myfile.close();
        }

    //assemble final command string
    string str3 = ffmpegPath + commands;
    system(str3.c_str());
    return 0;
}
