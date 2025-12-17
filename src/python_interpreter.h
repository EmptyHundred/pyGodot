#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

using namespace godot;

class PythonInterpreter : public RefCounted {
	GDCLASS(PythonInterpreter, RefCounted)

protected:
	static void _bind_methods();

public:
	PythonInterpreter() = default;
	~PythonInterpreter() override = default;

	void print_type(const Variant &p_variant) const;
};
