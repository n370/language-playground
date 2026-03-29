package main

import (
	"0004/fileutils"
	"fmt"
	"os"
)

func main() {
	cwd, _ := os.Getwd()
	fileContents, err := fileutils.ReadTextFile(cwd + "/data/text.txt")

	if err == nil {
		fmt.Println(fileContents)
	} else {
		fmt.Printf("ERROR PANIC!! %v", err)
	}
}
