 
#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

using namespace std;

string getPath(int numArgs, char *passedArgs[])
{
    // Get the last position of '/'
    string aux(passedArgs[0]);
    // get '/' or '\\' depending on unix/mac or windows.
#if defined(_WIN32) || defined(WIN32)
    int pos = aux.rfind('\\');
#else
    int pos = aux.rfind('/');
#endif
    // Get the path and the name
    string path = aux.substr(0,pos+1);
    string name = aux.substr(pos+1);
    // show results
    return (path);
    //cout << "Name: " << name << std::endl;

}

bool exists(const char *fileName)
{
	ifstream infile(fileName);
	return infile.good();
}

string exec(const char* cmd) {
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}



int main(int numArgs, char *args[]) 
{
	
	string busyboxPath=getPath(numArgs, args)+"busybox.exe";
	string launcherPath=getPath(numArgs, args)+"launcher.exe";
	
	string updateCMD=busyboxPath+" wget -P "+ getPath(numArgs, args) +" http://files.ultirts.net/newrelease/engine.zip && unzip "+getPath(numArgs, args)+"engine.zip && rm -rf "+getPath(numArgs, args)+"engine.zip && chmod +Xx "+getPath(numArgs, args)+"launcher.exe ";
	system(updateCMD.c_str()); //get the newest version and avoid writing to the actual disk if possible
	
    	return 0;
}
