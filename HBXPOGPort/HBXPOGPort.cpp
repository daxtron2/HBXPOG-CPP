// HBXPOGPort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "helpers.h"
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    cout << "To generate OTP type(1)" << endl
         << "To Decode a message type (2)" << endl
         << "Encode a message with a custom OTP type (3)" << endl
         << "Generate a less secure OTP type (4): ";
    
    char initResp{};
    cin >> initResp;

	switch (initResp) 
	{
	case '1': GenerateOTP();
		break;
	case '2': DecodeMessage();
		break;
	case '3': 
	{
		cout << "Enter the key, seperated by '/': ";
		string key{ "" };
		cin >> key;

		vector<string> keyVec{ Split(key,"/") };
		vector<int> keyVecInt{};
		for (unsigned int i = 0; i < keyVec.size(); i++)
		{
			keyVecInt.push_back(stoi(keyVec[i]));
		}

		EncryptMessage(keyVecInt);
		break;
	}
	case '4': PiOTP();
	default: 
		cout << "Incorrect entry, exiting the program..." << endl;
		return -1;
	}
    return 0;
}
