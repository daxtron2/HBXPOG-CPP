#pragma once
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <map>
std::vector<std::string> Split(std::string str, std::string token);
void GenerateOTP();
void DecodeMessage();
void EncryptMessage(std::vector<int> shiftAmt);
void PiOTP();
char Shift(char letterToShift, int amtToShift);