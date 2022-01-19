package main

import "fmt"

func fun1() {
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Println(sum)
}

func fun2() {
	sum := 1
	for sum < 10 {
		sum += sum
	}
	fmt.Println(sum)
}

func main() {
	fun1()
	fun2()
}
