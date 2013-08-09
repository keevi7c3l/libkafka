//////////////////////////////////////////////////////////////////
//                                                              //
// libkafka - C/C++ client for Apache Kafka v0.8+               //
//                                                              //
// David Tompkins -- 8/8/2013                                   //
// http://dt.org/                                               //
//                                                              //
// Copyright (c) 2013 by David Tompkins.                        //
//                                                              //
//////////////////////////////////////////////////////////////////
//                                                              //
// This program is free software; you can redistribute it       //
// and/or modify it under the terms of the GNU General Public   //
// License as published by the Free Software Foundation.        //
//                                                              //
// This program is distributed in the hope that it will be      //
// useful, but WITHOUT ANY WARRANTY; without even the implied   //
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      //
// PURPOSE. See the GNU General Public License for more details //
//                                                              //
// You should have received a copy of the GNU General Public    //
// License along with this program; if not, write to the Free   //
// Software Foundation, Inc., 59 Temple Place, Suite 330,       //
// Boston, MA 02111-1307 USA                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

#include <RequestOrResponse.h>

using namespace std;

RequestOrResponse::RequestOrResponse(unsigned char *buffer)
{
  cout << "--------------RequestOrResponse()\n";
  this->buffer = buffer;
  this->head = buffer;

  // Kafka Protocol: int32 size
  this->size = read_int32();
}

short int RequestOrResponse::read_int16()
{
  short int value = *(int*)(this->head);
  this->head += sizeof(short int);
  return value;
}

int RequestOrResponse::read_int32()
{
  int value = *(int*)(this->head);
  this->head += sizeof(int);
  return value;
}

string RequestOrResponse::read_string()
{
  short int length = read_int16();
  string value = string((const char *)(this->head), length);
  this->head += length;
  return value;
}