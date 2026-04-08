package main

import (
	"0009/api"
	"0009/data"
	"fmt"
	"net/http"
	"text/template"
)

func handleHello(w http.ResponseWriter, r *http.Request) {
	_, err := w.Write([]byte("Hello from a Go program!!"))

	if err != nil {
		fmt.Println("Error handling request")
	}
}

func handleTemplate(w http.ResponseWriter, r *http.Request) {
	html, err := template.ParseFiles("templates/index.tmpl")

	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		_, err := w.Write([]byte("Internal Server Error"))

		if err != nil {
			return
		}
		return
	}

	err = html.Execute(w, data.GetAll())

	if err != nil {
		return
	}
}

func main() {
	server := http.NewServeMux()
	server.HandleFunc("/hello", handleHello)
	server.HandleFunc("/template", handleTemplate)
	server.HandleFunc("/api/exhibitions", api.Get)
	server.HandleFunc("/api/exhibitions/new", api.Post)

	fs := http.FileServer(http.Dir("./public"))
	server.Handle("/", fs)

	err := http.ListenAndServe(":3333", server)

	if err != nil {
		fmt.Println("Error while opening the server")
	}
}
