package main

import "fmt"

var numberA = 1
var numberB = 1

func operateByValue(number int) int {
	number++
	return number
}

func operateByReference(number *int) int {
	*number++
	return *number
}

func main() {
	fmt.Println("number A: ", numberA)
	fmt.Println("call by value operator")
	var resultA = operateByValue(numberA)
	fmt.Println("result: ", resultA, resultA == numberA)
	fmt.Println("number A: ", numberA)
	fmt.Println("---")
	fmt.Println("number B: ", numberB)
	fmt.Println("call by reference operator")
	var resultB = operateByReference(&numberB)
	fmt.Println("result: ", resultB, resultB == numberB)
	fmt.Println("number B: ", numberB)
}
