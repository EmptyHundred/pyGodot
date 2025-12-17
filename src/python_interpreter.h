#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

using namespace godot;

class PythonInterpreter : public RefCounted {
	GDCLASS(PythonInterpreter, RefCounted)

protected:
	static void _bind_methods();

public:
	PythonInterpreter() = default;
	~PythonInterpreter() override = default;

	void print_type(const Variant &p_variant) const;
	String PythonInterpreter::runPython(String data);
};
