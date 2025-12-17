extends Node


func _ready() -> void:
	var example := PythonInterpreter.new()
	example.print_type(example)
