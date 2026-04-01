package main

import (
	"0005/data"
	"fmt"
)

func main() {
	valente := data.NewInstructor("Dylson", "Valente")

	print(valente.Print(), "\n")

	course := data.Course{Name: "Go Fundamentals", Instructor: valente}

	fmt.Printf("%v", course)

	rustWS := data.NewWorkshop("Rust", valente)

	fmt.Printf("%v", rustWS)

	var courses [2]data.Signable
	courses[0] = course
	courses[1] = rustWS

	for _, signable := range courses {
		fmt.Println(signable)
	}

}
