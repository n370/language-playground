package main

import (
	"0004/fileutils"
	"fmt"
	"os"
)

func main() {
	cwd, _ := os.Getwd()
	filePath := cwd + "/data/text.txt"
	fileContents, err := fileutils.ReadTextFile(filePath)

	if err == nil {
		fmt.Println(fileContents)
		newContent := fmt.Sprintf("Original: %vDouble original: %v%v", fileContents, fileContents, fileContents)
		fileutils.WriteToFile(filePath+".output.txt", newContent)
	} else {
		fmt.Printf("ERROR PANIC!! %v", err)
	}
}
