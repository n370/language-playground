package api

import (
	"0009/data"
	"encoding/json"
	"net/http"
	"strconv"
)

func Get(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-type", "application/json")

	// /api/exhibitions?id=1
	id := r.URL.Query()["id"]

	if id != nil {
		// We try to serve only one
		idNum, err := strconv.Atoi(id[0])

		if err == nil && idNum < len(data.GetAll()) {
			err := json.NewEncoder(w).Encode(data.GetAll()[idNum])

			if err != nil {
				return
			}
		} else {
			http.Error(w, "Invalid Exhibition", http.StatusBadRequest)
		}
	} else {
		// We serve all
		err := json.NewEncoder(w).Encode(data.GetAll())

		if err != nil {
			return
		}
	}
}
