package main

import "fmt"

func main() {
	var operation string
	var operand1, operand2 int

	fmt.Println("Go Calculator 1.0")
	fmt.Println("=================")
	fmt.Println("Select an operation (add, subtract, multiply, divide)")
	fmt.Scanf("%s", &operation)
	fmt.Println("Type first operand")
	fmt.Scanf("%d", &operand1)
	fmt.Println("Type second operand")
	fmt.Scanf("%d", &operand2)

	switch operation {
	case "add":
		fmt.Println(operand1 + operand2)
	case "subtract":
		fmt.Println(operand1 - operand2)
	case "multiply":
		fmt.Println(operand1 * operand2)
	case "divide":
		fmt.Println(operand1 / operand2)
	}
}
