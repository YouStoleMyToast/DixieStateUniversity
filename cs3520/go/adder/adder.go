package main

import (
	"fmt"
	"os"
	"strconv"
)

func Not(in chan bool) (out chan bool) {
	out = make(chan bool, 1)
	go func() {
		for {
			out <- !<-in
		}
	}()
	return
}

func And(a, b chan bool) (out chan bool) {
	out = make(chan bool, 1)
	go func() {
		for {
			x := <-a
			y := <-b
			out <- (x && y)
		}
	}()
	return
}

func Nand(a, b chan bool) (out chan bool) {
	out = make(chan bool, 1)
	var temp = make(chan bool, 1)
	go func() {
		for {
			x := <-a
			y := <-b
			temp <- (x && y)
			out <- !<-temp
		}
	}()
	return
}
func Or(a, b chan bool) (out chan bool) {
	out = make(chan bool, 1)
	go func() {
		for {
			x := <-a
			y := <-b
			out <- (x || y)
		}
	}()
	return
}

func Nor(a, b chan bool) (out chan bool) {
	out = make(chan bool, 1)
	go func() {
		for {
			x := <-a
			y := <-b
			out <- !(x || y)
		}
	}()
	return
}

func Xor(a, b chan bool) (out chan bool) {
	out = make(chan bool, 1)
	go func() {
		for {
			x := <-a
			y := <-b
			out <- (x && !y || y && !x)
		}
	}()
	return
}

func Split2(in chan bool) (outa, outb chan bool) {
	outa = make(chan bool,1)
	outb = make(chan bool,1)
	go func() {
		for {
			a := <- in
			outa <- a
			outb <- a
		}
	}()
	return
}

func Split3(in chan bool) (outa, outb, outc chan bool) {
	outa = make(chan bool,1)
	outb = make(chan bool,1)
	outc = make(chan bool,1)
	go func() {
		for {
			a := <-in
			outa <- a
			outb <- a
			outc <- a
		}
	}()
	return
}

func HalfAdder(a, b chan bool) (sum, cout chan bool) {
	a1, a2 := Split2(a)
	b1, b2 := Split2(b)
	sum = Xor(a1, b1)
	cout = And(a2, b2)
	return
}

func FullAdder(a, b, c chan bool) (sum, cout chan bool) {
	a1, a2, a3 := Split3(a)
	b1, b2, b3 := Split3(b)
	c1, c2 := Split2(c)

	w1 := Xor(a1,b1)
	sum = Xor(w1,c1)
	
	
	w2 := Xor(a2,b2)
	t1 := And(w2,c2)
	t2 := And(a3,b3)
	cout = Or(t1,t2)

	return
}
/*
	#from James
	a1, a2 := Split2(a)
	b1, b2 := Split2(b)
	c1, c2 := Split2(c)
	xorout := Xor(a1,b1)
	xor1out,xor2out := Split2(xorout)
	sum = Xor(xor1out,c1)
	and1out := And(xor2out,c2)
	and2out := And(a2,b2)
	cout = Or(and1out, and2out)

	#from .hdl
	w1 := Xor(a1, b1)
	sum = Xor(w1, c1)
	w2 := And(a2, b2)
	t1 := And(w2, c2)
	t2 := And(a3, b3)
	cout = Or(t1, t2)


	#2
	w1 := And(a1, b1)
	w2 := Xor(a2, b2)
	w3 := And(w2, c1)
	cout = Or(w3, w1)
	sum = Xor(b3, c2) 

	#3
	w1 := Xor(a1, b1)
	sum = Xor(w1, c1)
	t1 := Xor(a2, b2)
	t2 := Nand(t1, c2)
	t3 := Nand(a3, b3)
	cout = Nor(t2, t3)
	
*/

func Add32(a, b []chan bool) (sum []chan bool) {
	sum = make([]chan bool, 32)
	var cout chan bool
	sum[0], cout = HalfAdder(a[0], b[0])
	for i:=1;i<32;i++ {
		sum[i], cout = FullAdder(a[i], b[i], cout)
	}
	go func(){
		for {
			<-cout
		}
	}()

	return
}
//float addition
func Sum32(x, y uint32) uint32 {
	a, b := make([]chan bool, 32), make([]chan bool, 32)
	for i, _ := range a {
		a[i] = make(chan bool, 1)
		b[i] = make(chan bool, 1)
	}
	sum := Add32(a, b)
	for bit := uint32(0); bit < 32; bit++ {
		a[bit] <- (x & (1 << bit)) != 0
		b[bit] <- (y & (1 << bit)) != 0
	}
	total := uint32(0)
	for bit := uint32(0); bit < 32; bit++ {
		if <-sum[bit] {
			total += 1 << bit
		}
	}
	return total
}

func add(x, y int) int {
	return x + y
}

func main() {
	fmt.Println("Length of args", len(os.Args))
	if len(os.Args) != 3 {
		fmt.Println("You need three args")
		os.Exit(1)
	}
	fmt.Println(os.Args[1])
	fmt.Println(os.Args[2])
	var a int
	a, _ = strconv.Atoi(os.Args[1])
	var b int
	b, _ = strconv.Atoi(os.Args[2])
	au := uint32(a)
	bu := uint32(b)
	
	fmt.Println(Sum32(au,bu))
}
