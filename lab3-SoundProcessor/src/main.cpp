#include <fstream>

#include "Convert.h"
#include "Parsing.h"

int main(int argc, char** argv) {
	std::optional<ParserResult> pars_in_res = Parsing::parse_input(argc, argv);
	if (!pars_in_res) {
		return 0;
	}
	std::optional<std::vector<Action>> pars_cfg_res = Parsing::parse_cfg(pars_in_res->cfg_file, pars_in_res->input_files.size());
	if (!pars_cfg_res) {
		return 0;
	}
	Convert conv_obj;
	conv_obj.convert(std::move(pars_in_res->input_files), std::move(pars_in_res->output_file), std::move(*pars_cfg_res));
	return 0;
}