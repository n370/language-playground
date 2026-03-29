package main

import (
	"0001/module"
	"fmt"
)

var message = "Hello World!"
var price = 10.0

func main() {
	printData()
	fmt.Println(module.Hello)
	fmt.Print(module.Hello, message, price)
}
