#include    <iostream>
#include    <cstdlib>
#include    <vector>
#include    <string>
#define     UINT_LIMIT  100000000
#define     UINT_LIMIT_DIGITS   8

using namespace std;

vector<vector<unsigned int>> parsingExpression(string str);
bool counter(vector<unsigned int> valLine);

string buffer;

vector<vector<unsigned int>> parsingVals;
vector<unsigned int> result1;
vector<unsigned int> result2;
vector<unsigned int> result3;
vector<unsigned int> factor;

long long    tempAdd;
long long    tempCarry;

vector<unsigned int> countLine;

int main()
{
    while (true)
    {
        cout << "Input an exponential expression (positive numbers only) : ";
        cin >> buffer;
        if (!buffer.compare("exit"))
            break;
        parsingVals = parsingExpression(buffer);

        result3 = parsingVals[parsingVals.size() - 1];
        for (int i = parsingVals.size() - 2; i >= 0; i--)
        {
            result3[0]--;
            result1 = factor = parsingVals[i];

            countLine.clear();
            while (counter(result3))
            {
                result2.clear();
                result2.push_back(0);
                for (int j = 0; j < factor.size(); j++)
                {
                    tempCarry = 0;
                    int k;
                    for (k = 0; k < result1.size(); k++)
                    {
                        tempAdd = (long long)factor[j] * (long long)result1[k] + tempCarry;
                        tempCarry = tempAdd / UINT_LIMIT;
                        tempAdd %= UINT_LIMIT;
                        if (result2.size() - 1 < j + k)
                            result2.push_back(0);
                        if (j + k == result2.size()  - 1 && tempCarry > 0)
                            result2.push_back(0);
                        tempCarry += (result2[j + k] + tempAdd) / UINT_LIMIT;
                        result2[j + k] = (result2[j + k] + tempAdd) % UINT_LIMIT;
                    }
                    if (tempCarry > 0)
                        result2[j + k] += tempCarry;
                }
                result1 = result2;
            }
            result3 = result1;  
        }   // The part that calculates the values 
        for (int i = result3.size() - 1; i >= 0; i--)
        {
            if (i == result3.size() - 1)
                cout << result3[i];
            else
            {
                unsigned int tempVal = result3[i];
                int digitNum = 0;
                while (tempVal != 0)
                {
                    tempVal /= 10;
                    digitNum++;
                }
                for (int j = 0; j < UINT_LIMIT_DIGITS - digitNum; j++)
                    cout << "0"; // display result part
                if (digitNum != 0)
                    cout << result3[i];
            }

        }
        cout << endl;
    }

    //  [223][242][353][220][353]
    //  [432][595][242][943][230]
    return 0;
}

vector<vector<unsigned int>> parsingExpression(string str)
{
    vector<unsigned int> indices;
    vector<vector<unsigned int>> resultVals;
    vector<unsigned int> tempValLine;
    unsigned int tempVal;

    indices.push_back(-1);
    for(int i = 0; i < str.size() + 1; i++)
    {
        if(str[i] == '^' || str[i] == '\0')
            indices.push_back(i);
    }
    for(int i = 0; i < indices.size() - 1; i++)
    {
        tempValLine.clear();
        tempValLine.push_back(0);
        for(int j = indices[i] + 1; j < indices[i + 1]; j++)
        {
            tempVal = 0;
            if(str[j] >= '0' && str[j] <= '9')
            {
                for (int k = 0; k < tempValLine.size(); k++)
                {
                    tempValLine[k] *= 10;
                    if(k == 0)
                        tempValLine[k] += str[j] - '0';
                    tempValLine[k] += tempVal;
                    if (tempValLine[k] >= UINT_LIMIT)
                    {
                        tempVal = tempValLine[k] / UINT_LIMIT;
                        tempValLine[k] %= UINT_LIMIT;
                        if(k == tempValLine.size() - 1)
                        {
                            tempValLine.push_back(tempVal);
                            break;
                        }
                    }
                }
            } // "100000000000000"
              // [--0][10]
        }
        resultVals.push_back(tempValLine);
    }

    return resultVals;
}

bool counter(vector<unsigned int> valLine)
{
    bool continueState = false;
    unsigned int i = 0;
    unsigned int matchCount = 0;

    if(countLine.size() == 0)
        countLine.push_back(0);
    while(true)
    {
        if(countLine[i] == valLine[i])
        {
            matchCount++;
            if(matchCount == valLine.size())
            {
                continueState = false;
                break;
            }
        }
        if(countLine[i] == UINT_LIMIT - 1)
        {
            countLine[i] = 0;
            if(countLine.size() < i + 2)
                countLine.push_back(0);
            countLine[++i]++;
        }
        else
        {
            countLine[i]++;
            continueState = true;
            break;
        }
    }
    // [243][423][425]
    //      [  1][  0]

    return continueState;
} 
