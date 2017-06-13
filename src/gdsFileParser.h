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

#ifndef GDSFILEPARSER_H_
#define GDSFILEPARSER_H_

#include <fstream>
#include <sstream>

namespace gdsfp
{
    class ifstream;
    class gdsFileParser
    {
    public:
        int parse(const char *filePath);

    protected:
        virtual void onParsedGDSVersion(unsigned short version) = 0;
        virtual void onParsedModTime(short year, short month, short day,
                                     short hour, short minute, short sec) = 0;
        virtual void onParsedAccessTime(short year, short month, short day,
                                        short hour, short minute, short sec) = 0;
        virtual void onParsedLibName(const char *libName) = 0;
        virtual void onParsedUnits(double userUnits, double databaseUnits) = 0;
        virtual void onParsedStrName(const char *strName) = 0;
        virtual void onParsedBoundaryStart() = 0;
        virtual void onParsedPathStart() = 0;
        virtual void onParsedBoxStart() = 0;
        virtual void onParsedEndElement() = 0;
        virtual void onParsedEndStructure() = 0;
        virtual void onParsedEndLib() = 0;
        virtual void onParsedColumnsRows(unsigned short columns,
                                         unsigned short rows) = 0;
        virtual void onParsedPathType(unsigned short pathType) = 0;
        virtual void onParsedStrans(short strans) = 0;
        virtual void onParsedPresentation(short font, short valign,
                                          short halign) = 0;
        virtual void onParsedNodeStart() = 0;
        virtual void onParsedTextStart() = 0;
        virtual void onParsedSrefStart() = 0;
        virtual void onParsedArefStart() = 0;
        virtual void onParsedSname(const char *sname) = 0;
        virtual void onParsedString(const char *str) = 0;
        virtual void onParsedPropValue(const char *propValue) = 0;
        virtual void onParsedXY(int count, int x[], int y[]) = 0;
        virtual void onParsedLayer(unsigned short layer) = 0;
        virtual void onParsedWidth(int width) = 0;
        virtual void onParsedDataType(unsigned short dataType) = 0;
        virtual void onParsedTextType(unsigned short textType) = 0;
        virtual void onParsedAngle(double angle) = 0;
        virtual void onParsedMag(double mag) = 0;
        virtual void onParsedBeginExtension(unsigned short bext) = 0;
        virtual void onParsedEndExtension(unsigned short eext) = 0;
        virtual void onParsedPropertyNumber(unsigned short propNum) = 0;
        virtual void onParsedNodeType(unsigned short nodeType) = 0;
        virtual void onParsedBoxType(unsigned short boxType) = 0;

    private:
        void readString(std::stringstream *input, std::string *str);
        void readTimeStamp(std::stringstream *input, short *year, short *month,
                           short *day, short *hour, short *minute, short *sec);
        short readShort(std::ifstream *input);
        short readShort(std::stringstream *input);
        unsigned int readUInt(std::stringstream *input);
        int readInt(std::stringstream *input);
        double readDouble(std::stringstream *input);
        void readHeader(std::stringstream *input);
        void readModTimeStamp(std::stringstream *input);
        void readAccessTimeStamp(std::stringstream *input);
        void parseBuffer(std::stringstream *input);
        void readLibName(std::stringstream *input);
        void readUnits(std::stringstream *input);
        void readStrName(std::stringstream *input);
        void readBoundary(std::stringstream *input);
        void readPath(std::stringstream *input);
        void readNode(std::stringstream *input);
        void readBox(std::stringstream *input);
        void readEndElement(std::stringstream *input);
        void readEndStructure(std::stringstream *input);
        void readEndLib(std::stringstream *input);
        void readColumnRow(std::stringstream *input);
        void readPathType(std::stringstream *input);
        void readStrans(std::stringstream *input);
        void readPresentation(std::stringstream *input);
        void readText(std::stringstream *input);
        void readSref(std::stringstream *input);
        void readAref(std::stringstream *input);
        void readSname(std::stringstream *input);
        void readString(std::stringstream *input);
        void readPropValue(std::stringstream *input);
        void readXY(std::stringstream *input);
        void readLayer(std::stringstream *input);
        void readWidth(std::stringstream *input);
        void readDataType(std::stringstream *input);
        void readTextType(std::stringstream *input);
        void readAngle(std::stringstream *input);
        void readMag(std::stringstream *input);
        void readBeginExtension(std::stringstream *input);
        void readEndExtension(std::stringstream *input);
        void readPropertyNumber(std::stringstream *input);
        void readNodeType(std::stringstream *input);
        void readBoxType(std::stringstream *input);
    };

} // End namespace gdsfp

#endif //GDSFILEPARSER_H_
