# 
# MIT License
# 
# Copyright (c) 2017 EDDR Software, LLC.
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#
# Changes:
# 2017-05-05: First & Last Name: What you did. 
# 2017-06-10: Kevin Nesmith: Initial reading of the index of the OA file.
#


default: 	build

CXX         := /usr/bin/g++
TARGET		:= ../lib/libgdsFileParser.a
TARGET_TEMP	:= gdsFileParser.o
TARGET_TEST := testParser
CXX_FILES 	:= gdsFileParser.cpp
CXX_HEADERS := gdsFileParser.h

clean:
	rm $(TARGET)
	rm $(TARGET_TEMP)
	rm $(TARGET_TEST)

build:
	mkdir -p ../lib
	mkdir -p ../include
	$(CXX) -c -o $(TARGET_TEMP) $(CXX_FILES) $(CXX_LIBS) 
	ar crf $(TARGET) $(TARGET_TEMP)
	cp $(CXX_HEADERS) ../include/
	$(CXX) -o $(TARGET_TEST) main.cpp -I. ../lib/libgdsFileParser.a
