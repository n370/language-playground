package main

import (
	"fmt"
	"time"
)

func printMessage(text string, channel chan bool) {
	for i := 0; i < 10; i++ {
		fmt.Println(text)
		time.Sleep(400 * time.Millisecond)
	}
	channel <- true
}

func main() {
	channel := make(chan bool)
	go printMessage("Hello World!", channel)
	result := <-channel
	fmt.Println(result)
}
