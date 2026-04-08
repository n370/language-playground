package api

import (
	"0009/data"
	"encoding/json"
	"net/http"
)

func Post(w http.ResponseWriter, r *http.Request) {
	if r.Method == http.MethodPost {
		var e data.Exhibition
		err := json.NewDecoder(r.Body).Decode(&e)
		if err != nil {
			http.Error(w, err.Error(), http.StatusBadRequest)
			return
		}

		data.Add(e)
		w.WriteHeader(http.StatusCreated)
		_, err = w.Write([]byte("OK"))

		if err != nil {
			http.Error(w, err.Error(), http.StatusBadRequest)
			return
		}
	} else {
		http.Error(w, "Unsupported method", http.StatusMethodNotAllowed)
	}
}
