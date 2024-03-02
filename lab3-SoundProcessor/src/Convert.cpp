#include "Convert.h"
#include "MutingConverter.h"
#include "MixConverter.h"
#include "ReverseSecConverter.h"

#include <climits>
#include <iostream>

Convert::Convert() {
	registration();
}

void Convert::registration() {
	factory.register_creator("mute", std::make_shared<Creator<MutingConverter>>());
	factory.register_creator("mix", std::make_shared<Creator<MixConverter>>());
	factory.register_creator("rev", std::make_shared<Creator<ReverseSecConverter>>());
}

void Convert::read_sec(std::ifstream& in, int num) {
	const int n = 44100;
	for (int i = 0; i < n; i++) {
		in.read(reinterpret_cast<char*>(&sec_arrays[num][i]), sizeof(short int));
	}
}

void Convert::write_sec(std::ofstream& out) {
	const int n = 44100;
	for (int i = 0; i < n; i++) {
		out.write(reinterpret_cast<char*>(&sec_arrays[0][i]), sizeof(short int));
	}
}  

void Convert::convert(std::vector<std::ifstream>&& input_files, std::ofstream&& out, std::vector<Action>&& cfg_file) {
	try {
		size_t len_cfg_file = cfg_file.size();
		size_t count_in_files = input_files.size();
		for (int j = 0; j < count_in_files; j++) {
			read_header(input_files[j]);
			int s;
			input_files[j].read((char*)&s, sizeof(s));
			sizes.push_back(s);
		}
		write_header(out);
		out.write((char*)&sizes[0], sizeof(int));
		unsigned int n_sec = sizes[0] / (2 * 44100);
		for (int i = 0; i < n_sec + 1; i++) {
			for (int j = 0; j < count_in_files; j++) {
				if (i == 0) {
					std::array<short int, 44100> a;
					sec_arrays.push_back(a);
				}
				read_sec(input_files[j], j);
			}
			for (int j = 0; j < len_cfg_file; j++) {
				if (i >= cfg_file[j].begin_time && i < cfg_file[j].end_time) {
					auto conv = factory.create(cfg_file[j].converter_name);
					if (conv == nullptr) {
						throw std::string("Undefined converter in config file");
					}
					if (cfg_file[j].additional_stream != 0) {
						conv->run(sec_arrays[0], sec_arrays[cfg_file[j].additional_stream - 1]);
						if (cfg_file[j].end_time == UINT_MAX && sizes[cfg_file[j].additional_stream - 1] / (2 * 44100) < n_sec) {
							cfg_file[j].end_time = sizes[cfg_file[j].additional_stream - 1] / (2 * 44100);
						}
					}
					else {
						conv->run(sec_arrays[0], sec_arrays[0]);
					}
				}
			}
			write_sec(out);
		}
		std::cout << "SUCCESSFUL" << std::endl;
	
	}
	catch (const std::string& str) {
		std::cout << str << std::endl;
	}
}

void Convert::read_header(std::ifstream& in) {
	in.read((char*)wav_h.RIFF, 4);
	if (std::string(wav_h.RIFF) != "RIFF") {
		throw std::string("Invalid input file");
	}
	in.read((char*)&wav_h.chunk_size, sizeof(int));
	in.read((char*)wav_h.WAVE, 4);
	if (std::string(wav_h.WAVE) != "WAVE") {
		throw std::string("Invalid input file");
	}
	in.read((char*)wav_h.fmt, 4);
	if (std::string(wav_h.fmt) != "fmt ") {
		throw std::string("Invalid input file");
	}
	in.read((char*)&wav_h.subchunk1_size, sizeof(int));
	in.read((char*)&wav_h.audio_format, sizeof(short int));
	if (wav_h.audio_format != 1) {
		throw std::string("File audio format is not PCM");
	}
	in.read((char*)&wav_h.num_of_chan, sizeof(short int));
	if (wav_h.num_of_chan != 1) {
		throw std::string("Number of file channels is not mono");
	}
	in.read((char*)&wav_h.samples_per_sec, sizeof(int));
	if (wav_h.samples_per_sec != 44100) {
		throw std::string("Sampling Frequency is not 44100 Hz");
	}
	in.read((char*)&wav_h.bytes_per_sec, sizeof(int));
	if (wav_h.bytes_per_sec != 88200) {
		throw std::string("Invalid input file");
	}
	in.read((char*)&wav_h.block_align, sizeof(short int));
	if (wav_h.block_align != 2) {
		throw std::string("File is not 16-bit mono");
	}
	in.read((char*)&wav_h.bits_per_sample, sizeof(short int));
	if (wav_h.bits_per_sample != 16) {
		throw std::string("File is not 16-bit");
	}
	in.read((char*)wav_h.LIST, 4);
	if (std::string(wav_h.LIST) == "LIST") {
		in.read((char*)&wav_h.list_size, sizeof(int));
		for (int i = 0; i < wav_h.list_size; i++) {
			char sym;
			in.read((char*)&sym, sizeof(sym));
		}
		in.read((char*)wav_h.data, 4);
		if (std::string(wav_h.data) != "data") {
			throw std::string("Invalid input file");
		}
	}
	else if (std::string(wav_h.LIST) != "data") {
		throw std::string("Invalid input file");
	}
}

void Convert::write_header(std::ofstream& out) {
	out.write((char*)wav_h.RIFF, 4);
	out.write((char*)&wav_h.chunk_size, sizeof(int));
	out.write((char*)wav_h.WAVE, 4);
	out.write((char*)wav_h.fmt, 4);
	out.write((char*)&wav_h.subchunk1_size, sizeof(int));
	out.write((char*)&wav_h.audio_format, sizeof(short int));
	out.write((char*)&wav_h.num_of_chan, sizeof(short int));
	out.write((char*)&wav_h.samples_per_sec, sizeof(int));
	out.write((char*)&wav_h.bytes_per_sec, sizeof(int));
	out.write((char*)&wav_h.block_align, sizeof(short int));
	out.write((char*)&wav_h.bits_per_sample, sizeof(short int));
	out.write((char*)"data", 4);
}