/*******************************************************************************
 
 CoLoRd 
 Copyright (C) 2021, M. Kokot, S. Deorowicz, and A. Gudys
 https://github.com/refresh-bio/CoLoRd

 This program is free software: you can redistribute it and/or modify it under 
 the terms of the GNU General Public License as published by the Free Software 
 Foundation; either version 3 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY 
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR 
 A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this 
 program. If not, see https://www.gnu.org/licenses/.

******************************************************************************/
#pragma once

#include <cstdio>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

class CArchive
{
	bool input_mode;
	FILE* f;
	size_t f_offset;

	struct part_t{
		size_t offset;
		size_t size;

		part_t() : offset(0), size(0)
		{};

		part_t(size_t _offset, size_t _size) : offset(_offset), size(_size)
		{};
	};

	typedef struct {
		string stream_name;
		size_t cur_id;
		size_t raw_size;
		size_t packed_size;
		size_t packed_data_size;
		vector<part_t> parts;
	} stream_t;

	map<size_t, stream_t> m_streams;
	mutex mtx;

	bool serialize();
	bool deserialize();
	size_t write_fixed(size_t x);
	size_t write(size_t x);
	size_t write(string s);
	size_t read_fixed(size_t& x);
	size_t read(size_t& x);
	size_t read(string& s);

public:
	CArchive(bool _input_mode);
	~CArchive();

	bool Open(string file_name);
	bool Close();

	/**
	* @brief Registers a new stream in the archive.
	* @param stream_name - the name of the stream to be registered.
	* @return Returns the identifier of the registered stream.
	*/
	int RegisterStream(string stream_name);

	int GetStreamId(string stream_name);
	
	size_t GetStreamPackedSize(int stream_id)
	{
		lock_guard<mutex> lck(mtx);

		if (stream_id < 0 || stream_id >= static_cast<int>(m_streams.size()))
			return 0;

		return m_streams[stream_id].packed_size;
	}

	size_t GetStreamPackedDataSize(int stream_id)
	{
		lock_guard<mutex> lck(mtx);

		if (stream_id < 0 || stream_id >= static_cast<int>(m_streams.size()))
			return 0;

		return m_streams[stream_id].packed_data_size;
	}

	bool AddPart(int stream_id, vector<uint8_t> &v_data, size_t metadata = 0);
	int AddPartPrepare(int stream_id);
	bool AddPartComplete(int stream_id, int part_id, vector<uint8_t>& v_data, size_t metadata = 0);

	bool GetPart(int stream_id, vector<uint8_t> &v_data, size_t &metadata);
	void SetRawSize(int stream_id, size_t raw_size);
	size_t GetRawSize(int stream_id);

	size_t GetNoStreams()
	{
		lock_guard<mutex> lck(mtx);

		return m_streams.size();
	}
};

// EOF
