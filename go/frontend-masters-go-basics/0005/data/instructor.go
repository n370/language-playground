package data

type Instructor struct {
	Id        int
	FirstName string
	LastName  string
	Score     int
}

func NewInstructor(firstName string, lastName string) Instructor {
	return Instructor{FirstName: firstName, LastName: lastName}
}
