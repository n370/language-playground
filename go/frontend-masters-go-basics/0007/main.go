package main

import (
	"0007/api"
	"fmt"
	"sync"
)

func main() {
	currencies := []string{"btc", "eth", "bch"}
	var wg sync.WaitGroup

	for _, currency := range currencies {
		wg.Add(1)
		go func(c string) {
			getCurrencyData(c)
			wg.Done()
		}(currency)
	}

	wg.Wait()
}

func getCurrencyData(currency string) {
	rate, err := api.GetRate(currency)

	if err == nil {
		fmt.Printf("The rate for %v is %.2f\n", rate.Currency, rate.Price)
	}
}
