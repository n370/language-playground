package main

import (
	"fmt"
	"net/http"
)

func handleHello(w http.ResponseWriter, r *http.Request) {
	_, err := w.Write([]byte("Hello from a Go program!"))

	if err != nil {
		fmt.Println("Error handling request")
	}
}

func main() {
	http.HandleFunc("/hello", handleHello)

	err := http.ListenAndServe(":3333", nil)

	if err != nil {
		fmt.Println("Error while opening the server")
	}
}
