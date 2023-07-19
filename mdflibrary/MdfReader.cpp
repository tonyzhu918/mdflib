﻿/*
* Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#include <string>
#include <msclr/marshal_cppstd.h>

#include "MdfReader.h"

using namespace msclr::interop;

namespace MdfLibrary {

MdfReader::MdfReader(String^ filename) {
   reader_ = new mdf::MdfReader(marshal_as<std::string>(filename)); 
}


MdfReader::~MdfReader() {
  this->!MdfReader();
}

MdfReader::!MdfReader() {
  delete reader_;
  reader_ = nullptr;
}

long long MdfReader::Index::get() {
  return reader_ != nullptr ? reader_->Index(): 0;
}

void MdfReader::Index::set(long long index) {
  if (reader_ != nullptr) {
    reader_->Index(index);
  }
}

String^ MdfReader::Name::get() {
  const auto name = reader_ != nullptr ?
    reader_->ShortName() : std::string();

  array<unsigned char> ^ c_array =
      gcnew array<unsigned char>(name.length());

  for (int i = 0; i < name.length(); i++)
    c_array[i] = name[i];

  System::Text::Encoding ^ u8enc = System::Text::Encoding::UTF8;

  return u8enc->GetString(c_array);
}

MdfFile^ MdfReader::File::get() {
  auto* mdf_file = reader_ != nullptr ?
    const_cast<mdf::MdfFile*>(reader_->GetFile()) : nullptr;
  return mdf_file != nullptr ? gcnew MdfFile(mdf_file) : nullptr;
}

MdfHeader^ MdfReader::Header::get() {
   auto* header = reader_ != nullptr ?
     const_cast<mdf::IHeader*>(reader_->GetHeader()) : nullptr;
   return header != nullptr ? gcnew MdfHeader(header) : nullptr; 
}

MdfDataGroup^ MdfReader::DataGroup::get(size_t index) {
   auto* data_group = reader_ != nullptr ?
     const_cast<mdf::IDataGroup*>(reader_->GetDataGroup(index)) : nullptr;
   return data_group != nullptr ? gcnew MdfDataGroup(data_group) : nullptr;   
}

bool MdfReader::IsOk::get() {
  return reader_ != nullptr ? reader_->IsOk() : false;
}

bool MdfReader::Open() {
  return reader_ != nullptr ? reader_->Open() : false;
}

void MdfReader::Close() {
   if (reader_ != nullptr ) {
     reader_->Open();
   }
}

bool MdfReader::ReadHeader() {
  return reader_ != nullptr ? reader_->ReadHeader() : false;
}

bool MdfReader::ReadMeasurementInfo() {
  return reader_ != nullptr ? reader_->ReadMeasurementInfo() : false;  
}

bool MdfReader::ReadEverythingButData() {
  return reader_ != nullptr ? reader_->ReadEverythingButData() : false;  
}

bool MdfReader::ReadData(MdfDataGroup^ group) {
  const auto* data_group = group->group_;
  return reader_ != nullptr && data_group != nullptr ?
     reader_->ReadData(*data_group) : false;    
}

}

