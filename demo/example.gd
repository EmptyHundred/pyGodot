extends Node


func _ready() -> void:
	var example := PythonInterpreter.new()
	example.print_type(example)
	print(example.run_python("123"))
