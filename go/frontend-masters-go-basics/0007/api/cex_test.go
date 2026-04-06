package api_test

import (
	"0007/api"
	"testing"
)

func TestApiCall(t *testing.T) {
	_, err := api.GetRate("")

	if err == nil {
		t.Error()
	}
}
