#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <array>

#include "Parsing.h"
#include "Factory.h"
struct WavHeader {
    char                RIFF[5] = { 0 };        // RIFF Header      Magic header
    unsigned int        chunk_size;      // RIFF Chunk Size  
    char                WAVE[5] = { 0 };        // WAVE Header      
    char                fmt[5] = { 0 };         // fmt header       
    unsigned int        subchunk1_size;  // Size of the fmt chunk                                
    unsigned short int  audio_format;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    unsigned short int  num_of_chan;      // Number of channels 1=Mono 2=Sterio                   
    unsigned int        samples_per_sec;  // Sampling Frequency in Hz                             
    unsigned int        bytes_per_sec;    // bytes per second 
    unsigned short int  block_align;     // 2=16-bit mono, 4=16-bit stereo 
    unsigned short int  bits_per_sample;  // Number of bits per sample      
    char                LIST[5] = { 0 };         // LIST Header
    unsigned int        list_size;       // Size of LIST
    char                data[5] = { 0 };        // "data"  string   
    unsigned int        data_size;  // Sampled data length    

};

class Convert {
    std::vector<std::array<short int, 44100>> sec_arrays;
    std::vector<unsigned int> sizes;
    Factory factory;
    WavHeader wav_h;
    void read_sec(std::ifstream& in, int num);
    void write_sec(std::ofstream& out);
    void read_header(std::ifstream& in);
    void write_header(std::ofstream& out);
    void registration();
public:
    Convert();
    void convert(std::vector<std::ifstream>&& input_files, std::ofstream&& out, std::vector<struct Action>&& cfg_file);
	
};
