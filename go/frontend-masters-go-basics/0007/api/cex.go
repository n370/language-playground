package api

import (
	"0007/datatypes"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"net/http"
	"strings"
	"unicode/utf8"
)

const apiUrl = "https://cex.io/api/ticker/%s/USD"

func GetRate(currency string) (*datatypes.Rate, error) {
	if utf8.RuneCountInString(currency) == 0 {
		return nil, errors.New("invalid currency symbol")
	}

	CURRENCY := strings.ToUpper(currency)

	response, err := http.Get(fmt.Sprintf(apiUrl, CURRENCY))

	if err != nil {
		return nil, err
	}

	var cexResponse CEXResponse

	if response.StatusCode == http.StatusOK {
		bodyBytes, err := io.ReadAll(response.Body)

		if err != nil {
			return nil, err
		}

		err = json.Unmarshal(bodyBytes, &cexResponse)

		if err != nil {
			return nil, err
		}

	} else {
		return nil, fmt.Errorf("shit happened: %v", response.StatusCode)
	}

	rate := datatypes.Rate{Currency: currency, Price: cexResponse.Bid}

	return &rate, nil
}
