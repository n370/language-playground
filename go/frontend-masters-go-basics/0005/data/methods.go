package data

import "fmt"

func (i Instructor) Print() string {
	return fmt.Sprintf("%v, %v, (%d)", i.FirstName, i.LastName, i.Score)
}
