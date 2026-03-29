package fileutils

import "os"

func ReadTextFile(filename string) (string, error) {
	bytes, err := os.ReadFile(filename)

	if err != nil {
		return "", err
	} else {
		return string(bytes), nil
	}
}
