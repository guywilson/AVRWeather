#include <iostream>
#include <array>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "exception.h"
#include "csvhelper.h"

using namespace std;

CSVHelper::CSVHelper()
{
    vector<string>           header = {"TIME", "TYPE", "TEMPERATURE", "PRESSURE", "HUMIDITY"};

    fptr = fopen("./tph.csv", "at");

    if (fptr == NULL) {
        cout << "Failed to open CSV file: " << strerror(errno) << endl;
        throw new Exception("Error opening CSV file");
    }

    writeHeader(header.size(), header);
}

CSVHelper::~CSVHelper()
{
    fclose(fptr);
}

void CSVHelper::writeHeader(int numColumns, vector<string> & headerArray)
{
    int         i;

    if (headerArray.size() != numColumns) {
        cout << "Error: numColumns " << numColumns << " does not match array size " << headerArray.size() << endl;
        throw new Exception("Array size does not match column count!");
    }

    this->numColumns = numColumns;

    for (i = 0;i< numColumns;i++) {
        fputs(headerArray.at(i).c_str(), fptr);
    }

    fputc('\n', fptr);
}

void CSVHelper::writeRecord(int valueCount, vector<string> & valueArray)
{
    int         i;

    if (valueCount != numColumns || valueArray.size() != numColumns) {
        cout << "Error: valueCount " << valueCount << " does not match columnCount " << numColumns << " previously specified" << endl;
        throw new Exception("Num values does not match column count!");
    }

    for (i = 0;i< valueCount;i++) {
        fputs(valueArray.at(i).c_str(), fptr);
    }

    fputc('\n', fptr);
}

void CSVHelper::addValue(string & szValue)
{
    static int              cellCount = 0;

    if (cellCount < numColumns) {
        fputs(szValue.c_str(), fptr);
    }
    else {
        cellCount = 0;
        fputc('\n', fptr);
    }
}