// Lift simulator
// CS 3520
package main

import (
	"log"
	"math"
	"math/rand"
	"time"
)

var Pause = time.Second // the length of time to pause between floors and when opening doors
//////////////////////////////////////////////// Controller component ////////////////////////////////////////////////

/////////////////////////////////////////////// A controller component //////////////////////////////////////////////

// Use a pointer to this struct as your handle to a controller.
// Send a Step message to it by sending a destination floor across the Step channel.
// Only the lift should send this message. When NewController returns, the Lift field is nil.
// It should be set to a valid Lift before any messages are sent to the controller.
// The controller assumes that it starts on floor 1 with the motor stopped.
type Controller struct {
	Step chan int
	Lift *Lift
}

//////////////////////////////////////////// Construct a new controller component //////////////////////////////////////////

// Returns a handle to the controller, which runs in its own goroutine.
func NewController() *Controller {
	//cont := &Controller{Step:make(chan int, 1)}//make new controller object
	var controller *Controller
	controller = new(Controller)
	controller.Step = make(chan int, 1)
	go func(controller *Controller) {
		var running bool
		var currfloor = 1
		for {
			if !running {
				goalfloor := <-controller.Step
				if currfloor < 0 {
					running = false
					return //controller shuts down
				} else if currfloor == goalfloor { /*do nothing*/
					running = false
					return
				} else if currfloor > goalfloor { //motor starts(state change), set currfloor=nextfloor down, starts pause timer
					running = true
					currfloor = currfloor - 1
					stop := time.After(Pause)
					<-stop
					return
				} else if currfloor < goalfloor { //motor starts(state change), set currfloor=nextfloor up, starts pause timer
					running = true
					currfloor = currfloor + 1
					stop := time.After(Pause)
					<-stop
					return
				}
			} else if running {
				stop := time.After(Pause)
				<-stop //wait for timer to respond indicates its at next floor
				running = false
				controller.Lift.At <- currfloor //sends at message to lift that it is at a new floor
				return
			}
		}
	}(controller)
	return controller
}

//////////////////////////////////////////////// Lift component ////////////////////////////////////////////////

// A helper function to append a new element to the end of a slice, but only if it does not match the existing last element of the slice.
func scheduleLast(slice []int, elt int) []int {
	var floorlen = len(slice)
	var lastfloor = slice[floorlen]
	if elt != lastfloor {
		slice = append(slice, lastfloor)
	}
	return slice
}

//////////////////////////////////////////////// A lift component ////////////////////////////////////////////////

// Use a pointer to this struct as your handle to a lift.
// Send an At message to it by sending a floor number across the At channel.
// This should only be sent by the lift's controller, and indicates that the lift has arrived at a new floor.
// Send a Call message to it by sending a new destination floor number across the Call channel.
// This can come from a floor component (when someone presses the call button on that floor)
// or directly from a user (when the user is inside the elevator and pushes a button).
// Send a negative value to Call to shut the lift down and end its goroutine.
type Lift struct {
	At   chan int //currfloor -
	Call chan int //goalfloor - comes from floor or inside lift (user pushing buttons of either)
}

//////////////////////////////////////////////// Construct a new lift component ////////////////////////////////////////////////

// Returns a handle to the lift, which runs in its own goroutine.
// number is the lift number (1-based numbering) controller is the controller for this lift.
// floors is a slice of all of the floors in the building. This is a 1-based list, so entry #0 is unused.
// It is okay to pass in a slice of nil values, as long as they are all filled in before any messages are sent to the lift.
func NewLift(number int, controller *Controller, floors []*Floor) *Lift {
	//lift := &Lift{At:make(chan int, 1), Call:make(chan int, 1)} ////look up: composite literal////
	var lift *Lift
	lift = new(Lift)
	lift.At = make(chan int, 1)
	lift.Call = make(chan int, 1)
	var running bool
	//message := make(chan bool, 1)
	var goalstates []int = make([]int,2,20) 
	var ack AckChan = make(AckChan, 1)
	go func(number int, controller *Controller, floors []*Floor, lift *Lift) {
		for {
			select {
			case destination := <-lift.Call: // respond to a Call message
				if destination < 0 { //lift shuts down
					return
				} else if destination > 0 {
					log.Printf("lift: ", controller.Lift, " floor: ", lift.At) //log msg of lift # and floor #
				} else if destination == <- lift.At && !running {
					floors[destination].Arrive <- ack
					<- ack
				} else {
					scheduleLast(goalstates, destination)
					if !running {
						//controller.Step <- message //send controller a step msg
						running = true
						<- controller.Step
					}
				}
			case newFloor := <-lift.At: // respond to an At message
				log.Printf("lift: ", controller.Lift, " floor: ", newFloor) //log msg of lift # and floor #
				if newFloor == goalstates[0] {
					//Arrive := make(chan bool, 1)
					goalstates := goalstates[1:]
					if len(goalstates) == 0 {
						running = false
					} else {
						running = true
						<- controller.Step//send controller a step msg
						//controller.Step <- message //send controller a step msg
						//running = true
					}
				} else {
					lift.At <- newFloor //record your current floor
					//controller.Step <- message
					<- controller.Step 
				}
			}
		}
	}(number, controller, floors, lift)
	return (lift)
}

//////////////////////////////////////////////// Floor component ////////////////////////////////////////////////

// a convenience type representing an acknowledgement channel
type AckChan chan bool

// the states that a floor can be in
type floorState int

const (
	CALLED    floorState = iota // the floor is waiting for a lift to arrive
	NOTCALLED                   // the floor is idle
	DOORSOPEN                   // at least one lift is at this floor with its doors open
)

//////////////////////////////////////////////// A floor component ////////////////////////////////////////////////

// Use a pointer to this struct as your handle to a floor.
// Send a Call message to it by sending a boolean value across the Call channel. This should be send by a user, i.e., it can come from anywhere.
// Send an Arrive message to the lift by sending an AckChan across the Arrive channel.
// This message indicates that a lift has arrived as the result of a user call.
// Its doors are immediately opened, and a boolean should be send across the AckChan when they are closed again.
// This message is only sent by lift components.
// Send a negative value to Call to shut the floor down and end its goroutine.
type Floor struct {
	//two message types
	Call   chan bool    //user waiting on floor calls lift //send a call message to a random lift of the floors choosing
	Arrive chan AckChan //when a lift arrives and opens doors
}

//////////////////////////////////////////////// Construct a new floor component ////////////////////////////////////////////////

// Returns a handle to floor, which runs in its own goroutine.
// number is the floor number (1 based numbering) lifts is a slice containing all the lifts in the building.
// This is a 1-based list, so entry #0 is unused.
// It can contain nil values when NewFloor is called, as long as the lift values are filled in before any messages are send to the floor.
func NewFloor(number int, lifts []*Lift) *Floor {
	//floor := &Floor(Call:make(chan bool, 1),Arrive:make(chan bool, 1))
	var floor *Floor
	floor = new(Floor)
	floor.Call = make(chan bool, 1)
	floor.Arrive = make(chan AckChan, 1)
	floorstate := NOTCALLED
	go func(num int, liftlist []*Lift, floor *Floor, floorstate floorState) {
		for {
			if floorstate == NOTCALLED {
				select {
				case <- floor.Call:
					log.Printf("floor ", num, " is calling lift: ", "<lift num here>")
					rint := rand.Int()
					liftcount := len(liftlist)
					randlift := int(math.Mod(float64(rint), float64(liftcount)))
					liftlist[randlift] <- num
					floorstate = CALLED
				case <- floor.Arrive:
					log.Printf("Arrived message - Lift: ", "<lift num here>" , " floor: ", num)
					floorstate = DOORSOPEN
					stop := time.After(Pause)
					<- stop
				}
			} else if floorstate == CALLED {
				select {
				case <- floor.Call:
					return
				case <- floor.Arrive:
					log.Printf("lift", "<lift num here>", " has arrived at floor", number)
					stop := time.After(Pause)
					<- stop
					floorstate = DOORSOPEN
				}
			} else if floorstate == DOORSOPEN {
				stop := time.After(Pause)
				<-stop
				log.Printf("doors on floor ", num, " are closing")
				//send message to each acknowledgment channel (one for each lift that has its doors open)
				for i:=0; i<len(liftlist); i++ {
					liftlist[i] = nil
				}
				floorstate = NOTCALLED
				select {
				case <- floor.Arrive:
					//add acknowledgement chan to list of open lifts
				case <- floor.Call:
					return
				}
			} else {
				log.Printf("Error: floorstate not set")
			}
		}
	}(number, lifts, floor, floorstate)
	return(floor)
}

//////////////////////////////////////////////// Building component ////////////////////////////////////////////////

//////////////////////////////////// Construct a new building super-component ///////////////////////////////////////

// Returns the slice of floors and the slice of lifts, given the
// desired number of each. Note that these slices are 1-based, so
// entry #0 in each is unused.
func NewBuilding(nfloors, nlifts int) (floors []*Floor, lifts []*Lift) {
	return
}
func main() {
	//rand.Seed(time.Now().UnixNano())
	//log.Println("Insert your code here")
	//return
	// an example of how to use the components
	floors, lifts := NewBuilding(10, 2)
	floors[9].Call <- true
	time.Sleep(time.Second * 5 / 2)
	floors[10].Call <- true

	time.Sleep(time.Second / 2)
	lifts[1].Call <- 4
	lifts[2].Call <- 5

	time.Sleep(100 * time.Second)
}
