#include "python_interpreter.h"

void PythonInterpreter::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &PythonInterpreter::print_type);
	godot::ClassDB::bind_method(D_METHOD("run_python", "data"), &PythonInterpreter::runPython);
}

void PythonInterpreter::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

String PythonInterpreter::runPython(String data) {
	py::scoped_interpreter guard{};
	String result_value = "";
	py::module_ sys = py::module_::import("sys");
	sys.attr("path")
		.attr("append")("E:/Projects/pyGodot/demo/bin");
	try {
		py::module_ calc= py::module_::import("Main");
		std::string stdstring_foo(data.utf8().get_data());
		py::str py_string(stdstring_foo);
		py::object result = calc.attr("Main")(py_string);
		result_value =String(result.cast<std::string>().c_str());
	} catch(py::error_already_set& e){
		//py::print(e.type());
		//py::print(e.what());
		result_value = String(py::str(e.what()).cast<std::string>().c_str());
		return result_value;
		//py::finalize interpreter();
	}
	return result_value;
}
