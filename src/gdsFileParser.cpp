/*
 * MIT License
 *
 * Copyright (c) 2017 EDDR Software, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Changes:
 * 2017-01-01: First & Last Name: What you did.
 * 2017-06-10: Kevin Nesmith: Initial contribution.
 *
 */

#include "gdsFileParser.h"
#include "gdsCalmaRecords.h"
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

namespace gdsfp
{
    unsigned long p_256[8] = {  0x1, 
                                0x100,
                                0x10000,
                                0x1000000,
                                0x100000000,
                                0x10000000000,
                                0x1000000000000,
                                0x100000000000000 };

    short gdsFileParser::readShort(std::ifstream *input)
    {
        unsigned char p[2];
        input->read((char*)&p, sizeof(p));
        return ((p[0]<<8) | p[1]);
    }

    short gdsFileParser::readShort(stringstream *input)
    {
        unsigned char p[2];
        input->read((char*)&p, sizeof(p));
        return ((p[0]<<8) | p[1]);
    }

    double gdsFileParser::readDouble(stringstream *input)
    {
        short neg = 1;
        unsigned char p[8];
        int exp = 0;
        double man = 0.0;
        input->read((char*)&p, sizeof(p));
        if(p[0]>127){
            neg = -1;
            exp = p[0] - 192;
        }else{
            exp = p[0] - 64;
        }
        for(int i=1; i<8; ++i){
            man+=(double)p[i]/(double)p_256[i];
        }
        return man * pow(16, exp) * neg;
    }

    void gdsFileParser::readString(stringstream *input, string *str)
    {
        string temp = input->str();
        for(string::iterator it = temp.begin(); it!=temp.end(); ++it){
            if((*it)<32||(*it)>127)  // We only want viewable characters.
                continue;
            (*str)+=(*it);
        }
    }

    int gdsFileParser::readInt(stringstream *input)
    {
        unsigned char p[4];
        input->read((char*)&p[0], sizeof(p));
        return ((p[0]<<24) | (p[1]<<16) | (p[2]<<8) | p[3]);
    }

    unsigned int gdsFileParser::readUInt(stringstream *input)
    {
        char p[4];
        input->read((char*)&p[0], sizeof(p));
        return ((p[0]<<24) | (p[1]<<16) | (p[2]<<8) | p[3]);
    }

    void gdsFileParser::readTimeStamp(stringstream *input, short *year, 
                                      short *month, short *day, short *hour, 
                                      short *minute, short *sec)
    {
        (*year) = readShort(input);
        (*month) = readShort(input);
        (*day) = readShort(input);
        (*hour) = readShort(input);
        (*minute) = readShort(input);
        (*sec) = readShort(input);
        if((*year)<1000){
            (*year)+=1900;
        }
    }

    void gdsFileParser::readHeader(stringstream *input)
    {
        onParsedGDSVersion(readShort(input));
    }

    void gdsFileParser::readModTimeStamp(stringstream *input)
    {
        short year, month, day, hour, minute, sec;
        readTimeStamp(input, &year, &month, &day, &hour, &minute, &sec);
        onParsedModTime(year, month, day, hour, minute, sec);
    }
 
    void gdsFileParser::readAccessTimeStamp(stringstream *input)
    {
        short year, month, day, hour, minute, sec;
        readTimeStamp(input, &year, &month, &day, &hour, &minute, &sec);
        onParsedAccessTime(year, month, day, hour, minute, sec);
    }

    void gdsFileParser::readLibName(stringstream *input)
    {
        std::string libName;
        readString(input, &libName);
        onParsedLibName(libName.c_str());
    }

    void gdsFileParser::readUnits(stringstream *input)
    {
        double uu = readDouble(input);
        double db = readDouble(input);
        onParsedUnits(uu, db);
    }

    void gdsFileParser::readStrName(stringstream *input)
    {
        string strName;
        readString(input, &strName);
        onParsedStrName(strName.c_str());
    }

    void gdsFileParser::readBoundary(stringstream *input)
    {
        onParsedBoundaryStart();
    }

    void gdsFileParser::readPath(stringstream *input)
    {
        onParsedPathStart();
    }

    void gdsFileParser::readBox(stringstream *input)
    {
        onParsedBoxStart();
    }

    void gdsFileParser::readEndElement(stringstream *input)
    {
        onParsedEndElement();
    }

    void gdsFileParser::readEndStructure(stringstream *input)
    {
        onParsedEndStructure();
    }

    void gdsFileParser::readEndLib(stringstream *input)
    {
        onParsedEndLib();
    }

    void gdsFileParser::readColumnRow(stringstream *input)
    {
        unsigned short column, row;
        column = readShort(input);
        row = readShort(input);
        onParsedColumnsRows(column, row); 
    }

    void gdsFileParser::readPathType(stringstream *input)
    {
        unsigned short path;
        path = readShort(input);
        onParsedPathType(path);
    }

    void gdsFileParser::readStrans(stringstream *input)
    {
        short strans;
        strans = readShort(input);
        onParsedStrans(strans);
    }

    void gdsFileParser::readPresentation(stringstream *input)
    {
        short present;
        present = readShort(input);
        short font, valign, halign;
        font = (present & (0x10 | 0x20 | 0x30));
        valign = (present & (0x04 | 0x08));
        halign = (present & (0x01 | 0x02));
        onParsedPresentation(font, valign, halign);
    }

    void gdsFileParser::readNode(stringstream *input)
    {
        onParsedNodeStart();
    }

    void gdsFileParser::readText(stringstream *input)
    {
        onParsedTextStart();
    }

    void gdsFileParser::readSref(stringstream *input)
    {
        onParsedSrefStart();
    }

    void gdsFileParser::readAref(stringstream *input)
    {
        onParsedArefStart();
    }

    void gdsFileParser::readSname(stringstream *input)
    {
        string sname;
        readString(input, &sname);
        onParsedSname(sname.c_str());
    }

    void gdsFileParser::readString(stringstream *input)
    {
        string str;
        readString(input, &str);
        onParsedString(str.c_str());
    }

    void gdsFileParser::readPropValue(stringstream *input)
    {
        string prop;
        readString(input, &prop);
        onParsedPropValue(prop.c_str());
    }

    void gdsFileParser::readXY(stringstream *input)
    {
        input->seekp(0, ios::end);
        unsigned int length = input->tellp();
        int count = length/8;
        int x[count];
        int y[count];
        for(int i=0; i<count; ++i){
            x[i] = readInt(input);
            y[i] = readInt(input);
        }
        onParsedXY(count, x, y);
    }

    void gdsFileParser::readLayer(stringstream *input)
    {
        unsigned short layer;
        layer = readShort(input);
        onParsedLayer(layer);
    }

    void gdsFileParser::readWidth(stringstream *input)
    {
        int width;
        width = readInt(input);
        onParsedWidth(width);
    }

    void gdsFileParser::readDataType(stringstream *input)
    {
        unsigned short dataType;
        dataType = readShort(input);
        onParsedDataType(dataType);
    }

    void gdsFileParser::readTextType(stringstream *input)
    {
        unsigned short textType;
        textType = readShort(input);
        onParsedTextType(textType);
    }

    void gdsFileParser::readAngle(stringstream *input)
    {
        double angle;
        angle = readDouble(input);
        onParsedAngle(angle);
    }

    void gdsFileParser::readMag(stringstream *input)
    {
        double mag;
        mag = readDouble(input);
        onParsedMag(mag);
    }

    void gdsFileParser::readBeginExtension(stringstream *input)
    {
        unsigned int bext;
        bext = readInt(input);
        onParsedBeginExtension(bext);
    }

    void gdsFileParser::readEndExtension(stringstream *input)
    {
        unsigned int eext;
        eext = readInt(input);
        onParsedEndExtension(eext);
    }

    void gdsFileParser::readPropertyNumber(stringstream *input)
    {
        unsigned short propNum;
        propNum = readShort(input);
        onParsedPropertyNumber(propNum);
    }

    void gdsFileParser::readNodeType(stringstream *input)
    {
        unsigned short nodeType;
        nodeType = readShort(input);
        onParsedNodeType(nodeType);
    }

    void gdsFileParser::readBoxType(stringstream *input)
    {
        unsigned short boxType;
        boxType = readShort(input);
        onParsedBoxType(boxType);
    }

    void gdsFileParser::parseBuffer(stringstream *input)
    {
        char recType, dataType;
        input->read(&recType, sizeof(recType));
        input->read(&dataType, sizeof(dataType));
        switch(recType){
            case HEADER:        readHeader(input);              break;
            case BGNLIB:        readModTimeStamp(input);
                                readAccessTimeStamp(input);     break; 
            case LIBNAME:       readLibName(input);             break;
            case BGNSTR:        readModTimeStamp(input);
                                readAccessTimeStamp(input);     break; 
            case UNITS:         readUnits(input);               break;
            case STRNAME:       readStrName(input);             break;
            case BOUNDARY:      readBoundary(input);            break;
            case PATH:          readPath(input);                break;
            case ENDEL:         readEndElement(input);          break;
            case ENDSTR:        readEndStructure(input);        break;
            case ENDLIB:        readEndLib(input);              break;
            case COLROW:        readColumnRow(input);           break;
            case PATHTYPE:      readPathType(input);            break;
            case STRANS:        readStrans(input);              break;
            case PRESENTATION:  readPresentation(input);        break;
            case TEXT:          readText(input);                break;
            case SREF:          readSref(input);                break;
            case AREF:          readAref(input);                break;
            case SNAME:         readSname(input);               break;
            case STRING:        readString(input);              break;
            case PROPVALUE:     readPropValue(input);           break;
            case XY:            readXY(input);                  break;
            case LAYER:         readLayer(input);               break;
            case WIDTH:         readWidth(input);               break;
            case DATATYPE:      readDataType(input);            break;
            case TEXTTYPE:      readTextType(input);            break;
            case ANGLE:         readAngle(input);               break;
            case MAG:           readMag(input);                 break;
            case BGNEXTN:       readBeginExtension(input);      break;
            case ENDEXTN:       readEndExtension(input);        break;
            case PROPATTR:      readPropertyNumber(input);      break;
            case NODE:          readNode(input);                break;
            case NODETYPE:      readNodeType(input);            break;
            case BOX:           readBox(input);                 break;
            case BOXTYPE:       readBoxType(input);             break;
            default:
                break;
        }
    }

    int gdsFileParser::parse(const char *filePath)
    {
        std::ifstream gdsFile(filePath, ios::in | ios::binary);
        if(gdsFile.is_open()) {
            stringstream stream( ios::in | ios::out | ios::binary);
            unsigned short length;
            unsigned int total = 0;
            do{
                stream.str("");
                length = readShort(&gdsFile);
                if(length==0){
                    break;  // We have reached the end of the file.
                }
                short sub = sizeof(length);
                char buffer[length - sub];
                gdsFile.read((char*)&buffer, sizeof(buffer));
                total += length;
                stream.write(buffer, length - sub); 
                parseBuffer(&stream);
            } while(gdsFile.good());
        }else{
            cerr << "Error: something is wrong with the file." << endl;
            return 1;
        }

        return 0;
    }
} // End namespace gdsfp
