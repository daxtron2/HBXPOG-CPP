#include "stdafx.h"
#include "helpers.h"
#include <conio.h>
#include <time.h>

std::vector<std::string> Split(std::string str, std::string token)
{
    std::vector<std::string> result{};
    while (str.size())
    {
        auto index{ str.find(token) };
        if (index != std::string::npos)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0)
            {
                result.push_back(str);
            }
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

void GenerateOTP()
{
    std::cout << "How many characters is the message (no spaces): ";

    std::string characterStr{};
    std::cin >> characterStr;

    const int numOfCharacters{ std::stoi(characterStr) };

    std::vector<int> shiftAmt{};
    for (int i = 0; i < numOfCharacters; i++)
    {
        int randShift = rand() % 26;
        shiftAmt.push_back(randShift);
    }

    std::cout << "OTP Generated, press any key to print..." << std::endl;
    _getch();

    for (unsigned int i = 0; i < shiftAmt.size(); i++)
    {
        if (i + 1 != shiftAmt.size())
        {
            std::cout << shiftAmt[i] << '/';
        }
        else
        {
            std::cout << shiftAmt[i] << '\n';
        }
    }

    std::cout << "Would you like to generate a message with this OTP now(Y/N): ";
    std::string yesNo{};
    std::cin >> yesNo;
    if (yesNo == "y" || yesNo == "Y")
    {
        EncryptMessage(shiftAmt);
    }
    else
    {
        return;
    }
}

void DecodeMessage()
{
    std::cout << "Write out the message, do not use spaces: ";
    std::string encodedMsg{};
    std::cin >> encodedMsg;
    std::cout << "Enter the key, seperated by '/': ";

    std::string key{};
    std::cin >> key;

    std::vector<char> encodedMsgVec(encodedMsg.begin(), encodedMsg.end());
    std::vector<std::string> keyVecStr{ Split(key,"/") };

    std::vector<int>keyVecInt{};
    std::vector<char> decodedMsgVec{};

    for (unsigned int i = 0; i < keyVecStr.size(); i++)
    {
        keyVecInt.push_back(std::stoi(keyVecStr[i]));
    }

    for (unsigned int i = 0; i < keyVecStr.size(); i++)
    {
        decodedMsgVec.push_back(Shift(encodedMsgVec[i], keyVecInt[i]));
    }

    std::cout << "Message decoded, press any key to display..." << std::endl;
    _getch();

    for (unsigned int i = 0; i < decodedMsgVec.size(); i++)
    {
        std::cout << decodedMsgVec[i];
    }

    std::cout << std::endl << "Press any key to exit...";
    _getch();
}

void EncryptMessage(std::vector<int> shiftAmt)
{
    std::vector<char> encodedMessage{};

    std::cout << "Enter your message without spaces: ";

    std::string messageToEncode{};
    std::cin >> messageToEncode;

    std::vector<char> messageToEncodeVec(messageToEncode.begin(), messageToEncode.end());
    for (unsigned int i = 0; i < shiftAmt.size(); i++)
    {
        encodedMessage.push_back(Shift(messageToEncodeVec[i], shiftAmt[i] * -1));
    }

    std::cout << "Message encoded, press any key to display..." << std::endl;
    _getch();

    for (unsigned int i = 0; i < encodedMessage.size(); i++)
    {
        std::cout << encodedMessage[i];
    }
    std::cout << std::endl << "Press any key to exit...";
    _getch();
}

void PiOTP()
{
    //constants
    const int PI{ 314159265 };
    const double RANDOM_VEC_SIZE{ 200000000 };

    srand(PI);

    std::vector<int> randomVec{};

    std::cout << "Generating OTPs, please wait..." << std::endl;
    clock_t start{ clock() };
    int gend{};
    for (gend = 0; gend < RANDOM_VEC_SIZE; gend++)//Should only use this mode in release builds, otherwise really slow
    {
        int random{ rand() % 26 };
        //std::cout << (i / RANDOM_VEC_SIZE)*100 << '%' << '\r';
        try
        {
            randomVec.push_back(random);
        }
        catch(...)
        {
            std::cout << "Out of Memory... Ending with " << gend << " generated numbers." << std::endl;
            break;
        }
    }
    
    double execTime{ ((double)clock() - start) / CLOCKS_PER_SEC };
    std::cout << "Finished Generating. Took " << execTime << " seconds" << std::endl;

    bool stayInLoop{ false };
    int charNum{};
    int seqNum{};
    do
    {
        std::cout << "How many characters: ";
        std::string resp1{};
        std::cin >> resp1;
        charNum = std::stoi(resp1);

        std::cout << "Enter a number in the sequence(0 - " << gend - charNum << "): ";
        std::string resp2{};
        std::cin >> resp2;
        seqNum = std::stoi(resp2);

        if (seqNum > RANDOM_VEC_SIZE || charNum + seqNum > RANDOM_VEC_SIZE || seqNum == 0)
        {
            std::cout << "Please choose a lower number in the sequence..." << std::endl;
            _getch();
            stayInLoop = true;
        } else { stayInLoop = false; }
    } while (stayInLoop);
    
    std::vector<int> shiftAmt{};
    for (int i = seqNum; i < seqNum + charNum; i++)
    {
        shiftAmt.push_back(randomVec[i]);
        if (i == seqNum + charNum - 1)
        {
            std::cout << randomVec[i] << std::endl;
        }
        else
        {
            std::cout << randomVec[i] << '/';
        }
    }

    std::cout << std::endl << "Would you like to generate a message with this OTP now(Y/N): ";
    std::string yesNo{};
    std::cin >> yesNo;
    if (yesNo == "y" || yesNo == "Y")
    {
        EncryptMessage(shiftAmt);
    }
    else
    {
        std::cout << "Press any key to exit the program...";
        _getch();
    }

}

char Shift(char letterToShift, int amtToShift)
{
    std::map<char, int> alphabetMap{};
    std::vector<char> alphabet{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

    for (int i = 0; i < 26; i++)
    {
        alphabetMap.insert(std::pair<char, int>(alphabet[i], i));
    }

    int initLetterPlace{ alphabetMap[letterToShift] };
    int newLetterPlace{ initLetterPlace - amtToShift };

    if (newLetterPlace < 0)
    {
        newLetterPlace += 26;
    }
    if (newLetterPlace >= 26)
    {
        newLetterPlace -= 26;
    }

    return alphabet[newLetterPlace];
}