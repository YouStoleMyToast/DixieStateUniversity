package main

import (
	"testing"
	"testing/quick"
)

func TestNot(t *testing.T) {
	ch := make(chan bool, 1)
	gate := Not(ch)
	f := func(input []bool) bool {
		for _, elt := range input {
			ch <- elt
			if <-gate != !elt {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}

type BinaryInput struct {
	A bool
	B bool
}

// generic tester for binary gates
// takes a function to create a gate,
// a function to test an individual pair of inputs,
// and the testing object

func testBinaryFunc(ctor func(a, b chan bool) chan bool, test func(a, b bool) bool, t *testing.T) {
	a, b := make(chan bool, 1), make(chan bool, 1)
	gate := ctor(a, b)
	f := func(input []BinaryInput) bool {
		for _, elt := range input {
			a <- elt.A
			b <- elt.B
			if <-gate != test(elt.A, elt.B) {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}

func TestAnd(t *testing.T) {
	testBinaryFunc(And, func(a, b bool) bool { return a && b }, t)
}

func TestNand(t *testing.T) {
	testBinaryFunc(Nand, func(a, b bool) bool { return !(a && b) }, t)
}

func TestOr(t *testing.T) {
	testBinaryFunc(Or, func(a, b bool) bool { return a || b }, t)
}

func TestNor(t *testing.T) {
	testBinaryFunc(Nor, func(a, b bool) bool { return !(a || b) }, t)
}

func TestXor(t *testing.T) {
	testBinaryFunc(Xor, func(a, b bool) bool { return a != b }, t)
}

func TestSplit2(t *testing.T) {
	ch := make(chan bool, 1)
	out1, out2 := Split2(ch)
	f := func(input []bool) bool {
		for _, elt := range input {
			ch <- elt
			r1, r2 := <-out1, <-out2
			if r1 != elt || r2 != elt {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}

func TestSplit3(t *testing.T) {
	ch := make(chan bool, 1)
	out1, out2, out3 := Split3(ch)
	f := func(input []bool) bool {
		for _, elt := range input {
			ch <- elt
			r1, r2, r3 := <-out1, <-out2, <-out3
			if r1 != elt || r2 != elt || r3 != elt {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}

func TestHalfAdder(t *testing.T) {
	a, b := make(chan bool, 1), make(chan bool, 1)
	sum, carry := HalfAdder(a, b)
	f := func(input []BinaryInput) bool {
		for _, elt := range input {
			a <- elt.A
			b <- elt.B
			s := <-sum
			c := <-carry
			if s != (elt.A != elt.B) || c != (elt.A && elt.B) {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}

type TerneryInput struct {
	A bool
	B bool
	C bool
}

func TestFullAdder(t *testing.T) {
	a, b, c := make(chan bool, 1), make(chan bool, 1), make(chan bool, 1)
	sum, carry := FullAdder(a, b, c)
	f := func(input []TerneryInput) bool {
		for _, elt := range input {
			a <- elt.A
			b <- elt.B
			c <- elt.C
			s := <-sum
			c := <-carry
			if s != ((elt.A != elt.B) != elt.C) {
				return false
			}
			if c != (elt.A && elt.B || elt.A && elt.C || elt.B && elt.C) {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}

type Uint32PairInput struct {
	A uint32
	B uint32
}

func TestAdd32(t *testing.T) {
	a, b := make([]chan bool, 32), make([]chan bool, 32)
	for i, _ := range a {
		a[i] = make(chan bool, 1)
		b[i] = make(chan bool, 1)
	}
	sum := Add32(a, b)
	if len(sum) != 32 {
		t.Error("wrong number of bits in return value")
	}
	f := func(input []Uint32PairInput) bool {
		for _, elt := range input {
			for bit := uint32(0); bit < 32; bit++ {
				a[bit] <- (elt.A & (1 << bit)) != 0
				b[bit] <- (elt.B & (1 << bit)) != 0
			}
			total := uint32(0)
			for bit := uint32(0); bit < 32; bit++ {
				if <-sum[bit] {
					total += 1 << bit
				}
			}
			if total != elt.A+elt.B {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}

func TestSum32(t *testing.T) {
	f := func(input []Uint32PairInput) bool {
		for _, elt := range input {
			if Sum32(elt.A, elt.B) != elt.A+elt.B {
				return false
			}
		}
		return true
	}
	if err := quick.Check(f, nil); err != nil {
		t.Error(err)
	}
}
