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
#include "defs.h"
#include "params.h"
#include <string>

class CKmerCounter
{
	uint32_t n_reads;
	uint64_t tot_kmers;
	uint64_t n_unique_counted_kmers;
public:
	/**
	* @brief Constructs a k-mer counter with specified parameters.
	* @param k - the length of the k-mers to count.
	* @param ci - the minimum count threshold for k-mers.
	* @param cs - the maximum count threshold for k-mers.
	* @param n_threads - the number of threads to use for counting.
	* @param modulo - modulo parameter for k-mer filtering.
	* @param inputPath - path to the input file containing sequences.
	* @param outPath - path where output results will be saved.
	* @param tmpPath - path for temporary files.
	* @param is_fastq - flag indicating if the input file is in FASTQ format.
	* @param verbose - flag indicating whether to enable verbose output.
	*
	* This constructor initializes a k-mer counter, setting up the necessary parameters
	* for counting k-mers from the provided input file. It prepares to execute an external
	* k-mer counting command, reads k-mer statistics from a generated JSON file,
	* and stores relevant counts of unique k-mers, total k-mers, and reads.
	*/
	explicit CKmerCounter(uint32_t k, uint32_t ci, uint32_t cs, uint32_t n_threads, uint32_t modulo, const std::string& inputPath, const std::string& outPath, const std::string& tmpPath, bool is_fastq, bool verbose);
	uint32_t GetNReads() const { return n_reads; }
	uint64_t GetTotKmers() const { return tot_kmers; }
	uint64_t GetNUniqueCounted() const { return n_unique_counted_kmers; }
};
