#include "python_interpreter.h"

void PythonInterpreter::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PythonInterpreter::print_type);
}

void PythonInterpreter::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}
