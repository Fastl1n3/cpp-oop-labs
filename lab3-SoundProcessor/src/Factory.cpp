#include "Factory.h"

void Factory::register_creator(std::string converter_name, std::shared_ptr<ICreator> creator) {
	factory_map_.insert({ std::move(converter_name), std::move(creator) });
}

std::shared_ptr<IConverter> Factory::create(const std::string& converter_name) {
	auto it = factory_map_.find(converter_name);
	if (it == factory_map_.end()) {
		return nullptr;
	}
	return it->second->create();
}